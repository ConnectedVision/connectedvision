/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPClientPoco.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef HTTPClientPoco_def
#define HTTPClientPoco_def

#include <IHTTPAbstraction.h>

namespace ConnectedVision {
namespace HTTP {

/**
* HTTP client implementation based on poco
*/
class HTTPClientPoco : public IHTTPClient
{
public:

	/**
	* constructor of class HTTPClientPoco
	*/
	HTTPClientPoco();

	/**
	* performs a http request - override of IHTTPClient performRequest function
	* @param request a reference to a ConnectedVision::HTTP::HTTPClientRequest used to specify the http client request
	* @param response a reference to a ConnectedVision::HTTP::HTTPResponse object which will be filled out with the response of the http client request
	*/
	virtual void performRequest(const HTTPClientRequest &request, HTTPResponse &response);
};

}
}

#endif // HTTPClientPoco_def


