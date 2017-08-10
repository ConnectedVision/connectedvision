/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "FileImporterModuleFactory.h"
#include "FileImporterModule.h"

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

ConnectedVision::shared_ptr<IConnectedVisionModule> FileImporterModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new FileImporterModule() );
	if ( !moduleInstance ) 
		throw std::runtime_error("FileImporterModuleFactory: error creating instance for module: FileImporter");

	return moduleInstance;
}

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision