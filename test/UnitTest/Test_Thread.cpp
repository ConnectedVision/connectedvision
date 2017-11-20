/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/scoped_thread.hpp>
#include <boost/atomic.hpp>

#include <ConnectedVision_Thread.h>

#include <CppUTest/TestHarness.h>

static void sleep( uint64_t time )
{
	boost::this_thread::sleep_for(boost::chrono::milliseconds( time ));
}

class TestProgressDataClass
{
public:
	// init constructor
	TestProgressDataClass(int i) : val(i) 
	{
		int blocktime = constructorBlockTime.load(boost::memory_order_acquire);
		++constructorCount;

		// block constructor
		if ( blocktime )
			sleep( (uint64_t)blocktime );
	}

	// copy constructor
	TestProgressDataClass(const TestProgressDataClass& other)
	{
		int blocktime = copyConstructorBlockTime.load(boost::memory_order_acquire);
		++copyConstructorCount;
		val = other.val;

		// block copy constructor
		if ( blocktime )
			sleep( (uint64_t)blocktime );
	}

	// move constructor
	TestProgressDataClass(TestProgressDataClass&& other)
	{
		++moveConstructorCount;
		val = other.val;
	}

	// assignment operator
	TestProgressDataClass& operator=(const TestProgressDataClass& other) 
	{
		int blocktime = assignmentBlockTime.load(boost::memory_order_acquire);
		++assignmentCount;
		val = other.val;

		// block copy constructor
		if ( blocktime )
			sleep( (uint64_t)blocktime );

		return *this;
	}

	int operator()() const { return val; }

	// static functions
	static boost::atomic<int> constructorCount;
	static boost::atomic<int> copyConstructorCount;
	static boost::atomic<int> moveConstructorCount;
	static boost::atomic<int> assignmentCount;
	static boost::atomic<int> constructorBlockTime;
	static boost::atomic<int> copyConstructorBlockTime;
	static boost::atomic<int> assignmentBlockTime;
	static void resetStat()
	{
		constructorCount = 0;
		copyConstructorCount = 0;
		moveConstructorCount = 0;
		assignmentCount = 0;

		constructorBlockTime = 0;
		copyConstructorBlockTime = 0;
		assignmentBlockTime = 0;
	}
private:
	int val;
};
bool operator< (const TestProgressDataClass &a, const TestProgressDataClass &b)
{
	return a() < b();
}
boost::atomic<int> TestProgressDataClass::constructorCount(0);
boost::atomic<int> TestProgressDataClass::copyConstructorCount(0);
boost::atomic<int> TestProgressDataClass::moveConstructorCount(0);
boost::atomic<int> TestProgressDataClass::assignmentCount(0);
boost::atomic<int> TestProgressDataClass::constructorBlockTime(0);
boost::atomic<int> TestProgressDataClass::copyConstructorBlockTime(0);
boost::atomic<int> TestProgressDataClass::assignmentBlockTime(0);

template<class T>
class TestWrapper_thread_safe_progress : public ConnectedVision::thread_safe_progress<T>
{
public:
	TestWrapper_thread_safe_progress(const T& val) : ConnectedVision::thread_safe_progress<T>(val) {}

	boost::condition_variable& spy_cond() { return ConnectedVision::thread_safe_progress<T>::cond; }
	boost::mutex& spy_mutex() { return ConnectedVision::thread_safe_progress<T>::mutex; }
};

TEST_GROUP(thread_safe_progress)
{
	void setup()
	{
		// Init stuff
		TestProgressDataClass::resetStat();
	}

	void teardown()
	{
		// Uninit stuff
	}
};

TEST(thread_safe_progress, handles_custom_class)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::thread_safe_progress<TestProgressDataClass> a(1);
	LONGS_EQUAL( 1, a.get()() );

	ConnectedVision::thread_safe_progress<TestProgressDataClass> b(a);
	LONGS_EQUAL( 1, b.get()() );
}

TEST(thread_safe_progress, copy_constructor_copies_data_value)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::thread_safe_progress<int> a(1);
	ConnectedVision::thread_safe_progress<int> b(a);
	LONGS_EQUAL( a.get(), b.get() );
	LONGS_EQUAL( 1, b.get() );
}

TEST(thread_safe_progress, get_should_return_value)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::thread_safe_progress<int> a(1);
	LONGS_EQUAL( 1, a.get() );
}

TEST(thread_safe_progress, set_should_set_value)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::thread_safe_progress<int> a(1);
	a.set(2);
	LONGS_EQUAL( 2, a.get() );
}

TEST(thread_safe_progress, set_should_enforce_strict_increase_values)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::thread_safe_progress<int> a(1);
	a.set(2);
	a.set(2); // OK
	CHECK_THROWS( ConnectedVision::sequence_exception, a.set(1) );
}

TEST(thread_safe_progress, assignment_from_raw_data_type)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);

	//////////////////////////////////////
	// actual test
	int i = 2;
	a = i;

	LONGS_EQUAL( i, a.get() );
}

TEST(thread_safe_progress, assignment_to_raw_data_type)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);

	//////////////////////////////////////
	// actual test
	int i = 0;
	i = a;

	LONGS_EQUAL( a.get(), i );
}

TEST(thread_safe_progress, wait_until_should_return_immediately_if_fullfilled)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);

	//////////////////////////////////////
	// actual test

	a.set(10);
	a.wait_until(5); // wait for previous match
	a.wait_until(10); // wait for exact match

	LONGS_EQUAL( 10, a.get() );
}

TEST(thread_safe_progress, wait_until_should_timeout)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int timeout = 10;
	int tol = 50;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();

	a.wait_until(10, timeout);

	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
	
	CHECK( runtime < (timeout + tol) );
}

TEST(thread_safe_progress, set_calls_constructor_once)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<TestProgressDataClass> a(0);
	TestProgressDataClass x(1);
	TestProgressDataClass::resetStat();

	//////////////////////////////////////
	// actual test
	a.set(x);
	LONGS_EQUAL( 0, TestProgressDataClass::constructorCount );
	LONGS_EQUAL( 0, TestProgressDataClass::copyConstructorCount );
	LONGS_EQUAL( 0, TestProgressDataClass::moveConstructorCount );
	LONGS_EQUAL( 1, TestProgressDataClass::assignmentCount );
}

TEST(thread_safe_progress, get_calls_copy_and_move_constructor_once)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<TestProgressDataClass> a(0);
	TestProgressDataClass::resetStat();

	//////////////////////////////////////
	// actual test
	a.get();
	LONGS_EQUAL( 0, TestProgressDataClass::constructorCount );
	LONGS_EQUAL( 1, TestProgressDataClass::copyConstructorCount );
#ifndef _DEBUG
	// the compiler return value optimization should remove the move() operation in release configuration
	LONGS_EQUAL( 0, TestProgressDataClass::moveConstructorCount );
#endif
	LONGS_EQUAL( 0, TestProgressDataClass::assignmentCount );

}

TEST(thread_safe_progress, wait_while_should_return_immediately_if_not_current_state)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(10);

	//////////////////////////////////////
	// actual test
	a.wait_while(5); // does not match current state
	a.wait_while(15); // does not match current state

	CHECK( true );
}

TEST(thread_safe_progress, wait_while_should_timeout)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int timeout = 10;
	int tol = 50;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();

	a.wait_while(1, timeout);

	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
	
	CHECK( runtime < (timeout + tol) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  synchronization tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
static void thread_set_delayed(ConnectedVision::thread_safe_progress<T>* a, const T val, int64_t delay)
{
	sleep(delay);
	a->set(val);
}
template<typename T>
static void thread_get_delayed(ConnectedVision::thread_safe_progress<T>* a, int64_t delay)
{
	sleep(delay);
	T val = a->get();
}
template<typename T>
static void thread_reset_delayed(ConnectedVision::thread_safe_progress<T>* a, const T val, int64_t delay)
{
	sleep(delay);
	a->reset(val);
}
template<typename T>
static void thread_wait_until_timeout(ConnectedVision::thread_safe_progress<T>* a, const T val, int64_t timeout)
{
	a->wait_until(val, timeout);
}

TEST(thread_safe_progress, wait_until_should_wait_until_progress_has_been_reached)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int waittime = 20;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_set_delayed<int>, &a, 10, waittime ));
	a.wait_until(10);
	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
	t.interrupt(); t.join();
	LONGS_EQUAL( 10, a.get() );
	CHECK( runtime >= waittime );
}

