/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_DataHandling.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

TEST_GROUP(Store_Manager_Ringbuffer_Pool)
{
	void setup()
	{
		// Init stuff
		configID = "testConfigID";
	}

	void teardown()
	{
		// Uninit stuff
	}

	id_t configID;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store_Manager_Ringbuffer_Pool tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(Store_Manager_Ringbuffer_Pool, example_usage_of_store_manager)
{
	static const int64_t storeCount = 2;
	static const int64_t ringbufferSize = 10;
	static const int64_t poolSize = storeCount*ringbufferSize + 5;	

	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	Store_Manager_Ringbuffer_Pool<TestDataClass> mydataStoreManager(
		storeCount,		// number of stores in manager
		ringbufferSize,	// number of element slots in ringbuffer
		poolSize		// total number of available objects (for all ring buffers)
	);

	//////////////////////////////////////
	// producer / e.g. worker example
	{
		auto mydataStore = mydataStoreManager.getReadWriteStore(configID);
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
		auto mydataStore = mydataStoreManager.getReadStore(configID);
		CHECK( mydataStore );

		// get data by ID
		auto data = mydataStore->getByID( testID );
		CHECK( data );
		CHECK_EQUAL( testID, data->getconst_id() );
		CHECK_EQUAL( configID, data->getconst_configID() );
		LONGS_EQUAL( testTimestamp, data->getconst_timestamp() );
	}

}

TEST(Store_Manager_Ringbuffer_Pool, complex_example_usage_of_store_manager)
{
	static const int64_t storeCount = 2;
	static const int64_t ringbufferSize = 10;
	static const int64_t poolSize = storeCount*ringbufferSize + 5;	

	const id_t configID_A = "configID_A";
	const id_t configID_B = "configID_B";
	const id_t configID_C = "configID_C";

	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	Store_Manager_Ringbuffer_Pool<TestDataClass> mydataStoreManager(
		storeCount,		// number of stores in manager
		ringbufferSize,	// number of element slots in ringbuffer
		poolSize		// total number of available objects (for all ring buffers)
	);

	//////////////////////////////////////
	// two workers are running concurrently

	auto writeStore_A = mydataStoreManager.getReadWriteStore(configID_A);
	CHECK( writeStore_A );
	auto writeStore_B = mydataStoreManager.getReadWriteStore(configID_B);
	CHECK( writeStore_B );

	// get & save data object A
	auto data = writeStore_A->create();
	data->set_configID( configID_A ); data->set_id( testID );
	writeStore_A->save_const( writeStore_A->make_const(data) );

	// get & save data object B
	data = writeStore_B->create();
	data->set_configID( configID_B ); data->set_id( testID );
	writeStore_B->save_const( writeStore_B->make_const(data) );

	// the manager has a pool of 2 stores only -> we cannot start a 3rd worker
	CHECK_THROWS( ConnectedVision::runtime_error, mydataStoreManager.getReadWriteStore(configID_C) );

	//////////////////////////////////////
	// but we can get multiple readers to the existing stores

	auto readStore_A1 = mydataStoreManager.getReadStore(configID_A);
	CHECK( readStore_A1 );
	auto readStore_A2 = mydataStoreManager.getReadStore(configID_A);
	CHECK( readStore_A2 );
	auto readStore_B = mydataStoreManager.getReadStore(configID_B);
	CHECK( readStore_B );

	// get data by ID
	auto data_A1 = readStore_A1->getByID( testID );
	CHECK( data_A1 );
	auto data_A2 = readStore_A2->getByID( testID );
	CHECK( data_A2 );
	auto data_B = readStore_B->getByID( testID );
	CHECK( data_B );

	// data_A1 and data_A2 have the same ID and are from different store requests, 
	// but belong to the same config, so they are equal
	CHECK( data_A1 == data_A2 );

	// data_A1 and data_B have the same ID and are from different store requests, 
	// and are from different configs, so they are not equal
	CHECK( data_A1 != data_B );

	//////////////////////////////////////
	// even if we release all stores and data, we can get them again (they are still in the ringbuffer)

	writeStore_A.reset();
	writeStore_B.reset();
	readStore_A1.reset();
	readStore_A2.reset();
	readStore_B.reset();
	data_A1.reset();
	data_A2.reset();
	data_B.reset();

	// get the store again
	readStore_A1 = mydataStoreManager.getReadStore(configID_A);
	CHECK( readStore_A1 );
	// get data by ID
	auto data_A = readStore_A1->getByID( testID );
	CHECK( data_A );
	data_A.reset();

	//////////////////////////////////////
	// now we can get another store

	auto readStore_C = mydataStoreManager.getReadStore(configID_C);
	CHECK( readStore_C );
	readStore_C.reset();

	// store A is still in pool, since we had an active store pointer
	data_A = readStore_A1->getByID( testID );
	CHECK( data_A );
	data_A.reset();

	// but store B has been replaced by store C
	// since store C has been released, we can get a store B pointer, but the ring-buffer is empty
	readStore_B = mydataStoreManager.getReadStore(configID_B);
	CHECK( readStore_B );
	data_B = readStore_B->getByID( testID );
	CHECK_FALSE( data_B );

}

TEST(Store_Manager_Ringbuffer_Pool, create_poolSize_number_of_objects)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	auto store = manager.getReadWriteStore(configID);

	//////////////////////////////////////
	// actual test
	std::vector< shared_ptr<TestDataClass> > usedData;
	for( int i = 0; i < poolSize; ++i)
	{
		auto data = store->create();
		CHECK( data );
		usedData.push_back( data );	// keep shared pointer in use, so that the object cannot be reused by the allocator
	}
}

TEST(Store_Manager_Ringbuffer_Pool, cannot_create_more_elements_than_poolSize)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	auto store = manager.getReadWriteStore(configID);

	std::vector< shared_ptr<TestDataClass> > usedData;
	for( int i = 0; i < poolSize; ++i)
	{
		auto data = store->create();
		usedData.push_back( data );	// keep shared pointer in use, so that the object cannot be reused by the allocator
	}

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( store->create() );
//	CHECK_THROWS( ConnectedVision::runtime_error, store->create() );

}

TEST(Store_Manager_Ringbuffer_Pool, reuse_object_from_allocator)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	auto store = manager.getReadWriteStore(configID);

	std::vector< shared_ptr<TestDataClass> > usedData;
	for( int i = 0; i < poolSize; ++i)
	{
		auto data = store->create();
		usedData.push_back( data );	// keep shared pointer in use, so that the object cannot be reused by the allocator
	}

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( store->create() );

	// release store
	usedData.erase(usedData.begin());

	// get store
	auto data = store->create();
	CHECK( store );
}

TEST(Store_Manager_Ringbuffer_Pool, save_ringbufferSize_objects_to_store)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	auto store = manager.getReadWriteStore(configID);
	std::vector<id_t> idList;

	//////////////////////////////////////
	// actual test
	CHECK( ringbufferSize < poolSize );
	for( int i = 0; i < ringbufferSize; ++i)
	{
		id_t id = "id" + intToStr(i);
		auto data = store->create();
		CHECK( data );
		data->set_configID( configID );
		data->set_id( id );
		idList.push_back( data->getconst_id() );
		auto idSaved = store->save_const( store->make_const(data) );
		CHECK_EQUAL( id, idSaved );
	}

	// read data should have ringbufferSize number of elements
	auto dataList = store->getByIndexRange(0, ringbufferSize + 100);
	LONGS_EQUAL( ringbufferSize, dataList.size() );

	// check ids
	for( int i = 0; i < ringbufferSize; ++i)
	{
		CHECK_EQUAL( idList[i], dataList[i]->getconst_id() );
	}
}

TEST(Store_Manager_Ringbuffer_Pool, save_more_objects_to_store_than_ringbufferSize_wraps_ring_buffer)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	auto store = manager.getReadWriteStore(configID);
	std::vector<id_t> idList;

	for( int i = 0; i < ringbufferSize; ++i)
	{
		id_t id = "id" + intToStr(i);
		auto data = store->create();
		data->set_configID( configID );
		data->set_id( id );
		idList.push_back( data->getconst_id() );
		store->save_const( store->make_const(data) );
	}

	//////////////////////////////////////
	// actual test

	// save next object -> wrap ringbuffer
	auto data = store->create();
	data->set_configID( configID );
	data->set_id( "idXXX" );
	idList.erase( idList.begin() );
	idList.push_back( data->getconst_id() );
	store->save_const( store->make_const(data) );

	// read data should have ringbufferSize number of elements
	auto dataList = store->getByIndexRange(0, ringbufferSize + 100);
	LONGS_EQUAL( ringbufferSize, dataList.size() );

	// check ids
	for( int i = 0; i < ringbufferSize; ++i)
	{
		CHECK_EQUAL( idList[i], dataList[i]->getconst_id() );
	}
}

TEST(Store_Manager_Ringbuffer_Pool, get_storeCount_stores_from_store_manager)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	std::vector< shared_ptr<IStore_Read<TestDataClass>> > usedData;

	//////////////////////////////////////
	// actual test
	for( int i = 0; i < storeCount; ++i)
	{
		id_t configID = "configID" + intToStr(i);
		auto store = manager.getReadStore(configID);
		CHECK( store );
		usedData.push_back( store );	// keep shared pointer in use, so that the store cannot be reused
	}
}

TEST(Store_Manager_Ringbuffer_Pool, cannot_get_more_stores_from_manager_than_storeCount)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	std::vector< shared_ptr<IStore_Read<TestDataClass>> > usedData;

	for( int i = 0; i < storeCount; ++i)
	{
		id_t configID = "configID" + intToStr(i);
		auto store = manager.getReadStore(configID);
		usedData.push_back( store );	// keep shared pointer in use, so that the store cannot be reused
	}

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, manager.getReadStore(configID) );
}

TEST(Store_Manager_Ringbuffer_Pool, reuse_store)
{
	//////////////////////////////////////
	// test initialization
	const int64_t storeCount = 2;
	const int64_t ringbufferSize = 10;
	const int64_t poolSize = storeCount*ringbufferSize + 5;	
	Store_Manager_Ringbuffer_Pool<TestDataClass> manager(storeCount, ringbufferSize, poolSize);
	std::vector< shared_ptr<IStore_Read<TestDataClass>> > usedData;

	for( int i = 0; i < storeCount; ++i)
	{
		id_t configID = "configID" + intToStr(i);
		auto store = manager.getReadStore(configID);
		usedData.push_back( store );	// keep shared pointer in use, so that the store cannot be reused
	}

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, manager.getReadStore(configID) );

	// release store
	usedData.erase(usedData.begin());

	// get store
	auto store = manager.getReadStore(configID);
	CHECK( store );
}

}} // namespace scope

