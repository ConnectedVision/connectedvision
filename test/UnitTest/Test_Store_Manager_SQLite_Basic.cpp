/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_SQLite_BaseClass.h>
#include <DataHandling/Store_Manager_Basic.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_Store_SQLite.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_SQLite_Basic_Manager.db"

class TestWrapper_Store_Manager_SQLite_Basic : public Store_Manager_Basic<TestDataClass>
{
public:
	TestWrapper_Store_Manager_SQLite_Basic(
		DBConnection& db				///< [in] DB connection object
	) :	Store_Manager_Basic<TestDataClass>(
		boost::dynamic_pointer_cast< IStore_ReadWrite_Factory<TestDataClass> >( make_shared< TestWrapper_Store_SQLite_Factory >( db	))
	) {}

	/*
	* virtual destructor
	*/
	virtual ~TestWrapper_Store_Manager_SQLite_Basic() {}


	// spy functions
	std::map< id_t, shared_ptr<IStore_ReadWrite<TestDataClass>> >& spy_storeMap() { return this->storeMap; }
	ConnectedVision::mutex& spy_mapMutex() { return this->mapMutex; }
};

TEST_GROUP(Store_SQLite_Basic_Manager)
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
		std::string sql = std::string("DROP TABLE IF EXISTS ") + env.tableName;
		sqlite3_exec(lock.db, sql.c_str(), NULL, NULL, NULL);
		}
#else
		db.init(":memory:", SQLITE_OPEN_CREATE);
#endif

		// init store
		storePtr = ConnectedVision::make_shared<TestWrapper_Store_SQLite>(configID, db);
	}

	void teardown()
	{
		// Uninit stuff
	}

	TestWrapper_Store_SQLite& store() 
	{ 
		return *storePtr; 
	}

	id_t configID;
	DBConnection db;
	shared_ptr<TestWrapper_Store_SQLite> storePtr;
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store_SQLite_Basic_Manager tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(Store_SQLite_Basic_Manager, example_usage_of_store_manager)
{
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	TestWrapper_Store_Manager_SQLite_Basic mydataStoreManager(
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

TEST(Store_SQLite_Basic_Manager, request_for_used_store_returns_original_store)
{
	//////////////////////////////////////
	// test initialization
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;
	TestWrapper_Store_Manager_SQLite_Basic storeManager(db);
	const id_t configID1 = "configID-1";
	const id_t configID2 = "configID-2";
	const id_t configID3 = "configID-3";
	auto store1 = storeManager.getReadWriteStore(configID1);
	auto store2 = storeManager.getReadWriteStore(configID2);

	//////////////////////////////////////
	// actual test
	auto storeWrite = storeManager.getReadWriteStore(configID1);
	CHECK_EQUAL( store1, storeWrite );

	auto storeRead = storeManager.getReadStore(configID2);
	CHECK_EQUAL( store2, storeRead );
}

TEST(Store_SQLite_Basic_Manager, request_store_sould_implicitly_purge_unused_stores)
{
	//////////////////////////////////////
	// test initialization
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;
	TestWrapper_Store_Manager_SQLite_Basic storeManager(db);
	const id_t configID1 = "configID-1";
	const id_t configID2 = "configID-2";
	const id_t configID3 = "configID-3";

	//////////////////////////////////////
	// actual test
	auto store1 = storeManager.getReadWriteStore(configID1);
	auto store2 = storeManager.getReadWriteStore(configID2);
	auto store3 = storeManager.getReadWriteStore(configID3);
	LONGS_EQUAL( 3, storeManager.spy_storeMap().size() );

	// release store 1 & 2
	store1.reset();
	store2.reset();
	// implicitly purge stores within getReadWriteStore()
	store3 = storeManager.getReadWriteStore(configID3);
	LONGS_EQUAL( 1, storeManager.spy_storeMap().size() );

	// release store 3
	store3.reset();
	// implicitly purge stores within getReadWriteStore()
	auto store = storeManager.getReadStore("configID-Reader");
	CHECK(store);
	LONGS_EQUAL( 1, storeManager.spy_storeMap().size() );

}

}} // namespace scope

