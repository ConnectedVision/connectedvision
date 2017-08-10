/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_ThumbnailGenerator_input_ImageMetadata.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_SQLite_ThumbnailGenerator_input_ImageMetadata_def
#define Store_SQLite_ThumbnailGenerator_input_ImageMetadata_def

#include "stubs/Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_ThumbnailGenerator_input_ImageMetadata_extended

#ifdef Store_SQLite_ThumbnailGenerator_input_ImageMetadata_extended
/**
 * Store_SQLite_ThumbnailGenerator_input_ImageMetadata
 *
 * module: Thumbnail Generator
 * description: image metadata
 */
class Store_SQLite_ThumbnailGenerator_input_ImageMetadata : public Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata {
public:
	/**
	* constructor
	*/
	Store_SQLite_ThumbnailGenerator_input_ImageMetadata(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_ThumbnailGenerator_input_ImageMetadata()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_ThumbnailGenerator_input_ImageMetadata_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata_extended

#ifdef Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata_extended
/**
 * factory for Store_SQLite_ThumbnailGenerator_input_ImageMetadata
 */
class Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata : public Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_ThumbnailGenerator_input_ImageMetadata ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata_enabled
#endif // Store_SQLite_Factory_ThumbnailGenerator_input_ImageMetadata_extended

} // namespace DataHandling
} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_SQLite_ThumbnailGenerator_input_ImageMetadata_Default.h"

#endif // Store_SQLite_ThumbnailGenerator_input_ImageMetadata_def