// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/InputPin_Stub_ThumbnailGenerator_input_ImageMetadata.h
// NEVER TOUCH this file!

#include <ConnectedVisionInputPin.h>

#include "../Class_ThumbnailGenerator_input_ImageMetadata.h"

#ifndef InputPin_Stub_ThumbnailGenerator_input_ImageMetadata_def
#define InputPin_Stub_ThumbnailGenerator_input_ImageMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for ThumbnailGenerator_input_ImageMetadata
 *
 * module: Thumbnail Generator
 * description: image metadata
 */
class InputPin_Stub_ThumbnailGenerator_input_ImageMetadata : public ConnectedVisionInputPinData<Class_ThumbnailGenerator_input_ImageMetadata> {
public:
	static const pinID_t PinID() { return "ImageMetadata"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	InputPin_Stub_ThumbnailGenerator_input_ImageMetadata(IModuleEnvironment *env, const pinID_t inputPinID) : ConnectedVisionInputPinData<Class_ThumbnailGenerator_input_ImageMetadata>(env, inputPinID) {};

};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // InputPin_Stub_ThumbnailGenerator_input_ImageMetadata_def