/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_status_qualityOfService.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_generic_status_qualityOfService_def
#define Stub_generic_status_qualityOfService_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_status_qualityOfService
 * 
 * module: 
 * description: quality of service (QoS) parameters
 */
class Stub_generic_status_qualityOfService {

public:
	Stub_generic_status_qualityOfService();
	Stub_generic_status_qualityOfService(const Stub_generic_status_qualityOfService& other);
	Stub_generic_status_qualityOfService(const rapidjson::Value& value);
	Stub_generic_status_qualityOfService(const std::string& str);
	virtual ~Stub_generic_status_qualityOfService();
	Stub_generic_status_qualityOfService &operator =(const Stub_generic_status_qualityOfService& other);
	Stub_generic_status_qualityOfService &operator =(Stub_generic_status_qualityOfService&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* compuationDuration - computation duration based on the elapsed time between updates of the systemTimeProcessing parameter */
	virtual ConnectedVision::timestamp_t get_compuationDuration() const;
	virtual const ConnectedVision::timestamp_t getconst_compuationDuration() const;
	virtual void set_compuationDuration(ConnectedVision::timestamp_t value);

	/* compuationDurationAverage - average of the computation duration of 10 preceding iterations based on the elapsed time between updates of the systemTimeProcessing parameter computed using the simple moving average method */
	virtual ConnectedVision::timestamp_t get_compuationDurationAverage() const;
	virtual const ConnectedVision::timestamp_t getconst_compuationDurationAverage() const;
	virtual void set_compuationDurationAverage(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** computation duration based on the elapsed time between updates of the systemTimeProcessing parameter */
	ConnectedVision::timestamp_t compuationDuration;
	
	/** average of the computation duration of 10 preceding iterations based on the elapsed time between updates of the systemTimeProcessing parameter computed using the simple moving average method */
	ConnectedVision::timestamp_t compuationDurationAverage;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_status_qualityOfService_def