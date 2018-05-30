/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_Ringbuffer.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_DataHandling.hpp"
#include "MixIn_IStore.h"

namespace ConnectedVision 
{ namespace DataHandling
{

static StoreEnvironment<TestDataClass> env;

/*
* test wrapper for Store_Ringbuffer class
*/
class TestWrapper_Store_Ringbuffer : public Store_Ringbuffer<TestDataClass>
{
public:
	TestWrapper_Store_Ringbuffer(const int size = 10) : 
		Store_Ringbuffer<TestDataClass>(env.configID, size),
		initSize(size)
		{};
	virtual ~TestWrapper_Store_Ringbuffer() {};

	/**
	* save a single object
	*	This function is OPTIONAL.
	*  The default implementation will make copy of the object so that it will not be
	*  modified once it is in the store.
	*
	* @param obj			data object
	*/
	virtual id_t save_copy(const ConnectedVision::shared_ptr<TestDataClass> obj)
	{
		// make copy of the object, not just the pointer
		const ConnectedVision::shared_ptr<const TestDataClass> constObj = ConnectedVision::make_shared<const TestDataClass>(*obj);
		return this->save_const(constObj); // call const version of save
	}


	// test helper functions
	boost::shared_mutex& spy_containerMutex()
	{
		return this->containerMutex;
	}
	int64_t& spyBufferSize() { return bufferSize; }
	int64_t& spyBufferFirstPos() { return bufferFirstPos; }
	int64_t& spyBufferLastPos() { return bufferLastPos; }

	const int initSize;
};

TEST_GROUP(Store_Ringbuffer)
{
	void setup()
	{
		// Init stuff

		// init store
		storePtr = make_shared<TestWrapper_Store_Ringbuffer>();
	}

	void teardown()
	{
		// Uninit stuff
	}

	TestWrapper_Store_Ringbuffer& store() { return *storePtr; }

	shared_ptr<TestWrapper_Store_Ringbuffer> storePtr;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIXIN_APPLY(Store_Ringbuffer, MixIn_IStore, IStore_tests)
{
	params.env = &env;
	params.store = boost::static_pointer_cast< IStore_ReadWrite<TestDataClass> >(storePtr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific Store_Ringbuffer tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_Ringbuffer, initStore)
{
	//////////////////////////////////////
	// test initialization
	const int initSize = 10;
	Store_Ringbuffer<TestDataClass> store(env.configID, initSize);

	//////////////////////////////////////
	// actual test

	TestWrapper_Store_Ringbuffer::Stats stats = store.getStats();
	LONGS_EQUAL(initSize, stats.size);
	LONGS_EQUAL(0, stats.entriesUsed);
	LONGS_EQUAL(-1, stats.firstIndex);
	LONGS_EQUAL(-1, stats.lastIndex);
	LONGS_EQUAL(-1, stats.firstTimestamp);
	LONGS_EQUAL(-1, stats.lastTimestamp);

	// custom allocator
	ConnectedVision::shared_ptr< IDataAllocator<TestDataClass> > allocatorNULL;
	CHECK_THROWS(ConnectedVision::runtime_error, Store_Ringbuffer<TestDataClass>(env.configID, initSize, allocatorNULL) );
	ConnectedVision::shared_ptr< IDataAllocator<TestDataClass> > allocator = boost::static_pointer_cast<IDataAllocator<TestDataClass>>(ConnectedVision::make_shared< DataAllocator_Primitive<TestDataClass> >());
	Store_Ringbuffer<TestDataClass> storeAlloc(env.configID, initSize, allocator);
}

TEST(Store_Ringbuffer, saveStats)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestDataClass> data;
	TestWrapper_Store_Ringbuffer::Stats stats;

	TestWrapper_Store_Ringbuffer store;

	//////////////////////////////////////
	// actual test
	const timestamp_t testTime = 12345;

	// add first element
	data.reset(new TestDataClass);
	data->set_timestamp(testTime);
	data->set_id( intToStr(1) );
	data->set_configID( env.configID );
	store.save_copy(data);
	
	stats = store.getStats();
	LONGS_EQUAL(1, stats.entriesUsed);
	LONGS_EQUAL(0, stats.firstIndex);
	LONGS_EQUAL(0, stats.lastIndex);
	LONGS_EQUAL(testTime, stats.firstTimestamp);
	LONGS_EQUAL(testTime, stats.lastTimestamp);


	// add second element
	data.reset(new TestDataClass);
	data->set_timestamp(testTime);
	data->set_id( intToStr(2) );
	data->set_configID( env.configID );
	store.save_copy(data);
	
	stats = store.getStats();
	LONGS_EQUAL(2, stats.entriesUsed);
	LONGS_EQUAL(0, stats.firstIndex);
	LONGS_EQUAL(1, stats.lastIndex);
	LONGS_EQUAL(testTime, stats.firstTimestamp);
	LONGS_EQUAL(testTime, stats.lastTimestamp);
}

TEST(Store_Ringbuffer, resetIndex_sets_index_for_next_element)
{
	//////////////////////////////////////
	// test initialization
	const int64_t index = 100;
	const timestamp_t testTime = 12345;

	TestWrapper_Store_Ringbuffer store;

	ConnectedVision::shared_ptr<TestDataClass> data(new TestDataClass);
	data->set_timestamp(testTime);
	data->set_id( intToStr(1) );
	data->set_configID( env.configID );

	//////////////////////////////////////
	// actual test
	store.resetIndex(index);

	// start index is set, but no data in ringbuffer
	auto range = store.getDataRange();
	LONGS_EQUAL( range.INDEX_NA, range.indexStart );
	LONGS_EQUAL( range.INDEX_NA, range.indexEnd );

	// add first element
	store.save_copy(data);

	// check index
	range = store.getDataRange();
	LONGS_EQUAL( index, range.indexStart );
	LONGS_EQUAL( index, range.indexEnd );
}

TEST(Store_Ringbuffer, resetIndex_calls_deleteAll)
{
	//////////////////////////////////////
	// test initialization
	const int64_t index = 100;
	ConnectedVision::shared_ptr<TestDataClass> data;
	TestWrapper_Store_Ringbuffer::Stats stats;

	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 10);

	//////////////////////////////////////
	// actual test
	store.resetIndex(index);
	
	auto range = store.getDataRange();
	LONGS_EQUAL( -1, range.indexStart );
	LONGS_EQUAL( -1, range.indexEnd );
	LONGS_EQUAL( -1, range.timestampStart );
	LONGS_EQUAL( -1, range.timestampEnd );
}

TEST(Store_Ringbuffer, readonlyElements)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestDataClass> data;

	TestWrapper_Store_Ringbuffer store;

	//////////////////////////////////////
	// actual test
	const timestamp_t testTime = 12345;

	// add element
	data.reset(new TestDataClass);
	data->set_timestamp(testTime);
	data->set_id( intToStr(1) );
	data->set_configID( env.configID );
	store.save_copy(data);

	// modify element
	data->set_timestamp(testTime +1);

	// read element
	ConnectedVision::shared_ptr<const TestDataClass> readData = store.getByIndex(0);
	CHECK(readData);
	LONGS_EQUAL(testTime, readData->getconst_timestamp());
}

TEST(Store_Ringbuffer, wrappAround)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 15);
	int removed = (int)(dataList.size() - store.initSize);
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);
	ConnectedVision::shared_ptr<TestDataClass> data;
	TestWrapper_Store_Ringbuffer::Stats stats;

	//////////////////////////////////////
	// actual test

	// check store stats
	stats = store.getStats();
	LONGS_EQUAL(store.initSize, stats.entriesUsed);
	LONGS_EQUAL(removed, stats.firstIndex);
	LONGS_EQUAL(store.initSize + removed-1, stats.lastIndex);
	LONGS_EQUAL(dataList[0]->getconst_timestamp(), stats.firstTimestamp);
	LONGS_EQUAL(dataList[dataList.size()-1]->getconst_timestamp(), stats.lastTimestamp);
	auto ids = store.getIDList();
	LONGS_EQUAL(store.initSize, ids.size());
	for( int i = 0; i < store.initSize; ++i)
	{
		CHECK_EQUAL(dataList[i]->getconst_id(), ids.at(i));
	}

}

