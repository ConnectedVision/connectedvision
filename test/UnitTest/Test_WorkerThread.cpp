/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <Module/WorkerThread.h>

#include "TestHelper_Module.hpp"
#include "TestHelper_Threads.hpp"

#include <CppUTest/TestHarness.h>


namespace ConnectedVision {
namespace Module {

static const timestamp_t tolerance = 1000;
static const timestamp_t timeout = 100;

class TestWrapper_WorkerThread : public WorkerThread
{
public:

	TestWrapper_WorkerThread(
		const ConnectedVision::shared_ptr<IWorkerFactory>& workerFactory,		///< [in] worker factory
		const ConnectedVision::shared_ptr<const Class_generic_config>& config	///< [in] config for worker
		) :  WorkerThread(workerFactory, config, timeout) {}


	TestWrapper_WorkerThread(
		const ConnectedVision::shared_ptr<IWorkerFactory>& workerFactory,		///< [in] worker factory
		const ConnectedVision::shared_ptr<const Class_generic_config>& config,	///< [in] config for worker
		const timestamp_t workerTimeout											///< timeout to wait for 
																				///		- start a new thread 
																				///		- stop, before forcing an interrupt
		) :  WorkerThread(workerFactory, config, workerTimeout) {}

	// spy functions
	boost::thread& spy_thread() { return this->thread; }
};

TEST_GROUP(WorkerThread)
{
	void setup()
	{
		// Init stuff
		config = ConnectedVision::make_shared<const Class_generic_config>();
		workerFactory_Mockup = ConnectedVision::make_shared<WorkerFactory_Mockup>(&module, 1000);
		workerFactory = boost::static_pointer_cast<IWorkerFactory>(workerFactory_Mockup);
	}

	void teardown()
	{
		// Uninit stuff
	}

	Module_Mockup module;
	ConnectedVision::shared_ptr<const Class_generic_config> config;
	ConnectedVision::shared_ptr</* const */WorkerFactory_Mockup> workerFactory_Mockup;
	ConnectedVision::shared_ptr</* const */IWorkerFactory> workerFactory;
};

TEST(WorkerThread, constructor_starts_new_thread)
{
	//////////////////////////////////////
	// test initialization
	auto startThreadList = getRunningThreads();

	//////////////////////////////////////
	// actual test
	TestWrapper_WorkerThread workerThread(workerFactory, config);

	// check that we have a valid, new thread
	auto workerThreadList = getRunningThreads();
	auto deltaThreadList = compareVector(startThreadList, workerThreadList);
	auto& t = workerThread.spy_thread();

	CHECK( t.get_id() != boost::thread::id() );
	LONGS_EQUAL( 1, deltaThreadList.size() );
}

TEST(WorkerThread, immediate_destroy_worker)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create worker thread
	std::unique_ptr<TestWrapper_WorkerThread> workerThread(new TestWrapper_WorkerThread(workerFactory, config) );
	
	// wait for worker thread
	workerThread.reset();

