{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{DataClass.defaultHeaderPath}}
// This file contains the business logic.
// NEVER TOUCH this file!

#ifndef {{DataClass.className}}_default
#define {{DataClass.className}}_default

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

#ifndef {{DataClass.className}}_extended
/**
 * {{DataClass.className}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
typedef {{DataClass.stubName}} {{DataClass.className}};
typedef boost::shared_ptr<{{DataClass.className}}> {{DataClass.className}}_p;
#endif // {{DataClass.className}}_extended

{{ closeNamespace(global.namespace) }}

#endif // {{DataClass.className}}_default