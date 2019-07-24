// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger.cpp
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "../Store_SQLite_DummyBoundingBoxes_input_Trigger.h"

#include "Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "DummyBoundingBoxes_input_Trigger";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
	("'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */")
	("'id' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */")
	("'configID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */")
	("'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */")
;

// --> Do NOT EDIT <--
Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<Class_DummyBoundingBoxes_input_Trigger>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::~Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger()
{
}

#ifdef ENABLE_SQLITE_SEARCH
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by id
 */
std::vector<shared_ptr<const Class_DummyBoundingBoxes_input_Trigger> > Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::getBy_id(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("id", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by configID
 */
std::vector<shared_ptr<const Class_DummyBoundingBoxes_input_Trigger> > Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::getBy_configID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by timestamp
 */
std::vector<shared_ptr<const Class_DummyBoundingBoxes_input_Trigger> > Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::getBy_timestamp(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

#endif

// --> Do NOT EDIT <--
int Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::readObject(sqlite3_stmt *stmt, shared_ptr<const Class_DummyBoundingBoxes_input_Trigger>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

	int64_t objSortID = sqlite3_column_int64(stmt, 0);
	int64_t sortID = objSortID;
	outObj.reset( new Class_DummyBoundingBoxes_input_Trigger() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
		// process row
			// DummyBoundingBoxes_input_Trigger_id -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
  				obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
			// DummyBoundingBoxes_input_Trigger_configID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
  				obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,2) ) ) );
			// DummyBoundingBoxes_input_Trigger_timestamp -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 3) != SQLITE_NULL )
  				obj->set_timestamp( sqlite3_column_int64(stmt,3) );

		error = sqlite3_step(stmt);
		if ( error == SQLITE_ROW )
			sortID = sqlite3_column_int64(stmt, 0);
	}

	outObj = this->make_const(obj);
	return error;
}

// --> Do NOT EDIT <--
int Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::writeObject(sqlite3_stmt *stmt, const shared_ptr<const Class_DummyBoundingBoxes_input_Trigger>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;


		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		bind_DummyBoundingBoxes_input_Trigger( stmt, obj, sortID );
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
	return error;
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::bind_DummyBoundingBoxes_input_Trigger(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_DummyBoundingBoxes_input_Trigger>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_id()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, IDToChar(obj->getconst_configID()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 4, obj->getconst_timestamp() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string Store_SQLite_Stub_DummyBoundingBoxes_input_Trigger::objectKey() const
{
	return std::string("_sortID");
}


//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger::Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger::~Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_DummyBoundingBoxes_input_Trigger> > Store_SQLite_Factory_Stub_DummyBoundingBoxes_input_Trigger::create(const id_t configID = ID_NULL)
{
#ifdef Store_SQLite_Factory_DummyBoundingBoxes_input_Trigger_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<Class_DummyBoundingBoxes_input_Trigger> > (make_shared< DataHandling::Store_SQLite_DummyBoundingBoxes_input_Trigger >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_DummyBoundingBoxes_input_Trigger> >();
#endif
}


} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision