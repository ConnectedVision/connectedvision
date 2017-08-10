// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata_def
#define Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_DirectoryIterator_output_FileMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_DirectoryIterator_output_FileMetadata
 *
 * module: Directory Iterator
 * description: The file metadata.
 */
class Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_DirectoryIterator_output_FileMetadata> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata(const Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata & operator = (const Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_DirectoryIterator_output_FileMetadata_def