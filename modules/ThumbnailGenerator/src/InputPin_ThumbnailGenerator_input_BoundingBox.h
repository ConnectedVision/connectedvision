/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// InputPin_ThumbnailGenerator_input_BoundingBox.h
// This file implements the InputPin interface.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef InputPin_ThumbnailGenerator_input_BoundingBox_def
#define InputPin_ThumbnailGenerator_input_BoundingBox_def

#include "stubs/InputPin_Stub_ThumbnailGenerator_input_BoundingBox.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

// if you want to extend the auto-generated class, enable the line below
//#define InputPin_ThumbnailGenerator_input_BoundingBox_extended

#ifdef InputPin_ThumbnailGenerator_input_BoundingBox_extended
/**
 * ThumbnailGenerator_input_BoundingBox
 *
 * module: Thumbnail Generator
 * description: rectangular region which is used for the cropping or for overlaying bounding boxes
 */
class InputPin_ThumbnailGenerator_input_BoundingBox : public InputPin_Stub_ThumbnailGenerator_input_BoundingBox {
public:
	InputPin_ThumbnailGenerator_input_BoundingBox(IModuleEnvironment *env, const pinID_t inputPinID) : InputPin_Stub_ThumbnailGenerator_input_BoundingBox(env, inputPinID) {};

};
#endif // InputPin_ThumbnailGenerator_input_BoundingBox_extended

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/InputPin_ThumbnailGenerator_input_BoundingBox_Default.h"

#endif // InputPin_ThumbnailGenerator_input_BoundingBox_def