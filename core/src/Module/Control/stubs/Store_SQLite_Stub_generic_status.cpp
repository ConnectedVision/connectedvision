/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_generic_status.cpp
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "../Store_SQLite_generic_status.h"

#include "Store_SQLite_Stub_generic_status.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Stub_generic_status
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "generic_status";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
	("'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */")
	("'id' VARCHAR(32) NOT NULL DEFAULT '' /* config id (string) */")
	("'timestamp' BIGINT /* time of modification (integer) */")
	("'moduleID' VARCHAR(32) NOT NULL DEFAULT '' /* ID of module (string) */")
	("'moduleURI' TEXT NOT NULL DEFAULT '' /* URI of module instance (string) */")
	("'commandQueue._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'commandQueue' TEXT /*  (string) */")
	("'status' TEXT NOT NULL DEFAULT 'n/a' /* current status of config / job (string) */")
	("'message' TEXT /* general message (e.g. description of last error) (string) */")
	("'progress' DOUBLE NOT NULL DEFAULT '0' /* processing progress (0.0 - 1.0) (number) */")
	("'startTime' BIGINT NOT NULL DEFAULT '-1' /* System time when the config was started. (integer) */")
	("'systemTimeProcessing' BIGINT NOT NULL DEFAULT '-1' /* System time when the config was / is processed. This time is updated only during processing the config (i.e. status='running'). (integer) */")
	("'estimatedFinishTime' BIGINT DEFAULT '-1' /* estimated time to finish processing of this configChain (integer) */")
	("'qualityOfService.compuationDuration' BIGINT DEFAULT '-1' /* computation duration based on the elapsed time between updates of the systemTimeProcessing parameter (integer) */")
	("'qualityOfService.compuationDurationAverage' BIGINT DEFAULT '-1' /* average of the computation duration of 10 preceding iterations based on the elapsed time between updates of the systemTimeProcessing parameter computed using the simple moving average method (integer) */")
	("'stableResults._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'stableResults.pinID' TEXT /* id of output pin (string) */")
	("'stableResults.indexStart' BIGINT /*  (integer) */")
	("'stableResults.indexEnd' BIGINT /*  (integer) */")
	("'stableResults.timestampStart' BIGINT /*  (integer) */")
	("'stableResults.timestampEnd' BIGINT /*  (integer) */")
	("'chain._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'chain' BLOB /*  (any) */")
	("'configID' VARCHAR(32) /* virtual config id (string) */")
;

