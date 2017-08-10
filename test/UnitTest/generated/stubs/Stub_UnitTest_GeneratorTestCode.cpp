// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_UnitTest_GeneratorTestCode.h"
#include "../Class_UnitTest_GeneratorTestCode.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_UnitTest_GeneratorTestCode::Stub_UnitTest_GeneratorTestCode(const Stub_UnitTest_GeneratorTestCode& other)
{
	// TODO: other.readLock
	// configID
	configID = other.configID;
	// id
	id = other.id;
	// timestamp
	timestamp = other.timestamp;
	// boolVal
	boolVal = other.boolVal;
	// intVal
	intVal = other.intVal;
	// numberVal
	numberVal = other.numberVal;
	// stringVal
	if ( other.stringVal ) 
		stringVal = boost::make_shared<std::string>(*other.stringVal);
	// anyVal
	if ( other.anyVal ) 
		anyVal = boost::make_shared<std::string>(*other.anyVal);
	// simpleArray
	{
		const auto& n0 = other.simpleArray;
		auto a0 = boost::make_shared<std::vector<int64_t>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			a0->at(i0) = n0->at(i0);
		}
		simpleArray = a0;
	}
	// stringArray
	{
		const auto& n0 = other.stringArray;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<std::string>( *n0->at(i0) );
		}
		stringArray = a0;
	}
	// intArray
	{
		const auto& n0 = other.intArray;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			const auto& n1 = n0->at(i0);
			auto a1 = boost::make_shared<std::vector<boost::shared_ptr<std::vector<int64_t>>>>( (n1->size()) );
			for (size_t i1 = 0; i1 < n1->size(); ++i1)
			{
				const auto& n2 = n1->at(i1);
				auto a2 = boost::make_shared<std::vector<int64_t>>( (n2->size()) );
				for (size_t i2 = 0; i2 < n2->size(); ++i2)
				{
					a2->at(i2) = n2->at(i2);
				}
				a1->at(i1) = a2;
			}
			a0->at(i0) = a1;
		}
		intArray = a0;
	}
	// floatArray
	{
		const auto& n0 = other.floatArray;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			const auto& n1 = n0->at(i0);
			auto a1 = boost::make_shared<std::vector<boost::shared_ptr<std::vector<double>>>>( (n1->size()) );
			for (size_t i1 = 0; i1 < n1->size(); ++i1)
			{
				const auto& n2 = n1->at(i1);
				auto a2 = boost::make_shared<std::vector<double>>( (n2->size()) );
				for (size_t i2 = 0; i2 < n2->size(); ++i2)
				{
					a2->at(i2) = n2->at(i2);
				}
				a1->at(i1) = a2;
			}
			a0->at(i0) = a1;
		}
		floatArray = a0;
	}
	// objArray
	{
		const auto& n0 = other.objArray;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<Class_UnitTest_GeneratorTestCode_objArray>( *n0->at(i0) );
		}
		objArray = a0;
	}
	// simpleObject
	if ( other.simpleObject ) 
		simpleObject = boost::make_shared<Class_UnitTest_GeneratorTestCode_simpleObject>(*other.simpleObject);
	// complexObject
	if ( other.complexObject ) 
		complexObject = boost::make_shared<Class_UnitTest_GeneratorTestCode_complexObject>(*other.complexObject);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_UnitTest_GeneratorTestCode& Stub_UnitTest_GeneratorTestCode::operator =(const Stub_UnitTest_GeneratorTestCode& other)
{
	Stub_UnitTest_GeneratorTestCode tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_UnitTest_GeneratorTestCode& Stub_UnitTest_GeneratorTestCode::operator =(Stub_UnitTest_GeneratorTestCode&& other) noexcept
{
	// configID
    std::swap(configID, other.configID);
	// id
    std::swap(id, other.id);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// boolVal
    std::swap(boolVal, other.boolVal);
	// intVal
    std::swap(intVal, other.intVal);
	// numberVal
    std::swap(numberVal, other.numberVal);
	// stringVal
    std::swap(stringVal, other.stringVal);
	// anyVal
    std::swap(anyVal, other.anyVal);
	// simpleArray
    std::swap(simpleArray, other.simpleArray);
	// stringArray
    std::swap(stringArray, other.stringArray);
	// intArray
    std::swap(intArray, other.intArray);
	// floatArray
    std::swap(floatArray, other.floatArray);
	// objArray
    std::swap(objArray, other.objArray);
	// simpleObject
    std::swap(simpleObject, other.simpleObject);
	// complexObject
    std::swap(complexObject, other.complexObject);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_UnitTest_GeneratorTestCode::Stub_UnitTest_GeneratorTestCode()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode::Stub_UnitTest_GeneratorTestCode(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode::Stub_UnitTest_GeneratorTestCode(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_UnitTest_GeneratorTestCode::~Stub_UnitTest_GeneratorTestCode()
{
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::clear()
{
	this->configID = "";
	this->id = "";
	this->timestamp = 0;
	this->boolVal = static_cast<bool>(false);
	this->intVal = static_cast<int64_t>(0);
	this->numberVal = static_cast<double>(0.0);
	this->stringVal.reset( new std::string("") );
	this->anyVal.reset( new std::string("") );
	this->simpleArray.reset( new std::vector<int64_t> );
	this->stringArray.reset( new std::vector<boost::shared_ptr<std::string>> );
	this->intArray.reset( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>> );
	this->floatArray.reset( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>> );
	this->objArray.reset( new std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>> );
	this->simpleObject.reset( new Class_UnitTest_GeneratorTestCode_simpleObject );
	this->complexObject.reset( new Class_UnitTest_GeneratorTestCode_complexObject );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::parseJson(const char *str)
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
void Stub_UnitTest_GeneratorTestCode::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// configID
	if ((value.HasMember("configID")) && value["configID"].IsString())
	{
		set_configID( ConnectedVision::strToID( value["configID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'configID'");

	// id
	if ((value.HasMember("id")) && value["id"].IsString())
	{
		set_id( ConnectedVision::strToID( value["id"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'id'");

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestamp'");

	// boolVal
	if ((value.HasMember("boolVal")) && value["boolVal"].IsBool())
	{
		set_boolVal( value["boolVal"].GetBool() );
	}
	// intVal
	if ((value.HasMember("intVal")) && value["intVal"].IsInt64())
	{
		set_intVal( value["intVal"].GetInt64() );
	}
	// numberVal
	if ((value.HasMember("numberVal")) && value["numberVal"].IsNumber())
	{
		set_numberVal( value["numberVal"].GetDouble() );
	}
	// stringVal
	if ((value.HasMember("stringVal")) && value["stringVal"].IsString())
	{
		set_stringVal( boost::shared_ptr<std::string>( new std::string( value["stringVal"].GetString() ) ) );
	}
	// anyVal
	if ((value.HasMember("anyVal")) && ( value["anyVal"].IsObject() || value["anyVal"].IsArray() || value["anyVal"].IsInt64() || value["anyVal"].IsNumber() || value["anyVal"].IsBool() ))
	{
		set_anyVal( boost::shared_ptr<std::string>( new std::string( ConnectedVision::jsonToStr(value["anyVal"]) ) ) );
	}
	// simpleArray
	if ((value.HasMember("simpleArray")) && value["simpleArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["simpleArray"];
		boost::shared_ptr<std::vector<int64_t>> a0( new std::vector<int64_t>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = n0[i0].GetInt64();
		}
		set_simpleArray( a0 );
	}
	// stringArray
	if ((value.HasMember("stringArray")) && value["stringArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["stringArray"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> a0( new std::vector<boost::shared_ptr<std::string>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<std::string>( new std::string( n0[i0].GetString() ) );
		}
		set_stringArray( a0 );
	}
	// intArray
	if ((value.HasMember("intArray")) && value["intArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["intArray"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> a0( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			const rapidjson::Value& n1 = n0[i0];
			boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>> a1( new std::vector<boost::shared_ptr<std::vector<int64_t>>>(n1.Size()) );
			for (rapidjson::SizeType i1 = 0; i1 < n1.Size(); i1++)
			{
				const rapidjson::Value& n2 = n1[i1];
				boost::shared_ptr<std::vector<int64_t>> a2( new std::vector<int64_t>(n2.Size()) );
				for (rapidjson::SizeType i2 = 0; i2 < n2.Size(); i2++)
				{
					a2->at(i2) = n2[i2].GetInt64();
				}
				a1->at(i1) = a2;
			}
			a0->at(i0) = a1;
		}
		set_intArray( a0 );
	}
	// floatArray
	if ((value.HasMember("floatArray")) && value["floatArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["floatArray"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> a0( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			const rapidjson::Value& n1 = n0[i0];
			boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>> a1( new std::vector<boost::shared_ptr<std::vector<double>>>(n1.Size()) );
			for (rapidjson::SizeType i1 = 0; i1 < n1.Size(); i1++)
			{
				const rapidjson::Value& n2 = n1[i1];
				boost::shared_ptr<std::vector<double>> a2( new std::vector<double>(n2.Size()) );
				for (rapidjson::SizeType i2 = 0; i2 < n2.Size(); i2++)
				{
					a2->at(i2) = n2[i2].GetDouble();
				}
				a1->at(i1) = a2;
			}
			a0->at(i0) = a1;
		}
		set_floatArray( a0 );
	}
	// objArray
	if ((value.HasMember("objArray")) && value["objArray"].IsArray())
	{
		const rapidjson::Value& n0 = value["objArray"];
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> a0( new std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>( new Class_UnitTest_GeneratorTestCode_objArray( n0[i0] ) );
		}
		set_objArray( a0 );
	}
	// simpleObject
	if ((value.HasMember("simpleObject")) && value["simpleObject"].IsObject())
	{
		set_simpleObject( boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject>( new Class_UnitTest_GeneratorTestCode_simpleObject( value["simpleObject"] ) ) );
	}
	// complexObject
	if ((value.HasMember("complexObject")) && value["complexObject"].IsObject())
	{
		set_complexObject( boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject>( new Class_UnitTest_GeneratorTestCode_complexObject( value["complexObject"] ) ) );
	}
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_UnitTest_GeneratorTestCode::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_UnitTest_GeneratorTestCode::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // configID
		node.AddMember("configID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_configID() ), allocator), allocator);
	}
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_id() ), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // boolVal
		node.AddMember("boolVal", rapidjson::Value().SetBool( get_boolVal() ), allocator);
	}
	{ // intVal
		node.AddMember("intVal", rapidjson::Value().SetInt64( get_intVal() ), allocator);
	}
	{ // numberVal
		node.AddMember("numberVal", rapidjson::Value().SetDouble( get_numberVal() ), allocator);
	}
	{ // stringVal
		node.AddMember("stringVal", rapidjson::Value().SetString( get_stringVal()->c_str(), allocator), allocator);
	}
	{ // anyVal
		rapidjson::Document doc(&allocator);
		doc.Parse<0>( get_anyVal()->c_str() );
		node.AddMember("anyVal", static_cast<rapidjson::Value&>(doc), allocator);
	}
	{ // simpleArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<int64_t>>&& a0 = get_simpleArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add integer
			n0.PushBack(rapidjson::Value().SetInt64( a0->at(i0) ), allocator);
		}
		node.AddMember("simpleArray", n0, allocator);
	}
	{ // stringArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a0 = get_stringArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add string
			n0.PushBack(rapidjson::Value().SetString( a0->at(i0)->c_str(), allocator), allocator);
		}
		node.AddMember("stringArray", n0, allocator);
	}
	{ // intArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>&& a0 = get_intArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			rapidjson::Value n1; n1.SetArray();
			boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>& a1 = a0->at(i0); // lvalue reference for non-const functions like vector::at()
			for (size_t i1 = 0; i1 < a1->size(); i1++)
			{
				// process array level 1
				rapidjson::Value n2; n2.SetArray();
				boost::shared_ptr<std::vector<int64_t>>& a2 = a1->at(i1); // lvalue reference for non-const functions like vector::at()
				for (size_t i2 = 0; i2 < a2->size(); i2++)
				{
					// process array level 2
					// final level of array, add integer
					n2.PushBack(rapidjson::Value().SetInt64( a2->at(i2) ), allocator);
				}
				// add actual data to array level 1
				n1.PushBack(n2, allocator);
			}
			// add actual data to array level 0
			n0.PushBack(n1, allocator);
		}
		node.AddMember("intArray", n0, allocator);
	}
	{ // floatArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>>&& a0 = get_floatArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			rapidjson::Value n1; n1.SetArray();
			boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>& a1 = a0->at(i0); // lvalue reference for non-const functions like vector::at()
			for (size_t i1 = 0; i1 < a1->size(); i1++)
			{
				// process array level 1
				rapidjson::Value n2; n2.SetArray();
				boost::shared_ptr<std::vector<double>>& a2 = a1->at(i1); // lvalue reference for non-const functions like vector::at()
				for (size_t i2 = 0; i2 < a2->size(); i2++)
				{
					// process array level 2
					// final level of array, add number
					n2.PushBack(rapidjson::Value().SetDouble( a2->at(i2) ), allocator);
				}
				// add actual data to array level 1
				n1.PushBack(n2, allocator);
			}
			// add actual data to array level 0
			n0.PushBack(n1, allocator);
		}
		node.AddMember("floatArray", n0, allocator);
	}
	{ // objArray
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>>&& a0 = get_objArray(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final dimension of array, add actual value
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				n0.PushBack(a0->at(i0)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
			}
		}
		node.AddMember("objArray", n0, allocator);
	}
	{ // simpleObject
		node.AddMember("simpleObject", get_simpleObject()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // complexObject
		node.AddMember("complexObject", get_complexObject()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_UnitTest_GeneratorTestCode::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_UnitTest_GeneratorTestCode::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_UnitTest_GeneratorTestCode::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_UnitTest_GeneratorTestCode::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_UnitTest_GeneratorTestCode::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_UnitTest_GeneratorTestCode::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
bool Stub_UnitTest_GeneratorTestCode::get_boolVal() const
{
	return( this->boolVal );
}

// --> Do NOT EDIT <--
const bool Stub_UnitTest_GeneratorTestCode::getconst_boolVal() const
{
	return( this->boolVal );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_boolVal(bool value)
{
	this->boolVal = value;
}

// --> Do NOT EDIT <--
int64_t Stub_UnitTest_GeneratorTestCode::get_intVal() const
{
	return( this->intVal );
}

// --> Do NOT EDIT <--
const int64_t Stub_UnitTest_GeneratorTestCode::getconst_intVal() const
{
	return( this->intVal );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_intVal(int64_t value)
{
	this->intVal = value;
}

// --> Do NOT EDIT <--
double Stub_UnitTest_GeneratorTestCode::get_numberVal() const
{
	return( this->numberVal );
}

// --> Do NOT EDIT <--
const double Stub_UnitTest_GeneratorTestCode::getconst_numberVal() const
{
	return( this->numberVal );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_numberVal(double value)
{
	this->numberVal = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode::get_stringVal() const
{
	return( this->stringVal );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_UnitTest_GeneratorTestCode::getconst_stringVal() const
{
	return( boost::static_pointer_cast<const std::string>(this->stringVal) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_stringVal(boost::shared_ptr<std::string> value)
{
	this->stringVal = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode::get_anyVal() const
{
	return( this->anyVal );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_UnitTest_GeneratorTestCode::getconst_anyVal() const
{
	return( boost::static_pointer_cast<const std::string>(this->anyVal) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_anyVal(boost::shared_ptr<std::string> value)
{
	this->anyVal = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<int64_t>> Stub_UnitTest_GeneratorTestCode::get_simpleArray() const
{
	return( this->simpleArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<int64_t>> Stub_UnitTest_GeneratorTestCode::getconst_simpleArray() const
{
	return( boost::static_pointer_cast<const std::vector<int64_t>>(this->simpleArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_simpleArray(boost::shared_ptr<std::vector<int64_t>> value)
{
	this->simpleArray = value;
}

// --> Do NOT EDIT <--
int64_t Stub_UnitTest_GeneratorTestCode::get_simpleArray(int index) const
{
	return( this->simpleArray->at(index) );
}

// --> Do NOT EDIT <--
const int64_t& Stub_UnitTest_GeneratorTestCode::getconst_simpleArray(int index) const
{
	return( this->simpleArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::add_simpleArray(int64_t value)
{
	this->simpleArray->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> Stub_UnitTest_GeneratorTestCode::get_stringArray() const
{
	return( this->stringArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> Stub_UnitTest_GeneratorTestCode::getconst_stringArray() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::string>>>(this->stringArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_stringArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value)
{
	this->stringArray = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_UnitTest_GeneratorTestCode::get_stringArray(int index) const
{
	return( this->stringArray->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::string>& Stub_UnitTest_GeneratorTestCode::getconst_stringArray(int index) const
{
	return( this->stringArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::add_stringArray(boost::shared_ptr<std::string> value)
{
	this->stringArray->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> Stub_UnitTest_GeneratorTestCode::get_intArray() const
{
	return( this->intArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> Stub_UnitTest_GeneratorTestCode::getconst_intArray() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>(this->intArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_intArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> value)
{
	this->intArray = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>> Stub_UnitTest_GeneratorTestCode::get_intArray(int index) const
{
	return( this->intArray->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>& Stub_UnitTest_GeneratorTestCode::getconst_intArray(int index) const
{
	return( this->intArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::add_intArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>> value)
{
	this->intArray->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> Stub_UnitTest_GeneratorTestCode::get_floatArray() const
{
	return( this->floatArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> Stub_UnitTest_GeneratorTestCode::getconst_floatArray() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>>(this->floatArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_floatArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> value)
{
	this->floatArray = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>> Stub_UnitTest_GeneratorTestCode::get_floatArray(int index) const
{
	return( this->floatArray->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>& Stub_UnitTest_GeneratorTestCode::getconst_floatArray(int index) const
{
	return( this->floatArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::add_floatArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>> value)
{
	this->floatArray->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> Stub_UnitTest_GeneratorTestCode::get_objArray() const
{
	return( this->objArray );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> Stub_UnitTest_GeneratorTestCode::getconst_objArray() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>>(this->objArray) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_objArray(boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> value)
{
	this->objArray = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray> Stub_UnitTest_GeneratorTestCode::get_objArray(int index) const
{
	return( this->objArray->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>& Stub_UnitTest_GeneratorTestCode::getconst_objArray(int index) const
{
	return( this->objArray->at(index) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::add_objArray(boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray> value)
{
	this->objArray->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject> Stub_UnitTest_GeneratorTestCode::get_simpleObject() const
{
	return( this->simpleObject );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_simpleObject> Stub_UnitTest_GeneratorTestCode::getconst_simpleObject() const
{
	return( boost::static_pointer_cast<const Class_UnitTest_GeneratorTestCode_simpleObject>(this->simpleObject) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_simpleObject(boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject> value)
{
	this->simpleObject = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject> Stub_UnitTest_GeneratorTestCode::get_complexObject() const
{
	return( this->complexObject );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_complexObject> Stub_UnitTest_GeneratorTestCode::getconst_complexObject() const
{
	return( boost::static_pointer_cast<const Class_UnitTest_GeneratorTestCode_complexObject>(this->complexObject) );
}

// --> Do NOT EDIT <--
void Stub_UnitTest_GeneratorTestCode::set_complexObject(boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject> value)
{
	this->complexObject = value;
}


} // namespace UnitTest
} // namespace ConnectedVision