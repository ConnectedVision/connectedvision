/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// 
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_generic_config_def
#define Class_generic_config_def

#include <IStore.h>
#include "stubs/Stub_generic_config.h"

namespace ConnectedVision
{

/**
 * Class_generic_config
 * 
 * module: 
 * description: config chain
 */
class Class_generic_config : public Stub_generic_config {

public:
	Class_generic_config();
	Class_generic_config(const rapidjson::Value& value);
	Class_generic_config(const std::string& str);
	virtual ~Class_generic_config() {};

	virtual std::string toJson() const;	
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };

	// overwrite compute_id
	virtual id_t compute_id();

	// set a dynamic parameter
	virtual void setDynamicParameter(std::string name, std::string value);

	inline ConnectedVision::shared_ptr<Class_generic_config> copy() const
	{
		ConnectedVision::shared_ptr<Class_generic_config> clone( new Class_generic_config( static_cast<const Class_generic_config &>(*this) ) );
		return clone;
	}

	// helper function
	virtual boost::shared_ptr<Class_generic_config_chain> getSubConfigConnectionByInputPin( const pinID_t& pinID ) const;

	// dummy configID getter / setter
	virtual const id_t getconst_configID() const { return ID_NULL; } // the generic config class does not use the configID
	virtual id_t get_configID() const { return ID_NULL; } // the generic config class does not use the configID
	virtual void set_configID(id_t configID) { /* do nothing */ }


	/**
	* preprocesses a config to remove c-like comments and replace occurencies of replacement references by their replacement defines (which are also removed)
	* syntax for comments:
	*   single line comments: "//"
	*     these can be extended to the next line with a backslash ("\") character
	*   multiple line comments: "/" followed by "*" character for opening and "*" followed by "/" character for closing comments
	* syntax for replacement defines and references
	*   replacement defines:
	*     single line replacement defines: "#define [replacementIdentifier] [replacementValue] - newline is closing the single line replacement define
	*     multiple line replacement defines: "#startdef [replacementIdentifier]" followed by a multi-line [replacementValue] and ended by "#enddef"
	*   replacement references:
	*     "$[replacementIdentifier]$
	*   note: recursive replacement defines are not allowed (e.g. "#define id1 #define id2 123)
	* @param config the augmented input config (augmented with comments and replacement defines and references)	
	* @return the processed config without comments and with resolved references (now a valid json config)
	*/
	static std::string removeCommentsAndResolveReferencesInConfig(const std::string &config);

};
typedef boost::shared_ptr<Class_generic_config> Class_generic_config_p;

} // namespace ConnectedVision

#endif // Class_generic_config_def
