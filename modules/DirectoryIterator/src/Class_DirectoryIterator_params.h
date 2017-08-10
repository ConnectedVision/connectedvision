/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_DirectoryIterator_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_DirectoryIterator_params_def
#define Class_DirectoryIterator_params_def

#include "stubs/Stub_DirectoryIterator_params.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

// if you want to extend the auto-generated class, enable the line below
//#define Class_DirectoryIterator_params_extended

#ifdef Class_DirectoryIterator_params_extended
/**
 * Class_DirectoryIterator_params
 * 
 * module: Directory Iterator
 * description: 
 */
class Class_DirectoryIterator_params : public Stub_DirectoryIterator_params {

public:
	Class_DirectoryIterator_params() {};
	Class_DirectoryIterator_params(const ::rapidjson::Value& value) : Stub_DirectoryIterator_params(value) {};
	Class_DirectoryIterator_params(const std::string& str) : Stub_DirectoryIterator_params(str) {};
	virtual ~Class_DirectoryIterator_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_DirectoryIterator_params> Class_DirectoryIterator_params_p;
#endif // Class_DirectoryIterator_params_extended

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_DirectoryIterator_params_Default.h"

#endif // Class_DirectoryIterator_params_def