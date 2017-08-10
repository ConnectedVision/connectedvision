/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Class_RawData_def
#define Class_RawData_def

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

#include <rapidjson/document.h>	// TODO remove

#include <general.h>

namespace ConnectedVision
{

/**
 * class to handle raw data
 */
class Class_RawData {

public:
	Class_RawData();
	Class_RawData(const std::string &str);
	virtual ~Class_RawData();

	virtual void clear();
	virtual void parseJson(const ::rapidjson::Value& value);
	virtual void parseJson(const std::string &str);

public:
	std::string get() const;
	const std::string& getconst() const;
	void set(const std::string &str);

protected:
	std::string data;
};

} // namespace ConnectedVision

#endif // Class_RawData_def


