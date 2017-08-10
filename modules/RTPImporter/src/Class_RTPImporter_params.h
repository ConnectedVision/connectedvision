/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_RTPImporter_params.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_RTPImporter_params_def
#define Class_RTPImporter_params_def

#include "stubs/Stub_RTPImporter_params.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

// if you want to extend the auto-generated class, enable the line below
//#define Class_RTPImporter_params_extended

#ifdef Class_RTPImporter_params_extended
/**
 * Class_RTPImporter_params
 * 
 * module: RTP stream receiver module
 * description: RTP Receiver parameters
 */
class Class_RTPImporter_params : public Stub_RTPImporter_params {

public:
	Class_RTPImporter_params() {};
	Class_RTPImporter_params(const ::rapidjson::Value& value) : Stub_RTPImporter_params(value) {};
	Class_RTPImporter_params(const std::string& str) : Stub_RTPImporter_params(str) {};
	virtual ~Class_RTPImporter_params() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_RTPImporter_params> Class_RTPImporter_params_p;
#endif // Class_RTPImporter_params_extended

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#include "stubs/Class_RTPImporter_params_Default.h"

#endif // Class_RTPImporter_params_def