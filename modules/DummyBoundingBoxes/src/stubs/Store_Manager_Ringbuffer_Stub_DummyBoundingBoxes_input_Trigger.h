// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger_def
#define Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_DummyBoundingBoxes_input_Trigger.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_DummyBoundingBoxes_input_Trigger
 *
 * module: DummyBoundingBoxes
 * description: Trigger pulse used as signal for the generation of a bounding box.
 */
class Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_DummyBoundingBoxes_input_Trigger> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger(const Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger & operator = (const Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_input_Trigger_def