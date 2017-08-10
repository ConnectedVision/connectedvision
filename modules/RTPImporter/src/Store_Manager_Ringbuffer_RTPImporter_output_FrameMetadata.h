/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata.h
// This file implements the Store_Manager interface for a ringbuffer
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_def
#define Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_def

#include "stubs/Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_extended

#ifdef Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_extended
/**
 * Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata
 *
 * module: RTP stream receiver module
 * description: frame meta data
 */
class Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata : public Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) : Store_Manager_Ringbuffer_Stub_RTPImporter_output_FrameMetadata ( storeCount, ringbufferSize, poolSize )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_extended

} // namespace DataHandling
} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_Default.h"

#endif // Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata_def