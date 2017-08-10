// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// --> Do NOT EDIT <--
int Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::creationCount = 0;

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata( DBConnection& db ) : 
	Store_Manager_Basic<Class_ThumbnailGenerator_input_ImageMetadata>( boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_ThumbnailGenerator_input_ImageMetadata> >( make_shared<Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata>( db	)) )
{
	if ( creationCount > 0 )
	{
		// we have one instance already
		throw ConnectedVision::runtime_error("just one instance of Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata allowed");
	}
	creationCount = 1;
}

// --> Do NOT EDIT <--
Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::~Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata()
{
	creationCount = 0; 
}

} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision