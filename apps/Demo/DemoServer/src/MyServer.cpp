/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "MyServer.h"
#include <ConnectedVisionModule.h>

using namespace ConnectedVision;

void MyServer::handleDefault(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response)
{
	return getHostStatus(request, response);
}