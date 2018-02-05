/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPServerPoco.cpp
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#include "HTTPServerPoco.h"

#include <IConnectedVisionModule.h>

#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>
#include <Poco/URI.h>
#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/NetException.h>

using namespace ConnectedVision;
using namespace ConnectedVision::HTTP;

using namespace Poco;
using namespace Poco::Net;
using namespace Poco::Util;

#define MAXQUEUED 100

class HTTPServerPoco_HTTPRequestHandler : public Poco::Net::HTTPRequestHandler
{
public:
	HTTPServerPoco_HTTPRequestHandler(ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject) : Poco::Net::HTTPRequestHandler()
	{		
		this->pCallbackObject = pCallbackObject;
	}
	void handleRequest(Poco::Net::HTTPServerRequest& request,
		Poco::Net::HTTPServerResponse& response)
	{
		try
		{
			ConnectedVision::HTTP::HTTPServerRequest requestConverted;

			requestConverted.setHost(request.getHost());

			Poco::Net::SocketAddress serverAddress = request.serverAddress();
			requestConverted.setServerAddress(serverAddress.toString());
			
			requestConverted.setHttpVersion(request.getVersion());

			Poco::Net::HTMLForm htmlForm(request);
			const std::string nameTargetURL = "targetURL";
			if (htmlForm.has(nameTargetURL)) { // it is intended that the .has() and .get() functions of HTMLForm are used instead of operator[] to decrease Poco Exception messages in debug mode
				requestConverted.setTargetURL(htmlForm.get(nameTargetURL));
			}
			//try
			//{
			//	requestConverted.setTargetURL(htmlForm["targetURL"]);
			//}
			//catch (Poco::NotFoundException &e)
			//{
			//}

			const std::string nameJsonString = "callback";
			if (htmlForm.has(nameJsonString)) {
				requestConverted.setJsonString(htmlForm.get(nameJsonString));
			}
			//try
			//{
			//	requestConverted.setJsonString(htmlForm["callback"]);
			//}
			//catch (Poco::NotFoundException &e)
			//{
			//}

			const std::string nameSenderID = "senderID";
			if (htmlForm.has(nameSenderID)) {
				requestConverted.setSenderID(htmlForm.get(nameSenderID));
			}
		
			//std::string uri = request.getURI();
			std::string uri;
			URI::decode(request.getURI(), uri);

			std::string queryString = "";

			// cut off query string from uri for ModuleDispatcher
			size_t pos = uri.find_first_of("?", 0);
			if (pos != std::string::npos)
			{
				queryString = uri.substr(pos+1); // queryString is part of Poco Uri from "?" to end
				uri = uri.substr(0, pos); // uri is remaining Poco uri to "?" (excluding "?")
			}

			requestConverted.setUri(uri);

			std::string clientIp = request.clientAddress().toString();
			std::string clientPort;
			pos = clientIp.find_first_of(":", 0);
			if (pos != std::string::npos)
			{
				clientPort = clientIp.substr(pos+1); 
				clientIp = clientIp.substr(0, pos);
			}
			requestConverted.setRemoteIp(clientIp);

			requestConverted.setRemotePort(boost::lexical_cast<int>(clientPort));


			//LOG_DEBUG("handle new request");
			boost::shared_ptr<ConnectedVision::Module::IModule> module;
			ConnectedVisionResponse responsePayload;

			ConnectedVision::HTTP::EnumConnectedVisionCommandType cmd = CMD_NA;

			if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
			{			
				//LOG_DEBUG("HTTP Command: GET");

				cmd = CMD_GET;
				std::string cmdString = "GET";

				const std::string nameCmd = "cmd";
				if (htmlForm.has(nameCmd)) {
					cmdString = htmlForm.get(nameCmd);
				}
				//try
				//{
				//	cmdString = htmlForm["cmd"];
				//}
				//catch (Poco::NotFoundException &e)
				//{					
				//}

				if ( cmdString == "SET" )
				{
					//LOG_DEBUG("Parameter Command: SET");

					cmd = CMD_SET;

					const std::string namePayload = "payload";
					if (htmlForm.has(namePayload)) {
						requestConverted.setPayload(htmlForm.get(namePayload));
					}
					//try
					//{
					//	requestConverted.payload = htmlForm["payload"];
					//}
					//catch (Poco::NotFoundException &e)
					//{
					//}
				}
				
				if ( cmdString == "DELETE" )
				{
					//LOG_DEBUG("Parameter Command: DELETE");

					cmd = CMD_DEL;
				}
			}
			

			if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT )
			{			
				//LOG_DEBUG("HTTP Command: PUT");

				cmd = CMD_SET;

				Poco::StreamCopier::copyToString(request.stream(), requestConverted.getRefPayload());
			}			

			if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST )
			{			
				//LOG_DEBUG("HTTP Command: POST");

				cmd = CMD_SET;

				//boost::posix_time::ptime start = boost::posix_time::microsec_clock::universal_time();

				htmlForm.read(request.stream());

				const std::string namePayload = "payload";
				if (htmlForm.has(namePayload)) {
					requestConverted.setPayload(htmlForm.get(namePayload));
				}
				else {
					throw ConnectedVision::runtime_error("payload field not found in http post request (in HTTPRequestHandler (HTTPServerPoco))");
				}
				//try
				//{
				//	requestConverted.payload = htmlForm["payload"];
				//}
				//catch (Poco::NotFoundException &e)
				//{
				//	throw ConnectedVision::runtime_error("payload field not found in http post request (in HTTPRequestHandler (HTTPServerPoco))");
				//}

				//boost::posix_time::ptime end = boost::posix_time::microsec_clock::universal_time();
				//int64_t delta = (end - start).total_milliseconds();
				//LOG_DEBUG("readQueryString runtime: " + delta);
			}			
			if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE )
			{
				//LOG_DEBUG("HTTP Command: DELETE");
				cmd = CMD_DEL;
			}

			requestConverted.setCommandType(cmd);

			ConnectedVision::HTTP::HTTPResponse responseResult;

			if (pCallbackObject)
			{
				pCallbackObject->handleRequest(requestConverted, responseResult);
			}
			else
			{
				throw ConnectedVision::runtime_error("pCallbackObject is null (in HTTPRequestHandler (HTTPServerPoco))");
			}

			response.setChunkedTransferEncoding(true);
			response.setContentType(responseResult.content.getContentTypeConst());
			response.set("Access-Control-Allow-Origin", "*"); // implement CORS (thanks to Lenis Dimitrios)
			response.set("Access-Control-Allow-Headers", "*"); // implement CORS (thanks to Lenis Dimitrios)
			response.setStatus((Poco::Net::HTTPResponse::HTTPStatus)responseResult.status);
			std::ostream& ostr = response.send();

			std::string jsonP = requestConverted.getJsonString();
			if ( !jsonP.empty() && responseResult.content.getContentTypeConst() == "application/json" )
			{
				ostr << jsonP;
				ostr << "(";
				ostr << responseResult.content.getContentConst();
				ostr << ")";
			}
			else
			{
				ostr << responseResult.content.getContentConst();
			}

		}
		catch(Poco::Net::NetException& ex)
		{
			std::string err = ex.displayText();
			throw ConnectedVision::runtime_error( err );
		}
		catch(...)
		{
			throw ConnectedVision::runtime_error( "error" ); // FIXME
		}
	}
