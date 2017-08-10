/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_SyntheticVideo_params_fgColor.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_SyntheticVideo_params_fgColor_def
#define Class_SyntheticVideo_params_fgColor_def

#include "stubs/Stub_SyntheticVideo_params_fgColor.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

// if you want to extend the auto-generated class, enable the line below
//#define Class_SyntheticVideo_params_fgColor_extended

#ifdef Class_SyntheticVideo_params_fgColor_extended
/**
 * Class_SyntheticVideo_params_fgColor
 * 
 * module: SyntheticVideo
 * description: foreground color
 */
class Class_SyntheticVideo_params_fgColor : public Stub_SyntheticVideo_params_fgColor {

public:
	Class_SyntheticVideo_params_fgColor() {};
	Class_SyntheticVideo_params_fgColor(const ::rapidjson::Value& value) : Stub_SyntheticVideo_params_fgColor(value) {};
	Class_SyntheticVideo_params_fgColor(const std::string& str) : Stub_SyntheticVideo_params_fgColor(str) {};
	virtual ~Class_SyntheticVideo_params_fgColor() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_SyntheticVideo_params_fgColor> Class_SyntheticVideo_params_fgColor_p;
#endif // Class_SyntheticVideo_params_fgColor_extended

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_SyntheticVideo_params_fgColor_Default.h"

#endif // Class_SyntheticVideo_params_fgColor_def