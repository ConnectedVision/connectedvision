/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>

#include <stdlib.h>
#include <stdint.h>

#include <helper.h>

#include "VersionInfo/VersionInfo.h"

#include "ModuleDispatcher.h"
#include "Module/Module_BaseClass.h"

#include "IHTTPAbstraction.h"
#include "HTTP/HTTPServerPoco.h"
#include "HTTP/HTTPSServerPoco.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/asio/ip/host_name.hpp>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <opencv2/highgui/highgui.hpp> // needed for host logo

using namespace std;

using namespace ConnectedVision;
using namespace ConnectedVision::HTTP;
using namespace ConnectedVision::Module;

static bool matches(std::vector<std::string> &path, std::string match, unsigned int pos)
{
	if ( path.size() > pos && path[pos].compare( match ) == 0 )
		return true;
	return false;
}

void ModuleDispatcher::setHostAndSystemID()
{
	boost::uuids::basic_random_generator<boost::mt19937> gen;
	boost::uuids::uuid u = gen();
	hostStatus.set_hostID(boost::uuids::to_string(u));

	hostStatus.set_systemID(boost::asio::ip::host_name());
}

void ModuleDispatcher::initHttpServer(HttpServerParams &httpServerParams)
{
	pHttpServer.reset(new ConnectedVision::HTTP::HTTPServerPoco());
	if (!pHttpServer)
		throw ConnectedVision::runtime_error("error in constructor of ModuleDispatcher: error when creating httpServer");

	pHttpServer->setImplementationCallbackInterface(this);

	pHttpServer->setOption_listeningPort(httpServerParams.listeningPort);
	pHttpServer->setOption_numThreads(httpServerParams.numThreads);
}

void ModuleDispatcher::initHttpsServer(HttpsServerParams &httpsServerParams)
{
	ConnectedVision::HTTP::HTTPSServerPoco::HttpsParams pocoHttpsParams;
	pocoHttpsParams.privateKeyFile = httpsServerParams.privateKeyFile;
	pocoHttpsParams.certificateFile = httpsServerParams.certificateFile;
	pocoHttpsParams.caLocation = httpsServerParams.caLocation;
	pocoHttpsParams.password = httpsServerParams.password;
	pHttpsServer.reset(new ConnectedVision::HTTP::HTTPSServerPoco(pocoHttpsParams));
	if (!pHttpsServer)
		throw ConnectedVision::runtime_error("error in constructor of ModuleDispatcher: error when creating httpsServer");

	pHttpsServer->setImplementationCallbackInterface(this);

	pHttpsServer->setOption_listeningPort(httpsServerParams.listeningPort);
	pHttpsServer->setOption_numThreads(httpsServerParams.numThreads);
}

ModuleDispatcher::ModuleDispatcher(HttpServerParams &httpServerParams) : dataPath( "./data/" )
{
	LOG_SCOPE;

	initHttpServer(httpServerParams);

	//boost::shared_ptr<Logging::ILogWriter> l( new Logging::LogWriterStream(std::cout) );
	//this->setLogWriter( l );
	this->logName = "ModuleDispatcher";

	setHostAndSystemID();

	LOG_INFO("ModuleDispatcher created");
}

ModuleDispatcher::ModuleDispatcher(HttpServerParams &httpServerParams, HttpsServerParams &httpsServerParams) : dataPath( "./data/" )
{
	LOG_SCOPE;

	initHttpServer(httpServerParams);

	initHttpsServer(httpsServerParams);

	//boost::shared_ptr<Logging::ILogWriter> l( new Logging::LogWriterStream(std::cout) );
	//this->setLogWriter( l );
	this->logName = "ModuleDispatcher";

	setHostAndSystemID();

	LOG_INFO("ModuleDispatcher created");
}

