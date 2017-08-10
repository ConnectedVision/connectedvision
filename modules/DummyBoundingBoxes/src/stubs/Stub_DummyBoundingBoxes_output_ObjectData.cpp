// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_output_ObjectData.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_DummyBoundingBoxes_output_ObjectData.h"
#include "../Class_DummyBoundingBoxes_output_ObjectData.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_DummyBoundingBoxes_output_ObjectData::Stub_DummyBoundingBoxes_output_ObjectData(const Stub_DummyBoundingBoxes_output_ObjectData& other)
{
	// TODO: other.readLock
	// configID
	configID = other.configID;
	// id
	id = other.id;
	// timestamp
	timestamp = other.timestamp;
	// objectID
	objectID = other.objectID;
	// detections
	{
		const auto& n0 = other.detections;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<Class_DummyBoundingBoxes_output_ObjectData_detections>( *n0->at(i0) );
		}
		detections = a0;
	}
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_DummyBoundingBoxes_output_ObjectData& Stub_DummyBoundingBoxes_output_ObjectData::operator =(const Stub_DummyBoundingBoxes_output_ObjectData& other)
{
	Stub_DummyBoundingBoxes_output_ObjectData tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_DummyBoundingBoxes_output_ObjectData& Stub_DummyBoundingBoxes_output_ObjectData::operator =(Stub_DummyBoundingBoxes_output_ObjectData&& other) noexcept
{
	// configID
    std::swap(configID, other.configID);
	// id
    std::swap(id, other.id);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// objectID
    std::swap(objectID, other.objectID);
	// detections
    std::swap(detections, other.detections);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_DummyBoundingBoxes_output_ObjectData::Stub_DummyBoundingBoxes_output_ObjectData()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData::Stub_DummyBoundingBoxes_output_ObjectData(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData::Stub_DummyBoundingBoxes_output_ObjectData(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_DummyBoundingBoxes_output_ObjectData::~Stub_DummyBoundingBoxes_output_ObjectData()
{
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::clear()
{
	this->configID = "";
	this->id = "";
	this->timestamp = 0;
	this->objectID = "";
	this->detections.reset( new std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>> );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::parseJson(const char *str)
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
void Stub_DummyBoundingBoxes_output_ObjectData::parseJson(const rapidjson::Value& value)
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

	// objectID
	if ((value.HasMember("objectID")) && value["objectID"].IsString())
	{
		set_objectID( ConnectedVision::strToID( value["objectID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'objectID'");

	// detections
	if ((value.HasMember("detections")) && value["detections"].IsArray())
	{
		const rapidjson::Value& n0 = value["detections"];
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> a0( new std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>( new Class_DummyBoundingBoxes_output_ObjectData_detections( n0[i0] ) );
		}
		set_detections( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'detections'");

}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_output_ObjectData::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_DummyBoundingBoxes_output_ObjectData::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_DummyBoundingBoxes_output_ObjectData::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
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
	{ // objectID
		node.AddMember("objectID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_objectID() ), allocator), allocator);
	}
	{ // detections
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>>&& a0 = get_detections(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final dimension of array, add actual value
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				n0.PushBack(a0->at(i0)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
			}
		}
		node.AddMember("detections", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DummyBoundingBoxes_output_ObjectData::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DummyBoundingBoxes_output_ObjectData::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DummyBoundingBoxes_output_ObjectData::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DummyBoundingBoxes_output_ObjectData::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_output_ObjectData::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DummyBoundingBoxes_output_ObjectData::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DummyBoundingBoxes_output_ObjectData::get_objectID() const
{
	return( this->objectID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DummyBoundingBoxes_output_ObjectData::getconst_objectID() const
{
	return( this->objectID );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::set_objectID(ConnectedVision::id_t value)
{
	this->objectID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> Stub_DummyBoundingBoxes_output_ObjectData::get_detections() const
{
	return( this->detections );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> Stub_DummyBoundingBoxes_output_ObjectData::getconst_detections() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>>(this->detections) );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::set_detections(boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>> value)
{
	this->detections = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections> Stub_DummyBoundingBoxes_output_ObjectData::get_detections(int index) const
{
	return( this->detections->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>& Stub_DummyBoundingBoxes_output_ObjectData::getconst_detections(int index) const
{
	return( this->detections->at(index) );
}

// --> Do NOT EDIT <--
void Stub_DummyBoundingBoxes_output_ObjectData::add_detections(boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections> value)
{
	this->detections->push_back(value);
}


} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision