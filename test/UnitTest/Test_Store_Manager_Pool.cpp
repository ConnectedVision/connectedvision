/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_Ringbuffer.h>
#include <DataHandling/Store_Manager_Pool.h>
#include <ConnectedVision_Thread.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_DataHandling.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

/*
* test wrapper for Store_Ringbuffer class
*/
class TestWrapper_Store_Manager_Pool : public Store_Manager_Pool<TestDataClass>
{
public:
	TestWrapper_Store_Manager_Pool(const int64_t storeCount = 5, const int64_t ringbufferSize = 10) : 
		Store_Manager_Pool<TestDataClass>(storeCount, 
			boost::dynamic_pointer_cast< IStore_ReadWrite_Factory<TestDataClass> >( make_shared< Store_Ringbuffer_Factory<TestDataClass> >(ringbufferSize) ))
		{};

		virtual ~TestWrapper_Store_Manager_Pool() {}


	// make public 
	typedef Store_Manager_Pool::StoreStruct StoreStruct;
	
	void init() { Store_Manager_Pool::init(); }
	StoreStruct createStore( const id_t configID ) { return Store_Manager_Pool::createStore(configID); }
	void purgeStore(const Lock &lock) { Store_Manager_Pool::purgeStore(lock); }

	// spy functions
	ConnectedVision::mutex& spy_mapMutex() { return this->mapMutex; }
	std::map< id_t, StoreStruct >& spy_storeMap() { return this->storeMap; }

};

TEST_GROUP(Store_Manager_Pool)
{
	void setup()
	{
		// Init stuff
		configID = "testConfigID";
		otherConfigID = "otherConfigID";
	}

	void teardown()
	{
		// Uninit stuff
	}

	id_t configID;
	id_t otherConfigID;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_Manager_Pool, getReadStore)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	shared_ptr< const IStore_Read<TestDataClass> > store = boost::static_pointer_cast<const IStore_Read<TestDataClass>>(manager.getReadStore(configID));
	CHECK( store );
}

TEST(Store_Manager_Pool, getReadWriteStore)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	shared_ptr< IStore_ReadWrite<TestDataClass> > store = manager.getReadWriteStore(configID);
	CHECK( store );
}

TEST(Store_Manager_Pool, example_usage_of_store_manager)
{
	//////////////////////////////////////
	// module mock-up
	struct
	{
		TestWrapper_Store_Manager_Pool mydataStoreManager;
	} module;
	id_t testID = "testID";
	timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// producer / e.g. worker example
	{
		auto mydataStore = module.mydataStoreManager.getReadWriteStore(configID);
		CHECK( mydataStore );

		// get data object
		auto data = mydataStore->create();
		CHECK( data );

		// fill object
		data->set_configID( configID );
		data->set_id( testID );
		data->set_timestamp( testTimestamp );
		// set other data properties ...

		// save object
		mydataStore->save_const( mydataStore->make_const(data) );
		CHECK_FALSE( data );
	}


	//////////////////////////////////////
	// consumer example
	{
		auto mydataStore = module.mydataStoreManager.getReadStore(configID);
		CHECK( mydataStore );

		// get data by ID
		auto data = mydataStore->getByID( testID );
		CHECK( data );
		CHECK_EQUAL( testID, data->getconst_id() );
		CHECK_EQUAL( configID, data->getconst_configID() );
		LONGS_EQUAL( testTimestamp, data->getconst_timestamp() );
	}

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_Manager_Pool, createStore_should_generate_a_valid_store_pointer)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
 	auto storeStruct = manager.createStore( configID );
	CHECK( storeStruct.store );
}

TEST(Store_Manager_Pool, getReadStore_with_same_configID_should_return_the_same_store)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	auto store = manager.getReadStore(configID);
	auto anotherStore = manager.getReadStore(configID);
	CHECK_EQUAL(store, anotherStore);

	// even if smart pointer is released
	auto rawPtr = store.get();
	store.reset();
	anotherStore.reset();

	// get store again
	store = manager.getReadStore(configID);
	POINTERS_EQUAL( rawPtr, store.get() );
}

TEST(Store_Manager_Pool, getReadWriteStore_with_same_configID_should_return_the_same_store)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	auto store = manager.getReadWriteStore(configID);
	auto anotherStore = manager.getReadWriteStore(configID);
	CHECK_EQUAL(store, anotherStore);

	// even if smart pointer is released
	auto rawPtr = store.get();
	store.reset();
	anotherStore.reset();

	// get store again
	store = manager.getReadWriteStore(configID);
	POINTERS_EQUAL( rawPtr, store.get() );
}

