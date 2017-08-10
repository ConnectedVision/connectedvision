/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_PinDescription.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_PinDescription_def
#define Class_PinDescription_def

#include "stubs/Stub_PinDescription.h"

namespace ConnectedVision {

// if you want to extend the auto-generated class, enable the line below
//#define Class_PinDescription_extended

#ifdef Class_PinDescription_extended
/**
 * Class_PinDescription
 * 
 * module: 
 * description: 
 */
class Class_PinDescription : public Stub_PinDescription {

public:
	Class_PinDescription() {};
	Class_PinDescription(const ::rapidjson::Value& value) : Stub_PinDescription(value) {};
	Class_PinDescription(const std::string& str) : Stub_PinDescription(str) {};
	virtual ~Class_PinDescription() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_PinDescription> Class_PinDescription_p;
#endif // Class_PinDescription_extended

} // namespace ConnectedVision

#include "stubs/Class_PinDescription_Default.h"

#endif // Class_PinDescription_def