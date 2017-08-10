// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections.h
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
#include "../Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox.h"
#include "../Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint.h"

#ifndef Stub_DummyBoundingBoxes_output_ObjectData_detections_def
#define Stub_DummyBoundingBoxes_output_ObjectData_detections_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_output_ObjectData_detections
 * 
 * module: DummyBoundingBoxes
 * description: detection
 */
class Stub_DummyBoundingBoxes_output_ObjectData_detections {

public:
	Stub_DummyBoundingBoxes_output_ObjectData_detections();
	Stub_DummyBoundingBoxes_output_ObjectData_detections(const Stub_DummyBoundingBoxes_output_ObjectData_detections& other);
	Stub_DummyBoundingBoxes_output_ObjectData_detections(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_output_ObjectData_detections(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_output_ObjectData_detections();
	Stub_DummyBoundingBoxes_output_ObjectData_detections &operator =(const Stub_DummyBoundingBoxes_output_ObjectData_detections& other);
	Stub_DummyBoundingBoxes_output_ObjectData_detections &operator =(Stub_DummyBoundingBoxes_output_ObjectData_detections&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* timestamp - timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* confidence - confidence of detection [0-1] */
	virtual double get_confidence() const;
	virtual const double getconst_confidence() const;
	virtual void set_confidence(double value);

	/* boundingBox - bounding box */
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> get_boundingBox() const;
	virtual const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> getconst_boundingBox() const;
	virtual void set_boundingBox(boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> value);
	virtual void set_boundingBox(const Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox &value) { boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> ptr = boost::make_shared<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox>(value); set_boundingBox(ptr); };
	virtual void set_boundingBox(const rapidjson::Value& value) { boundingBox->parseJson( value ); };

	/* basePoint - base point */
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> get_basePoint() const;
	virtual const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> getconst_basePoint() const;
	virtual void set_basePoint(boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> value);
	virtual void set_basePoint(const Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint &value) { boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> ptr = boost::make_shared<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint>(value); set_basePoint(ptr); };
	virtual void set_basePoint(const rapidjson::Value& value) { basePoint->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	ConnectedVision::timestamp_t timestamp;
	
	/** confidence of detection [0-1] */
	double confidence;
	
	/** bounding box */
	boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> boundingBox;
	
	/** base point */
	boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> basePoint;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_output_ObjectData_detections_def