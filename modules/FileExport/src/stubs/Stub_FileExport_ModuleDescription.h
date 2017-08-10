// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_FileExport_ModuleDescription.h
// NEVER TOUCH this file!

#ifndef Stub_FileExport_ModuleDescription_def
#define Stub_FileExport_ModuleDescription_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace FileExport {

/// module description
// --> Do NOT EDIT <--
static const char _moduleDescription[] =
	"{\n"
	"	\"name\": \"FileExport\",\n"
	"	\"description\": \"exports data to file(s)\",\n"
	"	\"version\": 1.01,\n"
	"	\"moduleID\": \"FileExport\",\n"
	"	\"moduleURI\": \"http://localhost:2020/FileExport/\",\n"
	"	\"moduleLogoURI\": \"FileExport.png\",\n"
	"	\"moduleFeatures\": {\n"
	"		\"supportsLive\": true,\n"
	"		\"supportsResume\": false,\n"
	"		\"supportsDynamicParameters\": false\n"
	"	},\n"
	"	\"author\": \"Connected Vision\",\n"
	"	\"params\": {\n"
	"		\"type\": \"object\",\n"
	"		\"properties\": {\n"
	"			\"filepath_format\": {\n"
	"				\"description\": \"specification of filepath (path + filename) of target output file, there are several reserved character sequences defined to allow folders and filenames to change over time and have identifiers in them, these special reserved character sequences are:[timestamp],[index],[identifier],etc.\",\n"
	"				\"type\": \"string\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"\"\n"
	"			}\n"
	"		}\n"
	"	}\n"
	"}";

/// input description
// --> Do NOT EDIT <--
static const char _inputPinDescription[] =
	"[\n"
	"	{\n"
	"		\"name\": \"data\",\n"
	"		\"description\": \"data elements to be exported into file(s)\",\n"
	"		\"id\": \"data\",\n"
	"		\"static\": false,\n"
	"		\"type\": \"*\",\n"
	"		\"properties\": {}\n"
	"	}\n"
	"]";

/// output description
// --> Do NOT EDIT <--
static const char _outputPinDescription[] =
	"[\n"
	"	{\n"
	"		\"name\": \"FileExportTrigger\",\n"
	"		\"id\": \"FileExportTrigger\",\n"
	"		\"description\": \"output pin used as trigger for file export of data elements available at the input pin with matching timestamp or id\",\n"
	"		\"static\": true,\n"
	"		\"type\": \"application/json\",\n"
	"		\"properties\": {\n"
	"			\"timestamp\": {\n"
	"				\"description\": \"timestamp of data element triggered for file export\",\n"
	"				\"required\": true,\n"
	"				\"type\": \"integer\",\n"
	"				\"exttype\": \"timestamp\",\n"
	"				\"unit\": \"ms\"\n"
	"			}\n"
	"		}\n"
	"	}\n"
	"]";

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_FileExport_ModuleDescription_def