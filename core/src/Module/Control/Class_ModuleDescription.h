/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ModuleDescription.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_ModuleDescription_def
#define Class_ModuleDescription_def

#include "stubs/Stub_ModuleDescription.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ModuleDescription_extended

#ifdef Class_ModuleDescription_extended
/**
 * Class_ModuleDescription
 * 
 * module: 
 * description: Module Description Schema
 */
class Class_ModuleDescription : public Stub_ModuleDescription {

public:
	Class_ModuleDescription() {};
	Class_ModuleDescription(const ::rapidjson::Value& value) : Stub_ModuleDescription(value) {};
	Class_ModuleDescription(const std::string& str) : Stub_ModuleDescription(str) {};
	virtual ~Class_ModuleDescription() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ModuleDescription> Class_ModuleDescription_p;
#endif // Class_ModuleDescription_extended

} // namespace ConnectedVision

#include "stubs/Class_ModuleDescription_Default.h"

#endif // Class_ModuleDescription_def