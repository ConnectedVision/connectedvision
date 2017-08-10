{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.managerDefaultHeaderPath}}
// NEVER TOUCH this file!

#ifndef {{StoreSQLite.managerName}}_default
#define {{StoreSQLite.managerName}}_default

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

#ifndef {{StoreSQLite.managerName}}_extended
/**
 * SQLite store manager for: {{StoreSQLite.className}}
 */
typedef {{StoreSQLite.managerStubName}} {{StoreSQLite.managerName}};
#endif // {{StoreSQLite.managerName}}_extended

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#endif // {{StoreSQLite.managerName}}_default