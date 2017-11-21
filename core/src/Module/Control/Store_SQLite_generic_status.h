/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_generic_status.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_SQLite_generic_status_def
#define Store_SQLite_generic_status_def

#include "DataHandling/Store_Cache.h"
#include "stubs/Store_SQLite_Stub_generic_status.h"

namespace ConnectedVision {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
#define Store_SQLite_generic_status_extended

#ifdef Store_SQLite_generic_status_extended
/**
 * Store_SQLite_generic_status
 *
 * module: 
 * description: config status
 */
class Store_SQLite_generic_status : public Store_Cache<Class_generic_status>
{
public: 
	/**
	* constructor
	*/
	Store_SQLite_generic_status(
		const id_t& configID,			///< [in] config ID
		DBConnection& db,				///< [in] DB connection object
		const int64_t cacheSize = 100	///< [in] number of maximal elements in cache
	) : Store_Cache<Class_generic_status>(configID, cacheSize, 
		static_cast<shared_ptr< IStore_ReadWrite<Class_generic_status> >>(make_shared< Store_SQLite_Stub_generic_status >(configID, db)) )
	{}
	virtual ~Store_SQLite_generic_status() {}

	// overwrite write through
	virtual bool write_through(	const shared_ptr<const Class_generic_status>& statusConst )
	{
		// status is not running -> alwasy write to base store
		if ( !statusConst->is_status_running() )
			return true;

		Store_SQLite_generic_status::CacheLock lock(this->cacheMutex);

		// search cache for existing entry
		auto it = this->cache.find( statusConst->getconst_id() );
		if ( it != this->cache.end() )
		{
			// already in cache
			if ( it->second.data->is_status_running() )
				return false;
		}

		return true;
	}

};
#endif // Store_SQLite_generic_status_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_generic_status_extended

#ifdef Store_SQLite_Factory_generic_status_extended
/**
 * factory for Store_SQLite_generic_status
 */
class Store_SQLite_Factory_generic_status : public Store_SQLite_Factory_Stub_generic_status {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_generic_status(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_generic_status ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_generic_status()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_generic_status_enabled
#endif // Store_SQLite_Factory_generic_status_extended

} // namespace DataHandling
} // namespace ConnectedVision

#include "stubs/Store_SQLite_generic_status_Default.h"

#endif // Store_SQLite_generic_status_def