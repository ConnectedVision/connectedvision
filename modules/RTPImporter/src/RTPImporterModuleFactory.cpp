/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "RTPImporterModuleFactory.h"
#include "RTPImporterModule.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

ConnectedVision::shared_ptr<IConnectedVisionModule> RTPImporterModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new RTPImporterModule() );
	if ( !moduleInstance ) 
		throw std::runtime_error("RTPImporterModuleFactory: error creating instance for module: RTP stream receiver module");

	return moduleInstance;
}

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision