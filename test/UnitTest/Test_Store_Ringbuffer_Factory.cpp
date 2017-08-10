/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/Store_Ringbuffer.h>

#include <CppUTest/TestHarness.h>

#include "TestHelper_DataHandling.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{


TEST_GROUP(Store_Ringbuffer_Factory)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific IStore_ReadWrite_Factory tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Store_Ringbuffer_Factory, initFactory_with_negative_or_zero_size_should_throw)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	CHECK_THROWS(ConnectedVision::runtime_error, Store_Ringbuffer_Factory<TestDataClass>(-10) );
	CHECK_THROWS(ConnectedVision::runtime_error, Store_Ringbuffer_Factory<TestDataClass>(-1) );
	CHECK_THROWS(ConnectedVision::runtime_error, Store_Ringbuffer_Factory<TestDataClass>(0) );
	Store_Ringbuffer_Factory<TestDataClass> factory(1); // OK
}

TEST(Store_Ringbuffer_Factory, createStore)
{
	//////////////////////////////////////
	// test initialization
	const int ringbufferSize = 10;
	Store_Ringbuffer_Factory<TestDataClass> factory(ringbufferSize);

	//////////////////////////////////////
	// actual test
	shared_ptr< IStore_ReadWrite<TestDataClass> > store = factory.create();
	CHECK( store );
}

}} // namespace scope

