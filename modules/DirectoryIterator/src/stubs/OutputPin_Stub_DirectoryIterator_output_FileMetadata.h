// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/OutputPin_Stub_DirectoryIterator_output_FileMetadata.h
// NEVER TOUCH this file!

#include <IStore.h>
#include <IStoreCV.h>
#include <IConnectedVisionModule.h>
#include <ConnectedVisionOutputPin.h>
#include <Module/Control/Class_generic_status.h>

#include "../Class_DirectoryIterator_output_FileMetadata.h"

#ifndef OutputPin_Stub_DirectoryIterator_output_FileMetadata_def
#define OutputPin_Stub_DirectoryIterator_output_FileMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
 * stub class for DirectoryIterator_output_FileMetadata
 *
 * module: Directory Iterator
 * description: The file metadata.
 */
class OutputPin_Stub_DirectoryIterator_output_FileMetadata : public ConnectedVisionOutputPin< boost::shared_ptr<Class_DirectoryIterator_output_FileMetadata> > {
public:
	static const pinID_t PinID() { return "FileMetadata"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	OutputPin_Stub_DirectoryIterator_output_FileMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DirectoryIterator_output_FileMetadata> > > dataStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_DirectoryIterator_output_FileMetadata> >( dataStore) {};
	
	/// deprecated constructor
	OutputPin_Stub_DirectoryIterator_output_FileMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DirectoryIterator_output_FileMetadata> > > dataStore, boost::shared_ptr< Store::IStore< boost::shared_ptr<Class_generic_status> > > statusStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_DirectoryIterator_output_FileMetadata> >( dataStore) {};

};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_Stub_DirectoryIterator_output_FileMetadata_def