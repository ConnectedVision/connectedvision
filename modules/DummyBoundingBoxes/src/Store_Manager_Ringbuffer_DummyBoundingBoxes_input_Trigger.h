// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger.h
// This file implements the Store_Manager interface for a ringbuffer
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_def
#define Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_def

#include "stubs/Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_extended

#ifdef Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_extended
/**
 * Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger
 *
 * module: DummyBoundingBoxes
 * description: Trigger pulse used as signal for the generation of a bounding box.
 */
class Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger : public Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) : Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger ( storeCount, ringbufferSize, poolSize )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_extended

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_Default.h"

#endif // Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger_def