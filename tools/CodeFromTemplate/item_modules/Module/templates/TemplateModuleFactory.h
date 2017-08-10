{%- autoescape false -%}{%- include global.macroPath -%}
#ifndef {{Module.moduleID}}ModuleFactory_def
#define {{Module.moduleID}}ModuleFactory_def

#include <IConnectedVisionModule.h>

{{ openNamespace(global.namespace) }}

/**
*	module factory for: {{Module.name}}
*	{{Module.description}}
*/
class {{Module.moduleID}}ModuleFactory
{
public:
	/**
	* factory for {{Module.name}}
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> createModule();
};

{{ closeNamespace(global.namespace) }}

#endif // {{Module.moduleID}}ModuleFactory_def