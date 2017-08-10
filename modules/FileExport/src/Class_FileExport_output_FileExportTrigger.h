/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_FileExport_output_FileExportTrigger.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_FileExport_output_FileExportTrigger_def
#define Class_FileExport_output_FileExportTrigger_def

#include "stubs/Stub_FileExport_output_FileExportTrigger.h"

namespace ConnectedVision {
namespace Module {
namespace FileExport {

// if you want to extend the auto-generated class, enable the line below
//#define Class_FileExport_output_FileExportTrigger_extended

#ifdef Class_FileExport_output_FileExportTrigger_extended
/**
 * Class_FileExport_output_FileExportTrigger
 * 
 * module: FileExport
 * description: output pin used as trigger for file export of data elements available at the input pin with matching timestamp or id
 */
class Class_FileExport_output_FileExportTrigger : public Stub_FileExport_output_FileExportTrigger {

public:
	Class_FileExport_output_FileExportTrigger() {};
	Class_FileExport_output_FileExportTrigger(const ::rapidjson::Value& value) : Stub_FileExport_output_FileExportTrigger(value) {};
	Class_FileExport_output_FileExportTrigger(const std::string& str) : Stub_FileExport_output_FileExportTrigger(str) {};
	virtual ~Class_FileExport_output_FileExportTrigger() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_FileExport_output_FileExportTrigger> Class_FileExport_output_FileExportTrigger_p;
#endif // Class_FileExport_output_FileExportTrigger_extended

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_FileExport_output_FileExportTrigger_Default.h"

#endif // Class_FileExport_output_FileExportTrigger_def