/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// OutputPin_DummyBoundingBoxes_output_Detections.h
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef OutputPin_DummyBoundingBoxes_output_Detections_def
#define OutputPin_DummyBoundingBoxes_output_Detections_def

#include "stubs/OutputPin_Stub_DummyBoundingBoxes_output_Detections.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

// if you want to extend the auto-generated class, enable the line below
//#define OutputPin_DummyBoundingBoxes_output_Detections_extended

#ifdef OutputPin_DummyBoundingBoxes_output_Detections_extended
/**
 * DummyBoundingBoxes_output_Detections
 *
 * module: DummyBoundingBoxes
 * description: bounding box
 */
class OutputPin_DummyBoundingBoxes_output_Detections : public OutputPin_Stub_DummyBoundingBoxes_output_Detections {
public:
	OutputPin_DummyBoundingBoxes_output_Detections(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections> > > dataStore) :
		OutputPin_Stub_DummyBoundingBoxes_output_Detections(dataStore) {};
	virtual ~OutputPin_DummyBoundingBoxes_output_Detections() {}
};
#endif // OutputPin_DummyBoundingBoxes_output_Detections_extended

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#include "stubs/OutputPin_DummyBoundingBoxes_output_Detections_Default.h"

#endif // OutputPin_DummyBoundingBoxes_output_Detections_def