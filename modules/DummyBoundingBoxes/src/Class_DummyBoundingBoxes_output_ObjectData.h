/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_DummyBoundingBoxes_output_ObjectData.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_DummyBoundingBoxes_output_ObjectData_def
#define Class_DummyBoundingBoxes_output_ObjectData_def

#include "stubs/Stub_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

// if you want to extend the auto-generated class, enable the line below
//#define Class_DummyBoundingBoxes_output_ObjectData_extended

#ifdef Class_DummyBoundingBoxes_output_ObjectData_extended
/**
 * Class_DummyBoundingBoxes_output_ObjectData
 * 
 * module: DummyBoundingBoxes
 * description: object meta data
 */
class Class_DummyBoundingBoxes_output_ObjectData : public Stub_DummyBoundingBoxes_output_ObjectData {

public:
	Class_DummyBoundingBoxes_output_ObjectData() {};
	Class_DummyBoundingBoxes_output_ObjectData(const ::rapidjson::Value& value) : Stub_DummyBoundingBoxes_output_ObjectData(value) {};
	Class_DummyBoundingBoxes_output_ObjectData(const std::string& str) : Stub_DummyBoundingBoxes_output_ObjectData(str) {};
	virtual ~Class_DummyBoundingBoxes_output_ObjectData() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData> Class_DummyBoundingBoxes_output_ObjectData_p;
#endif // Class_DummyBoundingBoxes_output_ObjectData_extended

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_DummyBoundingBoxes_output_ObjectData_Default.h"

#endif // Class_DummyBoundingBoxes_output_ObjectData_def