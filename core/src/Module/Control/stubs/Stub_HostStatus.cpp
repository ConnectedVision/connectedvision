/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_HostStatus.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_HostStatus.h"
#include "../Class_HostStatus.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_HostStatus::Stub_HostStatus(const Stub_HostStatus& other)
{
	// TODO: other.readLock
	// hostID
	hostID = other.hostID;
	// systemID
	systemID = other.systemID;
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_HostStatus& Stub_HostStatus::operator =(const Stub_HostStatus& other)
{
	Stub_HostStatus tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_HostStatus& Stub_HostStatus::operator =(Stub_HostStatus&& other) noexcept
{
	// hostID
    std::swap(hostID, other.hostID);
	// systemID
    std::swap(systemID, other.systemID);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_HostStatus::Stub_HostStatus()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_HostStatus::Stub_HostStatus(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_HostStatus::Stub_HostStatus(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_HostStatus::~Stub_HostStatus()
{
}

// --> Do NOT EDIT <--
void Stub_HostStatus::clear()
{
	this->hostID = "";
	this->systemID = "";
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_HostStatus::parseJson(const char *str)
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
void Stub_HostStatus::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// hostID
	if ((value.HasMember("hostID")) && value["hostID"].IsString())
	{
		set_hostID( ConnectedVision::strToID( value["hostID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'hostID'");

	// systemID
	if ((value.HasMember("systemID")) && value["systemID"].IsString())
	{
		set_systemID( ConnectedVision::strToID( value["systemID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'systemID'");

}

// --> Do NOT EDIT <--
std::string Stub_HostStatus::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_HostStatus::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_HostStatus::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // hostID
		node.AddMember("hostID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_hostID() ), allocator), allocator);
	}
	{ // systemID
		node.AddMember("systemID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_systemID() ), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_HostStatus::get_hostID() const
{
	return( this->hostID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_HostStatus::getconst_hostID() const
{
	return( this->hostID );
}

// --> Do NOT EDIT <--
void Stub_HostStatus::set_hostID(ConnectedVision::id_t value)
{
	this->hostID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_HostStatus::get_systemID() const
{
	return( this->systemID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_HostStatus::getconst_systemID() const
{
	return( this->systemID );
}

// --> Do NOT EDIT <--
void Stub_HostStatus::set_systemID(ConnectedVision::id_t value)
{
	this->systemID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_HostStatus::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_HostStatus::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_HostStatus::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_HostStatus::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_HostStatus::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_HostStatus::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace ConnectedVision