// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DirectoryIterator_ModuleDescription.h
// NEVER TOUCH this file!

#ifndef Stub_DirectoryIterator_ModuleDescription_def
#define Stub_DirectoryIterator_ModuleDescription_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/// module description
// --> Do NOT EDIT <--
static const char _moduleDescription[] =
	"{\n"
	"	\"name\": \"Directory Iterator\",\n"
	"	\"description\": \"Iterates a directory and returns the files with the extensions specified in the config.\",\n"
	"	\"version\": 1,\n"
	"	\"moduleID\": \"DirectoryIterator\",\n"
	"	\"moduleURI\": \"http://localhost:2020/DirectoryIterator\",\n"
	"	\"author\": \"Connected Vision\",\n"
	"	\"params\": {\n"
	"		\"type\": \"object\",\n"
	"		\"properties\": {\n"
	"			\"rootDirectory\": {\n"
	"				\"description\": \"root directory\",\n"
	"				\"type\": \"string\",\n"
	"				\"required\": false,\n"
	"				\"default\": \".\"\n"
	"			},\n"
	"			\"fileTypes\": {\n"
	"				\"description\": \"file types to process\",\n"
	"				\"type\": \"array\",\n"
	"				\"required\": false,\n"
	"				\"default\": [],\n"
	"				\"items\": {\n"
	"					\"type\": \"string\",\n"
	"					\"required\": false,\n"
	"					\"default\": \"\"\n"
	"				}\n"
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
	"		\"name\": \"File Metadata\",\n"
	"		\"id\": \"FileMetadata\",\n"
	"		\"description\": \"The file metadata.\",\n"
	"		\"static\": false,\n"
	"		\"type\": \"application/json\",\n"
	"		\"properties\": {\n"
	"			\"id\": {\n"
	"				\"description\": \"file ID\",\n"
	"				\"type\": \"string\",\n"
	"				\"exttype\": \"id\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"md5\"\n"
	"			},\n"
	"			\"configID\": {\n"
	"				\"description\": \"job / config ID\",\n"
	"				\"type\": \"string\",\n"
	"				\"exttype\": \"id\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"md5\"\n"
	"			},\n"
	"			\"timestamp\": {\n"
	"				\"description\": \"timestamp\",\n"
	"				\"type\": \"integer\",\n"
	"				\"exttype\": \"timestamp\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"time in ms since 1.1.1970\"\n"
	"			},\n"
	"			\"filePath\": {\n"
	"				\"description\": \"absolute file path\",\n"
	"				\"type\": \"string\",\n"
	"				\"required\": true\n"
	"			}\n"
	"		}\n"
	"	},\n"
	"	{\n"
	"		\"name\": \"Binary Data\",\n"
	"		\"id\": \"BinaryData\",\n"
	"		\"description\": \"binary data\",\n"
	"		\"static\": false,\n"
	"		\"type\": \"application/binary\",\n"
	"		\"properties\": {}\n"
	"	}\n"
	"]";

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DirectoryIterator_ModuleDescription_def