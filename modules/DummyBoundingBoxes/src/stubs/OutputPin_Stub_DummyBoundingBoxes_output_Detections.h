// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/OutputPin_Stub_DummyBoundingBoxes_output_Detections.h
// NEVER TOUCH this file!

#include <IStore.h>
#include <IStoreCV.h>
#include <IConnectedVisionModule.h>
#include <ConnectedVisionOutputPin.h>
#include <Module/Control/Class_generic_status.h>

#include "../Class_DummyBoundingBoxes_output_Detections.h"

#ifndef OutputPin_Stub_DummyBoundingBoxes_output_Detections_def
#define OutputPin_Stub_DummyBoundingBoxes_output_Detections_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for DummyBoundingBoxes_output_Detections
 *
 * module: DummyBoundingBoxes
 * description: bounding box
 */
class OutputPin_Stub_DummyBoundingBoxes_output_Detections : public ConnectedVisionOutputPin< boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections> > {
public:
	static const pinID_t PinID() { return "Detections"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	OutputPin_Stub_DummyBoundingBoxes_output_Detections(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections> > > dataStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections> >( dataStore) {};
	
	/// deprecated constructor
	OutputPin_Stub_DummyBoundingBoxes_output_Detections(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections> > > dataStore, boost::shared_ptr< Store::IStore< boost::shared_ptr<Class_generic_status> > > statusStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections> >( dataStore) {};

};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_Stub_DummyBoundingBoxes_output_Detections_def