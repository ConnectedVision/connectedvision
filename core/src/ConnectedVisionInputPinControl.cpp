/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef ConnectedVisionInputPinControl_code
#define ConnectedVisionInputPinControl_code

#include <string>
#include <helper.h>
#include <boost/thread.hpp>

#include <IConnectedVisionModule.h>
#include "ConnectedVisionInputPin.h"
#include "HTTP/HTTPXClient.h"

using namespace std;
using namespace ConnectedVision;

static void wait(int s)
{
	boost::this_thread::sleep( boost::posix_time::seconds(s) );
}


ConnectedVisionInputPinControl::ConnectedVisionInputPinControl(IModuleEnvironment *env, const pinID_t& inputPinID)
	: inputPinID(inputPinID)
{
	this->env = env;
	this->status.clear();
	this->config.clear();

	pModuleSource.reset();

	pModuleSource_REST.reset(new ModuleSource_REST_BaseClass());
	pModuleSource_Memory.reset(new ModuleSource_Memory_BaseClass());
}



ConnectedVisionInputPinControl::~ConnectedVisionInputPinControl(void)
{

}


void ConnectedVisionInputPinControl::update()
{
	string uri = *config.getconst_moduleURI();
	string configID = config.getconst_id();
 	string protocol, name;
	parseURI(uri, protocol, name);

	
	std::string moduleID = *config.getconst_moduleURI();

	// reduce module URI to a string that just contains the moduleID
	size_t found = string::npos;
	do
	{
		found = moduleID.find_last_of("/");
		if (found != string::npos)
		{
			if (found == moduleID.length()-1) // if slash was just at the end of the string repeat to find slash that is separating the host URI from the module identifier
			{
				moduleID = moduleID.substr(0, found); // replace old tmpURI string with string containing everything before the slash
			}
			else
			{
				moduleID = moduleID.substr(found+1, string::npos); // replace old tmpURI string with string containing everything after the slash - which should be the moduleID now
				break;
			}
		}
		else
		{
			throw ::ConnectedVision::runtime_error("ill-formated module URI detected"); // no slash found although it is expected
		}
	}
	while (true);	

	if ((uri.compare("")!=0)&&(configID.compare("")!=0))
	{
		pModuleSource_REST->init(uri, configID);
		pModuleSource_Memory->init(env, moduleID, configID);

		pModuleSource = this->getModuleSource();
	}	
}

pinID_t ConnectedVisionInputPinControl::getInputPinID() const
{
	return this->inputPinID;
}

pinID_t ConnectedVisionInputPinControl::getOutputPinID() const
{
	return this->outputPinID;
}

boost::shared_ptr<IModuleSource> ConnectedVisionInputPinControl::getModuleSource()
{
	std::string tmpURI = *config.getconst_moduleURI();

	// reduce module URI to a string that just contains the host URI
	size_t found = string::npos;
	do
	{
		found = tmpURI.find_last_of("/");
		if (found != string::npos)
		{
			tmpURI = tmpURI.substr(0, found); // replace old tmpURI string with string containing everything before the slash
		}
		else
		{
			throw ::ConnectedVision::runtime_error("ill-formated module URI detected"); // no slash found although it is expected
		}
	}
	while (found == tmpURI.length()-1); // if slash was just at the end of the string repeat to find slash that is separating the host URI from the module identifier

	//boost::shared_ptr<string> data;

	std::stringstream restURL;
	restURL << tmpURI << "/_hostStatus_";
	
	ConnectedVision::HTTP::HTTPClientRequest request;
	request.setUri(restURL.str());
	request.setMethod(ConnectedVision::HTTP::HTTP_Method_GET);
	
	ConnectedVision::HTTP::HTTPResponse response;

	HTTP::HTTPXClient::performHttpxRequest(request, response);

	ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
	if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
	{
		throw ::ConnectedVision::runtime_error( response.content.getContentConst() );
	}

	Class_HostStatus hostStatusConnectedModule;
	hostStatusConnectedModule.parseJson(response.content.getContentConst());

	boost::shared_ptr<IModuleSource> pModuleSource;

	if (env->getHostStatus().getconst_hostID().compare(hostStatusConnectedModule.getconst_hostID())==0)
	{
		pModuleSource = pModuleSource_Memory;
	}
	else
	{
		pModuleSource = pModuleSource_REST;
	}

	return(pModuleSource);
}


void ConnectedVisionInputPinControl::init(const id_t parentConfigID, const std::string& configStr, const pinID_t& outputPinID)
{
	this->parentConfigID = parentConfigID;
	this->config.parseJson( configStr.c_str() );
	this->outputPinID = outputPinID;
	update();
}

ConnectedVision::id_t ConnectedVisionInputPinControl::getID()
{
	return this->config.get_id();
}

Class_generic_config ConnectedVisionInputPinControl::getConfig()
{
	Class_generic_config config = Class_generic_config(*pModuleSource->getConfig().get());
	return (config);
}