TEST(Store_Ringbuffer, getByIndexRange_WrappedRingbuffer)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 15);
	int removed = dataList.size() - store.initSize;
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = store.getByIndexRange(0, 100);
	LONGS_EQUAL( store.initSize, vec.size() );

	vec = store.getByIndexRange(0, 0);
	LONGS_EQUAL( 0, vec.size() );

	vec = store.getByIndexRange(5, 6);
	LONGS_EQUAL( 2, vec.size() );

	vec = store.getByIndexRange(7, 11);
	LONGS_EQUAL( 5, vec.size() );

	vec = store.getByIndexRange(13, 14);
	LONGS_EQUAL( 2, vec.size() );

	vec = store.getByIndexRange(15, 100);
	LONGS_EQUAL( 0, vec.size() );
}

TEST(Store_Ringbuffer, getByTimestamp_FoundWrappedRingbuffer)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 15);
	int removed = dataList.size() - store.initSize;
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);
	std::vector<ConnectedVision::shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = store.getByTimestamp(testTime);
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	// underrun
	vec = store.getByTimestamp(env.startTime - 1000);
	LONGS_EQUAL( 0, vec.size() );

	// overrun
	vec = store.getByTimestamp(env.endTime + 1000);
	LONGS_EQUAL( 0, vec.size() );

}

TEST(Store_Ringbuffer, getBeforeTimestamp_FoundWrappedRingbuffer)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 15);
	int removed = dataList.size() - store.initSize;
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = store.getBeforeTimestamp( testTime + 10 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	testTime = dataList[8]->getconst_timestamp();
	vec = store.getBeforeTimestamp( testTime + 5 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
}

TEST(Store_Ringbuffer, getAfterTimestamp_FoundWrappedRingbuffer)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 15);
	int removed = dataList.size() - store.initSize;
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = store.getAfterTimestamp( testTime - 10 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	testTime = dataList[8]->getconst_timestamp();
	vec = store.getAfterTimestamp( testTime - 5 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
}

TEST(Store_Ringbuffer, getAllInTimespan_FoundWrappedRingbuffer)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, 15);
	int removed = dataList.size() - store.initSize;
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[4]->getconst_timestamp();
	vec = store.getAllInTimespan( testTime, testTime );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	vec = store.getAllInTimespan( testTime, testTime + 10 );
	LONGS_EQUAL( 2, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	LONGS_EQUAL( testTime + 10, vec.at(1)->getconst_timestamp() );

	vec = store.getAllInTimespan( testTime - 5, testTime + 15 );
	LONGS_EQUAL( 2, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	LONGS_EQUAL( testTime + 10, vec.at(1)->getconst_timestamp() );

	testTime = dataList[0]->getconst_timestamp();
	vec = store.getAllInTimespan( 0, testTime - 100 );
	LONGS_EQUAL( 0, vec.size() );
	vec = store.getAllInTimespan( 0, testTime );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	testTime = dataList[9]->getconst_timestamp();
	vec = store.getAllInTimespan( testTime + 100, 1000000 );
	LONGS_EQUAL( 0, vec.size() );
	vec = store.getAllInTimespan( testTime, 1000000 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
}

TEST(Store_Ringbuffer, getXXXTimestamp_UnorderedTimestamps)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Ringbuffer store;
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vec;

	// add elements with unordered timestamps
	std::vector<ConnectedVision::shared_ptr<const TestDataClass> > dataList;
	for (int i = 0; i< 15; i++ )
	{
		auto data = env.makeConstData(i, env.startTime - i*10);
		store.save_const(data);
		dataList.push_back(data);
	}
	int removed = dataList.size() - store.initSize;
	if ( removed > 0 )
		dataList.erase(dataList.begin(), dataList.begin() + removed);

	//////////////////////////////////////
	// actual test
	int testIdx;
	timestamp_t testTime;

	// get element by timestamp
	testIdx = 2;
	testTime = dataList[testIdx]->getconst_timestamp();
	vec = store.getByTimestamp( testTime );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	CHECK_EQUAL( dataList[testIdx]->getconst_id(), vec.at(0)->getconst_id() );

	// get element with lowest timestamp
	testIdx = 9;
	testTime = dataList[testIdx]->getconst_timestamp();
	vec = store.getAfterTimestamp( testTime - 1000 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	CHECK_EQUAL( dataList[testIdx]->getconst_id(), vec.at(0)->getconst_id() );

	// get element with highest timestamp
	testIdx = 0;
	testTime = dataList[testIdx]->getconst_timestamp();
	vec = store.getBeforeTimestamp( testTime + 1000 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	CHECK_EQUAL( dataList[testIdx]->getconst_id(), vec.at(0)->getconst_id() );

	// get elements within timespan
	testIdx = 2;
	testTime = dataList[testIdx]->getconst_timestamp();
	vec = store.getAllInTimespan( testTime, testTime + 10 );
	LONGS_EQUAL( 2, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	LONGS_EQUAL( testTime + 10, vec.at(1)->getconst_timestamp() );
}

TEST(Store_Ringbuffer, synchronization_readLock)
{
	//////////////////////////////////////
	// test initialization

	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, (size_t)store.initSize);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vec;
	ConnectedVision::shared_ptr<const TestDataClass> data = env.makeConstData(1);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vecSave; vecSave.push_back( env.makeConstData(2) );
	TestWrapper_Store_Ringbuffer::Stats stats;

	//////////////////////////////////////
	// actual test

	// reader lock
	TestWrapper_Store_Ringbuffer::ReadLock lock( store.spy_containerMutex() );
	int testIndex = 5;

	ConnectedVision::shared_ptr<const TestDataClass> readData = store.getByID(dataList[testIndex]->getconst_id());
	CHECK_EQUAL( dataList[testIndex]->getconst_id(), readData->getconst_id() );

	readData = store.getByIndex(testIndex);
	CHECK_EQUAL( dataList[testIndex]->getconst_id(), readData->getconst_id() );

	vec = store.getByIndexRange(0, 100);
	LONGS_EQUAL( store.initSize, vec.size() );

	vec = store.getByTimestamp(dataList[testIndex]->getconst_timestamp());
	LONGS_EQUAL( 1, vec.size() );

	vec = store.getBeforeTimestamp(dataList[testIndex]->getconst_timestamp() +1);
	LONGS_EQUAL( 1, vec.size() );

	vec = store.getAfterTimestamp(dataList[testIndex]->getconst_timestamp() -1);
	LONGS_EQUAL( 1, vec.size() );

	vec = store.getAllInTimespan(dataList[testIndex]->getconst_timestamp(),dataList[testIndex]->getconst_timestamp());
	LONGS_EQUAL( 1, vec.size() );

	stats = store.getStats();
	LONGS_EQUAL( store.initSize, stats.size );

	CHECK_THROWS( ConnectedVision::runtime_error, store.save_const(data) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.save_constVector(vecSave) );
}

TEST(Store_Ringbuffer, synchronization_writeLock)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Ringbuffer store;
	auto dataList = env.fillStoreWithData(store, (size_t)store.initSize);
	const ConnectedVision::shared_ptr<const TestDataClass> data = env.makeConstData(1);
	std::vector< ConnectedVision::shared_ptr<const TestDataClass> > vecSave; vecSave.push_back( env.makeConstData(2) );

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = env.startTime;

	TestWrapper_Store_Ringbuffer::WriteLock lock( store.spy_containerMutex() );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getByID("???") );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getByIndex(5) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getByIndexRange(0, 100) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getByTimestamp(testTime) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getBeforeTimestamp(testTime +1) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getAfterTimestamp(testTime -1) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getAllInTimespan(testTime,testTime) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.getStats() );

	CHECK_THROWS( ConnectedVision::runtime_error, store.save_const(data) );

	CHECK_THROWS( ConnectedVision::runtime_error, store.save_constVector(vecSave) );
}

TEST(Store_Ringbuffer, virtual_desctuctor_of_read_store_should_be_called)
{
	//////////////////////////////////////
	// test initialization
	shared_ptr<const IStore_Read<TestDataClass>> readStore;

	//////////////////////////////////////
	// actual test
	{
		auto store = ConnectedVision::make_shared< Store_Ringbuffer<TestDataClass> >(env.configID, 10);
		readStore = boost::dynamic_pointer_cast< const IStore_Read<TestDataClass> >(store);
		store.reset();
	}

	CHECK( readStore );
	CHECK( readStore.unique() );
}

TEST(Store_Ringbuffer, virtual_desctuctor_of_write_store_should_be_called)
{
	//////////////////////////////////////
	// test initialization
	shared_ptr<const IStore_ReadWrite<TestDataClass>> writeStore;
	ConnectedVision::shared_ptr< IDataAllocator<TestDataClass> > allocator = boost::static_pointer_cast<IDataAllocator<TestDataClass>>(make_shared<TestWrapper_DataAllocator>());

	//////////////////////////////////////
	// actual test
	{
		ConnectedVision::shared_ptr< Store_Ringbuffer<TestDataClass> > store = boost::make_shared< Store_Ringbuffer<TestDataClass> >(env.configID, 10, allocator);
		writeStore = boost::dynamic_pointer_cast< const IStore_ReadWrite<TestDataClass> >(store);
		store.reset();
	}

	CHECK( writeStore );
	CHECK( writeStore.unique() );
}

}} // namespace scope

