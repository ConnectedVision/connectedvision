{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreRingbuffer.stubHeaderPath}}
// NEVER TOUCH this file!

#ifndef {{StoreRingbuffer.managerStubName}}_def
#define {{StoreRingbuffer.managerStubName}}_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "{{global.relativeStubToSrcPath}}{{DataClass.classHeaderPath}}"

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: {{StoreRingbuffer.managerName}}
 *
 * module: {{global.moduleName}}
 * description: {{DataClass.description}}
 */
class {{StoreRingbuffer.managerStubName}} : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<{{DataClass.className}}> {
public:
	/**
	* constructor
	*/
	{{StoreRingbuffer.managerStubName}}(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~{{StoreRingbuffer.managerStubName}}();

private:
	// singleton in module scope
	{{StoreRingbuffer.managerStubName}}(const {{StoreRingbuffer.managerStubName}} &);	// restrict copy constructor
	{{StoreRingbuffer.managerStubName}} & operator = (const {{StoreRingbuffer.managerStubName}} &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
{{ closeNamespace(global.namespace) }}

#endif // {{StoreRingbuffer.managerStubName}}_def