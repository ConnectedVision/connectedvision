// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_params_lineColor.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ThumbnailGenerator_params_lineColor_def
#define Stub_ThumbnailGenerator_params_lineColor_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for: Class_ThumbnailGenerator_params_lineColor
 * 
 * module: Thumbnail Generator
 * description: line color
 */
class Stub_ThumbnailGenerator_params_lineColor {

public:
	Stub_ThumbnailGenerator_params_lineColor();
	Stub_ThumbnailGenerator_params_lineColor(const Stub_ThumbnailGenerator_params_lineColor& other);
	Stub_ThumbnailGenerator_params_lineColor(const rapidjson::Value& value);
	Stub_ThumbnailGenerator_params_lineColor(const std::string& str);
	virtual ~Stub_ThumbnailGenerator_params_lineColor();
	Stub_ThumbnailGenerator_params_lineColor &operator =(const Stub_ThumbnailGenerator_params_lineColor& other);
	Stub_ThumbnailGenerator_params_lineColor &operator =(Stub_ThumbnailGenerator_params_lineColor&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* R - red component */
	virtual double get_R() const;
	virtual const double getconst_R() const;
	virtual void set_R(double value);

	/* G - green component */
	virtual double get_G() const;
	virtual const double getconst_G() const;
	virtual void set_G(double value);

	/* B - blue component */
	virtual double get_B() const;
	virtual const double getconst_B() const;
	virtual void set_B(double value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** red component */
	double R;
	
	/** green component */
	double G;
	
	/** blue component */
	double B;
	
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_ThumbnailGenerator_params_lineColor_def