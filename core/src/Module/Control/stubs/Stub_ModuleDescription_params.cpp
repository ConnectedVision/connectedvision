/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ModuleDescription_params.h"
#include "../Class_ModuleDescription_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {

const boost::shared_ptr<std::string> Stub_ModuleDescription_params::type_object = boost::make_shared<std::string>("object");



// --> Do NOT EDIT <--
/* copy constructors */
Stub_ModuleDescription_params::Stub_ModuleDescription_params(const Stub_ModuleDescription_params& other)
{
	// TODO: other.readLock
	// type
	if ( other.type ) 
		type = boost::make_shared<std::string>(*other.type);
	// properties
	if ( other.properties ) 
		properties = boost::make_shared<Class_ModuleDescription_params_properties>(*other.properties);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ModuleDescription_params& Stub_ModuleDescription_params::operator =(const Stub_ModuleDescription_params& other)
{
	Stub_ModuleDescription_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ModuleDescription_params& Stub_ModuleDescription_params::operator =(Stub_ModuleDescription_params&& other) noexcept
{
	// type
    std::swap(type, other.type);
	// properties
    std::swap(properties, other.properties);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ModuleDescription_params::Stub_ModuleDescription_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ModuleDescription_params::Stub_ModuleDescription_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ModuleDescription_params::Stub_ModuleDescription_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ModuleDescription_params::~Stub_ModuleDescription_params()
{
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_params::clear()
{
	this->type.reset( new std::string("") );
	this->properties.reset( new Class_ModuleDescription_params_properties );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_params::parseJson(const char *str)
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
void Stub_ModuleDescription_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// type
	if ((value.HasMember("type")) && value["type"].IsString())
	{
		set_type( boost::shared_ptr<std::string>( new std::string( value["type"].GetString() ) ) );
	}
	// properties
	if ((value.HasMember("properties")) && value["properties"].IsObject())
	{
		set_properties( boost::shared_ptr<Class_ModuleDescription_params_properties>( new Class_ModuleDescription_params_properties( value["properties"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'properties'");

}

// --> Do NOT EDIT <--
std::string Stub_ModuleDescription_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ModuleDescription_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ModuleDescription_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // type
		node.AddMember("type", rapidjson::Value().SetString( get_type()->c_str(), allocator), allocator);
	}
	{ // properties
		node.AddMember("properties", get_properties()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleDescription_params::get_type() const
{
	return( this->type );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleDescription_params::getconst_type() const
{
	return( boost::static_pointer_cast<const std::string>(this->type) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_params::set_type(boost::shared_ptr<std::string> value)
{
	this->type = value;
}

// --> Do NOT EDIT <--
bool Stub_ModuleDescription_params::is_type(const boost::shared_ptr<std::string> &value) const
{
	return ( (*this->type) == (*value) );
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_ModuleDescription_params_properties> Stub_ModuleDescription_params::get_properties() const
{
	return( this->properties );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_ModuleDescription_params_properties> Stub_ModuleDescription_params::getconst_properties() const
{
	return( boost::static_pointer_cast<const Class_ModuleDescription_params_properties>(this->properties) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_params::set_properties(boost::shared_ptr<Class_ModuleDescription_params_properties> value)
{
	this->properties = value;
}


} // namespace ConnectedVision