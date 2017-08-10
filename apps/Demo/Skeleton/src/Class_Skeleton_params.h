/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_Skeleton_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_Skeleton_params_def
#define Class_Skeleton_params_def

#include "stubs/Stub_Skeleton_params.h"

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

// if you want to extend the auto-generated class, enable the line below
//#define Class_Skeleton_params_extended

#ifdef Class_Skeleton_params_extended
/**
 * Class_Skeleton_params
 * 
 * module: Skeleton Module
 * description: Skeleton Dummy Parameter
 */
class Class_Skeleton_params : public Stub_Skeleton_params {

public:
	Class_Skeleton_params() {};
	Class_Skeleton_params(const ::rapidjson::Value& value) : Stub_Skeleton_params(value) {};
	Class_Skeleton_params(const std::string& str) : Stub_Skeleton_params(str) {};
	virtual ~Class_Skeleton_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_Skeleton_params> Class_Skeleton_params_p;
#endif // Class_Skeleton_params_extended

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_Skeleton_params_Default.h"

#endif // Class_Skeleton_params_def