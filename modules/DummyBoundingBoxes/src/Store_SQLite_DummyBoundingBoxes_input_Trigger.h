// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_DummyBoundingBoxes_input_Trigger.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_SQLite_DummyBoundingBoxes_input_Trigger_def
#define Store_SQLite_DummyBoundingBoxes_input_Trigger_def

#include "stubs/Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_DummyBoundingBoxes_input_Trigger_extended

#ifdef Store_SQLite_DummyBoundingBoxes_input_Trigger_extended
/**
 * Store_SQLite_DummyBoundingBoxes_input_Trigger
 *
 * module: DummyBoundingBoxes
 * description: Trigger pulse used as signal for the generation of a bounding box.
 */
class Store_SQLite_DummyBoundingBoxes_input_Trigger : public Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger {
public:
	/**
	* constructor
	*/
	Store_SQLite_DummyBoundingBoxes_input_Trigger(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_DummyBoundingBoxes_input_Trigger()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_DummyBoundingBoxes_input_Trigger_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger_extended

#ifdef Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger_extended
/**
 * factory for Store_SQLite_DummyBoundingBoxes_input_Trigger
 */
class Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger : public Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger_enabled
#endif // Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger_extended

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_SQLite_DummyBoundingBoxes_input_Trigger_Default.h"

#endif // Store_SQLite_DummyBoundingBoxes_input_Trigger_def