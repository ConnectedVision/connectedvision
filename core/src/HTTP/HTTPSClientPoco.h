/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** HTTPSClientPoco.h
**
** written by Michael Rauter
** 
*******************************************************/

#ifndef HTTPSClientPoco_def
#define HTTPSClientPoco_def

#include <IHTTPAbstraction.h>

namespace ConnectedVision {
namespace HTTP {

class PimplHTTPSClientPoco;
/**
* HTTPS client implementation based on poco
*/
class HTTPSClientPoco : public IHTTPClient
{
public:

	/**
	* https params used for establishing a certified https connection
	*/
	struct Params
	{
		std::string caLocation; ///< path to CA/root certificates  - see documentation about Poco::Net::Context in Poco docu for more details
		std::string caPassword; ///< password used for CA certificate (if one was used to protect the certificate by a passphrase)
	};

	/**
	* constructor of class HTTPSClientPoco
	* @param Params the https params used for establishing a certified https connection for https client requests
	*/
	HTTPSClientPoco(Params);

	~HTTPSClientPoco();

	/**
	* performs a https request - override of IHTTPClient performRequest function
	* @param request a reference to a ConnectedVision::HTTP::HTTPClientRequest used to specify the https client request
	* @param response a reference to a ConnectedVision::HTTP::HTTPResponse object which will be filled out with the response of the https client request
	*/
	virtual void performRequest(const HTTPClientRequest &request, HTTPResponse &response);
private:
	PimplHTTPSClientPoco *pImpl; ///< pimpl paradigm is used for implementing class details

	HTTPSClientPoco() {}; ///< prevent standard constructor invocation
};

}
}

#endif // HTTPSClientPoco_def


