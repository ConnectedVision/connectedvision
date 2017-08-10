/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DBConnection_def
#define DBConnection_def

#include <string>
#include <sqlite3.h>
#include <boost/thread.hpp>

namespace ConnectedVision
{

// TODO add scoped lock

class DBConnection
{
public:
	DBConnection();
    virtual ~DBConnection();

	void init(std::string filename, int SQLiteFlags = 0);
	void free();

	sqlite3 *lock(int& key);
	void unlock(int& key);

protected:
	sqlite3 *db;
	int key;
	boost::timed_mutex mutex;

};

class scoped_db_lock
{
public:
	scoped_db_lock(DBConnection& dbConn);
	virtual ~scoped_db_lock();

	sqlite3 *db;

private:
	DBConnection& dbConn;
	int key;

	// disable default constructor
    scoped_db_lock();
    scoped_db_lock(scoped_db_lock const&);
    scoped_db_lock& operator=(scoped_db_lock const&);
};

} // namespace ConnectedVision

#endif // DBConnection_def