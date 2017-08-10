{%- autoescape false -%}{%- include global.macroPath -%}
#include "{{Module.moduleID}}ModuleFactory.h"
#include "{{Module.moduleID}}Module.h"

{{ openNamespace(global.namespace) }}

ConnectedVision::shared_ptr<IConnectedVisionModule> {{Module.moduleID}}ModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new {{Module.moduleID}}Module() );
	if ( !moduleInstance ) 
		throw std::runtime_error("{{Module.moduleID}}ModuleFactory: error creating instance for module: {{Module.name}}");

	return moduleInstance;
}

{{ closeNamespace(global.namespace) }}