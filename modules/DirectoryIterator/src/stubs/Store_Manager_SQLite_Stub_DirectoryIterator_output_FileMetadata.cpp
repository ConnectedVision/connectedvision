// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata::Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata( DBConnection& db ) : 
	Store_Manager_Basic<Class_DirectoryIterator_output_FileMetadata>( boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_DirectoryIterator_output_FileMetadata> >( make_shared<Store_SQLite_Factory_DirectoryIterator_output_FileMetadata>( db	)) )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata::~Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision