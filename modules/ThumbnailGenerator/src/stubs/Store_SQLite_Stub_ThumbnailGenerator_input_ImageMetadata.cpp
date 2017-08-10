// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.cpp
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "../Store_SQLite_ThumbnailGenerator_input_ImageMetadata.h"

#include "Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "ThumbnailGenerator_input_ImageMetadata";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
	("'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */")
	("'id' VARCHAR(32) NOT NULL DEFAULT '' /* ID (string) */")
	("'configID' VARCHAR(32) NOT NULL DEFAULT '' /* job / config ID (string) */")
	("'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */")
;

// --> Do NOT EDIT <--
Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<Class_ThumbnailGenerator_input_ImageMetadata>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::~Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata()
{
}

#ifdef ENABLE_SQLITE_SEARCH
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by id
 */
std::vector<shared_ptr<const Class_ThumbnailGenerator_input_ImageMetadata> > Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::getBy_id(const ConnectedVision::id_t& val)
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
std::vector<shared_ptr<const Class_ThumbnailGenerator_input_ImageMetadata> > Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::getBy_configID(const ConnectedVision::id_t& val)
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
std::vector<shared_ptr<const Class_ThumbnailGenerator_input_ImageMetadata> > Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::getBy_timestamp(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

#endif

// --> Do NOT EDIT <--
int Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::readObject(sqlite3_stmt *stmt, shared_ptr<const Class_ThumbnailGenerator_input_ImageMetadata>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

	int64_t objSortID = sqlite3_column_int64(stmt, 0);
	int64_t sortID = objSortID;
	outObj.reset( new Class_ThumbnailGenerator_input_ImageMetadata() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
		// process row
			// ThumbnailGenerator_input_ImageMetadata_id -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
  				obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
			// ThumbnailGenerator_input_ImageMetadata_configID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
  				obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,2) ) ) );
			// ThumbnailGenerator_input_ImageMetadata_timestamp -> ConnectedVision::timestamp_t
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
int Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::writeObject(sqlite3_stmt *stmt, const shared_ptr<const Class_ThumbnailGenerator_input_ImageMetadata>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;


		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		bind_ThumbnailGenerator_input_ImageMetadata( stmt, obj, sortID );
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
	return error;
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::bind_ThumbnailGenerator_input_ImageMetadata(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_ThumbnailGenerator_input_ImageMetadata>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_id()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, IDToChar(obj->getconst_configID()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 4, obj->getconst_timestamp() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata::objectKey() const
{
	return std::string("_sortID");
}


//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata::Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata::~Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_ThumbnailGenerator_input_ImageMetadata> > Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata::create(const id_t configID = ID_NULL)
{
#ifdef Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<Class_ThumbnailGenerator_input_ImageMetadata> > (make_shared< DataHandling::Store_SQLite_ThumbnailGenerator_input_ImageMetadata >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_ThumbnailGenerator_input_ImageMetadata> >();
#endif
}


} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision