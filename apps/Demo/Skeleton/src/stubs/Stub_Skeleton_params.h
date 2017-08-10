// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_Skeleton_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_Skeleton_params_def
#define Stub_Skeleton_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {

/**
 * stub class for: Class_Skeleton_params
 * 
 * module: Skeleton Module
 * description: Skeleton Dummy Parameter
 */
class Stub_Skeleton_params {

public:
	Stub_Skeleton_params();
	Stub_Skeleton_params(const Stub_Skeleton_params& other);
	Stub_Skeleton_params(const rapidjson::Value& value);
	Stub_Skeleton_params(const std::string& str);
	virtual ~Stub_Skeleton_params();
	Stub_Skeleton_params &operator =(const Stub_Skeleton_params& other);
	Stub_Skeleton_params &operator =(Stub_Skeleton_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* dummy - just a place holder */
	virtual int64_t get_dummy() const;
	virtual const int64_t getconst_dummy() const;
	virtual void set_dummy(int64_t value);

	/* dummy_dynamic_parameter - just a place holder for a dynamic parameter */
	virtual int64_t get_dummy_dynamic_parameter() const;
	virtual const int64_t getconst_dummy_dynamic_parameter() const;
	virtual void set_dummy_dynamic_parameter(int64_t value);

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

	/** just a place holder */
	int64_t dummy;
	
	/** just a place holder for a dynamic parameter */
	int64_t dummy_dynamic_parameter;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_Skeleton_params_def