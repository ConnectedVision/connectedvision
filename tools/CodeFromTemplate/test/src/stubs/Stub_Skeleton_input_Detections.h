// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_Skeleton_input_Detections.h
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
#include "../Class_Skeleton_input_Detections_boundingBox.h"

#ifndef Stub_Skeleton_input_Detections_def
#define Stub_Skeleton_input_Detections_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace test {

/**
 * stub class for: Class_Skeleton_input_Detections
 * 
 * module: Skeleton Module
 * description: bounding box
 */
class Stub_Skeleton_input_Detections {

public:
	Stub_Skeleton_input_Detections();
	Stub_Skeleton_input_Detections(const Stub_Skeleton_input_Detections& other);
	Stub_Skeleton_input_Detections(const rapidjson::Value& value);
	Stub_Skeleton_input_Detections(const std::string& str);
	virtual ~Stub_Skeleton_input_Detections();
	Stub_Skeleton_input_Detections &operator =(const Stub_Skeleton_input_Detections& other);
	Stub_Skeleton_input_Detections &operator =(Stub_Skeleton_input_Detections&& other) noexcept;

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

	/* objectID -  */
	virtual ConnectedVision::id_t get_objectID() const;
	virtual const ConnectedVision::id_t getconst_objectID() const;
	virtual void set_objectID(ConnectedVision::id_t value);

	/* timestamp - first detection */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* boundingBox - bounding box */
	virtual boost::shared_ptr<Class_Skeleton_input_Detections_boundingBox> get_boundingBox() const;
	virtual const boost::shared_ptr<const Class_Skeleton_input_Detections_boundingBox> getconst_boundingBox() const;
	virtual void set_boundingBox(boost::shared_ptr<Class_Skeleton_input_Detections_boundingBox> value);
	virtual void set_boundingBox(const Class_Skeleton_input_Detections_boundingBox &value) { boost::shared_ptr<Class_Skeleton_input_Detections_boundingBox> ptr = boost::make_shared<Class_Skeleton_input_Detections_boundingBox>(value); set_boundingBox(ptr); };
	virtual void set_boundingBox(const rapidjson::Value& value) { boundingBox->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	ConnectedVision::id_t id;
	
	/**  */
	ConnectedVision::id_t configID;
	
	/**  */
	ConnectedVision::id_t objectID;
	
	/** first detection */
	ConnectedVision::timestamp_t timestamp;
	
	/** bounding box */
	boost::shared_ptr<Class_Skeleton_input_Detections_boundingBox> boundingBox;
	
};

} // namespace test
} // namespace ConnectedVision

#endif // Stub_Skeleton_input_Detections_def