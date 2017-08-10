// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/OutputPin_Stub_VideoImporter_output_FrameMetadata.h
// NEVER TOUCH this file!

#include <IStore.h>
#include <IStoreCV.h>
#include <IConnectedVisionModule.h>
#include <ConnectedVisionOutputPin.h>
#include <Module/Control/Class_generic_status.h>

#include "../Class_VideoImporter_output_FrameMetadata.h"

#ifndef OutputPin_Stub_VideoImporter_output_FrameMetadata_def
#define OutputPin_Stub_VideoImporter_output_FrameMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

/**
 * stub class for VideoImporter_output_FrameMetadata
 *
 * module: VideoImporter
 * description: frame meta data
 */
class OutputPin_Stub_VideoImporter_output_FrameMetadata : public ConnectedVisionOutputPin< boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> > {
public:
	static const pinID_t PinID() { return "FrameMetadata"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	OutputPin_Stub_VideoImporter_output_FrameMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> > > dataStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> >( dataStore) {};
	
	/// deprecated constructor
	OutputPin_Stub_VideoImporter_output_FrameMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> > > dataStore, boost::shared_ptr< Store::IStore< boost::shared_ptr<Class_generic_status> > > statusStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> >( dataStore) {};

};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_Stub_VideoImporter_output_FrameMetadata_def