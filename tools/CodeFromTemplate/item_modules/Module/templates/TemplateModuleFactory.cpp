{%- autoescape false -%}{%- include global.macroPath -%}
#include "{{Module.moduleID}}ModuleFactory.h"
#include "{{Module.moduleID}}Module.h"

{{ openNamespace(global.namespace) }}

ConnectedVision::shared_ptr<IModule> {{Module.moduleID}}ModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<IModule> moduleInstance = boost::dynamic_pointer_cast<IModule>(ConnectedVision::make_shared<{{Module.moduleID}}Module>());
	if ( !moduleInstance ) 
		throw std::runtime_error("{{Module.moduleID}}ModuleFactory: error creating instance for module: {{Module.name}}");

	return moduleInstance;
}


{{ closeNamespace(global.namespace) }}
