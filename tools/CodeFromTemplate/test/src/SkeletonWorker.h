#ifndef SkeletonWorker_def
#define SkeletonWorker_def

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmWorker.h>

namespace ConnectedVision {
namespace test {

/**
*	worker for Skeleton Module
*	
*/
class SkeletonWorker : public ConnectedVisionAlgorithmWorker
{
public:
	/**
	* worker constructor
	*/
	SkeletonWorker(
		IModuleEnvironment *env,								///< [in] general environment
		ConnectedVisionModule *module,							///< [in] corresponding module
		boost::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) :	ConnectedVisionAlgorithmWorker(env, module, config) {}
	virtual ~SkeletonWorker() {}

protected:
	virtual void run();
};

} // namespace test
} // namespace ConnectedVision

#endif // SkeletonWorker_def