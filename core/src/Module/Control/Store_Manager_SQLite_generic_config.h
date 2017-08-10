/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_generic_config.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_Manager_SQLite_generic_config_def
#define Store_Manager_SQLite_generic_config_def

#include "stubs/Store_Manager_SQLite_Stub_generic_config.h"

namespace ConnectedVision {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_generic_config_extended

#ifdef Store_Manager_SQLite_generic_config_extended
/**
 * SQLite store manager for: Store_SQLite_generic_config
 */
class Store_Manager_SQLite_generic_config : public Store_Manager_SQLite_Stub_generic_config {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_generic_config(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_generic_config ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_generic_config()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_generic_config_Default.h"

#endif // Store_Manager_SQLite_generic_config_def