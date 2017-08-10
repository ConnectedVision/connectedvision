/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef OutputPin_FramePNG_def
#define OutputPin_FramePNG_def

#include <Module/OutputPins/OutputPin_PNG.h>

#include "Class_RTPImporter_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

/**
* class OutputPin_ImagesMetadata
* provides a custom output pin class for the metadata of the collection of images
*/
class OutputPin_FramePNG : public ConnectedVision::OutputPins::OutputPin_PNG<Class_RTPImporter_output_FrameMetadata>
{
public:
	OutputPin_FramePNG(
		ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<Class_RTPImporter_output_FrameMetadata> > dataStoreManager	///< [in] store manager for frame data
	) : ConnectedVision::OutputPins::OutputPin_PNG<Class_RTPImporter_output_FrameMetadata>(dataStoreManager, &Class_RTPImporter_output_FrameMetadata::selectPNGImage) {}
	virtual ~OutputPin_FramePNG() {}

	static const pinID_t PinID() { return "PNG-Image"; }
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); }
};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_FramePNG_def
