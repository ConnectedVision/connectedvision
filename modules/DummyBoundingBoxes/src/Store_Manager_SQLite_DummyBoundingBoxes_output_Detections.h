/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_DummyBoundingBoxes_output_Detections.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_def
#define Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_def

#include "stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_extended

#ifdef Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_extended
/**
 * SQLite store manager for: Store_SQLite_DummyBoundingBoxes_output_Detections
 */
class Store_Manager_SQLite_DummyBoundingBoxes_output_Detections : public Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_DummyBoundingBoxes_output_Detections(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_Detections ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_DummyBoundingBoxes_output_Detections()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_Default.h"

#endif // Store_Manager_SQLite_DummyBoundingBoxes_output_Detections_def