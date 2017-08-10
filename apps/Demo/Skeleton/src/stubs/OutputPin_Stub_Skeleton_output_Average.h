// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/OutputPin_Stub_Skeleton_output_Average.h
// NEVER TOUCH this file!

#include <IStore.h>
#include <IStoreCV.h>
#include <IConnectedVisionModule.h>
#include <ConnectedVisionOutputPin.h>
#include <Module/Control/Class_generic_status.h>

#include "../Class_Skeleton_output_Average.h"

#ifndef OutputPin_Stub_Skeleton_output_Average_def
#define OutputPin_Stub_Skeleton_output_Average_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {

/**
 * stub class for Skeleton_output_Average
 *
 * module: Skeleton Module
 * description: This is a completely senseless output pin providing the average color of the area in the bounding box.
 */
class OutputPin_Stub_Skeleton_output_Average : public ConnectedVisionOutputPin< boost::shared_ptr<Class_Skeleton_output_Average> > {
public:
	static const pinID_t PinID() { return "Average"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	OutputPin_Stub_Skeleton_output_Average(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_Skeleton_output_Average> > > dataStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_Skeleton_output_Average> >( dataStore) {};
	
	/// deprecated constructor
	OutputPin_Stub_Skeleton_output_Average(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_Skeleton_output_Average> > > dataStore, boost::shared_ptr< Store::IStore< boost::shared_ptr<Class_generic_status> > > statusStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<Class_Skeleton_output_Average> >( dataStore) {};

};

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_Stub_Skeleton_output_Average_def