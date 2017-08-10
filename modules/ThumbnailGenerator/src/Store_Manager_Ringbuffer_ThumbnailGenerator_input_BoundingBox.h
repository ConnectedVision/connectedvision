/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox.h
// This file implements the Store_Manager interface for a ringbuffer
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_def
#define Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_def

#include "stubs/Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_extended

#ifdef Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_extended
/**
 * Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox
 *
 * module: Thumbnail Generator
 * description: rectangular region which is used for the cropping or for overlaying bounding boxes
 */
class Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox : public Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) : Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox ( storeCount, ringbufferSize, poolSize )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_extended

} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_Default.h"

#endif // Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_def