/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPServerPoco.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef HTTPServerPoco_def
#define HTTPServerPoco_def

#include <IHTTPAbstraction.h>

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
*/
class HTTPServerPoco : public IHTTPServer
{
public:

	/**
	* constructor of class HTTPServerPoco
	*/
	HTTPServerPoco();

	/**
	* virtual destructor of class HTTPServerPoco
	*/
	virtual ~HTTPServerPoco();

	/**
	* used to create a server socket a specified port
	* @param port the server port number used for the http server
	* @return the created server socket
	*/
	virtual Poco::Net::ServerSocket createServerSocket(int port);

	/**
	* override of IHTTPServer::start() function
	*/
	void start();

	/**
	* override of IHTTPServer::stop() function
	*/
	void stop();

	/**
	* function to set the callback class which must be inheriting from IHTTPAbstractionCallback interface
	* (and thus the callback function implementation must be implemented and process the HTTP request and produce the HTTP response)
	* @param pCallbackObject a pointer to the callback class instance
	*/
	void setImplementationCallbackInterface(ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject);

	/**
	* function to get base uri
	* @return the base uri as string
	*/
	const std::string getBaseURI() const { return(serverURIs.at(0));};

	/**
	* function to get protocol used
	* @return the protocol as string
	*/
	const std::string getProtocol() const { return("http"); };

	/**
	* function to get listening port
	* @return the listing port used
	*/
	const int getListeningPort() const { return(port); };

	/**
	* returns a std::vector of server uris that can be used to communicate with the server
	* all network interfaces will be taken into account as well as every configured ip address for each interface
	* (every ip address configured for the network interface will result in a seperate server uri)
	* @return a std::vector containing the list of server uris
	*/
	const std::vector<std::string> getServerURIs() const { return(serverURIs); };

	void setOption_listeningPort(const int port);
	void setOption_numThreads(const int numThreads);
	void setOption_maxQueued(const int maxQueued);

protected:

	/**
	* custom error handler class that will ignore ConnectionResetException and ConnectionAbortedException (and rethrow all other exceptions)
	*/
	class CustomErrorHandler : public Poco::ErrorHandler
	{
	public:
		CustomErrorHandler() {}
		virtual ~CustomErrorHandler() {}

		virtual void exception(const Poco::Exception& exc);
	} customErrorHandler;

	ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject; ///< pointer to the callback class instance (use function @ref setCallback to register a callback class instance) - NOTE: it is intended that this is a raw pointer - otherwise a shared_ptr cycle would be created between the class implementing IHTTPAbstractionCallback and this class (implementing IHTTPServer)

	std::unique_ptr<Poco::Net::HTTPServer> pServer; ///< pointer to Poco::Net::HTTPServer instance

	Poco::UInt16 port; ///< port used for http server connection
	Poco::AutoPtr<Poco::Net::HTTPServerParams> pServerParams; ///< server parameters used for Poco::Net::HTTPServer instance

	std::vector<std::string> serverURIs; ///< the list of server uri strings (a server will likely have more than just one server uri, because several ip adresses might be assigned to the list of network interfaces on the host system)

	Poco::ErrorHandler *pOriginalPocoErrorHandler; ///< original global POCO error handler
};

}
}

#endif // HTTPServerPoco_def


