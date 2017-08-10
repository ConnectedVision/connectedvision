/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "VideoImporterModuleFactory.h"
#include "VideoImporterModule.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

ConnectedVision::shared_ptr<IConnectedVisionModule> VideoImporterModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new VideoImporterModule() );
	if ( !moduleInstance ) 
		throw std::runtime_error("VideoImporterModuleFactory: error creating instance for module: VideoImporter");

	return moduleInstance;
}

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision