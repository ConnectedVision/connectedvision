/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_aliasID.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_config_aliasID.h"
#include "../Class_generic_config_aliasID.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_config_aliasID::Stub_generic_config_aliasID(const Stub_generic_config_aliasID& other)
{
	// TODO: other.readLock
	// id
	if ( other.id ) 
		id = boost::make_shared<std::string>(*other.id);
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_config_aliasID& Stub_generic_config_aliasID::operator =(const Stub_generic_config_aliasID& other)
{
	Stub_generic_config_aliasID tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_config_aliasID& Stub_generic_config_aliasID::operator =(Stub_generic_config_aliasID&& other) noexcept
{
	// id
    std::swap(id, other.id);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_config_aliasID::Stub_generic_config_aliasID()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_config_aliasID::Stub_generic_config_aliasID(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_config_aliasID::Stub_generic_config_aliasID(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_config_aliasID::~Stub_generic_config_aliasID()
{
}

// --> Do NOT EDIT <--
void Stub_generic_config_aliasID::clear()
{
	this->id.reset( new std::string("") );
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_generic_config_aliasID::parseJson(const char *str)
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
void Stub_generic_config_aliasID::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// id
	if ((value.HasMember("id")) && value["id"].IsString())
	{
		set_id( boost::shared_ptr<std::string>( new std::string( value["id"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'id'");

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_aliasID::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_aliasID::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_config_aliasID::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( get_id()->c_str(), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config_aliasID::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config_aliasID::getconst_id() const
{
	return( boost::static_pointer_cast<const std::string>(this->id) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_aliasID::set_id(boost::shared_ptr<std::string> value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_config_aliasID::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_config_aliasID::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_generic_config_aliasID::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace ConnectedVision