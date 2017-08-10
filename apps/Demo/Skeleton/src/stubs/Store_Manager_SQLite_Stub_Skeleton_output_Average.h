// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_Skeleton_output_Average.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_Skeleton_output_Average_def
#define Store_Manager_SQLite_Stub_Skeleton_output_Average_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_Skeleton_output_Average.h"
#include "../Store_SQLite_Skeleton_output_Average.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_Skeleton_output_Average
 */
class Store_Manager_SQLite_Stub_Skeleton_output_Average :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_Skeleton_output_Average>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_Skeleton_output_Average(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_Skeleton_output_Average();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_Skeleton_output_Average(const Store_Manager_SQLite_Stub_Skeleton_output_Average &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_Skeleton_output_Average & operator = (const Store_Manager_SQLite_Stub_Skeleton_output_Average &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_Skeleton_output_Average_def