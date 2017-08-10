// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_input_Trigger.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_DummyBoundingBoxes_input_Trigger_def
#define Stub_DummyBoundingBoxes_input_Trigger_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_input_Trigger
 * 
 * module: DummyBoundingBoxes
 * description: Trigger pulse used as signal for the generation of a bounding box.
 */
class Stub_DummyBoundingBoxes_input_Trigger {

public:
	Stub_DummyBoundingBoxes_input_Trigger();
	Stub_DummyBoundingBoxes_input_Trigger(const Stub_DummyBoundingBoxes_input_Trigger& other);
	Stub_DummyBoundingBoxes_input_Trigger(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_input_Trigger(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_input_Trigger();
	Stub_DummyBoundingBoxes_input_Trigger &operator =(const Stub_DummyBoundingBoxes_input_Trigger& other);
	Stub_DummyBoundingBoxes_input_Trigger &operator =(Stub_DummyBoundingBoxes_input_Trigger&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id -  */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* configID -  */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	ConnectedVision::id_t id;
	
	/**  */
	ConnectedVision::id_t configID;
	
	/** timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_input_Trigger_def