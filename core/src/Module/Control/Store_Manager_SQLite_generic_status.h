/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_generic_status.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_Manager_SQLite_generic_status_def
#define Store_Manager_SQLite_generic_status_def

#include "stubs/Store_Manager_SQLite_Stub_generic_status.h"

namespace ConnectedVision {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_generic_status_extended

#ifdef Store_Manager_SQLite_generic_status_extended
/**
 * SQLite store manager for: Store_SQLite_generic_status
 */
class Store_Manager_SQLite_generic_status : public Store_Manager_SQLite_Stub_generic_status {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_generic_status(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_generic_status ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_generic_status()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_generic_status_Default.h"

#endif // Store_Manager_SQLite_generic_status_def