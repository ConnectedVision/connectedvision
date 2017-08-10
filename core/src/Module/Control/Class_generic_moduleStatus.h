/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_generic_moduleStatus.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_generic_moduleStatus_def
#define Class_generic_moduleStatus_def

#include "stubs/Stub_generic_moduleStatus.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_generic_moduleStatus_extended

#ifdef Class_generic_moduleStatus_extended
/**
 * Class_generic_moduleStatus
 * 
 * module: 
 * description: Module Status Schema
 */
class Class_generic_moduleStatus : public Stub_generic_moduleStatus {

public:
	Class_generic_moduleStatus() {};
	Class_generic_moduleStatus(const ::rapidjson::Value& value) : Stub_generic_moduleStatus(value) {};
	Class_generic_moduleStatus(const std::string& str) : Stub_generic_moduleStatus(str) {};
	virtual ~Class_generic_moduleStatus() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_generic_moduleStatus> Class_generic_moduleStatus_p;
#endif // Class_generic_moduleStatus_extended

} // namespace ConnectedVision

#include "stubs/Class_generic_moduleStatus_Default.h"

#endif // Class_generic_moduleStatus_def