/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ModuleDescription_configFeatures.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_ModuleDescription_configFeatures_def
#define Class_ModuleDescription_configFeatures_def

#include "stubs/Stub_ModuleDescription_configFeatures.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ModuleDescription_configFeatures_extended

#ifdef Class_ModuleDescription_configFeatures_extended
/**
 * Class_ModuleDescription_configFeatures
 * 
 * module: 
 * description: JSON schema of features of the config
 */
class Class_ModuleDescription_configFeatures : public Stub_ModuleDescription_configFeatures {

public:
	Class_ModuleDescription_configFeatures() {};
	Class_ModuleDescription_configFeatures(const ::rapidjson::Value& value) : Stub_ModuleDescription_configFeatures(value) {};
	Class_ModuleDescription_configFeatures(const std::string& str) : Stub_ModuleDescription_configFeatures(str) {};
	virtual ~Class_ModuleDescription_configFeatures() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ModuleDescription_configFeatures> Class_ModuleDescription_configFeatures_p;
#endif // Class_ModuleDescription_configFeatures_extended

} // namespace ConnectedVision

#include "stubs/Class_ModuleDescription_configFeatures_Default.h"

#endif // Class_ModuleDescription_configFeatures_def