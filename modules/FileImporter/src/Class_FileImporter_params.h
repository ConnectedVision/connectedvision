/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_FileImporter_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_FileImporter_params_def
#define Class_FileImporter_params_def

#include "stubs/Stub_FileImporter_params.h"

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

// if you want to extend the auto-generated class, enable the line below
//#define Class_FileImporter_params_extended

#ifdef Class_FileImporter_params_extended
/**
 * Class_FileImporter_params
 * 
 * module: FileImporter
 * description: 
 */
class Class_FileImporter_params : public Stub_FileImporter_params {

public:
	Class_FileImporter_params() {};
	Class_FileImporter_params(const ::rapidjson::Value& value) : Stub_FileImporter_params(value) {};
	Class_FileImporter_params(const std::string& str) : Stub_FileImporter_params(str) {};
	virtual ~Class_FileImporter_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_FileImporter_params> Class_FileImporter_params_p;
#endif // Class_FileImporter_params_extended

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_FileImporter_params_Default.h"

#endif // Class_FileImporter_params_def