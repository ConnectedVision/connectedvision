{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreRingbuffer.managerStubPath}}
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "{{StoreRingbuffer.managerStubHeaderName}}"

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

// --> Do NOT EDIT <--
int {{StoreRingbuffer.managerStubName}}::creationCount = 0;

// --> Do NOT EDIT <--
{{StoreRingbuffer.managerStubName}}::{{StoreRingbuffer.managerStubName}}(const int64_t storeCount, const int64_t ringbufferSize, const int64_t poolSize) :
	ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<{{DataClass.className}}> ( storeCount, ringbufferSize, poolSize )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of {{StoreRingbuffer.managerStubName}} allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
{{StoreRingbuffer.managerStubName}}::~{{StoreRingbuffer.managerStubName}}()
{
	creationCount = 0; 
}

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}