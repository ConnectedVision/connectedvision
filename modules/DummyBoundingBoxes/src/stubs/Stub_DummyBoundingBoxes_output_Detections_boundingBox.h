// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_Detections_boundingBox.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_DummyBoundingBoxes_output_Detections_boundingBox_def
#define Stub_DummyBoundingBoxes_output_Detections_boundingBox_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_output_Detections_boundingBox
 * 
 * module: DummyBoundingBoxes
 * description: bounding box
 */
class Stub_DummyBoundingBoxes_output_Detections_boundingBox {

public:
	Stub_DummyBoundingBoxes_output_Detections_boundingBox();
	Stub_DummyBoundingBoxes_output_Detections_boundingBox(const Stub_DummyBoundingBoxes_output_Detections_boundingBox& other);
	Stub_DummyBoundingBoxes_output_Detections_boundingBox(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_output_Detections_boundingBox(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_output_Detections_boundingBox();
	Stub_DummyBoundingBoxes_output_Detections_boundingBox &operator =(const Stub_DummyBoundingBoxes_output_Detections_boundingBox& other);
	Stub_DummyBoundingBoxes_output_Detections_boundingBox &operator =(Stub_DummyBoundingBoxes_output_Detections_boundingBox&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* left - x position of top left point of the rectangle */
	virtual double get_left() const;
	virtual const double getconst_left() const;
	virtual void set_left(double value);

	/* right - x position of bottom right point of the rectangle */
	virtual double get_right() const;
	virtual const double getconst_right() const;
	virtual void set_right(double value);

	/* top - y position of top left point of the rectangle */
	virtual double get_top() const;
	virtual const double getconst_top() const;
	virtual void set_top(double value);

	/* bottom - y position of bottom right point of the rectangle */
	virtual double get_bottom() const;
	virtual const double getconst_bottom() const;
	virtual void set_bottom(double value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** x position of top left point of the rectangle */
	double left;
	
	/** x position of bottom right point of the rectangle */
	double right;
	
	/** y position of top left point of the rectangle */
	double top;
	
	/** y position of bottom right point of the rectangle */
	double bottom;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_output_Detections_boundingBox_def