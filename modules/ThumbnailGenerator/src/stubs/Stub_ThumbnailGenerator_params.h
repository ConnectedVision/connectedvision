// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_params.h
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
#include "../Class_ThumbnailGenerator_params_lineColor.h"

#ifndef Stub_ThumbnailGenerator_params_def
#define Stub_ThumbnailGenerator_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for: Class_ThumbnailGenerator_params
 * 
 * module: Thumbnail Generator
 * description: 
 */
class Stub_ThumbnailGenerator_params {

public:
	Stub_ThumbnailGenerator_params();
	Stub_ThumbnailGenerator_params(const Stub_ThumbnailGenerator_params& other);
	Stub_ThumbnailGenerator_params(const rapidjson::Value& value);
	Stub_ThumbnailGenerator_params(const std::string& str);
	virtual ~Stub_ThumbnailGenerator_params();
	Stub_ThumbnailGenerator_params &operator =(const Stub_ThumbnailGenerator_params& other);
	Stub_ThumbnailGenerator_params &operator =(Stub_ThumbnailGenerator_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* imageFormat - image format */
	virtual boost::shared_ptr<std::string> get_imageFormat() const;
	virtual const boost::shared_ptr<const std::string> getconst_imageFormat() const;
	virtual void set_imageFormat(boost::shared_ptr<std::string> value);
	virtual void set_imageFormat(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_imageFormat(ptr); };
	// enum functions
	virtual bool is_imageFormat(const boost::shared_ptr<std::string>& value) const;
	const static boost::shared_ptr<std::string> imageFormat_JPEG;
	virtual bool is_imageFormat_JPEG() const { return is_imageFormat( Stub_ThumbnailGenerator_params::imageFormat_JPEG ); }
	virtual void set_imageFormat_JPEG() { set_imageFormat ( Stub_ThumbnailGenerator_params::imageFormat_JPEG ); }
	const static boost::shared_ptr<std::string> imageFormat_PNG;
	virtual bool is_imageFormat_PNG() const { return is_imageFormat( Stub_ThumbnailGenerator_params::imageFormat_PNG ); }
	virtual void set_imageFormat_PNG() { set_imageFormat ( Stub_ThumbnailGenerator_params::imageFormat_PNG ); }

	/* lineWidth - line width */
	virtual int64_t get_lineWidth() const;
	virtual const int64_t getconst_lineWidth() const;
	virtual void set_lineWidth(int64_t value);

	/* lineColor - line color */
	virtual boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor> get_lineColor() const;
	virtual const boost::shared_ptr<const Class_ThumbnailGenerator_params_lineColor> getconst_lineColor() const;
	virtual void set_lineColor(boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor> value);
	virtual void set_lineColor(const Class_ThumbnailGenerator_params_lineColor &value) { boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor> ptr = boost::make_shared<Class_ThumbnailGenerator_params_lineColor>(value); set_lineColor(ptr); };
	virtual void set_lineColor(const rapidjson::Value& value) { lineColor->parseJson( value ); };

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

	/** image format */
	boost::shared_ptr<std::string> imageFormat;
	
	/** line width */
	int64_t lineWidth;
	
	/** line color */
	boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor> lineColor;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_ThumbnailGenerator_params_def