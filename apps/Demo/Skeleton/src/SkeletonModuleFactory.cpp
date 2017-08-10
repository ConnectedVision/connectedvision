/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "SkeletonModuleFactory.h"
#include "SkeletonModule.h"

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

ConnectedVision::shared_ptr<IConnectedVisionModule> SkeletonModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new SkeletonModule() );
	if ( !moduleInstance ) 
		throw std::runtime_error("SkeletonModuleFactory: error creating instance for module: Skeleton Module");

	return moduleInstance;
}

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision