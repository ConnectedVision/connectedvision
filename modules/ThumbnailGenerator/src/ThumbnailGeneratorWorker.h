/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmWorker.h>

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

class ThumbnailGeneratorWorker : public ConnectedVisionAlgorithmWorker
{
public:
	ThumbnailGeneratorWorker(IModuleEnvironment *env, ConnectedVisionModule *module, boost::shared_ptr<const Class_generic_config> config) :
		ConnectedVisionAlgorithmWorker(env, module, config) {};

protected:
	virtual void run();

};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision