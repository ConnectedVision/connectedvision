/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ThumbnailGenerator_input_BoundingBox_boundingBox.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_ThumbnailGenerator_input_BoundingBox_boundingBox_def
#define Class_ThumbnailGenerator_input_BoundingBox_boundingBox_def

#include "stubs/Stub_ThumbnailGenerator_input_BoundingBox_boundingBox.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ThumbnailGenerator_input_BoundingBox_boundingBox_extended

#ifdef Class_ThumbnailGenerator_input_BoundingBox_boundingBox_extended
/**
 * Class_ThumbnailGenerator_input_BoundingBox_boundingBox
 * 
 * module: Thumbnail Generator
 * description: bounding box
 */
class Class_ThumbnailGenerator_input_BoundingBox_boundingBox : public Stub_ThumbnailGenerator_input_BoundingBox_boundingBox {

public:
	Class_ThumbnailGenerator_input_BoundingBox_boundingBox() {};
	Class_ThumbnailGenerator_input_BoundingBox_boundingBox(const ::rapidjson::Value& value) : Stub_ThumbnailGenerator_input_BoundingBox_boundingBox(value) {};
	Class_ThumbnailGenerator_input_BoundingBox_boundingBox(const std::string& str) : Stub_ThumbnailGenerator_input_BoundingBox_boundingBox(str) {};
	virtual ~Class_ThumbnailGenerator_input_BoundingBox_boundingBox() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> Class_ThumbnailGenerator_input_BoundingBox_boundingBox_p;
#endif // Class_ThumbnailGenerator_input_BoundingBox_boundingBox_extended

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_ThumbnailGenerator_input_BoundingBox_boundingBox_Default.h"

#endif // Class_ThumbnailGenerator_input_BoundingBox_boundingBox_def