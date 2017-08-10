{%- autoescape false -%}{%- include global.macroPath -%}
#ifndef {{Module.moduleID}}Worker_def
#define {{Module.moduleID}}Worker_def

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmWorker.h>

{{ openNamespace(global.namespace) }}

/**
*	worker for {{Module.name}}
*	{{Module.description}}
*/
class {{Module.moduleID}}Worker : public ConnectedVisionAlgorithmWorker
{
public:
	/**
	* worker constructor
	*/
	{{Module.moduleID}}Worker(
		IModuleEnvironment *env,								///< [in] general environment
		ConnectedVisionModule *module,							///< [in] corresponding module
		boost::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	) :	ConnectedVisionAlgorithmWorker(env, module, config) {}
	virtual ~{{Module.moduleID}}Worker() {}

protected:
	virtual void run();
};

{{ closeNamespace(global.namespace) }}

#endif // {{Module.moduleID}}Worker_def