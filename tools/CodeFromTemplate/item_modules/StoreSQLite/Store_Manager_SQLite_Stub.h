{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.managerStubHeaderPath}}
// NEVER TOUCH this file!

#ifndef {{StoreSQLite.managerStubName}}_def
#define {{StoreSQLite.managerStubName}}_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "{{global.relativeStubToSrcPath}}{{DataClass.classHeaderName}}"
#include "{{global.relativeStubToSrcPath}}{{StoreSQLite.headerPath}}"

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: {{StoreSQLite.className}}
 */
class {{StoreSQLite.managerStubName}} :
	public ConnectedVision::DataHandling::Store_Manager_Basic<{{DataClass.className}}>
{
public:
	/**
	* constructor
	*/
	{{StoreSQLite.managerStubName}}(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~{{StoreSQLite.managerStubName}}();

private:
	// singleton in module scope
	{{StoreSQLite.managerStubName}}(const {{StoreSQLite.managerStubName}} &);	// restrict copy constructor
	{{StoreSQLite.managerStubName}} & operator = (const {{StoreSQLite.managerStubName}} &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#endif // {{StoreSQLite.managerStubName}}_def