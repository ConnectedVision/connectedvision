/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_callback.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_config_callback.h"
#include "../Class_generic_config_callback.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_config_callback::Stub_generic_config_callback(const Stub_generic_config_callback& other)
{
	// TODO: other.readLock
	// moduleID
	moduleID = other.moduleID;
	// moduleURI
	if ( other.moduleURI ) 
		moduleURI = boost::make_shared<std::string>(*other.moduleURI);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_config_callback& Stub_generic_config_callback::operator =(const Stub_generic_config_callback& other)
{
	Stub_generic_config_callback tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_config_callback& Stub_generic_config_callback::operator =(Stub_generic_config_callback&& other) noexcept
{
	// moduleID
    std::swap(moduleID, other.moduleID);
	// moduleURI
    std::swap(moduleURI, other.moduleURI);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_config_callback::Stub_generic_config_callback()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_config_callback::Stub_generic_config_callback(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_config_callback::Stub_generic_config_callback(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_config_callback::~Stub_generic_config_callback()
{
}

// --> Do NOT EDIT <--
void Stub_generic_config_callback::clear()
{
	this->moduleID = "";
	this->moduleURI.reset( new std::string("") );
}

// --> Do NOT EDIT <--
void Stub_generic_config_callback::parseJson(const char *str)
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
void Stub_generic_config_callback::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// moduleID
	if ((value.HasMember("moduleID")) && value["moduleID"].IsString())
	{
		set_moduleID( ConnectedVision::strToID( value["moduleID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'moduleID'");

	// moduleURI
	if ((value.HasMember("moduleURI")) && value["moduleURI"].IsString())
	{
		set_moduleURI( boost::shared_ptr<std::string>( new std::string( value["moduleURI"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'moduleURI'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_config_callback::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_callback::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_config_callback::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // moduleID
		node.AddMember("moduleID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_moduleID() ), allocator), allocator);
	}
	{ // moduleURI
		node.AddMember("moduleURI", rapidjson::Value().SetString( get_moduleURI()->c_str(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_config_callback::get_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_config_callback::getconst_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
void Stub_generic_config_callback::set_moduleID(ConnectedVision::id_t value)
{
	this->moduleID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config_callback::get_moduleURI() const
{
	return( this->moduleURI );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config_callback::getconst_moduleURI() const
{
	return( boost::static_pointer_cast<const std::string>(this->moduleURI) );
}

// --> Do NOT EDIT <--
void Stub_generic_config_callback::set_moduleURI(boost::shared_ptr<std::string> value)
{
	this->moduleURI = value;
}


} // namespace ConnectedVision