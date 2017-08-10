/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// OutputPin_SyntheticVideo_output_FrameMetadata.h
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef OutputPin_SyntheticVideo_output_FrameMetadata_def
#define OutputPin_SyntheticVideo_output_FrameMetadata_def

#include "stubs/OutputPin_Stub_SyntheticVideo_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

// if you want to extend the auto-generated class, enable the line below
//#define OutputPin_SyntheticVideo_output_FrameMetadata_extended

#ifdef OutputPin_SyntheticVideo_output_FrameMetadata_extended
/**
 * SyntheticVideo_output_FrameMetadata
 *
 * module: SyntheticVideo
 * description: synthetic frame meta data
 */
class OutputPin_SyntheticVideo_output_FrameMetadata : public OutputPin_Stub_SyntheticVideo_output_FrameMetadata {
public:
	OutputPin_SyntheticVideo_output_FrameMetadata(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_SyntheticVideo_output_FrameMetadata> > > dataStore) :
		OutputPin_Stub_SyntheticVideo_output_FrameMetadata(dataStore) {};
	virtual ~OutputPin_SyntheticVideo_output_FrameMetadata() {}
};
#endif // OutputPin_SyntheticVideo_output_FrameMetadata_extended

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#include "stubs/OutputPin_SyntheticVideo_output_FrameMetadata_Default.h"

#endif // OutputPin_SyntheticVideo_output_FrameMetadata_def