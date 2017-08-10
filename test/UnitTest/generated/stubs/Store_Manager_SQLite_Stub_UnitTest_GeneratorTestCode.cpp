// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode::Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode( DBConnection& db ) : 
	Store_Manager_Basic<Class_UnitTest_GeneratorTestCode>( boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_UnitTest_GeneratorTestCode> >( make_shared<Store_SQLite_Factory_UnitTest_GeneratorTestCode>( db	)) )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode::~Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision