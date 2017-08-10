// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// Store_SQLite_UnitTest_GeneratorTestCode.h
// This file implements the IStore interface for SQLite access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Store_SQLite_UnitTest_GeneratorTestCode_def
#define Store_SQLite_UnitTest_GeneratorTestCode_def

#include "stubs/Store_SQLite_Stub_UnitTest_GeneratorTestCode.h"

namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_UnitTest_GeneratorTestCode_extended

#ifdef Store_SQLite_UnitTest_GeneratorTestCode_extended
/**
 * Store_SQLite_UnitTest_GeneratorTestCode
 *
 * module: 
 * description: test object to check generator
 */
class Store_SQLite_UnitTest_GeneratorTestCode : public Store_SQLite_Stub_UnitTest_GeneratorTestCode {
public:
	/**
	* constructor
	*/
	Store_SQLite_UnitTest_GeneratorTestCode(
		const id_t& configID,			///< [in] config ID
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Stub_UnitTest_GeneratorTestCode ( configID, db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_UnitTest_GeneratorTestCode()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_SQLite_UnitTest_GeneratorTestCode_extended


// if you want to extend the auto-generated class, enable the line below
//#define Store_SQLite_Factory_UnitTest_GeneratorTestCode_extended

#ifdef Store_SQLite_Factory_UnitTest_GeneratorTestCode_extended
/**
 * factory for Store_SQLite_UnitTest_GeneratorTestCode
 */
class Store_SQLite_Factory_UnitTest_GeneratorTestCode : public Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode {
public:
	/**
	* constructor
	*/
	Store_SQLite_Factory_UnitTest_GeneratorTestCode(
		DBConnection& db				///< [in] DB connection object
	) : Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode ( db )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_SQLite_Factory_UnitTest_GeneratorTestCode()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#define Store_SQLite_Factory_UnitTest_GeneratorTestCode_enabled
#endif // Store_SQLite_Factory_UnitTest_GeneratorTestCode_extended

} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision

#include "stubs/Store_SQLite_UnitTest_GeneratorTestCode_Default.h"

#endif // Store_SQLite_UnitTest_GeneratorTestCode_def