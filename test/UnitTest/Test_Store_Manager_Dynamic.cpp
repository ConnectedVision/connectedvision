/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_Manager_Dynamic.h>
#include <DataHandling/Store_Manager_Pool.h> ///////////////////////////////////////////////////////////////////////////////
#include <DataHandling/Store_Manager_Basic.h>
#include <DataHandling/Store_Ringbuffer.h>
#include <DataHandling/Store_SQLite_BaseClass.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_DataHandling.hpp"
#include "TestHelper_Store_SQLite.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

// helper function
static shared_ptr<IStore_Manager<TestDataClass>> createStoreManagerRingbuffer()
{
	const int64_t storeCount = 5;
	const int64_t ringbufferSize = 10;

	shared_ptr<IStore_Manager<TestDataClass>> storeManager( 
		new Store_Manager_Pool<TestDataClass>(
			storeCount, 
			boost::dynamic_pointer_cast< IStore_ReadWrite_Factory<TestDataClass> >( make_shared< Store_Ringbuffer_Factory<TestDataClass> >(ringbufferSize) )
		) 
	);

	return storeManager;
}
static shared_ptr<IStore_Manager<TestDataClass>> createStoreManagerSQLite()
{
	DBConnection db;
	db.init(":memory:", SQLITE_OPEN_CREATE);

	shared_ptr<IStore_Manager<TestDataClass>> storeManager( 
		new Store_Manager_Basic<TestDataClass>(
			boost::dynamic_pointer_cast< IStore_ReadWrite_Factory<TestDataClass> >( make_shared< TestWrapper_Store_SQLite_Factory >( db	) )
		)
	);

	return storeManager;
}

class Mockup_Store_Manager_Selector : public IStore_Manager_Dynamic_Selector<TestDataClass>
{
public:
	std::vector< shared_ptr<IStore_Manager<TestDataClass>> > storeManagerList;

	Mockup_Store_Manager_Selector()
	{
		// add ringbuffer store manager 
		this->storeManagerList.push_back( createStoreManagerRingbuffer() );

		// add SQLite store manager 
		this->storeManagerList.push_back( createStoreManagerSQLite() );
	}


	virtual shared_ptr< IStore_Manager<TestDataClass> > selectStoreManager(const id_t configID)
	{
		// select store according to config ...
		if ( configID == "SQLite" )
			return this->storeManagerList.at(1);
		else
			return this->storeManagerList.at(0);
	}

};


TEST_GROUP(Store_Manager_Dynamic)
{
	void setup()
	{
		// Init stuff
		configID = "testConfigID";
		storeManagerSelector.reset( new Mockup_Store_Manager_Selector() );
	}

	void teardown()
	{
		// Uninit stuff
	}

	id_t configID;
	shared_ptr< IStore_Manager_Dynamic_Selector<TestDataClass> > storeManagerSelector;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_Manager_Dynamic, example_usage_of_store_manager)
{
	//////////////////////////////////////
	// module mock-up
	class Mockup_Module
	{
	public:
		// store manager selector implementation for Mockup_Module
		class mydata_Store_Manager_Selector : public IStore_Manager_Dynamic_Selector<TestDataClass>
		{
		public:
			mydata_Store_Manager_Selector( std::vector< shared_ptr<IStore_Manager<TestDataClass>> > storeManagerList ) :
				storeManagerList( storeManagerList )
			{}


			shared_ptr< IStore_Manager<TestDataClass> > selectStoreManager(const id_t configID)
			{
				// select store according to config ...
				if ( configID == "SQLite" )
					return this->storeManagerList.at(1);
				else
					return this->storeManagerList.at(0);
			}

			std::vector< shared_ptr<IStore_Manager<TestDataClass>> > storeManagerList;
		};

		// Mockup_Module constructor
		Mockup_Module()
		{
			// list of store managers to be selected
			std::vector< shared_ptr<IStore_Manager<TestDataClass>> > storeManagerList;

			// add ringbuffer store manager 
			storeManagerList.push_back( createStoreManagerRingbuffer() );

			// add SQLite store manager 
			storeManagerList.push_back( createStoreManagerSQLite() );

			// instantiate selector
			this->mydataStoreManagerSelector.reset( new mydata_Store_Manager_Selector( storeManagerList ) );
	
			// the module itself implements IStore_Manager_Dynamic_Selector so we can use -> this
			this->mydataStoreManager.reset( new Store_Manager_Dynamic<TestDataClass>( this->mydataStoreManagerSelector ) );
		}

		shared_ptr< IStore_Manager<TestDataClass> > mydataStoreManager;				// data store manager selecting actual store (manager) according to config
		shared_ptr< IStore_Manager_Dynamic_Selector<TestDataClass> > mydataStoreManagerSelector;					// actual store manager selector

	} module;

	id_t testID = "testID";
	timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// producer / e.g. worker example
	{
		auto mydataStore = module.mydataStoreManager->getReadWriteStore(configID);
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
		auto mydataStore = module.mydataStoreManager->getReadStore(configID);
		CHECK( mydataStore );

		// get data by ID
		auto data = mydataStore->getByID( testID );
		CHECK( data );
		CHECK_EQUAL( testID, data->getconst_id() );
		CHECK_EQUAL( configID, data->getconst_configID() );
		LONGS_EQUAL( testTimestamp, data->getconst_timestamp() );
	}

}

TEST(Store_Manager_Dynamic, getReadStore)
{
	//////////////////////////////////////
	// test initialization
	Store_Manager_Dynamic<TestDataClass> manager(storeManagerSelector);

	//////////////////////////////////////
	// actual test
	shared_ptr< const IStore_Read<TestDataClass> > store = boost::static_pointer_cast<const IStore_Read<TestDataClass>>(manager.getReadStore(configID));
	CHECK( store );
}

TEST(Store_Manager_Dynamic, getReadWriteStore)
{
	//////////////////////////////////////
	// test initialization
	Store_Manager_Dynamic<TestDataClass> manager(storeManagerSelector);

	//////////////////////////////////////
	// actual test
	shared_ptr< IStore_ReadWrite<TestDataClass> > store = boost::static_pointer_cast<IStore_ReadWrite<TestDataClass>>(manager.getReadWriteStore(configID));
	CHECK( store );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific IStore tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_Manager_Dynamic, getReadStore_with_same_configID_should_return_the_same_store)
{
	//////////////////////////////////////
	// test initialization
	Store_Manager_Dynamic<TestDataClass> manager(storeManagerSelector);

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

TEST(Store_Manager_Dynamic, getReadWriteStore_with_same_configID_should_return_the_same_store)
{
	//////////////////////////////////////
	// test initialization
	Store_Manager_Dynamic<TestDataClass> manager(storeManagerSelector);

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

}} // namespace scope

