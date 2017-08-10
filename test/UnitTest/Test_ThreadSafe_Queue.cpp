/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/chrono.hpp>

#include <ConnectedVision_Thread.h>

#include <CppUTest/TestHarness.h>

template<class T>
class TestWrapper_thread_safe_queue : public ConnectedVision::thread_safe_queue<T>
{
};

TEST_GROUP(thread_safe_queue)
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

TEST(thread_safe_queue, size_returns_zero_on_empty_list)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_queue<int> q;

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( 0, q.size() );
}

TEST(thread_safe_queue, size_returns_number_of_elements_in_list)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_queue<int> q;
	q.push(1);
	q.push(2);
	q.push(3);

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( 3, q.size() );
}

TEST(thread_safe_queue, push_should_add_an_element)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_queue<int> q;

	//////////////////////////////////////
	// actual test
	q.push(1);

	LONGS_EQUAL( 1, q.size() );
}

TEST(thread_safe_queue, try_pop_removes_element_from_queue)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_queue<int> q;
	int val;
	q.push(1);

	//////////////////////////////////////
	// actual test
	CHECK( q.try_pop(val) );

	LONGS_EQUAL( 1, val );
	LONGS_EQUAL( 0, q.size() );
}

TEST(thread_safe_queue, try_pop_waits_for_timeout)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_queue<int> q;
	int val;
	const int64_t timeout = 100;

	//////////////////////////////////////
	// actual test

	auto start = boost::chrono::high_resolution_clock::now();

	CHECK_FALSE( q.try_pop(val, timeout) );

	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	CHECK_TEXT( timeout <= runtime, "try_pop() returns before timeout");
}
