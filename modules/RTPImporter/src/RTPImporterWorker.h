/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>
#include <ConnectedVisionAlgorithmWorker.h>

#include "Class_RTPImporter_params.h"

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavformat/avio.h>
    #include <libswscale/swscale.h>
}
#include <boost/circular_buffer.hpp>

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

class RTPImporterWorker : public ConnectedVisionAlgorithmWorker
{
public:
	RTPImporterWorker(IModuleEnvironment *env, ConnectedVisionModule *module, boost::shared_ptr<const Class_generic_config> config);

	void start();
	void stop();
	
protected:
	void initResources(); ///< function used to initialize resources
	void freeResources(); ///< function used to free up resources
	virtual void run();

	Class_RTPImporter_params params;

	SwsContext *imgConvertCtx;
	AVFormatContext* formatCtx;
	AVCodecContext* codecCtx;
	int videoStreamIndex;

	boost::circular_buffer<AVPacket> rcvdGOPs;
	boost::mutex rcvdGOPs_access;
	boost::condition_variable rcvdGOPs_notEmpty;
};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision