/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_SyntheticVideo_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_SyntheticVideo_params_def
#define Class_SyntheticVideo_params_def

#include "stubs/Stub_SyntheticVideo_params.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

// if you want to extend the auto-generated class, enable the line below
//#define Class_SyntheticVideo_params_extended

#ifdef Class_SyntheticVideo_params_extended
/**
 * Class_SyntheticVideo_params
 * 
 * module: SyntheticVideo
 * description: 
 */
class Class_SyntheticVideo_params : public Stub_SyntheticVideo_params {

public:
	Class_SyntheticVideo_params() {};
	Class_SyntheticVideo_params(const ::rapidjson::Value& value) : Stub_SyntheticVideo_params(value) {};
	Class_SyntheticVideo_params(const std::string& str) : Stub_SyntheticVideo_params(str) {};
	virtual ~Class_SyntheticVideo_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_SyntheticVideo_params> Class_SyntheticVideo_params_p;
#endif // Class_SyntheticVideo_params_extended

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_SyntheticVideo_params_Default.h"

#endif // Class_SyntheticVideo_params_def