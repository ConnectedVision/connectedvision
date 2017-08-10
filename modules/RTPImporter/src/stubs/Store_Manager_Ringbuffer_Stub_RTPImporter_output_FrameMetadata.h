// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata_def
#define Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_RTPImporter_output_FrameMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace RTPImporter {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata
 *
 * module: RTP stream receiver module
 * description: frame meta data
 */
class Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_RTPImporter_output_FrameMetadata> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata(const Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata & operator = (const Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata_def