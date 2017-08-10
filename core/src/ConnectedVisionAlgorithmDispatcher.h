/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>
#include <sqlite3.h>

#include <IModuleEnvironment.h>
#include <IConnectedVisionModule.h>

#include "Module/Control/Class_generic_config.h"

namespace ConnectedVision
{

class ConnectedVisionModule;

class IConnectedVisionAlgorithmWorker
{
public:
	virtual ~IConnectedVisionAlgorithmWorker() {};

	virtual id_t getID() = 0;

	virtual void start() = 0;
	virtual void stop() = 0;
	virtual bool isRunning()= 0;

	virtual ConnectedVisionModule* getModule() = 0; 
};

class IConnectedVisionWorkerFactory
{
public:
	virtual ~IConnectedVisionWorkerFactory() {};

	virtual ConnectedVisionModule* getModule() = 0; 

	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config) = 0;
};

class ConnectedVisionAlgorithmDispatcher
{
public:
	ConnectedVisionAlgorithmDispatcher(IModuleEnvironment *env, IConnectedVisionWorkerFactory *workerFactory, IConnectedVisionModule* module);
    ~ConnectedVisionAlgorithmDispatcher();
	IConnectedVisionModule* getModule(); 

	void start( boost::shared_ptr<const Class_generic_config> config);
	void stop( boost::shared_ptr<const Class_generic_config> config);
	void reset( boost::shared_ptr<const Class_generic_config> config);
	void recover( boost::shared_ptr<const Class_generic_config> config);
	
	std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> > getRunningWorkers();
	std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> > getWaitingWorkers();

	void cleanup();

///todo	std::string imageByIndex(const id_t configID, const int64_t index);

protected:

	IModuleEnvironment *env;
	IConnectedVisionWorkerFactory *workerFactory;
	IConnectedVisionModule* module; 
	
	boost::mutex mutexCriticalSectionWorkerCreation; ///< mutex to protect creation of worker threads - used to prevent parallel create requests to create more than one thread and also preventing mutexWorkerList to be locked longer than necessary

	std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> > workers;
	boost::shared_mutex mutexWorkerList; ///< mutex to protect read/write operations on the list of workers (a single writer/multiple reader paradigm is used)

	std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> > queue;

};

} // namespace ConnectedVision