ModuleDispatcher::ModuleDispatcher(HttpsServerParams &httpsServerParams) : dataPath( "./data/" )
{
	LOG_SCOPE;

	initHttpsServer(httpsServerParams);

	//boost::shared_ptr<Logging::ILogWriter> l( new Logging::LogWriterStream(std::cout) );
	//this->setLogWriter( l );
	this->logName = "ModuleDispatcher";

	setHostAndSystemID();

	LOG_INFO("ModuleDispatcher created");
}

ModuleDispatcher::~ModuleDispatcher()
{
	LOG_SCOPE;

	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end(); ++it) 
	{
		LOG_INFO("release module: " + (*it)->getModuleName());
		(*it)->releaseModule();
	}
}


std::string ModuleDispatcher::getDataPath() const
{
	return dataPath;
}

void ModuleDispatcher::setDataPath(std::string path)
{
	dataPath = path;
}

void ModuleDispatcher::setLogoPNG(const BufferLogoPNG &logoPNG)
{
	cv::_InputArray input(logoPNG.pBufferLogoAsPNG, logoPNG.sizeBufferLogoAsPNG);
	this->logo = boost::make_shared<cv::Mat>(cv::imdecode(input, cv::IMREAD_COLOR));
}

void ModuleDispatcher::registerModule(boost::shared_ptr<ConnectedVision::Module::IModule> module)
{
	LOG_SCOPE;

	modules.push_back(module);

	LOG_INFO("module " + module->getModuleName() + " registered");
}

/**
 * get module by name
 *
 * @param moduleID		ID of requested module
 *
 * @return module pointer (to NOT delete module)
 */
boost::shared_ptr<ConnectedVision::Module::IModule> ModuleDispatcher::getModule(std::string moduleID) const
{
	LOG_SCOPE;

	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::const_iterator it = modules.begin(); it != modules.end(); ++it) 
	{
		boost::shared_ptr<ConnectedVision::Module::IModule> module = *it;
		if ( moduleID == module->getModuleID() )
			return module;
	}

	boost::shared_ptr<ConnectedVision::Module::IModule> null_ptr;
	return null_ptr;
}



void ModuleDispatcher::start()
{
	LOG_SCOPE;

	if (pHttpServer)
		pHttpServer->start();
	if (pHttpsServer)
		pHttpsServer->start();

	// init / start modules
	LOG_INFO("init modules");
	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end(); ++it) 
	{
		(*it)->initModule( this );
	}
}

void ModuleDispatcher::stop()
{
	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end(); ++it)
	{
		(*it)->releaseModule();
	}

	if (pHttpsServer)
		pHttpsServer->stop();
	if (pHttpServer)
		pHttpServer->stop();
}

/**
 * process an HTTP event
 *
 * @warning This mehtod has to be THREADSAFE
 *
 * @param [in]eventCode	type of event
 * @param [in]connection	current connection
 * @param [in]request	http request
 * @param [out]response	answer to request
 *
 * @return true if event was consumed
 */
