/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef SyntheticVideoModuleFactory_def
#define SyntheticVideoModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

/**
*	module factory for: SyntheticVideo
*	This module produces synthetic video frames as well as synthetic video meta data. It has 2 metadata output pins and 3 raw frame output pins and a png output pin.
*/
class SyntheticVideoModuleFactory
{
public:
	/**
	* factory for SyntheticVideo
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> createModule();
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#endif // SyntheticVideoModuleFactory_def