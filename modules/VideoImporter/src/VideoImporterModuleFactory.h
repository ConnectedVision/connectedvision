/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef VideoImporterModuleFactory_def
#define VideoImporterModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

/**
*	module factory for: VideoImporter
*	This module imports video frames as well as video meta data from .avi files. It has 2 metadata output pins and 3 raw frame output pins and a png output pin.
*/
class VideoImporterModuleFactory
{
public:
	/**
	* factory for VideoImporter
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> createModule();
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#endif // VideoImporterModuleFactory_def