	CHECK(true); // just to make sure that the test is counted
}

// This test is disabled because it would wait 5 sec. for the worker thread to join (default timeout).
#if 0
TEST(WorkerThread, constructor_default_timeout)
{
	//////////////////////////////////////
	// test initialization
	auto startThreadList = getRunningThreads();

	//////////////////////////////////////
	// actual test
	
	timestamp_t timeout = 5000; // default
	// create worker thread
	std::unique_ptr<WorkerThread> workerThread(new WorkerThread(workerFactory, config) );
	// wait for worker thread
	auto start = boost::chrono::high_resolution_clock::now();
	workerThread.reset();
	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
	CHECK_TEXT( runtime + tolerance > timeout, intToStr(runtime).c_str() );
	CHECK_TEXT( runtime < timeout + tolerance, intToStr(runtime).c_str() );
}
#endif

TEST(WorkerThread, constructor_takes_timeout_to_destroy_worker)
{
	//////////////////////////////////////
	// test initialization
	auto startThreadList = getRunningThreads();
	workerFactory_Mockup->cooperative = false;

	//////////////////////////////////////
	// actual test
	
	// create worker thread with 0 timeout
	CHECK_THROWS( std::invalid_argument, new TestWrapper_WorkerThread(workerFactory, config, 0) );

	{
		timestamp_t timeout = 1;
		// create worker thread
		std::unique_ptr<TestWrapper_WorkerThread> workerThread(new TestWrapper_WorkerThread(workerFactory, config, timeout) );
		workerThread->wait_until(ThreadState::Running);
		// wait for worker thread
		auto start = boost::chrono::high_resolution_clock::now();
		workerThread.reset();
		auto end = boost::chrono::high_resolution_clock::now();
		auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
		CHECK_TEXT( runtime + tolerance > timeout, intToStr(runtime).c_str() );
		CHECK_TEXT( runtime < timeout + tolerance, intToStr(runtime).c_str() );
	}

	{
		timestamp_t timeout = 100;
		// create worker thread
		std::unique_ptr<TestWrapper_WorkerThread> workerThread(new TestWrapper_WorkerThread(workerFactory, config, timeout) );
		workerThread->wait_until(ThreadState::Running);
		// wait for worker thread
		auto start = boost::chrono::high_resolution_clock::now();
		workerThread.reset();
		auto end = boost::chrono::high_resolution_clock::now();
		auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
		CHECK_TEXT( runtime + tolerance > timeout, intToStr(runtime).c_str() );
		CHECK_TEXT( runtime < timeout + tolerance, intToStr(runtime).c_str() );
	}
}

TEST(WorkerThread, destructor_waits_for_thread_to_finish)
{
	//////////////////////////////////////
	// test initialization

	auto startThreadList = getRunningThreads();

	//////////////////////////////////////
	// actual test
	std::unique_ptr<TestWrapper_WorkerThread> workerThread(new TestWrapper_WorkerThread(workerFactory, config) );
	
	// check threads
	auto workerThreadList = getRunningThreads();
	LONGS_EQUAL( 1, (long)(workerThreadList.size() - startThreadList.size()) );
	auto deltaThreadList = compareVector(startThreadList, workerThreadList);
	LONGS_EQUAL( 1, (long)(deltaThreadList.size()) );

	// destroy workerThread
	workerThread.reset();

	// check threads
	auto finishThreadList = getRunningThreads();
	LONGS_EQUAL( -1, (long)(finishThreadList.size() - workerThreadList.size()) );
	auto removedThreadList = compareVector(workerThreadList, finishThreadList);
	LONGS_EQUAL( 1, (long)(removedThreadList.size()) );

	CHECK( startThreadList == finishThreadList );
	CHECK( deltaThreadList == removedThreadList );
}

TEST(WorkerThread, start_in_new_thread)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	// create & start worker
	LONGS_EQUAL( 0, workerFactory_Mockup->numberOfCreatedWorkers );

	TestWrapper_WorkerThread workerThread(workerFactory, config);

	// wait for thread status
	auto state = workerThread.getCurrentState().get();
	CHECK_TEXT( state  >= ThreadState::Startup, std::string("current state (" + ThreadState::toString(state) + ") is less than Startup").c_str());

	// wait for factory
	CHECK( workerThread.wait_until(ThreadState::Running, 100) );
	CHECK_TEXT( state  >= ThreadState::Running, std::string("current state (" + ThreadState::toString(state) + ") is less than Running").c_str());

	// check worker factory
	LONGS_EQUAL( 1, workerFactory_Mockup->numberOfCreatedWorkers );

	// check that worker was constructed in worker thread
	auto threadID = getCurrentThread().id;
	CHECK( Worker_Mockup_spy::constructorThreadID != threadID );

	// check that worker is running in worker thread
	LONGS_EQUAL( Worker_Mockup_spy::runThreadID, Worker_Mockup_spy::constructorThreadID );
}

TEST(WorkerThread, stop_async_forced_timeout)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);

	// wait for worter to start
	CHECK( workerThread.wait_until(ThreadState::Running, 100) );
	CHECK( workerThread.getCurrentState().get() == ThreadState::Running );
	boost::this_thread::sleep_for(boost::chrono::milliseconds( 50 ));

	// send async stop signal to worker
	workerThread.stop_async();

	// test that worker was forced to stop
	CHECK( workerThread.wait_until(ThreadState::Stopped, timeout + tolerance) );
}

TEST(WorkerThread, stop_async_returns_threadstate_stopping)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);

	// wait for worter to start
	CHECK( workerThread.wait_until(ThreadState::Running, 100) );

	// send async stop signal to worker
	workerThread.stop_async();

	// test that thread is in shutdown state
	CHECK( workerThread.getSetState().get() >= ThreadState::Stopping );
}

TEST(WorkerThread, call_stop_async_multiple)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);

	// send multiple async stop signal to worker
	workerThread.stop_async();
	workerThread.stop_async();

	// wait
	boost::this_thread::sleep_for(boost::chrono::milliseconds( (timeout + tolerance)/2 ));

	// send multiple async stop signal to worker
	workerThread.stop_async();
	workerThread.stop_async();

	// test that worker was forced to stop
	CHECK( workerThread.wait_until(ThreadState::Stopped, (timeout + tolerance)/2 ) );
}

TEST(WorkerThread, stop_wait_cooperative_worker)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	workerFactory_Mockup->cooperative = true;
	TestWrapper_WorkerThread workerThread(workerFactory, config );

	// wait for worker factory
	CHECK( workerThread.wait_until(ThreadState::Running, 100) );

	// stop worker
	auto start = boost::chrono::high_resolution_clock::now();
	workerThread.stop_wait();
	auto end = boost::chrono::high_resolution_clock::now();
	auto shutdowntime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	// test that worker was stop
	LONGS_EQUAL( ThreadState::Stopped, workerThread.getCurrentState().get() );

	// the worker was cooperative, so it has not been timed out 
	CHECK_TEXT(shutdowntime < timeout, std::string("workerThread runtime (" + intToStr(shutdowntime) + ") is greater than timeout (" + intToStr(timeout) + ")").c_str() );
}

TEST(WorkerThread, forced_stop_wait_uncooperative_worker)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	workerFactory_Mockup->cooperative = false;
	TestWrapper_WorkerThread workerThread(workerFactory, config );

	// wait for worker factory
	CHECK( workerThread.wait_until(ThreadState::Running, 100) );

	// stop worker
	auto start = boost::chrono::high_resolution_clock::now();
	workerThread.stop_wait();
	auto end = boost::chrono::high_resolution_clock::now();
	auto shutdowntime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	// test that worker was forced to stop
	LONGS_EQUAL( ThreadState::Interrupt, workerThread.getCurrentState().get() );

	// test that thread has timed out 
	CHECK_TEXT(shutdowntime >= timeout, std::string("workerThread runtime (" + intToStr(shutdowntime) + ") is less than timeout (" + intToStr(timeout) + ")").c_str() );
}

TEST(WorkerThread, call_stop_wait_multiple)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);

	// stop worker
	workerThread.stop_wait();

	// worker is stopped
	CHECK(	workerThread.getCurrentState().get() == ThreadState::Stopped || 
			workerThread.getCurrentState().get() == ThreadState::Interrupt );

	// resend stop worker
	workerThread.stop_wait();

	// worker is still stopped
	CHECK(	workerThread.getCurrentState().get() == ThreadState::Stopped || 
			workerThread.getCurrentState().get() == ThreadState::Interrupt );
}

TEST(WorkerThread, isRunning_returns_true_on_running_thread)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);
	workerThread.wait_until(ThreadState::Running, 100);

	// check that thread is running
	CHECK( workerThread.isRunning() );
}

