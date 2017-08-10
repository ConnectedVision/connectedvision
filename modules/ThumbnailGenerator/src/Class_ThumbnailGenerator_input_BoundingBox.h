/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ThumbnailGenerator_input_BoundingBox.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_ThumbnailGenerator_input_BoundingBox_def
#define Class_ThumbnailGenerator_input_BoundingBox_def

#include "stubs/Stub_ThumbnailGenerator_input_BoundingBox.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ThumbnailGenerator_input_BoundingBox_extended

#ifdef Class_ThumbnailGenerator_input_BoundingBox_extended
/**
 * Class_ThumbnailGenerator_input_BoundingBox
 * 
 * module: Thumbnail Generator
 * description: rectangular region which is used for the cropping or for overlaying bounding boxes
 */
class Class_ThumbnailGenerator_input_BoundingBox : public Stub_ThumbnailGenerator_input_BoundingBox {

public:
	Class_ThumbnailGenerator_input_BoundingBox() {};
	Class_ThumbnailGenerator_input_BoundingBox(const ::rapidjson::Value& value) : Stub_ThumbnailGenerator_input_BoundingBox(value) {};
	Class_ThumbnailGenerator_input_BoundingBox(const std::string& str) : Stub_ThumbnailGenerator_input_BoundingBox(str) {};
	virtual ~Class_ThumbnailGenerator_input_BoundingBox() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox> Class_ThumbnailGenerator_input_BoundingBox_p;
#endif // Class_ThumbnailGenerator_input_BoundingBox_extended

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_ThumbnailGenerator_input_BoundingBox_Default.h"

#endif // Class_ThumbnailGenerator_input_BoundingBox_def