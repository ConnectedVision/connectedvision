/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_generic_config.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_generic_config_def
#define Store_Manager_SQLite_Stub_generic_config_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_generic_config.h"
#include "../Store_SQLite_generic_config.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_generic_config
 */
class Store_Manager_SQLite_Stub_generic_config :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_generic_config>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_generic_config(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_generic_config();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_generic_config(const Store_Manager_SQLite_Stub_generic_config &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_generic_config & operator = (const Store_Manager_SQLite_Stub_generic_config &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_generic_config_def