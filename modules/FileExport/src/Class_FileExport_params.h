/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_FileExport_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_FileExport_params_def
#define Class_FileExport_params_def

#include "stubs/Stub_FileExport_params.h"

namespace ConnectedVision {
namespace Module {
namespace FileExport {

// if you want to extend the auto-generated class, enable the line below
//#define Class_FileExport_params_extended

#ifdef Class_FileExport_params_extended
/**
 * Class_FileExport_params
 * 
 * module: FileExport
 * description: 
 */
class Class_FileExport_params : public Stub_FileExport_params {

public:
	Class_FileExport_params() {};
	Class_FileExport_params(const ::rapidjson::Value& value) : Stub_FileExport_params(value) {};
	Class_FileExport_params(const std::string& str) : Stub_FileExport_params(str) {};
	virtual ~Class_FileExport_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_FileExport_params> Class_FileExport_params_p;
#endif // Class_FileExport_params_extended

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_FileExport_params_Default.h"

#endif // Class_FileExport_params_def