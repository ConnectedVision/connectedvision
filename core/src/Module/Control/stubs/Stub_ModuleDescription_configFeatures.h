/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription_configFeatures.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ModuleDescription_configFeatures_def
#define Stub_ModuleDescription_configFeatures_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_ModuleDescription_configFeatures
 * 
 * module: 
 * description: JSON schema of features of the config
 */
class Stub_ModuleDescription_configFeatures {

public:
	Stub_ModuleDescription_configFeatures();
	Stub_ModuleDescription_configFeatures(const Stub_ModuleDescription_configFeatures& other);
	Stub_ModuleDescription_configFeatures(const rapidjson::Value& value);
	Stub_ModuleDescription_configFeatures(const std::string& str);
	virtual ~Stub_ModuleDescription_configFeatures();
	Stub_ModuleDescription_configFeatures &operator =(const Stub_ModuleDescription_configFeatures& other);
	Stub_ModuleDescription_configFeatures &operator =(Stub_ModuleDescription_configFeatures&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* allowDynamicParameters - the config does support dynamic parameters */
	virtual bool get_allowDynamicParameters() const;
	virtual const bool getconst_allowDynamicParameters() const;
	virtual void set_allowDynamicParameters(bool value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** the config does support dynamic parameters */
	bool allowDynamicParameters;
	
};

} // namespace ConnectedVision

#endif // Stub_ModuleDescription_configFeatures_def