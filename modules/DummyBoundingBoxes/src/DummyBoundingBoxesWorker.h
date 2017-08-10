/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>
#include <ConnectedVisionAlgorithmWorker.h>

#include "Class_DummyBoundingBoxes_output_Detections.h"
#include "Class_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

class DummyBoundingBoxesWorker : public ConnectedVisionAlgorithmWorker
{
public:
	DummyBoundingBoxesWorker(IModuleEnvironment *env, ConnectedVisionModule *module, boost::shared_ptr<const Class_generic_config> config) :
		ConnectedVisionAlgorithmWorker(env, module, config) {};

protected:
	virtual void run();
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision