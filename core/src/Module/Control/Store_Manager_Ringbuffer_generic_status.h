/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_Ringbuffer_generic_status.h
// This file implements the Store_Manager interface for a ringbuffer
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_Ringbuffer_generic_status_def
#define Store_Manager_Ringbuffer_generic_status_def

#include "stubs/Store_Manager_Ringbuffer_Stub_generic_status.h"

namespace ConnectedVision {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_Ringbuffer_generic_status_extended

#ifdef Store_Manager_Ringbuffer_generic_status_extended
/**
 * Store_Manager_Ringbuffer_generic_status
 *
 * module: 
 * description: config status
 */
class Store_Manager_Ringbuffer_generic_status : public Store_Manager_Ringbuffer_Stub_generic_status {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_generic_status(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) : Store_Manager_Ringbuffer_Stub_generic_status ( storeCount, ringbufferSize, poolSize )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_generic_status()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_Manager_Ringbuffer_generic_status_extended

} // namespace DataHandling
} // namespace ConnectedVision

#include "stubs/Store_Manager_Ringbuffer_generic_status_Default.h"

#endif // Store_Manager_Ringbuffer_generic_status_def