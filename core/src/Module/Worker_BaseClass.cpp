/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "Worker_BaseClass.h"

namespace ConnectedVision {
namespace Module {
	
Worker_BaseClass::Worker_BaseClass (Module_BaseClass &module, IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config) :
	module(module), controller(controller), config(config)
{
	this->logName = module.getModuleID() + " Worker";
}


} // namespace Module
} // namespace ConnectedVision