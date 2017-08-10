/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef helper_def
#define helper_def

#include <string>
#include <math.h>

#include <boost/algorithm/string/replace.hpp>

#include <IConnectedVisionModule.h>

namespace ConnectedVision
{

pinID_t getIndexedPinID(const pinID_t& pinID, int index = -1);

pinID_t getTypedPinID(const pinID_t& pinID);

int getIndex(const pinID_t& pinID);

std::string intToStr(int64_t i);

void parseURI(std::string uri, std::string &protocol, std::string &moduleName);

void extendJsonObject(const ::rapidjson::Value& baseObject, const ::rapidjson::Value& masterObject, ::rapidjson::Value& extendedObject, ::rapidjson::Value::AllocatorType &allocator);

std::string trimStringAndRemoveSpaces(const std::string& s);

static inline int writeError(ConnectedVisionResponse &response, int status, const id_t &moduleID, std::string error)
{
	response.setContentType("application/json");
	error = boost::replace_all_copy( error, "\"", "'");
	boost::replace_all( error, "\n", "");	boost::replace_all( error, "\r", "");
	response.setContent( "{ \"status\": " + intToStr(status) + ", \"moduleID\": \"" + moduleID + "\"" + ", \"error\": \"" + error + "\"}" );

	return status;
}

static inline int64_t round_int64(double number)
{
    int64_t i = static_cast<int64_t>(number < 0.0 ? ceil(number - 0.5) : floor(number + 0.5));
	return i;
}

} // namespace ConnectedVision

#endif // helper_def
