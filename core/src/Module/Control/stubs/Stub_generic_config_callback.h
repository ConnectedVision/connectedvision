/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_callback.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_generic_config_callback_def
#define Stub_generic_config_callback_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_config_callback
 * 
 * module: 
 * description: register a callback for live mode
 */
class Stub_generic_config_callback {

public:
	Stub_generic_config_callback();
	Stub_generic_config_callback(const Stub_generic_config_callback& other);
	Stub_generic_config_callback(const rapidjson::Value& value);
	Stub_generic_config_callback(const std::string& str);
	virtual ~Stub_generic_config_callback();
	Stub_generic_config_callback &operator =(const Stub_generic_config_callback& other);
	Stub_generic_config_callback &operator =(Stub_generic_config_callback&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* moduleID -  */
	virtual ConnectedVision::id_t get_moduleID() const;
	virtual const ConnectedVision::id_t getconst_moduleID() const;
	virtual void set_moduleID(ConnectedVision::id_t value);

	/* moduleURI - URI of module instance */
	virtual boost::shared_ptr<std::string> get_moduleURI() const;
	virtual const boost::shared_ptr<const std::string> getconst_moduleURI() const;
	virtual void set_moduleURI(boost::shared_ptr<std::string> value);
	virtual void set_moduleURI(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_moduleURI(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	ConnectedVision::id_t moduleID;
	
	/** URI of module instance */
	boost::shared_ptr<std::string> moduleURI;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_config_callback_def