TEST(Store_Manager_Pool, getReadStore_with_different_configID_should_return_other_stores)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	auto store = manager.getReadStore(configID);
	auto otherStore = manager.getReadStore(otherConfigID);
	CHECK(store != otherStore);
}

TEST(Store_Manager_Pool, getReadWriteStore_with_different_configID_should_return_other_stores)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	auto store = manager.getReadWriteStore(configID);
	auto otherStore = manager.getReadWriteStore(otherConfigID);
	CHECK(store != otherStore);
}

TEST(Store_Manager_Pool, purgeStore_should_not_remove_if_there_is_free_space_in_the_map)
{
	//////////////////////////////////////
	// test initialization
	const int storeCount = 2;
	TestWrapper_Store_Manager_Pool manager(storeCount);

	// fill store map with read stores
	for ( int i = 0; (i+1) < storeCount; ++i)
	{
		auto dummyStore = manager.getReadStore(configID + intToStr(i));
	}

	// lock store map
	ConnectedVision::Lock lock( manager.spy_mapMutex() );

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( storeCount-1, manager.spy_storeMap().size() );
	manager.purgeStore(lock);
 	LONGS_EQUAL( storeCount-1, manager.spy_storeMap().size() );
}

TEST(Store_Manager_Pool, purgeStore_should_remove_a_store_to_free_space_in_the_map)
{
	//////////////////////////////////////
	// test initialization
	const int storeCount = 2;
	TestWrapper_Store_Manager_Pool manager(storeCount);

	// fill store map with read stores
	for ( int i = 0; i < storeCount; ++i)
	{
		auto dummyStore = manager.getReadStore(configID + intToStr(i));
	}

	// lock store map
	ConnectedVision::Lock lock( manager.spy_mapMutex() );

	//////////////////////////////////////
	// actual test
 	LONGS_EQUAL( storeCount, manager.spy_storeMap().size() );
	manager.purgeStore(lock);
 	LONGS_EQUAL( storeCount-1 , manager.spy_storeMap().size() );
}

TEST(Store_Manager_Pool, throws_if_all_available_stores_are_used_as_writer)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager(2);

	//////////////////////////////////////
	// actual test
	auto store1 = manager.getReadWriteStore(configID+"1");
	CHECK( store1 );
	auto store2 = manager.getReadWriteStore(configID+"2");
	CHECK( store2 );
	// all available stores in manager are used
	CHECK_THROWS( ConnectedVision::runtime_error, manager.getReadStore(configID+"3") );
	CHECK_THROWS( ConnectedVision::runtime_error, manager.getReadWriteStore(configID+"3") );
}

TEST(Store_Manager_Pool, throws_if_all_available_stores_are_used_as_reader)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager(2);

	//////////////////////////////////////
	// actual test
	auto store1 = manager.getReadStore(configID+"1");
	CHECK( store1 );
	auto store2 = manager.getReadStore(configID+"2");
	CHECK( store2 );
	// all available stores in manager are used
	CHECK_THROWS( ConnectedVision::runtime_error, manager.getReadStore(configID+"3") );
	CHECK_THROWS( ConnectedVision::runtime_error, manager.getReadWriteStore(configID+"3") );
}

TEST(Store_Manager_Pool, remove_read_store_if_unused)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager(2);

	//////////////////////////////////////
	// actual test
	auto store1 = manager.getReadStore(configID+"1");
	CHECK( store1 );
	auto store2 = manager.getReadStore(configID+"2");
	CHECK( store2 );

	// release store
	store2.reset();
	
	// get new read store
	auto store3 = manager.getReadStore(configID+"3");
	CHECK( store3 );

	// release store
	store3.reset();

	// get new write store
	auto store4 = manager.getReadWriteStore(configID+"4");
	CHECK( store4 );
}

TEST(Store_Manager_Pool, remove_write_store_if_unused)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager(2);

	//////////////////////////////////////
	// actual test
	auto store1 = manager.getReadWriteStore(configID+"1");
	CHECK( store1 );
	auto store2 = manager.getReadWriteStore(configID+"2");
	CHECK( store2 );

	// release store
	store2.reset();
	
	// get new read store
	auto store3 = manager.getReadStore(configID+"3");
	CHECK( store3 );

	// release store
	store3.reset();

	// get new write store
	auto store4 = manager.getReadWriteStore(configID+"4");
	CHECK( store4 );
}

TEST(Store_Manager_Pool, synchronization)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_Store_Manager_Pool manager;

	//////////////////////////////////////
	// actual test
	ConnectedVision::Lock lock( manager.spy_mapMutex() );

	CHECK_THROWS( ConnectedVision::mutex_error, manager.getReadStore(configID) );
	CHECK_THROWS( ConnectedVision::mutex_error, manager.getReadWriteStore(configID) );
}

}} // namespace scope

