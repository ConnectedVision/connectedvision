/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "InputPin_RAWYUV420.h"

namespace ConnectedVision {

InputPin_RAWYUV420::InputPin_RAWYUV420(IModuleEnvironment *env, const pinID_t inputPinID)  
	: ConnectedVisionInputPinData(env, inputPinID)
{
}

InputPin_RAWYUV420::~InputPin_RAWYUV420(void)
{
}

} // namespace ConnectedVision