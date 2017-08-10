/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_SQLite_BaseClass_class
#define Store_SQLite_BaseClass_class

#include <exception>
#include <boost/regex.hpp>

#include <helper.h>

#include "Store_SQLite_BaseClass.h"
#include "DataAllocator_Primitive.h"

namespace ConnectedVision 
{
namespace DataHandling
{

template <IConnectedVisionDataClass TDataClass>
Store_SQLite_BaseClass<TDataClass>::Store_SQLite_BaseClass(const id_t& configID, DBConnection& dbConn, const std::string& tableName, const std::vector<std::string> columnDesc) :
	configID( configID ), 
	dbConn( dbConn ), 
	tableName( tableName ),
	dataAllocator( ConnectedVision::make_shared< DataAllocator_Primitive<TDataClass> >() )
{
	// mutex lock
	scoped_db_lock lock(dbConn);

	std::string sql;
	int error;
	const char *tail;
	sqlite3_stmt *stmt = NULL;
	// verify that we have a valid DB connection
	sqlite3 *db = lock.db;
	if ( !db )
		throw ConnectedVision::runtime_error( "no DB connection" );

	// test table
	if ( tableName.empty() )
		throw ConnectedVision::runtime_error( "no table defined" );	
	if ( columnDesc.size() < 1 )
		throw ConnectedVision::runtime_error( "no colums defined" );	

	// prepare statement
	sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" + tableName + "'";
	error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);		
	if (error == SQLITE_OK)
	{
		// read first line
		error = sqlite3_step(stmt);
		// clean up
		sqlite3_finalize(stmt); stmt = NULL;

		if ( error != SQLITE_ROW )
		{
			// create table
			sql = "CREATE TABLE '" + tableName + "'( "+ std::string(columnDesc[0]) + " );";
			error = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
			if ( error )
			{
				throw ConnectedVision::runtime_error( sqlite3_errmsg( db ) );
			}
		}
	}
	else
	{
		sqlite3_finalize(stmt); stmt = NULL;
		throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
	}


	// build columns and bind index list
	this->columnNames = "";
	int i = 0;
	for( auto it = columnDesc.begin(); it != columnDesc.end(); ++it, ++i )
	{
		if ( i > 0 ) 
		{
			this->columnBindIdx += ", ";
			this->columnNames += ", ";
		}
		this->columnBindIdx += "?" + intToStr(i+1);

		auto &column = *it;

		// extract column name
		// match column name, SQL statement
		boost::smatch matches;    // same as std::match_results<string::const_iterator> sm;
		if ( boost::regex_match(column, matches, boost::regex("'([\\w\\.]+)'\\s(.*)")) )
		{
			std::string name = matches[1];
			this->columnNames += '"' + name + '"';

			// try to create column
			sql = "ALTER TABLE '" + tableName + "' ADD COLUMN " + column;
			sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL); // ignore error if already exists
		}
		else
		{
			throw ConnectedVision::runtime_error( "Store_SQLite_BaseClass() cannot extract column name: " + column );
		}
	}


}

template <IConnectedVisionDataClass TDataClass>
std::vector<id_t> Store_SQLite_BaseClass<TDataClass>::getIDList()
{
	// mutex lock
	scoped_db_lock lock(dbConn);

	// call function with lock guard
	return getIDList( lock.db );
}

template <IConnectedVisionDataClass TDataClass>
std::vector<id_t> Store_SQLite_BaseClass<TDataClass>::getIDList(sqlite3 *db) const
{
	std::vector<id_t> list;

	// verify that we have a valid DB connection
	if ( !db )
	{
		throw ConnectedVision::runtime_error( "no DB connection" );
	}

	sqlite3_stmt *stmt = NULL;
	std::string sql = "SELECT DISTINCT id FROM " + this->tableName;

	const char *tail;
	int error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);		
	if (error == SQLITE_OK)
	{
		while (sqlite3_step(stmt) == SQLITE_ROW)
			list.push_back( std::string((const char*)sqlite3_column_text(stmt, 0)) );
		sqlite3_finalize(stmt);
	}
	else
	{
		throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
	}

	return list;
}

template <IConnectedVisionDataClass TDataClass>
DataRange Store_SQLite_BaseClass<TDataClass>::getDataRange() const
{
	DataRange range;
	range.indexEnd = -1;

	// mutex lock
	scoped_db_lock lock(dbConn);
	auto &db = lock.db;

	sqlite3_stmt *stmt = NULL;

	// verify that we have a valid DB connection
	if ( !db )
	{
		throw ConnectedVision::runtime_error( "no DB connection" );
	}

	// build SQL statement
	std::string sql =	"SELECT COUNT(DISTINCT(id)) AS count, MIN(timestamp) AS startTimestamp, MAX(timestamp) AS lastTimestamp FROM "
						+ this->tableName + " WHERE configID=?1";


	// prepare statement
	const char *tail;
	int error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);		
	if (error == SQLITE_OK)
	{
		// bind filter
		sqlite3_bind_text(stmt, 1, this->configID.c_str(), -1, SQLITE_TRANSIENT);

		// read first line
		// execute SQL
		error = sqlite3_step(stmt);

		// read all objects
		if ( error == SQLITE_ROW )
		{
			range.indexStart = 0;
			range.indexEnd = sqlite3_column_int64(stmt, 0) -1;	// count of unique IDs - 1
			range.timestampStart = sqlite3_column_int64(stmt, 1);
			range.timestampEnd = sqlite3_column_int64(stmt, 2);
		}

		// is the DB empty?
		if ( range.indexEnd < 0 )
		{
			range.indexStart = -1;
			range.timestampStart = -1;
			range.indexEnd = -1;
			range.timestampEnd = -1;
		}

		// clean up
		sqlite3_finalize(stmt); stmt = NULL;

		if ( error != SQLITE_ROW )
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
		}
	}
	else
	{
		sqlite3_finalize(stmt); stmt = NULL;
		throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
	}

	return(range);
}


template <IConnectedVisionDataClass TDataClass>
const id_t& Store_SQLite_BaseClass<TDataClass>::getConfigID() const
{
	return this->configID;
}

template <IConnectedVisionDataClass TDataClass>
shared_ptr<const TDataClass> Store_SQLite_BaseClass<TDataClass>::getByID(const id_t& id)
{
	std::vector<Store::FilterEntry> filterList;
	filterList.push_back( Store::FilterEntry("id", Store::Op::EQUAL, IDToStr(id) ) );
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	std::vector< shared_ptr<const TDataClass> > list( getByFilter(filterList) );
	
	if ( list.size() == 1 )
		return list.at(0);
	else
		return shared_ptr<const TDataClass>();
}
	
template <IConnectedVisionDataClass TDataClass>
shared_ptr<const TDataClass> Store_SQLite_BaseClass<TDataClass>::getByIndex(const int64_t index)
{
	std::vector< shared_ptr<const TDataClass> > objs = this->getByIndexRange(index, index);
	
	if ( objs.size() == 1 )
		return objs[0];
	else
		return shared_ptr<const TDataClass>();
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getByIndexRange(const int64_t start, const int64_t end)
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	std::vector< Store::SortEntry > sortList;
	return getByFilter(filterList, sortList, start, (end - start +1) );
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getByTimestamp(const timestamp_t timestamp)
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, timestamp) );

	return this->getByFilter(filterList);
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getBeforeTimestamp(const timestamp_t timestamp)
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::SMALLER, timestamp) );

	std::vector< Store::SortEntry > sortList;
	sortList.push_back( Store::SortEntry("timestamp", Store::Order::DESC) );

	std::vector< shared_ptr<const TDataClass> >objs = this->getByFilter(filterList, sortList, 0, 1);
	if ( objs.size() )
	{
		timestamp_t objTime = objs[0]->getconst_timestamp();

		filterList.clear();
		filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
		Store::FilterEntry filterTimestamp("timestamp", Store::Op::EQUAL, objTime);
		filterList.push_back( filterTimestamp );
		objs = getByFilter(filterList, sortList);
	}

	return objs;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getAfterTimestamp(const timestamp_t timestamp)
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::GREATER, timestamp) );

	std::vector< Store::SortEntry > sortList;
	sortList.push_back( Store::SortEntry("timestamp", Store::Order::ASC) );

	std::vector< shared_ptr<const TDataClass> >objs = this->getByFilter(filterList, sortList, 0, 1);
	if ( objs.size() )
	{
		timestamp_t objTime = objs[0]->getconst_timestamp();

		filterList.clear();
		filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
		Store::FilterEntry filterTimestamp("timestamp", Store::Op::EQUAL, objTime);
		filterList.push_back( filterTimestamp );
		objs = getByFilter(filterList, sortList);
	}

	return objs;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getAllInTimespan(const timestamp_t start, const timestamp_t end)
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::GREATEREQUAL, start) );
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::SMALLEREQUAL, end) );

	return getByFilter(filterList);
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::deleteAll()
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );

	this->deleteByFilter(filterList);
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::deleteByID(const id_t& id)
{
	std::vector< Store::FilterEntry > filterList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, this->configID) );
	filterList.push_back( Store::FilterEntry("id", Store::Op::EQUAL, IDToStr(id)) );

	this->deleteByFilter(filterList);
}

