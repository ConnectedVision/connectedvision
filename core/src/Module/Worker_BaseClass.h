 /**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Worker_BaseClass_def
#define Worker_BaseClass_def

#include "Module_BaseClass.h"

namespace ConnectedVision {
namespace Module {

class Worker_BaseClass : public IWorker
{
public:
	/**
	* worker constructor
	*/
	Worker_BaseClass(
		Module_BaseClass &module,						///< [in] reference to "parent" module
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	);


	virtual IModule* getModule() { return static_cast<IModule*>(&module); };

	virtual boost::shared_ptr<Logging::ILogWriter> log() const { return module.log(); };
protected:
	Module_BaseClass &module;
	IWorkerControllerCallbacks &controller;
	ConnectedVision::shared_ptr<const Class_generic_config> config;
	
	std::string logName;
};

} // namespace Module
} // namespace ConnectedVision

#endif // Worker_BaseClass_def