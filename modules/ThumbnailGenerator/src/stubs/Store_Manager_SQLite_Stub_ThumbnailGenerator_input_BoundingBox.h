// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox_def
#define Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_ThumbnailGenerator_input_BoundingBox.h"
#include "../Store_SQLite_ThumbnailGenerator_input_BoundingBox.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_ThumbnailGenerator_input_BoundingBox
 */
class Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_ThumbnailGenerator_input_BoundingBox>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox(const Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox & operator = (const Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox_def