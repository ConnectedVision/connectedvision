/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_def
#define Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_def

#include "stubs/Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_extended

#ifdef Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_extended
/**
 * SQLite store manager for: Store_SQLite_DummyBoundingBoxes_output_ObjectData
 */
class Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData : public Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_DummyBoundingBoxes_output_ObjectData ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_Default.h"

#endif // Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData_def