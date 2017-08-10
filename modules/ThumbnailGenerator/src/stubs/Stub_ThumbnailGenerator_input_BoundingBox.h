// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_input_BoundingBox.h
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
#include "../Class_ThumbnailGenerator_input_BoundingBox_boundingBox.h"

#ifndef Stub_ThumbnailGenerator_input_BoundingBox_def
#define Stub_ThumbnailGenerator_input_BoundingBox_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for: Class_ThumbnailGenerator_input_BoundingBox
 * 
 * module: Thumbnail Generator
 * description: rectangular region which is used for the cropping or for overlaying bounding boxes
 */
class Stub_ThumbnailGenerator_input_BoundingBox {

public:
	Stub_ThumbnailGenerator_input_BoundingBox();
	Stub_ThumbnailGenerator_input_BoundingBox(const Stub_ThumbnailGenerator_input_BoundingBox& other);
	Stub_ThumbnailGenerator_input_BoundingBox(const rapidjson::Value& value);
	Stub_ThumbnailGenerator_input_BoundingBox(const std::string& str);
	virtual ~Stub_ThumbnailGenerator_input_BoundingBox();
	Stub_ThumbnailGenerator_input_BoundingBox &operator =(const Stub_ThumbnailGenerator_input_BoundingBox& other);
	Stub_ThumbnailGenerator_input_BoundingBox &operator =(Stub_ThumbnailGenerator_input_BoundingBox&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - ID */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* configID - job / config ID */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* boundingBox - bounding box */
	virtual boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> get_boundingBox() const;
	virtual const boost::shared_ptr<const Class_ThumbnailGenerator_input_BoundingBox_boundingBox> getconst_boundingBox() const;
	virtual void set_boundingBox(boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> value);
	virtual void set_boundingBox(const Class_ThumbnailGenerator_input_BoundingBox_boundingBox &value) { boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> ptr = boost::make_shared<Class_ThumbnailGenerator_input_BoundingBox_boundingBox>(value); set_boundingBox(ptr); };
	virtual void set_boundingBox(const rapidjson::Value& value) { boundingBox->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** ID */
	ConnectedVision::id_t id;
	
	/** job / config ID */
	ConnectedVision::id_t configID;
	
	/** timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	ConnectedVision::timestamp_t timestamp;
	
	/** bounding box */
	boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> boundingBox;
	
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_ThumbnailGenerator_input_BoundingBox_def