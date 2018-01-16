/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "ThumbnailGeneratorModuleFactory.h"
#include "ThumbnailGeneratorModule.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

ConnectedVision::shared_ptr<IModule> ThumbnailGeneratorModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<IModule> moduleInstance = ConnectedVision::make_shared<ThumbnailGeneratorModule>();
	if ( !moduleInstance ) 
		throw std::runtime_error("ThumbnailGeneratorModuleFactory: error creating instance for module: Thumbnail Generator");

	return moduleInstance;
}

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision