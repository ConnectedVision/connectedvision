/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


// include child classes
#include "../Class_ModuleDescription_params_properties.h"

#ifndef Stub_ModuleDescription_params_def
#define Stub_ModuleDescription_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_ModuleDescription_params
 * 
 * module: 
 * description: JSON schema of parameters
 */
class Stub_ModuleDescription_params {

public:
	Stub_ModuleDescription_params();
	Stub_ModuleDescription_params(const Stub_ModuleDescription_params& other);
	Stub_ModuleDescription_params(const rapidjson::Value& value);
	Stub_ModuleDescription_params(const std::string& str);
	virtual ~Stub_ModuleDescription_params();
	Stub_ModuleDescription_params &operator =(const Stub_ModuleDescription_params& other);
	Stub_ModuleDescription_params &operator =(Stub_ModuleDescription_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* type -  */
	virtual boost::shared_ptr<std::string> get_type() const;
	virtual const boost::shared_ptr<const std::string> getconst_type() const;
	virtual void set_type(boost::shared_ptr<std::string> value);
	virtual void set_type(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_type(ptr); };
	// enum functions
	virtual bool is_type(const boost::shared_ptr<std::string>& value) const;
	const static boost::shared_ptr<std::string> type_object;
	virtual bool is_type_object() const { return is_type( Stub_ModuleDescription_params::type_object ); }
	virtual void set_type_object() { set_type ( Stub_ModuleDescription_params::type_object ); }

	/* properties - algorithmic specific configuration parameters. This is part of the config chain. */
	virtual boost::shared_ptr<Class_ModuleDescription_params_properties> get_properties() const;
	virtual const boost::shared_ptr<const Class_ModuleDescription_params_properties> getconst_properties() const;
	virtual void set_properties(boost::shared_ptr<Class_ModuleDescription_params_properties> value);
	virtual void set_properties(const Class_ModuleDescription_params_properties &value) { boost::shared_ptr<Class_ModuleDescription_params_properties> ptr = boost::make_shared<Class_ModuleDescription_params_properties>(value); set_properties(ptr); };
	virtual void set_properties(const rapidjson::Value& value) { properties->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	boost::shared_ptr<std::string> type;
	
	/** algorithmic specific configuration parameters. This is part of the config chain. */
	boost::shared_ptr<Class_ModuleDescription_params_properties> properties;
	
};

} // namespace ConnectedVision

#endif // Stub_ModuleDescription_params_def