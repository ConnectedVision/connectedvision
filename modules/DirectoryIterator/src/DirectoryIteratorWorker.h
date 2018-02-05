/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DirectoryIteratorWorker_def
#define DirectoryIteratorWorker_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
*	worker for Directory Iterator
*	Iterates a directory and returns the files with the extensions specified in the config.
*/
class DirectoryIteratorWorker : public IWorker
{
public:
	/**
	* worker constructor
	*/
	DirectoryIteratorWorker(
		DirectoryIteratorModule &module,						///< [in] reference to "parent" module
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
		) : module(module), controller(controller), config(config) {}
	virtual ~DirectoryIteratorWorker() {}

	virtual void run();

	virtual IModule* getModule() { return static_cast<IModule*>(&module); };

protected:
	DirectoryIteratorModule &module;
	IWorkerControllerCallbacks &controller;
	ConnectedVision::shared_ptr<const Class_generic_config> config;

};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // DirectoryIteratorWorker_def