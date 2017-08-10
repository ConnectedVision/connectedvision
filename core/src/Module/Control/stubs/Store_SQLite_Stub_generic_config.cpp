/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_generic_config.cpp
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "../Store_SQLite_generic_config.h"

#include "Store_SQLite_Stub_generic_config.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Stub_generic_config
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "generic_config";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
	("'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */")
	("'id' VARCHAR(32) NOT NULL DEFAULT '' /* config ID (string) */")
	("'timestamp' BIGINT /* time of modification (integer) */")
	("'name' TEXT NOT NULL DEFAULT '' /* config name (string) */")
	("'description' TEXT NOT NULL DEFAULT '' /* config description (string) */")
	("'aliasID._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'aliasID.id' TEXT /* an aliasID to be assigned to this config (string) */")
	("'aliasID.timestamp' BIGINT /* creation timestamp of aliasID for this config (integer) */")
	("'version' BIGINT NOT NULL DEFAULT '0' /* config version (integer) */")
	("'moduleID' VARCHAR(32) NOT NULL DEFAULT '' /*  (string) */")
	("'moduleURI' TEXT NOT NULL DEFAULT '' /* URI of module instance (string) */")
	("'configFeatures.allowDynamicParameters' TINYINT /* the config does support dynamic parameters (boolean) */")
	("'callback.moduleID' VARCHAR(32) /*  (string) */")
	("'callback.moduleURI' TEXT /* URI of module instance (string) */")
	("'params' BLOB /*  (any) */")
	("'initialParams' BLOB /*  (any) */")
	("'chain._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'chain.connections._idx2' BIGINT /* array index dimension: 2 (array) */")
	("'chain.connections.inputPinID' TEXT /* id of input pin (string) */")
	("'chain.connections.outputPinID' TEXT /* id of output pin (string) */")
	("'chain.config' BLOB /* config of sub module (any) */")
	("'configID' VARCHAR(32) /* virtual config id (string) */")
;

