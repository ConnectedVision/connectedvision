/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef TestHelper_Module_code
#define TestHelper_Module_code

#include <boost/atomic.hpp>
#include "IModuleEnvironment.h"
#include "IConnectedVisionModule.h"
#include "ConnectedVision_Exceptions.h"
#include "TestHelper_Threads.hpp"

namespace ConnectedVision {
namespace Module {


/*
 * mock-up implementation of module environment
 */
class ModuleEnvironment_Mockup : public IModuleEnvironment {
public:
	ModuleEnvironment_Mockup() {}
	virtual ~ModuleEnvironment_Mockup() {}

	////////////////////////////////////////////////////////////
	// module functions

	/**
	* register module
	*/
	virtual void registerModule( 
		boost::shared_ptr<IConnectedVisionModule> module ///< module instance
	) {}

	/**
	* get module by module ID
	*
	* @return module instance
	*/
	virtual boost::shared_ptr<IConnectedVisionModule> getModule(
		std::string moduleID	///< module ID
	) const
	{ return boost::shared_ptr<IConnectedVisionModule>(); }


	/**
	* get module by module ID
	*
	* @return current module URL
	*/
	virtual std::string getModuleURL(
		std::string serverAddress,	///< server base URL including protocol and port, e.g.: "http://example.com:2020" (optional as "")
		std::string moduleID		///< module ID
	) const
	{ return std::string(); }

	////////////////////////////////////////////////////////////
	// server functions

	/**
	* get root data path
	*
	* @return path to server root data
	*/
	virtual std::string getDataPath() const
	{ return std::string("./data"); }

	/**
	* get server status
	*
	* @return status
	*/
	virtual Class_HostStatus getHostStatus()
	{ return Class_HostStatus(); }


};

namespace Worker_Mockup_spy {
static 	boost::atomic<uint64_t> constructorThreadID;
static 	boost::atomic<uint64_t> runThreadID;
};
class Worker_Mockup : public IWorker
{
public:
	/** constructor */
	Worker_Mockup(
		IModule* module,	///< [in] associated module
		IWorkerController &workerThread,	///< [in] reference to controller
		uint64_t runtime,	///< [in] runtime of worker.run() in milliseconds
		bool cooperative	///< [in] cooperative worker
	) : pModule(module), runtime(runtime), workerThread(workerThread), cooperative(cooperative)
	{
		Worker_Mockup_spy::constructorThreadID = getCurrentThread().id;
		Worker_Mockup_spy::runThreadID = 0;
	}

	/** destructor */
	virtual ~Worker_Mockup() {}

	/**
	* actual worker function
	*/
	virtual void run()
	{ 
		const int64_t iterationTime = 10;
		Worker_Mockup_spy::runThreadID = getCurrentThread().id;

		int64_t iterations = runtime;
		for ( int64_t i = 0; i < iterations/iterationTime; i++ )
		{
			// simulate some work
			boost::this_thread::sleep_for(boost::chrono::milliseconds(iterationTime));

			// test exit condition
			if ( this->cooperative )
			{
				if ( !this->workerThread.nextIterationStep() )
					return;
			}
		}

		//finished
		return;
	}


	/**
	* clear computed data in store
	*/
	virtual void clearResults()
	{}

	/**
	* get corresponding module
	*
	* @return module 
	*/
	virtual IModule* getModule()
	{ return this->pModule; }

protected:
	IWorkerController &workerThread;
	const bool cooperative;
	uint64_t runtime;
	IModule* pModule;
};

class WorkerFactory_Mockup : public IWorkerFactory
{
public:
	/** constructor */
	WorkerFactory_Mockup(
		IModule* module,		///< [in] associated module
		uint64_t runtime = 100,	///< [in] runtime of worker.run() in milliseconds
		bool cooperative = true	///< [in] cooperative worker
	) : pModule(module), runtime(runtime), cooperative(cooperative), numberOfCreatedWorkers(0)
	{
	}
	/** destructor */
	virtual ~WorkerFactory_Mockup() {}