// --> Do NOT EDIT <--
Store_SQLite_Stub_generic_status::Store_SQLite_Stub_generic_status(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<Class_generic_status>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
Store_SQLite_Stub_generic_status::~Store_SQLite_Stub_generic_status()
{
}

#ifdef ENABLE_SQLITE_SEARCH
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by id
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_id(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("id", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by timestamp
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_timestamp(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by moduleID
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_moduleID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("moduleID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by progress
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_progress(const double& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("progress", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by startTime
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_startTime(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("startTime", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by systemTimeProcessing
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_systemTimeProcessing(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("systemTimeProcessing", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by estimatedFinishTime
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_estimatedFinishTime(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("estimatedFinishTime", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by configID
 */
std::vector<shared_ptr<const Class_generic_status> > Store_SQLite_Stub_generic_status::getBy_configID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

#endif

// --> Do NOT EDIT <--
int Store_SQLite_Stub_generic_status::readObject(sqlite3_stmt *stmt, shared_ptr<const Class_generic_status>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

	int64_t objSortID = sqlite3_column_int64(stmt, 0);
	int64_t sortID = objSortID;
	outObj.reset( new Class_generic_status() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
		// process row
			// generic_status_id -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
  				obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
			// generic_status_timestamp -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
  				obj->set_timestamp( sqlite3_column_int64(stmt,2) );
			// generic_status_moduleID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 3) != SQLITE_NULL )
  				obj->set_moduleID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,3) ) ) );
			// generic_status_moduleURI -> std::string
  			if ( sqlite3_column_type(stmt, 4) != SQLITE_NULL )
  				obj->set_moduleURI( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,4)) ) ) );
			// generic_status_commandQueue -> std::vector<boost::shared_ptr<std::string>>
  			if ( sqlite3_column_type(stmt, 5) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a1 = obj->get_commandQueue(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<std::string>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,5) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// commandQueue -> std::string
  				if ( sqlite3_column_type(stmt, 6) != SQLITE_NULL )
  					a1->at(idx1) = boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,6)) ) );
			}
			// generic_status_status -> std::string
  			if ( sqlite3_column_type(stmt, 7) != SQLITE_NULL )
  				obj->set_status( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,7)) ) ) );
			// generic_status_message -> std::string
  			if ( sqlite3_column_type(stmt, 8) != SQLITE_NULL )
  				obj->set_message( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,8)) ) ) );
			// generic_status_progress -> double
  			if ( sqlite3_column_type(stmt, 9) != SQLITE_NULL )
  				obj->set_progress( sqlite3_column_double(stmt,9) );
			// generic_status_startTime -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 10) != SQLITE_NULL )
  				obj->set_startTime( sqlite3_column_int64(stmt,10) );
			// generic_status_systemTimeProcessing -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 11) != SQLITE_NULL )
  				obj->set_systemTimeProcessing( sqlite3_column_int64(stmt,11) );
			// generic_status_estimatedFinishTime -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 12) != SQLITE_NULL )
  				obj->set_estimatedFinishTime( sqlite3_column_int64(stmt,12) );
			// generic_status_qualityOfService -> Class_generic_status_qualityOfService
  			{
  				boost::shared_ptr<Class_generic_status_qualityOfService>&& o1 = obj->get_qualityOfService(); // rvalue reference for const functions
  				if ( !o1 ) o1.reset( new Class_generic_status_qualityOfService );
				// generic_status_qualityOfService_compuationDuration -> ConnectedVision::timestamp_t
  				if ( sqlite3_column_type(stmt, 13) != SQLITE_NULL )
  					o1->set_compuationDuration( sqlite3_column_int64(stmt,13) );
				// generic_status_qualityOfService_compuationDurationAverage -> ConnectedVision::timestamp_t
  				if ( sqlite3_column_type(stmt, 14) != SQLITE_NULL )
  					o1->set_compuationDurationAverage( sqlite3_column_int64(stmt,14) );
  			}
			// generic_status_stableResults -> std::vector<boost::shared_ptr<Class_generic_status_stableResults>>
  			if ( sqlite3_column_type(stmt, 15) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>>&& a1 = obj->get_stableResults(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<Class_generic_status_stableResults>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,15) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// generic_status_stableResults -> Class_generic_status_stableResults
  				{
  					boost::shared_ptr<Class_generic_status_stableResults>& o2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !o2 ) o2.reset( new Class_generic_status_stableResults );
					// generic_status_stableResults_pinID -> std::string
  					if ( sqlite3_column_type(stmt, 16) != SQLITE_NULL )
  						o2->set_pinID( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,16)) ) ) );
					// generic_status_stableResults_indexStart -> int64_t
  					if ( sqlite3_column_type(stmt, 17) != SQLITE_NULL )
  						o2->set_indexStart( sqlite3_column_int64(stmt,17) );
					// generic_status_stableResults_indexEnd -> int64_t
  					if ( sqlite3_column_type(stmt, 18) != SQLITE_NULL )
  						o2->set_indexEnd( sqlite3_column_int64(stmt,18) );
					// generic_status_stableResults_timestampStart -> ConnectedVision::timestamp_t
  					if ( sqlite3_column_type(stmt, 19) != SQLITE_NULL )
  						o2->set_timestampStart( sqlite3_column_int64(stmt,19) );
					// generic_status_stableResults_timestampEnd -> ConnectedVision::timestamp_t
  					if ( sqlite3_column_type(stmt, 20) != SQLITE_NULL )
  						o2->set_timestampEnd( sqlite3_column_int64(stmt,20) );
  				}
			}
			// generic_status_chain -> std::vector<boost::shared_ptr<std::string>>
  			if ( sqlite3_column_type(stmt, 21) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a1 = obj->get_chain(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<std::string>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,21) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// chain -> std::string
  				if ( sqlite3_column_type(stmt, 22) != SQLITE_NULL )
  					a1->at(idx1) = boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_blob(stmt,22)), sqlite3_column_bytes(stmt,22) ) );
			}
			// generic_status_configID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 23) != SQLITE_NULL )
  				obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,23) ) ) );

		error = sqlite3_step(stmt);
		if ( error == SQLITE_ROW )
			sortID = sqlite3_column_int64(stmt, 0);
	}

	outObj = this->make_const(obj);
	return error;
}

// --> Do NOT EDIT <--
int Store_SQLite_Stub_generic_status::writeObject(sqlite3_stmt *stmt, const shared_ptr<const Class_generic_status>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;


		size_t i1_max = 1;
		if ( i1_max < obj->getconst_commandQueue()->size() )
			i1_max = obj->getconst_commandQueue()->size();
		if ( i1_max < obj->getconst_stableResults()->size() )
			i1_max = obj->getconst_stableResults()->size();
		if ( i1_max < obj->getconst_chain()->size() )
			i1_max = obj->getconst_chain()->size();
	for ( size_t i1 = 0; i1 < i1_max; i1++ )
	{
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		bind_generic_status( stmt, obj, sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_commandQueue()->size() )
		bind_commandQueue( stmt, obj->getconst_commandQueue()->at(i1), sortID, i1 );

		bind_qualityOfService( stmt, obj->getconst_qualityOfService(), sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_stableResults()->size() )
		bind_stableResults( stmt, obj->getconst_stableResults()->at(i1), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_chain()->size() )
		bind_chain( stmt, obj->getconst_chain()->at(i1), sortID, i1 );
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
	}
	return error;
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_status::bind_generic_status(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_status>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_id()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, obj->getconst_timestamp() );
	sqlite3_bind_text(stmt, 4, IDToChar(obj->getconst_moduleID()), -1, SQLITE_TRANSIENT);
  	sqlite3_bind_text(stmt, 5, obj->getconst_moduleURI()->c_str(), -1, SQLITE_TRANSIENT );
  	// array: commandQueue handled separately
  	sqlite3_bind_text(stmt, 8, obj->getconst_status()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_text(stmt, 9, obj->getconst_message()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_double(stmt, 10, obj->getconst_progress() );
	sqlite3_bind_int64(stmt, 11, obj->getconst_startTime() );
	sqlite3_bind_int64(stmt, 12, obj->getconst_systemTimeProcessing() );
	sqlite3_bind_int64(stmt, 13, obj->getconst_estimatedFinishTime() );
	// object: qualityOfService handled separately
  	// array: stableResults handled separately
  	// array: chain handled separately
	sqlite3_bind_text(stmt, 24, IDToChar(obj->getconst_configID()), -1, SQLITE_TRANSIENT);
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_status::bind_commandQueue(sqlite3_stmt *stmt, const boost::shared_ptr<const std::string>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 6, idx1 );
  	sqlite3_bind_text(stmt, 7, obj->c_str(), -1, SQLITE_TRANSIENT );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_status::bind_qualityOfService(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_status_qualityOfService>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 14, obj->getconst_compuationDuration() );
	sqlite3_bind_int64(stmt, 15, obj->getconst_compuationDurationAverage() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_status::bind_stableResults(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_status_stableResults>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 16, idx1 );
  	sqlite3_bind_text(stmt, 17, obj->getconst_pinID()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_int64(stmt, 18, obj->getconst_indexStart() );
  	sqlite3_bind_int64(stmt, 19, obj->getconst_indexEnd() );
	sqlite3_bind_int64(stmt, 20, obj->getconst_timestampStart() );
	sqlite3_bind_int64(stmt, 21, obj->getconst_timestampEnd() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_status::bind_chain(sqlite3_stmt *stmt, const boost::shared_ptr<const std::string>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 22, idx1 );
  	sqlite3_bind_blob(stmt, 23, obj->c_str(), (int)obj->size(), SQLITE_TRANSIENT); // TODO update & use sqlite3_bind_blob64()
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_status::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string Store_SQLite_Stub_generic_status::objectKey() const
{
	return std::string("_sortID");
}


//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Factory_Stub_generic_status
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_generic_status::Store_SQLite_Factory_Stub_generic_status(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_generic_status::~Store_SQLite_Factory_Stub_generic_status()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > Store_SQLite_Factory_Stub_generic_status::create(const id_t configID = ID_NULL)
{
#ifdef Store_SQLite_Factory_generic_status_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > (make_shared< DataHandling::Store_SQLite_generic_status >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> >();
#endif
}


} // namespace DataHandling
} // namespace ConnectedVision