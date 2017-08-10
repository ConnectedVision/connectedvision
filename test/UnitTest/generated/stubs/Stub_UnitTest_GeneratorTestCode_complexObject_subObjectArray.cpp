// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h"
#include "../Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray(const Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray& other)
{
	// TODO: other.readLock
	// sub
	if ( other.sub ) 
		sub = boost::make_shared<std::string>(*other.sub);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray& Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::operator =(const Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray& other)
{
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray& Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::operator =(Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray&& other) noexcept
{
	// sub
    std::swap(sub, other.sub);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::~Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray()
{
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::clear()
{
	this->sub.reset( new std::string("") );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::parseJson(const char *str)
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
void Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// sub
	if ((value.HasMember("sub")) && value["sub"].IsString())
	{
		set_sub( boost::shared_ptr<std::string>( new std::string( value["sub"].GetString() ) ) );
	}
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // sub
		node.AddMember("sub", rapidjson::Value().SetString( get_sub()->c_str(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::get_sub() const
{
	return( this->sub );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::getconst_sub() const
{
	return( boost::static_pointer_cast<const std::string>(this->sub) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray::set_sub(boost::shared_ptr<std::string> value)
{
	this->sub = value;
}


} // namespace UnitTest
} // namespace ConnectedVision