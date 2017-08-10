/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_HostStatus.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_HostStatus_def
#define Stub_HostStatus_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_HostStatus
 * 
 * module: 
 * description: host status
 */
class Stub_HostStatus {

public:
	Stub_HostStatus();
	Stub_HostStatus(const Stub_HostStatus& other);
	Stub_HostStatus(const rapidjson::Value& value);
	Stub_HostStatus(const std::string& str);
	virtual ~Stub_HostStatus();
	Stub_HostStatus &operator =(const Stub_HostStatus& other);
	Stub_HostStatus &operator =(Stub_HostStatus&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* hostID - host id */
	virtual ConnectedVision::id_t get_hostID() const;
	virtual const ConnectedVision::id_t getconst_hostID() const;
	virtual void set_hostID(ConnectedVision::id_t value);

	/* systemID - system ID */
	virtual ConnectedVision::id_t get_systemID() const;
	virtual const ConnectedVision::id_t getconst_systemID() const;
	virtual void set_systemID(ConnectedVision::id_t value);

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

	/** host id */
	ConnectedVision::id_t hostID;
	
	/** system ID */
	ConnectedVision::id_t systemID;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace ConnectedVision

#endif // Stub_HostStatus_def