// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// InputPin_Skeleton_input_Detections.h
// This file implements the InputPin interface.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef InputPin_Skeleton_input_Detections_def
#define InputPin_Skeleton_input_Detections_def

#include "stubs/InputPin_Stub_Skeleton_input_Detections.h"

namespace ConnectedVision {
namespace test {

// if you want to extend the auto-generated class, enable the line below
//#define InputPin_Skeleton_input_Detections_extended

#ifdef InputPin_Skeleton_input_Detections_extended
/**
 * Skeleton_input_Detections
 *
 * module: Skeleton Module
 * description: bounding box
 */
class InputPin_Skeleton_input_Detections : public InputPin_Stub_Skeleton_input_Detections {
public:
	InputPin_Skeleton_input_Detections(IModuleEnvironment *env, const pinID_t inputPinID) : InputPin_Stub_Skeleton_input_Detections(env, inputPinID) {};

};
#endif // InputPin_Skeleton_input_Detections_extended

} // namespace test
} // namespace ConnectedVision

#include "stubs/InputPin_Skeleton_input_Detections_Default.h"

#endif // InputPin_Skeleton_input_Detections_def