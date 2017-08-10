/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_chain_connections.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_generic_config_chain_connections_def
#define Stub_generic_config_chain_connections_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_config_chain_connections
 * 
 * module: 
 * description: 
 */
class Stub_generic_config_chain_connections {

public:
	Stub_generic_config_chain_connections();
	Stub_generic_config_chain_connections(const Stub_generic_config_chain_connections& other);
	Stub_generic_config_chain_connections(const rapidjson::Value& value);
	Stub_generic_config_chain_connections(const std::string& str);
	virtual ~Stub_generic_config_chain_connections();
	Stub_generic_config_chain_connections &operator =(const Stub_generic_config_chain_connections& other);
	Stub_generic_config_chain_connections &operator =(Stub_generic_config_chain_connections&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* inputPinID - id of input pin */
	virtual boost::shared_ptr<std::string> get_inputPinID() const;
	virtual const boost::shared_ptr<const std::string> getconst_inputPinID() const;
	virtual void set_inputPinID(boost::shared_ptr<std::string> value);
	virtual void set_inputPinID(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_inputPinID(ptr); };

	/* outputPinID - id of output pin */
	virtual boost::shared_ptr<std::string> get_outputPinID() const;
	virtual const boost::shared_ptr<const std::string> getconst_outputPinID() const;
	virtual void set_outputPinID(boost::shared_ptr<std::string> value);
	virtual void set_outputPinID(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_outputPinID(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** id of input pin */
	boost::shared_ptr<std::string> inputPinID;
	
	/** id of output pin */
	boost::shared_ptr<std::string> outputPinID;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_config_chain_connections_def