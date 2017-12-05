/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <unordered_set>

#include <ConnectedVision_Thread.h>
#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>
#include <DataHandling/Store_Ringbuffer.h>
#include <Module/Module_BaseClass.h>

#include "TestHelper_Module.hpp"
#include "TestHelper_Threads.hpp"

#include <CppUTest/TestHarness.h>


#include "WorkerController.cpp"
typedef ConnectedVision::Module::WorkerController TestWrapper_WorkerController;

namespace ConnectedVision {
namespace Module {

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

TEST_GROUP(WorkerController)
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

TEST(WorkerController, constructor_checks_parameters)
{
	//////////////////////////////////////
	// test initialization
	auto configStore = module.configStore;
	auto statusStore = module.statusStore;

	//////////////////////////////////////
	// actual test

	// constructor with config ID
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerController(configID, module, NULL) );
	module.configStore.reset();
	module.statusStore = statusStore;
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerController(configID, module, workerFactory) );
	module.configStore = configStore;
	module.statusStore.reset();
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerController(configID, module, workerFactory) );

	// constructor with config object
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerController(configObj, module, NULL) );
	module.configStore.reset();
	module.statusStore = statusStore;
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerController(configObj, module, workerFactory) );
	module.configStore = configStore;
	module.statusStore.reset();
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerController(configObj, module, workerFactory) );
}

TEST(WorkerController, constructor_loads_config_from_store)
{
	//////////////////////////////////////
	// test initialization
	auto configOrig = module.configStore->getByID(configID);

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	auto config = workerCtrl.getConfig();
	CHECK( config ); // config is not NULL
	CHECK_EQUAL( configOrig->getconst_id(), config->getconst_id() ); 
	CHECK_EQUAL( *configOrig->getconst_name(), *config->getconst_name() ); 
}

TEST(WorkerController, constructor_creates_new_config_and_checks_id)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerController workerCtrl(configObj, module, workerFactory);

	// get and check config
	auto config = workerCtrl.getConfig();
	CHECK( config );
	CHECK_EQUAL( configID, config->getconst_id() );

}

TEST(WorkerController, constructor_sets_worker_status)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerController workerCtrl(configObj, module, workerFactory);

	// get and check config
	// TODO auto status = workerCtrl.spy_workerStatus();
	// TODO CHECK_EQUAL( ConfigStatus::init, status );
}

TEST(WorkerController, constructor_checks_there_is_only_one_instance_per_config)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	auto workerCtrl = ConnectedVision::make_shared<TestWrapper_WorkerController>(configObj, module, workerFactory);

	// try to create second instance
	CHECK_THROWS( std::runtime_error, TestWrapper_WorkerController(configObj, module, workerFactory) );
}

TEST(WorkerController, the_same_config_can_be_instanced_afte_the_previouse_instance_has_been_released)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	auto workerCtrl = ConnectedVision::make_shared<TestWrapper_WorkerController>(configObj, module, workerFactory);

	// release first instance
	workerCtrl.reset();

	// try to create second instance
	workerCtrl = ConnectedVision::make_shared<TestWrapper_WorkerController>(configObj, module, workerFactory);
}

TEST(WorkerController, constructor_creates_new_config_and_saves_to_store)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config configOrig(configStr);

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerController workerCtrl(configOrig, module, workerFactory);

	// load from store
	auto config = module.configStore->getByIndex(0);
	CHECK( config );
	STRCMP_EQUAL( configOrig.getconst_name()->c_str(), config->getconst_name()->c_str() );
}

TEST(WorkerController, constructor_loads_status_from_store)
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
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	// compare with original status
	auto status = workerCtrl.getStatus();
	CHECK_EQUAL( configID, status->getconst_id() );
	CHECK_EQUAL( *statusOrig->getconst_status(), *status->getconst_status() );
	CHECK_EQUAL( *statusOrig->getconst_message(), *status->getconst_message() );
}

TEST(WorkerController, constructor_creates_new_status)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	// compare with original status
	auto status = workerCtrl.getStatus();
	CHECK_EQUAL( configID, status->getconst_id() );
	CHECK_EQUAL( *Class_generic_status::status_init, *status->getconst_status() );
	DOUBLES_EQUAL( 0.0, status->getconst_progress(), 0.0001 );
}

TEST(WorkerController, destructor_terminates_all_threads)
{
	//////////////////////////////////////
	// test initialization
	auto startThreadList = getRunningThreads();

	//////////////////////////////////////
	// actual test
	{
		TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

		// compare with original status
		auto status = workerCtrl.getStatus();
		CHECK_EQUAL( configID, status->getconst_id() );
	}

	auto endThreadList = getRunningThreads();
	auto deltaThreadList = compareVector(startThreadList, endThreadList);
	LONGS_EQUAL( 0, deltaThreadList.size() );
}

TEST(WorkerController, config_is_not_running_at_construction)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test

	CHECK_FALSE( workerCtrl.activeWorker() );
}

IGNORE_TEST(WorkerController, start_command_is_enqueued_to_commandQueue)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = workerCtrl.start();

	auto commandQueue = status->getconst_commandQueue();

	// command queue holds exactly one command
	LONGS_EQUAL( 1, commandQueue->size() );
	CHECK_EQUAL( "start", *commandQueue->at(0) );
}

IGNORE_TEST(WorkerController, stop_command_is_enqueued_to_commandQueue)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = workerCtrl.stop();

	auto commandQueue = status->getconst_commandQueue();

	// command queue holds exactly one command
	LONGS_EQUAL( 1, commandQueue->size() );
	CHECK_EQUAL( "stop", *commandQueue->at(0) );
}

IGNORE_TEST(WorkerController, reset_command_is_enqueued_to_commandQueue)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = workerCtrl.reset();

	auto commandQueue = status->getconst_commandQueue();

	// command queue holds exactly one command
	LONGS_EQUAL( 1, commandQueue->size() );
	CHECK_EQUAL( "reset", *commandQueue->at(0) );
}

IGNORE_TEST(WorkerController, revocer_command_is_enqueued_to_commandQueue)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = workerCtrl.recover();

	auto commandQueue = status->getconst_commandQueue();

	// command queue holds exactly one command
	LONGS_EQUAL( 1, commandQueue->size() );
	CHECK_EQUAL( "recover", *commandQueue->at(0) );
}

TEST(WorkerController, reset_makes_implicit_stop)
{
	//////////////////////////////////////
	// test initialization
	const int timeout = 1000;
	workerFactory_Mockup->runtime = 5000;
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	workerCtrl.start();
	workerCtrl.spy_workerThreadProgress().wait_until(WorkerThreadProgress::Running, timeout);

	//////////////////////////////////////
	// actual test
	CHECK( workerCtrl.activeWorker() );

	// reset module
	workerCtrl.reset();
	workerCtrl.spy_workerThreadProgress().wait_equal(WorkerThreadProgress::Init, timeout);
	CHECK_EQUAL(WorkerThreadProgress::Init, workerCtrl.spy_workerThreadProgress());

	CHECK_FALSE( workerCtrl.activeWorker() );
}

TEST(WorkerController, reset_calls_cleanup_to_remove_data_from_store)
{
	//////////////////////////////////////
	// test initialization
	const int timeout = 1000;
	workerFactory_Mockup->runtime = 5000;
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	workerCtrl.start();
	workerCtrl.spy_workerThreadProgress().wait_until(WorkerThreadProgress::Running, timeout);

	//////////////////////////////////////
	// actual test
	CHECK( workerCtrl.activeWorker() );

	// add some data
	for ( int i = 0; i < 10; ++i )
		module.resultData.push_back(i);

	// reset module
	workerCtrl.reset();
	workerCtrl.spy_workerThreadProgress().wait_equal(WorkerThreadProgress::Init, timeout);
	CHECK_EQUAL(WorkerThreadProgress::Init, workerCtrl.spy_workerThreadProgress());

	// make sure that data have been deleted
	CHECK( module.resultData.empty() );
}

// status.equals is not implemented, so this test will always fail
IGNORE_TEST(WorkerController, getStatus_returns_the_same_object_if_status_has_not_changed)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status1 = workerCtrl.getStatus();
	auto status2 = workerCtrl.getStatus();

	CHECK( status1 );
	CHECK( status2 );
	CHECK( status1.get() == status2.get() );
}

IGNORE_TEST(WorkerController, getStatus_returns_different_object_if_status_has_changed)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status1 = workerCtrl.getStatus();
	workerCtrl.start();
	auto status2 = workerCtrl.getStatus();

	CHECK( status1 );
	CHECK( status2 );
	CHECK_FALSE( status1.get() == status2.get() );
}

IGNORE_TEST(WorkerController, getStatus_caches_status)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	FAIL("test not implemented");
}

TEST(WorkerController, start_a_stopped_config_does_start_a_new_worker)
{
	//////////////////////////////////////
	// test initialization
	const int timeout = 1000;
	workerFactory_Mockup->runtime = 5000;
	TestWrapper_WorkerController workerCtrl(configID, module, workerFactory);

	//////////////////////////////////////
	// actual test
	auto status = workerCtrl.start();
	CHECK( workerCtrl.activeWorker() );

	workerCtrl.stop();

	// wait for config to stop
	workerCtrl.spy_workerThreadProgress().wait_until(WorkerThreadProgress::Stopped, timeout);
	CHECK_FALSE( workerCtrl.activeWorker() );

	// resend start
	workerCtrl.start();
	workerCtrl.spy_workerThreadProgress().wait_while(WorkerThreadProgress::Stopped, timeout);
	workerCtrl.spy_workerThreadProgress().wait_until(WorkerThreadProgress::Running, timeout);
	CHECK( workerCtrl.activeWorker() );

	// stop worker
	workerCtrl.stop();
}

}} // namespace