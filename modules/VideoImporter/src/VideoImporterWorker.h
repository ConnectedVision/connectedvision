/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef VideoImporterWorker_def
#define VideoImporterWorker_def

//TODO do we need env? #include <IModuleEnvironment.h>
#include <Module/Worker_BaseClass.h>

#include "VideoImporterModule.h"


namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

/**
*	worker for VideoImporter
*	This module imports video frames as well as video meta data from .avi files. It has 2 metadata output pins and 3 raw frame output pins and a png output pin.
*/
class VideoImporterWorker : public Worker_BaseClass
{
public:
	/**
	* worker constructor
	*/
	VideoImporterWorker(
		VideoImporterModule &module,		///< [in] reference to "parent" module; This is the explicit VideoImporterWorker (no interface) so it is ok to use the explicit VideoImporterModule class.
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) : Worker_BaseClass(module, controller, config), module(module) {}
	virtual ~VideoImporterWorker() {}

	virtual void run();
	
protected:
	VideoImporterModule &module;	
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#endif // VideoImporterWorker_def