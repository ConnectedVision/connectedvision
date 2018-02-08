/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "FileImporterModuleFactory.h"
#include "FileImporterModule.h"

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

ConnectedVision::shared_ptr<IModule> FileImporterModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<IModule> moduleInstance = boost::dynamic_pointer_cast<IModule>(ConnectedVision::make_shared<FileImporterModule>());
	if ( !moduleInstance ) 
		throw std::runtime_error("FileImporterModuleFactory: error creating instance for module: FileImporter");

	return moduleInstance;
}

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision