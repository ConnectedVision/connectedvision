{%- autoescape false -%}{%- include global.macroPath -%}
#ifndef {{Module.moduleID}}Worker_def
#define {{Module.moduleID}}Worker_def

#include "{{Module.moduleID}}Module.h"
#include <Module/Worker_BaseClass.h>

{{ openNamespace(global.namespace) }}

/**
*	worker for {{Module.name}}
*	{{Module.description}}
*/
class {{Module.moduleID}}Worker : public Worker_BaseClass
{
public:
	/**
	* worker constructor
	*/
	{{Module.moduleID}}Worker(
		{{Module.moduleID}}Module &module,		///< [in] reference to "parent" module; This is the explicit xxxWorker (no interface) so it is ok to use the explicit xxxModule class.
		IWorkerControllerCallbacks &controller,					///< [in] worker controller (for callbacks)
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) : Worker_BaseClass(module, controller, config), module(module) {}
	virtual ~{{Module.moduleID}}Worker() {}

	virtual void run();


protected:
	{{Module.moduleID}}Module &module;
};

{{ closeNamespace(global.namespace) }}

#endif // {{Module.moduleID}}Worker_def

