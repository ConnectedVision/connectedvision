/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_SQLite_BaseClass.h>

#include <CppUTest/TestHarness.h>
#include <boost/shared_ptr.hpp>

#include <DataHandling/Store_Cache.h>
#include "Store_Null.h"

#include "TestHelper_Store_SQLite.hpp"
#include "MixIn_IStore.h"

namespace ConnectedVision {
namespace DataHandling {

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_SQLite_table.db"


// test wrapper for SQLiteCache
class TestWrapper_Store_Cache : public Store_Cache<TestDataClass>
{
public: 
	TestWrapper_Store_Cache(
		const id_t& configID,				///< [in] config ID
		const int64_t cacheSize,			///< [in] number of maximal elements in cache
		const shared_ptr< IStore_ReadWrite<TestDataClass> >& baseStore		///< [in] store to be cached (typically a DB store)
	) : Store_Cache(configID, cacheSize, baseStore ), spy_write_through(true)
	{
		baseStoreOrig = baseStore;
		nullStore = make_shared< Store_Null<TestDataClass> >();
	}

	// overwrite write through
	virtual bool write_through(
		const shared_ptr<const TestDataClass>& data	///< [in] shared pointer to read-only data object
	)
	{ return spy_write_through; }
	bool spy_write_through;

	// test helper functions
	void flush()
	{ this->cacheFlush(); }

	void useCacheOnly()
	{ this->baseStore = this->nullStore; }

	void useCacheAndBaseStore()
	{ this->baseStore = this->baseStoreOrig; }

protected:
	shared_ptr< IStore_ReadWrite<TestDataClass> > baseStoreOrig;
	shared_ptr< IStore_ReadWrite<TestDataClass> > nullStore;
};


static StoreEnvironment<TestDataClass> env;
TEST_GROUP(Store_SQLiteCache)
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

		// init SQLite store
		baseStorePtr = ConnectedVision::make_shared<TestWrapper_Store_SQLite>(env.configID, db);

		// init cache store
		cacheSize = 10;
		storePtr = ConnectedVision::make_shared<TestWrapper_Store_Cache>(env.configID, cacheSize, baseStorePtr);
	}

	void teardown()
	{
		// Uninit stuff
	}

	DBConnection db;
	shared_ptr< IStore_ReadWrite<TestDataClass> > baseStorePtr;
	shared_ptr<TestWrapper_Store_Cache> storePtr;
	int64_t cacheSize;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIXIN_APPLY(Store_SQLiteCache, MixIn_IStore, IStore_tests)
{
	params.env = &env;
	params.store = boost::static_pointer_cast< IStore_ReadWrite<TestDataClass> >(storePtr);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific Store_SQLiteCAche tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IGNORE_TEST(Store_SQLiteCache, initStore)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	store.flush();

	FAIL("TODO LONGS_EQUAL( cacheSize, store.spy_cache().size() );");
}

IGNORE_TEST(Store_SQLiteCache, getByIndex_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	auto data = store.getByIndex(index);
	CHECK_DATA_EQUAL( dataList[index], data );

	// disable DB access
	store.useCacheOnly();
	auto cachedData = store.getByIndex(index);
	CHECK_DATA_EQUAL(dataList[index], cachedData);
	CHECK_EQUAL(data, cachedData);
}

IGNORE_TEST(Store_SQLiteCache, getByIndexRange_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t start = 0;
	size_t end = (size_t)cacheSize -1;
	auto dataByRange = store.getByIndexRange(start, end);
	LONGS_EQUAL( (end + 1 - start), dataByRange.size() );
	for ( size_t i = 0; i < (end + 1 - start); ++i )
	{
		CHECK_DATA_EQUAL( dataList[start + i], dataByRange[i] );
	}

	// disable DB access
	store.useCacheOnly();
	auto cachedDataByRange = store.getByIndexRange(start, end);
	LONGS_EQUAL( (end + 1 - start), cachedDataByRange.size() );
	for ( size_t i = 0; i < (end + 1 - start); ++i )
	{
		CHECK_DATA_EQUAL( dataList[start + i], cachedDataByRange[i] );
		CHECK_EQUAL( dataByRange[i], cachedDataByRange[i] );
	}
}

TEST(Store_SQLiteCache, getByID_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	id_t id = dataList[index]->getconst_id();
	auto data = store.getByID(id);
	CHECK_DATA_EQUAL( dataList[index], data );

	// disable DB access
	store.useCacheOnly();
	auto cachedData = store.getByID(id);
	CHECK_DATA_EQUAL( dataList[index], cachedData );
	CHECK_EQUAL( data, cachedData );
}

TEST(Store_SQLiteCache, getByID_cached_objects_have_priority_over_baseStore)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	id_t id = dataList[index]->getconst_id();
	auto data = store.getByID(id);
	CHECK_DATA_EQUAL( dataList[index], data );

	// by-pass cache and alter base store
	auto clone = data->copy();
	clone->set_timestamp( data->getconst_timestamp() + 5 );
	baseStorePtr->save_move(clone);

	// query cache again
	auto cachedData = store.getByID(id);
	CHECK_DATA_EQUAL( dataList[index], cachedData );
}

IGNORE_TEST(Store_SQLiteCache, getByTimestamp_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	timestamp_t time = dataList[index]->getconst_timestamp();
	auto data = store.getByTimestamp(time);
	LONGS_EQUAL( 1, data.size() );
	CHECK_DATA_EQUAL( dataList[index], data[0] );

	// disable DB access
	store.useCacheOnly();
	auto cachedData = store.getByTimestamp(time);
	LONGS_EQUAL( 1, cachedData.size() );
	CHECK_DATA_EQUAL( dataList[index], cachedData[0] );
	CHECK_EQUAL( data[0], cachedData[0] );
}

IGNORE_TEST(Store_SQLiteCache, getBeforeTimestamp_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	timestamp_t time = dataList[index]->getconst_timestamp() +1;
	auto data = store.getBeforeTimestamp(time);
	LONGS_EQUAL( 1, data.size() );
	CHECK_DATA_EQUAL( dataList[index], data[0] );

	// disable DB access
	store.useCacheOnly();
	auto cachedData = store.getBeforeTimestamp(time);
	LONGS_EQUAL( 1, cachedData.size() );
	CHECK_DATA_EQUAL( dataList[index], cachedData[0] );
	CHECK_EQUAL( data[0], cachedData[0] );
}

IGNORE_TEST(Store_SQLiteCache, getAfterTimestamp_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	timestamp_t time = dataList[index]->getconst_timestamp() -1;
	auto data = store.getAfterTimestamp(time);
	LONGS_EQUAL( 1, data.size() );
	CHECK_DATA_EQUAL( dataList[index], data[0] );

	// disable DB access
	store.useCacheOnly();
	auto cachedData = store.getAfterTimestamp(time);
	LONGS_EQUAL( 1, cachedData.size() );
	CHECK_DATA_EQUAL( dataList[index], cachedData[0] );
	CHECK_EQUAL( data[0], cachedData[0] );
}

IGNORE_TEST(Store_SQLiteCache, getAllInTimespan_should_cache_the_object)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	size_t index = 0;
	timestamp_t time = dataList[index]->getconst_timestamp();
	auto data = store.getAllInTimespan(time-1, time);
	LONGS_EQUAL( 1, data.size() );
	CHECK_DATA_EQUAL( dataList[index], data[0] );

	// disable DB access
	store.useCacheOnly();
	auto cachedData = store.getAllInTimespan(time-1, time);
	LONGS_EQUAL( 1, cachedData.size() );
	CHECK_DATA_EQUAL( dataList[index], cachedData[0] );
	CHECK_EQUAL( data[0], cachedData[0] );
}

IGNORE_TEST(Store_SQLiteCache, getByTimestamp_should_return_all_objects_of_the_timestamp_not_just_the_cached_ones)
{
	//////////////////////////////////////
	// test initialization
	timestamp_t time = env.startTime;

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	std::vector< shared_ptr<const TestDataClass> > dataList;
	for (int i = 0; i < (cacheSize + 10); i++ )
	{
		auto tmp = env.makeConstData(i, time, env.configID);
		store.save_const(tmp);
		dataList.push_back(tmp);
	}
	store.flush();

	//////////////////////////////////////
	// actual test

	auto data = store.getByTimestamp(time);
	CHECK_DATAVECTOR_EQUAL( dataList, data );
}

IGNORE_TEST(Store_SQLiteCache, getBeforeTimestamp_should_return_all_objects_of_the_timestamp_not_just_the_cached_ones)
{
	//////////////////////////////////////
	// test initialization
	timestamp_t time = env.startTime;

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	std::vector< shared_ptr<const TestDataClass> > dataList;
	for (int i = 0; i < (cacheSize + 10); i++ )
	{
		auto tmp = env.makeConstData(i, time, env.configID);
		store.save_const(tmp);
		dataList.push_back(tmp);
	}
	store.flush();

	//////////////////////////////////////
	// actual test

	auto data = store.getBeforeTimestamp(time+1);
	CHECK_DATAVECTOR_EQUAL( dataList, data );
}

