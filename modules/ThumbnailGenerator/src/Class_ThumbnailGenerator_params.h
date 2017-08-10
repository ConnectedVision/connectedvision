/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ThumbnailGenerator_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_ThumbnailGenerator_params_def
#define Class_ThumbnailGenerator_params_def

#include "stubs/Stub_ThumbnailGenerator_params.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ThumbnailGenerator_params_extended

#ifdef Class_ThumbnailGenerator_params_extended
/**
 * Class_ThumbnailGenerator_params
 * 
 * module: Thumbnail Generator
 * description: 
 */
class Class_ThumbnailGenerator_params : public Stub_ThumbnailGenerator_params {

public:
	Class_ThumbnailGenerator_params() {};
	Class_ThumbnailGenerator_params(const ::rapidjson::Value& value) : Stub_ThumbnailGenerator_params(value) {};
	Class_ThumbnailGenerator_params(const std::string& str) : Stub_ThumbnailGenerator_params(str) {};
	virtual ~Class_ThumbnailGenerator_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ThumbnailGenerator_params> Class_ThumbnailGenerator_params_p;
#endif // Class_ThumbnailGenerator_params_extended

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_ThumbnailGenerator_params_Default.h"

#endif // Class_ThumbnailGenerator_params_def