/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_status_qualityOfService.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_status_qualityOfService.h"
#include "../Class_generic_status_qualityOfService.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_status_qualityOfService::Stub_generic_status_qualityOfService(const Stub_generic_status_qualityOfService& other)
{
	// TODO: other.readLock
	// compuationDuration
	compuationDuration = other.compuationDuration;
	// compuationDurationAverage
	compuationDurationAverage = other.compuationDurationAverage;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_status_qualityOfService& Stub_generic_status_qualityOfService::operator =(const Stub_generic_status_qualityOfService& other)
{
	Stub_generic_status_qualityOfService tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_status_qualityOfService& Stub_generic_status_qualityOfService::operator =(Stub_generic_status_qualityOfService&& other) noexcept
{
	// compuationDuration
    std::swap(compuationDuration, other.compuationDuration);
	// compuationDurationAverage
    std::swap(compuationDurationAverage, other.compuationDurationAverage);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_status_qualityOfService::Stub_generic_status_qualityOfService()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_status_qualityOfService::Stub_generic_status_qualityOfService(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_status_qualityOfService::Stub_generic_status_qualityOfService(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_status_qualityOfService::~Stub_generic_status_qualityOfService()
{
}

// --> Do NOT EDIT <--
void Stub_generic_status_qualityOfService::clear()
{
	this->compuationDuration = -1;
	this->compuationDurationAverage = -1;
}

// --> Do NOT EDIT <--
void Stub_generic_status_qualityOfService::parseJson(const char *str)
{
	// ignore empty data
	if ( str[0] == 0 )
		return;
	
	// parse data
	rapidjson::Document document;
	if (document.Parse<0>(str).HasParseError())
	{
		std::string context;
		size_t off = document.GetErrorOffset();
		size_t i, line_start = 0, context_start = 0;
		int num_line = 1;
		for ( i = 0; (i < off) && str[i]; i++ )
		{
			if ( str[i] == '\n' )
			{ line_start = i+1; context_start = i+1; num_line++; }
			if ( str[i] == '{' || str[i] == '[' )
			{ context_start = i; }
		}
		for ( i = context_start; str[i]; i++ )
		{
			if ( str[i] == '\n' || str[i] == '\r' ) break;
			context += str[i];
			if ( str[i] == '}' || str[i] == ']' ) break;
		}
		throw ConnectedVision::runtime_error( std::string("parse error of JSON Object: ") + rapidjson::GetParseError_En(document.GetParseError()) + std::string(" at line ") + ConnectedVision::intToStr( num_line ) + ": " + context);
	}

	parseJson(document);
}

// --> Do NOT EDIT <--
void Stub_generic_status_qualityOfService::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// compuationDuration
	if ((value.HasMember("compuationDuration")) && value["compuationDuration"].IsInt64())
	{
		set_compuationDuration( value["compuationDuration"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'compuationDuration'");

	// compuationDurationAverage
	if ((value.HasMember("compuationDurationAverage")) && value["compuationDurationAverage"].IsInt64())
	{
		set_compuationDurationAverage( value["compuationDurationAverage"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'compuationDurationAverage'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_status_qualityOfService::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_status_qualityOfService::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_status_qualityOfService::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // compuationDuration
		node.AddMember("compuationDuration", rapidjson::Value().SetInt64( get_compuationDuration() ), allocator);
	}
	{ // compuationDurationAverage
		node.AddMember("compuationDurationAverage", rapidjson::Value().SetInt64( get_compuationDurationAverage() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status_qualityOfService::get_compuationDuration() const
{
	return( this->compuationDuration );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status_qualityOfService::getconst_compuationDuration() const
{
	return( this->compuationDuration );
}

// --> Do NOT EDIT <--
void Stub_generic_status_qualityOfService::set_compuationDuration(ConnectedVision::timestamp_t value)
{
	this->compuationDuration = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status_qualityOfService::get_compuationDurationAverage() const
{
	return( this->compuationDurationAverage );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status_qualityOfService::getconst_compuationDurationAverage() const
{
	return( this->compuationDurationAverage );
}

// --> Do NOT EDIT <--
void Stub_generic_status_qualityOfService::set_compuationDurationAverage(ConnectedVision::timestamp_t value)
{
	this->compuationDurationAverage = value;
}


} // namespace ConnectedVision