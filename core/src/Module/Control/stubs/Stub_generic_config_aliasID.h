/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_aliasID.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_generic_config_aliasID_def
#define Stub_generic_config_aliasID_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_config_aliasID
 * 
 * module: 
 * description: 
 */
class Stub_generic_config_aliasID {

public:
	Stub_generic_config_aliasID();
	Stub_generic_config_aliasID(const Stub_generic_config_aliasID& other);
	Stub_generic_config_aliasID(const rapidjson::Value& value);
	Stub_generic_config_aliasID(const std::string& str);
	virtual ~Stub_generic_config_aliasID();
	Stub_generic_config_aliasID &operator =(const Stub_generic_config_aliasID& other);
	Stub_generic_config_aliasID &operator =(Stub_generic_config_aliasID&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - an aliasID to be assigned to this config */
	virtual boost::shared_ptr<std::string> get_id() const;
	virtual const boost::shared_ptr<const std::string> getconst_id() const;
	virtual void set_id(boost::shared_ptr<std::string> value);
	virtual void set_id(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_id(ptr); };

	/* timestamp - creation timestamp of aliasID for this config */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** an aliasID to be assigned to this config */
	boost::shared_ptr<std::string> id;
	
	/** creation timestamp of aliasID for this config */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_config_aliasID_def