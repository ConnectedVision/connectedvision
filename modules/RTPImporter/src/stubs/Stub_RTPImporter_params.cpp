// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_RTPImporter_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_RTPImporter_params.h"
#include "../Class_RTPImporter_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace RTPImporter {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_RTPImporter_params::Stub_RTPImporter_params(const Stub_RTPImporter_params& other)
{
	// TODO: other.readLock
	// url
	if ( other.url ) 
		url = boost::make_shared<std::string>(*other.url);
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_RTPImporter_params& Stub_RTPImporter_params::operator =(const Stub_RTPImporter_params& other)
{
	Stub_RTPImporter_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_RTPImporter_params& Stub_RTPImporter_params::operator =(Stub_RTPImporter_params&& other) noexcept
{
	// url
    std::swap(url, other.url);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_RTPImporter_params::Stub_RTPImporter_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_RTPImporter_params::Stub_RTPImporter_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_RTPImporter_params::Stub_RTPImporter_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_RTPImporter_params::~Stub_RTPImporter_params()
{
}

// --> Do NOT EDIT <--
void Stub_RTPImporter_params::clear()
{
	this->url.reset( new std::string("") );
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_RTPImporter_params::parseJson(const char *str)
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
void Stub_RTPImporter_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// url
	if ((value.HasMember("url")) && value["url"].IsString())
	{
		set_url( boost::shared_ptr<std::string>( new std::string( value["url"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'url'");

}

// --> Do NOT EDIT <--
std::string Stub_RTPImporter_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_RTPImporter_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_RTPImporter_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // url
		node.AddMember("url", rapidjson::Value().SetString( get_url()->c_str(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_RTPImporter_params::get_url() const
{
	return( this->url );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_RTPImporter_params::getconst_url() const
{
	return( boost::static_pointer_cast<const std::string>(this->url) );
}

// --> Do NOT EDIT <--
void Stub_RTPImporter_params::set_url(boost::shared_ptr<std::string> value)
{
	this->url = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_RTPImporter_params::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_RTPImporter_params::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_RTPImporter_params::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_RTPImporter_params::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_RTPImporter_params::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_RTPImporter_params::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision