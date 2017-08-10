/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <Poco/Thread.h>
#include <curl/curl.h>

#include <IHTTPAbstraction.h>
#include <HTTP/HTTPServerPoco.h>

#include <CppUTest/TestHarness.h>
#include <CppUTest/MemoryLeakDetectorNewMacros.h>

/**
 * cleanup and deallocate CURL
 */
static void curl_Deallocator(CURL *curl)
{
	curl_easy_cleanup(curl);
}

/**
 * read date from HTTP response
 */
static size_t curl_writeToString(void *ptr, size_t size, size_t count, void *stream) 
{
  ((std::string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

/**
 * abort read date from HTTP response
 */
static size_t curl_abortWrite(void *ptr, size_t size, size_t count, void *stream) 
{
  return -1;
}


/**
 * create CURL instance as shared pointer
 */
static boost::shared_ptr<CURL> make_curl( std::string &buffer )
{
	boost::shared_ptr<CURL> curl( curl_easy_init(), curl_Deallocator );
	if ( !curl )
		throw std::runtime_error("cannot create CURL");
	
	curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, curl_writeToString);
	curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &buffer);

	return curl;
}


namespace ConnectedVision {
namespace HTTP {

class ServerCallback_Test: public ConnectedVision::HTTP::IHTTPAbstractionCallback
{
public:
	virtual bool handleRequest(const HTTPServerRequest &request, HTTPResponse &response)
	{
		response.content.setContent("<html><body>TEST</body></hrml>");
		response.content.setContentType("text/html");
		response.status = ConnectedVision::HTTP::EnumHTTPStatus::HTTP_Status_OK;
		return true;
	}

};


TEST_GROUP(HTTPServerPoco)
{
	void setup()
	{
		// Init stuff
		MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();
		// TODO: fix memory leak false alarms for POCO
	}

	void teardown()
	{
		// Uninit stuff
		MemoryLeakWarningPlugin::turnOnNewDeleteOverloads();
	}

};

IGNORE_TEST(HTTPServerPoco, MemoryLeakWarning)
{
	FAIL("fix memory leak false alarms for POCO");
}

IGNORE_TEST(HTTPServerPoco, init)
{
	//////////////////////////////////////
	// test initialization


	//////////////////////////////////////
	// actual test
	ConnectedVision::HTTP::HTTPServerPoco server;

	ConnectedVision::HTTP::ServerCallback_Test callback;
	server.setOption_listeningPort(8888);
	server.setImplementationCallbackInterface(&callback);

	server.start();
	server.stop();

}

IGNORE_TEST(HTTPServerPoco, answers_to_request)
{
	//////////////////////////////////////
	// test initialization
	std::string data;

	// HTTP Client: curl
	auto curl = make_curl( data );

	// HTTP Server: POCO
	ConnectedVision::HTTP::HTTPServerPoco server;
	ServerCallback_Test callback;
	server.setOption_listeningPort(8888);
	server.setImplementationCallbackInterface(&callback);


	//////////////////////////////////////
	// actual test
	server.start();

	// perform request
	curl_easy_setopt(curl.get(), CURLOPT_URL, "localhost:8888");
	CURLcode status = curl_easy_perform(curl.get());

	// stop server
	server.stop();

	// test response
	CHECK_EQUAL( CURLE_OK, status );
	CHECK( !data.empty() );
}

IGNORE_TEST(HTTPServerPoco, abort_request_while_reading_response)
{
	//////////////////////////////////////
	// test initialization
	std::string data;

	// HTTP Client: curl
	auto curl = make_curl( data );
	curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, curl_abortWrite);

	// HTTP Server: POCO
	ConnectedVision::HTTP::HTTPServerPoco server;
	ServerCallback_Test callback;
	server.setOption_listeningPort(8888);
	server.setImplementationCallbackInterface(&callback);


	//////////////////////////////////////
	// actual test
	server.start();

	// perform request
	curl_easy_setopt(curl.get(), CURLOPT_URL, "localhost:8888");
	CURLcode status = curl_easy_perform(curl.get());

	// stop server
	server.stop();

	// test response
	CHECK( CURLE_OK != status );
}



}} // namespace scope