bool ModuleDispatcher::handleRequest(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response)
{
	LOG_SCOPE;
		
	bool res = false;

	int status = 0;

	boost::shared_ptr<ConnectedVision::Module::IModule> module;

	LOG_DEBUG("handle new request");

	ConnectedVision::HTTP::EnumConnectedVisionCommandType cmd = request.getCommandType();

	std::string uri = request.getUri();
	
	// remove trailing slash characters
	while (!uri.empty() && uri.back() == '/')
	{
		uri.pop_back();
	}

	std::vector<std::string> uriPath;
	boost::split(uriPath, uri, boost::is_any_of("/"));

	//if(uriPath[0] == "") // if first element is empty - string started with leading slash
	//{
	//	uriPath.erase(uriPath.begin()); // erase this empty element
	//}

	ConnectedVisionResponse responsePayload;

	if ( matches(uriPath, "_post_", 1) ) 
	{
		handlePostRequests(request, response);
		res = true;
	}

	if ( matches(uriPath, "_moduleList_", 1) ) 
	{
		getModuleList(request, response);
		res = true;
	}

	if ( matches(uriPath, "_hostStatus_", 1) ) 
	{
		getHostStatus(request, response);
		res = true;
	}

	if ( matches(uriPath, "_hostLogo_", 1) ) 
	{
		getHostLogoPNG(request, response);
		res = true;
	}

	if ( uriPath.size() > 1 )
	{
		for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end() && !module; ++it) 
		{
			boost::shared_ptr<ConnectedVision::Module::IModule>& m = *it;
			if ( uriPath[1] == (*it)->getModuleID() )
				module = *it;
		}
	}

	if ( module )
	{
		try
		{
			// redmine Issue #623: workaround to prevent crash:
			// before: crash occured when web-url was processed which consisted of the url + "/ModuleName"  of a known module name but without a terminating slash
			// reason was that after parsing the request url the std::vector uriPath contained only 2 instead of 3 elements in this special case
			if (uriPath.size()<3)
			{
				uriPath.push_back("");
			}

			LOG_INFO_CONFIG("request module: " + module->getModuleName() + " -> " + uriPath[2], uriPath[2]);
			LOG_DEBUG_CONFIG("request URI: " + request.getUri(), uriPath[2]);
			LOG_DEBUG_CONFIG("request Command: " + cmd, uriPath[2]);

			if ( matches(uriPath, "init", 2) ) 
			{
				module->initModule( this );
				status = module->getModuleStatus(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "release", 2) ) 
			{
				module->releaseModule();
				status = module->getModuleStatus(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "status", 2) ) 
			{
				status = module->getModuleStatus(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "moduleDescription", 2) ) 
			{
				status = module->getModuleDescription(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "inputDescription", 2) ) 
			{
				status = module->getInputDescription(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "outputDescription", 2) ) 
			{
				status = module->getOutputDescription(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "configListOverview", 2) ) 
			{
				status = getConfigListOverview(request, response);
				responsePayload = response.content;
				res = true;
			}
			else if ( matches(uriPath, "configList", 2) ) 
			{
				status = module->getConfigList(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "configListDetailed", 2) ) 
			{
				status = module->getConfigListDetailed(responsePayload);
				res = true;
			}
			else if ( matches(uriPath, "moduleLogo", 2) ) 
			{
				status = module->getModuleLogo(responsePayload);
				res = true;
			}
			else if ( uriPath.size() > 3 && uriPath[3].length() )
			{
				// job specific functions
				string configID = uriPath[2];
				
				if ( matches(uriPath, "config", 3) )
				{
					if ( cmd == ConnectedVision::HTTP::CMD_GET )
					{
						// get
						status = module->getConfig( configID, responsePayload );
						res = true;
					}
					else if ( cmd == ConnectedVision::HTTP::CMD_SET )
					{
						// preprocess a potential augmented config (remove comments and resolve replacement references by their defines) and set config
						status = module->setConfig( configID, Class_generic_config::removeCommentsAndResolveReferencesInConfig(request.getPayload()), responsePayload );
						res = true;
					}
					else if ( cmd == ConnectedVision::HTTP::CMD_DEL )
					{
						// delete
						status = module->deleteConfig( configID, responsePayload );
						res = true;
					}
				}
				else if ( matches(uriPath, "configSummary", 3) )
				{
					boost::shared_ptr<Module_BaseClass> pModule = boost::dynamic_pointer_cast<Module_BaseClass>(module);
					status = pModule->getConfigHTMLsummary( configID, responsePayload );
					res = true;
				}
				else if ( matches(uriPath, "configOnlyThis", 3) )
				{
					if ( cmd == ConnectedVision::HTTP::CMD_DEL )
					{
						// set
						status = module->deleteConfigOnlyThis( configID, responsePayload );
						res = true;
					}
				}
				else if ( matches(uriPath, "status", 3) )
				{
					status = module->getStatus( configID, responsePayload );
					res = true;
				}
				else if ( matches(uriPath, "control", 3) && uriPath.size() > 4 )
				{
					id_t senderID = ID_NULL;

					std::string stringSenderID = request.getSenderID();
					if (stringSenderID != "")
					{					
						senderID = strToID(stringSenderID);
					}

					status = module->control( configID, uriPath[4], senderID, responsePayload );
					res = true;
				}
				else if ( uriPath[3].substr(0, 6).compare("params") == 0 ) // handle also commands like "params={...}" -> substr(0, 6) <-> "params" (6 characters starting at position 0)
				{
					// concatenate all remaining tokens after params command
					std::string parameterPath;
					for (int i=4; i<uriPath.size(); i++)
					{
						parameterPath += uriPath[i];
						if (i < uriPath.size() - 1)
						{
							parameterPath += "/";
						}
					}

					// handle command "params={...}"
					auto posFound = uriPath[3].find_first_of('=');
					if (posFound != string::npos) // '=' found
					{
						if (posFound != 6) // if '=' is at wrong position (not immediately after "params")
						{
							throw ConnectedVision::runtime_error(std::string("error: \"params\" command with unknown character sequence found! "));
						}
						parameterPath = uriPath[3].substr(posFound, string::npos);
					}
					else // '=' not found
					{
						if (uriPath[3].compare("params") != 0) // different than just "params"
						{
							throw ConnectedVision::runtime_error(std::string("error: \"params\" command with unknown character sequence found! "));
						}
					}

					// process "params" command
					if (cmd == ConnectedVision::HTTP::CMD_GET)
					{
						status = module->processParameterCommand( configID, parameterPath, responsePayload);
					}
					else if  (cmd == ConnectedVision::HTTP::CMD_SET)
					{
						status = module->processParameterCommand( configID, parameterPath, request.getPayload(), responsePayload );
					}
					res = true;
				}
				else if ( uriPath.size() > 4 )
				{
					try
					{
						// get job results
						string pinID( uriPath[3] );
						boost::shared_ptr< IConnectedVisionOutputPin > pin = module->getOutputPin(configID, pinID);
						if ( pin )
						{
							// get meta data
							if ( matches(uriPath, "id", 4) )
							{
								status = pin->getByID( uriPath[5], responsePayload);
								res = true;
							}
							else if ( matches(uriPath, "index", 4) && uriPath.size() == 6 )
							{
								int64_t index = boost::lexical_cast<int64_t>(uriPath[5].c_str());
								status = pin->getByIndex( index, responsePayload );
								res = true;
							}
							else if ( matches(uriPath, "index", 4) && uriPath.size() == 7 )
							{
								int64_t start = boost::lexical_cast<int64_t>(uriPath[5].c_str());
								int64_t end = boost::lexical_cast<int64_t>(uriPath[6].c_str());
								status = pin->getByIndexRange( start, end, responsePayload );
								res = true;
							}
							else if ( matches(uriPath, "time", 4) && uriPath.size() == 6 )
							{
								timestamp_t timestamp = boost::lexical_cast<int64_t>(uriPath[5].c_str());
								status = pin->getByTimestamp( timestamp, responsePayload );
								res = true;
							}
							else if ( matches(uriPath, "time", 4) && uriPath.size() == 7 )
							{
								timestamp_t start = boost::lexical_cast<int64_t>(uriPath[5].c_str());
								timestamp_t end = boost::lexical_cast<int64_t>(uriPath[6].c_str());
								status = pin->getAllInTimespan( start, end, responsePayload );
								res = true;
							}
							else if ( matches(uriPath, "beforetime", 4) && uriPath.size() == 6 )
							{
								timestamp_t timestamp = boost::lexical_cast<int64_t>(uriPath[5].c_str());
								status = pin->getBeforeTimestamp( timestamp, responsePayload );
								res = true;
							}
							else if ( matches(uriPath, "aftertime", 4) && uriPath.size() == 6 )
							{
								timestamp_t timestamp = boost::lexical_cast<int64_t>(uriPath[5].c_str());
								status = pin->getAfterTimestamp( timestamp, responsePayload );
								res = true;
							}
							else if ( matches(uriPath, "newest", 4) && uriPath.size() == 5 )
							{
								timestamp_t timestamp = TIMESTAMP_MAX;
								status = pin->getBeforeTimestamp( timestamp, responsePayload );
								res = true;
							}
						}
						else
						{
							res = true;
							status = HTTP_Status_NOT_FOUND;
							responsePayload.setContentType("application/json");
							responsePayload.setContent("{\n\t\"status\": 404,\n\t\"error\": \"pin / config not found\"\n}");
						}
					}
					catch (exception& e)
					{
						res = true;
						status = HTTP_Status_NOT_FOUND;
						responsePayload.setContentType("application/json");
						responsePayload.setContent("{\n\t\"status\": 404,\n\t\"error\": \"" + string(e.what()) + "\"\n}");
					}

				}
			}

			if ( res )
			{
				response.content = responsePayload;
				response.status = (ConnectedVision::HTTP::EnumHTTPStatus) (status); // TODO: mapping instead of int to ConnectedVision::HTTP::EnumHTTPStatus cast
			}
		}
		catch (std::exception &e)
		{
			res = true;
			response.status = HTTP_Status_ERROR;
			response.content.setContentType("application/json");
			response.content.setContent("{\n\t\"status\": 404,\n\t\"error\": \"" + string(e.what()) + "\"\n}");
		}
	}

	if ( !res )
	{
		handleDefault(request, response);
		res = true;
	}

    return res;
}