// --> Do NOT EDIT <--
Store_SQLite_Stub_generic_config::Store_SQLite_Stub_generic_config(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<Class_generic_config>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
Store_SQLite_Stub_generic_config::~Store_SQLite_Stub_generic_config()
{
}

#ifdef ENABLE_SQLITE_SEARCH
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by id
 */
std::vector<shared_ptr<const Class_generic_config> > Store_SQLite_Stub_generic_config::getBy_id(const ConnectedVision::id_t& val)
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
std::vector<shared_ptr<const Class_generic_config> > Store_SQLite_Stub_generic_config::getBy_timestamp(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by version
 */
std::vector<shared_ptr<const Class_generic_config> > Store_SQLite_Stub_generic_config::getBy_version(const int64_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("version", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by moduleID
 */
std::vector<shared_ptr<const Class_generic_config> > Store_SQLite_Stub_generic_config::getBy_moduleID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("moduleID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by configID
 */
std::vector<shared_ptr<const Class_generic_config> > Store_SQLite_Stub_generic_config::getBy_configID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

#endif

// --> Do NOT EDIT <--
int Store_SQLite_Stub_generic_config::readObject(sqlite3_stmt *stmt, shared_ptr<const Class_generic_config>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

	int64_t objSortID = sqlite3_column_int64(stmt, 0);
	int64_t sortID = objSortID;
	outObj.reset( new Class_generic_config() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
		// process row
			// generic_config_id -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
  				obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
			// generic_config_timestamp -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
  				obj->set_timestamp( sqlite3_column_int64(stmt,2) );
			// generic_config_name -> std::string
  			if ( sqlite3_column_type(stmt, 3) != SQLITE_NULL )
  				obj->set_name( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,3)) ) ) );
			// generic_config_description -> std::string
  			if ( sqlite3_column_type(stmt, 4) != SQLITE_NULL )
  				obj->set_description( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,4)) ) ) );
			// generic_config_aliasID -> std::vector<boost::shared_ptr<Class_generic_config_aliasID>>
  			if ( sqlite3_column_type(stmt, 5) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>>&& a1 = obj->get_aliasID(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<Class_generic_config_aliasID>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,5) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// generic_config_aliasID -> Class_generic_config_aliasID
  				{
  					boost::shared_ptr<Class_generic_config_aliasID>& o2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !o2 ) o2.reset( new Class_generic_config_aliasID );
					// generic_config_aliasID_id -> std::string
  					if ( sqlite3_column_type(stmt, 6) != SQLITE_NULL )
  						o2->set_id( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,6)) ) ) );
					// generic_config_aliasID_timestamp -> ConnectedVision::timestamp_t
  					if ( sqlite3_column_type(stmt, 7) != SQLITE_NULL )
  						o2->set_timestamp( sqlite3_column_int64(stmt,7) );
  				}
			}
			// generic_config_version -> int64_t
  			if ( sqlite3_column_type(stmt, 8) != SQLITE_NULL )
  				obj->set_version( sqlite3_column_int64(stmt,8) );
			// generic_config_moduleID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 9) != SQLITE_NULL )
  				obj->set_moduleID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,9) ) ) );
			// generic_config_moduleURI -> std::string
  			if ( sqlite3_column_type(stmt, 10) != SQLITE_NULL )
  				obj->set_moduleURI( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,10)) ) ) );
			// generic_config_configFeatures -> Class_generic_config_configFeatures
  			{
  				boost::shared_ptr<Class_generic_config_configFeatures>&& o1 = obj->get_configFeatures(); // rvalue reference for const functions
  				if ( !o1 ) o1.reset( new Class_generic_config_configFeatures );
				// generic_config_configFeatures_allowDynamicParameters -> bool
  				if ( sqlite3_column_type(stmt, 11) != SQLITE_NULL )
  					o1->set_allowDynamicParameters( ( sqlite3_column_int(stmt,11) ? true : false ) );
  			}
			// generic_config_callback -> Class_generic_config_callback
  			{
  				boost::shared_ptr<Class_generic_config_callback>&& o1 = obj->get_callback(); // rvalue reference for const functions
  				if ( !o1 ) o1.reset( new Class_generic_config_callback );
				// generic_config_callback_moduleID -> ConnectedVision::id_t
  				if ( sqlite3_column_type(stmt, 12) != SQLITE_NULL )
  					o1->set_moduleID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,12) ) ) );
				// generic_config_callback_moduleURI -> std::string
  				if ( sqlite3_column_type(stmt, 13) != SQLITE_NULL )
  					o1->set_moduleURI( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,13)) ) ) );
  			}
			// generic_config_params -> std::string
  			if ( sqlite3_column_type(stmt, 14) != SQLITE_NULL )
  				obj->set_params( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_blob(stmt,14)), sqlite3_column_bytes(stmt,14) ) ) );
			// generic_config_initialParams -> std::string
  			if ( sqlite3_column_type(stmt, 15) != SQLITE_NULL )
  				obj->set_initialParams( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_blob(stmt,15)), sqlite3_column_bytes(stmt,15) ) ) );
			// generic_config_chain -> std::vector<boost::shared_ptr<Class_generic_config_chain>>
  			if ( sqlite3_column_type(stmt, 16) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>>&& a1 = obj->get_chain(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<Class_generic_config_chain>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,16) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// generic_config_chain -> Class_generic_config_chain
  				{
  					boost::shared_ptr<Class_generic_config_chain>& o2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !o2 ) o2.reset( new Class_generic_config_chain );
					// generic_config_chain_connections -> std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>
  					if ( sqlite3_column_type(stmt, 17) != SQLITE_NULL )
  					{
  						boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>>&& a3 = o2->get_connections(); // rvalue reference for const functions
  						if ( !a3 ) a3.reset( new std::vector<boost::shared_ptr<Class_generic_config_chain_connections>> );
  						size_t idx3 = static_cast<size_t>( sqlite3_column_int64(stmt,17) );
  						if ( idx3 >= a3->size() ) a3->resize( idx3 +1 );
						// generic_config_chain_connections -> Class_generic_config_chain_connections
  						{
  							boost::shared_ptr<Class_generic_config_chain_connections>& o4 = a3->at(idx3); // lvalue reference for non-const functions like vector::at()
  							if ( !o4 ) o4.reset( new Class_generic_config_chain_connections );
							// generic_config_chain_connections_inputPinID -> std::string
  							if ( sqlite3_column_type(stmt, 18) != SQLITE_NULL )
  								o4->set_inputPinID( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,18)) ) ) );
							// generic_config_chain_connections_outputPinID -> std::string
  							if ( sqlite3_column_type(stmt, 19) != SQLITE_NULL )
  								o4->set_outputPinID( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,19)) ) ) );
  						}
					}
					// generic_config_chain_config -> std::string
  					if ( sqlite3_column_type(stmt, 20) != SQLITE_NULL )
  						o2->set_config( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_blob(stmt,20)), sqlite3_column_bytes(stmt,20) ) ) );
  				}
			}
			// generic_config_configID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 21) != SQLITE_NULL )
  				obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,21) ) ) );

		error = sqlite3_step(stmt);
		if ( error == SQLITE_ROW )
			sortID = sqlite3_column_int64(stmt, 0);
	}

	outObj = this->make_const(obj);
	return error;
}

