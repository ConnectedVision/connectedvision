/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_HostStatus.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_HostStatus_def
#define Class_HostStatus_def

#include "stubs/Stub_HostStatus.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_HostStatus_extended

#ifdef Class_HostStatus_extended
/**
 * Class_HostStatus
 * 
 * module: 
 * description: host status
 */
class Class_HostStatus : public Stub_HostStatus {

public:
	Class_HostStatus() {};
	Class_HostStatus(const ::rapidjson::Value& value) : Stub_HostStatus(value) {};
	Class_HostStatus(const std::string& str) : Stub_HostStatus(str) {};
	virtual ~Class_HostStatus() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_HostStatus> Class_HostStatus_p;
#endif // Class_HostStatus_extended

} // namespace ConnectedVision

#include "stubs/Class_HostStatus_Default.h"

#endif // Class_HostStatus_def