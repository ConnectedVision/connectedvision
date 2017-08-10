/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>

#include <ConnectedVisionInputPin.h>
#include <IConnectedVisionModule.h>

#include <Module/Control/Class_RawData.h>

namespace ConnectedVision
{

/**
 *
 */
class InputPin_RAWYUV420 : public ConnectedVisionInputPinData<Class_RawData>
{
public:
	static const pinID_t PinID() { return "RAWYUV420-Image"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };

public:
	InputPin_RAWYUV420(IModuleEnvironment *env, const pinID_t inputPinID);
	virtual ~InputPin_RAWYUV420();
};

} // namespace ConnectedVision