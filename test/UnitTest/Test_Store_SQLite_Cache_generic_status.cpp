/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_SQLite_BaseClass.h>

#include <CppUTest/TestHarness.h>
#include <boost/shared_ptr.hpp>

#include <Module/Control/Class_generic_status.h>
#include <Module/Control/Store_SQLite_generic_status.h>
#include <DataHandling/Store_Cache.h>
#include "Store_Null.h"

#include "TestHelper_Store_SQLite.hpp"
#include "TestHelper_StoreEnvironment.hpp"

namespace ConnectedVision {
namespace DataHandling {

// activate this define to write DB to file (e.g. for debugging purpose)
// DO NOT commit with UseFileDB enabled
// #define UseFileDB "Test_Store_SQLite_table.db"


// test wrapper for SQLiteCache
class TestWrapper_Store_Status : public Store_SQLite_generic_status
{
public: 
	TestWrapper_Store_Status(
		const id_t& configID,		///< [in] config ID
		DBConnection& db,			///< [in] DB connection object
		const int64_t cacheSize		///< [in] number of maximal elements in cache
	) : Store_SQLite_generic_status(configID, db, cacheSize)
	{
		baseStoreOrig = baseStore;
		nullStore = make_shared< Store_Null<Class_generic_status> >();
	}
	virtual ~TestWrapper_Store_Status() {}

	// test helper functions
	void flush()
	{ this->cacheFlush(); }

	void useCacheOnly()
	{ this->baseStore = this->nullStore; }

	void useCacheAndBaseStore()
	{ this->baseStore = this->baseStoreOrig; }

	shared_ptr< IStore_ReadWrite<Class_generic_status> >& spy_baseStore()
	{ return this->baseStore; }

protected:
	shared_ptr< IStore_ReadWrite<Class_generic_status> > baseStoreOrig;
	shared_ptr< IStore_ReadWrite<Class_generic_status> > nullStore;

public:
	static const std::string tableName;
};
const std::string TestWrapper_Store_Status::tableName = "generic_status";


static StoreEnvironment<Class_generic_status> env;
TEST_GROUP(Store_SQLite_Status)
{
	void setup()
	{
		// Init stuff
		env.configID = ID_NULL;

#ifdef UseFileDB
		db.init(UseFileDB, SQLITE_OPEN_CREATE);
		
		// delete existing data
		{
		scoped_db_lock lock(db);
		std::string sql = std::string("DROP TABLE IF EXISTS ") + TestWrapper_Store_Status::tableName;
		sqlite3_exec(lock.db, sql.c_str(), NULL, NULL, NULL);
		}
#else
		db.init(":memory:", SQLITE_OPEN_CREATE);
#endif

		// init store
		cacheSize = 10;
		storePtr = ConnectedVision::make_shared<TestWrapper_Store_Status>(env.configID, db, cacheSize);
	}

	void teardown()
	{
		// Uninit stuff
	}

	DBConnection db;
	shared_ptr<TestWrapper_Store_Status> storePtr;
	int64_t cacheSize;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific Store_SQLite_generic_status tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(Store_SQLite_Status, getByID_should_cache)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Status store(env.configID, db, cacheSize);
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
	CHECK_DATA_EQUAL( data, cachedData );
}

TEST(Store_SQLite_Status, save_const_caches)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Status store(env.configID, db, cacheSize);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	shared_ptr<const Class_generic_status> saveDataConst = boost::static_pointer_cast<const Class_generic_status>(env.makeData(100, 0, env.configID));

	//////////////////////////////////////
	// actual test

	// save
	store.save_const(saveDataConst);

	// check cache
	store.useCacheOnly();
	auto cachedData = store.getByID( saveDataConst->getconst_id() );
	CHECK_DATA_EQUAL( saveDataConst, cachedData );
}

TEST(Store_SQLite_Status, normal_status_sequence_init_running_finished_is_write_through_base_store)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Status store(env.configID, db, cacheSize);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	auto status = store.create();
	status->set_id("testID");

	//////////////////////////////////////
	// actual test

