// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_Skeleton_output_Average_color.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_Skeleton_output_Average_color.h"
#include "../Class_Skeleton_output_Average_color.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace test {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_Skeleton_output_Average_color::Stub_Skeleton_output_Average_color(const Stub_Skeleton_output_Average_color& other)
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
Stub_Skeleton_output_Average_color& Stub_Skeleton_output_Average_color::operator =(const Stub_Skeleton_output_Average_color& other)
{
	Stub_Skeleton_output_Average_color tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_Skeleton_output_Average_color& Stub_Skeleton_output_Average_color::operator =(Stub_Skeleton_output_Average_color&& other) noexcept
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
Stub_Skeleton_output_Average_color::Stub_Skeleton_output_Average_color()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_Skeleton_output_Average_color::Stub_Skeleton_output_Average_color(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_Skeleton_output_Average_color::Stub_Skeleton_output_Average_color(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_Skeleton_output_Average_color::~Stub_Skeleton_output_Average_color()
{
}

// --> Do NOT EDIT <--
void Stub_Skeleton_output_Average_color::clear()
{
	this->R = static_cast<int64_t>(0);
	this->G = static_cast<int64_t>(0);
	this->B = static_cast<int64_t>(0);
}

// --> Do NOT EDIT <--
void Stub_Skeleton_output_Average_color::parseJson(const char *str)
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
void Stub_Skeleton_output_Average_color::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// R
	if ((value.HasMember("R")) && value["R"].IsInt64())
	{
		set_R( value["R"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'R'");

	// G
	if ((value.HasMember("G")) && value["G"].IsInt64())
	{
		set_G( value["G"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'G'");

	// B
	if ((value.HasMember("B")) && value["B"].IsInt64())
	{
		set_B( value["B"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'B'");

}

// --> Do NOT EDIT <--
std::string Stub_Skeleton_output_Average_color::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_Skeleton_output_Average_color::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_Skeleton_output_Average_color::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // R
		node.AddMember("R", rapidjson::Value().SetInt64( get_R() ), allocator);
	}
	{ // G
		node.AddMember("G", rapidjson::Value().SetInt64( get_G() ), allocator);
	}
	{ // B
		node.AddMember("B", rapidjson::Value().SetInt64( get_B() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
int64_t Stub_Skeleton_output_Average_color::get_R() const
{
	return( this->R );
}

// --> Do NOT EDIT <--
const int64_t Stub_Skeleton_output_Average_color::getconst_R() const
{
	return( this->R );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_output_Average_color::set_R(int64_t value)
{
	this->R = value;
}

// --> Do NOT EDIT <--
int64_t Stub_Skeleton_output_Average_color::get_G() const
{
	return( this->G );
}

// --> Do NOT EDIT <--
const int64_t Stub_Skeleton_output_Average_color::getconst_G() const
{
	return( this->G );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_output_Average_color::set_G(int64_t value)
{
	this->G = value;
}

// --> Do NOT EDIT <--
int64_t Stub_Skeleton_output_Average_color::get_B() const
{
	return( this->B );
}

// --> Do NOT EDIT <--
const int64_t Stub_Skeleton_output_Average_color::getconst_B() const
{
	return( this->B );
}

// --> Do NOT EDIT <--
void Stub_Skeleton_output_Average_color::set_B(int64_t value)
{
	this->B = value;
}


} // namespace test
} // namespace ConnectedVision