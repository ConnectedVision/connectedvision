// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_input_BoundingBox.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ThumbnailGenerator_input_BoundingBox.h"
#include "../Class_ThumbnailGenerator_input_BoundingBox.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_ThumbnailGenerator_input_BoundingBox::Stub_ThumbnailGenerator_input_BoundingBox(const Stub_ThumbnailGenerator_input_BoundingBox& other)
{
	// TODO: other.readLock
	// id
	id = other.id;
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
	// boundingBox
	if ( other.boundingBox ) 
		boundingBox = boost::make_shared<Class_ThumbnailGenerator_input_BoundingBox_boundingBox>(*other.boundingBox);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ThumbnailGenerator_input_BoundingBox& Stub_ThumbnailGenerator_input_BoundingBox::operator =(const Stub_ThumbnailGenerator_input_BoundingBox& other)
{
	Stub_ThumbnailGenerator_input_BoundingBox tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ThumbnailGenerator_input_BoundingBox& Stub_ThumbnailGenerator_input_BoundingBox::operator =(Stub_ThumbnailGenerator_input_BoundingBox&& other) noexcept
{
	// id
    std::swap(id, other.id);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// boundingBox
    std::swap(boundingBox, other.boundingBox);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ThumbnailGenerator_input_BoundingBox::Stub_ThumbnailGenerator_input_BoundingBox()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_input_BoundingBox::Stub_ThumbnailGenerator_input_BoundingBox(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_input_BoundingBox::Stub_ThumbnailGenerator_input_BoundingBox(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_input_BoundingBox::~Stub_ThumbnailGenerator_input_BoundingBox()
{
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_input_BoundingBox::clear()
{
	this->id = "";
	this->configID = "";
	this->timestamp = 0;
	this->boundingBox.reset( new Class_ThumbnailGenerator_input_BoundingBox_boundingBox );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_input_BoundingBox::parseJson(const char *str)
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
void Stub_ThumbnailGenerator_input_BoundingBox::parseJson(const rapidjson::Value& value)
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

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestamp'");

	// boundingBox
	if ((value.HasMember("boundingBox")) && value["boundingBox"].IsObject())
	{
		set_boundingBox( boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox>( new Class_ThumbnailGenerator_input_BoundingBox_boundingBox( value["boundingBox"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'boundingBox'");

}

// --> Do NOT EDIT <--
std::string Stub_ThumbnailGenerator_input_BoundingBox::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ThumbnailGenerator_input_BoundingBox::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ThumbnailGenerator_input_BoundingBox::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_id() ), allocator), allocator);
	}
	{ // configID
		node.AddMember("configID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_configID() ), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // boundingBox
		node.AddMember("boundingBox", get_boundingBox()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ThumbnailGenerator_input_BoundingBox::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_ThumbnailGenerator_input_BoundingBox::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_input_BoundingBox::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ThumbnailGenerator_input_BoundingBox::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_ThumbnailGenerator_input_BoundingBox::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_input_BoundingBox::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_ThumbnailGenerator_input_BoundingBox::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_ThumbnailGenerator_input_BoundingBox::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_input_BoundingBox::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> Stub_ThumbnailGenerator_input_BoundingBox::get_boundingBox() const
{
	return( this->boundingBox );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_ThumbnailGenerator_input_BoundingBox_boundingBox> Stub_ThumbnailGenerator_input_BoundingBox::getconst_boundingBox() const
{
	return( boost::static_pointer_cast<const Class_ThumbnailGenerator_input_BoundingBox_boundingBox>(this->boundingBox) );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_input_BoundingBox::set_boundingBox(boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> value)
{
	this->boundingBox = value;
}


} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision