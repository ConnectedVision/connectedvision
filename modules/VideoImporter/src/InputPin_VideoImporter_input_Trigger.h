/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// InputPin_VideoImporter_input_Trigger.h
// This file implements the InputPin interface.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef InputPin_VideoImporter_input_Trigger_def
#define InputPin_VideoImporter_input_Trigger_def

#include "stubs/InputPin_Stub_VideoImporter_input_Trigger.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

// if you want to extend the auto-generated class, enable the line below
//#define InputPin_VideoImporter_input_Trigger_extended

#ifdef InputPin_VideoImporter_input_Trigger_extended
/**
 * VideoImporter_input_Trigger
 *
 * module: VideoImporter
 * description: Trigger pulse used as signal for the generation of a bounding box.
 */
class InputPin_VideoImporter_input_Trigger : public InputPin_Stub_VideoImporter_input_Trigger {
public:
	InputPin_VideoImporter_input_Trigger(IModuleEnvironment *env, const pinID_t inputPinID) : InputPin_Stub_VideoImporter_input_Trigger(env, inputPinID) {};

};
#endif // InputPin_VideoImporter_input_Trigger_extended

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/InputPin_VideoImporter_input_Trigger_Default.h"

#endif // InputPin_VideoImporter_input_Trigger_def