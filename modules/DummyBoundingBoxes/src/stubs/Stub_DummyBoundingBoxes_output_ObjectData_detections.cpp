// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_ObjectData_detections.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_DummyBoundingBoxes_output_ObjectData_detections.h"
#include "../Class_DummyBoundingBoxes_output_ObjectData_detections.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_DummyBoundingBoxes_output_ObjectData_detections::Stub_DummyBoundingBoxes_output_ObjectData_detections(const Stub_DummyBoundingBoxes_output_ObjectData_detections& other)
{
	// TODO: other.readLock
	// timestamp
	timestamp = other.timestamp;
	// confidence
	confidence = other.confidence;
	// boundingBox
	if ( other.boundingBox ) 
		boundingBox = boost::make_shared<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox>(*other.boundingBox);
	// basePoint
	if ( other.basePoint ) 
		basePoint = boost::make_shared<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint>(*other.basePoint);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_DummyBoundingBoxes_output_ObjectData_detections& Stub_DummyBoundingBoxes_output_ObjectData_detections::operator =(const Stub_DummyBoundingBoxes_output_ObjectData_detections& other)
{
	Stub_DummyBoundingBoxes_output_ObjectData_detections tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_DummyBoundingBoxes_output_ObjectData_detections& Stub_DummyBoundingBoxes_output_ObjectData_detections::operator =(Stub_DummyBoundingBoxes_output_ObjectData_detections&& other) noexcept
{
	// timestamp
    std::swap(timestamp, other.timestamp);
	// confidence
    std::swap(confidence, other.confidence);
	// boundingBox
    std::swap(boundingBox, other.boundingBox);
	// basePoint
    std::swap(basePoint, other.basePoint);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_DummyBoundingBoxes_output_ObjectData_detections::Stub_DummyBoundingBoxes_output_ObjectData_detections()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData_detections::Stub_DummyBoundingBoxes_output_ObjectData_detections(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData_detections::Stub_DummyBoundingBoxes_output_ObjectData_detections(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData_detections::~Stub_DummyBoundingBoxes_output_ObjectData_detections()
{
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections::clear()
{
	this->timestamp = 0;
	this->confidence = static_cast<double>(1);
	this->boundingBox.reset( new Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox );
	this->basePoint.reset( new Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections::parseJson(const char *str)
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
void Stub_DummyBoundingBoxes_output_ObjectData_detections::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestamp'");

	// confidence
	if ((value.HasMember("confidence")) && value["confidence"].IsNumber())
	{
		set_confidence( value["confidence"].GetDouble() );
	}
	// boundingBox
	if ((value.HasMember("boundingBox")) && value["boundingBox"].IsObject())
	{
		set_boundingBox( boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox>( new Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox( value["boundingBox"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'boundingBox'");

	// basePoint
	if ((value.HasMember("basePoint")) && value["basePoint"].IsObject())
	{
		set_basePoint( boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint>( new Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint( value["basePoint"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'basePoint'");

}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_output_ObjectData_detections::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_output_ObjectData_detections::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_DummyBoundingBoxes_output_ObjectData_detections::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // confidence
		node.AddMember("confidence", rapidjson::Value().SetDouble( get_confidence() ), allocator);
	}
	{ // boundingBox
		node.AddMember("boundingBox", get_boundingBox()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // basePoint
		node.AddMember("basePoint", get_basePoint()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_output_ObjectData_detections::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_output_ObjectData_detections::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
double Stub_DummyBoundingBoxes_output_ObjectData_detections::get_confidence() const
{
	return( this->confidence );
}

// --> Do NOT EDIT <--
const double Stub_DummyBoundingBoxes_output_ObjectData_detections::getconst_confidence() const
{
	return( this->confidence );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections::set_confidence(double value)
{
	this->confidence = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> Stub_DummyBoundingBoxes_output_ObjectData_detections::get_boundingBox() const
{
	return( this->boundingBox );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> Stub_DummyBoundingBoxes_output_ObjectData_detections::getconst_boundingBox() const
{
	return( boost::static_pointer_cast<const Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox>(this->boundingBox) );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections::set_boundingBox(boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox> value)
{
	this->boundingBox = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> Stub_DummyBoundingBoxes_output_ObjectData_detections::get_basePoint() const
{
	return( this->basePoint );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> Stub_DummyBoundingBoxes_output_ObjectData_detections::getconst_basePoint() const
{
	return( boost::static_pointer_cast<const Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint>(this->basePoint) );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData_detections::set_basePoint(boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint> value)
{
	this->basePoint = value;
}


} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision