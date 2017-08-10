/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "TestHelper_Module.hpp"
#include "TestHelper_Threads.hpp"

#include <CppUTest/TestHarness.h>

#include "Module/WorkerDispatcher.h"

namespace ConnectedVision {
namespace Module {

class TestWrapper_WorkerDispatcher : public WorkerDispatcher
{
public:
	/**
	* constructor
	*/
	TestWrapper_WorkerDispatcher(		
		const ConnectedVision::shared_ptr<IWorkerFactory> workerFactory,	///< [in] worker factory
		const timestamp_t workerStopTimeout = 5000							///< [in] timeout to wait for worker to stop, befor forcing an interrupt
	) : WorkerDispatcher(workerFactory, workerStopTimeout)
	{}

	/**
	* virtual destructor
	*/
    virtual ~TestWrapper_WorkerDispatcher()	{}

	// spy functions
	std::unordered_map<id_t, std::unique_ptr<WorkerThread> >& spy_workers() { return this->workers; }
	ConnectedVision::mutex& spy_mutex() { return this->mutex; }

};

TEST_GROUP(WorkerDispatcher)
{
	void setup()
	{
		// Init stuff
		workerFactory_Mockup = ConnectedVision::make_shared<WorkerFactory_Mockup>(&module);
		workerFactory = boost::static_pointer_cast<IWorkerFactory>(workerFactory_Mockup);
	}

	void teardown()
	{
		// Uninit stuff
	}

	Module_Mockup module;
	ConnectedVision::shared_ptr</* const */WorkerFactory_Mockup> workerFactory_Mockup;
	ConnectedVision::shared_ptr</* const */IWorkerFactory> workerFactory;
};

TEST(WorkerDispatcher, init)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);

	// check for NULL pointer
	CHECK_THROWS( std::invalid_argument, TestWrapper_WorkerDispatcher(ConnectedVision::shared_ptr<IWorkerFactory>()) );
}

TEST(WorkerDispatcher, getRunningWorkers_returns_empty_list)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);

	//////////////////////////////////////
	// actual test
	auto workers = dispatcher.getRunningWorkerIDs();
	LONGS_EQUAL(0, workers.size() );
}

TEST(WorkerDispatcher, getRunningWorkers_is_thread_safe)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);

	//////////////////////////////////////
	// actual test
	
	// lock mutex
	ConnectedVision::Lock lock(dispatcher.spy_mutex());

	// start should not be able to get lock of mutex
	CHECK_THROWS( mutex_error, dispatcher.getRunningWorkerIDs() );
}

TEST(WorkerDispatcher, start_creates_a_new_thread_and_starts_worker)
{
/* 
	It is important to create the worker (call constructor) within the new thread:
	 - the original thread should not be blocked 
	 - the worker should be allowed to do resource allocation in the constructor, even if it is time consuming
*/

	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");

	//////////////////////////////////////
	// actual test
	dispatcher.start(config);

	auto workerIDs = dispatcher.getRunningWorkerIDs();
	LONGS_EQUAL( 1, workerIDs.size() );
	CHECK_EQUAL( config->getconst_id(), workerIDs.at(0) );

	// spy worker from factory
	LONGS_EQUAL( 1, workerFactory_Mockup->numberOfCreatedWorkers );

	// check that worker is running in worker thread
	auto thisThreadID = getCurrentThread().id;
	CHECK( Worker_Mockup_spy::constructorThreadID != thisThreadID );
	CHECK( Worker_Mockup_spy::runThreadID != thisThreadID );
	CHECK( Worker_Mockup_spy::constructorThreadID == Worker_Mockup_spy::runThreadID );
}

TEST(WorkerDispatcher, start_creates_only_one_worker)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);
	auto startThreadList = getRunningThreads();

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");


	//////////////////////////////////////
	// actual test
	
	// start config
	dispatcher.start(config);
	LONGS_EQUAL( 1, dispatcher.getRunningWorkerIDs().size() );

	// check threads
	auto workerThreadList1 = getRunningThreads();
	LONGS_EQUAL( 1, (long)(workerThreadList1.size() - startThreadList.size()) );

	// start the same config a second time
	dispatcher.start(config);
	LONGS_EQUAL( 1, dispatcher.getRunningWorkerIDs().size() );

	// check threads
	auto workerThreadList2 = getRunningThreads();
	CHECK_EQUAL( workerThreadList1, workerThreadList2 );

	// spy worker from factory
	LONGS_EQUAL( 1, workerFactory_Mockup->numberOfCreatedWorkers );
}

TEST(WorkerDispatcher, start_is_thread_safe)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");

	//////////////////////////////////////
	// actual test
	
	// lock mutex
	ConnectedVision::Lock lock(dispatcher.spy_mutex());

	// start should not be able to get lock of mutex
	CHECK_THROWS( mutex_error, dispatcher.start(config) );
}

TEST(WorkerDispatcher, stop_send_shutdown_to_worker)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);
	auto startThreadList = getRunningThreads();
	auto& workers = dispatcher.spy_workers();

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");

	//////////////////////////////////////
	// actual test

	// start config
	dispatcher.start(config);
	LONGS_EQUAL( 1, workers.size() );
	auto& workerThread = workers.begin()->second;

	// stop config
	dispatcher.stop(config->getconst_id());

	// check that worker is is shutdown mode
	CHECK( workerThread->getSetState().get() >= ThreadState::Stopping );
}

TEST(WorkerDispatcher, stop_is_thread_safe)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");

	//////////////////////////////////////
	// actual test
	
	// lock mutex
	ConnectedVision::Lock lock(dispatcher.spy_mutex());

	// stop should not be able to get lock of mutex
	CHECK_THROWS( mutex_error, dispatcher.stop(config->getconst_id()) );
}

TEST(WorkerDispatcher, stop_threads_are_removed_from_thread_list)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);
	auto& workers = dispatcher.spy_workers();
	auto startThreadList = getRunningThreads();

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");

	//////////////////////////////////////
	// actual test

	// start config
	dispatcher.start(config);
	LONGS_EQUAL( 1, dispatcher.getRunningWorkerIDs().size() );
	LONGS_EQUAL( 1, workers.size() );

	// stop config
	dispatcher.stop(config->getconst_id());

	// wait for worker thread to be stopped
	auto& workerThread = workers.begin()->second;
	CHECK( workerThread->wait_until(ThreadState::Stopped, 1000) );

	// config is no longer running
	LONGS_EQUAL( 0, dispatcher.getRunningWorkerIDs().size() );
	LONGS_EQUAL( 0, workers.size() );
}

TEST(WorkerDispatcher, finished_threads_are_removed_from_thread_list)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_WorkerDispatcher dispatcher(workerFactory);
	auto startThreadList = getRunningThreads();
	auto& workers = dispatcher.spy_workers();

	auto config = ConnectedVision::make_shared<Class_generic_config>();
	config->set_id("condifID");

	//////////////////////////////////////
	// actual test

	// start config
	workerFactory_Mockup->runtime = 10;
	dispatcher.start(config);
	LONGS_EQUAL( 1, dispatcher.getRunningWorkerIDs().size() );
	LONGS_EQUAL( 1, workers.size() );

	// wait for worker thread to finish
	auto& workerThread = workers.begin()->second;
	CHECK( workerThread->wait_until(ThreadState::Finished, workerFactory_Mockup->runtime + 1000) );

	// config is no longer running
	LONGS_EQUAL( 0, dispatcher.getRunningWorkerIDs().size() );
	LONGS_EQUAL( 0, workers.size() );
}

}} // namespace
