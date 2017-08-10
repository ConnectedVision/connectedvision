// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_complexObject.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_UnitTest_GeneratorTestCode_complexObject.h"
#include "../Class_UnitTest_GeneratorTestCode_complexObject.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_UnitTest_GeneratorTestCode_complexObject::Stub_UnitTest_GeneratorTestCode_complexObject(const Stub_UnitTest_GeneratorTestCode_complexObject& other)
{
	// TODO: other.readLock
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// subObjectArray
	{
		const auto& n0 = other.subObjectArray;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			const auto& n1 = n0->at(i0);
			auto a1 = boost::make_shared<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>( (n1->size()) );
			for (size_t i1 = 0; i1 < n1->size(); ++i1)
			{
				if ( n1->at(i1) )
					a1->at(i1) = boost::make_shared<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>( *n1->at(i1) );
			}
			a0->at(i0) = a1;
		}
		subObjectArray = a0;
	}
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_UnitTest_GeneratorTestCode_complexObject& Stub_UnitTest_GeneratorTestCode_complexObject::operator =(const Stub_UnitTest_GeneratorTestCode_complexObject& other)
{
	Stub_UnitTest_GeneratorTestCode_complexObject tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_UnitTest_GeneratorTestCode_complexObject& Stub_UnitTest_GeneratorTestCode_complexObject::operator =(Stub_UnitTest_GeneratorTestCode_complexObject&& other) noexcept
{
	// name
    std::swap(name, other.name);
	// subObjectArray
    std::swap(subObjectArray, other.subObjectArray);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_UnitTest_GeneratorTestCode_complexObject::Stub_UnitTest_GeneratorTestCode_complexObject()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_complexObject::Stub_UnitTest_GeneratorTestCode_complexObject(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_complexObject::Stub_UnitTest_GeneratorTestCode_complexObject(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode_complexObject::~Stub_UnitTest_GeneratorTestCode_complexObject()
{
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject::clear()
{
	this->name.reset( new std::string("") );
	this->subObjectArray.reset( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>> );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject::parseJson(const char *str)
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
void Stub_UnitTest_GeneratorTestCode_complexObject::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// name
	if ((value.HasMember("name")) && value["name"].IsString())
	{
		set_name( boost::shared_ptr<std::string>( new std::string( value["name"].GetString() ) ) );
	}
	// subObjectArray
	if ((value.HasMember("subObjectArray")) && value["subObjectArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["subObjectArray"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> a0( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			const rapidjson::Value& n1 = n0[i0];
			boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>> a1( new std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>(n1.Size()) );
			for (rapidjson::SizeType i1 = 0; i1 < n1.Size(); i1++)
			{
				a1->at(i1) = boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>( new Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray( n1[i1] ) );
			}
			a0->at(i0) = a1;
		}
		set_subObjectArray( a0 );
	}
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_complexObject::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode_complexObject::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_UnitTest_GeneratorTestCode_complexObject::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // subObjectArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>>&& a0 = get_subObjectArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			rapidjson::Value n1; n1.SetArray();
			boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>& a1 = a0->at(i0); // lvalue reference for non-const functions like vector::at()
			for (size_t i1 = 0; i1 < a1->size(); i1++)
			{
				// process array level 1
				// final dimension of array, add actual value
				if ( a1->at(i1) )	// ensure that we have no NULL pointer
				{
					n1.PushBack(a1->at(i1)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
				}
			}
			// add actual data to array level 0
			n0.PushBack(n1, allocator);
		}
		node.AddMember("subObjectArray", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode_complexObject::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_UnitTest_GeneratorTestCode_complexObject::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> Stub_UnitTest_GeneratorTestCode_complexObject::get_subObjectArray() const
{
	return( this->subObjectArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> Stub_UnitTest_GeneratorTestCode_complexObject::getconst_subObjectArray() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>>(this->subObjectArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject::set_subObjectArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> value)
{
	this->subObjectArray = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>> Stub_UnitTest_GeneratorTestCode_complexObject::get_subObjectArray(int index) const
{
	return( this->subObjectArray->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>& Stub_UnitTest_GeneratorTestCode_complexObject::getconst_subObjectArray(int index) const
{
	return( this->subObjectArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode_complexObject::add_subObjectArray(boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>> value)
{
	this->subObjectArray->push_back(value);
}


} // namespace UnitTest
} // namespace ConnectedVision