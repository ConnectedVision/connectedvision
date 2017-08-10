// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_UnitTest_GeneratorTestCode.h
// NEVER TOUCH this file!
#ifndef Store_SQLite_Stub_UnitTest_GeneratorTestCode_def
#define Store_SQLite_Stub_UnitTest_GeneratorTestCode_def

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
#include "../Class_UnitTest_GeneratorTestCode.h"
#include "../Class_UnitTest_GeneratorTestCode_objArray.h"
#include "../Class_UnitTest_GeneratorTestCode_simpleObject.h"
#include "../Class_UnitTest_GeneratorTestCode_complexObject.h"
#include "../Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_SQLite_UnitTest_GeneratorTestCode
 *
 * module: 
 * description: test object to check generator
 */
class Store_SQLite_Stub_UnitTest_GeneratorTestCode :
	public ConnectedVision::DataHandling::Store_SQLite_BaseClass<Class_UnitTest_GeneratorTestCode>
{

public:
	/**
	* constructor
	*/
	Store_SQLite_Stub_UnitTest_GeneratorTestCode(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	);

	/**
	* virtual desctructor
	*/
	virtual ~Store_SQLite_Stub_UnitTest_GeneratorTestCode();

#ifdef ENABLE_SQLITE_SEARCH
public:
	// additional search functions
	/**
	*  Get objects filtered by configID
	*/
	virtual std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > getBy_configID(const ConnectedVision::id_t& val);
	/**
	*  Get objects filtered by id
	*/
	virtual std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > getBy_id(const ConnectedVision::id_t& val);
	/**
	*  Get objects filtered by timestamp
	*/
	virtual std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > getBy_timestamp(const ConnectedVision::timestamp_t& val);
	/**
	*  Get objects filtered by boolVal
	*/
	virtual std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > getBy_boolVal(const bool& val);
	/**
	*  Get objects filtered by intVal
	*/
	virtual std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > getBy_intVal(const int64_t& val);
	/**
	*  Get objects filtered by numberVal
	*/
	virtual std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > getBy_numberVal(const double& val);
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
		shared_ptr<const Class_UnitTest_GeneratorTestCode>& outObj,	///< [out] data object read from DB
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
		const shared_ptr<const Class_UnitTest_GeneratorTestCode>& obj,	///< [in] data object read from DB
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
	virtual void bind_UnitTest_GeneratorTestCode(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode>& obj,					///< [in] data object read from DB
		const int64_t sortID	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_simpleArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const int64_t& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_stringArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const std::string>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_intArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const int64_t& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1,	///< [in] unique index of object
		const int64_t idx2,	///< [in] unique index of object
		const int64_t idx3	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_floatArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const double& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1,	///< [in] unique index of object
		const int64_t idx2,	///< [in] unique index of object
		const int64_t idx3	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_objArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_objArray>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_objArray_subArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const std::string>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1,	///< [in] unique index of object
		const int64_t idx2	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_simpleObject(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_simpleObject>& obj,					///< [in] data object read from DB
		const int64_t sortID	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_complexObject(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_complexObject>& obj,					///< [in] data object read from DB
		const int64_t sortID	///< [in] sub array index to order sub items
	) const;
	/**
	* bind object values for writing
	*/
	virtual void bind_complexObject_subObjectArray(
		sqlite3_stmt *stmt, 							///< [in/out] SQLite statement to bind with
		const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>& obj,					///< [in] data object read from DB
		const int64_t sortID,	///< [in] unique index of object
		const int64_t idx1,	///< [in] unique index of object
		const int64_t idx2	///< [in] sub array index to order sub items
	) const;
};

// --> Do NOT EDIT <--
/**
 * factory for: Store_SQLite_UnitTest_GeneratorTestCode
 */
class Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode :
	public ConnectedVision::DataHandling::IStore_ReadWrite_Factory<Class_UnitTest_GeneratorTestCode>
{
public:
	/**
	* constructor
	*	uses DataAllocator_Primitive (new / delete for every object request)
	*/
	Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode(
		DBConnection& db			///< [in] DB connection object
	);

	/**
	* virtual desctuctor
	*/
	virtual ~Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode();

	/**
	* creates a new store
	*/
	virtual shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_UnitTest_GeneratorTestCode> > create(
		const id_t configID			///< [in] config ID of requested store (optional)
	);

protected:
	DBConnection& db;
};

} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision

#endif // Store_SQLite_Stub_UnitTest_GeneratorTestCode_def