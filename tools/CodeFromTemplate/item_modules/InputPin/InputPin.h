{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{InputPin.headerPath}}
// This file implements the InputPin interface.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{InputPin.className}}_def
#define {{InputPin.className}}_def

#include "{{InputPin.stubHeaderPath}}"

{{ openNamespace(global.namespace) }}

// if you want to extend the auto-generated class, enable the line below
//#define {{InputPin.className}}_extended

#ifdef {{InputPin.className}}_extended
/**
 * {{InputPin.name}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
class {{InputPin.className}} : public {{InputPin.stubName}} {
public:
	{{InputPin.className}}(IModuleEnvironment *env, const pinID_t inputPinID) : {{InputPin.stubName}}(env, inputPinID) {};

};
#endif // {{InputPin.className}}_extended

{{ closeNamespace(global.namespace) }}

#include "{{InputPin.defaultHeaderPath}}"

#endif // {{InputPin.className}}_def