template <IConnectedVisionDataClass TDataClass>
id_t Store_SQLite_BaseClass<TDataClass>::save_const(const shared_ptr<const TDataClass>& data)
{
	std::vector<shared_ptr<const TDataClass>> dataVector;
	dataVector.push_back( data );

	std::vector<id_t> ids = this->save_constVector(dataVector);

	if ( ids.size() == 1 )
		return ids[0];
	else
		throw ConnectedVision::runtime_error("cannot save object");
}

template <IConnectedVisionDataClass TDataClass>
std::vector<id_t> Store_SQLite_BaseClass<TDataClass>::save_constVector(const std::vector<shared_ptr<const TDataClass>>& data)
{
	// mutex lock
	scoped_db_lock lock(dbConn);

	// call function with lock guard
	return save_constVector(data, lock.db);
}

template <IConnectedVisionDataClass TDataClass>
std::vector<id_t> Store_SQLite_BaseClass<TDataClass>::save_constVector(const std::vector<shared_ptr<const TDataClass>>& objs, sqlite3 *db)
{
	std::vector<id_t> ids;
	id_t id;
	int error;
	sqlite3_stmt *stmt = NULL;
	// verify that we have a valid DB connection
	if ( !db )
	{
		throw ConnectedVision::runtime_error( "no DB connection" );
	}

	// check config IDs
	for ( auto it = objs.begin(); it != objs.end(); ++it )
	{
		auto const &obj = *it;
		if ( !obj )
			throw ConnectedVision::runtime_error("try to save NULL object");

		if ( this->configID != obj->getconst_configID() )
		{
			throw ConnectedVision::runtime_error( "configID not set correctly for object ID: " + IDToStr(obj->getconst_id()) + 
										" was set to: " + IDToStr(obj->getconst_configID()) +
										" should be: " + IDToStr(this->configID) );
		}
		if ( obj->getconst_id() == ID_NULL )
		{
			throw ConnectedVision::runtime_error( "id was not set");
		}
	}


	// open DB transaction
	error = sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
	if ( error )
	{
		throw ConnectedVision::runtime_error( sqlite3_errmsg( db ) );
	}
	
	try 
	{
		const char *tail;
		std::string sql;

		// get sort ID
		sql = "SELECT MAX(" + this->objectKey() + ") FROM " + this->tableName;
		error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);
		if (error != SQLITE_OK)
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg( db ) );
		}
		int64_t objSortKeyMax = 0;
		int64_t objSortKey;
		if ( sqlite3_step(stmt) == SQLITE_ROW )
			objSortKeyMax = sqlite3_column_int64(stmt, 0);
		sqlite3_finalize(stmt);

		// build id list placeholder
		std::string placeholderStr("?"); placeholderStr.reserve( objs.size()*2 );
		for( unsigned int i = 1; i < objs.size(); i++ ) 
			placeholderStr += ",?";

		// search for existing objects
		sql = "SELECT DISTINCT id, " + this->objectKey() + " FROM " + this->tableName + " WHERE configID = ? AND id IN (" + placeholderStr + ")";
		error = sqlite3_prepare_v2( db , sql.c_str(), -1, &stmt, &tail);
		if (error != SQLITE_OK)
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg( db ) );
		}
		sqlite3_bind_text(stmt, 1, this->configID.c_str(), -1, SQLITE_TRANSIENT);
		for( unsigned int i = 0; i < objs.size(); i++ )
		{
			auto const &obj = objs[i];
			sqlite3_bind_text(stmt, i+2, obj->getconst_id().c_str(), -1, SQLITE_TRANSIENT);
		}
		std::map<id_t, int64_t> objStoreKeyMap;
		while ( sqlite3_step(stmt) == SQLITE_ROW )
		{
			id_t id( (const char*)(sqlite3_column_text(stmt, 0)) );
			int64_t objSortKey = sqlite3_column_int64(stmt, 1);
			objStoreKeyMap.insert( std::make_pair(id, objSortKey) );
		}
		sqlite3_finalize(stmt);


		// delete old elements
		sql = "DELETE FROM " + this->tableName + " WHERE configID = ? AND id IN (" + placeholderStr + ")";
		error = sqlite3_prepare_v2( db , sql.c_str(), -1, &stmt, &tail);
		if (error != SQLITE_OK)
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg( db ) );
		}
		sqlite3_bind_text(stmt, 1, this->configID.c_str(), -1, SQLITE_TRANSIENT);
		for( unsigned int i = 0; i < objs.size(); i++ )
		{
			auto const &obj = objs[i];
			sqlite3_bind_text(stmt, i+2, obj->getconst_id().c_str(), -1, SQLITE_TRANSIENT);
		}
		error = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
		if (error != SQLITE_DONE)
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg( db ) );
		}

		// start writing to DB
		sql = "INSERT INTO " + this->tableName + " (" + this->columnNames + ") VALUES (" + this->columnBindIdx + ");";
		error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);
		if (error != SQLITE_OK)
		{
			const char *err_msg = sqlite3_errmsg(db);
			sqlite3_finalize(stmt);
			throw ConnectedVision::runtime_error( err_msg );
		}
		for( unsigned int i = 0; i < objs.size(); i++ )
		{
			auto const &obj = objs[i];

			// is object (id) already in DB?
			id = obj->getconst_id();

			auto it = objStoreKeyMap.find(id);
			if ( it == objStoreKeyMap.end() )
			{
				// insert new object
				objSortKeyMax++;
				objSortKey = objSortKeyMax;
			}
			else
			{
				// overwrite existing object
				// reuse object keys / sort index
				objSortKey = it->second;
			}

			// write actual object
			error = this->writeObject(stmt, obj, db, objSortKey);
			if (error != SQLITE_DONE)
			{
				const char *err_msg = sqlite3_errmsg(db);
				throw ConnectedVision::runtime_error( err_msg );
			}
			ids.push_back( id );
		}
		sqlite3_finalize(stmt);
		stmt = NULL;

		// commit DB transaction
		error = sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
		if ( error )
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
		}
	}
	catch (ConnectedVision::runtime_error& e)
	{
		if ( stmt )
		{
			sqlite3_finalize(stmt);
			stmt = NULL;
		}

		// roll back on error
		sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
		throw e;
	}

	return ids;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getByFilter(const std::vector< Store::FilterEntry > filterList, const std::vector< Store::SortEntry > sortList, const int64_t resultsStartIndex, const int64_t resultsNumber)
{
	// mutex lock
	scoped_db_lock lock(dbConn);

	// call function with lock guard
	return getByFilter(filterList, sortList, resultsStartIndex, resultsNumber, lock.db);
}

template <IConnectedVisionDataClass TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_SQLite_BaseClass<TDataClass>::getByFilter(std::vector< Store::FilterEntry > filterList, std::vector< Store::SortEntry > sortList, const int64_t resultsStartIndex, const int64_t resultsNumber, sqlite3 *db)
{
	std::vector< shared_ptr<const TDataClass> > objs;
	sqlite3_stmt *stmt = NULL;
	int bindIdx;

	// do we have a valid range
	bool limitationEnabled = ( resultsStartIndex > 0 ) || ( resultsNumber > 0 );
	if ( resultsStartIndex < 0 )
		return objs;

	// verify that we have a valid DB connection
	if ( !db )
	{
		throw ConnectedVision::runtime_error( "no DB connection" );
	}

	// get unique object id name
	const std::string& key = objectKey();

	// build SQL statement
	std::string sql = "SELECT ";

	// fields
	sql += this->columnNames;

	// add limit / close SQL
	if ( limitationEnabled )
	{
		// inner select to get distinct list of ids for limitation
		sql += " FROM ( SELECT DISTINCT " + key + " AS __key from " + this->tableName + " ";
	}
	else
	{
		// table name
		sql += " FROM " + this->tableName +" ";
	}

	// prepare filter
	bindIdx = 2;
	if ( filterList.size() > 0 )
	{
		sql += "WHERE ";
		appendFilter(sql, filterList, bindIdx);
	}

	std::vector< Store::SortEntry > internalSortList;
	// copy sort list
	for ( std::vector< Store::SortEntry >::const_iterator it = sortList.begin(); it != sortList.end(); it++ )
	{
		// make sure that we do not sort by sub criteria
		if ( it->name.find('.') == std::string::npos )
			internalSortList.push_back( *it );
	}

	// force sort (grouping) by sort index
	appendObjectGrouping( internalSortList );

	// prepare sort
	sql += " ORDER BY ";
	appendSort(sql, internalSortList);


	// add limit / close SQL
	if ( limitationEnabled )
	{
		// self join table with its distinct list of ids)
		sql += " LIMIT ?2 OFFSET ?1 ), "  + this->tableName + " WHERE " + key + " = __key ORDER BY ";
		appendSort(sql, internalSortList);
	}

	// prepare statement
	const char *tail;
	int error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);		
	if (error == SQLITE_OK)
	{
		// bind filter
		bindIdx = 2;
		if ( filterList.size() > 0 )
		{
			bindFilter(stmt, filterList, bindIdx);
		}

		// set range
		if ( limitationEnabled )
		{
			sqlite3_bind_int64(stmt, 1, resultsStartIndex);
			sqlite3_bind_int64(stmt, 2, resultsNumber );
		}

		// read first line
		// execute SQL
		error = sqlite3_step(stmt);

		// read all objects
		shared_ptr<const TDataClass> obj;
		while ( error == SQLITE_ROW )
		{
			error = readObject(stmt, obj, db);
			if ( obj )
				objs.push_back(obj);
		}

		// clean up
		sqlite3_finalize(stmt); stmt = NULL;

		if ( error != SQLITE_DONE )
		{
			throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
		}
	}
	else
	{
		sqlite3_finalize(stmt); stmt = NULL;
		throw ConnectedVision::runtime_error( sqlite3_errmsg(db) );
	}

	return objs;
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::appendSort(std::string& sql, const std::vector<Store::SortEntry>& sortList) const
{
	unsigned int size = 0;

	for (std::vector<Store::SortEntry>::const_iterator item = sortList.begin(); item != sortList.end(); ++item)
	{
		if ( item != sortList.begin() )
			sql += ", ";

		if ( item->name.find('\"') != std::string::npos )
		{
			throw ConnectedVision::runtime_error( "DB Order Item Error: malformed name: " + item->name);
		}

		sql += "\"" + item->name + "\" ";
		if ( item->order == Store::Order:: DESC )
			sql += "DESC";
		else
			sql += "ASC";
	}
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::appendFilter(std::string& sql, const std::vector<Store::FilterEntry>& filterList, int& bindIdx) const
{
	size_t size = 0;

	for (std::vector<Store::FilterEntry>::const_iterator item = filterList.begin(); item != filterList.end(); ++item)
	{
		if ( item != filterList.begin() )
			sql += " AND";

		if ( item->name.find('\"') != std::string::npos )
		{
			throw ConnectedVision::runtime_error( "DB Filter Error: malformed name: " + item->name);
		}

		switch ( item->operation )
		{	
		case Store::Op::EQUAL:
			sql += " \"" + item->name + "\" = ?" + intToStr( ++bindIdx );
			break;
		case Store::Op::NOTEQUAL:
			sql += " \"" + item->name + "\" <> ?" + intToStr( ++bindIdx );
			break;
		case Store::Op::SMALLEREQUAL:
			sql += " \"" + item->name + "\" <= ?" + intToStr( ++bindIdx );
			break;
		case Store::Op::GREATEREQUAL:
			sql += " \"" + item->name + "\" >= ?" + intToStr( ++bindIdx );
			break;
		case Store::Op::SMALLER:
			sql += " \"" + item->name + "\" < ?" + intToStr( ++bindIdx );
			break;
		case Store::Op::GREATER:
			sql += " \"" + item->name + "\" > ?" + intToStr( ++bindIdx );
			break;
		case Store::Op::INLIST:
		case Store::Op::NOTINLIST:
			sql += " \"" + item->name + "\" ";
			if ( item->operation == Store::Op::NOTINLIST )
				sql += "NOT ";
			sql += "IN (";
			switch ( item->type )
			{	
			case Store::Type::STRING:
				size = item->vectorString.size();
				break;
			case Store::Type::INTEGER:
				size = item->vectorInteger.size();
				break;
			case Store::Type::DOUBLE:
				size = item->vectorDouble.size();
				break;
			default:
				throw ConnectedVision::runtime_error( "DB Filter Error: unknown type");
				
			}
			for ( size_t i=0; i < size; i++)
			{
				if ( i != 0 )
					sql += ", ";
				sql += "?" + intToStr( ++bindIdx );
			}
			sql += ")";
			break;

		default:
			throw ConnectedVision::runtime_error( "DB Filter Error: unknown filter operation");
			break;
		}
	}
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::bindFilter(sqlite3_stmt *stmt, const std::vector<Store::FilterEntry>& filterList, int& bindIdx) const
{
	for (std::vector<Store::FilterEntry>::const_iterator item = filterList.begin(); item != filterList.end(); ++item)
	{
		switch ( item->type )
		{	
		case Store::Type::STRING:
			if ( item->operation == Store::Op::INLIST || item->operation == Store::Op::NOTINLIST )
			{
				// vector value
				for ( unsigned int i = 0; i < item->vectorString.size(); i++ )
				{
					sqlite3_bind_text(stmt, ++bindIdx, item->vectorString[i].c_str(), -1, SQLITE_STATIC);
				}
			}
			else
			{
				// scalar value
				sqlite3_bind_text(stmt, ++bindIdx, item->valueString.c_str(), -1, SQLITE_STATIC);
			}
			break;
		case Store::Type::INTEGER:
			if ( item->operation == Store::Op::INLIST || item->operation == Store::Op::NOTINLIST )
			{
				// vector value
				for ( unsigned int i = 0; i < item->vectorInteger.size(); i++ )
				{
					sqlite3_bind_int64(stmt, ++bindIdx, item->vectorInteger[i]);
				}
			}
			else
			{
				// scalar value
				sqlite3_bind_int64(stmt, ++bindIdx, item->valueInteger);
			}
			break;
		case Store::Type::DOUBLE:
			if ( item->operation == Store::Op::INLIST || item->operation == Store::Op::NOTINLIST )
			{
				// vector value
				for ( unsigned int i = 0; i < item->vectorInteger.size(); i++ )
				{
					sqlite3_bind_double(stmt, ++bindIdx, item->vectorDouble[i]);
				}
			}
			else
			{
				// scalar value
				sqlite3_bind_double(stmt, ++bindIdx, item->valueDouble);
			}
			break;

		default:
			throw ConnectedVision::runtime_error( "DB Filter Error: unknown type");
			
		}
	}
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::deleteByFilter(const std::vector< Store::FilterEntry > filterList)
{
	// mutex lock
	scoped_db_lock lock(dbConn);

	// call function with lock guard
	deleteByFilter(filterList, lock.db);
}

template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::deleteByFilter(const std::vector< Store::FilterEntry > filterList,  sqlite3 *db)
{
	int bindIdx;	sqlite3_stmt *stmt = NULL;

	// verify that we have a valid DB connection
	if ( !db )
	{
		throw ConnectedVision::runtime_error( "no DB connection" );
	}

	std::string sql = "DELETE FROM " + this->tableName;

	// prepare filter
	bindIdx = 2;
	if ( filterList.size() > 0 )
	{
		sql += " WHERE ";
		appendFilter(sql, filterList, bindIdx);
	}


	// prepare statement
	const char *tail;
	int error = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, &tail);		
	
	if (error == SQLITE_OK)
	{
		bindIdx = 2;

		// bind filter
		if ( filterList.size() > 0 )
		{
			bindFilter(stmt, filterList, bindIdx);
		}

		// execute SQL
		error = sqlite3_step(stmt);
		sqlite3_finalize(stmt);
	}

	if (error != SQLITE_DONE)
	{
		const char *err_msg = sqlite3_errmsg( db );
		sqlite3_finalize(stmt);
		throw ConnectedVision::runtime_error( err_msg );
	}


}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<TDataClass> Store_SQLite_BaseClass<TDataClass>::create()
{
	ConnectedVision::shared_ptr<TDataClass> data = dataAllocator->create();
	if ( data )
	{
		data->set_configID( this->configID );
	}
	return data;
}


template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<const TDataClass> Store_SQLite_BaseClass<TDataClass>::make_const(ConnectedVision::shared_ptr<TDataClass>& data) const
{
	return this->dataAllocator->make_const(data);
}
		
template <IConnectedVisionDataClass TDataClass>
void Store_SQLite_BaseClass<TDataClass>::initiateRelease(ConnectedVision::shared_ptr<const TDataClass>& dataConst)
{
	this->dataAllocator->initiateRelease(dataConst);
}

}} // namespace scope

#endif // Store_SQLite_BaseClass_class
