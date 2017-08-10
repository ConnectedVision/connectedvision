// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_Skeleton_output_Average_color.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_Skeleton_output_Average_color_def
#define Stub_Skeleton_output_Average_color_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {

/**
 * stub class for: Class_Skeleton_output_Average_color
 * 
 * module: Skeleton Module
 * description: average color of bounding box
 */
class Stub_Skeleton_output_Average_color {

public:
	Stub_Skeleton_output_Average_color();
	Stub_Skeleton_output_Average_color(const Stub_Skeleton_output_Average_color& other);
	Stub_Skeleton_output_Average_color(const rapidjson::Value& value);
	Stub_Skeleton_output_Average_color(const std::string& str);
	virtual ~Stub_Skeleton_output_Average_color();
	Stub_Skeleton_output_Average_color &operator =(const Stub_Skeleton_output_Average_color& other);
	Stub_Skeleton_output_Average_color &operator =(Stub_Skeleton_output_Average_color&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* R - red */
	virtual int64_t get_R() const;
	virtual const int64_t getconst_R() const;
	virtual void set_R(int64_t value);

	/* G - green */
	virtual int64_t get_G() const;
	virtual const int64_t getconst_G() const;
	virtual void set_G(int64_t value);

	/* B - blue */
	virtual int64_t get_B() const;
	virtual const int64_t getconst_B() const;
	virtual void set_B(int64_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** red */
	int64_t R;
	
	/** green */
	int64_t G;
	
	/** blue */
	int64_t B;
	
};

} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_Skeleton_output_Average_color_def