{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.managerHeaderPath}}
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{StoreSQLite.managerName}}_def
#define {{StoreSQLite.managerName}}_def

#include "{{StoreSQLite.managerStubHeaderPath}}"

{{ openNamespace(global.namespace) }}
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define {{StoreSQLite.managerName}}_extended

#ifdef {{StoreSQLite.managerName}}_extended
/**
 * SQLite store manager for: {{StoreSQLite.className}}
 */
class {{StoreSQLite.managerName}} : public {{StoreSQLite.managerStubName}} {
public:
	/**
	* constructor
	*/
	{{StoreSQLite.managerName}}(
		DBConnection& db				///< [in] DB connection object
	) : {{StoreSQLite.managerStubName}} ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~{{StoreSQLite.managerName}}()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#include "{{StoreSQLite.managerDefaultHeaderPath}}"

#endif // {{StoreSQLite.managerName}}_def