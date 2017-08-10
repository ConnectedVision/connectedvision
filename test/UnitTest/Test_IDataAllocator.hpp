/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Test_IDataAllocator_code
#define Test_IDataAllocator_code

#include "IStore.h"

namespace ConnectedVision 
{ namespace DataHandling
{

template <class TDataClass>
static void IDataAllocatorTest_create(IDataAllocator<TDataClass>& allocator)
{
	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TDataClass> data = allocator.create();
	CHECK(data);
	CHECK(data->spy_clearCount() > 0);
}

template <class TDataClass>
static void IDataAllocatorTest_initiateRelease(IDataAllocator<TDataClass>& allocator)
{
	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TDataClass> data = allocator.create();
	CHECK(data);
	auto dataConst = make_dataConst(data);
	allocator.initiateRelease(dataConst);
	CHECK(!dataConst);
}

template <class TDataClass>
static void IDataAllocatorTest_make_const(IDataAllocator<TDataClass>& allocator)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TDataClass> data, dataCopy;
	ConnectedVision::shared_ptr<const TDataClass> dataConst;

	//////////////////////////////////////
	// actual test
	data = allocator.create();
	CHECK(data);
	dataConst = allocator.make_const(data);
	CHECK(!data);
	CHECK(dataConst);

	// NULL ptr
	data.reset();
	dataConst = allocator.make_const(data);
	CHECK(!data);
	CHECK(dataConst == NULL);

	// illegaly hold copy
	data = allocator.create();
	dataCopy = data;
	CHECK_THROWS(ConnectedVision::runtime_error, allocator.make_const(data) );
	CHECK(data);

}


}} // namespace scope

#endif // Test_IDataAllocator_code