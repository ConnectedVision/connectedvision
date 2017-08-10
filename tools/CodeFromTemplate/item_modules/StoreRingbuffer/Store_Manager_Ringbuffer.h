{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreRingbuffer.managerHeaderPath}}
// This file implements the Store_Manager interface for a ringbuffer
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{StoreRingbuffer.managerName}}_def
#define {{StoreRingbuffer.managerName}}_def

#include "{{StoreRingbuffer.managerStubHeaderPath}}"

{{ openNamespace(global.namespace) }}
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define {{StoreRingbuffer.managerName}}_extended

#ifdef {{StoreRingbuffer.managerName}}_extended
/**
 * {{StoreRingbuffer.managerName}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
class {{StoreRingbuffer.managerName}} : public {{StoreRingbuffer.managerStubName}} {
public:
	/**
	* constructor
	*/
	{{StoreRingbuffer.managerName}}(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) : {{StoreRingbuffer.managerStubName}} ( storeCount, ringbufferSize, poolSize )
	{}

	/*
	* virtual destructor
	*/
	virtual ~{{StoreRingbuffer.managerName}}()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // {{StoreRingbuffer.managerName}}_extended

} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#include "{{StoreRingbuffer.managerDefaultHeaderPath}}"

#endif // {{StoreRingbuffer.managerName}}_def