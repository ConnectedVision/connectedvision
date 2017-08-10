/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config.h
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
#include "../Class_generic_config_aliasID.h"
#include "../Class_generic_config_configFeatures.h"
#include "../Class_generic_config_callback.h"
#include "../Class_generic_config_chain.h"

#ifndef Stub_generic_config_def
#define Stub_generic_config_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_config
 * 
 * module: 
 * description: config chain
 */
class Stub_generic_config {

public:
	Stub_generic_config();
	Stub_generic_config(const Stub_generic_config& other);
	Stub_generic_config(const rapidjson::Value& value);
	Stub_generic_config(const std::string& str);
	virtual ~Stub_generic_config();
	Stub_generic_config &operator =(const Stub_generic_config& other);
	Stub_generic_config &operator =(Stub_generic_config&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - config ID */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* timestamp - time of modification */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* name - config name */
	virtual boost::shared_ptr<std::string> get_name() const;
	virtual const boost::shared_ptr<const std::string> getconst_name() const;
	virtual void set_name(boost::shared_ptr<std::string> value);
	virtual void set_name(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_name(ptr); };

	/* description - config description */
	virtual boost::shared_ptr<std::string> get_description() const;
	virtual const boost::shared_ptr<const std::string> getconst_description() const;
	virtual void set_description(boost::shared_ptr<std::string> value);
	virtual void set_description(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_description(ptr); };

	/* aliasID - a list of (new) aliasIDs to be assigned to this config */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> get_aliasID() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> getconst_aliasID() const;
	virtual void set_aliasID(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> value);
	virtual void set_aliasID(const std::vector<boost::shared_ptr<Class_generic_config_aliasID>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>>(value); set_aliasID(ptr); };
	// array functions
	virtual boost::shared_ptr<Class_generic_config_aliasID> get_aliasID(int index) const;
	virtual const boost::shared_ptr<Class_generic_config_aliasID>& getconst_aliasID(int index) const;
	virtual void add_aliasID(boost::shared_ptr<Class_generic_config_aliasID> value);
	virtual void add_aliasID(const Class_generic_config_aliasID &value) { boost::shared_ptr<Class_generic_config_aliasID> ptr = boost::make_shared<Class_generic_config_aliasID>(value); add_aliasID(ptr); };

	/* version - config version */
	virtual int64_t get_version() const;
	virtual const int64_t getconst_version() const;
	virtual void set_version(int64_t value);

	/* moduleID -  */
	virtual ConnectedVision::id_t get_moduleID() const;
	virtual const ConnectedVision::id_t getconst_moduleID() const;
	virtual void set_moduleID(ConnectedVision::id_t value);

	/* moduleURI - URI of module instance */
	virtual boost::shared_ptr<std::string> get_moduleURI() const;
	virtual const boost::shared_ptr<const std::string> getconst_moduleURI() const;
	virtual void set_moduleURI(boost::shared_ptr<std::string> value);
	virtual void set_moduleURI(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_moduleURI(ptr); };

	/* configFeatures - JSON schema of features of the config */
	virtual boost::shared_ptr<Class_generic_config_configFeatures> get_configFeatures() const;
	virtual const boost::shared_ptr<const Class_generic_config_configFeatures> getconst_configFeatures() const;
	virtual void set_configFeatures(boost::shared_ptr<Class_generic_config_configFeatures> value);
	virtual void set_configFeatures(const Class_generic_config_configFeatures &value) { boost::shared_ptr<Class_generic_config_configFeatures> ptr = boost::make_shared<Class_generic_config_configFeatures>(value); set_configFeatures(ptr); };
	virtual void set_configFeatures(const rapidjson::Value& value) { configFeatures->parseJson( value ); };

	/* callback - register a callback for live mode */
	virtual boost::shared_ptr<Class_generic_config_callback> get_callback() const;
	virtual const boost::shared_ptr<const Class_generic_config_callback> getconst_callback() const;
	virtual void set_callback(boost::shared_ptr<Class_generic_config_callback> value);
	virtual void set_callback(const Class_generic_config_callback &value) { boost::shared_ptr<Class_generic_config_callback> ptr = boost::make_shared<Class_generic_config_callback>(value); set_callback(ptr); };
	virtual void set_callback(const rapidjson::Value& value) { callback->parseJson( value ); };

	/* params -  */
	virtual boost::shared_ptr<std::string> get_params() const;
	virtual const boost::shared_ptr<const std::string> getconst_params() const;
	virtual void set_params(boost::shared_ptr<std::string> value);
	virtual void set_params(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_params(ptr); };

	/* initialParams -  */
	virtual boost::shared_ptr<std::string> get_initialParams() const;
	virtual const boost::shared_ptr<const std::string> getconst_initialParams() const;
	virtual void set_initialParams(boost::shared_ptr<std::string> value);
	virtual void set_initialParams(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_initialParams(ptr); };

	/* chain -  */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> get_chain() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_config_chain>>> getconst_chain() const;
	virtual void set_chain(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> value);
	virtual void set_chain(const std::vector<boost::shared_ptr<Class_generic_config_chain>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_config_chain>>>(value); set_chain(ptr); };
	// array functions
	virtual boost::shared_ptr<Class_generic_config_chain> get_chain(int index) const;
	virtual const boost::shared_ptr<Class_generic_config_chain>& getconst_chain(int index) const;
	virtual void add_chain(boost::shared_ptr<Class_generic_config_chain> value);
	virtual void add_chain(const Class_generic_config_chain &value) { boost::shared_ptr<Class_generic_config_chain> ptr = boost::make_shared<Class_generic_config_chain>(value); add_chain(ptr); };

	/* configID - virtual config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** config ID */
	ConnectedVision::id_t id;
	
	/** time of modification */
	ConnectedVision::timestamp_t timestamp;
	
	/** config name */
	boost::shared_ptr<std::string> name;
	
	/** config description */
	boost::shared_ptr<std::string> description;
	
	/** a list of (new) aliasIDs to be assigned to this config */
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> aliasID;
	
	/** config version */
	int64_t version;
	
	/**  */
	ConnectedVision::id_t moduleID;
	
	/** URI of module instance */
	boost::shared_ptr<std::string> moduleURI;
	
	/** JSON schema of features of the config */
	boost::shared_ptr<Class_generic_config_configFeatures> configFeatures;
	
	/** register a callback for live mode */
	boost::shared_ptr<Class_generic_config_callback> callback;
	
	/**  */
	boost::shared_ptr<std::string> params;
	
	/**  */
	boost::shared_ptr<std::string> initialParams;
	
	/**  */
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> chain;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_config_def