IGNORE_TEST(Store_SQLiteCache, getAfterTimestamp_should_return_all_objects_of_the_timestamp_not_just_the_cached_ones)
{
	//////////////////////////////////////
	// test initialization
	timestamp_t time = env.startTime;

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	std::vector< shared_ptr<const TestDataClass> > dataList;
	for (int i = 0; i < (cacheSize + 10); i++ )
	{
		auto tmp = env.makeConstData(i, time, env.configID);
		store.save_const(tmp);
		dataList.push_back(tmp);
	}
	store.flush();

	//////////////////////////////////////
	// actual test

	auto data = store.getAfterTimestamp(time-1);
	CHECK_DATAVECTOR_EQUAL( dataList, data );
}

IGNORE_TEST(Store_SQLiteCache, getByIndexRange_should_return_all_object_not_just_the_cached_ones)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	auto data = store.getByIndexRange( 0, dataList.size() );
	CHECK_DATAVECTOR_EQUAL( dataList, data );
}

IGNORE_TEST(Store_SQLiteCache, getAllInTimespan_should_return_all_object_not_just_the_cached_ones)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	//////////////////////////////////////
	// actual test

	// get data / fill cache
	auto data = store.getAllInTimespan( dataList.front()->getconst_timestamp(), dataList.back()->getconst_timestamp() );
	CHECK_DATAVECTOR_EQUAL( dataList, data );
}

TEST(Store_SQLiteCache, save_const_caches_objects)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = boost::static_pointer_cast<const TestDataClass>(env.makeData(100, 0, env.configID));

	//////////////////////////////////////
	// actual test

	// save
	store.save_const(saveDataConst);

	// check cache
	store.useCacheOnly();
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLiteCache, save_move_caches_objects)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = env.makeConstData(100, 0, env.configID);
	shared_ptr<TestDataClass> saveData = saveDataConst->copy();

	//////////////////////////////////////
	// actual test

	// save
	store.save_move(saveData);

	// check cache
	store.useCacheOnly();
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLiteCache, save_copy_caches_objects)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = env.makeConstData(100, 0, env.configID);
	shared_ptr<TestDataClass> saveData = saveDataConst->copy();

	//////////////////////////////////////
	// actual test

	// save
	store.save_copy(saveData);

	// check cache
	store.useCacheOnly();
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLiteCache, save_constVector_caches_objects)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	std::vector<shared_ptr<const TestDataClass> > saveList;
	saveList.push_back( dataList[0] );

	//////////////////////////////////////
	// actual test

	// save
	store.save_constVector(saveList);

	// check cache
	store.useCacheOnly();
	auto cachedData = store.getByID( saveList[0]->getconst_id() );
	CHECK_DATA_EQUAL( saveList[0], cachedData );
}

TEST(Store_SQLiteCache, save_const_write_through_to_base_store)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = env.makeConstData(100, 0, env.configID);

	//////////////////////////////////////
	// actual test

	// set write through
	store.spy_write_through = true;

	// save
	store.save_const(saveDataConst);

	// check base store
	auto data = baseStorePtr->getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, data );

	// check cache
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLiteCache, save_const_do_not_write_through_to_base_store)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = env.makeConstData(100, 0, env.configID);

	//////////////////////////////////////
	// actual test

	// set write through
	store.spy_write_through = false;

	// save
	store.save_const(saveDataConst);

	// check base store
	auto data = baseStorePtr->getByID( saveDataConst->getconst_id() );
	CHECK_FALSE( data );

	// check cache
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLiteCache, save_constVector_write_through_to_base_store)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = env.makeConstData(100, 0, env.configID);
	std::vector< shared_ptr<const TestDataClass> > saveList;
	saveList.push_back( saveDataConst );

	//////////////////////////////////////
	// actual test

	// set write through
	store.spy_write_through = true;

	// save
	store.save_constVector(saveList);

	// check base store
	auto data = baseStorePtr->getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, data );

	// check cache
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLiteCache, save_constVector_do_not_write_through_to_base_store)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Cache store(env.configID, cacheSize, baseStorePtr);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const TestDataClass> saveDataConst = env.makeConstData(100, 0, env.configID);
	std::vector< shared_ptr<const TestDataClass> > saveList;
	saveList.push_back( saveDataConst );

	//////////////////////////////////////
	// actual test

	// set write through
	store.spy_write_through = false;

	// save
	store.save_constVector(saveList);

	// check base store
	auto data = baseStorePtr->getByID( saveDataConst->getconst_id() );
	CHECK_FALSE( data );

	// check cache
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

}} // namespace scope

