/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_DummyBoundingBoxes_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_DummyBoundingBoxes_params_def
#define Class_DummyBoundingBoxes_params_def

#include "stubs/Stub_DummyBoundingBoxes_params.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

// if you want to extend the auto-generated class, enable the line below
//#define Class_DummyBoundingBoxes_params_extended

#ifdef Class_DummyBoundingBoxes_params_extended
/**
 * Class_DummyBoundingBoxes_params
 * 
 * module: DummyBoundingBoxes
 * description: Dummy Bounding Box Generator configuration
 */
class Class_DummyBoundingBoxes_params : public Stub_DummyBoundingBoxes_params {

public:
	Class_DummyBoundingBoxes_params() {};
	Class_DummyBoundingBoxes_params(const ::rapidjson::Value& value) : Stub_DummyBoundingBoxes_params(value) {};
	Class_DummyBoundingBoxes_params(const std::string& str) : Stub_DummyBoundingBoxes_params(str) {};
	virtual ~Class_DummyBoundingBoxes_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_DummyBoundingBoxes_params> Class_DummyBoundingBoxes_params_p;
#endif // Class_DummyBoundingBoxes_params_extended

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_DummyBoundingBoxes_params_Default.h"

#endif // Class_DummyBoundingBoxes_params_def