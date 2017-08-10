// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_Skeleton_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_Skeleton_params.h"
#include "../Class_Skeleton_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace Skeleton {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_Skeleton_params::Stub_Skeleton_params(const Stub_Skeleton_params& other)
{
	// TODO: other.readLock
	// dummy
	dummy = other.dummy;
	// dummy_dynamic_parameter
	dummy_dynamic_parameter = other.dummy_dynamic_parameter;
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_Skeleton_params& Stub_Skeleton_params::operator =(const Stub_Skeleton_params& other)
{
	Stub_Skeleton_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_Skeleton_params& Stub_Skeleton_params::operator =(Stub_Skeleton_params&& other) noexcept
{
	// dummy
    std::swap(dummy, other.dummy);
	// dummy_dynamic_parameter
    std::swap(dummy_dynamic_parameter, other.dummy_dynamic_parameter);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_Skeleton_params::Stub_Skeleton_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_Skeleton_params::Stub_Skeleton_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_Skeleton_params::Stub_Skeleton_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_Skeleton_params::~Stub_Skeleton_params()
{
}

// --> Do NOT EDIT <--
void Stub_Skeleton_params::clear()
{
	this->dummy = static_cast<int64_t>(0);
	this->dummy_dynamic_parameter = static_cast<int64_t>(0);
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_Skeleton_params::parseJson(const char *str)
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
void Stub_Skeleton_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// dummy
	if ((value.HasMember("dummy")) && value["dummy"].IsInt64())
	{
		set_dummy( value["dummy"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'dummy'");

	// dummy_dynamic_parameter
	if ((value.HasMember("dummy_dynamic_parameter")) && value["dummy_dynamic_parameter"].IsInt64())
	{
		set_dummy_dynamic_parameter( value["dummy_dynamic_parameter"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'dummy_dynamic_parameter'");

}

// --> Do NOT EDIT <--
std::string Stub_Skeleton_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_Skeleton_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_Skeleton_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // dummy
		node.AddMember("dummy", rapidjson::Value().SetInt64( get_dummy() ), allocator);
	}
	{ // dummy_dynamic_parameter
		node.AddMember("dummy_dynamic_parameter", rapidjson::Value().SetInt64( get_dummy_dynamic_parameter() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
int64_t Stub_Skeleton_params::get_dummy() const
{
	return( this->dummy );
}

// --> Do NOT EDIT <--
const int64_t Stub_Skeleton_params::getconst_dummy() const
{
	return( this->dummy );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_params::set_dummy(int64_t value)
{
	this->dummy = value;
}

// --> Do NOT EDIT <--
int64_t Stub_Skeleton_params::get_dummy_dynamic_parameter() const
{
	return( this->dummy_dynamic_parameter );
}

// --> Do NOT EDIT <--
const int64_t Stub_Skeleton_params::getconst_dummy_dynamic_parameter() const
{
	return( this->dummy_dynamic_parameter );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_params::set_dummy_dynamic_parameter(int64_t value)
{
	this->dummy_dynamic_parameter = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_Skeleton_params::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_Skeleton_params::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_params::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_Skeleton_params::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_Skeleton_params::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_params::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace Skeleton
} // namespace Module
} // namespace ConnectedVision