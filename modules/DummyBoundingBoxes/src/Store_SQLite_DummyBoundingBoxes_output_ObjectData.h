/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_DummyBoundingBoxes_output_ObjectData.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_SQLite_DummyBoundingBoxes_output_ObjectData_def
#define Store_SQLite_DummyBoundingBoxes_output_ObjectData_def

#include "stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_DummyBoundingBoxes_output_ObjectData_extended

#ifdef Store_SQLite_DummyBoundingBoxes_output_ObjectData_extended
/**
 * Store_SQLite_DummyBoundingBoxes_output_ObjectData
 *
 * module: DummyBoundingBoxes
 * description: object meta data
 */
class Store_SQLite_DummyBoundingBoxes_output_ObjectData : public Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData {
public:
	/**
	* constructor
	*/
	Store_SQLite_DummyBoundingBoxes_output_ObjectData(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_DummyBoundingBoxes_output_ObjectData()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_DummyBoundingBoxes_output_ObjectData_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData_extended

#ifdef Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData_extended
/**
 * factory for Store_SQLite_DummyBoundingBoxes_output_ObjectData
 */
class Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData : public Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData_enabled
#endif // Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData_extended

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_SQLite_DummyBoundingBoxes_output_ObjectData_Default.h"

#endif // Store_SQLite_DummyBoundingBoxes_output_ObjectData_def