private:
	ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject;

	std::string dataAsString;	
};

class HTTPServerPoco_RequestHandlerFactory : public
	Poco::Net::HTTPRequestHandlerFactory
{
public:
	HTTPServerPoco_RequestHandlerFactory(ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject)
	{
		this->pCallbackObject = pCallbackObject;
	}
	Poco::Net::HTTPRequestHandler* createRequestHandler(
		const Poco::Net::HTTPServerRequest& request)
	{
			return new HTTPServerPoco_HTTPRequestHandler(pCallbackObject);
	}
private:
	ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject;
};

HTTPServerPoco::HTTPServerPoco() : pCallbackObject(NULL) {
	pServerParams = new Poco::Net::HTTPServerParams;
	if (!pServerParams) throw ConnectedVision::runtime_error("allocation of Poco::Net::HTTPServerParams failed in HTTPServerPoco::HTTPServerPoco()");
	pServerParams->setMaxQueued(MAXQUEUED);

	this->pOriginalPocoErrorHandler = Poco::ErrorHandler::get();
	Poco::ErrorHandler::set( &this->customErrorHandler );
};

HTTPServerPoco::~HTTPServerPoco() {
	// restore POCO error handler
	Poco::ErrorHandler::set(this->pOriginalPocoErrorHandler);
}

Poco::Net::ServerSocket HTTPServerPoco::createServerSocket(int port)
{
	Poco::Net::ServerSocket socket(port); // set-up a server socket
	return(socket);
}

void HTTPServerPoco::start() {
	Poco::Net::ServerSocket socket = this->createServerSocket(port);
	pServer.reset(new Poco::Net::HTTPServer(new HTTPServerPoco_RequestHandlerFactory(this->pCallbackObject), socket, pServerParams));

	Poco::Net::NetworkInterface::List networkInterfaces = Poco::Net::NetworkInterface::list(true, true);
	Poco::Net::IPAddress ipAddress;
	Poco::Net::NetworkInterface::List::const_iterator it;
	for (it = networkInterfaces.begin(); it != networkInterfaces.end(); it++)
	{
		if ((!it->isLoopback())&&(it->supportsIPv4()))
		{
			ipAddress = it->address();
			std::string protocol = this->getProtocol();
			this->serverURIs.push_back(protocol + "://" + ipAddress.toString() + ":" + boost::lexical_cast<std::string>(port) + "/");
		}
	}

	if (serverURIs.size() == 0)
	{
		throw ConnectedVision::runtime_error("no network interface found (install at least a loopback adapter)"); 
	}

	pServer->start();
};

void HTTPServerPoco::stop() {
	pCallbackObject = NULL;
	if (pServer)
	{
		pServer->stop();
		pServer->stopAll(true);
		int currentConnections = pServer->currentConnections();
		int currentThreads = pServer->currentThreads();
		int totalConnections = pServer->totalConnections();
		pServer.reset();
	}
};

void HTTPServerPoco::setImplementationCallbackInterface(ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject) {
	this->pCallbackObject = pCallbackObject;
};

void HTTPServerPoco::setOption_listeningPort(const int port)
{
	this->port = port;	
}

void HTTPServerPoco::setOption_numThreads(const int numThreads)
{
	pServerParams->setMaxThreads(numThreads);
}

void HTTPServerPoco::setOption_maxQueued(const int maxQueued)
{
	pServerParams->setMaxQueued(maxQueued);
}

void HTTPServerPoco::CustomErrorHandler::exception(const Poco::Exception& exc)
{
	std::string className( exc.className() );

	if ( className.find("ConnectionResetException") != std::string::npos )
	{
		// ignore ConnectionResetException
		return;
	}

	if ( className.find("ConnectionAbortedException") != std::string::npos )
	{
		// ignore ConnectionAbortedException
		return;
	}

	// use default handling for other exceptions
	Poco::ErrorHandler::exception(exc);
}