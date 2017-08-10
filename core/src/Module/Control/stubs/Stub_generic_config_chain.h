/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_chain.h
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
#include "../Class_generic_config_chain_connections.h"

#ifndef Stub_generic_config_chain_def
#define Stub_generic_config_chain_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_config_chain
 * 
 * module: 
 * description: 
 */
class Stub_generic_config_chain {

public:
	Stub_generic_config_chain();
	Stub_generic_config_chain(const Stub_generic_config_chain& other);
	Stub_generic_config_chain(const rapidjson::Value& value);
	Stub_generic_config_chain(const std::string& str);
	virtual ~Stub_generic_config_chain();
	Stub_generic_config_chain &operator =(const Stub_generic_config_chain& other);
	Stub_generic_config_chain &operator =(Stub_generic_config_chain&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* connections - connection between input pin of consumer module and output pin of producer module */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> get_connections() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> getconst_connections() const;
	virtual void set_connections(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> value);
	virtual void set_connections(const std::vector<boost::shared_ptr<Class_generic_config_chain_connections>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>>(value); set_connections(ptr); };
	// array functions
	virtual boost::shared_ptr<Class_generic_config_chain_connections> get_connections(int index) const;
	virtual const boost::shared_ptr<Class_generic_config_chain_connections>& getconst_connections(int index) const;
	virtual void add_connections(boost::shared_ptr<Class_generic_config_chain_connections> value);
	virtual void add_connections(const Class_generic_config_chain_connections &value) { boost::shared_ptr<Class_generic_config_chain_connections> ptr = boost::make_shared<Class_generic_config_chain_connections>(value); add_connections(ptr); };

	/* config - config of sub module */
	virtual boost::shared_ptr<std::string> get_config() const;
	virtual const boost::shared_ptr<const std::string> getconst_config() const;
	virtual void set_config(boost::shared_ptr<std::string> value);
	virtual void set_config(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_config(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** connection between input pin of consumer module and output pin of producer module */
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> connections;
	
	/** config of sub module */
	boost::shared_ptr<std::string> config;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_config_chain_def