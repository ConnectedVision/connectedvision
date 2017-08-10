/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <unordered_set>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>
#include <DataHandling/Store_Ringbuffer.h>
#include "Module/ConfigManager.h"
#include "Module/Module_BaseClass.h"

#include "TestHelper_Module.hpp"
#include "TestHelper_Threads.hpp"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {
namespace Module {

/**

http://plantuml.com/plantuml/form

@startuml
class Module <<IModule>> {
#std::unordered_map<ConfigManager> configList
}
Module .. "Status Store": read status \n (current implementation) (1) 
Module -- ConfigManager: read status \n (TODO) (2)
Module -- "Data Store": read \n (via OutputPin)
note top of Module
The Module controls and coordinates multiple configs.

configList holds all active (running) ConfigManager plus a number of inactive (e.g. initialized, or finished) ones.
Inactive ConfigManager can be removed from the list to make space for new entries.

<b>used patterns:</b>
- [Active Object] to decouple config control command invocation from command execution.
  The goal is to introduce concurrency, by using asynchronous method invocation and a scheduler for handling requests.
  (https://en.wikipedia.org/wiki/Active_object, 
  http://www.dre.vanderbilt.edu/~schmidt/PDF/Act-Obj.pdf)
- [Command Pattern, Command Queue] To queue invoked commands and execute them in 1…X processing threads.
  Commands must be synchronized with respect to the corresponding config. 
  Commands of different configs may be reordered and / or executed concurrently. Commands for the same config
  have to be executed strictly in their queuing order. 
  (https://en.wikipedia.org/wiki/Command_queue, 
  https://en.wikipedia.org/wiki/Command_pattern, 
  http://www.dre.vanderbilt.edu/~schmidt/PDF/CommandRevisited.pdf)

<b>TODO:</b>
- query Class_generic_status via ConfigManager (2)
- remove Store_SQLite_generic_status (3)
end note

class ConfigManager {
-- control --
+ start() / startThis()
+ stop() / stopThis()
+ reset() / resetThis()
+ recover() / recoverThis()
-- information --
+ isRunning()
+ getStatus() / getStatusThis()
+ getConfig()
-- data handling --
# {abstract} clearResults()
}
Module -- "*" ConfigManager : controls 
ConfigManager -- "Status Store": read / write
ConfigManager -- "Config Store": read / write
ConfigManager -- "Data Store": clear

note top of ConfigManager
The ConfigManager manages and controls exactly one config and its config chain.

<b>TODO:</b>
- getStatus() updates Class_generic_status on the fly (2)
- stableResultCounts are read updated by the store automatically (3)

end note 

class WorkerThread <<IWorkerController>> {
}
ConfigManager -- WorkerThread: has 
WorkerThread --> ConfigManager: automatically update status \n (TODO) (2)

note top of WorkerThread
The WorkerThread wraps the Worker in a dedicated thread:
 - create a thread for the worker
 - construct the actual worker instance
 - run the worker
 - synchronication between worker (thread) and module (thread)
 - error handling

<b>used patterns:</b>
- [Mediator] between Worker and ConfigManager -> to avoid threading problems and run worker in own, dedicated thread

end note

package "thread for worker" <<Node>> {

	class Worker << IWorker>> {
	}
	WorkerThread -- Worker: runs
	Worker -- "Data Store": write
	Worker .. "Status Store": write status \n (current implementation) (1) 

	class WorkerFactory <<IWorkerFactory>> {
	std::unique_ptr<IWorker> createWorker()
	}
	WorkerFactory --> Worker: creates

	note top of WorkerFactory
	create a new worker instance for a given config
	end note

}

package "Config Store" <<Database>> {
}
package "Status Store" <<Database>> {
}
package "Data Store" <<Database>> {
}
"Data Store" --> ConfigManager : automatically update status \n (TODO) (3) ???

note as TODO
<b>TODO:</b>

- The status of a specific config is requested through the corresponding ConfigManager only. 
  There is no direct access to the status store by the module.
  
phase (1)  (current implementation) - DONE
- Module --> Class_generic_status: reads status

phase (2)
- query Class_generic_status via ConfigManager
- getStatus() updates Class_generic_status on the fly

phase (3)
- remove Store_SQLite_generic_status from worker
- stableResultCounts are read updated by the store automatically

end note

@enduml
*/

static const std::string configStr =	"{"	
									"	\"id\": \"\", \"name\": \"test config\", \"description\": \"\","
									"	\"version\": 1, "
									"	\"moduleID\": \"ID\", \"moduleURI\": \"\", "
									"	\"params\": {}, "
									"	\"chain\": []"
									"}";

class ConfigStore_Mockup : public ConnectedVision::DataHandling::Store_Ringbuffer<Class_generic_config>
{
public:
	ConfigStore_Mockup() : ConnectedVision::DataHandling::Store_Ringbuffer<Class_generic_config>(ID_NULL, 10)
	{}

	virtual ~ConfigStore_Mockup() {}

	/**
	* get a single element by ID
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_config> getByID(
		const id_t& id	///< [in] object ID
	)
	{
		// mock().actualCall("getByID").onObject(this).withParameter("id", id);
		
		auto data = ConnectedVision::make_shared<Class_generic_config>( configStr );
		data->compute_id();
		if ( id == data->getconst_id() )
		{
			return this->make_const(data);
		}
		else
		{
			return ConnectedVision::shared_ptr<const Class_generic_config>();
		}
	}

};
class StatusStore_Mockup : public ConnectedVision::DataHandling::Store_Ringbuffer<Class_generic_status>
{
public:
	StatusStore_Mockup(const int size = 10) : ConnectedVision::DataHandling::Store_Ringbuffer<Class_generic_status>(ID_NULL, size)
	{}

	virtual ~StatusStore_Mockup() {}
};

#define CHECK_INSTANCE_SINGLETON
class TestWrapper_ConfigManager
{
public:
	typedef boost::unique_lock<boost::mutex> Lock;

	TestWrapper_ConfigManager(		
		const id_t& configID,																///< config chain ID
		const ConnectedVision::Module::IModule& module,							///< ConnectedVision module
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to 
	) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout)
	{
		if ( !workerFactory )
			throw std::invalid_argument("[ConfigManager] invalid workerFactory (null pointer)");
		auto configStore = this->module.getConfigStore();
		if ( !configStore )
			throw std::invalid_argument("[ConfigManager] invalid configStore (null pointer)");

		// load config from store
		auto config = configStore->getByID(configID);
		if ( !config )
			throw std::invalid_argument("[ConfigManager] cannot find config with config id: " + configID);

		// init config manager
		this->init(config);
	}

	TestWrapper_ConfigManager(		
		const Class_generic_config& configOrig,												///< config chain
		const ConnectedVision::Module::IModule& module,										///< module
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to 
	) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout)
	{
		if ( !workerFactory )
			throw std::invalid_argument("[ConfigManager] invalid workerFactory (null pointer)");
		auto configStore = this->module.getConfigStore();
		if ( !configStore )
			throw std::invalid_argument("[ConfigManager] invalid configStore (null pointer)");

		// parse config
		auto config = ConnectedVision::make_shared<Class_generic_config>( configOrig );
		
		// compute id
		id_t configID = config->compute_id();

		// save config to store
		auto configConst = configStore->make_const(config);
		configStore->save_const(configConst);

		// init config manager
		this->init(configConst);
	}


	virtual ~TestWrapper_ConfigManager()
	{
		Lock lock(this->commandMutex);

#ifdef CHECK_INSTANCE_SINGLETON
		// remove from instance list
		{
			Lock instanceLock(this->instanceListMutex);
			if ( this->configConst ) {
				this->instanceList.erase( this->configConst->getconst_id() );
			}
		}
#endif
	}

	/**
	* test if the worker for this config is running
	*
	* @return true if running
	*/
	bool isRunning() const
	{ 
		ConnectedVision::shared_ptr<WorkerThread> workerThread = this->getWorkerThread();
		if ( workerThread )
			return workerThread->isRunning();

		return false;
	}

