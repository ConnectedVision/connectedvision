/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_VideoImporter_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_VideoImporter_params_def
#define Class_VideoImporter_params_def

#include "stubs/Stub_VideoImporter_params.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

// if you want to extend the auto-generated class, enable the line below
//#define Class_VideoImporter_params_extended

#ifdef Class_VideoImporter_params_extended
/**
 * Class_VideoImporter_params
 * 
 * module: VideoImporter
 * description: 
 */
class Class_VideoImporter_params : public Stub_VideoImporter_params {

public:
	Class_VideoImporter_params() {};
	Class_VideoImporter_params(const ::rapidjson::Value& value) : Stub_VideoImporter_params(value) {};
	Class_VideoImporter_params(const std::string& str) : Stub_VideoImporter_params(str) {};
	virtual ~Class_VideoImporter_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_VideoImporter_params> Class_VideoImporter_params_p;
#endif // Class_VideoImporter_params_extended

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_VideoImporter_params_Default.h"

#endif // Class_VideoImporter_params_def