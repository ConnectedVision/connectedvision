{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.headerPath}}
// This file implements the IStore interface for SQLite access.
// NEVER TOUCH this file!

#ifndef {{StoreSQLite.className}}_default
#define {{StoreSQLite.className}}_default

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

#ifndef {{StoreSQLite.className}}_extended
/**
 * {{StoreSQLite.className}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
typedef {{StoreSQLite.stubName}} {{StoreSQLite.className}};
#endif // {{StoreSQLite.className}}_extended

#ifndef {{StoreSQLite.factoryName}}_extended
/**
 * factory for {{StoreSQLite.className}}
 */
typedef {{StoreSQLite.factoryStubName}} {{StoreSQLite.factoryName}};
#define {{StoreSQLite.factoryName}}_enabled
#endif // {{StoreSQLite.factoryName}}_extended

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#endif // {{StoreSQLite.className}}_default