	/**
	* start the worker for a given config
	*
	* If there is already an existing worker, this function does nothing.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> start() 
	{
		// TODO start chain
		this->startThis();

		return this->getStatus();
	}

	/**
	* start the worker for a given config
	*
	* If there is already an existing worker, this function does nothing.
	*
	* @returns current config status
	*/
	virtual void startThis() 
	{ 
		Lock commandLock(this->commandMutex);
		ConnectedVision::shared_ptr<WorkerThread> workerThread = this->getWorkerThread(); // get local copy of worker thread pointer to avoid scheduling problems

		auto state = waitForStableState( workerThread ); 
		if ( state == ThreadState::NA )
		{
			Lock statusLock(this->statusMutex);
			// we have no active worker -> get state from status class
			state = statusToThreadState( this->statusObj->getconst_status() );
		}

		// a config can only be started if it has the status: init or stopped
		if ( state == ThreadState::Init || state == ThreadState::Stopped )
		{
			if ( workerThread )
			{
				if ( workerThread->isRunning() )
					throw ConnectedVision::runtime_error("[ConfigManager] startThis() config status is not running, but worker thread is running");
			}

			// create new worker thread
			workerThread = ConnectedVision::make_shared<WorkerThread>(this->workerFactory, this->configConst, this->workerTimeout);
			this->setWorkerThread( workerThread );
			state = waitForStableState( workerThread );
		}
	}

	/**
	* stop the worker of a specific config chain, if the config is running
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> stop()
	{
		this->stopThis();
		// TODO stop chain

		return this->getStatus();
	}

	/**
	* stop the worker of a specific config chain, if the config is running
	*
	* @returns current config status
	*/
	virtual void stopThis()
	{
		Lock lock(this->commandMutex);

		ConnectedVision::shared_ptr<WorkerThread> workerThread = this->getWorkerThread(); // get local copy of worker thread pointer to avoid scheduling problems
		if ( workerThread )
		{
			// stop worker thread if we have an active worker
			workerThread->stop_wait();
		}
	}

	/**
	* resets the given config
	*
	* If the config is running, it is stopped in advance.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> reset()
	{
		// make sure that the chain has been stopped
		this->stop();

		// reset this worker
		this->resetThis();
		// TODO reset chain

		return this->getStatus();
	}
	
	/**
	* resets the given config
	*
	* If the config is running, it is stopped in advance.
	*
	* @returns current config status
	*/
	virtual void resetThis()
	{ 
		// make sure that worker is stopped
		this->stopThis();

		// clear results of this config
		this->clearResults();
	}

	/**
	* get status of config chain
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> getStatus()
	{
		auto status = this->getStatusThis();
		// TODO update chain status

		return status;
	}

	/**
	* make const copy of current config status
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> getStatusThis()
	{
		Lock lock(this->statusMutex);

		// update status
		ConnectedVision::shared_ptr<WorkerThread> workerThread = this->getWorkerThread(); // get local copy of worker thread pointer to avoid scheduling problems
		if ( workerThread )
		{
			auto state = workerThread->getCurrentState().get();
			this->statusObj->set_status( this->threadStateToStatus(state) );
		}

		// compate status with prepared statusConst
		if ( this->statusConst )
		{
			if ( this->statusObj->equals( *this->statusConst ) )
			{
				// we have already a valit and up-to-date const status object
				return statusConst;
			}
		}

		// create new const status object
		this->statusConst = this->statusObj->copy();

		return this->statusConst;
	}

	/**
	* get current config
	*
	* @returns current config
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_config> getConfig()
	{
		return this->configConst;
	}

protected:

	/**
	* wait until worker thread ha a stable state
	*
	* @returns state of worker thread
	*/
	ThreadState::ThreadState waitForStableState( const ConnectedVision::shared_ptr<WorkerThread> workerThread ) const
	{
		if ( workerThread )
		{
			for(;;)
			{
				ThreadState::ThreadState threadState = workerThread->getCurrentState();			
	
				switch (threadState)
				{
					case ThreadState::Init:
						return ThreadState::Init;
					case ThreadState::Startup:
						workerThread->wait_until(ThreadState::Running);
						break;
					case ThreadState::Running:
						return ThreadState::Running;
					case ThreadState::Stopping:
						workerThread->wait_until(ThreadState::Stopped);
						break;
					case ThreadState::Stopped:
						return ThreadState::Stopped;
					case ThreadState::Interrupt:
						return ThreadState::Interrupt;
					case ThreadState::Finished:
						return ThreadState::Finished;
					case ThreadState::Error:
						return ThreadState::Error;
					default:
						throw ConnectedVision::runtime_error("[ConfigManager] waitForStableState() unknown ThreadState: " + intToStr(threadState) );
				}
			}
		}

		return ThreadState::NA;
	}

	/**
	* convert thread state to status class status
	*
	* @returns status
	*/
	static ConnectedVision::shared_ptr<std::string> threadStateToStatus(const ThreadState::ThreadState threadState)
	{
		switch (threadState)
		{
			case ThreadState::Init:
				return Class_generic_status::status_init;
			case ThreadState::Startup:
				return Class_generic_status::status_startup;
			case ThreadState::Running:
				return Class_generic_status::status_running;
			case ThreadState::Stopping:
				return Class_generic_status::status_stopping;
			case ThreadState::Stopped:
				return Class_generic_status::status_stopped;
			case ThreadState::Interrupt:
				return Class_generic_status::status_error;
			case ThreadState::Finished:
				return Class_generic_status::status_finished;
			case ThreadState::Error:
				return Class_generic_status::status_error;
			default:
				throw ConnectedVision::runtime_error("[ConfigManager] threadStateToStatus() unknown ThreadState: " + intToStr(threadState) );
		}
	}

	/**
	* convert status class status to thread state
	*
	* @returns status
	*/
	static ThreadState::ThreadState statusToThreadState(const ConnectedVision::shared_ptr<const std::string>& status)
	{
		if ( status == Class_generic_status::status_init )
			return ThreadState::Init;
		if ( status == Class_generic_status::status_startup )
			return ThreadState::Startup;
		if ( status == Class_generic_status::status_running )
			return ThreadState::Running;
		if ( status == Class_generic_status::status_stopping )
			return ThreadState::Stopping;
		if ( status == Class_generic_status::status_stopped )
			return ThreadState::Stopped;
		if ( status == Class_generic_status::status_finished )
			return ThreadState::Finished;
		if ( status == Class_generic_status::status_error )
			return ThreadState::Error;
		throw ConnectedVision::runtime_error("[ConfigManager] statusToThreadState() unknown status: " + *status );
	}

	/**
	* init Config Manager
	*	- load / create status
	*/
	void init(
		ConnectedVision::shared_ptr<const Class_generic_config> config ///< config object
	)
	{
		// set config
		if ( !config )
			throw std::invalid_argument("[ConfigManager] init(): invalid config (null pointer)");
		id_t configID = config->getconst_id();
		if ( configID.empty() )
			throw std::invalid_argument("[ConfigManager] init(): invalid config has no ID");
		this->configConst = config;

#ifdef CHECK_INSTANCE_SINGLETON
		// make sure that we have only one instance per config
		{
			Lock instanceLock(this->instanceListMutex);
			bool insert = this->instanceList.insert(configID).second;
			if ( insert == false )
				throw ConnectedVision::runtime_error("[ConfigManager] there is already an instance for config: " + IDToStr(configID) );
		}
#endif
		try
		{

			// status
			this->statusStore = this->module.getStatusStore();
			if ( !this->statusStore )
				throw std::invalid_argument("[ConfigManager] invalid statusStore (null pointer)");

			// read status from store
			auto statusConst = this->statusStore->getByID(configID);
			if ( statusConst )
			{
				this->statusObj = statusConst->copy();
			}
			else
			{
				// create new status
				this->statusObj = boost::make_shared<Class_generic_status>(config->getconst_id(), module.getModuleID(), module.getModuleURI(), this->module.getOutputPinIDs());
				this->statusStore->save_copy( this->statusObj );
			}

			// TODO: set config for sub configs
			// TODO: get status from sub configs

		}
		catch (...)
		{
#ifdef CHECK_INSTANCE_SINGLETON
			// remove from instance list
			{
				Lock instanceLock(this->instanceListMutex);
				this->instanceList.erase( configID );
			}
#endif

			// rethrow
			throw;
		}
	}

	/**
	* clear computed data in store
	*
	* This function is called when the config is reseted.
	*/
	virtual void clearResults()
	{
		// TODO
	}


	// module
	const ConnectedVision::Module::IModule& module;

	// config
	ConnectedVision::shared_ptr<const Class_generic_config> configConst;

	// worker
	mutable boost::mutex commandMutex;
	ConnectedVision::shared_ptr<WorkerThread> getWorkerThread() const
	{
		Lock workerLock(this->workerMutex);
		ConnectedVision::shared_ptr<WorkerThread> workerThread = this->workerThread; // get local copy of worker thread pointer to avoid scheduling problems
		return workerThread;
	}
	void setWorkerThread(const ConnectedVision::shared_ptr<WorkerThread>& workerThread)
	{
		Lock workerLock(this->workerMutex);
		this->workerThread = workerThread;
	}
	mutable boost::mutex workerMutex;
	ConnectedVision::shared_ptr<WorkerThread> workerThread;
	const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory;
	timestamp_t workerTimeout;

	// status
	ConnectedVision::shared_ptr<Class_generic_status> statusObj;
	ConnectedVision::shared_ptr<const Class_generic_status> statusConst;
	mutable boost::mutex statusMutex;
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > statusStore;

	// config singleton
	static boost::mutex instanceListMutex;
	static std::unordered_set<id_t> instanceList;

public:
	// spy functions
	ConnectedVision::shared_ptr<WorkerThread> spy_workerThread() { return this->workerThread; }

};
#ifdef CHECK_INSTANCE_SINGLETON
boost::mutex TestWrapper_ConfigManager::instanceListMutex;
std::unordered_set<id_t> TestWrapper_ConfigManager::instanceList;
#endif

TEST_GROUP(ConfigManager)
{
	void setup()
	{
		// Init stuff
		// config
		configObj.parseJson( configStr );
		configObj.compute_id();
		configID = configObj.getconst_id();
		module.configStore = ConnectedVision::make_shared<ConfigStore_Mockup>();

		// status
		module.statusStore = ConnectedVision::make_shared<StatusStore_Mockup>();

		// worker factory
		workerFactory_Mockup = ConnectedVision::make_shared<WorkerFactory_Mockup>(&module);
		workerFactory = boost::static_pointer_cast<IWorkerFactory>(workerFactory_Mockup);

	}

	void teardown()
	{
		// Uninit stuff
	}

	Module_Mockup module;

	Class_generic_config configObj;

	id_t configID;

	ConnectedVision::shared_ptr</* const */WorkerFactory_Mockup> workerFactory_Mockup;
	ConnectedVision::shared_ptr</* const */IWorkerFactory> workerFactory;
};

TEST(ConfigManager, constructor_checks_parameters)
{
	//////////////////////////////////////
	// test initialization
	auto configStore = module.configStore;
	auto statusStore = module.statusStore;

	//////////////////////////////////////
	// actual test

	// constructor with config ID
	CHECK_THROWS( std::invalid_argument, TestWrapper_ConfigManager(configID, module, NULL) );
	module.configStore.reset();
	module.statusStore = statusStore;
	CHECK_THROWS( std::invalid_argument, TestWrapper_ConfigManager(configID, module, workerFactory) );
	module.configStore = configStore;
	module.statusStore.reset();
	CHECK_THROWS( std::invalid_argument, TestWrapper_ConfigManager(configID, module, workerFactory) );

	// constructor with config object
	CHECK_THROWS( std::invalid_argument, TestWrapper_ConfigManager(configObj, module, NULL) );
	module.configStore.reset();
	module.statusStore = statusStore;
	CHECK_THROWS( std::invalid_argument, TestWrapper_ConfigManager(configObj, module, workerFactory) );
	module.configStore = configStore;
	module.statusStore.reset();
	CHECK_THROWS( std::invalid_argument, TestWrapper_ConfigManager(configObj, module, workerFactory) );
}

TEST(ConfigManager, constructor_loads_config_from_store)
{
	//////////////////////////////////////
	// test initialization
	auto configOrig = module.configStore->getByID(configID);

	//////////////////////////////////////
	// actual test
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	auto config = configMng.getConfig();
	CHECK( config ); // config is not NULL
	CHECK_EQUAL( configOrig->getconst_id(), config->getconst_id() ); 
	CHECK_EQUAL( *configOrig->getconst_name(), *config->getconst_name() ); 
}

TEST(ConfigManager, constructor_creates_new_config_and_computes_id)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_ConfigManager configMng(configObj, module, workerFactory);

