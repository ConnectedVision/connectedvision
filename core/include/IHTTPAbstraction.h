/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** IHTTPAbstraction.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef IHTTPAbstraction_def
#define IHTTPAbstraction_def

#include "IConnectedVisionModule.h"

namespace ConnectedVision {
namespace HTTP {
	// http server enums
	enum EnumConnectedVisionCommandType { CMD_NA = 0, CMD_GET, CMD_SET, CMD_DEL };

	enum EnumHTTPMethod { HTTP_Method_NA = 0, HTTP_Method_HEAD, HTTP_Method_GET, HTTP_Method_POST, HTTP_Method_PUT, HTTP_Method_DELETE };
	enum EnumHTTPStatus { HTTP_Status_NA = 0, HTTP_Status_OK = 200, HTTP_Status_NOT_FOUND = 404, HTTP_Status_ERROR = 500 };

	class HTTPServerRequest; // forward declaration (see definition below)
	class HTTPResponse; // forward declaration (see definition below)

	/**
	* the IHTTPAbstractionCallback interface is a callback class interface that provides the callback to handle HTTP requests
	* an actual implementation of this interface will have to implement the HTTP request handling
	*/
	class IHTTPAbstractionCallback {
	public:
		/**
		* callback function to be overwritten by implementations of the IHTTPAbstractionCallback interface
		* @param request the request object	which holds all necessary data needed to process the request - this data must be filled out by the specific http server implementation before calling this function via its registered callback
		* @param response the response object which holds the results after successful processing of the request - this is the return value and must be filled by the implementation of this function by the class implementing it (the module dispatcher)
		* @return true if request was handled successfully
		*/
		virtual bool handleRequest(const HTTPServerRequest &request, HTTPResponse &response) = 0;
	};

	/**
	* HTTP server request object class
	*/
	class HTTPServerRequest {
	public:
		HTTPServerRequest() : 
			uri(""),
			httpVersion(""),
			jsonString(""),
			targetURL(""),
			host(""),
			serverAddress(""),
			remoteIp(""),
			remotePort(0),
			commandType(CMD_NA),
			payload(""),
			senderID("")
		{
		};

		virtual ~HTTPServerRequest() {};

		const std::string getUri() const { return(uri); };
		const std::string getHttpVersion() const { return(httpVersion); };
		std::string getRemoteIp() const { return(remoteIp); };
		int getRemotePort() const { return(remotePort); };
		const std::string getJsonString() const { return(jsonString); };
		const std::string getTargetURL() const { return(targetURL); };
		const std::string getHost() const { return(host); };
		const std::string getServerAddress() const { return(serverAddress); };

		void setUri(const std::string &uri) { this->uri = uri; };
		void setHttpVersion(const std::string &httpVersion) { this->httpVersion = httpVersion; };
		void setRemoteIp(const std::string &remoteIp) { this->remoteIp = remoteIp; };
		void setRemotePort(const int &remotePort) { this->remotePort = remotePort; };
		void setJsonString(const std::string &jsonString) { this->jsonString = jsonString; };
		void setTargetURL(const std::string &targetURL) { this->targetURL = targetURL; };
		void setHost(const std::string &host) { this->host = host; };
		void setServerAddress(const std::string &serverAddress) { this->serverAddress = serverAddress; };

		const EnumConnectedVisionCommandType getCommandType() const { return(commandType); };
		const std::string getPayload() const { return(payload); };
		const std::string getSenderID() const { return(senderID); };

		void setCommandType(const EnumConnectedVisionCommandType &commandType) { this->commandType = commandType; };
		void setPayload(const std::string &payload) { this->payload = payload; };
		const std::string& getConstRefPayload() const { return(payload); };
		std::string& getRefPayload() { return(payload); };
		void setSenderID(const std::string &senderID) { this->senderID = senderID; };

	protected:
		std::string uri;
		std::string httpVersion;
		std::string jsonString;
		std::string targetURL;
		std::string host;
		std::string serverAddress;
		std::string remoteIp;
		int remotePort;

		EnumConnectedVisionCommandType commandType;
		std::string payload;
		std::string senderID;
	};

	/**
	* HTTP response object class
	*/
	class HTTPResponse {
	public:
		ConnectedVisionResponse content; ///< mime-type and payload
		EnumHTTPStatus status; ///< HTTP status code
	};

	/**
	* the IHTTPServer interface specifies the interface for a HTTP server implementation
	*/
	class IHTTPServer {
	public:
		/**
		* this function must implement the start up of the HTTP server
		*/
		virtual void start() = 0;

