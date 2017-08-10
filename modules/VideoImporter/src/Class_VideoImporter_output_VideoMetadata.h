/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_VideoImporter_output_VideoMetadata.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_VideoImporter_output_VideoMetadata_def
#define Class_VideoImporter_output_VideoMetadata_def

#include "stubs/Stub_VideoImporter_output_VideoMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

// if you want to extend the auto-generated class, enable the line below
//#define Class_VideoImporter_output_VideoMetadata_extended

#ifdef Class_VideoImporter_output_VideoMetadata_extended
/**
 * Class_VideoImporter_output_VideoMetadata
 * 
 * module: VideoImporter
 * description: video meta data
 */
class Class_VideoImporter_output_VideoMetadata : public Stub_VideoImporter_output_VideoMetadata {

public:
	Class_VideoImporter_output_VideoMetadata() {};
	Class_VideoImporter_output_VideoMetadata(const ::rapidjson::Value& value) : Stub_VideoImporter_output_VideoMetadata(value) {};
	Class_VideoImporter_output_VideoMetadata(const std::string& str) : Stub_VideoImporter_output_VideoMetadata(str) {};
	virtual ~Class_VideoImporter_output_VideoMetadata() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_VideoImporter_output_VideoMetadata> Class_VideoImporter_output_VideoMetadata_p;
#endif // Class_VideoImporter_output_VideoMetadata_extended

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_VideoImporter_output_VideoMetadata_Default.h"

#endif // Class_VideoImporter_output_VideoMetadata_def