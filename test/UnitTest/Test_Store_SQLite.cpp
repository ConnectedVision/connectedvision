/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_SQLite_BaseClass.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_Store_SQLite.hpp"
#include "MixIn_IStore.h"

namespace ConnectedVision {
namespace DataHandling {

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_SQLite_table.db"

static StoreEnvironment<TestDataClass> env;
TEST_GROUP(Store_SQLite)
{
	void setup()
	{
		// Init stuff
#ifdef UseFileDB
		db.init(UseFileDB, SQLITE_OPEN_CREATE);
		
		// delete existing data
		{
		scoped_db_lock lock(db);
		std::string sql = std::string("DROP TABLE IF EXISTS ") + TestWrapper_Store_SQLite_Table::tableName;
		sqlite3_exec(lock.db, sql.c_str(), NULL, NULL, NULL);
		}
#else
		db.init(":memory:", SQLITE_OPEN_CREATE);
#endif

		// init store
		storePtr = ConnectedVision::make_shared<TestWrapper_Store_SQLite>(env.configID, db);
	}

	void teardown()
	{
		// Uninit stuff
	}

	TestWrapper_Store_SQLite& store() 
	{ 
		return *storePtr; 
	}

	DBConnection db;
	shared_ptr<TestWrapper_Store_SQLite> storePtr;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIXIN_APPLY(Store_SQLite, MixIn_IStore, IStore_tests)
{
	params.env = &env;
	params.store = boost::static_pointer_cast< IStore_ReadWrite<TestDataClass> >(storePtr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific Store_SQLite tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_SQLite, initStore)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_Store_SQLite store(env.configID, db);
}

TEST(Store_SQLite, initStore_malformed_column_description_should_throw)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, TestWrapper_Store_SQLite(env.configID, db, 
		boost::assign::list_of("'' BIGINT NOT NULL DEFAULT '0' /* empty column name MALFORMED */")) );

	CHECK_THROWS( ConnectedVision::runtime_error, TestWrapper_Store_SQLite(env.configID, db, 
		boost::assign::list_of("\"test\" BIGINT NOT NULL DEFAULT '0' /* wrong quoting MALFORMED */")) );

	CHECK_THROWS( ConnectedVision::runtime_error, TestWrapper_Store_SQLite(env.configID, db, 
		boost::assign::list_of("\"foo bar\" BIGINT NOT NULL DEFAULT '0' /* whitespace in name MALFORMED */")) );
}

TEST(Store_SQLite, save_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// test store
	TestWrapper_Store_SQLite store(configID, db);

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// prepare data
	auto data = env.makeConstData(1, env.startTime, configID);

	//////////////////////////////////////
	// actual test

	// save data
	id_t id = store.save_const(data);
	CHECK_EQUAL(data->getconst_id(), id);

	// check data
	auto actualList = store.getByIndexRange(0, 1000);
	LONGS_EQUAL( 1, actualList.size() );
	CHECK_DATA_EQUAL( data, actualList[0] );

	// check other data
	auto otherActualList = otherStore.getByIndexRange(0, 1000);
	CHECK_DATAVECTOR_EQUAL( otherDataList, otherActualList );
}

TEST(Store_SQLite, save_constVector_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// test store
	TestWrapper_Store_SQLite store(configID, db);

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// prepare data
	std::vector< shared_ptr<const TestDataClass> > dataList;
	for (int i = 0; i < 5; ++i)
		dataList.push_back( env.makeConstData(i, env.startTime + i*10, configID) );

	//////////////////////////////////////
	// actual test

	// save data
	store.save_constVector(dataList);

	// check data
	auto actualList = store.getByIndexRange(0, 1000);
	CHECK_DATAVECTOR_EQUAL( dataList, actualList );

	// check other data
	auto otherActualList = otherStore.getByIndexRange(0, 1000);
	CHECK_DATAVECTOR_EQUAL( otherDataList, otherActualList );
}

TEST(Store_SQLite, deleteAll_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	//////////////////////////////////////
	// actual test
	store.deleteAll();

	// check data
	auto actualList = store.getByIndexRange(0, 1000);
	CHECK( actualList.empty() );

	// check other data
	auto otherActualList = otherStore.getByIndexRange(0, 1000);
	CHECK_DATAVECTOR_EQUAL( otherDataList, otherActualList );
}

TEST(Store_SQLite, getByID_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	
	// getByID
	auto obj = store.getByID( dataList[0]->getconst_id() );
	CHECK_DATA_EQUAL( dataList[0], obj );
}

TEST(Store_SQLite, getByIndex_DB_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	auto obj = store.getByIndex( 0 );
	CHECK_DATA_EQUAL( dataList[0], obj );
}

TEST(Store_SQLite, getByIndexRange_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	auto actualList = store.getByIndexRange(0, 1000);
	CHECK_DATAVECTOR_EQUAL( dataList, actualList );
}

TEST(Store_SQLite, getByTimestamp_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	auto actualList = store.getByTimestamp( dataList[0]->getconst_timestamp() );
	LONGS_EQUAL( 1, actualList.size() );
	CHECK_DATA_EQUAL( dataList[0], actualList[0] );
}

TEST(Store_SQLite, getBeforeTimestamp_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	auto actualList = store.getBeforeTimestamp( dataList[0]->getconst_timestamp()+1 );
	LONGS_EQUAL( 1, actualList.size() );
	CHECK_DATA_EQUAL( dataList[0], actualList[0] );
}

TEST(Store_SQLite, getAfterTimestamp_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	auto actualList = store.getAfterTimestamp( dataList[0]->getconst_timestamp()-1 );
	LONGS_EQUAL( 1, actualList.size() );
	CHECK_DATA_EQUAL( dataList[0], actualList[0] );
}

TEST(Store_SQLite, getAllInTimespan_should_not_interfere_with_other_configs)
{
	//////////////////////////////////////
	// test initialization
	const id_t configID = "testConfigID";
	const id_t otherConfigID = "otherConfigID";

	// other store
	TestWrapper_Store_SQLite otherStore(otherConfigID, db);
	auto otherDataList = env.fillStoreWithData(otherStore, 10, otherConfigID);

	// test store
	TestWrapper_Store_SQLite store(configID, db);
	auto dataList = env.fillStoreWithData(store, 10, configID);

	//////////////////////////////////////
	// actual test
	auto actualList = store.getAllInTimespan( dataList[0]->getconst_timestamp(), dataList[9]->getconst_timestamp() );
	CHECK_DATAVECTOR_EQUAL( dataList, actualList );
}


#ifdef UseFileDB
	#undef UseFileDB
#endif
}} // namespace scope

