/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_def
#define Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_def

#include "stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_extended

#ifdef Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_extended
/**
 * SQLite store manager for: Store_SQLite_ThumbnailGenerator_input_ImageMetadata
 */
class Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata : public Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_Default.h"

#endif // Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_def