/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef SkeletonModuleFactory_def
#define SkeletonModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

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

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // SkeletonModuleFactory_def