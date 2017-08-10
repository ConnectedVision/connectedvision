/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_PinDescription_properties.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_PinDescription_properties_def
#define Stub_PinDescription_properties_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_PinDescription_properties
 * 
 * module: 
 * description: JSON schema of data returned by pin (if MIME is application/json)
 */
class Stub_PinDescription_properties {

public:
	Stub_PinDescription_properties();
	Stub_PinDescription_properties(const Stub_PinDescription_properties& other);
	Stub_PinDescription_properties(const rapidjson::Value& value);
	Stub_PinDescription_properties(const std::string& str);
	virtual ~Stub_PinDescription_properties();
	Stub_PinDescription_properties &operator =(const Stub_PinDescription_properties& other);
	Stub_PinDescription_properties &operator =(Stub_PinDescription_properties&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:

protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

};

} // namespace ConnectedVision

#endif // Stub_PinDescription_properties_def