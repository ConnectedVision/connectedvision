/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_SyntheticVideo_params_bgColor.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_SyntheticVideo_params_bgColor_def
#define Class_SyntheticVideo_params_bgColor_def

#include "stubs/Stub_SyntheticVideo_params_bgColor.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

// if you want to extend the auto-generated class, enable the line below
//#define Class_SyntheticVideo_params_bgColor_extended

#ifdef Class_SyntheticVideo_params_bgColor_extended
/**
 * Class_SyntheticVideo_params_bgColor
 * 
 * module: SyntheticVideo
 * description: background color
 */
class Class_SyntheticVideo_params_bgColor : public Stub_SyntheticVideo_params_bgColor {

public:
	Class_SyntheticVideo_params_bgColor() {};
	Class_SyntheticVideo_params_bgColor(const ::rapidjson::Value& value) : Stub_SyntheticVideo_params_bgColor(value) {};
	Class_SyntheticVideo_params_bgColor(const std::string& str) : Stub_SyntheticVideo_params_bgColor(str) {};
	virtual ~Class_SyntheticVideo_params_bgColor() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_SyntheticVideo_params_bgColor> Class_SyntheticVideo_params_bgColor_p;
#endif // Class_SyntheticVideo_params_bgColor_extended

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_SyntheticVideo_params_bgColor_Default.h"

#endif // Class_SyntheticVideo_params_bgColor_def