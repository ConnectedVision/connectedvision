/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DummyBoundingBoxesModuleFactory_def
#define DummyBoundingBoxesModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
*	module factory for: DummyBoundingBoxes
*	This module generates dummy bounding boxes.
*/
class DummyBoundingBoxesModuleFactory
{
public:
	/**
	* factory for DummyBoundingBoxes
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::Module::IModule> createModule();
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // DummyBoundingBoxesModuleFactory_def