// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_Detections.h
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
#include "../Class_DummyBoundingBoxes_output_Detections_boundingBox.h"
#include "../Class_DummyBoundingBoxes_output_Detections_basePoint.h"

#ifndef Stub_DummyBoundingBoxes_output_Detections_def
#define Stub_DummyBoundingBoxes_output_Detections_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_output_Detections
 * 
 * module: DummyBoundingBoxes
 * description: bounding box
 */
class Stub_DummyBoundingBoxes_output_Detections {

public:
	Stub_DummyBoundingBoxes_output_Detections();
	Stub_DummyBoundingBoxes_output_Detections(const Stub_DummyBoundingBoxes_output_Detections& other);
	Stub_DummyBoundingBoxes_output_Detections(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_output_Detections(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_output_Detections();
	Stub_DummyBoundingBoxes_output_Detections &operator =(const Stub_DummyBoundingBoxes_output_Detections& other);
	Stub_DummyBoundingBoxes_output_Detections &operator =(Stub_DummyBoundingBoxes_output_Detections&& other) noexcept;

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

	/* id - detection ID */
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

	/* boundingBox - bounding box */
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_boundingBox> get_boundingBox() const;
	virtual const boost::shared_ptr<const Class_DummyBoundingBoxes_output_Detections_boundingBox> getconst_boundingBox() const;
	virtual void set_boundingBox(boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_boundingBox> value);
	virtual void set_boundingBox(const Class_DummyBoundingBoxes_output_Detections_boundingBox &value) { boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_boundingBox> ptr = boost::make_shared<Class_DummyBoundingBoxes_output_Detections_boundingBox>(value); set_boundingBox(ptr); };
	virtual void set_boundingBox(const rapidjson::Value& value) { boundingBox->parseJson( value ); };

	/* basePoint - base point */
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_basePoint> get_basePoint() const;
	virtual const boost::shared_ptr<const Class_DummyBoundingBoxes_output_Detections_basePoint> getconst_basePoint() const;
	virtual void set_basePoint(boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_basePoint> value);
	virtual void set_basePoint(const Class_DummyBoundingBoxes_output_Detections_basePoint &value) { boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_basePoint> ptr = boost::make_shared<Class_DummyBoundingBoxes_output_Detections_basePoint>(value); set_basePoint(ptr); };
	virtual void set_basePoint(const rapidjson::Value& value) { basePoint->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** ID of config chain */
	ConnectedVision::id_t configID;
	
	/** detection ID */
	ConnectedVision::id_t id;
	
	/** timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	ConnectedVision::timestamp_t timestamp;
	
	/** object ID */
	ConnectedVision::id_t objectID;
	
	/** bounding box */
	boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_boundingBox> boundingBox;
	
	/** base point */
	boost::shared_ptr<Class_DummyBoundingBoxes_output_Detections_basePoint> basePoint;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_output_Detections_def