void ModuleDispatcher::handleDefault(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response)
{
	return getHostInfo(request, response);
}

std::string ModuleDispatcher::getModuleURL(std::string serverAddress, std::string moduleName ) const
{
	LOG_SCOPE

	if (serverAddress == "")
	{
		if (pHttpServer)
			return string(pHttpServer->getBaseURI() + moduleName);
		else if (pHttpsServer)
			return string(pHttpsServer->getBaseURI() + moduleName);
		else
			throw ConnectedVision::runtime_error("error in ModuleDispatcher::getModuleURL(): no http(s) server instance found");
	}
	else
	{
		int port = boost::lexical_cast<int>(serverAddress.substr(serverAddress.find_last_of(":")+1, std::string::npos));
		if ((pHttpServer)&&(pHttpServer->getListeningPort() == port))
		{
			return string(pHttpServer->getProtocol() + "://" + serverAddress + "/" + moduleName);
		}
		else if ((pHttpsServer)&&(pHttpsServer->getListeningPort() == port))
		{
			return string(pHttpsServer->getProtocol() + "://" + serverAddress + "/" + moduleName);
		}
		else
		{
			throw ConnectedVision::runtime_error("error in ModuleDispatcher::getModuleURL(): no http(s) server instance found");
		}		
	}

	return "";
}

