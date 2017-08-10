// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode.h
// This file implements the Store_Manager interface for a ringbuffer
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_def
#define Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_def

#include "stubs/Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode.h"

namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

// if you want to extend the auto-generated class, enable the line below
//#define Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_extended

#ifdef Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_extended
/**
 * Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode
 *
 * module: 
 * description: test object to check generator
 */
class Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode : public Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) : Store_Manager_Ringbuffer_Stub_UnitTest_GeneratorTestCode ( storeCount, ringbufferSize, poolSize )
	{}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode()
	{}

 // TODO --> Your declarations and code comes HERE! <--

};
#endif // Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_extended

} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision

#include "stubs/Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_Default.h"

#endif // Store_Manager_Ringbuffer_UnitTest_GeneratorTestCode_def