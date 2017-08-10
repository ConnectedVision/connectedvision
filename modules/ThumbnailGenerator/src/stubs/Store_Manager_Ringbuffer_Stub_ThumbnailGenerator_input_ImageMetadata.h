// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata_def
#define Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_ThumbnailGenerator_input_ImageMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_ThumbnailGenerator_input_ImageMetadata
 *
 * module: Thumbnail Generator
 * description: image metadata
 */
class Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_ThumbnailGenerator_input_ImageMetadata> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata(const Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata & operator = (const Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata_def