/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleStatus.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ModuleStatus_def
#define Stub_ModuleStatus_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_ModuleStatus
 * 
 * module: 
 * description: Module Status Schema
 */
class Stub_ModuleStatus {

public:
	Stub_ModuleStatus();
	Stub_ModuleStatus(const Stub_ModuleStatus& other);
	Stub_ModuleStatus(const rapidjson::Value& value);
	Stub_ModuleStatus(const std::string& str);
	virtual ~Stub_ModuleStatus();
	Stub_ModuleStatus &operator =(const Stub_ModuleStatus& other);
	Stub_ModuleStatus &operator =(Stub_ModuleStatus&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* name - module name */
	virtual boost::shared_ptr<std::string> get_name() const;
	virtual const boost::shared_ptr<const std::string> getconst_name() const;
	virtual void set_name(boost::shared_ptr<std::string> value);
	virtual void set_name(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_name(ptr); };

	/* moduleID - ID of module */
	virtual ConnectedVision::id_t get_moduleID() const;
	virtual const ConnectedVision::id_t getconst_moduleID() const;
	virtual void set_moduleID(ConnectedVision::id_t value);

	/* moduleStatus - current status of module */
	virtual boost::shared_ptr<std::string> get_moduleStatus() const;
	virtual const boost::shared_ptr<const std::string> getconst_moduleStatus() const;
	virtual void set_moduleStatus(boost::shared_ptr<std::string> value);
	virtual void set_moduleStatus(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_moduleStatus(ptr); };
	// enum functions
	virtual bool is_moduleStatus(const boost::shared_ptr<std::string>& value) const;
	const static boost::shared_ptr<std::string> moduleStatus_na;
	virtual bool is_moduleStatus_na() const { return is_moduleStatus( Stub_ModuleStatus::moduleStatus_na ); }
	virtual void set_moduleStatus_na() { set_moduleStatus ( Stub_ModuleStatus::moduleStatus_na ); }
	const static boost::shared_ptr<std::string> moduleStatus_up;
	virtual bool is_moduleStatus_up() const { return is_moduleStatus( Stub_ModuleStatus::moduleStatus_up ); }
	virtual void set_moduleStatus_up() { set_moduleStatus ( Stub_ModuleStatus::moduleStatus_up ); }
	const static boost::shared_ptr<std::string> moduleStatus_down;
	virtual bool is_moduleStatus_down() const { return is_moduleStatus( Stub_ModuleStatus::moduleStatus_down ); }
	virtual void set_moduleStatus_down() { set_moduleStatus ( Stub_ModuleStatus::moduleStatus_down ); }

	/* configsRunning - list of currently processed configs / jobs */
	virtual boost::shared_ptr<std::vector<ConnectedVision::id_t>> get_configsRunning() const;
	virtual const boost::shared_ptr<const std::vector<ConnectedVision::id_t>> getconst_configsRunning() const;
	virtual void set_configsRunning(boost::shared_ptr<std::vector<ConnectedVision::id_t>> value);
	virtual void set_configsRunning(const std::vector<ConnectedVision::id_t> &value) { boost::shared_ptr<std::vector<ConnectedVision::id_t>> ptr = boost::make_shared<std::vector<ConnectedVision::id_t>>(value); set_configsRunning(ptr); };
	// array functions
	virtual ConnectedVision::id_t get_configsRunning(int index) const;
	virtual const ConnectedVision::id_t& getconst_configsRunning(int index) const;
	virtual void add_configsRunning(ConnectedVision::id_t value);

	/* configsWaiting - list of configs / jobs waiting to be processed */
	virtual boost::shared_ptr<std::vector<ConnectedVision::id_t>> get_configsWaiting() const;
	virtual const boost::shared_ptr<const std::vector<ConnectedVision::id_t>> getconst_configsWaiting() const;
	virtual void set_configsWaiting(boost::shared_ptr<std::vector<ConnectedVision::id_t>> value);
	virtual void set_configsWaiting(const std::vector<ConnectedVision::id_t> &value) { boost::shared_ptr<std::vector<ConnectedVision::id_t>> ptr = boost::make_shared<std::vector<ConnectedVision::id_t>>(value); set_configsWaiting(ptr); };
	// array functions
	virtual ConnectedVision::id_t get_configsWaiting(int index) const;
	virtual const ConnectedVision::id_t& getconst_configsWaiting(int index) const;
	virtual void add_configsWaiting(ConnectedVision::id_t value);

	/* configID - virtual config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - virtual timestamp */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** module name */
	boost::shared_ptr<std::string> name;
	
	/** ID of module */
	ConnectedVision::id_t moduleID;
	
	/** current status of module */
	boost::shared_ptr<std::string> moduleStatus;
	
	/** list of currently processed configs / jobs */
	boost::shared_ptr<std::vector<ConnectedVision::id_t>> configsRunning;
	
	/** list of configs / jobs waiting to be processed */
	boost::shared_ptr<std::vector<ConnectedVision::id_t>> configsWaiting;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace ConnectedVision

#endif // Stub_ModuleStatus_def