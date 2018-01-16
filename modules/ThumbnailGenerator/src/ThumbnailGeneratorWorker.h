/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

//TODO do we need env? #include <IModuleEnvironment.h>
#include <Module/Worker_BaseClass.h>

#include "ThumbnailGeneratorModule.h"


namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

class ThumbnailGeneratorWorker : public Worker_BaseClass
{
public:
	ThumbnailGeneratorWorker(
		ThumbnailGeneratorModule &module,		///< [in] reference to "parent" module; This is the explicit ThumbnailGeneratorWorker (no interface) so it is ok to use the explicit ThumbnailGeneratorModule class.
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) : Worker_BaseClass(module, controller, config), module(module) {}

	virtual void run();

protected:
	ThumbnailGeneratorModule &module;
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision