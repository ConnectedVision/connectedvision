{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{InputPin.stubHeaderPath}}
// NEVER TOUCH this file!

#include <ConnectedVisionInputPin.h>

#include "{{global.relativeStubToSrcPath}}{{DataClass.classHeaderPath}}"

#ifndef {{InputPin.stubName}}_def
#define {{InputPin.stubName}}_def

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

/**
 * stub class for {{InputPin.name}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
class {{InputPin.stubName}} : public ConnectedVisionInputPinData<{{DataClass.className}}> {
public:
	static const pinID_t PinID() { return "{{InputPin.PinID}}"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	{{InputPin.stubName}}(IModuleEnvironment *env, const pinID_t inputPinID) : ConnectedVisionInputPinData<{{DataClass.className}}>(env, inputPinID) {};

};

{{ closeNamespace(global.namespace) }}

#endif // {{InputPin.stubName}}_def