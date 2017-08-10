/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef SkeletonWorker_def
#define SkeletonWorker_def

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmWorker.h>

#include "Class_Skeleton_input_Detections.h"

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

/**
* worker for Skeleton Module
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

	/**
	* The real algorithm ... or, in this case just a dummy example computing the average color of a bounding box.
	*/
	ConnectedVision::shared_ptr<const Class_Skeleton_output_Average> computeAverage(
		boost::shared_ptr<Class_Skeleton_input_Detections> detection, 
		boost::shared_ptr<std::string> pngImg,
		boost::shared_ptr< ConnectedVision::DataHandling::IDataAllocator<Class_Skeleton_output_Average> > allocator
	);
};

}}} // namespace

#endif // SkeletonWorker_def