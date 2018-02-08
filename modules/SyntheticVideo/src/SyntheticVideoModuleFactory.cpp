/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "SyntheticVideoModuleFactory.h"
#include "SyntheticVideoModule.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

ConnectedVision::shared_ptr<IModule> SyntheticVideoModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<IModule> moduleInstance = boost::dynamic_pointer_cast<IModule>(ConnectedVision::make_shared<SyntheticVideoModule>());
	if ( !moduleInstance ) 
		throw std::runtime_error("SyntheticVideoModuleFactory: error creating instance for module: SyntheticVideo");

	return moduleInstance;
}

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision