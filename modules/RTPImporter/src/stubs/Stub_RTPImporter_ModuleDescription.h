// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_RTPImporter_ModuleDescription.h
// NEVER TOUCH this file!

#ifndef Stub_RTPImporter_ModuleDescription_def
#define Stub_RTPImporter_ModuleDescription_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

/// module description
// --> Do NOT EDIT <--
static const char _moduleDescription[] =
	"{\n"
	"	\"name\": \"RTP stream receiver module\",\n"
	"	\"description\": \"\",\n"
	"	\"version\": 0.1,\n"
	"	\"moduleID\": \"RTPImporter\",\n"
	"	\"moduleURI\": \"http://localhost:2020/RTPImporter\",\n"
	"	\"moduleFeatures\": {\n"
	"		\"supportsLive\": true,\n"
	"		\"supportsResume\": false,\n"
	"		\"supportsDynamicParameters\": false\n"
	"	},\n"
	"	\"author\": \"Connected Vision\",\n"
	"	\"params\": {\n"
	"		\"description\": \"RTP Receiver parameters\",\n"
	"		\"required\": true,\n"
	"		\"type\": \"object\",\n"
	"		\"properties\": {\n"
	"			\"url\": {\n"
	"				\"description\": \"RTP multicast/unicast address (URL)\",\n"
	"				\"required\": true,\n"
	"				\"type\": \"string\"\n"
	"			},\n"
	"			\"preferTcp\": {\n"
	"				\"description\": \"Prefer TCP over UDP for the transmission of the video stream. Sets the FFmpeg::avformat_open_input([...] rtsp_flags::prefer_tcp [...]) to 1. This helped at least in one case where tearing/smearing artifacts repeatedly started to appear in the lower half of the frames with increasing artifact strength. They abruptly disappeared after some time, but not exactly at the I-frame positions in order to repeat the process some time later. Simply changing the camera stream configuration parameters such as codec (H.264, H.265), resolution, frame rate, I-/key-frame distance/interval, bitrate, etc. did not have an influence on the effect.\",\n"
	"				\"type\": \"boolean\",\n"
	"				\"required\": false,\n"
	"				\"default\": false\n"
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
	"		\"name\": \"Received image as PNG.\",\n"
	"		\"id\": \"PNG-Image\",\n"
	"		\"description\": \"Decoded image as PNG byte stream.\",\n"
	"		\"static\": false,\n"
	"		\"type\": \"image/png\",\n"
	"		\"properties\": {}\n"
	"	},\n"
	"	{\n"
	"		\"name\": \"Frame Metadata\",\n"
	"		\"id\": \"FrameMetadata\",\n"
	"		\"description\": \"frame meta data\",\n"
	"		\"static\": false,\n"
	"		\"type\": \"application/json\",\n"
	"		\"properties\": {\n"
	"			\"id\": {\n"
	"				\"description\": \"Object ID\",\n"
	"				\"type\": \"string\",\n"
	"				\"exttype\": \"id\",\n"
	"				\"unit\": \"md5\"\n"
	"			},\n"
	"			\"configID\": {\n"
	"				\"description\": \"job / config ID\",\n"
	"				\"type\": \"string\",\n"
	"				\"exttype\": \"id\",\n"
	"				\"unit\": \"md5\"\n"
	"			},\n"
	"			\"timestamp\": {\n"
	"				\"description\": \"frame time\",\n"
	"				\"type\": \"integer\",\n"
	"				\"exttype\": \"timestamp\",\n"
	"				\"unit\": \"ms\"\n"
	"			},\n"
	"			\"framenumber\": {\n"
	"				\"description\": \"frame number\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"\",\n"
	"				\"type\": \"integer\"\n"
	"			},\n"
	"			\"width\": {\n"
	"				\"description\": \"width of frame in pixels\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"pixel\",\n"
	"				\"type\": \"integer\"\n"
	"			},\n"
	"			\"height\": {\n"
	"				\"description\": \"height of frame in pixels\",\n"
	"				\"required\": true,\n"
	"				\"unit\": \"pixel\",\n"
	"				\"type\": \"integer\"\n"
	"			},\n"
	"			\"framediff\": {\n"
	"				\"description\": \"difference between current framenumber and last (reflects dropped frames)\",\n"
	"				\"required\": false,\n"
	"				\"unit\": \"\",\n"
	"				\"type\": \"integer\"\n"
	"			},\n"
	"			\"encerrors\": {\n"
	"				\"description\": \"number of encoder errors\",\n"
	"				\"required\": false,\n"
	"				\"unit\": \"\",\n"
	"				\"type\": \"integer\"\n"
	"			}\n"
	"		}\n"
	"	}\n"
	"]";

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_RTPImporter_ModuleDescription_def