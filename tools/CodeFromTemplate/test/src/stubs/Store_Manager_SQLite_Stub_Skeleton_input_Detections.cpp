// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_SQLite_Stub_Skeleton_input_Detections.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace test {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_SQLite_Stub_Skeleton_input_Detections::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_Skeleton_input_Detections::Store_Manager_SQLite_Stub_Skeleton_input_Detections( DBConnection& db ) : 
	Store_Manager_Basic<Class_Skeleton_input_Detections>( boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_Skeleton_input_Detections> >( make_shared<Store_SQLite_Factory_Skeleton_input_Detections>( db	)) )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_SQLite_Stub_Skeleton_input_Detections allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_Skeleton_input_Detections::~Store_Manager_SQLite_Stub_Skeleton_input_Detections()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace test
} // namespace ConnectedVision