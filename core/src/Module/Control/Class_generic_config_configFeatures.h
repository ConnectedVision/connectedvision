/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_generic_config_configFeatures.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_generic_config_configFeatures_def
#define Class_generic_config_configFeatures_def

#include "stubs/Stub_generic_config_configFeatures.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_generic_config_configFeatures_extended

#ifdef Class_generic_config_configFeatures_extended
/**
 * Class_generic_config_configFeatures
 * 
 * module: 
 * description: JSON schema of features of the config
 */
class Class_generic_config_configFeatures : public Stub_generic_config_configFeatures {

public:
	Class_generic_config_configFeatures() {};
	Class_generic_config_configFeatures(const ::rapidjson::Value& value) : Stub_generic_config_configFeatures(value) {};
	Class_generic_config_configFeatures(const std::string& str) : Stub_generic_config_configFeatures(str) {};
	virtual ~Class_generic_config_configFeatures() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_generic_config_configFeatures> Class_generic_config_configFeatures_p;
#endif // Class_generic_config_configFeatures_extended

} // namespace ConnectedVision

#include "stubs/Class_generic_config_configFeatures_Default.h"

#endif // Class_generic_config_configFeatures_def