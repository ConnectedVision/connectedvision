// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/InputPin_Stub_DummyBoundingBoxes_input_Trigger.h
// NEVER TOUCH this file!

#include <ConnectedVisionInputPin.h>

#include "../Class_DummyBoundingBoxes_input_Trigger.h"

#ifndef InputPin_Stub_DummyBoundingBoxes_input_Trigger_def
#define InputPin_Stub_DummyBoundingBoxes_input_Trigger_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for DummyBoundingBoxes_input_Trigger
 *
 * module: DummyBoundingBoxes
 * description: Trigger pulse used as signal for the generation of a bounding box.
 */
class InputPin_Stub_DummyBoundingBoxes_input_Trigger : public ConnectedVisionInputPinData<Class_DummyBoundingBoxes_input_Trigger> {
public:
	static const pinID_t PinID() { return "Trigger"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	InputPin_Stub_DummyBoundingBoxes_input_Trigger(IModuleEnvironment *env, const pinID_t inputPinID) : ConnectedVisionInputPinData<Class_DummyBoundingBoxes_input_Trigger>(env, inputPinID) {};

};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // InputPin_Stub_DummyBoundingBoxes_input_Trigger_def