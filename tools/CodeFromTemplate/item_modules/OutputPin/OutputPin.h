{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{OutputPin.headerPath}}
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{OutputPin.className}}_def
#define {{OutputPin.className}}_def

#include "{{OutputPin.stubHeaderPath}}"

{{ openNamespace(global.namespace) }}

// if you want to extend the auto-generated class, enable the line below
//#define {{OutputPin.className}}_extended

#ifdef {{OutputPin.className}}_extended
/**
 * {{OutputPin.name}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
class {{OutputPin.className}} : public {{OutputPin.stubName}} {
public:
	{{OutputPin.className}}(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<{{DataClass.className}}> > > dataStore) :
		{{OutputPin.stubName}}(dataStore) {};
	virtual ~{{OutputPin.className}}() {}
};
#endif // {{OutputPin.className}}_extended

{{ closeNamespace(global.namespace) }}

#include "{{OutputPin.defaultHeaderPath}}"

#endif // {{OutputPin.className}}_def