// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata.h
// NEVER TOUCH this file!

#ifndef Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata_def
#define Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_DirectoryIterator_output_FileMetadata.h"
#include "../Store_SQLite_DirectoryIterator_output_FileMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_DirectoryIterator_output_FileMetadata
 */
class Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_DirectoryIterator_output_FileMetadata>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata(const Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata & operator = (const Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata_def