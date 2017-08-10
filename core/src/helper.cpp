/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/regex.hpp>
#include <sstream>
#include <boost/algorithm/string.hpp> 

#include "helper.h"

using namespace std;

namespace ConnectedVision
{

int getIndex(const pinID_t& pinID)
{
	boost::regex re = boost::regex("^(.*)\\.([0-9]+)$");
	boost::smatch matches;

	int index = 0;

	if(boost::regex_match(pinID, matches, re))
	{
		index = stoi(matches[2]);
	}

	return index;
}

pinID_t getIndexedPinID(const pinID_t& pinID, int index)
{
	if(index == -1)
	{
		index = getIndex(pinID);
	}

	return getTypedPinID(pinID) + "." + intToStr(index);
}

pinID_t getTypedPinID(const pinID_t& pinID)
{
	boost::regex re = boost::regex("^(.*)\\.([0-9]+)$");
	boost::smatch matches;

	pinID_t pinIdTyped = pinID;

	if(boost::regex_match(pinID, matches, re))
	{
		pinIdTyped = static_cast<pinID_t>(matches[1]);
	}
	
	return pinIdTyped;
}

void parseURI(std::string uri, std::string &protocol, std::string &moduleName)
{
	size_t pos;
	pos = uri.find_first_of(":");
	if ( pos == string::npos )
			throw ConnectedVision::runtime_error("uri malformed: " + uri );
 	protocol = uri.substr(0, pos);
	pos = uri.find_first_not_of(":/", pos);
	if ( pos == string::npos )
			throw ConnectedVision::runtime_error("uri malformed: " + uri );
 	moduleName = uri.substr(pos);
}

void extendJsonObject(const rapidjson::Value& baseObject, const rapidjson::Value& masterObject, rapidjson::Value& extendedObject, rapidjson::Value::AllocatorType &allocator)
{	
	if ((baseObject.IsObject())&&(masterObject.IsObject()))
	{
		// copy all values from master object
		extendedObject.CopyFrom(masterObject, allocator);

		// extend it by additional members of base object
		for (auto it = baseObject.MemberBegin(); it != baseObject.MemberEnd(); it++)
		{
			rapidjson::Value::StringRefType refName(it->name.GetString());
			rapidjson::Value value(it->value, allocator);
			if (!extendedObject.HasMember(it->name))
			{			
				extendedObject.AddMember(refName, value, allocator);
			}
			else
			{
				// in case of sub-object -> recursively perform extending (merging)
				if ((it->value.IsObject()) && (extendedObject[it->name].IsObject()))
				{
					rapidjson::Value mergedObject;
					extendJsonObject(it->value, extendedObject[it->name], mergedObject, allocator);
					extendedObject[it->name] = mergedObject;
				}
			}
		}
	}
	else
	{
		throw ConnectedVision::runtime_error("error: both baseObject as well as masterObject need to be JSON objects");
	}
}

std::string trimStringAndRemoveSpaces(const std::string& s)
{
	std::string result = boost::trim_copy(s);
	while (result.find(" ") != result.npos)
	{
		boost::replace_all(result, " ", ""); // replace space
		boost::replace_all(result, "\n", ""); // replace line return
	}
	return result;
}

} // namespace ConnectedVision
