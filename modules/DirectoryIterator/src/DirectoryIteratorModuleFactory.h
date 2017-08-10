/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DirectoryIteratorModuleFactory_def
#define DirectoryIteratorModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
*	module factory for: Directory Iterator
*	Iterates a directory and returns the files with the extensions specified in the config.
*/
class DirectoryIteratorModuleFactory
{
public:
	/**
	* factory for Directory Iterator
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> createModule();
};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // DirectoryIteratorModuleFactory_def