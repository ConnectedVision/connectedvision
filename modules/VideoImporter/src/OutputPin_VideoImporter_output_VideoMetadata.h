/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// OutputPin_VideoImporter_output_VideoMetadata.h
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef OutputPin_VideoImporter_output_VideoMetadata_def
#define OutputPin_VideoImporter_output_VideoMetadata_def

#include "stubs/OutputPin_Stub_VideoImporter_output_VideoMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

// if you want to extend the auto-generated class, enable the line below
//#define OutputPin_VideoImporter_output_VideoMetadata_extended

#ifdef OutputPin_VideoImporter_output_VideoMetadata_extended
/**
 * VideoImporter_output_VideoMetadata
 *
 * module: VideoImporter
 * description: video meta data
 */
class OutputPin_VideoImporter_output_VideoMetadata : public OutputPin_Stub_VideoImporter_output_VideoMetadata {
public:
	OutputPin_VideoImporter_output_VideoMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_VideoImporter_output_VideoMetadata> > > dataStore) :
		OutputPin_Stub_VideoImporter_output_VideoMetadata(dataStore) {};
	virtual ~OutputPin_VideoImporter_output_VideoMetadata() {}
};
#endif // OutputPin_VideoImporter_output_VideoMetadata_extended

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/OutputPin_VideoImporter_output_VideoMetadata_Default.h"

#endif // OutputPin_VideoImporter_output_VideoMetadata_def