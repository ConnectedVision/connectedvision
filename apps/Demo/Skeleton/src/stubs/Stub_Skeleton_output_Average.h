// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_Skeleton_output_Average.h
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
#include "../Class_Skeleton_output_Average_color.h"

#ifndef Stub_Skeleton_output_Average_def
#define Stub_Skeleton_output_Average_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {

/**
 * stub class for: Class_Skeleton_output_Average
 * 
 * module: Skeleton Module
 * description: This is a completely senseless output pin providing the average color of the area in the bounding box.
 */
class Stub_Skeleton_output_Average {

public:
	Stub_Skeleton_output_Average();
	Stub_Skeleton_output_Average(const Stub_Skeleton_output_Average& other);
	Stub_Skeleton_output_Average(const rapidjson::Value& value);
	Stub_Skeleton_output_Average(const std::string& str);
	virtual ~Stub_Skeleton_output_Average();
	Stub_Skeleton_output_Average &operator =(const Stub_Skeleton_output_Average& other);
	Stub_Skeleton_output_Average &operator =(Stub_Skeleton_output_Average&& other) noexcept;

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

	/* timestamp - first detection */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* color - average color of bounding box */
	virtual boost::shared_ptr<Class_Skeleton_output_Average_color> get_color() const;
	virtual const boost::shared_ptr<const Class_Skeleton_output_Average_color> getconst_color() const;
	virtual void set_color(boost::shared_ptr<Class_Skeleton_output_Average_color> value);
	virtual void set_color(const Class_Skeleton_output_Average_color &value) { boost::shared_ptr<Class_Skeleton_output_Average_color> ptr = boost::make_shared<Class_Skeleton_output_Average_color>(value); set_color(ptr); };
	virtual void set_color(const rapidjson::Value& value) { color->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	ConnectedVision::id_t id;
	
	/**  */
	ConnectedVision::id_t configID;
	
	/** first detection */
	ConnectedVision::timestamp_t timestamp;
	
	/** average color of bounding box */
	boost::shared_ptr<Class_Skeleton_output_Average_color> color;
	
};

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_Skeleton_output_Average_def