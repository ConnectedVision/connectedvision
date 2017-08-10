/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef IDataClassJSON_def
#define IDataClassJSON_def

#include <stdint.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>

#include "general.h"

namespace ConnectedVision
{

/**
 * generic data object
 */
class IDataClassJSON 
{
public:
	virtual ~IDataClassJSON() {};

	virtual void clear() = 0;
	virtual void parseJson(const rapidjson::Value& value) = 0;
	virtual void parseJson(const char *str) = 0;
	virtual inline void parseJson(const std::string str) { this->parseJson( str.c_str() ); };

	virtual std::string toJsonStr() const = 0;
	virtual std::string toJson() const = 0;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const = 0;
};

} // namespace ConnectedVision

#endif // IDataClassJSON_def


