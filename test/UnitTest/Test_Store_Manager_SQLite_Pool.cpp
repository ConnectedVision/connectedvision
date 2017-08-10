/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_SQLite_BaseClass.h>
#include <DataHandling/Store_Manager_Pool.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_Store_SQLite.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_SQLite_Pool_Manager.db"

class TestWrapper_Store_Manager_SQLite_Pool : public Store_Manager_Pool<TestDataClass>
{
public:
	TestWrapper_Store_Manager_SQLite_Pool(
		const int64_t storeCount,			///< [in] number of stores in manager
		DBConnection& db					///< [in] DB connection object
	) :	Store_Manager_Pool<TestDataClass>(
		storeCount,							// number of stores in manager
		boost::dynamic_pointer_cast< IStore_ReadWrite_Factory<TestDataClass> >( make_shared< TestWrapper_Store_SQLite_Factory >( db	)) // [in] store factory
	) {}

	/*
	* virtual destructor
	*/
	virtual ~TestWrapper_Store_Manager_SQLite_Pool() {}
};

TEST_GROUP(Store_SQLite_Pool_Manager)
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
//  Store_SQLite_Pool_Manager tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(Store_SQLite_Pool_Manager, example_usage_of_store_manager)
{
	const int64_t storeCount = 2;

	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	TestWrapper_Store_Manager_SQLite_Pool mydataStoreManager(
		storeCount,		// number of stores in manager
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


}} // namespace scope

