/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <rapidjson/document.h>	// TODO remove
#include <boost/make_shared.hpp>

#include <Module/Control/Class_RawData.h>

using namespace ConnectedVision;

Class_RawData::Class_RawData()
{
	clear();
}


Class_RawData::Class_RawData(const std::string& str)
{
	clear();
	this->data = str;
}


Class_RawData::~Class_RawData()
{
}


void Class_RawData::clear()
{
	this->data.clear();
}


void Class_RawData::parseJson(const std::string &str)
{
	this->data = str;
}

void Class_RawData::parseJson(const rapidjson::Value& value)
{
	// TODO workaround, remove JSON
}

std::string Class_RawData::get() const
{
	return( this->data );
}


const std::string& Class_RawData::getconst() const
{
	return( this->data );
}


void Class_RawData::set(const std::string &str)
{
	this->data = str;
}
