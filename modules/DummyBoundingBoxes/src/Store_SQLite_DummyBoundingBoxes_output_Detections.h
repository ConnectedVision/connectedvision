/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_DummyBoundingBoxes_output_Detections.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_SQLite_DummyBoundingBoxes_output_Detections_def
#define Store_SQLite_DummyBoundingBoxes_output_Detections_def

#include "stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_Detections.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_DummyBoundingBoxes_output_Detections_extended

#ifdef Store_SQLite_DummyBoundingBoxes_output_Detections_extended
/**
 * Store_SQLite_DummyBoundingBoxes_output_Detections
 *
 * module: DummyBoundingBoxes
 * description: bounding box
 */
class Store_SQLite_DummyBoundingBoxes_output_Detections : public Store_SQLite_Stub_DummyBoundingBoxes_output_Detections {
public:
	/**
	* constructor
	*/
	Store_SQLite_DummyBoundingBoxes_output_Detections(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_DummyBoundingBoxes_output_Detections ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_DummyBoundingBoxes_output_Detections()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_DummyBoundingBoxes_output_Detections_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_DummyBoundingBoxes_output_Detections_extended

#ifdef Store_SQLite_Factory_DummyBoundingBoxes_output_Detections_extended
/**
 * factory for Store_SQLite_DummyBoundingBoxes_output_Detections
 */
class Store_SQLite_Factory_DummyBoundingBoxes_output_Detections : public Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_Detections {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_DummyBoundingBoxes_output_Detections(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_Detections ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_DummyBoundingBoxes_output_Detections()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_DummyBoundingBoxes_output_Detections_enabled
#endif // Store_SQLite_Factory_DummyBoundingBoxes_output_Detections_extended

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_SQLite_DummyBoundingBoxes_output_Detections_Default.h"

#endif // Store_SQLite_DummyBoundingBoxes_output_Detections_def