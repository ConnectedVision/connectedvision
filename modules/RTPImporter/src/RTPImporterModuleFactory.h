/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef RTPImporterModuleFactory_def
#define RTPImporterModuleFactory_def

#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

/**
*	module factory for: RTP stream receiver module
*	
*/
class RTPImporterModuleFactory
{
public:
	/**
	* factory for RTP stream receiver module
	*/
	static ConnectedVision::shared_ptr<ConnectedVision::IConnectedVisionModule> createModule();
};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#endif // RTPImporterModuleFactory_def