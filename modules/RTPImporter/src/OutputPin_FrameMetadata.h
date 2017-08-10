/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef OutputPin_FrameMetadata_def
#define OutputPin_FrameMetadata_def

#include <Module/OutputPins/OutputPin_JSON.h>

#include "Class_RTPImporter_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

/**
* class OutputPin_ImagesMetadata
* provides a custom output pin class for the metadata of the collection of images
*/
class OutputPin_FrameMetadata : public ConnectedVision::OutputPins::OutputPin_JSON<Class_RTPImporter_output_FrameMetadata>
{
public:
	OutputPin_FrameMetadata(
		ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<Class_RTPImporter_output_FrameMetadata> > dataStoreManager	///< [in] store manager for frame data
	) : ConnectedVision::OutputPins::OutputPin_JSON<Class_RTPImporter_output_FrameMetadata>(dataStoreManager) {}
	virtual ~OutputPin_FrameMetadata() {}

	static const pinID_t PinID() { return "FrameMetadata"; }
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); }
};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_FrameMetadata_def