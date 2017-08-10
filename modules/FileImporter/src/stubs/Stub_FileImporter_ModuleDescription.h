// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_FileImporter_ModuleDescription.h
// NEVER TOUCH this file!

#ifndef Stub_FileImporter_ModuleDescription_def
#define Stub_FileImporter_ModuleDescription_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace FileImporter {

/// module description
// --> Do NOT EDIT <--
static const char _moduleDescription[] =
	"{\n"
	"	\"name\": \"FileImporter\",\n"
	"	\"description\": \"sends a static file\",\n"
	"	\"version\": 0.1,\n"
	"	\"moduleID\": \"FileImporter\",\n"
	"	\"moduleURI\": \"http://localhost:2020/FileImporter/\",\n"
	"	\"moduleLogoURI\": \"FileImporter.png\",\n"
	"	\"author\": \"Stephan Veigl\",\n"
	"	\"params\": {\n"
	"		\"type\": \"object\",\n"
	"		\"properties\": {\n"
	"			\"filename\": {\n"
	"				\"description\": \"network path to file\",\n"
	"				\"type\": \"string\",\n"
	"				\"exttype\": \"filepath\",\n"
	"				\"unit\": \"\"\n"
	"			},\n"
	"			\"mimeType\": {\n"
	"				\"description\": \"mime type of file\",\n"
	"				\"unit\": \"mime type\",\n"
	"				\"type\": \"string\"\n"
	"			}\n"
	"		}\n"
	"	}\n"
	"}";

/// input description
// --> Do NOT EDIT <--
static const char _inputPinDescription[] =
	"[]";

/// output description
// --> Do NOT EDIT <--
static const char _outputPinDescription[] =
	"[\n"
	"	{\n"
	"		\"name\": \"File Output\",\n"
	"		\"id\": \"FileOutput\",\n"
	"		\"description\": \"static file\",\n"
	"		\"static\": true,\n"
	"		\"type\": \"application\",\n"
	"		\"properties\": {}\n"
	"	}\n"
	"]";

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_FileImporter_ModuleDescription_def