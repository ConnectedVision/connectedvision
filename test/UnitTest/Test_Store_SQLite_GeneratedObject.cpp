/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "generated/Store_Manager_SQLite_UnitTest_GeneratorTestCode.h"

#include <CppUTest/TestHarness.h>

#include "TestHelper_StoreEnvironment.hpp"

namespace ConnectedVision {
namespace UnitTest {

namespace DataHandling {

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_SQLite_GeneratedObject.db"

TEST_GROUP(Store_SQLite_GeneratedObject)
{
	void setup()
	{
		// Init stuff
		configID = "testConfigID";

#ifdef UseFileDB
		db.init(UseFileDB, SQLITE_OPEN_CREATE);
		
		// delete existing data
		{
		scoped_db_lock lock(db);
		std::string sql = std::string("DROP TABLE IF EXISTS GeneratorTestCode");
		sqlite3_exec(lock.db, sql.c_str(), NULL, NULL, NULL);
		}
#else
		db.init(":memory:", SQLITE_OPEN_CREATE);
#endif

		// init store
		storePtr = ConnectedVision::make_shared<DataHandling::Store_SQLite_UnitTest_GeneratorTestCode>(configID, db);
	}

	void teardown()
	{
		// Uninit stuff
	}

	Store_SQLite_UnitTest_GeneratorTestCode& store() 
	{ 
		return *storePtr; 
	}

	id_t configID;
	DBConnection db;
	shared_ptr<Store_SQLite_UnitTest_GeneratorTestCode> storePtr;
};

static boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> makeIntArray()
{
	auto intArray = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>();
	for ( size_t z = 0; z < 10; ++z )
	{
		auto intArrayY = boost::make_shared<std::vector<boost::shared_ptr<std::vector<int64_t>>>>();
		intArray->push_back( intArrayY );
		for ( size_t y = 0; y < 10; ++y )
		{
			auto intArrayX = boost::make_shared<std::vector<int64_t>>();
			intArrayY->push_back( intArrayX );
			for ( size_t x = 0; x < 10; ++x )
			{
				intArrayX->push_back( z*100 + y*10 + x );
			}
		}
	}

	return intArray;
}

static void checkIntArray( const boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> expected,
	const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> value )
{
	LONGS_EQUAL( expected->size(), value->size() );
	for ( size_t z = 0; z < expected->size(); ++z )
	{
		LONGS_EQUAL( expected->at(z)->size(), value->at(z)->size() );
		for ( size_t y = 0; y < expected->at(z)->size(); ++y )
		{
			LONGS_EQUAL( expected->at(z)->at(y)->size(), value->at(z)->at(y)->size() );
			for ( size_t x = 0; x < expected->at(z)->at(y)->size(); ++x )
			{
				LONGS_EQUAL( expected->at(z)->at(y)->at(x), value->at(z)->at(y)->at(x) );
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store_SQLite_GeneratedObject tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_SQLite_GeneratedObject, example_usage_of_store_manager)
{
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	Store_Manager_SQLite_UnitTest_GeneratorTestCode mydataStoreManager(
		db				// DB
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
		auto mydataStore = mydataStoreManager.getReadWriteStore(configID);
		CHECK( mydataStore );

		// get data by ID
		auto data = mydataStore->getByID( testID );
		CHECK( data );
		CHECK_EQUAL( testID, data->getconst_id() );
		CHECK_EQUAL( configID, data->getconst_configID() );
		LONGS_EQUAL( testTimestamp, data->getconst_timestamp() );
	}

}

TEST(Store_SQLite_GeneratedObject, save_and_getByID_for_single_store)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t testID = "testID";

	// test store
	Store_SQLite_UnitTest_GeneratorTestCode store(configID, db);

	// prepare data
	auto data = store.create();
	CHECK( data );

	// fill object
	data->set_configID( configID );
	data->set_id( testID );

	//////////////////////////////////////
	// actual test

	// save data
	id_t id = store.save_move(data);
	CHECK_EQUAL( testID, id );

	// check data
	auto readData = store.getByID( testID );
	CHECK( readData );
	CHECK_EQUAL( testID, readData->getconst_id() );
}

TEST(Store_SQLite_GeneratedObject, integer_array_handled_correctly)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t testID = "testID";

	// test store
	Store_SQLite_UnitTest_GeneratorTestCode store(configID, db);

	// prepare data
	auto data = store.create();
	CHECK( data );

	// fill object
	data->set_configID( configID );
	data->set_id( testID );
	auto intArray = makeIntArray();
	data->set_intArray( intArray );

	//////////////////////////////////////
	// actual test

	// save data
	id_t id = store.save_move(data);
	CHECK_EQUAL( testID, id );

	// read data
	auto readData = store.getByID( testID );
	CHECK( readData );

	// check integer array
	checkIntArray( intArray, readData->getconst_intArray() );
}

TEST(Store_SQLite_GeneratedObject, object_array_handled_correctly)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t testID = "testID";
	auto objArray = boost::make_shared<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>>();
	for ( size_t i = 0; i < 5; ++i )
	{
		auto obj = boost::make_shared<Class_UnitTest_GeneratorTestCode_objArray>();
		obj->set_name( "object in array - " + intToStr(i) );
		obj->set_index( i );
		for ( size_t j = 0; j < 3; ++j )
		{
			obj->add_subArray( *obj->get_name() + " - " + intToStr(j) );
		}
		objArray->push_back(obj);
	}

	// test store
	Store_SQLite_UnitTest_GeneratorTestCode store(configID, db);

	// prepare data
	auto data = store.create();
	CHECK( data );

	// fill object
	data->set_configID( configID );
	data->set_id( testID );
	data->set_objArray( objArray );

	//////////////////////////////////////
	// actual test

	// save data
	id_t id = store.save_move(data);
	CHECK_EQUAL( testID, id );

	// read data
	auto readData = store.getByID( testID );
	CHECK( readData );

	// check object array
	for ( size_t i = 0; i < objArray->size(); ++i )
	{
		auto &actualObj = objArray->at(i);
		auto &testObj = readData->getconst_objArray(i);
		CHECK_EQUAL( *actualObj->getconst_name(), *testObj->getconst_name() );
		for ( size_t j = 0; j < 3; ++j )
		{
			CHECK_EQUAL( *actualObj->getconst_subArray(j), *testObj->getconst_subArray(j) );
		}
	}

}

TEST(Store_SQLite_GeneratedObject, getDataRange_of_object_with_sub_array)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t testID1 = "testID_1";
	const timestamp_t timestamp1 = 1000;
	const id_t testID2 = "testID_2";
	const timestamp_t timestamp2 = 2000;
	auto intArray = makeIntArray();

	// test store
	Store_SQLite_UnitTest_GeneratorTestCode store(configID, db);

	// prepare data
	auto data = store.create();
	CHECK( data );
	data->set_configID( configID );
	data->set_intArray( intArray );

	// save first object
	data->set_id( testID1 );
	data->set_timestamp( timestamp1 );
	store.save_copy(data);

	// second first object
	data->set_id( testID2 );
	data->set_timestamp( timestamp2 );
	store.save_copy(data);

	//////////////////////////////////////
	// actual test

	// update timestamp
	auto range = store.getDataRange();

	LONGS_EQUAL( 0, range.indexStart );
	LONGS_EQUAL( 1, range.indexEnd );
	LONGS_EQUAL( timestamp1, range.timestampStart );
	LONGS_EQUAL( timestamp2, range.timestampEnd );

}

#ifdef UseFileDB
	#undef UseFileDB
#endif

} // namespace DataHandling

} // namespace UnitTest
} // namespace ConnectedVision
