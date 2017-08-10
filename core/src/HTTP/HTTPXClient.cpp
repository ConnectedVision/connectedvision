/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPXClient.cpp
**
** written by Michael Rauter
** 
*******************************************************/

#include "HTTPXClient.h"

using namespace ConnectedVision::HTTP;

HTTPXClient::HttpsClientParams HTTPXClient::httpsClientParams;

void HTTPXClient::performHttpxRequest(const ConnectedVision::HTTP::HTTPClientRequest &request, ConnectedVision::HTTP::HTTPResponse &response)
{
	EnumProtocolType protocolType = getProtocolTypeFromUri(request.getUri());
	
	if (protocolType == ProtocolTypeHTTP)
	{
		HTTPClient http;
		http.performRequest(request, response);
	}
	else if (protocolType == ProtocolTypeHTTPS)
	{
		HTTPSClientPoco::Params params;
		params.caLocation = httpsClientParams.caLocation;
		params.caPassword = httpsClientParams.caPassword;
		HTTPSClient https(params);
		https.performRequest(request, response);
	}
	else if (protocolType == ProtocolTypeUnknown)
	{
		throw std::runtime_error("error in HTTPXClient::performHttpxRequest(...): unknown HTTP protocol type used (request uri did not start with \"http://\" or \"https://\")");
	}

	ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
	if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
	{
		throw ConnectedVision::runtime_error( response.content.getContentConst() );
	}
}

HTTPXClient::EnumProtocolType HTTPXClient::getProtocolTypeFromUri(std::string uri)
{
	if (uri.substr(0,7) == "http://")
	{
		return ProtocolTypeHTTP;
	}
	else if (uri.substr(0,8) == "https://")
	{
		return ProtocolTypeHTTPS;
	}
	return ProtocolTypeUnknown;
}
