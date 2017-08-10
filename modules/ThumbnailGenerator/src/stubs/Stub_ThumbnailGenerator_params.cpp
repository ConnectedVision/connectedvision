// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ThumbnailGenerator_params.h"
#include "../Class_ThumbnailGenerator_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

const boost::shared_ptr<std::string> Stub_ThumbnailGenerator_params::imageFormat_JPEG = boost::make_shared<std::string>("JPEG");
const boost::shared_ptr<std::string> Stub_ThumbnailGenerator_params::imageFormat_PNG = boost::make_shared<std::string>("PNG");



// --> Do NOT EDIT <--
/* copy constructors */
Stub_ThumbnailGenerator_params::Stub_ThumbnailGenerator_params(const Stub_ThumbnailGenerator_params& other)
{
	// TODO: other.readLock
	// imageFormat
	if ( other.imageFormat ) 
		imageFormat = boost::make_shared<std::string>(*other.imageFormat);
	// lineWidth
	lineWidth = other.lineWidth;
	// lineColor
	if ( other.lineColor ) 
		lineColor = boost::make_shared<Class_ThumbnailGenerator_params_lineColor>(*other.lineColor);
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ThumbnailGenerator_params& Stub_ThumbnailGenerator_params::operator =(const Stub_ThumbnailGenerator_params& other)
{
	Stub_ThumbnailGenerator_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ThumbnailGenerator_params& Stub_ThumbnailGenerator_params::operator =(Stub_ThumbnailGenerator_params&& other) noexcept
{
	// imageFormat
    std::swap(imageFormat, other.imageFormat);
	// lineWidth
    std::swap(lineWidth, other.lineWidth);
	// lineColor
    std::swap(lineColor, other.lineColor);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ThumbnailGenerator_params::Stub_ThumbnailGenerator_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_params::Stub_ThumbnailGenerator_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_params::Stub_ThumbnailGenerator_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_params::~Stub_ThumbnailGenerator_params()
{
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::clear()
{
	this->imageFormat.reset( new std::string("JPEG") );
	this->lineWidth = static_cast<int64_t>(3);
	this->lineColor.reset( new Class_ThumbnailGenerator_params_lineColor );
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::parseJson(const char *str)
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
void Stub_ThumbnailGenerator_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// imageFormat
	if ((value.HasMember("imageFormat")) && value["imageFormat"].IsString())
	{
		set_imageFormat( boost::shared_ptr<std::string>( new std::string( value["imageFormat"].GetString() ) ) );
	}
	// lineWidth
	if ((value.HasMember("lineWidth")) && value["lineWidth"].IsInt64())
	{
		set_lineWidth( value["lineWidth"].GetInt64() );
	}
	// lineColor
	if ((value.HasMember("lineColor")) && value["lineColor"].IsObject())
	{
		set_lineColor( boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor>( new Class_ThumbnailGenerator_params_lineColor( value["lineColor"] ) ) );
	}
}

// --> Do NOT EDIT <--
std::string Stub_ThumbnailGenerator_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ThumbnailGenerator_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ThumbnailGenerator_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // imageFormat
		node.AddMember("imageFormat", rapidjson::Value().SetString( get_imageFormat()->c_str(), allocator), allocator);
	}
	{ // lineWidth
		node.AddMember("lineWidth", rapidjson::Value().SetInt64( get_lineWidth() ), allocator);
	}
	{ // lineColor
		node.AddMember("lineColor", get_lineColor()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ThumbnailGenerator_params::get_imageFormat() const
{
	return( this->imageFormat );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ThumbnailGenerator_params::getconst_imageFormat() const
{
	return( boost::static_pointer_cast<const std::string>(this->imageFormat) );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::set_imageFormat(boost::shared_ptr<std::string> value)
{
	this->imageFormat = value;
}

// --> Do NOT EDIT <--
bool Stub_ThumbnailGenerator_params::is_imageFormat(const boost::shared_ptr<std::string> &value) const
{
	return ( (*this->imageFormat) == (*value) );
}

// --> Do NOT EDIT <--
int64_t Stub_ThumbnailGenerator_params::get_lineWidth() const
{
	return( this->lineWidth );
}

// --> Do NOT EDIT <--
const int64_t Stub_ThumbnailGenerator_params::getconst_lineWidth() const
{
	return( this->lineWidth );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::set_lineWidth(int64_t value)
{
	this->lineWidth = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor> Stub_ThumbnailGenerator_params::get_lineColor() const
{
	return( this->lineColor );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_ThumbnailGenerator_params_lineColor> Stub_ThumbnailGenerator_params::getconst_lineColor() const
{
	return( boost::static_pointer_cast<const Class_ThumbnailGenerator_params_lineColor>(this->lineColor) );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::set_lineColor(boost::shared_ptr<Class_ThumbnailGenerator_params_lineColor> value)
{
	this->lineColor = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ThumbnailGenerator_params::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_ThumbnailGenerator_params::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_ThumbnailGenerator_params::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_ThumbnailGenerator_params::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision