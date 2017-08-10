/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// OutputPin_DummyBoundingBoxes_output_ObjectData.h
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef OutputPin_DummyBoundingBoxes_output_ObjectData_def
#define OutputPin_DummyBoundingBoxes_output_ObjectData_def

#include "stubs/OutputPin_Stub_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

// if you want to extend the auto-generated class, enable the line below
//#define OutputPin_DummyBoundingBoxes_output_ObjectData_extended

#ifdef OutputPin_DummyBoundingBoxes_output_ObjectData_extended
/**
 * DummyBoundingBoxes_output_ObjectData
 *
 * module: DummyBoundingBoxes
 * description: object meta data
 */
class OutputPin_DummyBoundingBoxes_output_ObjectData : public OutputPin_Stub_DummyBoundingBoxes_output_ObjectData {
public:
	OutputPin_DummyBoundingBoxes_output_ObjectData(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData> > > dataStore) :
		OutputPin_Stub_DummyBoundingBoxes_output_ObjectData(dataStore) {};
	virtual ~OutputPin_DummyBoundingBoxes_output_ObjectData() {}
};
#endif // OutputPin_DummyBoundingBoxes_output_ObjectData_extended

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/OutputPin_DummyBoundingBoxes_output_ObjectData_Default.h"

#endif // OutputPin_DummyBoundingBoxes_output_ObjectData_def