/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription_moduleFeatures.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ModuleDescription_moduleFeatures.h"
#include "../Class_ModuleDescription_moduleFeatures.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_ModuleDescription_moduleFeatures::Stub_ModuleDescription_moduleFeatures(const Stub_ModuleDescription_moduleFeatures& other)
{
	// TODO: other.readLock
	// supportsLive
	supportsLive = other.supportsLive;
	// supportsResume
	supportsResume = other.supportsResume;
	// supportsDynamicParameters
	supportsDynamicParameters = other.supportsDynamicParameters;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ModuleDescription_moduleFeatures& Stub_ModuleDescription_moduleFeatures::operator =(const Stub_ModuleDescription_moduleFeatures& other)
{
	Stub_ModuleDescription_moduleFeatures tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ModuleDescription_moduleFeatures& Stub_ModuleDescription_moduleFeatures::operator =(Stub_ModuleDescription_moduleFeatures&& other) noexcept
{
	// supportsLive
    std::swap(supportsLive, other.supportsLive);
	// supportsResume
    std::swap(supportsResume, other.supportsResume);
	// supportsDynamicParameters
    std::swap(supportsDynamicParameters, other.supportsDynamicParameters);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ModuleDescription_moduleFeatures::Stub_ModuleDescription_moduleFeatures()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ModuleDescription_moduleFeatures::Stub_ModuleDescription_moduleFeatures(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ModuleDescription_moduleFeatures::Stub_ModuleDescription_moduleFeatures(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ModuleDescription_moduleFeatures::~Stub_ModuleDescription_moduleFeatures()
{
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_moduleFeatures::clear()
{
	this->supportsLive = static_cast<bool>(false);
	this->supportsResume = static_cast<bool>(false);
	this->supportsDynamicParameters = static_cast<bool>(false);
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_moduleFeatures::parseJson(const char *str)
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
void Stub_ModuleDescription_moduleFeatures::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// supportsLive
	if ((value.HasMember("supportsLive")) && value["supportsLive"].IsBool())
	{
		set_supportsLive( value["supportsLive"].GetBool() );
	}
	// supportsResume
	if ((value.HasMember("supportsResume")) && value["supportsResume"].IsBool())
	{
		set_supportsResume( value["supportsResume"].GetBool() );
	}
	// supportsDynamicParameters
	if ((value.HasMember("supportsDynamicParameters")) && value["supportsDynamicParameters"].IsBool())
	{
		set_supportsDynamicParameters( value["supportsDynamicParameters"].GetBool() );
	}
}

// --> Do NOT EDIT <--
std::string Stub_ModuleDescription_moduleFeatures::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ModuleDescription_moduleFeatures::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ModuleDescription_moduleFeatures::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // supportsLive
		node.AddMember("supportsLive", rapidjson::Value().SetBool( get_supportsLive() ), allocator);
	}
	{ // supportsResume
		node.AddMember("supportsResume", rapidjson::Value().SetBool( get_supportsResume() ), allocator);
	}
	{ // supportsDynamicParameters
		node.AddMember("supportsDynamicParameters", rapidjson::Value().SetBool( get_supportsDynamicParameters() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
bool Stub_ModuleDescription_moduleFeatures::get_supportsLive() const
{
	return( this->supportsLive );
}

// --> Do NOT EDIT <--
const bool Stub_ModuleDescription_moduleFeatures::getconst_supportsLive() const
{
	return( this->supportsLive );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_moduleFeatures::set_supportsLive(bool value)
{
	this->supportsLive = value;
}

// --> Do NOT EDIT <--
bool Stub_ModuleDescription_moduleFeatures::get_supportsResume() const
{
	return( this->supportsResume );
}

// --> Do NOT EDIT <--
const bool Stub_ModuleDescription_moduleFeatures::getconst_supportsResume() const
{
	return( this->supportsResume );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_moduleFeatures::set_supportsResume(bool value)
{
	this->supportsResume = value;
}

// --> Do NOT EDIT <--
bool Stub_ModuleDescription_moduleFeatures::get_supportsDynamicParameters() const
{
	return( this->supportsDynamicParameters );
}

// --> Do NOT EDIT <--
const bool Stub_ModuleDescription_moduleFeatures::getconst_supportsDynamicParameters() const
{
	return( this->supportsDynamicParameters );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription_moduleFeatures::set_supportsDynamicParameters(bool value)
{
	this->supportsDynamicParameters = value;
}


} // namespace ConnectedVision