// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_ObjectData.h
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
#include "../Class_DummyBoundingBoxes_output_ObjectData_detections.h"

#ifndef Stub_DummyBoundingBoxes_output_ObjectData_def
#define Stub_DummyBoundingBoxes_output_ObjectData_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_output_ObjectData
 * 
 * module: DummyBoundingBoxes
 * description: object meta data
 */
class Stub_DummyBoundingBoxes_output_ObjectData {

public:
	Stub_DummyBoundingBoxes_output_ObjectData();
	Stub_DummyBoundingBoxes_output_ObjectData(const Stub_DummyBoundingBoxes_output_ObjectData& other);
	Stub_DummyBoundingBoxes_output_ObjectData(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_output_ObjectData(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_output_ObjectData();
	Stub_DummyBoundingBoxes_output_ObjectData &operator =(const Stub_DummyBoundingBoxes_output_ObjectData& other);
	Stub_DummyBoundingBoxes_output_ObjectData &operator =(Stub_DummyBoundingBoxes_output_ObjectData&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* configID - ID of config chain */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* id - object ID */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* timestamp - timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* objectID - object ID */
	virtual ConnectedVision::id_t get_objectID() const;
	virtual const ConnectedVision::id_t getconst_objectID() const;
	virtual void set_objectID(ConnectedVision::id_t value);

	/* detections - list of detections of event */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> get_detections() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> getconst_detections() const;
	virtual void set_detections(boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> value);
	virtual void set_detections(const std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>>(value); set_detections(ptr); };
	// array functions
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections> get_detections(int index) const;
	virtual const boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>& getconst_detections(int index) const;
	virtual void add_detections(boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections> value);
	virtual void add_detections(const Class_DummyBoundingBoxes_output_ObjectData_detections &value) { boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections> ptr = boost::make_shared<Class_DummyBoundingBoxes_output_ObjectData_detections>(value); add_detections(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** ID of config chain */
	ConnectedVision::id_t configID;
	
	/** object ID */
	ConnectedVision::id_t id;
	
	/** timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	ConnectedVision::timestamp_t timestamp;
	
	/** object ID */
	ConnectedVision::id_t objectID;
	
	/** list of detections of event */
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> detections;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_output_ObjectData_def