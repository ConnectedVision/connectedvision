/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_chain_connections.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_config_chain_connections.h"
#include "../Class_generic_config_chain_connections.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_config_chain_connections::Stub_generic_config_chain_connections(const Stub_generic_config_chain_connections& other)
{
	// TODO: other.readLock
	// inputPinID
	if ( other.inputPinID ) 
		inputPinID = boost::make_shared<std::string>(*other.inputPinID);
	// outputPinID
	if ( other.outputPinID ) 
		outputPinID = boost::make_shared<std::string>(*other.outputPinID);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_config_chain_connections& Stub_generic_config_chain_connections::operator =(const Stub_generic_config_chain_connections& other)
{
	Stub_generic_config_chain_connections tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_config_chain_connections& Stub_generic_config_chain_connections::operator =(Stub_generic_config_chain_connections&& other) noexcept
{
	// inputPinID
    std::swap(inputPinID, other.inputPinID);
	// outputPinID
    std::swap(outputPinID, other.outputPinID);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_config_chain_connections::Stub_generic_config_chain_connections()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_config_chain_connections::Stub_generic_config_chain_connections(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_config_chain_connections::Stub_generic_config_chain_connections(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_config_chain_connections::~Stub_generic_config_chain_connections()
{
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain_connections::clear()
{
	this->inputPinID.reset( new std::string("") );
	this->outputPinID.reset( new std::string("") );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain_connections::parseJson(const char *str)
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
void Stub_generic_config_chain_connections::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// inputPinID
	if ((value.HasMember("inputPinID")) && value["inputPinID"].IsString())
	{
		set_inputPinID( boost::shared_ptr<std::string>( new std::string( value["inputPinID"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'inputPinID'");

	// outputPinID
	if ((value.HasMember("outputPinID")) && value["outputPinID"].IsString())
	{
		set_outputPinID( boost::shared_ptr<std::string>( new std::string( value["outputPinID"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'outputPinID'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_config_chain_connections::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_chain_connections::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_config_chain_connections::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // inputPinID
		node.AddMember("inputPinID", rapidjson::Value().SetString( get_inputPinID()->c_str(), allocator), allocator);
	}
	{ // outputPinID
		node.AddMember("outputPinID", rapidjson::Value().SetString( get_outputPinID()->c_str(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config_chain_connections::get_inputPinID() const
{
	return( this->inputPinID );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config_chain_connections::getconst_inputPinID() const
{
	return( boost::static_pointer_cast<const std::string>(this->inputPinID) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain_connections::set_inputPinID(boost::shared_ptr<std::string> value)
{
	this->inputPinID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config_chain_connections::get_outputPinID() const
{
	return( this->outputPinID );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config_chain_connections::getconst_outputPinID() const
{
	return( boost::static_pointer_cast<const std::string>(this->outputPinID) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain_connections::set_outputPinID(boost::shared_ptr<std::string> value)
{
	this->outputPinID = value;
}


} // namespace ConnectedVision