void ModuleDispatcher::getHostInfo(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response) 
{
	LOG_SCOPE

	string result;
	string stringServerIpsHttp, stringServerIpsHttps;
	std::vector<std::string> listServerIpsHttp, listServerIpsHttps;
	
	if (pHttpServer)
	{
		listServerIpsHttp = pHttpServer->getServerURIs();
	}
	
	if (pHttpsServer)
	{
		listServerIpsHttps = pHttpsServer->getServerURIs();
	}

	
	for (int i=0; i<listServerIpsHttp.size(); i++)
	{
		if (i>0)
			stringServerIpsHttp += " - ";
		stringServerIpsHttp += listServerIpsHttp[i];
	}

	for (int i=0; i<listServerIpsHttps.size(); i++)
	{
		if (i>0)
			stringServerIpsHttps += " - ";
		stringServerIpsHttps += listServerIpsHttps[i];
	}

	string address = this->getModuleURL(request.getServerAddress(), "");

	result = "<html><body>";
	if (this->logo)
	{
		result += "<img src=" + address + "_hostLogo_></img>";
	}
	result += "<h1>ConnectedVision Module Info Page</h1>";

	result += "Connected Vision Core Git commit hash: " + string(CONNECTED_VISION_CORE_GIT_COMMIT_HASH);
	result += (CONNECTED_VISION_CORE_GIT_LOCAL_MODIFICATIONS ? " (local modifications)" : "");
	result += "<br />";
	
	result += "<br />Server IPs:<br />";
	if (stringServerIpsHttp.size() != 0)
		result += stringServerIpsHttp + "<br />";
	if (stringServerIpsHttps.size() != 0)
		result += stringServerIpsHttps + "<br />";

	result += "<br />Your IP: " + request.getRemoteIp();
	time_t tim;
	time(&tim);
    result += "<br />Current date / time: " + string(ctime(&tim)) + "<br />";

	std::vector<std::string> tokens;
	boost::split(tokens, request.getUri(), boost::is_any_of("/"));

	result += "<br/><hr/>";
	result += "<h2>Modules</h2><ul>";
	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end(); ++it) 
	{
		boost::shared_ptr<ConnectedVision::Module::IModule> module = *it;
		string base = address + module->getModuleID();
		
		result += "<li><a href='#" + module->getModuleID() + "'>" + module->getModuleID() + "</a></li>";
	
	}
	result += "</ul><br/>";

	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end(); ++it) 
	{
		boost::shared_ptr<ConnectedVision::Module::IModule> module = *it;
		
		result += "<hr/>";
		result += "<p><h2><a name='" + module->getModuleID() + "'>" + module->getModuleID() + "</a></h2><ul>";

		string base = this->getModuleURL(request.getServerAddress(), module->getModuleID() ) + "/";
		
		result += "<b> Module Description: </b>"
					"<ul>"
					"<a href='" + base + "moduleDescription'>" + base + "moduleDescription</a><br />"
					"<a href='" + base + "inputDescription'>" + base + "inputDescription</a><br />"
					"<a href='" + base + "outputDescription'>" + base + "outputDescription</a><br />"
					"<a href='" + base + "status'>" + base + "status</a><br />"
					"<a href='" + base + "init'>" + base + "init</a><br />"
					"<a href='" + base + "release'>" + base + "release</a><br />"
					"</ul>";

		result += "<b> Configuration: </b>"
					"<ul>"
					"<a href='" + base + "configListOverview'>" + base + "configListOverview</a><br />"
					"<a href='" + base + "configList'>" + base + "configList</a><br />"
					"<a href='" + base + "configListDetailed'>" + base + "configListDetailed</a><br />"
					"<a href='" + base + "xyz/configSummary'>" + base + "<i>configID</i>/configSummary</a><br />"
					"<a href='" + base + "xyz/config'>" + base + "<i>configID</i>/config</a><br />"
					"<a href='_post_?targetURL=" + base + "0/config'>" + base + "<i>configID</i>/config</a> (POST/PUT)<br />"
					"<a href='" + base + "0/config?cmd=DELETE'>" + base + "<i>configID</i>/config</a> (DELETE)<br />"
					"<a href='" + base + "xyz/status'>" + base + "<i>configID</i>/status</a><br />"
					"<a href='" + base + "xyz/params'>" + base + "<i>configID</i>/params</a> (POST/PUT), extra syntax: \"/\" (target sub-param), \"=\" (set via GET)<br />"
					"<a href='" + base + "xyz/control/start'>" + base + "<i>configID</i>/control/start</a> <br />"
					"<a href='" + base + "xyz/control/stop'>" + base + "<i>configID</i>/control/stop</a> <br />"
					"<a href='" + base + "xyz/control/stopThis'>" + base + "<i>configID</i>/control/stopThis</a> <br />"
					"<a href='" + base + "xyz/control/reset'>" + base + "<i>configID</i>/control/reset</a><br />"
					"<a href='" + base + "xyz/control/resetThis'>" + base + "<i>configID</i>/control/resetThis</a><br />"
					"</ul>";

		result += "<b> Request API: </b>"
					"<ul>"
					"<a href='" + base + "xyz/0/id/1'>" + base + "<i>configID</i>/<i>pinID</i>/id/<i>ID</i></a><br />"
					"<a href='" + base + "xyz/0/index/0'>" + base + "<i>configID</i>/<i>pinID</i>/index/<i>indexNr</i></a><br />"
					"<a href='" + base + "xyz/0/index/0/100'>" + base + "<i>configID</i>/<i>pinID</i>/index/<i>startIndex</i>/<i>endIndex</i></a><br />"
					"<a href='" + base + "xyz/0/time/0'>" + base + "<i>configID</i>/<i>pinID</i>/time/<i>timeStamp</i></a><br />"
					"<a href='" + base + "xyz/0/beforetime/0'>" + base + "<i>configID</i>/<i>pinID</i>/beforetime/<i>timeStamp</i></a><br />"
					"<a href='" + base + "xyz/0/aftertime/0'>" + base + "<i>configID</i>/<i>pinID</i>/aftertime/<i>timeStamp</i></a><br />"
					"<a href='" + base + "xyz/0/newest'>" + base + "<i>configID</i>/<i>pinID</i>/newest</a><br />"
					"<a href='" + base + "xyz/0/time/0/10000'>" + base + "<i>configID</i>/<i>pinID</i>/time/<i>startTime</i>/<i>endTime</i></a><br />"
					"</ul>";

		result += "</ul></p>";
	}

	result += "</body></html>";

    response.content.setContentType("text/html");
	response.content.setContent(result);
	response.status = ConnectedVision::HTTP::HTTP_Status_OK;
}


