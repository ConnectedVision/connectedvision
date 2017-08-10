// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DirectoryIterator_output_FileMetadata.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_DirectoryIterator_output_FileMetadata.h"
#include "../Class_DirectoryIterator_output_FileMetadata.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_DirectoryIterator_output_FileMetadata::Stub_DirectoryIterator_output_FileMetadata(const Stub_DirectoryIterator_output_FileMetadata& other)
{
	// TODO: other.readLock
	// id
	id = other.id;
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
	// filePath
	if ( other.filePath ) 
		filePath = boost::make_shared<std::string>(*other.filePath);
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_DirectoryIterator_output_FileMetadata& Stub_DirectoryIterator_output_FileMetadata::operator =(const Stub_DirectoryIterator_output_FileMetadata& other)
{
	Stub_DirectoryIterator_output_FileMetadata tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_DirectoryIterator_output_FileMetadata& Stub_DirectoryIterator_output_FileMetadata::operator =(Stub_DirectoryIterator_output_FileMetadata&& other) noexcept
{
	// id
    std::swap(id, other.id);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// filePath
    std::swap(filePath, other.filePath);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_DirectoryIterator_output_FileMetadata::Stub_DirectoryIterator_output_FileMetadata()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_DirectoryIterator_output_FileMetadata::Stub_DirectoryIterator_output_FileMetadata(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_DirectoryIterator_output_FileMetadata::Stub_DirectoryIterator_output_FileMetadata(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_DirectoryIterator_output_FileMetadata::~Stub_DirectoryIterator_output_FileMetadata()
{
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_output_FileMetadata::clear()
{
	this->id = "";
	this->configID = "";
	this->timestamp = 0;
	this->filePath.reset( new std::string("") );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_output_FileMetadata::parseJson(const char *str)
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
void Stub_DirectoryIterator_output_FileMetadata::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// id
	if ((value.HasMember("id")) && value["id"].IsString())
	{
		set_id( ConnectedVision::strToID( value["id"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'id'");

	// configID
	if ((value.HasMember("configID")) && value["configID"].IsString())
	{
		set_configID( ConnectedVision::strToID( value["configID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'configID'");

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'timestamp'");

	// filePath
	if ((value.HasMember("filePath")) && value["filePath"].IsString())
	{
		set_filePath( boost::shared_ptr<std::string>( new std::string( value["filePath"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'filePath'");

}

// --> Do NOT EDIT <--
std::string Stub_DirectoryIterator_output_FileMetadata::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_DirectoryIterator_output_FileMetadata::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_DirectoryIterator_output_FileMetadata::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_id() ), allocator), allocator);
	}
	{ // configID
		node.AddMember("configID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_configID() ), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // filePath
		node.AddMember("filePath", rapidjson::Value().SetString( get_filePath()->c_str(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DirectoryIterator_output_FileMetadata::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DirectoryIterator_output_FileMetadata::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_output_FileMetadata::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DirectoryIterator_output_FileMetadata::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DirectoryIterator_output_FileMetadata::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_output_FileMetadata::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DirectoryIterator_output_FileMetadata::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DirectoryIterator_output_FileMetadata::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_output_FileMetadata::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_DirectoryIterator_output_FileMetadata::get_filePath() const
{
	return( this->filePath );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_DirectoryIterator_output_FileMetadata::getconst_filePath() const
{
	return( boost::static_pointer_cast<const std::string>(this->filePath) );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_output_FileMetadata::set_filePath(boost::shared_ptr<std::string> value)
{
	this->filePath = value;
}


} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision