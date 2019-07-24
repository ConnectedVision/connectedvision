// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger_def
#define Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_DummyBoundingBoxes_input_Trigger.h"
#include "../Store_SQLite_DummyBoundingBoxes_input_Trigger.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_DummyBoundingBoxes_input_Trigger
 */
class Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_DummyBoundingBoxes_input_Trigger>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger(const Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger & operator = (const Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger_def