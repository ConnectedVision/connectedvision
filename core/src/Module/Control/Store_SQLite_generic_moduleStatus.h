/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_generic_moduleStatus.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_SQLite_generic_moduleStatus_def
#define Store_SQLite_generic_moduleStatus_def

#include "stubs/Store_SQLite_Stub_generic_moduleStatus.h"

namespace ConnectedVision {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_generic_moduleStatus_extended

#ifdef Store_SQLite_generic_moduleStatus_extended
/**
 * Store_SQLite_generic_moduleStatus
 *
 * module: 
 * description: Module Status Schema
 */
class Store_SQLite_generic_moduleStatus : public Store_SQLite_Stub_generic_moduleStatus {
public:
	/**
	* constructor
	*/
	Store_SQLite_generic_moduleStatus(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_generic_moduleStatus ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_generic_moduleStatus()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_generic_moduleStatus_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_generic_moduleStatus_extended

#ifdef Store_SQLite_Factory_generic_moduleStatus_extended
/**
 * factory for Store_SQLite_generic_moduleStatus
 */
class Store_SQLite_Factory_generic_moduleStatus : public Store_SQLite_Factory_Stub_generic_moduleStatus {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_generic_moduleStatus(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_generic_moduleStatus ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_generic_moduleStatus()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_generic_moduleStatus_enabled
#endif // Store_SQLite_Factory_generic_moduleStatus_extended

} // namespace DataHandling
} // namespace ConnectedVision

#include "stubs/Store_SQLite_generic_moduleStatus_Default.h"

#endif // Store_SQLite_generic_moduleStatus_def