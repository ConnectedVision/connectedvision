/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef VideoImporterWorker_def
#define VideoImporterWorker_def

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmWorker.h>

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

/**
*	worker for VideoImporter
*	This module imports video frames as well as video meta data from .avi files. It has 2 metadata output pins and 3 raw frame output pins and a png output pin.
*/
class VideoImporterWorker : public ConnectedVisionAlgorithmWorker
{
public:
	/**
	* worker constructor
	*/
	VideoImporterWorker(
		IModuleEnvironment *env,								///< [in] general environment
		ConnectedVisionModule *module,							///< [in] corresponding module
		boost::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) :	ConnectedVisionAlgorithmWorker(env, module, config) {}
	virtual ~VideoImporterWorker() {}

protected:
	virtual void run();
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#endif // VideoImporterWorker_def