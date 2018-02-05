/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ModuleDispatcher_def
#define ModuleDispatcher_def

#include <string>
#include <vector>

#include <IHTTPAbstraction.h>

#include <IConnectedVisionModule.h>
#include <IModuleEnvironment.h>

#include <boost/shared_ptr.hpp>

#include <opencv2/core/core.hpp> // needed for host logo

namespace ConnectedVision
{

class ModuleDispatcher: public IModuleEnvironment, public ConnectedVision::HTTP::IHTTPAbstractionCallback
{
public:
	struct HttpServerParams
	{
		int listeningPort;
		int numThreads;
	};

	struct HttpsServerParams
	{
		int listeningPort;
		int numThreads;		
		std::string privateKeyFile;
		std::string certificateFile;
		std::string caLocation;
		std::string password;
	};

	// buffer with host logo as PNG data - the logo will be displayed on the main html page
	typedef struct BufferLogoPNG
	{
		char *pBufferLogoAsPNG;
		int sizeBufferLogoAsPNG;
	} BufferLogoPNG;

	ModuleDispatcher(HttpServerParams &httpServerParams);
	ModuleDispatcher(HttpServerParams &httpServerParams, HttpsServerParams &httpsServerParams);
	ModuleDispatcher(HttpsServerParams &httpsServerParams);
    virtual ~ModuleDispatcher();

	void start();
	void stop();

	static inline std::string getModuleName() { return "ModuleDispatcher"; };

	virtual void registerModule( boost::shared_ptr<ConnectedVision::Module::IModule> module );
	virtual boost::shared_ptr<ConnectedVision::Module::IModule> getModule( std::string moduleName ) const;
	virtual std::string getModuleURL( std::string serverAddress, std::string moduleName ) const;
	virtual std::string getDataPath() const;
	virtual void setDataPath(std::string path);

	// sets the logo displayed on the main html page
	virtual void setLogoPNG(const BufferLogoPNG &logoPNG);

	virtual Class_HostStatus getHostStatus() { return hostStatus; };

	/**
	* overwrite of callback function
	* @param request the request object	which holds all necessary data needed to process the request - this data must be filled out by the specific http server implementation before calling it
	* @param response the response object which holds the results after successful processing of the request
	* @return true if request was handled successfully
	*/
	virtual bool handleRequest(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);

protected:
	virtual void handleDefault(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);
	virtual void handlePostRequests(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);

	virtual void getModuleList(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);
	virtual void getHostInfo(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);
	virtual void getHostStatus(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);
	virtual void getHostLogoPNG(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);
	virtual ConnectedVision::HTTP::EnumHTTPStatus getConfigListOverview(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);

protected:
	Class_HostStatus hostStatus;

	//std::string baseURI;
	std::string dataPath;
	std::vector< boost::shared_ptr<ConnectedVision::Module::IModule> > modules;

	// host logo png image as cv::Mat image
	boost::shared_ptr<cv::Mat> logo;

protected:
	boost::shared_ptr<ConnectedVision::HTTP::IHTTPServer> pHttpServer;

	boost::shared_ptr<ConnectedVision::HTTP::IHTTPServer> pHttpsServer;

//public:
	//void setOption_listeningPort(const int port);
	//void setOption_numThreads(const int numThreads);
private:
	void setHostAndSystemID();

	void initHttpServer(HttpServerParams &httpServerParams);
	void initHttpsServer(HttpsServerParams &httpsServerParams);
};

} // namespace ConnectedVision

#endif // ModuleDispatcher_def
