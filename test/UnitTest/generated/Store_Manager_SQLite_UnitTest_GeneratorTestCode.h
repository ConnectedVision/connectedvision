// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_SQLite_UnitTest_GeneratorTestCode.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_Manager_SQLite_UnitTest_GeneratorTestCode_def
#define Store_Manager_SQLite_UnitTest_GeneratorTestCode_def

#include "stubs/Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode.h"

namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_SQLite_UnitTest_GeneratorTestCode_extended

#ifdef Store_Manager_SQLite_UnitTest_GeneratorTestCode_extended
/**
 * SQLite store manager for: Store_SQLite_UnitTest_GeneratorTestCode
 */
class Store_Manager_SQLite_UnitTest_GeneratorTestCode : public Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode {
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_UnitTest_GeneratorTestCode(
		DBConnection& db				///< [in] DB connection object
	) : Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_UnitTest_GeneratorTestCode()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif

} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision

#include "stubs/Store_Manager_SQLite_UnitTest_GeneratorTestCode_Default.h"

#endif // Store_Manager_SQLite_UnitTest_GeneratorTestCode_def