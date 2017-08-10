/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_ModuleStatus.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_ModuleStatus_def
#define Class_ModuleStatus_def

#include "stubs/Stub_ModuleStatus.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_ModuleStatus_extended

#ifdef Class_ModuleStatus_extended
/**
 * Class_ModuleStatus
 * 
 * module: 
 * description: Module Status Schema
 */
class Class_ModuleStatus : public Stub_ModuleStatus {

public:
	Class_ModuleStatus() {};
	Class_ModuleStatus(const ::rapidjson::Value& value) : Stub_ModuleStatus(value) {};
	Class_ModuleStatus(const std::string& str) : Stub_ModuleStatus(str) {};
	virtual ~Class_ModuleStatus() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_ModuleStatus> Class_ModuleStatus_p;
#endif // Class_ModuleStatus_extended

} // namespace ConnectedVision

#include "stubs/Class_ModuleStatus_Default.h"

#endif // Class_ModuleStatus_def