TEST(WorkerThread, isRunning_returns_false_for_async_stopped_thread)
{
	//////////////////////////////////////
	// test initialization

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);

	//////////////////////////////////////
	// actual test

	// send async stop signal to worker
	workerThread.stop_async();
	// wait for worker thread to stop
	CHECK( workerThread.wait_until(ThreadState::Stopped, timeout + tolerance) );
	boost::this_thread::sleep_for(boost::chrono::milliseconds( tolerance ));

	CHECK_FALSE( workerThread.isRunning() );
}

TEST(WorkerThread, isRunning_returns_false_for_finished_thread)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr</* const */IWorkerFactory> workerFactory = boost::static_pointer_cast<IWorkerFactory>(ConnectedVision::make_shared<WorkerFactory_Mockup>(&module, 10));

	// create & start worker
	TestWrapper_WorkerThread workerThread(boost::static_pointer_cast<IWorkerFactory>(workerFactory), config);

	//////////////////////////////////////
	// actual test

	// wait for worker thread to finish
	workerThread.spy_thread().join();

	CHECK_FALSE( workerThread.isRunning() );
}

TEST(WorkerThread, isRunning_returns_correct_on_subsequent_calls)
{
	//////////////////////////////////////
	// test initialization

	// create & start worker
	TestWrapper_WorkerThread workerThread(workerFactory, config);
	workerThread.wait_until(ThreadState::Running, 100);

	//////////////////////////////////////
	// actual test

	CHECK( workerThread.isRunning() );
	CHECK( workerThread.isRunning() );

	// send stop signal to worker
	workerThread.stop_wait();

	CHECK_FALSE( workerThread.isRunning() );
	CHECK_FALSE( workerThread.isRunning() );

	// wait for worker thread to finish
	workerThread.spy_thread().join();

	CHECK_FALSE( workerThread.isRunning() );
	CHECK_FALSE( workerThread.isRunning() );
}

TEST(WorkerThread, intermediateContinueCheck_returnes_true_if_worker_has_been_started)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_WorkerThread workerThread(workerFactory, config );

	//////////////////////////////////////
	// actual test

	// nextIterationStep is true from the beginning
	CHECK( workerThread.intermediateContinueCheck() );

	// wait for worker factory
	workerThread.wait_until(ThreadState::Running);

	// intermediateContinueCheck() is still true as long as nobody stopped the worker
	CHECK( workerThread.intermediateContinueCheck() );

}

TEST(WorkerThread, intermediateContinueCheck_returnes_false_if_worker_has_been_stopped)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_WorkerThread workerThread(workerFactory, config );

	//////////////////////////////////////
	// actual test

	// immediately stop worker
	workerThread.stop_async();

	// intermediateContinueCheck() is false as soon as a (async) stop command has been sent
	CHECK_FALSE( workerThread.intermediateContinueCheck() );

	// wait for worker to actually stop
	workerThread.wait_until(ThreadState::Stopped);

	// intermediateContinueCheck() is still false
	CHECK_FALSE( workerThread.intermediateContinueCheck() );

}

TEST(WorkerThread, nextIterationStep_returnes_true_if_worker_has_been_started)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_WorkerThread workerThread(workerFactory, config );

	//////////////////////////////////////
	// actual test

	// nextIterationStep is true from the beginning
	CHECK( workerThread.nextIterationStep() );

	// wait for worker factory
	workerThread.wait_until(ThreadState::Running);

	// nextIterationStep() is still true as long as nobody stopped the worker
	CHECK( workerThread.nextIterationStep() );

}

TEST(WorkerThread, nextIterationStep_returnes_false_if_worker_has_been_stopped)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_WorkerThread workerThread(workerFactory, config );

	//////////////////////////////////////
	// actual test

	// immediately stop worker
	workerThread.stop_async();

	// nextIterationStep() is false as soon as a (async) stop command has been sent
	CHECK_FALSE( workerThread.nextIterationStep() );

	// wait for worker to actually stop
	workerThread.wait_until(ThreadState::Stopped);

	// nextIterationStep() is still false
	CHECK_FALSE( workerThread.nextIterationStep() );

}


}} // namespace
