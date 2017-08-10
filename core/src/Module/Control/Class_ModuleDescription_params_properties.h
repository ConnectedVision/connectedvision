/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ModuleDescription_params_properties.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_ModuleDescription_params_properties_def
#define Class_ModuleDescription_params_properties_def

#include "stubs/Stub_ModuleDescription_params_properties.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ModuleDescription_params_properties_extended

#ifdef Class_ModuleDescription_params_properties_extended
/**
 * Class_ModuleDescription_params_properties
 * 
 * module: 
 * description: algorithmic specific configuration parameters. This is part of the config chain.
 */
class Class_ModuleDescription_params_properties : public Stub_ModuleDescription_params_properties {

public:
	Class_ModuleDescription_params_properties() {};
	Class_ModuleDescription_params_properties(const ::rapidjson::Value& value) : Stub_ModuleDescription_params_properties(value) {};
	Class_ModuleDescription_params_properties(const std::string& str) : Stub_ModuleDescription_params_properties(str) {};
	virtual ~Class_ModuleDescription_params_properties() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ModuleDescription_params_properties> Class_ModuleDescription_params_properties_p;
#endif // Class_ModuleDescription_params_properties_extended

} // namespace ConnectedVision

#include "stubs/Class_ModuleDescription_params_properties_Default.h"

#endif // Class_ModuleDescription_params_properties_def