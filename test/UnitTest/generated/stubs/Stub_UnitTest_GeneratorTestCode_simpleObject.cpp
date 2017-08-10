// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_simpleObject.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_UnitTest_GeneratorTestCode_simpleObject.h"
#include "../Class_UnitTest_GeneratorTestCode_simpleObject.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_UnitTest_GeneratorTestCode_simpleObject::Stub_UnitTest_GeneratorTestCode_simpleObject(const Stub_UnitTest_GeneratorTestCode_simpleObject& other)
{
	// TODO: other.readLock
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// value
	value = other.value;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_UnitTest_GeneratorTestCode_simpleObject& Stub_UnitTest_GeneratorTestCode_simpleObject::operator =(const Stub_UnitTest_GeneratorTestCode_simpleObject& other)
{
	Stub_UnitTest_GeneratorTestCode_simpleObject tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_UnitTest_GeneratorTestCode_simpleObject& Stub_UnitTest_GeneratorTestCode_simpleObject::operator =(Stub_UnitTest_GeneratorTestCode_simpleObject&& other) noexcept
{
	// name
    std::swap(name, other.name);
	// value
    std::swap(value, other.value);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_UnitTest_GeneratorTestCode_simpleObject::Stub_UnitTest_GeneratorTestCode_simpleObject()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_simpleObject::Stub_UnitTest_GeneratorTestCode_simpleObject(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_simpleObject::Stub_UnitTest_GeneratorTestCode_simpleObject(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_simpleObject::~Stub_UnitTest_GeneratorTestCode_simpleObject()
{
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_simpleObject::clear()
{
	this->name.reset( new std::string("") );
	this->value = static_cast<int64_t>(0);
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_simpleObject::parseJson(const char *str)
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
void Stub_UnitTest_GeneratorTestCode_simpleObject::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// name
	if ((value.HasMember("name")) && value["name"].IsString())
	{
		set_name( boost::shared_ptr<std::string>( new std::string( value["name"].GetString() ) ) );
	}
	// value
	if ((value.HasMember("value")) && value["value"].IsInt64())
	{
		set_value( value["value"].GetInt64() );
	}
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_simpleObject::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_simpleObject::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_UnitTest_GeneratorTestCode_simpleObject::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // value
		node.AddMember("value", rapidjson::Value().SetInt64( get_value() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode_simpleObject::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_UnitTest_GeneratorTestCode_simpleObject::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_simpleObject::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
int64_t Stub_UnitTest_GeneratorTestCode_simpleObject::get_value() const
{
	return( this->value );
}

// --> Do NOT EDIT <--
const int64_t Stub_UnitTest_GeneratorTestCode_simpleObject::getconst_value() const
{
	return( this->value );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_simpleObject::set_value(int64_t value)
{
	this->value = value;
}


} // namespace UnitTest
} // namespace ConnectedVision