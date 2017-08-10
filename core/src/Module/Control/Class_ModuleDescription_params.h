/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ModuleDescription_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_ModuleDescription_params_def
#define Class_ModuleDescription_params_def

#include "stubs/Stub_ModuleDescription_params.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ModuleDescription_params_extended

#ifdef Class_ModuleDescription_params_extended
/**
 * Class_ModuleDescription_params
 * 
 * module: 
 * description: JSON schema of parameters
 */
class Class_ModuleDescription_params : public Stub_ModuleDescription_params {

public:
	Class_ModuleDescription_params() {};
	Class_ModuleDescription_params(const ::rapidjson::Value& value) : Stub_ModuleDescription_params(value) {};
	Class_ModuleDescription_params(const std::string& str) : Stub_ModuleDescription_params(str) {};
	virtual ~Class_ModuleDescription_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ModuleDescription_params> Class_ModuleDescription_params_p;
#endif // Class_ModuleDescription_params_extended

} // namespace ConnectedVision

#include "stubs/Class_ModuleDescription_params_Default.h"

#endif // Class_ModuleDescription_params_def