// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_params_lineColor.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ThumbnailGenerator_params_lineColor.h"
#include "../Class_ThumbnailGenerator_params_lineColor.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_ThumbnailGenerator_params_lineColor::Stub_ThumbnailGenerator_params_lineColor(const Stub_ThumbnailGenerator_params_lineColor& other)
{
	// TODO: other.readLock
	// R
	R = other.R;
	// G
	G = other.G;
	// B
	B = other.B;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ThumbnailGenerator_params_lineColor& Stub_ThumbnailGenerator_params_lineColor::operator =(const Stub_ThumbnailGenerator_params_lineColor& other)
{
	Stub_ThumbnailGenerator_params_lineColor tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ThumbnailGenerator_params_lineColor& Stub_ThumbnailGenerator_params_lineColor::operator =(Stub_ThumbnailGenerator_params_lineColor&& other) noexcept
{
	// R
    std::swap(R, other.R);
	// G
    std::swap(G, other.G);
	// B
    std::swap(B, other.B);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ThumbnailGenerator_params_lineColor::Stub_ThumbnailGenerator_params_lineColor()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_params_lineColor::Stub_ThumbnailGenerator_params_lineColor(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_params_lineColor::Stub_ThumbnailGenerator_params_lineColor(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ThumbnailGenerator_params_lineColor::~Stub_ThumbnailGenerator_params_lineColor()
{
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params_lineColor::clear()
{
	this->R = static_cast<double>(0);
	this->G = static_cast<double>(0);
	this->B = static_cast<double>(0);
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params_lineColor::parseJson(const char *str)
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
void Stub_ThumbnailGenerator_params_lineColor::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// R
	if ((value.HasMember("R")) && value["R"].IsNumber())
	{
		set_R( value["R"].GetDouble() );
	}
	// G
	if ((value.HasMember("G")) && value["G"].IsNumber())
	{
		set_G( value["G"].GetDouble() );
	}
	// B
	if ((value.HasMember("B")) && value["B"].IsNumber())
	{
		set_B( value["B"].GetDouble() );
	}
}

// --> Do NOT EDIT <--
std::string Stub_ThumbnailGenerator_params_lineColor::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ThumbnailGenerator_params_lineColor::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ThumbnailGenerator_params_lineColor::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // R
		node.AddMember("R", rapidjson::Value().SetDouble( get_R() ), allocator);
	}
	{ // G
		node.AddMember("G", rapidjson::Value().SetDouble( get_G() ), allocator);
	}
	{ // B
		node.AddMember("B", rapidjson::Value().SetDouble( get_B() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
double Stub_ThumbnailGenerator_params_lineColor::get_R() const
{
	return( this->R );
}

// --> Do NOT EDIT <--
const double Stub_ThumbnailGenerator_params_lineColor::getconst_R() const
{
	return( this->R );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params_lineColor::set_R(double value)
{
	this->R = value;
}

// --> Do NOT EDIT <--
double Stub_ThumbnailGenerator_params_lineColor::get_G() const
{
	return( this->G );
}

// --> Do NOT EDIT <--
const double Stub_ThumbnailGenerator_params_lineColor::getconst_G() const
{
	return( this->G );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params_lineColor::set_G(double value)
{
	this->G = value;
}

// --> Do NOT EDIT <--
double Stub_ThumbnailGenerator_params_lineColor::get_B() const
{
	return( this->B );
}

// --> Do NOT EDIT <--
const double Stub_ThumbnailGenerator_params_lineColor::getconst_B() const
{
	return( this->B );
}

// --> Do NOT EDIT <--
void Stub_ThumbnailGenerator_params_lineColor::set_B(double value)
{
	this->B = value;
}


} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision