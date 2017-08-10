// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode::Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode(const int64_t storeCount, const int64_t ringbufferSize, const int64_t poolSize) :
	ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_UnitTest_GeneratorTestCode> ( storeCount, ringbufferSize, poolSize )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode::~Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision