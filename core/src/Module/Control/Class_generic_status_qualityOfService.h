/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_generic_status_qualityOfService.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_generic_status_qualityOfService_def
#define Class_generic_status_qualityOfService_def

#include "stubs/Stub_generic_status_qualityOfService.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_generic_status_qualityOfService_extended

#ifdef Class_generic_status_qualityOfService_extended
/**
 * Class_generic_status_qualityOfService
 * 
 * module: 
 * description: quality of service (QoS) parameters
 */
class Class_generic_status_qualityOfService : public Stub_generic_status_qualityOfService {

public:
	Class_generic_status_qualityOfService() {};
	Class_generic_status_qualityOfService(const ::rapidjson::Value& value) : Stub_generic_status_qualityOfService(value) {};
	Class_generic_status_qualityOfService(const std::string& str) : Stub_generic_status_qualityOfService(str) {};
	virtual ~Class_generic_status_qualityOfService() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_generic_status_qualityOfService> Class_generic_status_qualityOfService_p;
#endif // Class_generic_status_qualityOfService_extended

} // namespace ConnectedVision

#include "stubs/Class_generic_status_qualityOfService_Default.h"

#endif // Class_generic_status_qualityOfService_def