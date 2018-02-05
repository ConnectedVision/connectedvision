/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <Module/Worker_BaseClass.h>

#include "DummyBoundingBoxesModule.h"
#include "Class_DummyBoundingBoxes_output_Detections.h"
#include "Class_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

class DummyBoundingBoxesWorker : public Worker_BaseClass
{
public:
	DummyBoundingBoxesWorker(
		DummyBoundingBoxesModule &module,		///< [in] reference to "parent" module; This is the explicit DummyBoundingBoxesWorker (no interface) so it is ok to use the explicit DummyBoundingBoxesModule class.
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) : Worker_BaseClass(module, controller, config), module(module) {}

	virtual void run();

protected:
	DummyBoundingBoxesModule &module;

};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision