/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef InputPin_PNG_def
#define InputPin_PNG_def

#include <string>

#include <ConnectedVisionInputPin.h>
#include <IConnectedVisionModule.h>

#include <Module/Control/Class_RawData.h>

namespace ConnectedVision
{

/**
 *
 */
class InputPin_PNG : public ConnectedVisionInputPinData<Class_RawData>
{
public:
	static const pinID_t PinID() { return "PNG-Image"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };

public:
	InputPin_PNG(IModuleEnvironment *env, const pinID_t inputPinID);
	virtual ~InputPin_PNG();
};

} // namespace ConnectedVision

#endif // InputPin_PNG_def
