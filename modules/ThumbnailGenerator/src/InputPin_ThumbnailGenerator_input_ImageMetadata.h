/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// InputPin_ThumbnailGenerator_input_ImageMetadata.h
// This file implements the InputPin interface.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef InputPin_ThumbnailGenerator_input_ImageMetadata_def
#define InputPin_ThumbnailGenerator_input_ImageMetadata_def

#include "stubs/InputPin_Stub_ThumbnailGenerator_input_ImageMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

// if you want to extend the auto-generated class, enable the line below
//#define InputPin_ThumbnailGenerator_input_ImageMetadata_extended

#ifdef InputPin_ThumbnailGenerator_input_ImageMetadata_extended
/**
 * ThumbnailGenerator_input_ImageMetadata
 *
 * module: Thumbnail Generator
 * description: image metadata
 */
class InputPin_ThumbnailGenerator_input_ImageMetadata : public InputPin_Stub_ThumbnailGenerator_input_ImageMetadata {
public:
	InputPin_ThumbnailGenerator_input_ImageMetadata(IModuleEnvironment *env, const pinID_t inputPinID) : InputPin_Stub_ThumbnailGenerator_input_ImageMetadata(env, inputPinID) {};

};
#endif // InputPin_ThumbnailGenerator_input_ImageMetadata_extended

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/InputPin_ThumbnailGenerator_input_ImageMetadata_Default.h"

#endif // InputPin_ThumbnailGenerator_input_ImageMetadata_def