// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_Skeleton_output_Average.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_Manager_SQLite_Skeleton_output_Average_def
#define Store_Manager_SQLite_Skeleton_output_Average_def

#include "stubs/Store_Manager_SQLite_Stub_Skeleton_output_Average.h"

namespace ConnectedVision {
namespace test {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_Skeleton_output_Average_extended

#ifdef Store_Manager_SQLite_Skeleton_output_Average_extended
/**
 * SQLite store manager for: Store_SQLite_Skeleton_output_Average
 */
class Store_Manager_SQLite_Skeleton_output_Average : public Store_Manager_SQLite_Stub_Skeleton_output_Average {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Skeleton_output_Average(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_Skeleton_output_Average ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Skeleton_output_Average()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace test
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_Skeleton_output_Average_Default.h"

#endif // Store_Manager_SQLite_Skeleton_output_Average_def