/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_status_stableResults.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_generic_status_stableResults_def
#define Stub_generic_status_stableResults_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_status_stableResults
 * 
 * module: 
 * description: 
 */
class Stub_generic_status_stableResults {

public:
	Stub_generic_status_stableResults();
	Stub_generic_status_stableResults(const Stub_generic_status_stableResults& other);
	Stub_generic_status_stableResults(const rapidjson::Value& value);
	Stub_generic_status_stableResults(const std::string& str);
	virtual ~Stub_generic_status_stableResults();
	Stub_generic_status_stableResults &operator =(const Stub_generic_status_stableResults& other);
	Stub_generic_status_stableResults &operator =(Stub_generic_status_stableResults&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* pinID - id of output pin */
	virtual boost::shared_ptr<std::string> get_pinID() const;
	virtual const boost::shared_ptr<const std::string> getconst_pinID() const;
	virtual void set_pinID(boost::shared_ptr<std::string> value);
	virtual void set_pinID(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_pinID(ptr); };

	/* indexStart -  */
	virtual int64_t get_indexStart() const;
	virtual const int64_t getconst_indexStart() const;
	virtual void set_indexStart(int64_t value);

	/* indexEnd -  */
	virtual int64_t get_indexEnd() const;
	virtual const int64_t getconst_indexEnd() const;
	virtual void set_indexEnd(int64_t value);

	/* timestampStart -  */
	virtual ConnectedVision::timestamp_t get_timestampStart() const;
	virtual const ConnectedVision::timestamp_t getconst_timestampStart() const;
	virtual void set_timestampStart(ConnectedVision::timestamp_t value);

	/* timestampEnd -  */
	virtual ConnectedVision::timestamp_t get_timestampEnd() const;
	virtual const ConnectedVision::timestamp_t getconst_timestampEnd() const;
	virtual void set_timestampEnd(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** id of output pin */
	boost::shared_ptr<std::string> pinID;
	
	/**  */
	int64_t indexStart;
	
	/**  */
	int64_t indexEnd;
	
	/**  */
	ConnectedVision::timestamp_t timestampStart;
	
	/**  */
	ConnectedVision::timestamp_t timestampEnd;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_status_stableResults_def