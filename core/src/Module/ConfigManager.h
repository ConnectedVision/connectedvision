/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConfigManager_def
#define ConfigManager_def

#include <unordered_map>

#include <IConnectedVisionModule.h>

#include "WorkerThread.h"

namespace ConnectedVision {
namespace Module {

class ConfigManager
{
public:

	/**
	* constructor
	*/
	ConfigManager(
		const ConnectedVision::shared_ptr<const Class_generic_config> config	///< [in] config for worker
	);

	/**
	* virtual destructor
	*/
    virtual ~ConfigManager();

	/**
	* start the worker for a given config
	*
	* If there is already an existing worker, this function does nothing.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> start()
	{ throw ConnectedVision::runtime_error("ConfigManager::start() not implemented"); }

	/**
	* stop the worker of a specific config chain,
	* if the config is running, otherwise it does nothing.
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> stop()
	{ throw ConnectedVision::runtime_error("ConfigManager::stop() not implemented"); }

	/**
	* stop the worker of a specific config chain,
	* if the config is running, otherwise it does nothing.
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> stopThis()
	{ throw ConnectedVision::runtime_error("ConfigManager::stopThis() not implemented"); }

	/**
	* resets the given config
	*
	* If the config is running, it is stopped in advance.
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> reset()
	{ throw ConnectedVision::runtime_error("ConfigManager::reset() not implemented"); }

	/**
	* resets the given config
	*
	* If the config is running, it is stopped in advance.
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> resetThis()
	{ throw ConnectedVision::runtime_error("ConfigManager::resetThis() not implemented"); }

	/**
	* recover the given config
	*
	* If the config is not in error mode, it does nothing.
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> recover()
	{ throw ConnectedVision::runtime_error("ConfigManager::recover() not implemented"); }

protected:
	typedef boost::unique_lock<boost::mutex> Lock;

	
	// configuration
	ConnectedVision::shared_ptr<Class_generic_config> config;

	/**
	* command queue processing (thread function)
	* handle commands asynchronously 
	*
	* - waits for new commands
	* - execute next command
	*/
	void commandQueueProcessing();
	// command queue processing thread
	boost::thread commandQueueProcessingThread;

};

}} // namespace scope

#endif // ConfigManager_def