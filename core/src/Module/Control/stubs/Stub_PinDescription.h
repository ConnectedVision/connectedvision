/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_PinDescription.h
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
#include "../Class_PinDescription_properties.h"

#ifndef Stub_PinDescription_def
#define Stub_PinDescription_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_PinDescription
 * 
 * module: 
 * description: 
 */
class Stub_PinDescription {

public:
	Stub_PinDescription();
	Stub_PinDescription(const Stub_PinDescription& other);
	Stub_PinDescription(const rapidjson::Value& value);
	Stub_PinDescription(const std::string& str);
	virtual ~Stub_PinDescription();
	Stub_PinDescription &operator =(const Stub_PinDescription& other);
	Stub_PinDescription &operator =(Stub_PinDescription&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* name - name of pin */
	virtual boost::shared_ptr<std::string> get_name() const;
	virtual const boost::shared_ptr<const std::string> getconst_name() const;
	virtual void set_name(boost::shared_ptr<std::string> value);
	virtual void set_name(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_name(ptr); };

	/* id - unique ID of pin (can be an number, name or uid) important: has to be URL friendly! */
	virtual boost::shared_ptr<std::string> get_id() const;
	virtual const boost::shared_ptr<const std::string> getconst_id() const;
	virtual void set_id(boost::shared_ptr<std::string> value);
	virtual void set_id(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_id(ptr); };

	/* description - long description of pin */
	virtual boost::shared_ptr<std::string> get_description() const;
	virtual const boost::shared_ptr<const std::string> getconst_description() const;
	virtual void set_description(boost::shared_ptr<std::string> value);
	virtual void set_description(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_description(ptr); };

	/* type - MIME type of pin */
	virtual boost::shared_ptr<std::string> get_type() const;
	virtual const boost::shared_ptr<const std::string> getconst_type() const;
	virtual void set_type(boost::shared_ptr<std::string> value);
	virtual void set_type(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_type(ptr); };

	/* minPinCount - minimal number of this type of pin (set to 0 for optional input pin) */
	virtual int64_t get_minPinCount() const;
	virtual const int64_t getconst_minPinCount() const;
	virtual void set_minPinCount(int64_t value);

	/* maxPinCount - maximal number of this type of pin (use this if you want multiple input pins of the same type) */
	virtual int64_t get_maxPinCount() const;
	virtual const int64_t getconst_maxPinCount() const;
	virtual void set_maxPinCount(int64_t value);

	/* properties - JSON schema of data returned by pin (if MIME is application/json) */
	virtual boost::shared_ptr<Class_PinDescription_properties> get_properties() const;
	virtual const boost::shared_ptr<const Class_PinDescription_properties> getconst_properties() const;
	virtual void set_properties(boost::shared_ptr<Class_PinDescription_properties> value);
	virtual void set_properties(const Class_PinDescription_properties &value) { boost::shared_ptr<Class_PinDescription_properties> ptr = boost::make_shared<Class_PinDescription_properties>(value); set_properties(ptr); };
	virtual void set_properties(const rapidjson::Value& value) { properties->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** name of pin */
	boost::shared_ptr<std::string> name;
	
	/** unique ID of pin (can be an number, name or uid) important: has to be URL friendly! */
	boost::shared_ptr<std::string> id;
	
	/** long description of pin */
	boost::shared_ptr<std::string> description;
	
	/** MIME type of pin */
	boost::shared_ptr<std::string> type;
	
	/** minimal number of this type of pin (set to 0 for optional input pin) */
	int64_t minPinCount;
	
	/** maximal number of this type of pin (use this if you want multiple input pins of the same type) */
	int64_t maxPinCount;
	
	/** JSON schema of data returned by pin (if MIME is application/json) */
	boost::shared_ptr<Class_PinDescription_properties> properties;
	
};

} // namespace ConnectedVision

#endif // Stub_PinDescription_def