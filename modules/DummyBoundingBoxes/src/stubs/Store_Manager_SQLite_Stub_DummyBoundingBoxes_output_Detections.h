// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections_def
#define Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_DummyBoundingBoxes_output_Detections.h"
#include "../Store_SQLite_DummyBoundingBoxes_output_Detections.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_DummyBoundingBoxes_output_Detections
 */
class Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_DummyBoundingBoxes_output_Detections>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections(const Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections & operator = (const Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections_def