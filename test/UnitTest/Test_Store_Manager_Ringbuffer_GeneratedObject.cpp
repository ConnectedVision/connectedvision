/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "generated/Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode.h"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {
namespace UnitTest {

namespace DataHandling {

TEST_GROUP(Store_Manager_Ringbuffer_GeneratedObject)
{
	void setup()
	{}

	void teardown()
	{}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store_Manager_Ringbuffer_GeneratedObject tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


TEST(Store_Manager_Ringbuffer_GeneratedObject, example_usage_of_store_manager)
{
	static const int64_t storeCount = 2;
	static const int64_t ringbufferSize = 10;
	static const int64_t poolSize = storeCount*ringbufferSize + 5;	

	const id_t configID = "testConfigID";
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// store manager

	DataHandling::Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode mydataStoreManager(
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

TEST(Store_Manager_Ringbuffer_GeneratedObject, only_one_storeManager_can_be_created)
{
	static const int64_t storeCount = 2;
	static const int64_t ringbufferSize = 10;
	static const int64_t poolSize = storeCount*ringbufferSize + 5;	

	const id_t configID = "testConfigID";
	const id_t testID = "testID";
	const timestamp_t testTimestamp = 12345000;

	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	
	// create first instance
	auto storeManager = make_shared<DataHandling::Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode>(storeCount, ringbufferSize, poolSize);
	CHECK( storeManager );

	// try to create second instance
	CHECK_THROWS( ConnectedVision::runtime_error, new Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode(storeCount, ringbufferSize, poolSize) );

	// release and recreate
	storeManager.reset();
	CHECK( !storeManager );
	storeManager = make_shared<Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode>(storeCount, ringbufferSize, poolSize);
	CHECK( storeManager );
}

} // namespace DataHandling

} // namespace UnitTest
} // namespace ConnectedVision





