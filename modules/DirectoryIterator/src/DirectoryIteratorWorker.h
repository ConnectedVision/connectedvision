/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DirectoryIteratorWorker_def
#define DirectoryIteratorWorker_def

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmWorker.h>

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
*	worker for Directory Iterator
*	Iterates a directory and returns the files with the extensions specified in the config.
*/
class DirectoryIteratorWorker : public ConnectedVisionAlgorithmWorker
{
public:
	/**
	* worker constructor
	*/
	DirectoryIteratorWorker(
		IModuleEnvironment *env,								///< [in] general environment
		ConnectedVisionModule *module,							///< [in] corresponding module
		boost::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) :	ConnectedVisionAlgorithmWorker(env, module, config) {}
	virtual ~DirectoryIteratorWorker() {}

protected:
	virtual void run();
};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // DirectoryIteratorWorker_def