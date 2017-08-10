/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "ConfigManager.h"

namespace ConnectedVision {
namespace Module {


ConfigManager::ConfigManager(		
		const ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for worker
)
{
}

ConfigManager::~ConfigManager()
{
}

void ConfigManager::commandQueueProcessing()
{
	try
	{
		// TODO wait for next command
	}
	catch (boost::thread_interrupted&)
	{
		// thread was interrupted, this is expected
		// -> exit thread function
	}
	catch (std::exception&)
	{
		// an unhandled exception reached this point
		// TODO handle async error
	}
}

}} // namespace scope
