/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/thread/thread.hpp>
#include <boost/thread/scoped_thread.hpp>

#include "ConnectedVision_ConcurrentQueue.h"

#include <CppUTest/TestHarness.h>

TEST_GROUP(ConcurrentQueue)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}
};

template<class T>
class TestWrapper_ConcurrentQueue : public ConnectedVision::ConcurrentQueue<T>
{
public:
	boost::mutex& spy_mutex() { return ConnectedVision::ConcurrentQueue<T>::mutex; }
	std::queue<T> & spy_queue() { return ConnectedVision::ConcurrentQueue<T>::queue; }
};


TEST(ConcurrentQueue, new_queue_is_empty)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test
	CHECK( queue.empty() );
}

TEST(ConcurrentQueue, populated_queue_is_not_empty)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConcurrentQueue<int> queue;
	queue.push(1);

	//////////////////////////////////////
	// actual test
	CHECK( !queue.empty() );
}

TEST(ConcurrentQueue, push_adds_element_to_queue)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test
	queue.push(1);
	LONGS_EQUAL(1, queue.spy_queue().size() );
}

TEST(ConcurrentQueue, pop_gets_element_from_queue)
{
	//////////////////////////////////////
	// test initialization
	int i = 0;
	TestWrapper_ConcurrentQueue<int> queue;
	queue.push(1);

	//////////////////////////////////////
	// actual test
	CHECK( !queue.empty() );

	// fetch data
	queue.pop_wait(i);

	CHECK( queue.empty() );
	LONGS_EQUAL(1, i);
}

TEST(ConcurrentQueue, pop_waits_for_timeout_if_queue_is_empty)
{
	//////////////////////////////////////
	// test initialization
	int i;
	int timeout = 100;
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();

	// wait for data
	bool popped = queue.pop_wait(i, timeout);

	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	CHECK_TEXT( runtime >= timeout, "runtime is less than timeout" );
	CHECK_FALSE( popped );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  synchronization tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
static void thread_push_delayed(TestWrapper_ConcurrentQueue<T>* queue, const T i, int64_t delay)
{
	boost::this_thread::sleep_for(boost::chrono::milliseconds(delay));
	queue->push(i);
}

TEST(ConcurrentQueue, pop_waits_for_queue_to_be_filled)
{
	//////////////////////////////////////
	// test initialization
	int i;
	int waittime = 100;
	int tol = 50;
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_push_delayed<int>, &queue, 1, (waittime + tol) ));

	// wait for data
	bool fetched = queue.pop_wait(i);

	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	CHECK_TEXT( runtime >= waittime, "pop_wait() returns befor data were pushed"  );
	CHECK( fetched );
	LONGS_EQUAL(1, i);
}

TEST(ConcurrentQueue, timed_pop_waits_for_queue_to_be_filled)
{
	//////////////////////////////////////
	// test initialization
	int i;
	int timeout = 1000;
	int waittime = 100;
	int tol = 50;
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_push_delayed<int>, &queue, 1, (waittime + tol) ));

	// wait for data
	bool fetched = queue.pop_wait(i, timeout);

	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	CHECK_TEXT( runtime >= waittime, "pop_wait() returns befor data were pushed"  );
	CHECK_TEXT( runtime < timeout, "runtime is greater than timeout"  );
	CHECK( fetched );
	LONGS_EQUAL(1, i);
}

IGNORE_TEST(ConcurrentQueue, empty_should_lock_mutex)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test

	// lock mutex
	queue.spy_mutex().lock();

	// empty() should throw exception
	CHECK_THROWS( ConnectedVision::mutex_error, queue.empty() );
}

IGNORE_TEST(ConcurrentQueue, push_should_lock_mutex)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_ConcurrentQueue<int> queue;

	//////////////////////////////////////
	// actual test

	// lock mutex
	queue.spy_mutex().lock();

	// push() should throw exception
	CHECK_THROWS( ConnectedVision::mutex_error, queue.push(1) );
}

IGNORE_TEST(ConcurrentQueue, pop_should_lock_mutex)
{
	//////////////////////////////////////
	// test initialization
	int i;
	TestWrapper_ConcurrentQueue<int> queue;
	queue.push(1);

	//////////////////////////////////////
	// actual test

	// lock mutex
	queue.spy_mutex().lock();

	// pop_wait() should throw exception
	CHECK_THROWS( ConnectedVision::mutex_error, queue.pop_wait(i) );
}






