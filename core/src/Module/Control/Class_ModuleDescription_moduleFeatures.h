/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ModuleDescription_moduleFeatures.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_ModuleDescription_moduleFeatures_def
#define Class_ModuleDescription_moduleFeatures_def

#include "stubs/Stub_ModuleDescription_moduleFeatures.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ModuleDescription_moduleFeatures_extended

#ifdef Class_ModuleDescription_moduleFeatures_extended
/**
 * Class_ModuleDescription_moduleFeatures
 * 
 * module: 
 * description: JSON schema of module features
 */
class Class_ModuleDescription_moduleFeatures : public Stub_ModuleDescription_moduleFeatures {

public:
	Class_ModuleDescription_moduleFeatures() {};
	Class_ModuleDescription_moduleFeatures(const ::rapidjson::Value& value) : Stub_ModuleDescription_moduleFeatures(value) {};
	Class_ModuleDescription_moduleFeatures(const std::string& str) : Stub_ModuleDescription_moduleFeatures(str) {};
	virtual ~Class_ModuleDescription_moduleFeatures() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ModuleDescription_moduleFeatures> Class_ModuleDescription_moduleFeatures_p;
#endif // Class_ModuleDescription_moduleFeatures_extended

} // namespace ConnectedVision

#include "stubs/Class_ModuleDescription_moduleFeatures_Default.h"

#endif // Class_ModuleDescription_moduleFeatures_def