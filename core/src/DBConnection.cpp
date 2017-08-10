/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "DBConnection.h"

using namespace std;
using namespace ConnectedVision;

DBConnection::DBConnection()
{
	db = NULL;
	key = 1;
}

DBConnection::~DBConnection()
{
	free();
}

void DBConnection::init(std::string filename, int SQLiteFlags)
{
	if ( !sqlite3_threadsafe() )
	{
		throw std::runtime_error( "[DBConnection::init] SQLite lib is not threadsafe" );	
	}

	// open SQLite connection	
	int error = sqlite3_open_v2( filename.c_str() , &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_FULLMUTEX | SQLiteFlags, NULL);
//	int error = sqlite3_open_v2( filename.c_str() , &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_NOMUTEX, NULL); //@TODO
	if (error)
	{
		db = NULL;
		throw std::runtime_error( "[DBConnection::init] can't open database: " + filename );	
	}
}

void DBConnection::free()
{
	if ( db )
	{
		sqlite3_close( db );
	}
	db = NULL;
}

sqlite3 *DBConnection::lock(int& key)
{
	if ( !db )
	{
		throw std::runtime_error( "[DBConnection::lock] database not initialized" );	
	}

	// mutex lock
	if ( !mutex.timed_lock( boost::posix_time::milliseconds(5000) ) )
	{
		throw std::runtime_error( "[DBConnection::lock] cannot lock database (mutex timeout)" );	
	}

	// create unique key for lock
	this->key++; if ( this->key == 0 ) this->key = 1;
	key = this->key;

	return db;
}

void DBConnection::unlock(int& key)
{
	// check that unlock is for actual lock
	if ( key != this->key )
	{
		throw std::runtime_error( "[DBConnection::lock] cannot unlock database (wrong key)" );	
	}
	key = 0;

	// mutex unlock
	mutex.unlock();
}


scoped_db_lock::scoped_db_lock(DBConnection& dbConn):
	dbConn( dbConn )
{
	this->db = dbConn.lock(this->key);
}

scoped_db_lock::~scoped_db_lock()
{
	dbConn.unlock(this->key);
}
