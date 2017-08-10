// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_Skeleton_input_Detections.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_SQLite_Skeleton_input_Detections_def
#define Store_SQLite_Skeleton_input_Detections_def

#include "stubs/Store_SQLite_Stub_Skeleton_input_Detections.h"

namespace ConnectedVision {
namespace test {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Skeleton_input_Detections_extended

#ifdef Store_SQLite_Skeleton_input_Detections_extended
/**
 * Store_SQLite_Skeleton_input_Detections
 *
 * module: Skeleton Module
 * description: bounding box
 */
class Store_SQLite_Skeleton_input_Detections : public Store_SQLite_Stub_Skeleton_input_Detections {
public:
	/**
	* constructor
	*/
	Store_SQLite_Skeleton_input_Detections(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_Skeleton_input_Detections ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Skeleton_input_Detections()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_Skeleton_input_Detections_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_Skeleton_input_Detections_extended

#ifdef Store_SQLite_Factory_Skeleton_input_Detections_extended
/**
 * factory for Store_SQLite_Skeleton_input_Detections
 */
class Store_SQLite_Factory_Skeleton_input_Detections : public Store_SQLite_Factory_Stub_Skeleton_input_Detections {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_Skeleton_input_Detections(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_Skeleton_input_Detections ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_Skeleton_input_Detections()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_Skeleton_input_Detections_enabled
#endif // Store_SQLite_Factory_Skeleton_input_Detections_extended

} // namespace DataHandling
} // namespace test
} // namespace ConnectedVision

#include "stubs/Store_SQLite_Skeleton_input_Detections_Default.h"

#endif // Store_SQLite_Skeleton_input_Detections_def