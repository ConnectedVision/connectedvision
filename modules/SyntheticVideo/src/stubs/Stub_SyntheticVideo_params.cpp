// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_SyntheticVideo_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_SyntheticVideo_params.h"
#include "../Class_SyntheticVideo_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_SyntheticVideo_params::Stub_SyntheticVideo_params(const Stub_SyntheticVideo_params& other)
{
	// TODO: other.readLock
	// recordingDateTime
	recordingDateTime = other.recordingDateTime;
	// numberOfFrames
	numberOfFrames = other.numberOfFrames;
	// height
	height = other.height;
	// width
	width = other.width;
	// fps
	fps = other.fps;
	// sizeOfObject
	sizeOfObject = other.sizeOfObject;
	// bgColor
	if ( other.bgColor ) 
		bgColor = boost::make_shared<Class_SyntheticVideo_params_bgColor>(*other.bgColor);
	// fgColor
	if ( other.fgColor ) 
		fgColor = boost::make_shared<Class_SyntheticVideo_params_fgColor>(*other.fgColor);
	// osdTextColor
	if ( other.osdTextColor ) 
		osdTextColor = boost::make_shared<Class_SyntheticVideo_params_osdTextColor>(*other.osdTextColor);
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_SyntheticVideo_params& Stub_SyntheticVideo_params::operator =(const Stub_SyntheticVideo_params& other)
{
	Stub_SyntheticVideo_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_SyntheticVideo_params& Stub_SyntheticVideo_params::operator =(Stub_SyntheticVideo_params&& other) noexcept
{
	// recordingDateTime
    std::swap(recordingDateTime, other.recordingDateTime);
	// numberOfFrames
    std::swap(numberOfFrames, other.numberOfFrames);
	// height
    std::swap(height, other.height);
	// width
    std::swap(width, other.width);
	// fps
    std::swap(fps, other.fps);
	// sizeOfObject
    std::swap(sizeOfObject, other.sizeOfObject);
	// bgColor
    std::swap(bgColor, other.bgColor);
	// fgColor
    std::swap(fgColor, other.fgColor);
	// osdTextColor
    std::swap(osdTextColor, other.osdTextColor);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_SyntheticVideo_params::Stub_SyntheticVideo_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_SyntheticVideo_params::Stub_SyntheticVideo_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_SyntheticVideo_params::Stub_SyntheticVideo_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_SyntheticVideo_params::~Stub_SyntheticVideo_params()
{
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::clear()
{
	this->recordingDateTime = 0;
	this->numberOfFrames = static_cast<double>(0.0);
	this->height = static_cast<double>(0.0);
	this->width = static_cast<double>(0.0);
	this->fps = static_cast<double>(0.0);
	this->sizeOfObject = static_cast<double>(0.0);
	this->bgColor.reset( new Class_SyntheticVideo_params_bgColor );
	this->fgColor.reset( new Class_SyntheticVideo_params_fgColor );
	this->osdTextColor.reset( new Class_SyntheticVideo_params_osdTextColor );
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::parseJson(const char *str)
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
void Stub_SyntheticVideo_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// recordingDateTime
	if ((value.HasMember("recordingDateTime")) && value["recordingDateTime"].IsInt64())
	{
		set_recordingDateTime( value["recordingDateTime"].GetInt64() );
	}
	// numberOfFrames
	if ((value.HasMember("numberOfFrames")) && value["numberOfFrames"].IsNumber())
	{
		set_numberOfFrames( value["numberOfFrames"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'numberOfFrames'");

	// height
	if ((value.HasMember("height")) && value["height"].IsNumber())
	{
		set_height( value["height"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'height'");

	// width
	if ((value.HasMember("width")) && value["width"].IsNumber())
	{
		set_width( value["width"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'width'");

	// fps
	if ((value.HasMember("fps")) && value["fps"].IsNumber())
	{
		set_fps( value["fps"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'fps'");

	// sizeOfObject
	if ((value.HasMember("sizeOfObject")) && value["sizeOfObject"].IsNumber())
	{
		set_sizeOfObject( value["sizeOfObject"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'sizeOfObject'");

	// bgColor
	if ((value.HasMember("bgColor")) && value["bgColor"].IsObject())
	{
		set_bgColor( boost::shared_ptr<Class_SyntheticVideo_params_bgColor>( new Class_SyntheticVideo_params_bgColor( value["bgColor"] ) ) );
	}
	// fgColor
	if ((value.HasMember("fgColor")) && value["fgColor"].IsObject())
	{
		set_fgColor( boost::shared_ptr<Class_SyntheticVideo_params_fgColor>( new Class_SyntheticVideo_params_fgColor( value["fgColor"] ) ) );
	}
	// osdTextColor
	if ((value.HasMember("osdTextColor")) && value["osdTextColor"].IsObject())
	{
		set_osdTextColor( boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor>( new Class_SyntheticVideo_params_osdTextColor( value["osdTextColor"] ) ) );
	}
}

// --> Do NOT EDIT <--
std::string Stub_SyntheticVideo_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_SyntheticVideo_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_SyntheticVideo_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // recordingDateTime
		node.AddMember("recordingDateTime", rapidjson::Value().SetInt64( get_recordingDateTime() ), allocator);
	}
	{ // numberOfFrames
		node.AddMember("numberOfFrames", rapidjson::Value().SetDouble( get_numberOfFrames() ), allocator);
	}
	{ // height
		node.AddMember("height", rapidjson::Value().SetDouble( get_height() ), allocator);
	}
	{ // width
		node.AddMember("width", rapidjson::Value().SetDouble( get_width() ), allocator);
	}
	{ // fps
		node.AddMember("fps", rapidjson::Value().SetDouble( get_fps() ), allocator);
	}
	{ // sizeOfObject
		node.AddMember("sizeOfObject", rapidjson::Value().SetDouble( get_sizeOfObject() ), allocator);
	}
	{ // bgColor
		node.AddMember("bgColor", get_bgColor()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // fgColor
		node.AddMember("fgColor", get_fgColor()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // osdTextColor
		node.AddMember("osdTextColor", get_osdTextColor()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_SyntheticVideo_params::get_recordingDateTime() const
{
	return( this->recordingDateTime );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_SyntheticVideo_params::getconst_recordingDateTime() const
{
	return( this->recordingDateTime );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_recordingDateTime(ConnectedVision::timestamp_t value)
{
	this->recordingDateTime = value;
}

// --> Do NOT EDIT <--
double Stub_SyntheticVideo_params::get_numberOfFrames() const
{
	return( this->numberOfFrames );
}

// --> Do NOT EDIT <--
const double Stub_SyntheticVideo_params::getconst_numberOfFrames() const
{
	return( this->numberOfFrames );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_numberOfFrames(double value)
{
	this->numberOfFrames = value;
}

// --> Do NOT EDIT <--
double Stub_SyntheticVideo_params::get_height() const
{
	return( this->height );
}

// --> Do NOT EDIT <--
const double Stub_SyntheticVideo_params::getconst_height() const
{
	return( this->height );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_height(double value)
{
	this->height = value;
}

// --> Do NOT EDIT <--
double Stub_SyntheticVideo_params::get_width() const
{
	return( this->width );
}

// --> Do NOT EDIT <--
const double Stub_SyntheticVideo_params::getconst_width() const
{
	return( this->width );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_width(double value)
{
	this->width = value;
}

// --> Do NOT EDIT <--
double Stub_SyntheticVideo_params::get_fps() const
{
	return( this->fps );
}

// --> Do NOT EDIT <--
const double Stub_SyntheticVideo_params::getconst_fps() const
{
	return( this->fps );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_fps(double value)
{
	this->fps = value;
}

// --> Do NOT EDIT <--
double Stub_SyntheticVideo_params::get_sizeOfObject() const
{
	return( this->sizeOfObject );
}

// --> Do NOT EDIT <--
const double Stub_SyntheticVideo_params::getconst_sizeOfObject() const
{
	return( this->sizeOfObject );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_sizeOfObject(double value)
{
	this->sizeOfObject = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_SyntheticVideo_params_bgColor> Stub_SyntheticVideo_params::get_bgColor() const
{
	return( this->bgColor );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_SyntheticVideo_params_bgColor> Stub_SyntheticVideo_params::getconst_bgColor() const
{
	return( boost::static_pointer_cast<const Class_SyntheticVideo_params_bgColor>(this->bgColor) );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_bgColor(boost::shared_ptr<Class_SyntheticVideo_params_bgColor> value)
{
	this->bgColor = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_SyntheticVideo_params_fgColor> Stub_SyntheticVideo_params::get_fgColor() const
{
	return( this->fgColor );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_SyntheticVideo_params_fgColor> Stub_SyntheticVideo_params::getconst_fgColor() const
{
	return( boost::static_pointer_cast<const Class_SyntheticVideo_params_fgColor>(this->fgColor) );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_fgColor(boost::shared_ptr<Class_SyntheticVideo_params_fgColor> value)
{
	this->fgColor = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor> Stub_SyntheticVideo_params::get_osdTextColor() const
{
	return( this->osdTextColor );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_SyntheticVideo_params_osdTextColor> Stub_SyntheticVideo_params::getconst_osdTextColor() const
{
	return( boost::static_pointer_cast<const Class_SyntheticVideo_params_osdTextColor>(this->osdTextColor) );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_osdTextColor(boost::shared_ptr<Class_SyntheticVideo_params_osdTextColor> value)
{
	this->osdTextColor = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_SyntheticVideo_params::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_SyntheticVideo_params::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_SyntheticVideo_params::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_SyntheticVideo_params::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_SyntheticVideo_params::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision