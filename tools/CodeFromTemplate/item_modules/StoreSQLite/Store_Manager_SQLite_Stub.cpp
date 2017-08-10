{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.managerStubPath}}
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "{{StoreSQLite.managerStubHeaderName}}"

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

// --> Do NOT EDIT <--
int {{StoreSQLite.managerStubName}}::creationCount = 0;

// --> Do NOT EDIT <--
{{StoreSQLite.managerStubName}}::{{StoreSQLite.managerStubName}}( DBConnection& db ) : 
	Store_Manager_Basic<{{DataClass.className}}>( boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite_Factory<{{DataClass.className}}> >( make_shared<{{StoreSQLite.factoryName}}>( db	)) )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of {{StoreSQLite.managerStubName}} allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
{{StoreSQLite.managerStubName}}::~{{StoreSQLite.managerStubName}}()
{
	creationCount = 0; 
}

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}