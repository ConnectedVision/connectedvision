{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{OutputPin.defaultHeaderPath}}
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{OutputPin.className}}_default
#define {{OutputPin.className}}_default

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

// if you want to extend the auto-generated class, enable the line below
//#define {{OutputPin.className}}_extended

#ifndef {{OutputPin.className}}_extended
/**
 * {{OutputPin.name}}
 */
typedef {{OutputPin.stubName}} {{OutputPin.className}};
#endif // {{OutputPin.className}}_extended

{{ closeNamespace(global.namespace) }}

#endif // {{OutputPin.className}}_default