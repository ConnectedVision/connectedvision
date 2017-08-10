/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <DataHandling/DataAllocator_Primitive.h>

#include <CppUTest/TestHarness.h>

#include "MixIn_IDataAllocator.h"

namespace ConnectedVision {
namespace DataHandling {

class TestWrapper_DataAllocator_Primitive : public DataAllocator_Primitive<TestDataClass>
{
public:
	TestWrapper_DataAllocator_Primitive() : DataAllocator_Primitive<TestDataClass>() {};
	static const int poolSize = 10;
};


TEST_GROUP(DataAllocator_Primitive)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}

	TestWrapper_DataAllocator_Primitive allocator;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  general IDataAllocator tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

MIXIN_APPLY(DataAllocator_Primitive, MixIn_IDataAllocator, IDataAllocator_tests)
{
	params.allocator = &allocator;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  specific DataAllocator_Primitive tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}} // namespace scope

