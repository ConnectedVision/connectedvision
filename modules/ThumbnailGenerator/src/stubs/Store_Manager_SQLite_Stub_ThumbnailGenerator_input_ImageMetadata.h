// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata_def
#define Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_ThumbnailGenerator_input_ImageMetadata.h"
#include "../Store_SQLite_ThumbnailGenerator_input_ImageMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_ThumbnailGenerator_input_ImageMetadata
 */
class Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_ThumbnailGenerator_input_ImageMetadata>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata(const Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata & operator = (const Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata_def