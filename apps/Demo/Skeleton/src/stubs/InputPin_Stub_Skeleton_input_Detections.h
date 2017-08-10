// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/InputPin_Stub_Skeleton_input_Detections.h
// NEVER TOUCH this file!

#include <ConnectedVisionInputPin.h>

#include "../Class_Skeleton_input_Detections.h"

#ifndef InputPin_Stub_Skeleton_input_Detections_def
#define InputPin_Stub_Skeleton_input_Detections_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {

/**
 * stub class for Skeleton_input_Detections
 *
 * module: Skeleton Module
 * description: bounding box
 */
class InputPin_Stub_Skeleton_input_Detections : public ConnectedVisionInputPinData<Class_Skeleton_input_Detections> {
public:
	static const pinID_t PinID() { return "Detections"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	InputPin_Stub_Skeleton_input_Detections(IModuleEnvironment *env, const pinID_t inputPinID) : ConnectedVisionInputPinData<Class_Skeleton_input_Detections>(env, inputPinID) {};

};

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // InputPin_Stub_Skeleton_input_Detections_def