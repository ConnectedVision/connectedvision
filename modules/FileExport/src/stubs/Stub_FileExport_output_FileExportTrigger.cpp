// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_FileExport_output_FileExportTrigger.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_FileExport_output_FileExportTrigger.h"
#include "../Class_FileExport_output_FileExportTrigger.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace FileExport {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_FileExport_output_FileExportTrigger::Stub_FileExport_output_FileExportTrigger(const Stub_FileExport_output_FileExportTrigger& other)
{
	// TODO: other.readLock
	// timestamp
	timestamp = other.timestamp;
	// configID
	configID = other.configID;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_FileExport_output_FileExportTrigger& Stub_FileExport_output_FileExportTrigger::operator =(const Stub_FileExport_output_FileExportTrigger& other)
{
	Stub_FileExport_output_FileExportTrigger tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_FileExport_output_FileExportTrigger& Stub_FileExport_output_FileExportTrigger::operator =(Stub_FileExport_output_FileExportTrigger&& other) noexcept
{
	// timestamp
    std::swap(timestamp, other.timestamp);
	// configID
    std::swap(configID, other.configID);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_FileExport_output_FileExportTrigger::Stub_FileExport_output_FileExportTrigger()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_FileExport_output_FileExportTrigger::Stub_FileExport_output_FileExportTrigger(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_FileExport_output_FileExportTrigger::Stub_FileExport_output_FileExportTrigger(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_FileExport_output_FileExportTrigger::~Stub_FileExport_output_FileExportTrigger()
{
}

// --> Do NOT EDIT <--
void Stub_FileExport_output_FileExportTrigger::clear()
{
	this->timestamp = 0;
	this->configID = "";
}

// --> Do NOT EDIT <--
void Stub_FileExport_output_FileExportTrigger::parseJson(const char *str)
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
void Stub_FileExport_output_FileExportTrigger::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestamp'");

}

// --> Do NOT EDIT <--
std::string Stub_FileExport_output_FileExportTrigger::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_FileExport_output_FileExportTrigger::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_FileExport_output_FileExportTrigger::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_FileExport_output_FileExportTrigger::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_FileExport_output_FileExportTrigger::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_FileExport_output_FileExportTrigger::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_FileExport_output_FileExportTrigger::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_FileExport_output_FileExportTrigger::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_FileExport_output_FileExportTrigger::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}


} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision