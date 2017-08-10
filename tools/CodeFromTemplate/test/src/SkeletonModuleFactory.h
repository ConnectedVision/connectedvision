#ifndef SkeletonModuleFactory_def
#define SkeletonModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace test {

/**
*	module factory for: Skeleton Module
*	
*/
class SkeletonModuleFactory
{
public:
	/**
	* factory for Skeleton Module
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> createModule();
};

} // namespace test
} // namespace ConnectedVision

#endif // SkeletonModuleFactory_def