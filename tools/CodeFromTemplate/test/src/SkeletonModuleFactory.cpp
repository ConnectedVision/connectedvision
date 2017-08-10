#include "SkeletonModuleFactory.h"
#include "SkeletonModule.h"

namespace ConnectedVision {
namespace test {

ConnectedVision::shared_ptr<IConnectedVisionModule> SkeletonModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new SkeletonModule() );
	if ( !moduleInstance ) 
		throw std::runtime_error("SkeletonModuleFactory: error creating instance for module: Skeleton Module");

	return moduleInstance;
}

} // namespace test
} // namespace ConnectedVision