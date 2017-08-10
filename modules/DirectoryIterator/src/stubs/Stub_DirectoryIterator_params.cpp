// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DirectoryIterator_params.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_DirectoryIterator_params.h"
#include "../Class_DirectoryIterator_params.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_DirectoryIterator_params::Stub_DirectoryIterator_params(const Stub_DirectoryIterator_params& other)
{
	// TODO: other.readLock
	// rootDirectory
	if ( other.rootDirectory ) 
		rootDirectory = boost::make_shared<std::string>(*other.rootDirectory);
	// fileTypes
	{
		const auto& n0 = other.fileTypes;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<std::string>( *n0->at(i0) );
		}
		fileTypes = a0;
	}
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_DirectoryIterator_params& Stub_DirectoryIterator_params::operator =(const Stub_DirectoryIterator_params& other)
{
	Stub_DirectoryIterator_params tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_DirectoryIterator_params& Stub_DirectoryIterator_params::operator =(Stub_DirectoryIterator_params&& other) noexcept
{
	// rootDirectory
    std::swap(rootDirectory, other.rootDirectory);
	// fileTypes
    std::swap(fileTypes, other.fileTypes);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_DirectoryIterator_params::Stub_DirectoryIterator_params()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_DirectoryIterator_params::Stub_DirectoryIterator_params(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_DirectoryIterator_params::Stub_DirectoryIterator_params(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_DirectoryIterator_params::~Stub_DirectoryIterator_params()
{
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::clear()
{
	this->rootDirectory.reset( new std::string(".") );
	this->fileTypes.reset( new std::vector<boost::shared_ptr<std::string>> );
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::parseJson(const char *str)
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
void Stub_DirectoryIterator_params::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// rootDirectory
	if ((value.HasMember("rootDirectory")) && value["rootDirectory"].IsString())
	{
		set_rootDirectory( boost::shared_ptr<std::string>( new std::string( value["rootDirectory"].GetString() ) ) );
	}
	// fileTypes
	if ((value.HasMember("fileTypes")) && value["fileTypes"].IsArray())
	{
		const rapidjson::Value& n0 = value["fileTypes"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> a0( new std::vector<boost::shared_ptr<std::string>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<std::string>( new std::string( n0[i0].GetString() ) );
		}
		set_fileTypes( a0 );
	}
}

// --> Do NOT EDIT <--
std::string Stub_DirectoryIterator_params::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_DirectoryIterator_params::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_DirectoryIterator_params::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // rootDirectory
		node.AddMember("rootDirectory", rapidjson::Value().SetString( get_rootDirectory()->c_str(), allocator), allocator);
	}
	{ // fileTypes
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a0 = get_fileTypes(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add string
			n0.PushBack(rapidjson::Value().SetString( a0->at(i0)->c_str(), allocator), allocator);
		}
		node.AddMember("fileTypes", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_DirectoryIterator_params::get_rootDirectory() const
{
	return( this->rootDirectory );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_DirectoryIterator_params::getconst_rootDirectory() const
{
	return( boost::static_pointer_cast<const std::string>(this->rootDirectory) );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::set_rootDirectory(boost::shared_ptr<std::string> value)
{
	this->rootDirectory = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> Stub_DirectoryIterator_params::get_fileTypes() const
{
	return( this->fileTypes );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> Stub_DirectoryIterator_params::getconst_fileTypes() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::string>>>(this->fileTypes) );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::set_fileTypes(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value)
{
	this->fileTypes = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_DirectoryIterator_params::get_fileTypes(int index) const
{
	return( this->fileTypes->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::string>& Stub_DirectoryIterator_params::getconst_fileTypes(int index) const
{
	return( this->fileTypes->at(index) );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::add_fileTypes(boost::shared_ptr<std::string> value)
{
	this->fileTypes->push_back(value);
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_DirectoryIterator_params::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_DirectoryIterator_params::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_DirectoryIterator_params::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_DirectoryIterator_params::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_DirectoryIterator_params::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision