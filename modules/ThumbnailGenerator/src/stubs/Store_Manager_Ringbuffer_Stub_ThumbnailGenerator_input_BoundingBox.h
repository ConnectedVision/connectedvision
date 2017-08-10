// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox_def
#define Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_ThumbnailGenerator_input_BoundingBox.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox
 *
 * module: Thumbnail Generator
 * description: rectangular region which is used for the cropping or for overlaying bounding boxes
 */
class Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_ThumbnailGenerator_input_BoundingBox> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox(const Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox & operator = (const Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox_def