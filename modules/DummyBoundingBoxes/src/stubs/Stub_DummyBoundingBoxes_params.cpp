// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_DummyBoundingBoxes_params.h"
#include "../Class_DummyBoundingBoxes_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_DummyBoundingBoxes_params::Stub_DummyBoundingBoxes_params(const Stub_DummyBoundingBoxes_params& other)
{
	// TODO: other.readLock
	// count
	count = other.count;
	// boundingBoxStart
	if ( other.boundingBoxStart ) 
		boundingBoxStart = boost::make_shared<Class_DummyBoundingBoxes_params_boundingBoxStart>(*other.boundingBoxStart);
	// timestampStart
	timestampStart = other.timestampStart;
	// boundingBoxEnd
	if ( other.boundingBoxEnd ) 
		boundingBoxEnd = boost::make_shared<Class_DummyBoundingBoxes_params_boundingBoxEnd>(*other.boundingBoxEnd);
	// timestampEnd
	timestampEnd = other.timestampEnd;
	// delay
	delay = other.delay;
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_DummyBoundingBoxes_params& Stub_DummyBoundingBoxes_params::operator =(const Stub_DummyBoundingBoxes_params& other)
{
	Stub_DummyBoundingBoxes_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_DummyBoundingBoxes_params& Stub_DummyBoundingBoxes_params::operator =(Stub_DummyBoundingBoxes_params&& other) noexcept
{
	// count
    std::swap(count, other.count);
	// boundingBoxStart
    std::swap(boundingBoxStart, other.boundingBoxStart);
	// timestampStart
    std::swap(timestampStart, other.timestampStart);
	// boundingBoxEnd
    std::swap(boundingBoxEnd, other.boundingBoxEnd);
	// timestampEnd
    std::swap(timestampEnd, other.timestampEnd);
	// delay
    std::swap(delay, other.delay);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_DummyBoundingBoxes_params::Stub_DummyBoundingBoxes_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_params::Stub_DummyBoundingBoxes_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_params::Stub_DummyBoundingBoxes_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_params::~Stub_DummyBoundingBoxes_params()
{
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::clear()
{
	this->count = static_cast<int64_t>(0);
	this->boundingBoxStart.reset( new Class_DummyBoundingBoxes_params_boundingBoxStart );
	this->timestampStart = 0;
	this->boundingBoxEnd.reset( new Class_DummyBoundingBoxes_params_boundingBoxEnd );
	this->timestampEnd = 0;
	this->delay = static_cast<int64_t>(0);
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::parseJson(const char *str)
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
void Stub_DummyBoundingBoxes_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// count
	if ((value.HasMember("count")) && value["count"].IsInt64())
	{
		set_count( value["count"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'count'");

	// boundingBoxStart
	if ((value.HasMember("boundingBoxStart")) && value["boundingBoxStart"].IsObject())
	{
		set_boundingBoxStart( boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart>( new Class_DummyBoundingBoxes_params_boundingBoxStart( value["boundingBoxStart"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'boundingBoxStart'");

	// timestampStart
	if ((value.HasMember("timestampStart")) && value["timestampStart"].IsInt64())
	{
		set_timestampStart( value["timestampStart"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestampStart'");

	// boundingBoxEnd
	if ((value.HasMember("boundingBoxEnd")) && value["boundingBoxEnd"].IsObject())
	{
		set_boundingBoxEnd( boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd>( new Class_DummyBoundingBoxes_params_boundingBoxEnd( value["boundingBoxEnd"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'boundingBoxEnd'");

	// timestampEnd
	if ((value.HasMember("timestampEnd")) && value["timestampEnd"].IsInt64())
	{
		set_timestampEnd( value["timestampEnd"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestampEnd'");

	// delay
	if ((value.HasMember("delay")) && value["delay"].IsInt64())
	{
		set_delay( value["delay"].GetInt64() );
	}
}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_DummyBoundingBoxes_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // count
		node.AddMember("count", rapidjson::Value().SetInt64( get_count() ), allocator);
	}
	{ // boundingBoxStart
		node.AddMember("boundingBoxStart", get_boundingBoxStart()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // timestampStart
		node.AddMember("timestampStart", rapidjson::Value().SetInt64( get_timestampStart() ), allocator);
	}
	{ // boundingBoxEnd
		node.AddMember("boundingBoxEnd", get_boundingBoxEnd()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // timestampEnd
		node.AddMember("timestampEnd", rapidjson::Value().SetInt64( get_timestampEnd() ), allocator);
	}
	{ // delay
		node.AddMember("delay", rapidjson::Value().SetInt64( get_delay() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
int64_t Stub_DummyBoundingBoxes_params::get_count() const
{
	return( this->count );
}

// --> Do NOT EDIT <--
const int64_t Stub_DummyBoundingBoxes_params::getconst_count() const
{
	return( this->count );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_count(int64_t value)
{
	this->count = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> Stub_DummyBoundingBoxes_params::get_boundingBoxStart() const
{
	return( this->boundingBoxStart );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_DummyBoundingBoxes_params_boundingBoxStart> Stub_DummyBoundingBoxes_params::getconst_boundingBoxStart() const
{
	return( boost::static_pointer_cast<const Class_DummyBoundingBoxes_params_boundingBoxStart>(this->boundingBoxStart) );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_boundingBoxStart(boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> value)
{
	this->boundingBoxStart = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_params::get_timestampStart() const
{
	return( this->timestampStart );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_params::getconst_timestampStart() const
{
	return( this->timestampStart );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_timestampStart(ConnectedVision::timestamp_t value)
{
	this->timestampStart = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd> Stub_DummyBoundingBoxes_params::get_boundingBoxEnd() const
{
	return( this->boundingBoxEnd );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_DummyBoundingBoxes_params_boundingBoxEnd> Stub_DummyBoundingBoxes_params::getconst_boundingBoxEnd() const
{
	return( boost::static_pointer_cast<const Class_DummyBoundingBoxes_params_boundingBoxEnd>(this->boundingBoxEnd) );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_boundingBoxEnd(boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd> value)
{
	this->boundingBoxEnd = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_params::get_timestampEnd() const
{
	return( this->timestampEnd );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_params::getconst_timestampEnd() const
{
	return( this->timestampEnd );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_timestampEnd(ConnectedVision::timestamp_t value)
{
	this->timestampEnd = value;
}

// --> Do NOT EDIT <--
int64_t Stub_DummyBoundingBoxes_params::get_delay() const
{
	return( this->delay );
}

// --> Do NOT EDIT <--
const int64_t Stub_DummyBoundingBoxes_params::getconst_delay() const
{
	return( this->delay );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_delay(int64_t value)
{
	this->delay = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DummyBoundingBoxes_params::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DummyBoundingBoxes_params::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_params::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_params::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_params::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision