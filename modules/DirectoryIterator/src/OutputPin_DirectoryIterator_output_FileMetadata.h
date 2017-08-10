/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// OutputPin_DirectoryIterator_output_FileMetadata.h
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef OutputPin_DirectoryIterator_output_FileMetadata_def
#define OutputPin_DirectoryIterator_output_FileMetadata_def

#include "stubs/OutputPin_Stub_DirectoryIterator_output_FileMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

// if you want to extend the auto-generated class, enable the line below
//#define OutputPin_DirectoryIterator_output_FileMetadata_extended

#ifdef OutputPin_DirectoryIterator_output_FileMetadata_extended
/**
 * DirectoryIterator_output_FileMetadata
 *
 * module: Directory Iterator
 * description: The file metadata.
 */
class OutputPin_DirectoryIterator_output_FileMetadata : public OutputPin_Stub_DirectoryIterator_output_FileMetadata {
public:
	OutputPin_DirectoryIterator_output_FileMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DirectoryIterator_output_FileMetadata> > > dataStore) :
		OutputPin_Stub_DirectoryIterator_output_FileMetadata(dataStore) {};
	virtual ~OutputPin_DirectoryIterator_output_FileMetadata() {}
};
#endif // OutputPin_DirectoryIterator_output_FileMetadata_extended

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/OutputPin_DirectoryIterator_output_FileMetadata_Default.h"

#endif // OutputPin_DirectoryIterator_output_FileMetadata_def