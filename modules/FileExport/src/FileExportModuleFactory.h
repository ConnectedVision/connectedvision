/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef FileExportModuleFactory_def
#define FileExportModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace FileExport {

/**
*	module factory for: FileExport
*	exports data to file(s)
*/
class FileExportModuleFactory
{
public:
	/**
	* factory for FileExport
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::Module::IModule> createModule();
};

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#endif // FileExportModuleFactory_def