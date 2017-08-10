// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!
#ifndef Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode_def
#define Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_UnitTest_GeneratorTestCode.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode
 *
 * module: 
 * description: test object to check generator
 */
class Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_UnitTest_GeneratorTestCode> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode(const Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode & operator = (const Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode_def