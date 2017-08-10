/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef TestHelper_Store_SQLite_code
#define TestHelper_Store_SQLite_code

#include <boost/assign/list_of.hpp>

#include "IStore.h"
#include "DataHandling/Store_SQLite_BaseClass.h"

#include "TestHelper_DataHandling.hpp"

namespace ConnectedVision {
namespace DataHandling {

namespace TestWrapper_Store_SQLite_Table 
{
static const std::string tableName = "Test_Store_SQLite_table";
static const std::vector<std::string> columnDesc = 
	boost::assign::list_of("'_sortID' BIGINT NOT NULL DEFAULT '0'")
							("'configID' VARCHAR(32) NOT NULL DEFAULT '' /* ID of config chain (string) */")
							("'id' VARCHAR(32) NOT NULL DEFAULT '' /* detection ID (string) */")
							("'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */")
							("'x' BIGINT NOT NULL DEFAULT '0' /* test name with one character */");
}

/**
 * simple test SQLite store
 *
 * implementing IStore_ReadWrite interface
 */
class TestWrapper_Store_SQLite : public Store_SQLite_BaseClass<TestDataClass>
{
public:
	TestWrapper_Store_SQLite(
		const id_t& configID,			///< [in] config ID
		DBConnection& db,				///< [in] DB connection object
		const std::vector<std::string> columnDesc = TestWrapper_Store_SQLite_Table::columnDesc		///< [in] default column description
	) : Store_SQLite_BaseClass(configID, db, TestWrapper_Store_SQLite_Table::tableName, columnDesc)
	{};


	// implement abstract methodes
	
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
		sqlite3_stmt *stmt,						///< [in] pre-executed SQLite statement
		shared_ptr<const TestDataClass>& outObj,	///< [out] data object read from DB
		sqlite3 *db								///< [in] SQLite DB object
	)
	{
		int error = SQLITE_ROW;

		outObj.reset();
		auto obj = this->create();

		// process row
		if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
			obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
		if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
			obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,2) ) ) );
		if ( sqlite3_column_type(stmt, 3) != SQLITE_NULL )
			obj->set_timestamp( sqlite3_column_int64(stmt,3) );
		if ( sqlite3_column_type(stmt, 4) != SQLITE_NULL )
			obj->set_x( sqlite3_column_int64(stmt,4) );
		outObj = this->make_const(obj);

		error = sqlite3_step(stmt);
		return error;
	}

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
		const shared_ptr<const TestDataClass>& obj,	///< [in] data object read from DB
		sqlite3 *db,								///< [in] SQLite DB object
		const int64_t sortID						///< [in] unique index of object
	)
	{
		int error = 0;

		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		// set object bindings
		sqlite3_bind_int64(stmt, 1, sortID );
		sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_configID()), -1, SQLITE_STATIC);
		sqlite3_bind_text(stmt, 3, IDToChar(obj->getconst_id()), -1, SQLITE_STATIC);
		sqlite3_bind_int64(stmt, 4, obj->getconst_timestamp() );
		sqlite3_bind_int64(stmt, 5, obj->getconst_x() );

		// write object base data and sub objects
		error = sqlite3_step(stmt);
		return error;
	}


	/**
	* append object internal sort criteria to list
	* @note This function is MANDATORY.
	*/
	virtual void appendObjectGrouping(
		std::vector< Store::SortEntry >& sortList ///< [in/out] list of sort criteria for table rows
	) const
	{
		sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
	}

	/**
	* get name of internal sort criteria column
	* @note This function is MANDATORY.
	*
	* @return column name
	*/
	virtual const std::string objectKey() const
	{
		return std::string("_sortID");
	}

};


/**
 * factory for TestWrapper_Store_SQLite
 */
class TestWrapper_Store_SQLite_Factory : public IStore_ReadWrite_Factory<TestDataClass>
{
public:
	/**
	* constructor
	*	uses DataAllocator_Primitive (new / delete for every object request)
	*/
	TestWrapper_Store_SQLite_Factory(
		DBConnection& db				///< [in] DB connection object
	) :	db(db)
	{}

	/**
	* virtual desctuctor
	*/
	virtual ~TestWrapper_Store_SQLite_Factory() {};

	/**
	* creates a new store
	*/
	virtual shared_ptr< IStore_ReadWrite<TestDataClass> > create(
		const id_t configID	= ID_NULL	///< [in] config ID of requested store (optional)
	)
	{
		return boost::static_pointer_cast<IStore_ReadWrite<TestDataClass>>(make_shared<TestWrapper_Store_SQLite>(configID, this->db));
	}

protected:
	DBConnection& db;
};

}} // namespace scope
#endif // TestHelper_Store_SQLite_code
