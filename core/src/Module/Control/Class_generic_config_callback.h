/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_generic_config_callback.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_generic_config_callback_def
#define Class_generic_config_callback_def

#include "stubs/Stub_generic_config_callback.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_generic_config_callback_extended

#ifdef Class_generic_config_callback_extended
/**
 * Class_generic_config_callback
 * 
 * module: 
 * description: register a callback for live mode
 */
class Class_generic_config_callback : public Stub_generic_config_callback {

public:
	Class_generic_config_callback() {};
	Class_generic_config_callback(const ::rapidjson::Value& value) : Stub_generic_config_callback(value) {};
	Class_generic_config_callback(const std::string& str) : Stub_generic_config_callback(str) {};
	virtual ~Class_generic_config_callback() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_generic_config_callback> Class_generic_config_callback_p;
#endif // Class_generic_config_callback_extended

} // namespace ConnectedVision

#include "stubs/Class_generic_config_callback_Default.h"

#endif // Class_generic_config_callback_def