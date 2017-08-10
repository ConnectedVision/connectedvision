// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData( DBConnection& db ) : 
	Store_Manager_Basic<Class_DummyBoundingBoxes_output_ObjectData>( boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_DummyBoundingBoxes_output_ObjectData> >( make_shared<Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData>( db	)) )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::~Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision