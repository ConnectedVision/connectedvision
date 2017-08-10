/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_status_stableResults.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_status_stableResults.h"
#include "../Class_generic_status_stableResults.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_status_stableResults::Stub_generic_status_stableResults(const Stub_generic_status_stableResults& other)
{
	// TODO: other.readLock
	// pinID
	if ( other.pinID ) 
		pinID = boost::make_shared<std::string>(*other.pinID);
	// indexStart
	indexStart = other.indexStart;
	// indexEnd
	indexEnd = other.indexEnd;
	// timestampStart
	timestampStart = other.timestampStart;
	// timestampEnd
	timestampEnd = other.timestampEnd;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_status_stableResults& Stub_generic_status_stableResults::operator =(const Stub_generic_status_stableResults& other)
{
	Stub_generic_status_stableResults tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_status_stableResults& Stub_generic_status_stableResults::operator =(Stub_generic_status_stableResults&& other) noexcept
{
	// pinID
    std::swap(pinID, other.pinID);
	// indexStart
    std::swap(indexStart, other.indexStart);
	// indexEnd
    std::swap(indexEnd, other.indexEnd);
	// timestampStart
    std::swap(timestampStart, other.timestampStart);
	// timestampEnd
    std::swap(timestampEnd, other.timestampEnd);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_status_stableResults::Stub_generic_status_stableResults()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_status_stableResults::Stub_generic_status_stableResults(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_status_stableResults::Stub_generic_status_stableResults(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_status_stableResults::~Stub_generic_status_stableResults()
{
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::clear()
{
	this->pinID.reset( new std::string("") );
	this->indexStart = static_cast<int64_t>(0);
	this->indexEnd = static_cast<int64_t>(0);
	this->timestampStart = 0;
	this->timestampEnd = 0;
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::parseJson(const char *str)
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
void Stub_generic_status_stableResults::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// pinID
	if ((value.HasMember("pinID")) && value["pinID"].IsString())
	{
		set_pinID( boost::shared_ptr<std::string>( new std::string( value["pinID"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'pinID'");

	// indexStart
	if ((value.HasMember("indexStart")) && value["indexStart"].IsInt64())
	{
		set_indexStart( value["indexStart"].GetInt64() );
	}
	// indexEnd
	if ((value.HasMember("indexEnd")) && value["indexEnd"].IsInt64())
	{
		set_indexEnd( value["indexEnd"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'indexEnd'");

	// timestampStart
	if ((value.HasMember("timestampStart")) && value["timestampStart"].IsInt64())
	{
		set_timestampStart( value["timestampStart"].GetInt64() );
	}
	// timestampEnd
	if ((value.HasMember("timestampEnd")) && value["timestampEnd"].IsInt64())
	{
		set_timestampEnd( value["timestampEnd"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestampEnd'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_status_stableResults::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_status_stableResults::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_status_stableResults::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // pinID
		node.AddMember("pinID", rapidjson::Value().SetString( get_pinID()->c_str(), allocator), allocator);
	}
	{ // indexStart
		node.AddMember("indexStart", rapidjson::Value().SetInt64( get_indexStart() ), allocator);
	}
	{ // indexEnd
		node.AddMember("indexEnd", rapidjson::Value().SetInt64( get_indexEnd() ), allocator);
	}
	{ // timestampStart
		node.AddMember("timestampStart", rapidjson::Value().SetInt64( get_timestampStart() ), allocator);
	}
	{ // timestampEnd
		node.AddMember("timestampEnd", rapidjson::Value().SetInt64( get_timestampEnd() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_status_stableResults::get_pinID() const
{
	return( this->pinID );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_status_stableResults::getconst_pinID() const
{
	return( boost::static_pointer_cast<const std::string>(this->pinID) );
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::set_pinID(boost::shared_ptr<std::string> value)
{
	this->pinID = value;
}

// --> Do NOT EDIT <--
int64_t Stub_generic_status_stableResults::get_indexStart() const
{
	return( this->indexStart );
}

// --> Do NOT EDIT <--
const int64_t Stub_generic_status_stableResults::getconst_indexStart() const
{
	return( this->indexStart );
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::set_indexStart(int64_t value)
{
	this->indexStart = value;
}

// --> Do NOT EDIT <--
int64_t Stub_generic_status_stableResults::get_indexEnd() const
{
	return( this->indexEnd );
}

// --> Do NOT EDIT <--
const int64_t Stub_generic_status_stableResults::getconst_indexEnd() const
{
	return( this->indexEnd );
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::set_indexEnd(int64_t value)
{
	this->indexEnd = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status_stableResults::get_timestampStart() const
{
	return( this->timestampStart );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status_stableResults::getconst_timestampStart() const
{
	return( this->timestampStart );
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::set_timestampStart(ConnectedVision::timestamp_t value)
{
	this->timestampStart = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status_stableResults::get_timestampEnd() const
{
	return( this->timestampEnd );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status_stableResults::getconst_timestampEnd() const
{
	return( this->timestampEnd );
}

// --> Do NOT EDIT <--
void Stub_generic_status_stableResults::set_timestampEnd(ConnectedVision::timestamp_t value)
{
	this->timestampEnd = value;
}


} // namespace ConnectedVision