	// get and check config
	auto config = configMng.getConfig();
	CHECK( config );
	CHECK_EQUAL( configID, config->getconst_id() );

}

TEST(ConfigManager, constructor_checks_there_is_only_one_instance_per_config)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	auto configMng = ConnectedVision::make_shared<TestWrapper_ConfigManager>(configObj, module, workerFactory);

	// try to create second instance
	CHECK_THROWS( ConnectedVision::runtime_error, TestWrapper_ConfigManager(configObj, module, workerFactory) );
}

TEST(ConfigManager, the_same_config_can_be_instanced_afte_the_previouse_instance_has_been_released)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	auto configMng = ConnectedVision::make_shared<TestWrapper_ConfigManager>(configObj, module, workerFactory);

	// release first instance
	configMng.reset();

	// try to create second instance
	configMng = ConnectedVision::make_shared<TestWrapper_ConfigManager>(configObj, module, workerFactory);
}

IGNORE_TEST(ConfigManager, constructor_creates_new_config_and_computes_id_including_sub_config)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config configOrig(configStr);

	//////////////////////////////////////
	// actual test

	FAIL("store test not implemented");
}

TEST(ConfigManager, constructor_creates_new_config_and_saves_to_store)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config configOrig(configStr);

	//////////////////////////////////////
	// actual test
	TestWrapper_ConfigManager configMng(configOrig, module, workerFactory);

	// load from store
	auto config = module.configStore->getByIndex(0);
	CHECK( config );
	STRCMP_EQUAL( configOrig.getconst_name()->c_str(), config->getconst_name()->c_str() );
}

IGNORE_TEST(ConfigManager, constructor_sets_sub_configs)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

TEST(ConfigManager, constructor_loads_status_from_store)
{
	//////////////////////////////////////
	// test initialization
	auto statusOrig = ConnectedVision::make_shared<Class_generic_status>();
	statusOrig->set_status_init();
	statusOrig->set_id( configID );
	statusOrig->set_message("constructor_loads_status_from_store");
	module.statusStore->save_copy(statusOrig);

	//////////////////////////////////////
	// actual test
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	// compare with original status
	auto status = configMng.getStatus();
	CHECK_EQUAL( configID, status->getconst_id() );
	CHECK_EQUAL( *statusOrig->getconst_status(), *status->getconst_status() );
	CHECK_EQUAL( *statusOrig->getconst_message(), *status->getconst_message() );
}

TEST(ConfigManager, constructor_creates_new_status)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	// compare with original status
	auto status = configMng.getStatus();
	CHECK_EQUAL( configID, status->getconst_id() );
	CHECK_EQUAL( *Class_generic_status::status_init, *status->getconst_status() );
	DOUBLES_EQUAL( 0.0, status->getconst_progress(), 0.0001 );
}

TEST(ConfigManager, config_is_not_running_at_construction)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test

	CHECK_FALSE( configMng.isRunning() );
}

TEST(ConfigManager, config_is_running_after_start)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = configMng.start();

	CHECK( configMng.isRunning() );
}

TEST(ConfigManager, status_is_running_after_start)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = configMng.start();

	CHECK( status->is_status_running() );
}

