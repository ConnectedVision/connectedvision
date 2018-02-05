/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/DataAllocator_Pool.h>
#include <CppUTest/TestHarness.h>

#include "MixIn_IDataAllocator.h"

namespace ConnectedVision {
namespace DataHandling {

class TestWrapper_DataAllocator_Pool : public DataAllocator_Pool<TestDataClass>
{
public:
	TestWrapper_DataAllocator_Pool(const int size = 10) : DataAllocator_Pool<TestDataClass>(size), poolSize(size) {};
	const int poolSize;

	// helper functions
	ConnectedVision::mutex& spy_allocatorMutex()
	{
		return this->allocatorMutex;
	}
};

TEST_GROUP(DataAllocator_Pool)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}

	TestWrapper_DataAllocator_Pool allocator;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IDataAllocator tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIXIN_APPLY(DataAllocator_Pool, MixIn_IDataAllocator, IDataAllocator_tests)
{
	params.allocator = &allocator;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific DataAllocator_Pool tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(DataAllocator_Pool, reuse)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_DataAllocator_Pool allocator(2);

	//////////////////////////////////////
	// actual test
	auto dataTmp1 = allocator.create();
	CHECK( dataTmp1 );

	auto data = allocator.create();
	CHECK( data );
	data->set_id("IDdata");
	LONGS_EQUAL(2, data->spy_clearCount() );
	auto ptr = data.get(); // get raw pointer

	auto dataTmp2 = allocator.create();
	CHECK(! dataTmp2 );

	// release pointer
	auto constData = allocator.make_const(data);
	allocator.initiateRelease(constData);
	CHECK( data == NULL );

	// reuse
	auto nouse = ConnectedVision::make_shared<TestDataClass>(); // make sure that memory layout is different
	data = allocator.create();
	CHECK( data );
	CHECK_EQUAL("", data->getconst_id());
	CHECK_TEXT( ptr == data.get(), "object instance is not reused");
	LONGS_EQUAL(3, data->spy_clearCount() );
}

TEST(DataAllocator_Pool, try_to_initiateRelease_double)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_DataAllocator_Pool allocator(1);

	//////////////////////////////////////
	// actual test
	auto data = allocator.create();
	CHECK( data );

	// make writable copy
	auto ptrCopy = data;

	// release original pointer
	ConnectedVision::shared_ptr<const TestDataClass> dataConst = make_dataConst(data);
	allocator.initiateRelease(dataConst);
	CHECK( !dataConst );

	// object is still in use, so we have no available object in the pool
	CHECK( !allocator.create() );

	// release copy of pointer
	auto constData = make_dataConst(ptrCopy);
	allocator.initiateRelease( constData );

	// reuse
	auto nouse = ConnectedVision::make_shared<TestDataClass>(); // make sure that memory layout is different
	CHECK( allocator.create() );
}

TEST(DataAllocator_Pool, synchronization_lock)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_DataAllocator_Pool allocator;
	auto data = allocator.create();
	auto dataConst = allocator.make_const(data);

	//////////////////////////////////////
	// actual test
	ConnectedVision::Lock lock( allocator.spy_allocatorMutex() );

	CHECK_THROWS( ConnectedVision::mutex_error, allocator.create() );

	CHECK_THROWS( ConnectedVision::mutex_error, allocator.initiateRelease(dataConst) );
}


TEST(DataAllocator_Pool, forgotten_objects_are_reused)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_DataAllocator_Pool allocator(1);

	//////////////////////////////////////
	// actual test
	{
		// get object in scope
		auto data = allocator.create();
		CHECK( data );

		auto dataX = allocator.create();
		CHECK( !dataX );
	}

	// now the object is out of scope and should be available again
	auto data2 = allocator.create();
	CHECK( data2 );
}

TEST(DataAllocator_Pool, external_objects_are_not_added_to_pool)
{
	//////////////////////////////////////
	// test initialization
	TestWrapper_DataAllocator_Pool allocator(1);
	ConnectedVision::shared_ptr<const TestDataClass> extObj = boost::static_pointer_cast<const TestDataClass>(ConnectedVision::make_shared<TestDataClass>());

	//////////////////////////////////////
	// actual test

	// get only object in pool
	auto dataObj = allocator.create();
	CHECK( dataObj );

	// there are no more objects
	CHECK( !allocator.create() );

	// external object is not added to pool
	allocator.initiateRelease(extObj);
	CHECK( !extObj );
	CHECK( !allocator.create() ); // there is still no available object in the pool
}


}} // namespace scope

