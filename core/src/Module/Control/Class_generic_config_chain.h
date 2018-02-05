/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_generic_config_chain_def
#define Class_generic_config_chain_def

#include "stubs/Stub_generic_config_chain.h"

namespace ConnectedVision
{

// if you want to extend the auto-generated class, enable the line below
#define Class_generic_config_chain_extended

#ifdef Class_generic_config_chain_extended
/**
 * Class_generic_config_chain
 * 
 * module: 
 * description: 
 */
class Class_generic_config_chain : public Stub_generic_config_chain {

public:
	Class_generic_config_chain() {};
	Class_generic_config_chain(const ::rapidjson::Value& value) : Stub_generic_config_chain(value) {};
	Class_generic_config_chain(const std::string& str) : Stub_generic_config_chain(str) {};
	virtual ~Class_generic_config_chain() {};

 // TODO --> Your declarations and code comes HERE! <--
	pinID_t getCorrespondingOutputPinID(const pinID_t& pinID ) const;
	boost::shared_ptr<Class_generic_config_chain> getConfigConnectionByInputPin( const pinID_t& pinID ) const;

};
typedef boost::shared_ptr<Class_generic_config_chain> Class_generic_config_chain_p;
#endif // Class_generic_config_chain_extended

} // namespace ConnectedVision

#include "stubs/Class_generic_config_chain_Default.h"

#endif // Class_generic_config_chain_def