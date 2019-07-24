// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// NEVER TOUCH this file!

#ifndef Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData_def
#define Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData_def

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>

// include class
#include "../Class_DummyBoundingBoxes_output_ObjectData.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

// --> Do NOT EDIT <--
/**
 * stub class for: Store_Manager_Ringbuffer_DummyBoundingBoxes_output_ObjectData
 *
 * module: DummyBoundingBoxes
 * description: object meta data
 */
class Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData : public ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool<Class_DummyBoundingBoxes_output_ObjectData> {
public:
	/**
	* constructor
	*/
	Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData();

private:
	// singleton in module scope
	Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData(const Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData &);	// restrict copy constructor
	Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData & operator = (const Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData &); // restrict assign operator
	static int creationCount;
};


} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Store_Manager_Ringbuffer_Stub_DummyBoundingBoxes_output_ObjectData_def