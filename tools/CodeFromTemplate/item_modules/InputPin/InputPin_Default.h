{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{InputPin.defaultHeaderPath}}
// This file implements the InputPin interface.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{InputPin.className}}_default
#define {{InputPin.className}}_default

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

// if you want to extend the auto-generated class, enable the line below
//#define {{InputPin.className}}_extended

#ifndef {{InputPin.className}}_extended
/**
 * {{InputPin.name}}
 */
typedef {{InputPin.stubName}} {{InputPin.className}};
#endif // {{InputPin.className}}_extended

{{ closeNamespace(global.namespace) }}

#endif // {{InputPin.className}}_default