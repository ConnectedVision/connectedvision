/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <algorithm>
#include <cctype>
#include <string>

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>
#include <Module/OutputPins/OutputPin_JSON.h>
#include <Module/Control/Class_generic_config.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_DataHandling.hpp"
#include "MixIn_IStore.h"

namespace ConnectedVision {
namespace OutputPins {

using namespace ConnectedVision::DataHandling;

typedef OutputPin_JSON<TestDataClass> TestWrapper_OutputPin;

static StoreEnvironment<TestDataClass> env;

TEST_GROUP(OutputPin_JSON)
{
	void setup()
	{
		// Init stuff
		config.set_id(env.configID);

		dataStoreManager.reset(	new Store_Manager_Ringbuffer_Pool<TestDataClass>(
			2,		// number of stores in manager
			10,		// number of element slots in ringbuffer
			20		// total number of available objects (for all ring buffers)
		));
		
		auto store = dataStoreManager->getReadWriteStore(env.configID);
		dataList = env.fillStoreWithData(*store, 10, env.configID);
	}

	void teardown()
	{
		// Uninit stuff
	}

	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TestDataClass> > dataStoreManager;
	Class_generic_config config;
	std::vector< shared_ptr<const TestDataClass> > dataList;
};

#define RESPONSE_OK	200
#define RESPONSE_NOT_FOUND	404

static inline std::string remove_whitespace(const std::string &inputStr)
{
	std::string str( inputStr );
	//str.erase(std::remove_if(str.begin(), str.end(), std::isspace), str.end());
	str.erase(std::remove_if(str.begin(), str.end(), [](char c){ return std::isspace(static_cast<unsigned char>(c)); }), str.end());

	return str;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  OutputPin tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(OutputPin_JSON, initStore)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	TestWrapper_OutputPin outputPin(dataStoreManager);
	outputPin.init( config.toJsonStr() );
	CHECK_EQUAL( env.configID, outputPin.get_configID() );
}


TEST(OutputPin_JSON, getByID_should_return_JSON_encoded_data)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	//////////////////////////////////////
	// actual test

	size_t index = 0;
	LONGS_EQUAL( RESPONSE_OK, outputPin.getByID(dataList[index]->getconst_id(), response) );
	CHECK_EQUAL( "application/json", response.getContentType() );
	CHECK_EQUAL( dataList[index]->toJsonStr(), response.getContent() );
}

TEST(OutputPin_JSON, getByID_should_return_NOT_FOUND_if_not_in_store)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( RESPONSE_NOT_FOUND, outputPin.getByID("???", response) );
}

TEST(OutputPin_JSON, getByIndex_should_return_JSON_encoded_data)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	//////////////////////////////////////
	// actual test

	size_t index = 0;
	LONGS_EQUAL( RESPONSE_OK, outputPin.getByIndex(index, response) );
	CHECK_EQUAL( "application/json", response.getContentType() );
	CHECK_EQUAL( dataList[index]->toJsonStr(), response.getContent() );
}

TEST(OutputPin_JSON, getByIndex_should_return_NOT_FOUND_if_not_in_store)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( RESPONSE_NOT_FOUND, outputPin.getByIndex(1000, response) );
}

TEST(OutputPin_JSON, getByIndexRange_should_return_JSON_encoded_array)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	//////////////////////////////////////
	// actual test

	size_t index = 0;
	LONGS_EQUAL( RESPONSE_OK, outputPin.getByIndexRange(index, index+1, response) );
	CHECK_EQUAL( "application/json", response.getContentType() );
	std::string str = "[" + dataList[index]->toJsonStr() + "," + dataList[index+1]->toJsonStr() + "]";
	CHECK_EQUAL( remove_whitespace( str ), remove_whitespace( response.getContent() ));
}

TEST(OutputPin_JSON, getByIndexRange_should_return_NOT_FOUND_if_range_is_out_of_store_data_range)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	// data
	auto store = dataStoreManager->getReadWriteStore(env.configID);
	auto dataRange = store->getDataRange();

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( RESPONSE_NOT_FOUND, outputPin.getByIndexRange((dataRange.indexStart-1), (dataRange.indexStart-1), response) );
	LONGS_EQUAL( RESPONSE_NOT_FOUND, outputPin.getByIndexRange((dataRange.indexEnd+1), (dataRange.indexEnd+1), response) );
}

TEST(OutputPin_JSON, getByIndexRange_should_return_an_empty_array_if_not_found_but_within_store_data_range)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	// data
	auto store = dataStoreManager->getReadWriteStore(env.configID);
	auto dataRange = store->getDataRange();

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( RESPONSE_OK, outputPin.getByIndexRange(0, 0, response) );
}

TEST(OutputPin_JSON, getAllInTimespan_should_return_NOT_FOUND_if_range_is_out_of_store_data_range)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	// data
	auto store = dataStoreManager->getReadWriteStore(env.configID);
	auto dataRange = store->getDataRange();

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( RESPONSE_NOT_FOUND, outputPin.getAllInTimespan((dataRange.timestampStart-1), (dataRange.timestampStart-1), response) );
	LONGS_EQUAL( RESPONSE_NOT_FOUND, outputPin.getAllInTimespan((dataRange.timestampEnd+1), (dataRange.timestampEnd+1), response) );
}

TEST(OutputPin_JSON, getAllInTimespan_should_return_an_empty_array_if_not_found_but_within_store_data_range)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_OutputPin outputPin(dataStoreManager); outputPin.init( config.toJsonStr() );

	// response
	ConnectedVisionResponse response;

	// data
	auto store = dataStoreManager->getReadWriteStore(env.configID);
	auto dataRange = store->getDataRange();

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL( RESPONSE_OK, outputPin.getAllInTimespan((dataRange.timestampStart+1), (dataRange.timestampStart+1), response) );
}

}} // namespace scope

