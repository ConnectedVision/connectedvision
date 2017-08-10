// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_objArray.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_UnitTest_GeneratorTestCode_objArray.h"
#include "../Class_UnitTest_GeneratorTestCode_objArray.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_UnitTest_GeneratorTestCode_objArray::Stub_UnitTest_GeneratorTestCode_objArray(const Stub_UnitTest_GeneratorTestCode_objArray& other)
{
	// TODO: other.readLock
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// index
	index = other.index;
	// subArray
	{
		const auto& n0 = other.subArray;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<std::string>( *n0->at(i0) );
		}
		subArray = a0;
	}
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_UnitTest_GeneratorTestCode_objArray& Stub_UnitTest_GeneratorTestCode_objArray::operator =(const Stub_UnitTest_GeneratorTestCode_objArray& other)
{
	Stub_UnitTest_GeneratorTestCode_objArray tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_UnitTest_GeneratorTestCode_objArray& Stub_UnitTest_GeneratorTestCode_objArray::operator =(Stub_UnitTest_GeneratorTestCode_objArray&& other) noexcept
{
	// name
    std::swap(name, other.name);
	// index
    std::swap(index, other.index);
	// subArray
    std::swap(subArray, other.subArray);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_UnitTest_GeneratorTestCode_objArray::Stub_UnitTest_GeneratorTestCode_objArray()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_objArray::Stub_UnitTest_GeneratorTestCode_objArray(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_objArray::Stub_UnitTest_GeneratorTestCode_objArray(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_objArray::~Stub_UnitTest_GeneratorTestCode_objArray()
{
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_objArray::clear()
{
	this->name.reset( new std::string("") );
	this->index = static_cast<int64_t>(0);
	this->subArray.reset( new std::vector<boost::shared_ptr<std::string>> );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_objArray::parseJson(const char *str)
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
void Stub_UnitTest_GeneratorTestCode_objArray::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// name
	if ((value.HasMember("name")) && value["name"].IsString())
	{
		set_name( boost::shared_ptr<std::string>( new std::string( value["name"].GetString() ) ) );
	}
	// index
	if ((value.HasMember("index")) && value["index"].IsInt64())
	{
		set_index( value["index"].GetInt64() );
	}
	// subArray
	if ((value.HasMember("subArray")) && value["subArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["subArray"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> a0( new std::vector<boost::shared_ptr<std::string>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<std::string>( new std::string( n0[i0].GetString() ) );
		}
		set_subArray( a0 );
	}
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_objArray::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_objArray::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_UnitTest_GeneratorTestCode_objArray::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // index
		node.AddMember("index", rapidjson::Value().SetInt64( get_index() ), allocator);
	}
	{ // subArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a0 = get_subArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add string
			n0.PushBack(rapidjson::Value().SetString( a0->at(i0)->c_str(), allocator), allocator);
		}
		node.AddMember("subArray", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode_objArray::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_UnitTest_GeneratorTestCode_objArray::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_objArray::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
int64_t Stub_UnitTest_GeneratorTestCode_objArray::get_index() const
{
	return( this->index );
}

// --> Do NOT EDIT <--
const int64_t Stub_UnitTest_GeneratorTestCode_objArray::getconst_index() const
{
	return( this->index );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_objArray::set_index(int64_t value)
{
	this->index = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> Stub_UnitTest_GeneratorTestCode_objArray::get_subArray() const
{
	return( this->subArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> Stub_UnitTest_GeneratorTestCode_objArray::getconst_subArray() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::string>>>(this->subArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_objArray::set_subArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value)
{
	this->subArray = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode_objArray::get_subArray(int index) const
{
	return( this->subArray->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::string>& Stub_UnitTest_GeneratorTestCode_objArray::getconst_subArray(int index) const
{
	return( this->subArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_objArray::add_subArray(boost::shared_ptr<std::string> value)
{
	this->subArray->push_back(value);
}


} // namespace UnitTest
} // namespace ConnectedVision