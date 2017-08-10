/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// OutputPin_Skeleton_output_Average.h
// This file implements the IStore interface for REST access.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef OutputPin_Skeleton_output_Average_def
#define OutputPin_Skeleton_output_Average_def

#include "stubs/OutputPin_Stub_Skeleton_output_Average.h"

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

// if you want to extend the auto-generated class, enable the line below
//#define OutputPin_Skeleton_output_Average_extended

#ifdef OutputPin_Skeleton_output_Average_extended
/**
 * Skeleton_output_Average
 *
 * module: Skeleton Module
 * description: This is a completely senseless output pin providing the average color of the area in the bounding box.
 */
class OutputPin_Skeleton_output_Average : public OutputPin_Stub_Skeleton_output_Average {
public:
	OutputPin_Skeleton_output_Average(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<Class_Skeleton_output_Average> > > dataStore) :
		OutputPin_Stub_Skeleton_output_Average(dataStore) {};
	virtual ~OutputPin_Skeleton_output_Average() {}
};
#endif // OutputPin_Skeleton_output_Average_extended

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#include "stubs/OutputPin_Skeleton_output_Average_Default.h"

#endif // OutputPin_Skeleton_output_Average_def