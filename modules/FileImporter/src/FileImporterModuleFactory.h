/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef FileImporterModuleFactory_def
#define FileImporterModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

/**
*	module factory for: FileImporter
*	sends a static file
*/
class FileImporterModuleFactory
{
public:
	/**
	* factory for FileImporter
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::Module::IModule> createModule();
};

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision

#endif // FileImporterModuleFactory_def