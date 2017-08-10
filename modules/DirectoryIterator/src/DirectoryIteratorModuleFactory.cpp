/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "DirectoryIteratorModuleFactory.h"
#include "DirectoryIteratorModule.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

ConnectedVision::shared_ptr<IConnectedVisionModule> DirectoryIteratorModuleFactory::createModule()
{
	ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> moduleInstance( new DirectoryIteratorModule() );
	if ( !moduleInstance ) 
		throw std::runtime_error("DirectoryIteratorModuleFactory: error creating instance for module: Directory Iterator");

	return moduleInstance;
}

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision