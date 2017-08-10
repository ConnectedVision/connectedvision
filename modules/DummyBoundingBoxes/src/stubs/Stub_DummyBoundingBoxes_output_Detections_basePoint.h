// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_Detections_basePoint.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_DummyBoundingBoxes_output_Detections_basePoint_def
#define Stub_DummyBoundingBoxes_output_Detections_basePoint_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_output_Detections_basePoint
 * 
 * module: DummyBoundingBoxes
 * description: base point
 */
class Stub_DummyBoundingBoxes_output_Detections_basePoint {

public:
	Stub_DummyBoundingBoxes_output_Detections_basePoint();
	Stub_DummyBoundingBoxes_output_Detections_basePoint(const Stub_DummyBoundingBoxes_output_Detections_basePoint& other);
	Stub_DummyBoundingBoxes_output_Detections_basePoint(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_output_Detections_basePoint(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_output_Detections_basePoint();
	Stub_DummyBoundingBoxes_output_Detections_basePoint &operator =(const Stub_DummyBoundingBoxes_output_Detections_basePoint& other);
	Stub_DummyBoundingBoxes_output_Detections_basePoint &operator =(Stub_DummyBoundingBoxes_output_Detections_basePoint&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* x - x position of point */
	virtual double get_x() const;
	virtual const double getconst_x() const;
	virtual void set_x(double value);

	/* y - y position of point */
	virtual double get_y() const;
	virtual const double getconst_y() const;
	virtual void set_y(double value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** x position of point */
	double x;
	
	/** y position of point */
	double y;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_output_Detections_basePoint_def