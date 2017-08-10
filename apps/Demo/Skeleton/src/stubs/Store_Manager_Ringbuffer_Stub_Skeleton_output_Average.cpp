// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_Ringbuffer_Stub_Skeleton_output_Average.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_Ringbuffer_Stub_Skeleton_output_Average::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_Ringbuffer_Stub_Skeleton_output_Average::Store_Manager_Ringbuffer_Stub_Skeleton_output_Average(const int64_t storeCount, const int64_t ringbufferSize, const int64_t poolSize) :
	ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_Skeleton_output_Average> ( storeCount, ringbufferSize, poolSize )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_Ringbuffer_Stub_Skeleton_output_Average allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_Ringbuffer_Stub_Skeleton_output_Average::~Store_Manager_Ringbuffer_Stub_Skeleton_output_Average()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision