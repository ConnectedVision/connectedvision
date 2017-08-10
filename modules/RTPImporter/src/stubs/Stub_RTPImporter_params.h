// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_RTPImporter_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_RTPImporter_params_def
#define Stub_RTPImporter_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

/**
 * stub class for: Class_RTPImporter_params
 * 
 * module: RTP stream receiver module
 * description: RTP Receiver parameters
 */
class Stub_RTPImporter_params {

public:
	Stub_RTPImporter_params();
	Stub_RTPImporter_params(const Stub_RTPImporter_params& other);
	Stub_RTPImporter_params(const rapidjson::Value& value);
	Stub_RTPImporter_params(const std::string& str);
	virtual ~Stub_RTPImporter_params();
	Stub_RTPImporter_params &operator =(const Stub_RTPImporter_params& other);
	Stub_RTPImporter_params &operator =(Stub_RTPImporter_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* url - RTP multicast/unicast address (URL) */
	virtual boost::shared_ptr<std::string> get_url() const;
	virtual const boost::shared_ptr<const std::string> getconst_url() const;
	virtual void set_url(boost::shared_ptr<std::string> value);
	virtual void set_url(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_url(ptr); };

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

	/** RTP multicast/unicast address (URL) */
	boost::shared_ptr<std::string> url;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_RTPImporter_params_def