TEST(thread_safe_progress, wait_while_should_wait_for_the_progress_to_change)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int waittime = 20;

	//////////////////////////////////////
	// actual test
	auto start = boost::chrono::high_resolution_clock::now();
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_set_delayed<int>, &a, 10, waittime ));
	a.wait_while(1);
	auto end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();
	t.interrupt(); t.join();
	LONGS_EQUAL( 10, a.get() );
	CHECK( runtime >= waittime );
}

TEST(thread_safe_progress, set_notifies_all_waiting_threads)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int timeout = 1000;

	//////////////////////////////////////
	// actual test
	
	// start waiting threads
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t1(boost::thread( thread_wait_until_timeout<int>, &a, 10, timeout*10 ));
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t2(boost::thread( thread_wait_until_timeout<int>, &a, 10, timeout*10 ));
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t3(boost::thread( thread_wait_until_timeout<int>, &a, 10, timeout*10 ));

	// set and notify threads
	a.set(10);

	// force task switch and give threads a chance to terminate
	sleep(1);

	// all threads should join immediately
	CHECK( t1.try_join_for(boost::chrono::milliseconds(timeout)) );
	CHECK( t2.try_join_for(boost::chrono::milliseconds(timeout)) );
	CHECK( t3.try_join_for(boost::chrono::milliseconds(timeout)) );
}

static boost::scoped_thread<boost::interrupt_and_join_if_joinable> async_set_blocked(ConnectedVision::thread_safe_progress<TestProgressDataClass>& a, int i, int64_t blocktime)
{
	TestProgressDataClass::resetStat();

	// start thread, call set() to block mutex
	TestProgressDataClass::assignmentBlockTime = static_cast<int>(blocktime);
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_set_delayed<TestProgressDataClass>, &a, i, 0));

	// wait for thread to call assignment
	while ( TestProgressDataClass::assignmentCount.load(boost::memory_order_acquire) == 0 ) {/* spinlock / busy-wait */}
	TestProgressDataClass::assignmentBlockTime = 0; // reset block time

	return std::move(t);
}
static boost::scoped_thread<boost::interrupt_and_join_if_joinable> async_get_blocked(ConnectedVision::thread_safe_progress<TestProgressDataClass>& a, int64_t blocktime)
{
	TestProgressDataClass::resetStat();

	// start thread, call get() to block mutex
	TestProgressDataClass::copyConstructorBlockTime = static_cast<int>(blocktime);
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_get_delayed<TestProgressDataClass>, &a, 0));

	// wait for thread to call constructor
	while ( TestProgressDataClass::copyConstructorCount.load(boost::memory_order_acquire) == 0 ) {/* spinlock / busy-wait */}
	TestProgressDataClass::copyConstructorBlockTime = 0; // reset block time

	return std::move(t);
}

TEST(thread_safe_progress, get_should_lock_mutex)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_progress<TestProgressDataClass> a(0);

	//////////////////////////////////////
	// actual test

	// call get and block
	auto blocktime = 20; // block time in ms
	auto t = async_get_blocked(a, blocktime);

	// make sure that mutex is locked
	boost::unique_lock<boost::mutex> lock(a.spy_mutex(), boost::try_to_lock);
	CHECK( !lock );
}

TEST(thread_safe_progress, set_should_lock_mutex)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_progress<TestProgressDataClass> a(0);

	//////////////////////////////////////
	// actual test

	// call get and block
	auto blocktime = 20; // block time in ms
	auto t = async_set_blocked(a, 1, blocktime);

	// make sure that mutex is locked
	boost::unique_lock<boost::mutex> lock(a.spy_mutex(), boost::try_to_lock);
	CHECK( !lock );
}

TEST(thread_safe_progress, get_with_concurrent_set_is_thread_safe)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_progress<TestProgressDataClass> a(0);

	// measure time for uninterrupted set
	auto start = boost::chrono::high_resolution_clock::now();
	a.set(1);
	auto end = boost::chrono::high_resolution_clock::now();
	auto runtimeSet = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	// measure time for uninterrupted get
	start = boost::chrono::high_resolution_clock::now();
	a.get();
	end = boost::chrono::high_resolution_clock::now();
	auto runtimeGet = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	// compute block time
	auto blocktime = runtimeGet*10 + 20; // block time in ms
	TestProgressDataClass::resetStat();

	//////////////////////////////////////
	// actual test

	// start thread, call set() to block mutex
	start = boost::chrono::high_resolution_clock::now();
	auto t = async_set_blocked(a, 2, blocktime);

	// make sure that mutex is locked
	boost::unique_lock<boost::mutex> lock(a.spy_mutex(), boost::try_to_lock);
	CHECK_TEXT( !lock , "mutex should be locked by other thread" );

	// check runtime for get, should wait until block thread has finished ( >= blocktime )
	a.get();
	end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	CHECK_TEXT( runtime >= blocktime, "get() does not wait for set() to finished" );
}

TEST(thread_safe_progress, set_with_concurrent_get_is_thread_safe)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_thread_safe_progress<TestProgressDataClass> a(0);

	// measure time for uninterrupted set
	auto start = boost::chrono::high_resolution_clock::now();
	a.set(1);
	auto end = boost::chrono::high_resolution_clock::now();
	auto runtimeSet = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	// measure time for uninterrupted get
	start = boost::chrono::high_resolution_clock::now();
	a.get();
	end = boost::chrono::high_resolution_clock::now();
	auto runtimeGet = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	// compute block time
	auto blocktime = runtimeSet*10 + 20; // block time in ms
	TestProgressDataClass::resetStat();

	//////////////////////////////////////
	// actual test

	// start thread, call set() to block mutex
	start = boost::chrono::high_resolution_clock::now();
	auto t = async_get_blocked(a, blocktime);

	// make sure that mutex is locked
	boost::unique_lock<boost::mutex> lock(a.spy_mutex(), boost::try_to_lock);
	CHECK_TEXT( !lock , "mutex should be locked by other thread" );

	// check runtime for get, should wait until block thread has finished ( >= blocktime )
	a.set(2);
	end = boost::chrono::high_resolution_clock::now();
	auto runtime = boost::chrono::duration_cast<boost::chrono::milliseconds>(end - start).count();

	CHECK_TEXT( runtime >= blocktime, "set() does not wait for get() to finished" );
}

TEST(thread_safe_progress, wait_until_throws_on_reset)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int waittime = 20;

	//////////////////////////////////////
	// actual test
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_reset_delayed<int>, &a, 0, waittime ));

	CHECK_THROWS( ConnectedVision::sequence_exception, a.wait_until(10) );
}

TEST(thread_safe_progress, wait_while_returns_on_reset)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int waittime = 20;

	//////////////////////////////////////
	// actual test
	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_reset_delayed<int>, &a, 0, waittime ));

	CHECK( a.wait_while(1) );
}

TEST(thread_safe_progress, wait_until_after_reset)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::thread_safe_progress<int> a(1);
	int waittime = 20;

	//////////////////////////////////////
	// actual test
	a.reset(0);

	boost::scoped_thread<boost::interrupt_and_join_if_joinable> t(boost::thread( thread_set_delayed<int>, &a, 10, waittime ));

	CHECK( a.wait_until(1) );
}


