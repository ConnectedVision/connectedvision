{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.headerPath}}
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{StoreSQLite.className}}_def
#define {{StoreSQLite.className}}_def

#include "{{StoreSQLite.stubHeaderPath}}"

{{ openNamespace(global.namespace) }}
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define {{StoreSQLite.className}}_extended

#ifdef {{StoreSQLite.className}}_extended
/**
 * {{StoreSQLite.className}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
class {{StoreSQLite.className}} : public {{StoreSQLite.stubName}} {
public:
	/**
	* constructor
	*/
	{{StoreSQLite.className}}(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : {{StoreSQLite.stubName}} ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~{{StoreSQLite.className}}()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // {{StoreSQLite.className}}_extended


// if you want to extend the auto-generated class, enable the line below
//#define {{StoreSQLite.factoryName}}_extended

#ifdef {{StoreSQLite.factoryName}}_extended
/**
 * factory for {{StoreSQLite.className}}
 */
class {{StoreSQLite.factoryName}} : public {{StoreSQLite.factoryStubName}} {
public:
	/**
	* constructor
	*/
	{{StoreSQLite.factoryName}}(
		DBConnection& db				///< [in] DB connection object
	) : {{StoreSQLite.factoryStubName}} ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~{{StoreSQLite.factoryName}}()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define {{StoreSQLite.factoryName}}_enabled
#endif // {{StoreSQLite.factoryName}}_extended

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#include "{{StoreSQLite.defaultHeaderPath}}"

#endif // {{StoreSQLite.className}}_def