// --> Do NOT EDIT <--
int Store_SQLite_Stub_generic_config::writeObject(sqlite3_stmt *stmt, const shared_ptr<const Class_generic_config>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;


		size_t i1_max = 1;
		if ( i1_max < obj->getconst_aliasID()->size() )
			i1_max = obj->getconst_aliasID()->size();
		if ( i1_max < obj->getconst_chain()->size() )
			i1_max = obj->getconst_chain()->size();
	for ( size_t i1 = 0; i1 < i1_max; i1++ )
	{
		size_t i2_max = 1;
		if ( i1 < obj->getconst_chain()->size() )
		if ( i2_max < obj->getconst_chain()->at(i1)->getconst_connections()->size() )
			i2_max = obj->getconst_chain()->at(i1)->getconst_connections()->size();
	for ( size_t i2 = 0; i2 < i2_max; i2++ )
	{
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		bind_generic_config( stmt, obj, sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_aliasID()->size() )
		bind_aliasID( stmt, obj->getconst_aliasID()->at(i1), sortID, i1 );

		bind_configFeatures( stmt, obj->getconst_configFeatures(), sortID );

		bind_callback( stmt, obj->getconst_callback(), sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_chain()->size() )
		bind_chain( stmt, obj->getconst_chain()->at(i1), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_chain()->size() )		if ( i2 < obj->getconst_chain()->at(i1)->getconst_connections()->size() )
		bind_chain_connections( stmt, obj->getconst_chain()->at(i1)->getconst_connections()->at(i2), sortID, i1, i2 );
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
	}
	}
	return error;
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::bind_generic_config(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_config>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_id()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 3, obj->getconst_timestamp() );
  	sqlite3_bind_text(stmt, 4, obj->getconst_name()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_text(stmt, 5, obj->getconst_description()->c_str(), -1, SQLITE_TRANSIENT );
  	// array: aliasID handled separately
  	sqlite3_bind_int64(stmt, 9, obj->getconst_version() );
	sqlite3_bind_text(stmt, 10, IDToChar(obj->getconst_moduleID()), -1, SQLITE_TRANSIENT);
  	sqlite3_bind_text(stmt, 11, obj->getconst_moduleURI()->c_str(), -1, SQLITE_TRANSIENT );
	// object: configFeatures handled separately
	// object: callback handled separately
  	sqlite3_bind_blob(stmt, 15, obj->getconst_params()->c_str(), (int)obj->getconst_params()->size(), SQLITE_TRANSIENT); // TODO update & use sqlite3_bind_blob64()
  	sqlite3_bind_blob(stmt, 16, obj->getconst_initialParams()->c_str(), (int)obj->getconst_initialParams()->size(), SQLITE_TRANSIENT); // TODO update & use sqlite3_bind_blob64()
  	// array: chain handled separately
	sqlite3_bind_text(stmt, 22, IDToChar(obj->getconst_configID()), -1, SQLITE_TRANSIENT);
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::bind_aliasID(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_config_aliasID>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 6, idx1 );
  	sqlite3_bind_text(stmt, 7, obj->getconst_id()->c_str(), -1, SQLITE_TRANSIENT );
	sqlite3_bind_int64(stmt, 8, obj->getconst_timestamp() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::bind_configFeatures(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_config_configFeatures>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 12, obj->getconst_allowDynamicParameters() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::bind_callback(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_config_callback>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 13, IDToChar(obj->getconst_moduleID()), -1, SQLITE_TRANSIENT);
  	sqlite3_bind_text(stmt, 14, obj->getconst_moduleURI()->c_str(), -1, SQLITE_TRANSIENT );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::bind_chain(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_config_chain>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 17, idx1 );
  	// array: connections handled separately
  	sqlite3_bind_blob(stmt, 21, obj->getconst_config()->c_str(), (int)obj->getconst_config()->size(), SQLITE_TRANSIENT); // TODO update & use sqlite3_bind_blob64()
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::bind_chain_connections(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_generic_config_chain_connections>& obj, const int64_t sortID, const int64_t idx1, const int64_t idx2) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 17, idx1 );
	sqlite3_bind_int64(stmt, 18, idx2 );
  	sqlite3_bind_text(stmt, 19, obj->getconst_inputPinID()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_text(stmt, 20, obj->getconst_outputPinID()->c_str(), -1, SQLITE_TRANSIENT );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_generic_config::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string Store_SQLite_Stub_generic_config::objectKey() const
{
	return std::string("_sortID");
}


//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Factory_Stub_generic_config
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_generic_config::Store_SQLite_Factory_Stub_generic_config(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_generic_config::~Store_SQLite_Factory_Stub_generic_config()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > Store_SQLite_Factory_Stub_generic_config::create(const id_t configID = ID_NULL)
{
#ifdef Store_SQLite_Factory_generic_config_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > (make_shared< DataHandling::Store_SQLite_generic_config >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> >();
#endif
}


} // namespace DataHandling
} // namespace ConnectedVision