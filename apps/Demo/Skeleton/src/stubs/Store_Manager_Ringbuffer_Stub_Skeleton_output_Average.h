// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_Skeleton_output_Average_def
#define Store_Manager_Ringbuffer_Stub_Skeleton_output_Average_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_Skeleton_output_Average.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_Skeleton_output_Average
 *
 * module: Skeleton Module
 * description: This is a completely senseless output pin providing the average color of the area in the bounding box.
 */
class Store_Manager_Ringbuffer_Stub_Skeleton_output_Average : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_Skeleton_output_Average> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_Skeleton_output_Average(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_Skeleton_output_Average();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_Skeleton_output_Average(const Store_Manager_Ringbuffer_Stub_Skeleton_output_Average &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_Skeleton_output_Average & operator = (const Store_Manager_Ringbuffer_Stub_Skeleton_output_Average &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_Skeleton_output_Average_def