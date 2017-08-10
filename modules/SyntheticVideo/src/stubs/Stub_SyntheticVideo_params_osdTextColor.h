// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_SyntheticVideo_params_osdTextColor.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_SyntheticVideo_params_osdTextColor_def
#define Stub_SyntheticVideo_params_osdTextColor_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

/**
 * stub class for: Class_SyntheticVideo_params_osdTextColor
 * 
 * module: SyntheticVideo
 * description: OSD text color
 */
class Stub_SyntheticVideo_params_osdTextColor {

public:
	Stub_SyntheticVideo_params_osdTextColor();
	Stub_SyntheticVideo_params_osdTextColor(const Stub_SyntheticVideo_params_osdTextColor& other);
	Stub_SyntheticVideo_params_osdTextColor(const rapidjson::Value& value);
	Stub_SyntheticVideo_params_osdTextColor(const std::string& str);
	virtual ~Stub_SyntheticVideo_params_osdTextColor();
	Stub_SyntheticVideo_params_osdTextColor &operator =(const Stub_SyntheticVideo_params_osdTextColor& other);
	Stub_SyntheticVideo_params_osdTextColor &operator =(Stub_SyntheticVideo_params_osdTextColor&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* R -  */
	virtual double get_R() const;
	virtual const double getconst_R() const;
	virtual void set_R(double value);

	/* G -  */
	virtual double get_G() const;
	virtual const double getconst_G() const;
	virtual void set_G(double value);

	/* B -  */
	virtual double get_B() const;
	virtual const double getconst_B() const;
	virtual void set_B(double value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	double R;
	
	/**  */
	double G;
	
	/**  */
	double B;
	
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_SyntheticVideo_params_osdTextColor_def