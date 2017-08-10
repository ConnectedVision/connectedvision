/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription_params_properties.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ModuleDescription_params_properties_def
#define Stub_ModuleDescription_params_properties_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_ModuleDescription_params_properties
 * 
 * module: 
 * description: algorithmic specific configuration parameters. This is part of the config chain.
 */
class Stub_ModuleDescription_params_properties {

public:
	Stub_ModuleDescription_params_properties();
	Stub_ModuleDescription_params_properties(const Stub_ModuleDescription_params_properties& other);
	Stub_ModuleDescription_params_properties(const rapidjson::Value& value);
	Stub_ModuleDescription_params_properties(const std::string& str);
	virtual ~Stub_ModuleDescription_params_properties();
	Stub_ModuleDescription_params_properties &operator =(const Stub_ModuleDescription_params_properties& other);
	Stub_ModuleDescription_params_properties &operator =(Stub_ModuleDescription_params_properties&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:

protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

};

} // namespace ConnectedVision

#endif // Stub_ModuleDescription_params_properties_def