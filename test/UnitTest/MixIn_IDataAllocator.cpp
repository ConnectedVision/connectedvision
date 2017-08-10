/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <IStore.h>

#include <CppUTest/TestHarness.h>

#include "MixIn_IDataAllocator.h"

namespace ConnectedVision 
{ namespace DataHandling
{

MIXIN_GROUP(MixIn_IDataAllocator)
{
	void setup() 
	{}
	void teardown()	
	{}
};

MIXIN_TEST(MixIn_IDataAllocator, create)
{
	//////////////////////////////////////
	// actual test
	auto data = params.allocator->create();
	CHECK(data);
	CHECK(data->spy_clearCount() > 0);
}

MIXIN_TEST(MixIn_IDataAllocator, initiateRelease)
{
	//////////////////////////////////////
	// actual test
	auto data = params.allocator->create();
	CHECK(data);
	auto dataConst = make_dataConst(data);
	params.allocator->initiateRelease(dataConst);
	CHECK(!dataConst);
}

MIXIN_TEST(MixIn_IDataAllocator, make_const)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestDataClass> data, dataCopy;
	ConnectedVision::shared_ptr<const TestDataClass> dataConst;

	//////////////////////////////////////
	// actual test
	data = params.allocator->create();
	CHECK(data);
	dataConst = params.allocator->make_const(data);
	CHECK(!data);
	CHECK(dataConst);

	// NULL ptr
	data.reset();
	dataConst = params.allocator->make_const(data);
	CHECK(!data);
	CHECK(dataConst == NULL);

	// illegaly hold copy
	data = params.allocator->create();
	dataCopy = data;
	CHECK_THROWS(ConnectedVision::runtime_error, params.allocator->make_const(data) );
	CHECK(data);

}


}} // namespace scope
