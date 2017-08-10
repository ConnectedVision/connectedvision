// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_VideoImporter_output_VideoMetadata.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_VideoImporter_output_VideoMetadata.h"
#include "../Class_VideoImporter_output_VideoMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace VideoImporter {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_VideoImporter_output_VideoMetadata::Stub_VideoImporter_output_VideoMetadata(const Stub_VideoImporter_output_VideoMetadata& other)
{
	// TODO: other.readLock
	// id
	id = other.id;
	// configID
	configID = other.configID;
	// filename
	if ( other.filename ) 
		filename = boost::make_shared<std::string>(*other.filename);
	// timestamp
	timestamp = other.timestamp;
	// lasttimestamp
	lasttimestamp = other.lasttimestamp;
	// width
	width = other.width;
	// height
	height = other.height;
	// numberofframes
	numberofframes = other.numberofframes;
	// fps
	fps = other.fps;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_VideoImporter_output_VideoMetadata& Stub_VideoImporter_output_VideoMetadata::operator =(const Stub_VideoImporter_output_VideoMetadata& other)
{
	Stub_VideoImporter_output_VideoMetadata tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_VideoImporter_output_VideoMetadata& Stub_VideoImporter_output_VideoMetadata::operator =(Stub_VideoImporter_output_VideoMetadata&& other) noexcept
{
	// id
    std::swap(id, other.id);
	// configID
    std::swap(configID, other.configID);
	// filename
    std::swap(filename, other.filename);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// lasttimestamp
    std::swap(lasttimestamp, other.lasttimestamp);
	// width
    std::swap(width, other.width);
	// height
    std::swap(height, other.height);
	// numberofframes
    std::swap(numberofframes, other.numberofframes);
	// fps
    std::swap(fps, other.fps);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_VideoImporter_output_VideoMetadata::Stub_VideoImporter_output_VideoMetadata()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_VideoImporter_output_VideoMetadata::Stub_VideoImporter_output_VideoMetadata(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_VideoImporter_output_VideoMetadata::Stub_VideoImporter_output_VideoMetadata(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_VideoImporter_output_VideoMetadata::~Stub_VideoImporter_output_VideoMetadata()
{
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::clear()
{
	this->id = "";
	this->configID = "";
	this->filename.reset( new std::string("") );
	this->timestamp = 0;
	this->lasttimestamp = 0;
	this->width = static_cast<int64_t>(0);
	this->height = static_cast<int64_t>(0);
	this->numberofframes = static_cast<int64_t>(0);
	this->fps = static_cast<double>(0.0);
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::parseJson(const char *str)
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
void Stub_VideoImporter_output_VideoMetadata::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// id
	if ((value.HasMember("id")) && value["id"].IsString())
	{
		set_id( ConnectedVision::strToID( value["id"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'id'");

	// configID
	if ((value.HasMember("configID")) && value["configID"].IsString())
	{
		set_configID( ConnectedVision::strToID( value["configID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'configID'");

	// filename
	if ((value.HasMember("filename")) && value["filename"].IsString())
	{
		set_filename( boost::shared_ptr<std::string>( new std::string( value["filename"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'filename'");

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestamp'");

	// lasttimestamp
	if ((value.HasMember("lasttimestamp")) && value["lasttimestamp"].IsInt64())
	{
		set_lasttimestamp( value["lasttimestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'lasttimestamp'");

	// width
	if ((value.HasMember("width")) && value["width"].IsInt64())
	{
		set_width( value["width"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'width'");

	// height
	if ((value.HasMember("height")) && value["height"].IsInt64())
	{
		set_height( value["height"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'height'");

	// numberofframes
	if ((value.HasMember("numberofframes")) && value["numberofframes"].IsInt64())
	{
		set_numberofframes( value["numberofframes"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'numberofframes'");

	// fps
	if ((value.HasMember("fps")) && value["fps"].IsNumber())
	{
		set_fps( value["fps"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'fps'");

}

// --> Do NOT EDIT <--
std::string Stub_VideoImporter_output_VideoMetadata::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_VideoImporter_output_VideoMetadata::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_VideoImporter_output_VideoMetadata::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_id() ), allocator), allocator);
	}
	{ // configID
		node.AddMember("configID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_configID() ), allocator), allocator);
	}
	{ // filename
		node.AddMember("filename", rapidjson::Value().SetString( get_filename()->c_str(), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // lasttimestamp
		node.AddMember("lasttimestamp", rapidjson::Value().SetInt64( get_lasttimestamp() ), allocator);
	}
	{ // width
		node.AddMember("width", rapidjson::Value().SetInt64( get_width() ), allocator);
	}
	{ // height
		node.AddMember("height", rapidjson::Value().SetInt64( get_height() ), allocator);
	}
	{ // numberofframes
		node.AddMember("numberofframes", rapidjson::Value().SetInt64( get_numberofframes() ), allocator);
	}
	{ // fps
		node.AddMember("fps", rapidjson::Value().SetDouble( get_fps() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_VideoImporter_output_VideoMetadata::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_VideoImporter_output_VideoMetadata::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_VideoImporter_output_VideoMetadata::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_VideoImporter_output_VideoMetadata::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_VideoImporter_output_VideoMetadata::get_filename() const
{
	return( this->filename );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_VideoImporter_output_VideoMetadata::getconst_filename() const
{
	return( boost::static_pointer_cast<const std::string>(this->filename) );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_filename(boost::shared_ptr<std::string> value)
{
	this->filename = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_VideoImporter_output_VideoMetadata::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_VideoImporter_output_VideoMetadata::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_VideoImporter_output_VideoMetadata::get_lasttimestamp() const
{
	return( this->lasttimestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_VideoImporter_output_VideoMetadata::getconst_lasttimestamp() const
{
	return( this->lasttimestamp );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_lasttimestamp(ConnectedVision::timestamp_t value)
{
	this->lasttimestamp = value;
}

// --> Do NOT EDIT <--
int64_t Stub_VideoImporter_output_VideoMetadata::get_width() const
{
	return( this->width );
}

// --> Do NOT EDIT <--
const int64_t Stub_VideoImporter_output_VideoMetadata::getconst_width() const
{
	return( this->width );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_width(int64_t value)
{
	this->width = value;
}

// --> Do NOT EDIT <--
int64_t Stub_VideoImporter_output_VideoMetadata::get_height() const
{
	return( this->height );
}

// --> Do NOT EDIT <--
const int64_t Stub_VideoImporter_output_VideoMetadata::getconst_height() const
{
	return( this->height );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_height(int64_t value)
{
	this->height = value;
}

// --> Do NOT EDIT <--
int64_t Stub_VideoImporter_output_VideoMetadata::get_numberofframes() const
{
	return( this->numberofframes );
}

// --> Do NOT EDIT <--
const int64_t Stub_VideoImporter_output_VideoMetadata::getconst_numberofframes() const
{
	return( this->numberofframes );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_numberofframes(int64_t value)
{
	this->numberofframes = value;
}

// --> Do NOT EDIT <--
double Stub_VideoImporter_output_VideoMetadata::get_fps() const
{
	return( this->fps );
}

// --> Do NOT EDIT <--
const double Stub_VideoImporter_output_VideoMetadata::getconst_fps() const
{
	return( this->fps );
}

// --> Do NOT EDIT <--
void Stub_VideoImporter_output_VideoMetadata::set_fps(double value)
{
	this->fps = value;
}


} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision