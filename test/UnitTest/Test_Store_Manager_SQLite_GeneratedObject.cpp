/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "generated/Store_Manager_SQLite_UnitTest_GeneratorTestCode.h"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {
namespace UnitTest {

namespace DataHandling {

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_Manager_SQLite_GeneratedObject.db"

TEST_GROUP(Store_Manager_SQLite_GeneratedObject)
{
	void setup()
	{
		// Init stuff
#ifdef UseFileDB
		db.init(UseFileDB, SQLITE_OPEN_CREATE);
		
		// delete existing data
		{
		scoped_db_lock lock(db);
		std::string sql = std::string("DROP TABLE IF EXISTS GeneratedTestCode");
		sqlite3_exec(lock.db, sql.c_str(), NULL, NULL, NULL);
		}
#else
		db.init(":memory:", SQLITE_OPEN_CREATE);
#endif
	}

	void teardown()
	{
		// Uninit stuff
	}

	DBConnection db;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store_Manager_SQLite_GeneratedObject tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(Store_Manager_SQLite_GeneratedObject, example_usage_of_store_manager)
{
	const id_t configID = "testConfigID";
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	Store_Manager_SQLite_UnitTest_GeneratorTestCode mydataStoreManager(
		db				// DB connection object
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

TEST(Store_Manager_SQLite_GeneratedObject, only_one_storeManager_can_be_created)
{
	const id_t configID = "testConfigID";
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	
	// create first instance
	auto storeManager = make_shared<Store_Manager_SQLite_UnitTest_GeneratorTestCode>(db);
	CHECK( storeManager );

	// try to create second instance
	CHECK_THROWS( ConnectedVision::runtime_error, new Store_Manager_SQLite_UnitTest_GeneratorTestCode(db) );

	// release and recreate
	storeManager.reset();
	CHECK( !storeManager );
	storeManager = make_shared<Store_Manager_SQLite_UnitTest_GeneratorTestCode>(db);
	CHECK( storeManager );
}

} // namespace DataHandling

} // namespace UnitTest
} // namespace ConnectedVision
