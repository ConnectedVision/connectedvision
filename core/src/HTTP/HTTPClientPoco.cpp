/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPClientPoco.cpp
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#include <Poco/Foundation.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/StreamCopier.h>

#include "HTTPClientPoco.h"

using namespace ConnectedVision::HTTP;

HTTPClientPoco::HTTPClientPoco()
{

}

void HTTPClientPoco::performRequest(const HTTPClientRequest &request, ConnectedVision::HTTP::HTTPResponse &response)
{
	try
	{
		// Initialize session
		Poco::URI uri(request.getUri());
		Poco::Net::HTTPClientSession client_session(uri.getHost(), uri.getPort());

		// Prepare and send request
		std::string path(uri.getPathAndQuery());
		Poco::Net::HTTPRequest requestPoco;

		std::string payload = "";

		switch (request.getMethod())
		{
		case ConnectedVision::HTTP::HTTP_Method_GET:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_GET);
			break;
		case ConnectedVision::HTTP::HTTP_Method_PUT:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_PUT);
			payload = request.getPayload();
			break;
		case ConnectedVision::HTTP::HTTP_Method_POST:
			//requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
			//requestPoco.set("payload", request.getPayload());
			throw HTTPClientException("error in HTTPClientPoco::performRequest(...): method HTTP POST not implemented");
			break;
		case ConnectedVision::HTTP::HTTP_Method_DELETE:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_DELETE);
			//requestPoco.set("payload", request.getPayload());
			break;
		case ConnectedVision::HTTP::HTTP_Method_HEAD:
			requestPoco.setMethod(Poco::Net::HTTPRequest::HTTP_HEAD);
			break;
		default:
			throw HTTPClientException("error in HTTPClientPoco::performRequest(...): unknown HTTP method issued");
			break;
		};
		
		requestPoco.setURI(path);
		requestPoco.setVersion(Poco::Net::HTTPMessage::HTTP_1_1);

		if (!payload.empty())
		{
			requestPoco.setContentLength( payload.length() );
			client_session.sendRequest(requestPoco) << payload;
		}
		else
		{
			client_session.sendRequest(requestPoco);
		}

		// Get response
		Poco::Net::HTTPResponse responsePoco;
		std::istream& is = client_session.receiveResponse(responsePoco);

		std::string responseString;
		Poco::StreamCopier::copyToString(is, responseString);

		response.content.setContent(responseString);
		response.content.setContentType(responsePoco.getContentType());
		response.status = (ConnectedVision::HTTP::EnumHTTPStatus) ( responsePoco.getStatus() );

	} catch (Poco::Exception& e) {
		throw ConnectedVision::runtime_error("Exception in HTTPClientPoco::performRequest(...): HTTP request failed, reason: " + std::string(e.what()));		
	}
};