/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "DummyBoundingBoxesModuleFactory.h"
#include "DummyBoundingBoxesModule.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

ConnectedVision::shared_ptr<IModule> DummyBoundingBoxesModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<IModule> moduleInstance = ConnectedVision::make_shared<DummyBoundingBoxesModule>();
	if ( !moduleInstance ) 
		throw std::runtime_error("DummyBoundingBoxesModuleFactory: error creating instance for module: DummyBoundingBoxes");

	return moduleInstance;
}

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision