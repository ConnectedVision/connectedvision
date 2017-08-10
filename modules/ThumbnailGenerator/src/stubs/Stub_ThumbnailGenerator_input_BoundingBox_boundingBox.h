// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_input_BoundingBox_boundingBox.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ThumbnailGenerator_input_BoundingBox_boundingBox_def
#define Stub_ThumbnailGenerator_input_BoundingBox_boundingBox_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for: Class_ThumbnailGenerator_input_BoundingBox_boundingBox
 * 
 * module: Thumbnail Generator
 * description: bounding box
 */
class Stub_ThumbnailGenerator_input_BoundingBox_boundingBox {

public:
	Stub_ThumbnailGenerator_input_BoundingBox_boundingBox();
	Stub_ThumbnailGenerator_input_BoundingBox_boundingBox(const Stub_ThumbnailGenerator_input_BoundingBox_boundingBox& other);
	Stub_ThumbnailGenerator_input_BoundingBox_boundingBox(const rapidjson::Value& value);
	Stub_ThumbnailGenerator_input_BoundingBox_boundingBox(const std::string& str);
	virtual ~Stub_ThumbnailGenerator_input_BoundingBox_boundingBox();
	Stub_ThumbnailGenerator_input_BoundingBox_boundingBox &operator =(const Stub_ThumbnailGenerator_input_BoundingBox_boundingBox& other);
	Stub_ThumbnailGenerator_input_BoundingBox_boundingBox &operator =(Stub_ThumbnailGenerator_input_BoundingBox_boundingBox&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* left - x position of left side */
	virtual double get_left() const;
	virtual const double getconst_left() const;
	virtual void set_left(double value);

	/* right - x position of right side */
	virtual double get_right() const;
	virtual const double getconst_right() const;
	virtual void set_right(double value);

	/* bottom - y position of bottom side */
	virtual double get_bottom() const;
	virtual const double getconst_bottom() const;
	virtual void set_bottom(double value);

	/* top - y position of top side */
	virtual double get_top() const;
	virtual const double getconst_top() const;
	virtual void set_top(double value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** x position of left side */
	double left;
	
	/** x position of right side */
	double right;
	
	/** y position of bottom side */
	double bottom;
	
	/** y position of top side */
	double top;
	
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_ThumbnailGenerator_input_BoundingBox_boundingBox_def