// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections_def
#define Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_Skeleton_input_Detections.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace test {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_Skeleton_input_Detections
 *
 * module: Skeleton Module
 * description: bounding box
 */
class Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_Skeleton_input_Detections> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections(const Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections & operator = (const Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace test
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_Skeleton_input_Detections_def