Class_generic_config ConnectedVisionInputPinControl::setConfig()
{
	string uri;

 	string protocol, name;
	parseURI( *this->config.get_moduleURI(), protocol, name);


// do not use manual protocol any more - TODO automatic access selection
//	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{	
		uri = *this->config.get_moduleURI() + "/0/config";

		ConnectedVision::HTTP::HTTPClientRequest request;
		request.setUri(uri);
		request.setMethod(ConnectedVision::HTTP::HTTP_Method_PUT);
		request.setPayload( this->config.toJsonStr() );

		ConnectedVision::HTTP::HTTPResponse response;

		HTTP::HTTPXClient::performHttpxRequest(request, response);

		ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
		if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
		{
			throw ::ConnectedVision::runtime_error( response.content.getContentConst() );
		}

		this->config.parseJson( response.content.getContentConst() );
	}

	update();

	return this->config;
}

Class_generic_config ConnectedVisionInputPinControl::deleteConfig()
{
	string uri;

 	string protocol, name;
	parseURI( *this->config.get_moduleURI(), protocol, name);


	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{
		string uri = *this->config.get_moduleURI() + "/" + this->config.get_id() + "/config";

		ConnectedVision::HTTP::HTTPClientRequest request;
		request.setUri(uri);
		request.setMethod(ConnectedVision::HTTP::HTTP_Method_DELETE);
		request.setPayload( this->config.toJsonStr() );

		ConnectedVision::HTTP::HTTPResponse response;

		HTTP::HTTPXClient::performHttpxRequest(request, response);

		HTTP::EnumHTTPStatus code = response.status;
		if ( ( code != HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
		{
			throw ::ConnectedVision::runtime_error( response.content.getContentConst() );
		}

		this->config.parseJson( response.content.getContentConst() );
	}
	else if ( protocol.compare("local") == 0 && this->env )
	{
		boost::shared_ptr<IConnectedVisionModule> module = this->env->getModule( name );
		if ( !module )
			throw ::ConnectedVision::runtime_error("ConnectedVisionInputPinControl: cannot find: " + *this->config.get_moduleURI() );


		ConnectedVisionResponse response;
		int code = module->setConfig( "*", this->config.toJsonStr(), response );

		if ( code != HTTP::HTTP_Status_OK )
			throw ::ConnectedVision::runtime_error( response.getContent() );
	

		this->config.parseJson( response.getContent() );
	}
	else
	{
		throw ::ConnectedVision::runtime_error("ConnectedVisionInputPinControl: unsupported protocol: " + *this->config.get_moduleURI());
	}

	update();

	return this->config;
}


Class_generic_status ConnectedVisionInputPinControl::getStatus()
{
	Class_generic_status status = Class_generic_status(*pModuleSource->getStatus().get());
	return (status);
}


Class_generic_status_stableResults ConnectedVisionInputPinControl::getStableResults()
{
	Class_generic_status status = this->getStatus();
	boost::shared_ptr<Class_generic_status_stableResults> stableResults = status.find_stableResultsByPinID(outputPinID);

	if ( stableResults )
	{
		return Class_generic_status_stableResults( *stableResults );
	}
	else
	{
		throw ::ConnectedVision::runtime_error("ConnectedVisionInputPinControl: cannot find stable results for pinID: " + IDToStr(outputPinID) );
	}


	///@TODO use some kind of caching or throttling
}



Class_generic_status& ConnectedVisionInputPinControl::control(std::string command)
{
	this->status.clear();

 	string protocol, name;
	parseURI( *this->config.get_moduleURI(), protocol, name);

//	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{
		string uri = *this->config.get_moduleURI() + "/" + this->config.get_id() + "/control/" + command + "?senderID=" + IDToStr(parentConfigID);

		HTTP::HTTPClientRequest request;
		request.setUri(uri);
		request.setMethod(HTTP::HTTP_Method_GET);
		HTTP::HTTPResponse response;

		HTTP::HTTPXClient::performHttpxRequest(request, response);

		this->status.parseJson( response.content.getContentConst() );
	}
	/*
	else if ( protocol.compare("local") == 0 && env )
	{
		boost::shared_ptr<IConnectedVisionModule> module = env->getModule( name );
		if ( !module )
			throw ConnectedVision::runtime_error("ConnectedVisionInputPinControl: cannot find: " + *this->config.get_moduleURI() );

		ConnectedVisionResponse response;
		int code = module->control( this->config.get_id(), command, response );
		
		if ( code != HTTP_OK )
			throw ConnectedVision::runtime_error( response.getContent() );
		this->status.parseJson( response.getContent() );
	}
	else
	{
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinControl: unsupported protocol: " + *this->config.get_moduleURI());
	}
	*/
	
	return this->status;
}


Class_generic_status& ConnectedVisionInputPinControl::start()
{
	return this->control("start");
}


Class_generic_status& ConnectedVisionInputPinControl::stop()
{
	return this->control("stop");
}


Class_generic_status& ConnectedVisionInputPinControl::recover()
{
	return this->control("recover");
}


Class_generic_status& ConnectedVisionInputPinControl::reset()
{
	return this->control("reset");
}

Class_generic_status& ConnectedVisionInputPinControl::notifyStop()
{
	return this->control("notifyStop");
}


#endif // ConnectedVisionInputPinControl_code