		/**
		* this function must implement the shutdown of the HTTP server
		*/
		virtual void stop() = 0;

		/**
		* function to set the callback class which must be inheriting from IHTTPAbstractionCallback interface
		* (and thus the callback function implementation must be implemented and carrying out the HTTP request) 
		* @param pCallbackObject a pointer to the callback class instance
		*/
		virtual void setImplementationCallbackInterface(ConnectedVision::HTTP::IHTTPAbstractionCallback *pCallbackObject) = 0;

		/**
		* function to get base uri
		* @return the base uri as string
		*/
		virtual const std::string getBaseURI() const = 0;

		/**
		* function to get list of server uris (a server will likely have more than just one server uri, because several ip adresses might be assigned to the list of network interfaces on the host system)
		* @return a list of strings containing the server uris
		*/
		virtual const std::vector<std::string> getServerURIs() const = 0;

		/**
		* function to get protocol used
		* @return the protocol ("http" or "https") as string
		*/
		virtual const std::string getProtocol() const = 0;

		/**
		* function to get listening port
		* @return the listing port used
		*/
		virtual const int getListeningPort() const = 0;

		/**
		* function to set the port to which the HTTP server will listen to
		* @param port the port number to which the HTTP server will listen to
		*/
		virtual void setOption_listeningPort(const int port) = 0;

		/**
		* function to set the number of threads for the HTTP server
		* @param numThreads the number of threads used by the HTTP server
		*/
		virtual void setOption_numThreads(const int numThreads) = 0;

		/**
		* function to set the maximum size of the request queue for the HTTP server
		* @param maxQueued the maximum size of the request queue of the HTTP server
		*/
		virtual void setOption_maxQueued(const int maxQueued) = 0;
	};

	/**
	* HTTP client request object class
	*/
	class HTTPClientRequest {
	public:
		HTTPClientRequest() : 
			uri(""),
			httpVersion(""),
			//jsonString(""),
			//targetURL(""),
			serverIp(""),
			serverPort(0),
			method(HTTP_Method_NA),
			payload("")
			//senderID("")
		{
		};

		virtual ~HTTPClientRequest() {};

		const std::string getUri() const { return(uri); };
		const std::string getHttpVersion() const { return(httpVersion); };
		std::string getServerIp() const { return(serverIp); };
		int getServerPort() const { return(serverPort); };
		//const std::string getJsonString() const { return(jsonString); };
		//const std::string getTargetURL() const { return(targetURL); };

		void setUri(const std::string &uri) { this->uri = uri; };
		void setHttpVersion(const std::string &httpVersion) { this->httpVersion = httpVersion; };
		void setServerIp(const std::string &serverIp) { this->serverIp = serverIp; };
		void setServerPort(const int &serverPort) { this->serverPort = serverPort; };
		//void setJsonString(const std::string &jsonString) { this->jsonString = jsonString; };
		//void setTargetURL(const std::string &targetURL) { this->targetURL = targetURL; };

		const EnumHTTPMethod getMethod() const { return this->method; };
		
		const std::string getPayload() const { return(payload); };
		//const std::string getSenderID() const { return(senderID); };

		void setMethod(EnumHTTPMethod method) { this->method = method; };
		
		void setPayload(const std::string &payload) { this->payload = payload; };
		const std::string& getConstRefPayload() const { return(payload); };
		//void setSenderID(const std::string &senderID) { this->senderID = senderID; };

	protected:
		std::string uri;
		std::string httpVersion;
		//std::string jsonString;
		//std::string targetURL;
		std::string serverIp;
		int serverPort;

		HTTP::EnumHTTPMethod method;
		std::string payload;
		//std::string senderID;
	};


	/**
	* interface IHTTPClient (no pure interface - there are function implementations in this interface!)
	*/
	class IHTTPClient {
	public:
		class HTTPClientException: public ::ConnectedVision::runtime_error
		{
		public:
			HTTPClientException(const std::string& msg) : ::ConnectedVision::runtime_error("HTTPClient-exception: " + msg) {};
		};		

		/**
		* used to perform a http client request
		* @param request a reference to a HTTPClientRequest used to specify the http request
		* @param response a reference to response object of type HTTPResponse that will be filled with the response/result of the http request
		*/
		virtual void performRequest(const HTTPClientRequest &request, HTTPResponse &response) = 0;
	};
} // namespace HTTP
} // namespace ConnectedVision

#endif // IHTTPAbstraction_def