	/**
	* get corresponding module
	*
	* @return module 
	*/
	virtual IModule* getModule() const
	{ return this->pModule; }

	/**
	* create a new worker instance for a given config
	*
	* @return worker instance
	*/
	virtual std::unique_ptr<IWorker> createWorker(
		IWorkerController &controller,									///< reference to controller
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
	)
	{
		std::unique_ptr<Worker_Mockup> worker( new Worker_Mockup( this->pModule, controller, runtime, this->cooperative ) );
		numberOfCreatedWorkers++;
		return std::move(worker);
	}

public:
	bool cooperative;
	IModule* pModule;
	uint64_t runtime;
	boost::atomic<uint64_t> numberOfCreatedWorkers;
};

class Module_Mockup : public IModule
{
public:
	Module_Mockup() : ready(false), deleteAllDataCallCount(0), processConfigRecoverCallCount(0)
	{}
	virtual ~Module_Mockup() {}

public:
	//////////////////////////////////////////////////////////////////////////////////
	// module specific

	/**
	* get user-friendly display name of module
	*
	* @return module name
	*/
	virtual std::string getModuleName() const
	{ return std::string("Module Mockup"); }

	/**
	* get ID of module
	*
	* @return module ID
	*/
	virtual std::string getModuleID() const
	{ return std::string("Module_Mockup"); }

	/**
	* get URL of module
	*
	* @return module URL
	*/
	virtual std::string getModuleURI() const
	{ return std::string("http://localhost:2020/Module_Mockup"); }

	/**
	* initialize module
	*
	* This function allocates required ressources, open DBs, ...
	*/
	virtual void initModule( 
		IModuleEnvironment *env	///< module environment
	) { 
		this->pEnv = env;
		this->ready = true;
	}

	/**
	* release module
	*/
	virtual void releaseModule()
	{}
	
	/**
	* is module initialized and ready
	*
	* @return module initialization is finished
	*/
	virtual bool isModuleReady() const
	{ return this->ready; }

	/**
	* get module initialization environment
	*
	* @return module environment
	*/
	virtual IModuleEnvironment *getEnv()
	{ return this->pEnv; }

