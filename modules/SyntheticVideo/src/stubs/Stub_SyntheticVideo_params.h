// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_SyntheticVideo_params.h
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
#include "../Class_SyntheticVideo_params_bgColor.h"
#include "../Class_SyntheticVideo_params_fgColor.h"
#include "../Class_SyntheticVideo_params_osdTextColor.h"

#ifndef Stub_SyntheticVideo_params_def
#define Stub_SyntheticVideo_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

/**
 * stub class for: Class_SyntheticVideo_params
 * 
 * module: SyntheticVideo
 * description: 
 */
class Stub_SyntheticVideo_params {

public:
	Stub_SyntheticVideo_params();
	Stub_SyntheticVideo_params(const Stub_SyntheticVideo_params& other);
	Stub_SyntheticVideo_params(const rapidjson::Value& value);
	Stub_SyntheticVideo_params(const std::string& str);
	virtual ~Stub_SyntheticVideo_params();
	Stub_SyntheticVideo_params &operator =(const Stub_SyntheticVideo_params& other);
	Stub_SyntheticVideo_params &operator =(Stub_SyntheticVideo_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* recordingDateTime - recording date (start time of video) */
	virtual ConnectedVision::timestamp_t get_recordingDateTime() const;
	virtual const ConnectedVision::timestamp_t getconst_recordingDateTime() const;
	virtual void set_recordingDateTime(ConnectedVision::timestamp_t value);

	/* numberOfFrames - number of frames in synthetic video */
	virtual double get_numberOfFrames() const;
	virtual const double getconst_numberOfFrames() const;
	virtual void set_numberOfFrames(double value);

	/* height - height of frames */
	virtual double get_height() const;
	virtual const double getconst_height() const;
	virtual void set_height(double value);

	/* width - width of frames */
	virtual double get_width() const;
	virtual const double getconst_width() const;
	virtual void set_width(double value);

	/* fps - number of frames per second */
	virtual double get_fps() const;
	virtual const double getconst_fps() const;
	virtual void set_fps(double value);

	/* sizeOfObject - size of object in synthetic video */
	virtual double get_sizeOfObject() const;
	virtual const double getconst_sizeOfObject() const;
	virtual void set_sizeOfObject(double value);

	/* bgColor - background color */
	virtual boost::shared_ptr<Class_SyntheticVideo_params_bgColor> get_bgColor() const;
	virtual const boost::shared_ptr<const Class_SyntheticVideo_params_bgColor> getconst_bgColor() const;
	virtual void set_bgColor(boost::shared_ptr<Class_SyntheticVideo_params_bgColor> value);
	virtual void set_bgColor(const Class_SyntheticVideo_params_bgColor &value) { boost::shared_ptr<Class_SyntheticVideo_params_bgColor> ptr = boost::make_shared<Class_SyntheticVideo_params_bgColor>(value); set_bgColor(ptr); };
	virtual void set_bgColor(const rapidjson::Value& value) { bgColor->parseJson( value ); };

	/* fgColor - foreground color */
	virtual boost::shared_ptr<Class_SyntheticVideo_params_fgColor> get_fgColor() const;
	virtual const boost::shared_ptr<const Class_SyntheticVideo_params_fgColor> getconst_fgColor() const;
	virtual void set_fgColor(boost::shared_ptr<Class_SyntheticVideo_params_fgColor> value);
	virtual void set_fgColor(const Class_SyntheticVideo_params_fgColor &value) { boost::shared_ptr<Class_SyntheticVideo_params_fgColor> ptr = boost::make_shared<Class_SyntheticVideo_params_fgColor>(value); set_fgColor(ptr); };
	virtual void set_fgColor(const rapidjson::Value& value) { fgColor->parseJson( value ); };

	/* osdTextColor - OSD text color */
	virtual boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor> get_osdTextColor() const;
	virtual const boost::shared_ptr<const Class_SyntheticVideo_params_osdTextColor> getconst_osdTextColor() const;
	virtual void set_osdTextColor(boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor> value);
	virtual void set_osdTextColor(const Class_SyntheticVideo_params_osdTextColor &value) { boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor> ptr = boost::make_shared<Class_SyntheticVideo_params_osdTextColor>(value); set_osdTextColor(ptr); };
	virtual void set_osdTextColor(const rapidjson::Value& value) { osdTextColor->parseJson( value ); };

	/* configID - virtual config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - virtual timestamp */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** recording date (start time of video) */
	ConnectedVision::timestamp_t recordingDateTime;
	
	/** number of frames in synthetic video */
	double numberOfFrames;
	
	/** height of frames */
	double height;
	
	/** width of frames */
	double width;
	
	/** number of frames per second */
	double fps;
	
	/** size of object in synthetic video */
	double sizeOfObject;
	
	/** background color */
	boost::shared_ptr<Class_SyntheticVideo_params_bgColor> bgColor;
	
	/** foreground color */
	boost::shared_ptr<Class_SyntheticVideo_params_fgColor> fgColor;
	
	/** OSD text color */
	boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor> osdTextColor;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_SyntheticVideo_params_def