/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_PinDescription_properties.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_PinDescription_properties_def
#define Class_PinDescription_properties_def

#include "stubs/Stub_PinDescription_properties.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_PinDescription_properties_extended

#ifdef Class_PinDescription_properties_extended
/**
 * Class_PinDescription_properties
 * 
 * module: 
 * description: JSON schema of data returned by pin (if MIME is application/json)
 */
class Class_PinDescription_properties : public Stub_PinDescription_properties {

public:
	Class_PinDescription_properties() {};
	Class_PinDescription_properties(const ::rapidjson::Value& value) : Stub_PinDescription_properties(value) {};
	Class_PinDescription_properties(const std::string& str) : Stub_PinDescription_properties(str) {};
	virtual ~Class_PinDescription_properties() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_PinDescription_properties> Class_PinDescription_properties_p;
#endif // Class_PinDescription_properties_extended

} // namespace ConnectedVision

#include "stubs/Class_PinDescription_properties_Default.h"

#endif // Class_PinDescription_properties_def