{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreRingbuffer.managerDefaultHeaderPath}}
// NEVER TOUCH this file!

#ifndef {{StoreRingbuffer.managerName}}_default
#define {{StoreRingbuffer.managerName}}_default

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

#ifndef {{StoreRingbuffer.managerName}}_extended
/**
 * {{StoreRingbuffer.managerName}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
typedef {{StoreRingbuffer.managerStubName}} {{StoreRingbuffer.managerName}};
#endif // {{StoreRingbuffer.managerName}}_extended

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#endif // {{StoreRingbuffer.managerName}}_default