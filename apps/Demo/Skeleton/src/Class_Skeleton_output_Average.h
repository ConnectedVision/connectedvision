/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_Skeleton_output_Average.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_Skeleton_output_Average_def
#define Class_Skeleton_output_Average_def

#include "stubs/Stub_Skeleton_output_Average.h"

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

// if you want to extend the auto-generated class, enable the line below
//#define Class_Skeleton_output_Average_extended

#ifdef Class_Skeleton_output_Average_extended
/**
 * Class_Skeleton_output_Average
 * 
 * module: Skeleton Module
 * description: This is a completely senseless output pin providing the average color of the area in the bounding box.
 */
class Class_Skeleton_output_Average : public Stub_Skeleton_output_Average {

public:
	Class_Skeleton_output_Average() {};
	Class_Skeleton_output_Average(const ::rapidjson::Value& value) : Stub_Skeleton_output_Average(value) {};
	Class_Skeleton_output_Average(const std::string& str) : Stub_Skeleton_output_Average(str) {};
	virtual ~Class_Skeleton_output_Average() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_Skeleton_output_Average> Class_Skeleton_output_Average_p;
#endif // Class_Skeleton_output_Average_extended

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_Skeleton_output_Average_Default.h"

#endif // Class_Skeleton_output_Average_def