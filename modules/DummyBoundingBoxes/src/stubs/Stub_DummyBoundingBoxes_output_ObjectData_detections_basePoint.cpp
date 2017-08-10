// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint.h"
#include "../Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint(const Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint& other)
{
	// TODO: other.readLock
	// x
	x = other.x;
	// y
	y = other.y;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint& Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::operator =(const Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint& other)
{
	Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint& Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::operator =(Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint&& other) noexcept
{
	// x
    std::swap(x, other.x);
	// y
    std::swap(y, other.y);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::~Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint()
{
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::clear()
{
	this->x = static_cast<double>(0.0);
	this->y = static_cast<double>(0.0);
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::parseJson(const char *str)
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
void Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// x
	if ((value.HasMember("x")) && value["x"].IsNumber())
	{
		set_x( value["x"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'x'");

	// y
	if ((value.HasMember("y")) && value["y"].IsNumber())
	{
		set_y( value["y"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'y'");

}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // x
		node.AddMember("x", rapidjson::Value().SetDouble( get_x() ), allocator);
	}
	{ // y
		node.AddMember("y", rapidjson::Value().SetDouble( get_y() ), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
double Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::get_x() const
{
	return( this->x );
}

// --> Do NOT EDIT <--
const double Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::getconst_x() const
{
	return( this->x );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::set_x(double value)
{
	this->x = value;
}

// --> Do NOT EDIT <--
double Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::get_y() const
{
	return( this->y );
}

// --> Do NOT EDIT <--
const double Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::getconst_y() const
{
	return( this->y );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections_basePoint::set_y(double value)
{
	this->y = value;
}


} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision