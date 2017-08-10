// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode.h
// NEVER TOUCH this file!
#ifndef Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode_def
#define Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode_def

#include <DBConnection.h>
#include <DataHandling/Store_Manager_Basic.h>

#include "../Class_UnitTest_GeneratorTestCode.h"
#include "../Store_SQLite_UnitTest_GeneratorTestCode.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * SQLite store manager for: Store_SQLite_UnitTest_GeneratorTestCode
 */
class Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode :
	public ConnectedVision::DataHandling::Store_Manager_Basic<Class_UnitTest_GeneratorTestCode>
{
public:
	/**
	* constructor
	*/
	Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode(
		DBConnection& db				///< [in] DB connection object
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode();

private:
	// singleton in module scope
	Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode(const Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode &);	// restrict copy constructor
	Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode & operator = (const Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision

#endif // Store_Manager_SQLite_Stub_UnitTest_GeneratorTestCode_def