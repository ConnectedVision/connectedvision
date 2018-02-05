/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "VideoImporterModuleFactory.h"
#include "VideoImporterModule.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

ConnectedVision::shared_ptr<IModule> VideoImporterModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<IModule> moduleInstance = ConnectedVision::make_shared<VideoImporterModule>();
	if ( !moduleInstance ) 
		throw std::runtime_error("VideoImporterModuleFactory: error creating instance for module: VideoImporter");

	return moduleInstance;
}

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision