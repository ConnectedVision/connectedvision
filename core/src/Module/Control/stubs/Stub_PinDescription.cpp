/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_PinDescription.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_PinDescription.h"
#include "../Class_PinDescription.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_PinDescription::Stub_PinDescription(const Stub_PinDescription& other)
{
	// TODO: other.readLock
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// id
	if ( other.id ) 
		id = boost::make_shared<std::string>(*other.id);
	// description
	if ( other.description ) 
		description = boost::make_shared<std::string>(*other.description);
	// type
	if ( other.type ) 
		type = boost::make_shared<std::string>(*other.type);
	// minPinCount
	minPinCount = other.minPinCount;
	// maxPinCount
	maxPinCount = other.maxPinCount;
	// properties
	if ( other.properties ) 
		properties = boost::make_shared<Class_PinDescription_properties>(*other.properties);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_PinDescription& Stub_PinDescription::operator =(const Stub_PinDescription& other)
{
	Stub_PinDescription tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_PinDescription& Stub_PinDescription::operator =(Stub_PinDescription&& other) noexcept
{
	// name
    std::swap(name, other.name);
	// id
    std::swap(id, other.id);
	// description
    std::swap(description, other.description);
	// type
    std::swap(type, other.type);
	// minPinCount
    std::swap(minPinCount, other.minPinCount);
	// maxPinCount
    std::swap(maxPinCount, other.maxPinCount);
	// properties
    std::swap(properties, other.properties);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_PinDescription::Stub_PinDescription()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_PinDescription::Stub_PinDescription(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_PinDescription::Stub_PinDescription(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_PinDescription::~Stub_PinDescription()
{
}

// --> Do NOT EDIT <--
void Stub_PinDescription::clear()
{
	this->name.reset( new std::string("") );
	this->id.reset( new std::string("") );
	this->description.reset( new std::string("") );
	this->type.reset( new std::string("application/json") );
	this->minPinCount = static_cast<int64_t>(1);
	this->maxPinCount = static_cast<int64_t>(1);
	this->properties.reset( new Class_PinDescription_properties );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::parseJson(const char *str)
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
void Stub_PinDescription::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// name
	if ((value.HasMember("name")) && value["name"].IsString())
	{
		set_name( boost::shared_ptr<std::string>( new std::string( value["name"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'name'");

	// id
	if ((value.HasMember("id")) && value["id"].IsString())
	{
		set_id( boost::shared_ptr<std::string>( new std::string( value["id"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'id'");

	// description
	if ((value.HasMember("description")) && value["description"].IsString())
	{
		set_description( boost::shared_ptr<std::string>( new std::string( value["description"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'description'");

	// type
	if ((value.HasMember("type")) && value["type"].IsString())
	{
		set_type( boost::shared_ptr<std::string>( new std::string( value["type"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'type'");

	// minPinCount
	if ((value.HasMember("minPinCount")) && value["minPinCount"].IsInt64())
	{
		set_minPinCount( value["minPinCount"].GetInt64() );
	}
	// maxPinCount
	if ((value.HasMember("maxPinCount")) && value["maxPinCount"].IsInt64())
	{
		set_maxPinCount( value["maxPinCount"].GetInt64() );
	}
	// properties
	if ((value.HasMember("properties")) && value["properties"].IsObject())
	{
		set_properties( boost::shared_ptr<Class_PinDescription_properties>( new Class_PinDescription_properties( value["properties"] ) ) );
	}
}

// --> Do NOT EDIT <--
std::string Stub_PinDescription::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_PinDescription::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_PinDescription::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( get_id()->c_str(), allocator), allocator);
	}
	{ // description
		node.AddMember("description", rapidjson::Value().SetString( get_description()->c_str(), allocator), allocator);
	}
	{ // type
		node.AddMember("type", rapidjson::Value().SetString( get_type()->c_str(), allocator), allocator);
	}
	{ // minPinCount
		node.AddMember("minPinCount", rapidjson::Value().SetInt64( get_minPinCount() ), allocator);
	}
	{ // maxPinCount
		node.AddMember("maxPinCount", rapidjson::Value().SetInt64( get_maxPinCount() ), allocator);
	}
	{ // properties
		node.AddMember("properties", get_properties()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_PinDescription::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_PinDescription::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_PinDescription::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_PinDescription::getconst_id() const
{
	return( boost::static_pointer_cast<const std::string>(this->id) );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_id(boost::shared_ptr<std::string> value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_PinDescription::get_description() const
{
	return( this->description );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_PinDescription::getconst_description() const
{
	return( boost::static_pointer_cast<const std::string>(this->description) );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_description(boost::shared_ptr<std::string> value)
{
	this->description = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_PinDescription::get_type() const
{
	return( this->type );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_PinDescription::getconst_type() const
{
	return( boost::static_pointer_cast<const std::string>(this->type) );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_type(boost::shared_ptr<std::string> value)
{
	this->type = value;
}

// --> Do NOT EDIT <--
int64_t Stub_PinDescription::get_minPinCount() const
{
	return( this->minPinCount );
}

// --> Do NOT EDIT <--
const int64_t Stub_PinDescription::getconst_minPinCount() const
{
	return( this->minPinCount );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_minPinCount(int64_t value)
{
	this->minPinCount = value;
}

// --> Do NOT EDIT <--
int64_t Stub_PinDescription::get_maxPinCount() const
{
	return( this->maxPinCount );
}

// --> Do NOT EDIT <--
const int64_t Stub_PinDescription::getconst_maxPinCount() const
{
	return( this->maxPinCount );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_maxPinCount(int64_t value)
{
	this->maxPinCount = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_PinDescription_properties> Stub_PinDescription::get_properties() const
{
	return( this->properties );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_PinDescription_properties> Stub_PinDescription::getconst_properties() const
{
	return( boost::static_pointer_cast<const Class_PinDescription_properties>(this->properties) );
}

// --> Do NOT EDIT <--
void Stub_PinDescription::set_properties(boost::shared_ptr<Class_PinDescription_properties> value)
{
	this->properties = value;
}


} // namespace ConnectedVision