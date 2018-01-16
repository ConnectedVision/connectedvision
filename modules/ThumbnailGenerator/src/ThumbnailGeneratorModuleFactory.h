/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ThumbnailGeneratorModuleFactory_def
#define ThumbnailGeneratorModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
*	module factory for: Thumbnail Generator
*	This module provides image manipulation functions. 1.: It can crop the input image according to the defined rectangular region. 2.: It can overlay the input image with bounding boxes.
*/
class ThumbnailGeneratorModuleFactory
{
public:
	/**
	* factory for Thumbnail Generator
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::Module::IModule> createModule();
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // ThumbnailGeneratorModuleFactory_def