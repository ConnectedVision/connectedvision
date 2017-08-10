/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_DummyBoundingBoxes_params_boundingBoxStart.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_DummyBoundingBoxes_params_boundingBoxStart_def
#define Class_DummyBoundingBoxes_params_boundingBoxStart_def

#include "stubs/Stub_DummyBoundingBoxes_params_boundingBoxStart.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

// if you want to extend the auto-generated class, enable the line below
//#define Class_DummyBoundingBoxes_params_boundingBoxStart_extended

#ifdef Class_DummyBoundingBoxes_params_boundingBoxStart_extended
/**
 * Class_DummyBoundingBoxes_params_boundingBoxStart
 * 
 * module: DummyBoundingBoxes
 * description: first bounding box data at start of video
 */
class Class_DummyBoundingBoxes_params_boundingBoxStart : public Stub_DummyBoundingBoxes_params_boundingBoxStart {

public:
	Class_DummyBoundingBoxes_params_boundingBoxStart() {};
	Class_DummyBoundingBoxes_params_boundingBoxStart(const ::rapidjson::Value& value) : Stub_DummyBoundingBoxes_params_boundingBoxStart(value) {};
	Class_DummyBoundingBoxes_params_boundingBoxStart(const std::string& str) : Stub_DummyBoundingBoxes_params_boundingBoxStart(str) {};
	virtual ~Class_DummyBoundingBoxes_params_boundingBoxStart() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> Class_DummyBoundingBoxes_params_boundingBoxStart_p;
#endif // Class_DummyBoundingBoxes_params_boundingBoxStart_extended

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_DummyBoundingBoxes_params_boundingBoxStart_Default.h"

#endif // Class_DummyBoundingBoxes_params_boundingBoxStart_def