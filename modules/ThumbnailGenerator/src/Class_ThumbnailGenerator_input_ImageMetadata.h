/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ThumbnailGenerator_input_ImageMetadata.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_ThumbnailGenerator_input_ImageMetadata_def
#define Class_ThumbnailGenerator_input_ImageMetadata_def

#include "stubs/Stub_ThumbnailGenerator_input_ImageMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ThumbnailGenerator_input_ImageMetadata_extended

#ifdef Class_ThumbnailGenerator_input_ImageMetadata_extended
/**
 * Class_ThumbnailGenerator_input_ImageMetadata
 * 
 * module: Thumbnail Generator
 * description: image metadata
 */
class Class_ThumbnailGenerator_input_ImageMetadata : public Stub_ThumbnailGenerator_input_ImageMetadata {

public:
	Class_ThumbnailGenerator_input_ImageMetadata() {};
	Class_ThumbnailGenerator_input_ImageMetadata(const ::rapidjson::Value& value) : Stub_ThumbnailGenerator_input_ImageMetadata(value) {};
	Class_ThumbnailGenerator_input_ImageMetadata(const std::string& str) : Stub_ThumbnailGenerator_input_ImageMetadata(str) {};
	virtual ~Class_ThumbnailGenerator_input_ImageMetadata() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata> Class_ThumbnailGenerator_input_ImageMetadata_p;
#endif // Class_ThumbnailGenerator_input_ImageMetadata_extended

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_ThumbnailGenerator_input_ImageMetadata_Default.h"

#endif // Class_ThumbnailGenerator_input_ImageMetadata_def