void ModuleDispatcher::handlePostRequests(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response) 
{
	LOG_SCOPE;

	string targetURL = request.getTargetURL();

	string result;

	result = "<html><body>";
	result += "<form method='post' action='" + targetURL + "'>";
	result += "target URL: <i>" + targetURL + "</i><br/><br/>";
	result += "payload: <br/><textarea name='payload' cols='80' rows='20'></textarea> <br/>";
//	result += "file: <br/><input name='file' type='file'></input> <br/>";
    result += "<input type='hidden' name='cmd' value='SET'></input>";
    result += "<input type='submit'></input>";
    result += "</form>";

	result += "</body></html>";

    response.content.setContentType("text/html");
	response.content.setContent(result);
	response.status = ConnectedVision::HTTP::HTTP_Status_OK;
}

void ModuleDispatcher::getModuleList(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response) 
{
	LOG_SCOPE;

	string result = "";

	result += "[\n";
	for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end(); ++it) 
	{
		boost::shared_ptr<ConnectedVision::Module::IModule> module = *it;
		if ( it != modules.begin() )
			result += ",\n";
		result += "{ \"name\": \"" + module->getModuleID() + "\", "
					"\"uri\": \"" + getModuleURL(request.getServerAddress(), module->getModuleID() ) + "\" }";
	}
	result += "\n]";

    response.content.setContentType("application/json");
	response.content.setContent(result);
	response.status = ConnectedVision::HTTP::HTTP_Status_OK;
}

