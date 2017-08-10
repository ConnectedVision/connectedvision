/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config_configFeatures.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_config_configFeatures.h"
#include "../Class_generic_config_configFeatures.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_config_configFeatures::Stub_generic_config_configFeatures(const Stub_generic_config_configFeatures& other)
{
	// TODO: other.readLock
	// allowDynamicParameters
	allowDynamicParameters = other.allowDynamicParameters;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_config_configFeatures& Stub_generic_config_configFeatures::operator =(const Stub_generic_config_configFeatures& other)
{
	Stub_generic_config_configFeatures tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_config_configFeatures& Stub_generic_config_configFeatures::operator =(Stub_generic_config_configFeatures&& other) noexcept
{
	// allowDynamicParameters
    std::swap(allowDynamicParameters, other.allowDynamicParameters);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_config_configFeatures::Stub_generic_config_configFeatures()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_config_configFeatures::Stub_generic_config_configFeatures(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_config_configFeatures::Stub_generic_config_configFeatures(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_config_configFeatures::~Stub_generic_config_configFeatures()
{
}

// --> Do NOT EDIT <--
void Stub_generic_config_configFeatures::clear()
{
	this->allowDynamicParameters = static_cast<bool>(false);
}

// --> Do NOT EDIT <--
void Stub_generic_config_configFeatures::parseJson(const char *str)
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
void Stub_generic_config_configFeatures::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// allowDynamicParameters
	if ((value.HasMember("allowDynamicParameters")) && value["allowDynamicParameters"].IsBool())
	{
		set_allowDynamicParameters( value["allowDynamicParameters"].GetBool() );
	}
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_configFeatures::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_config_configFeatures::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_config_configFeatures::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // allowDynamicParameters
		node.AddMember("allowDynamicParameters", rapidjson::Value().SetBool( get_allowDynamicParameters() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
bool Stub_generic_config_configFeatures::get_allowDynamicParameters() const
{
	return( this->allowDynamicParameters );
}

// --> Do NOT EDIT <--
const bool Stub_generic_config_configFeatures::getconst_allowDynamicParameters() const
{
	return( this->allowDynamicParameters );
}

// --> Do NOT EDIT <--
void Stub_generic_config_configFeatures::set_allowDynamicParameters(bool value)
{
	this->allowDynamicParameters = value;
}


} // namespace ConnectedVision