	// set status to init and save
	status->set_status_init();
	status->set_timestamp(0);
	auto statusCopy = status->copy();
	auto statusConst = store.make_const(statusCopy);
	store.save_const(statusConst);
	// check base store
	auto data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_init() );

	// set status to running and save
	status->set_status_running();
	status->set_timestamp(100);
	auto statusCopy1 = status->copy();
	statusConst = store.make_const(statusCopy1);
	store.save_const(statusConst);
	// check base store
	data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_running() );

	// update running status
	status->set_status_running();
	status->set_timestamp(200);
	auto statusCopy2 = status->copy();
	statusConst = store.make_const(statusCopy2);
	store.save_const(statusConst);
	// cache only
	data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK( statusConst->getconst_timestamp() != data->getconst_timestamp() );

	// set status to finished and save
	status->set_status_finished();
	status->set_timestamp(300);
	auto statusCopy3 = status->copy();
	statusConst = store.make_const(statusCopy3);
	store.save_const(statusConst);
	// check base store
	data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_finished() );
}

TEST(Store_SQLite_Status, save_write_through_if_status_is_not_running)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Status store(env.configID, db, cacheSize);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	auto status = store.create();
	status->set_id("testID");

	//////////////////////////////////////
	// actual test

	// set status to N/A and save
	status->set_status_na();
	status->set_timestamp(0);
	auto statusCopy1 = status->copy();
	auto statusConst = store.make_const(statusCopy1);
	store.save_const(statusConst);
	// check base store
	auto data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_na() );

	// set status to init and save
	status->set_status_init();
	status->set_timestamp(100);
	auto statusCopy2 = status->copy();
	statusConst = store.make_const(statusCopy2);
	store.save_const(statusConst);
	// check base store
	data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_init() );

	// set status to finished and save
	status->set_status_finished();
	status->set_timestamp(200);
	auto statusCopy3 = status->copy();
	statusConst = store.make_const(statusCopy3);
	store.save_const(statusConst);
	// check base store
	data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_finished() );
}

TEST(Store_SQLite_Status, save_write_through_if_status_is_running_only_once)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Status store(env.configID, db, cacheSize);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	auto status = store.create();
	status->set_id("testID");
	status->set_status_running();
	status->set_timestamp(0);

	//////////////////////////////////////
	// actual test

	// save
	auto statusCopy1 = status->copy();
	auto statusConst = store.make_const(statusCopy1);
	store.save_const(statusConst);

	// check base store
	auto data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_running() );

	// update and save
	status->set_timestamp(1000);
	auto statusCopy2 = status->copy();
	auto statusConst2 = store.make_const(statusCopy2);
	store.save_const(statusConst2);

	// base store holds old copy
	data = store.spy_baseStore()->getByID( statusConst->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_running() );

}

TEST(Store_SQLite_Status, save_updates_if_status_is_running_only_once)
{
	//////////////////////////////////////
	// test initialization

	// test store
	cacheSize = 2;
	TestWrapper_Store_Status store(env.configID, db, cacheSize);
	auto dataList = env.fillStoreWithData(store, (size_t)cacheSize + 10, env.configID);
	store.flush();

	auto status = store.create();
	status->set_id("testID");
	status->set_status_init();
	status->set_timestamp(0);

	//////////////////////////////////////
	// actual test

	// save
	store.save_copy(status);

	// check base store
	auto data = store.spy_baseStore()->getByID( status->getconst_id() );
	CHECK( data );
	CHECK( data->is_status_init() );

	// set running and save
	status->set_status_running();
	auto statusCopy1 = status->copy();
	auto statusConst = store.make_const(statusCopy1);
	store.save_const(statusConst);

	// check base store
	data = store.spy_baseStore()->getByID( status->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_running() );

	// update and save
	status->set_timestamp(1000);
	auto statusCopy2 = status->copy();
	auto statusConst2 = store.make_const(statusCopy2);
	store.save_const(statusConst2);

	// base store holds old copy
	data = store.spy_baseStore()->getByID( status->getconst_id() );
	CHECK_DATA_EQUAL( statusConst, data );
	CHECK( data->is_status_running() );
}

}} // namespace scope

