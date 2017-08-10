/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <ModuleDispatcher/ModuleDispatcher.h>

namespace ConnectedVision
{
class MyServer: public ModuleDispatcher
{
public:
	MyServer(HttpServerParams &httpServerParams) : ModuleDispatcher(httpServerParams) {};
	MyServer(HttpServerParams &httpServerParams, HttpsServerParams &httpsServerParams) : ModuleDispatcher(httpServerParams, httpsServerParams) {};
	MyServer(HttpsServerParams &httpsServerParams) : ModuleDispatcher(httpsServerParams) {};

	virtual void handleDefault(const ConnectedVision::HTTP::HTTPServerRequest &request, ConnectedVision::HTTP::HTTPResponse &response);
};
} // namespace ConnectedVision