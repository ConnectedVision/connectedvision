// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/InputPin_Stub_ThumbnailGenerator_input_BoundingBox.h
// NEVER TOUCH this file!

#include <ConnectedVisionInputPin.h>

#include "../Class_ThumbnailGenerator_input_BoundingBox.h"

#ifndef InputPin_Stub_ThumbnailGenerator_input_BoundingBox_def
#define InputPin_Stub_ThumbnailGenerator_input_BoundingBox_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for ThumbnailGenerator_input_BoundingBox
 *
 * module: Thumbnail Generator
 * description: rectangular region which is used for the cropping or for overlaying bounding boxes
 */
class InputPin_Stub_ThumbnailGenerator_input_BoundingBox : public ConnectedVisionInputPinData<Class_ThumbnailGenerator_input_BoundingBox> {
public:
	static const pinID_t PinID() { return "BoundingBox"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	InputPin_Stub_ThumbnailGenerator_input_BoundingBox(IModuleEnvironment *env, const pinID_t inputPinID) : ConnectedVisionInputPinData<Class_ThumbnailGenerator_input_BoundingBox>(env, inputPinID) {};

};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // InputPin_Stub_ThumbnailGenerator_input_BoundingBox_def