TEST(ConfigManager, status_is_stopped_after_stop)
{
	//////////////////////////////////////
	// test initialization
	workerFactory_Mockup->runtime = 1000;
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	configMng.start();
	auto status = configMng.stop();

	CHECK( status->is_status_stopped() );
}

IGNORE_TEST(ConfigManager, status_is_reset_after_reset)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	configMng.start();
	configMng.stop();
	auto status = configMng.reset();

	CHECK( status->is_status_reset() );
}

IGNORE_TEST(ConfigManager, reset_makes_implicit_stop)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	configMng.start();
	auto status = configMng.reset();

	CHECK( status->is_status_reset() );
	CHECK_FALSE( configMng.isRunning() );
}

// status.equals is not implemented, so this test will always fail
IGNORE_TEST(ConfigManager, getStatus_returns_the_same_object_if_status_has_not_changed)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status1 = configMng.getStatus();
	auto status2 = configMng.getStatus();

	CHECK( status1 );
	CHECK( status2 );
	CHECK( status1.get() == status2.get() );
}

TEST(ConfigManager, getStatus_returns_different_object_if_status_has_changed)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status1 = configMng.getStatus();
	configMng.start();
	auto status2 = configMng.getStatus();

	CHECK( status1 );
	CHECK( status2 );
	CHECK_FALSE( status1.get() == status2.get() );
}

IGNORE_TEST(ConfigManager, getStatus_caches_status)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

TEST(ConfigManager, start_a_running_config_does_not_create_a_new_thread)
{
	//////////////////////////////////////
	// test initialization
	workerFactory_Mockup->runtime = 1000;
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	auto status = configMng.start();
	CHECK( configMng.isRunning() );

	//////////////////////////////////////
	// actual test

	// wait for config to get started
	configMng.spy_workerThread()->wait_until(ThreadState::Running);

	// resend start
	auto startThreadList = getRunningThreads();
	configMng.start();
	CHECK( configMng.isRunning() );
	auto workerThreadList = getRunningThreads();
	auto deltaThreadList = compareVector(startThreadList, workerThreadList);
	LONGS_EQUAL( 0, deltaThreadList.size() );

	// stop worker
	configMng.stop();
}

TEST(ConfigManager, start_a_stopped_config_does_start_a_new_worker)
{
	//////////////////////////////////////
	// test initialization
	workerFactory_Mockup->runtime = 5000;
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = configMng.start();
	CHECK( configMng.isRunning() );

	configMng.stop();

	// wait for config to stop
	configMng.spy_workerThread()->wait_until(ThreadState::Stopped);
	CHECK_FALSE( configMng.isRunning() );

	// resend start
	configMng.start();
	CHECK( configMng.isRunning() );

	// stop worker
	configMng.stop();
}

TEST(ConfigManager, start_a_finished_config_does_not_create_a_new_thread)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	auto status = configMng.start();
	CHECK( configMng.isRunning() );

	//////////////////////////////////////
	// actual test

	// wait for config to finish
	configMng.spy_workerThread()->wait_until(ThreadState::Finished);
	CHECK_FALSE( configMng.isRunning() );

	// resend start
	auto startThreadList = getRunningThreads();
	configMng.start();
	auto workerThreadList = getRunningThreads();
	auto deltaThreadList = compareVector(startThreadList, workerThreadList);
	LONGS_EQUAL( 0, deltaThreadList.size() );
	CHECK_FALSE( configMng.isRunning() );

	configMng.stop();
}

IGNORE_TEST(ConfigManager, start_also_starts_sub_configs)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

IGNORE_TEST(ConfigManager, start_sets_sub_configs_if_not_existing)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

IGNORE_TEST(ConfigManager, stop_also_stopps_sub_configs)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

IGNORE_TEST(ConfigManager, reset_calls_cleanup_to_remove_data_from_store)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConfigManager configMng(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

IGNORE_TEST(ConfigManager, getStatus_fetches_status_from_sub_configs)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

IGNORE_TEST(ConfigManager, getStatusThis_fetches_this_module_status_only)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

}} // namespace