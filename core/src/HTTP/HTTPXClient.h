/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPXClient.h
**
** written by Michael Rauter
** 
*******************************************************/

#ifndef HTTPXClient_def
#define HTTPXClient_def

#include <IHTTPAbstraction.h>

#include <HTTP/HTTPClientPoco.h>
#include <HTTP/HTTPSClientPoco.h>

namespace ConnectedVision {
namespace HTTP {
	
/**
* HTTPXClient class
* encapsulates functionality used to perform client http/https requests
* implemented as static class
*/
class HTTPXClient {
public:
	enum EnumProtocolType { ProtocolTypeHTTP, ProtocolTypeHTTPS, ProtocolTypeUnknown }; ///< enumeration for protocol type

	/**
	* https client parameters - used for establishing a certified connection for https client requests
	*/
	struct HttpsClientParams
	{
		std::string caLocation; ///< path to CA/root certificates  - see documentation about Poco::Net::Context in Poco docu for more details
		std::string caPassword; ///< password used for CA certificate (if one was used to protect the certificate by a passphrase)
	};

	/**
	* function to set https client parameters
	* @param httpsClientParams contains the https client parameters used for https client requests
	*/
	static void setHttpsClientParams(HttpsClientParams httpsClientParams)
	{
		HTTPXClient::httpsClientParams = httpsClientParams;
	}

	/**
	* performs a http or https request according to the protocol specified in the uri in the request object
	* @param request a reference to a ConnectedVision::HTTP::HTTPClientRequest used to specify the http/https client request
	* @param response a reference to a ConnectedVision::HTTP::HTTPResponse object which will be filled out with the response of the http/https client request
	*/
	static void performHttpxRequest(const ConnectedVision::HTTP::HTTPClientRequest &request, ConnectedVision::HTTP::HTTPResponse &response);

private:
	typedef HTTPClientPoco HTTPClient;
	typedef HTTPSClientPoco HTTPSClient;

	static HttpsClientParams httpsClientParams; ///< the https client parameters used to establish a certified https connection

	/**
	* returns the protocol type extracted from a provided uri
	* @param uri the uri to be used for protocol extraction
	* @return the protocol type (of type HTTPXClient::EnumProtocolType) to be used to identify http respectively https requests
	*/
	static EnumProtocolType getProtocolTypeFromUri(std::string uri);
};

}
}

#endif // HTTPXClient_def