	/**
	* get module description as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getModuleDescription(
		ConnectedVisionResponse &response	///< [out] response containing module description
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get input pins description as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getInputDescription(
		ConnectedVisionResponse &response	///< [out] response containing input pins description
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get output pins description as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getOutputDescription(
		ConnectedVisionResponse &response	///< [out] response containing output pins description
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get list of configIDs as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getConfigList(
		ConnectedVisionResponse &response	///< [out] response containing list of configIDs
	) { throw ConnectedVision::runtime_error("not implemented"); }
	
	/**
	* get detailed config list as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getConfigListDetailed(
		ConnectedVisionResponse &response	///< [out] response containing detailed config list
	) { throw ConnectedVision::runtime_error("not implemented"); }
	
	/**
	* get module status as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getModuleStatus(
		ConnectedVisionResponse &response	///< [out] response containing module status
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get list of input pin IDs
	*
	* @return input pin IDs
	*/
	virtual std::vector<pinID_t> getInputPinIDs() const
	{ throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get specific input pin instance for given configID
	*
	* If no such instance exists, a new one is created.
	*
	* @return input pin
	*/
	virtual boost::shared_ptr< IConnectedVisionInputPin > getInputPin(
		const id_t configID,	///< ID of according config
		const pinID_t pinID		///< ID of requested input pin
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get list of output pin IDs
	*
	* @return output pin IDs
	*/
	virtual std::vector<pinID_t> getOutputPinIDs() const
	{ return std::vector<pinID_t>(); }

	/**
	* get specific output pin instance for given configID
	*
	* If no such instance exists, a new one is created.
	*
	* @return output pin
	*/
	virtual boost::shared_ptr< IConnectedVisionOutputPin > getOutputPin(
		const id_t configID,	///< ID of according config
		const pinID_t pinID		///< ID of requested output pin
	) { throw ConnectedVision::runtime_error("not implemented"); }


	//////////////////////////////////////////////////////////////////////////////////
	// config specific

	/**
	* get configuration for given config ID as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getConfig(
		const id_t configID,				///< [in] ID of config
		ConnectedVisionResponse &response	///< [out] response containing config chain
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* set configuration and return JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int setConfig(
		const id_t configID,				///< [in] ID of config
		const std::string& config,			///< [in] config chain to be set
		ConnectedVisionResponse &response	///< [out] response containing config chain
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* delete full config chain for given config ID as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int deleteConfig(
		const id_t configID,				///< [in] ID of config
		ConnectedVisionResponse &response	///< [out] response containing deleted config chain
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* delete the secified config but keep other configs from the config chain 
	* return deleted config as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int deleteConfigOnlyThis(
		const id_t configID,				///< [in] ID of config
		ConnectedVisionResponse &response	///< [out] response containing deleted config chain
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* get status for given config ID as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getStatus(
		const id_t configID,				///< [in] ID of config
		ConnectedVisionResponse &response	///< [out] response containing status
	) { throw ConnectedVision::runtime_error("not implemented"); }

	/**
	* execute a control command and return status as JSON response
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int control(
		const id_t configID,				///< [in] ID of config
		const std::string& command,			///< [in] control command: start, stop, recover, reset, stopThis, resetThis, notifyStop
		const id_t senderID,				///< [in] ID of sender (successor module)
		ConnectedVisionResponse &response	///< [out] response containing status
	) { throw ConnectedVision::runtime_error("not implemented"); }

	//////////////////////////////////////////////////////////////////////////////////
	// config / worker specific


	/**
		* register worker instance for specific config
		*/
	virtual void registerWorkerInstance(
		const id_t configID,						///< [in] ID of config
		const IWorkerController *workerController	///< [in] worker controller instance
	)  {
		if ( !this->workerMap.insert ( std::pair<id_t, const IWorkerController*>(configID, workerController)).second )
		{
			throw ConnectedVision::runtime_error("config: " + IDToStr(configID) + " already in worker list");
		}
	}

	/**
		* unregister worker instance for specific config
		*/
	virtual void unregisterWorkerInstance(
		const id_t configID,						///< [in] ID of config
		const IWorkerController *workerController	///< [in] worker controller instance
	) {
		try 
		{
			if ( this->workerMap.at(configID) == workerController )
			{
				// remove worker controller from map
				this->workerMap.erase(configID);
			}
			else
			{
				// ignore
			}
		}
		catch (std::out_of_range e)
		{
			// ignore
		}
	}

	/**
		* delete all results for a given configID
		*/
	virtual void deleteAllData(
		const id_t configID				///< [in] ID of config
	) {
		this->deleteAllDataCallCount++;
		this->resultData.clear();
	}


	/**
	* try to recover a given config
	*
	* @return	- true: if recovering was sucessfully (status is stopped)
	*			- false: if config could not be recovered or module does not support recovering
	*/
	virtual bool processConfigRecover(
		const id_t configID				///< [in] ID of config
	) { 
		this->processConfigRecoverCallCount++;
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////
	// store functions

	/**
	* get status store
	*
	* @return status store
	*/
	virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > getStatusStore() const
	{ return this->statusStore; }

	/**
	* get config store
	*
	* @return config store
	*/
	virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > getConfigStore() const
	{ return this->configStore; }


public:
	bool ready;
	IModuleEnvironment *pEnv;
	std::vector<int> resultData;
	std::map<id_t, const IWorkerController*> workerMap;

	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > statusStore;
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > configStore;

	int deleteAllDataCallCount;
	int processConfigRecoverCallCount;
};


}} // namespace scope

#endif // TestHelper_Module_code