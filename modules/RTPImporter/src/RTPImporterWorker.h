/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

//TODO do we need env? #include <IModuleEnvironment.h>
#include <Module/Worker_BaseClass.h>

#include "RTPImporterModule.h"
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

class RTPImporterWorker : public Worker_BaseClass
{
public:
	RTPImporterWorker(
		RTPImporterModule &module,		///< [in] reference to "parent" module; This is the explicit RTPImporterWorker (no interface) so it is ok to use the explicit RTPImporterModule class.
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	);

	virtual void run();
	
	
protected:
	RTPImporterModule &module;

	void initResources(); ///< function used to initialize resources
	void freeResources(); ///< function used to free up resources

	SwsContext *imgConvertCtx;
	AVFormatContext* formatCtx;
	AVCodecContext* codecCtx;
	uint8_t* pictureDst;
	uint8_t* pictureSrc;
	AVFrame* pic;
	AVFrame* picrgb;
};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision