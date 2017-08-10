/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_chain.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_config_chain.h"
#include "../Class_generic_config_chain.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_config_chain::Stub_generic_config_chain(const Stub_generic_config_chain& other)
{
	// TODO: other.readLock
	// connections
	{
		const auto& n0 = other.connections;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<Class_generic_config_chain_connections>( *n0->at(i0) );
		}
		connections = a0;
	}
	// config
	if ( other.config ) 
		config = boost::make_shared<std::string>(*other.config);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_config_chain& Stub_generic_config_chain::operator =(const Stub_generic_config_chain& other)
{
	Stub_generic_config_chain tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_config_chain& Stub_generic_config_chain::operator =(Stub_generic_config_chain&& other) noexcept
{
	// connections
    std::swap(connections, other.connections);
	// config
    std::swap(config, other.config);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_config_chain::Stub_generic_config_chain()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_config_chain::Stub_generic_config_chain(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_config_chain::Stub_generic_config_chain(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_config_chain::~Stub_generic_config_chain()
{
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain::clear()
{
	this->connections.reset( new std::vector<boost::shared_ptr<Class_generic_config_chain_connections>> );
	this->config.reset( new std::string("") );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain::parseJson(const char *str)
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
void Stub_generic_config_chain::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// connections
	if ((value.HasMember("connections")) && value["connections"].IsArray())
	{
		const rapidjson::Value& n0 = value["connections"];
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> a0( new std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<Class_generic_config_chain_connections>( new Class_generic_config_chain_connections( n0[i0] ) );
		}
		set_connections( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'connections'");

	// config
	if ((value.HasMember("config")) && ( value["config"].IsObject() || value["config"].IsArray() || value["config"].IsInt64() || value["config"].IsNumber() || value["config"].IsBool() ))
	{
		set_config( boost::shared_ptr<std::string>( new std::string( ConnectedVision::jsonToStr(value["config"]) ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'config'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_config_chain::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_chain::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_config_chain::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // connections
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>>&& a0 = get_connections(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final dimension of array, add actual value
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				n0.PushBack(a0->at(i0)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
			}
		}
		node.AddMember("connections", n0, allocator);
	}
	{ // config
		rapidjson::Document doc(&allocator);
		doc.Parse<0>( get_config()->c_str() );
		node.AddMember("config", static_cast<rapidjson::Value&>(doc), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> Stub_generic_config_chain::get_connections() const
{
	return( this->connections );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> Stub_generic_config_chain::getconst_connections() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>>(this->connections) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain::set_connections(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain_connections>>> value)
{
	this->connections = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_config_chain_connections> Stub_generic_config_chain::get_connections(int index) const
{
	return( this->connections->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<Class_generic_config_chain_connections>& Stub_generic_config_chain::getconst_connections(int index) const
{
	return( this->connections->at(index) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain::add_connections(boost::shared_ptr<Class_generic_config_chain_connections> value)
{
	this->connections->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config_chain::get_config() const
{
	return( this->config );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config_chain::getconst_config() const
{
	return( boost::static_pointer_cast<const std::string>(this->config) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_chain::set_config(boost::shared_ptr<std::string> value)
{
	this->config = value;
}


} // namespace ConnectedVision