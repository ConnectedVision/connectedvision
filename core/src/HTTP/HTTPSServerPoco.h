/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPSServerPoco.h
**
** written by Michael Rauter and Andi Zoufal
** 
*******************************************************/

#ifndef HTTPSServerPoco_def
#define HTTPSServerPoco_def

#include "HTTPServerPoco.h"

#include <Poco/Foundation.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/ThreadPool.h>
#include <Poco/ErrorHandler.h>

namespace ConnectedVision {
namespace HTTP {

/**
* HTTP server implementation based on Poco
* inherits from HTTPServerPoco and extends HTTPS functionality
*/
class HTTPSServerPoco : public HTTPServerPoco
{
public:

	/**
	* https parameters for HTTPSServerPoco
	* used in constructor of HTTPSServerPoco
	*/
	struct HttpsParams
	{
		std::string privateKeyFile; ///< path to private key file (used for encryption) - see documentation about Poco::Net::Context in Poco docu for more details
		std::string certificateFile; ///< path to the certificate file (in PEM format) - see documentation about Poco::Net::Context in Poco docu for more details
		std::string caLocation; ///< path to CA/root certificates  - see documentation about Poco::Net::Context in Poco docu for more details
		std::string password; ///< password used for CA certificate (if one was used to protect the certificate by a passphrase)
	};

	/**
	* constructor of class HTTPSServerPoco
	* @param httpsParams https server parameters used
	*/
	HTTPSServerPoco(HTTPSServerPoco::HttpsParams &httpsParams);

	/**
	* virtual destructor of class HTTPSServerPoco
	*/
	virtual ~HTTPSServerPoco();

	/**
	* override of createServerSocket(int port) function of HTTPServerPoco - used to create a secure server socket a specified port
	* @param port the server port number used for the https server
	* @return the created secure server socket
	*/
	virtual Poco::Net::ServerSocket createServerSocket(int port);

		/**
	* function to get protocol used
	* @return the protocol as string
	*/
	virtual const std::string getProtocol() const { return("https"); };

private:
	HTTPSServerPoco() {}; // overload standard constructor and prevent its invokation 

};

}
}

#endif // HTTPSServerPoco_def


