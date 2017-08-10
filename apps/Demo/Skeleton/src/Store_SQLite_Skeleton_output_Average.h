/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_Skeleton_output_Average.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_SQLite_Skeleton_output_Average_def
#define Store_SQLite_Skeleton_output_Average_def

#include "stubs/Store_SQLite_Stub_Skeleton_output_Average.h"

namespace ConnectedVision {
namespace Module {
namespace Skeleton {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Skeleton_output_Average_extended

#ifdef Store_SQLite_Skeleton_output_Average_extended
/**
 * Store_SQLite_Skeleton_output_Average
 *
 * module: Skeleton Module
 * description: This is a completely senseless output pin providing the average color of the area in the bounding box.
 */
class Store_SQLite_Skeleton_output_Average : public Store_SQLite_Stub_Skeleton_output_Average {
public:
	/**
	* constructor
	*/
	Store_SQLite_Skeleton_output_Average(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_Skeleton_output_Average ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Skeleton_output_Average()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_Skeleton_output_Average_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_Skeleton_output_Average_extended

#ifdef Store_SQLite_Factory_Skeleton_output_Average_extended
/**
 * factory for Store_SQLite_Skeleton_output_Average
 */
class Store_SQLite_Factory_Skeleton_output_Average : public Store_SQLite_Factory_Stub_Skeleton_output_Average {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_Skeleton_output_Average(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_Skeleton_output_Average ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_Skeleton_output_Average()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_Skeleton_output_Average_enabled
#endif // Store_SQLite_Factory_Skeleton_output_Average_extended

} // namespace DataHandling
} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_SQLite_Skeleton_output_Average_Default.h"

#endif // Store_SQLite_Skeleton_output_Average_def