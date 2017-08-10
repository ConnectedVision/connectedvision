/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_DirectoryIterator_output_FileMetadata.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_def
#define Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_def

#include "stubs/Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_extended

#ifdef Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_extended
/**
 * SQLite store manager for: Store_SQLite_DirectoryIterator_output_FileMetadata
 */
class Store_Manager_SQLite_DirectoryIterator_output_FileMetadata : public Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_DirectoryIterator_output_FileMetadata(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_DirectoryIterator_output_FileMetadata ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_DirectoryIterator_output_FileMetadata()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_Default.h"

#endif // Store_Manager_SQLite_DirectoryIterator_output_FileMetadata_def