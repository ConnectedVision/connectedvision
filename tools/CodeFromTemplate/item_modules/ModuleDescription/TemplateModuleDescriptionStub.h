{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{ModuleDescription.stubHeaderPath}}
// NEVER TOUCH this file!

#ifndef Stub_{{ModuleDescription.moduleID}}_ModuleDescription_def
#define Stub_{{ModuleDescription.moduleID}}_ModuleDescription_def

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

/// module description
// --> Do NOT EDIT <--
static const char _moduleDescription[] =
	"{{ModuleDescription.moduleDescription|replace('"','\"','g')|replace('(\n)','\n"$1	"','gm')}}";

/// input description
// --> Do NOT EDIT <--
static const char _inputPinDescription[] =
	"{{ModuleDescription.inputDescription|replace('"','\"','g')|replace('(\n)','\n"$1	"','gm')}}";

/// output description
// --> Do NOT EDIT <--
static const char _outputPinDescription[] =
	"{{ModuleDescription.outputDescription|replace('"','\"','g')|replace('(\n)','\n"$1	"','gm')}}";

{{ closeNamespace(global.namespace) }}

#endif // Stub_{{ModuleDescription.moduleID}}_ModuleDescription_def