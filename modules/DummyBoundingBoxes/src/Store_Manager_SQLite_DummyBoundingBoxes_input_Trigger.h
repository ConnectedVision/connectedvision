// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_def
#define Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_def

#include "stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_extended

#ifdef Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_extended
/**
 * SQLite store manager for: Store_SQLite_DummyBoundingBoxes_input_Trigger
 */
class Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger : public Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_DummyBoundingBoxes_input_Trigger ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_Default.h"

#endif // Store_Manager_SQLite_DummyBoundingBoxes_input_Trigger_def