ConnectedVision::HTTP::EnumHTTPStatus ModuleDispatcher::getConfigListOverview(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response) 
{
	LOG_SCOPE;

	boost::shared_ptr<Module_BaseClass> module;

	std::vector<std::string> uriPath;
	boost::split(uriPath, request.getUri(), boost::is_any_of("/"));

	if ( uriPath.size() > 1 )
	{
		for (vector<boost::shared_ptr<ConnectedVision::Module::IModule>>::iterator it = modules.begin(); it != modules.end() && !module; ++it) 
		{
			boost::shared_ptr<ConnectedVision::Module::IModule>& m = *it;
			if ( uriPath[1] == m->getModuleID() )
			{
				module = boost::dynamic_pointer_cast<Module_BaseClass>(m);
			}
		}
	}

	if ( module )
	{
		string moduleID = uriPath[1];
		string result = "<html><body>";
		result += "<br/><hr/>";
		if (module->isSetLogo())
		{
			string base = this->getModuleURL(request.getServerAddress(), module->getModuleID() ) + "/";
			result += "<img src=" + base + "moduleLogo></img>";
		}
		result += "<h2>configs of module ";
		result += moduleID;
		result += "</h2>";

		auto configStore = module->getConfigStore();
		if (!configStore)
		{
			throw ConnectedVision::runtime_error("error: could not retrieve configStore! ");
		}
		ConnectedVision::DataHandling::DataRange range = configStore->getDataRange();

		int numConfigs = 0;
		if ( (range.indexEnd>=0) && (range.indexStart>=0) )
		{
			numConfigs = range.indexEnd - range.indexStart + 1;
		}
		result += std::string("there are " + boost::lexical_cast<string>(numConfigs) + " configs in total\t");

		string commandUri = std::string("/_post_?targetURL=http://" + request.getHost() + "/" + moduleID + "/0/config");
		result += "\t[<a href='" + commandUri + "'>" + "create new config" + "</a>]\t";
		
		result += "<ul>";

		if (range.indexStart >= 0)
		{
			for (auto i = range.indexStart; i <= range.indexEnd; i++)
			{
				auto config = configStore->getByIndex(i);
				result += module->getConfigHTMLsummary(*module, *config);
			}
		}

		result += "</ul><br/>";
		result += "</body></html>";

		response.content.setContentType("text/html");
		response.content.setContent(result);
		response.status = ConnectedVision::HTTP::HTTP_Status_OK;

	}
	else
	{
		response.content.setContentType("text/html");
		response.status = ConnectedVision::HTTP::HTTP_Status_NOT_FOUND;
	}
	return(response.status);
}

void ModuleDispatcher::getHostStatus(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response)
{
	LOG_SCOPE;

	string result = "";

	result += hostStatus.toJsonStr();

    response.content.setContentType("application/json");
	response.content.setContent(result);
	response.status = ConnectedVision::HTTP::HTTP_Status_OK;
}

void ModuleDispatcher::getHostLogoPNG(const ConnectedVision::HTTP::HTTPServerRequest &request, HTTPResponse &response)
{
	LOG_SCOPE;

	if (this->logo)
	{
		vector<uchar> v_char;
		cv::imencode(".png", *this->logo, v_char);
	
		cv::Mat encoded(v_char);
		std::string content (reinterpret_cast<char*>(encoded.data), v_char.size());

		response.content.setContentType("image/png");
		response.content.setContent(content);
		response.status = ConnectedVision::HTTP::HTTP_Status_OK;
	}
	else
	{
		ConnectedVision::HTTP::EnumHTTPStatus status = ConnectedVision::HTTP::HTTP_Status_NOT_FOUND;
		writeError(response.content, status, id_t("ModuleDispatcher::getHostLogoPNG"), string("host logo was not set"));		
		response.status = status;
	}
}

/*
void ModuleDispatcher::setOption_listeningPort(const int port)
{
	pHttpServer->setOption_listeningPort(port);
	pHttpsServer->setOption_listeningPort(port+1);
}

void ModuleDispatcher::setOption_numThreads(const int numThreads)
{
	pHttpServer->setOption_numThreads(numThreads);
	pHttpsServer->setOption_numThreads(numThreads);
}
*/
