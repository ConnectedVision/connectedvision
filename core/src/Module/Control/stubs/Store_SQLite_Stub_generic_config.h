/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_generic_config.h
// NEVER TOUCH this file!

#ifndef Store_SQLite_Stub_generic_config_def
#define Store_SQLite_Stub_generic_config_def

#include <stdint.h>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <ConnectedVision.h>
#include <DBConnection.h>
#include <IStore.h>
#include <general.h>
#include <DataHandling/Store_SQLite_BaseClass.h>
#include <DataHandling/Store_Manager_Basic.h>

// include classes
#include "../Class_generic_config.h"
#include "../Class_generic_config_aliasID.h"
#include "../Class_generic_config_configFeatures.h"
#include "../Class_generic_config_callback.h"
#include "../Class_generic_config_chain.h"
#include "../Class_generic_config_chain_connections.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_SQLite_generic_config
 *
 * module: 
 * description: config chain
 */
class Store_SQLite_Stub_generic_config :
	public ConnectedVision::DataHandling::Store_SQLite_BaseClass<Class_generic_config>
{

public:
	/**
	* constructor
	*/
	Store_SQLite_Stub_generic_config(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	);

	/**
	* virtual desctructor
	*/
	virtual ~Store_SQLite_Stub_generic_config();

#ifdef ENABLE_SQLITE_SEARCH
public:
	// additional search functions
	/**
	*  Get objects filtered by id
	*/
	virtual std::vector<shared_ptr<const Class_generic_config> > getBy_id(const ConnectedVision::id_t& val);
	/**
	*  Get objects filtered by timestamp
	*/
	virtual std::vector<shared_ptr<const Class_generic_config> > getBy_timestamp(const ConnectedVision::timestamp_t& val);
	/**
	*  Get objects filtered by version
	*/
	virtual std::vector<shared_ptr<const Class_generic_config> > getBy_version(const int64_t& val);
	/**
	*  Get objects filtered by moduleID
	*/
	virtual std::vector<shared_ptr<const Class_generic_config> > getBy_moduleID(const ConnectedVision::id_t& val);
	/**
	*  Get objects filtered by configID
	*/
	virtual std::vector<shared_ptr<const Class_generic_config> > getBy_configID(const ConnectedVision::id_t& val);
#endif

protected:
	// internal functions

	/**
	* read Object from DB
	* @note This function is MANDATORY.
	*
	*	Read table colum fields to object member variables.
	*	Call sqlite3_step() to read all sub/child objects.
	*
	* @return SQLite return code
	*/
	virtual int readObject(
		sqlite3_stmt *stmt,							///< [in] pre-executed SQLite statement
		shared_ptr<const Class_generic_config>& outObj,	///< [out] data object read from DB
		sqlite3 *db									///< [in] SQLite DB object
	);

	/**
	* write Object to DB
	* @note This function is MANDATORY.
	*
	*	Bind object member variables to table colum fields.
	*	This function has to write the whole objects,
	*	i.e. ti has to loop over all sub/child object bind them and call sqlite3_step() for each row.
	*
	* @return SQLite return code
	*/
	virtual int writeObject(
		sqlite3_stmt *stmt,							///< [in] prepared SQLite statement
		const shared_ptr<const Class_generic_config>& obj,	///< [in] data object read from DB
		sqlite3 *db,								///< [in] SQLite DB object
		const int64_t sortID						///< [in] unique index of object
	);

	/**
	* append object internal sort criteria to list
	* @note This function is MANDATORY.
	*/
	virtual void appendObjectGrouping(
		std::vector< Store::SortEntry >& sortList ///< [in/out] list of sort criteria for table rows
	) const;

	/**
	* get name of internal sort criteria column
	* @note This function is MANDATORY.
	*
	* @return column name
	*/
	virtual const std::string objectKey() const;

	// bind functions
	/**
	* bind object values for writing
	*/
	virtual void bind_generic_config(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_generic_config>& obj,					///< [in] data object read from DB
		const int64_t sortID	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_aliasID(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_generic_config_aliasID>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_configFeatures(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_generic_config_configFeatures>& obj,					///< [in] data object read from DB
		const int64_t sortID	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_callback(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_generic_config_callback>& obj,					///< [in] data object read from DB
		const int64_t sortID	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_chain(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_generic_config_chain>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_chain_connections(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_generic_config_chain_connections>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1,	///< [in] unique index of object
		const int64_t idx2	///< [in] sub array index to order sub items
	) const;
};

// --> Do NOT EDIT <--
/**
 * factory for: Store_SQLite_generic_config
 */
class Store_SQLite_Factory_Stub_generic_config :
	public ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_generic_config>
{
public:
	/**
	* constructor
	*	uses DataAllocator_Primitive (new / delete for every object request)
	*/
	Store_SQLite_Factory_Stub_generic_config(
		DBConnection& db			///< [in] DB connection object
	);

	/**
	* virtual desctuctor
	*/
	virtual ~Store_SQLite_Factory_Stub_generic_config();

	/**
	* creates a new store
	*/
	virtual shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > create(
		const id_t configID			///< [in] config ID of requested store (optional)
	);

protected:
	DBConnection& db;
};

} // namespace DataHandling
} // namespace ConnectedVision

#endif // Store_SQLite_Stub_generic_config_def