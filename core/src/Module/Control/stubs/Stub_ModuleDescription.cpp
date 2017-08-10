/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ModuleDescription.h"
#include "../Class_ModuleDescription.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_ModuleDescription::Stub_ModuleDescription(const Stub_ModuleDescription& other)
{
	// TODO: other.readLock
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// description
	if ( other.description ) 
		description = boost::make_shared<std::string>(*other.description);
	// version
	version = other.version;
	// moduleID
	if ( other.moduleID ) 
		moduleID = boost::make_shared<std::string>(*other.moduleID);
	// moduleURI
	if ( other.moduleURI ) 
		moduleURI = boost::make_shared<std::string>(*other.moduleURI);
	// APIVersion
	APIVersion = other.APIVersion;
	// moduleFeatures
	if ( other.moduleFeatures ) 
		moduleFeatures = boost::make_shared<Class_ModuleDescription_moduleFeatures>(*other.moduleFeatures);
	// configFeatures
	if ( other.configFeatures ) 
		configFeatures = boost::make_shared<Class_ModuleDescription_configFeatures>(*other.configFeatures);
	// author
	if ( other.author ) 
		author = boost::make_shared<std::string>(*other.author);
	// params
	if ( other.params ) 
		params = boost::make_shared<Class_ModuleDescription_params>(*other.params);
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ModuleDescription& Stub_ModuleDescription::operator =(const Stub_ModuleDescription& other)
{
	Stub_ModuleDescription tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ModuleDescription& Stub_ModuleDescription::operator =(Stub_ModuleDescription&& other) noexcept
{
	// name
    std::swap(name, other.name);
	// description
    std::swap(description, other.description);
	// version
    std::swap(version, other.version);
	// moduleID
    std::swap(moduleID, other.moduleID);
	// moduleURI
    std::swap(moduleURI, other.moduleURI);
	// APIVersion
    std::swap(APIVersion, other.APIVersion);
	// moduleFeatures
    std::swap(moduleFeatures, other.moduleFeatures);
	// configFeatures
    std::swap(configFeatures, other.configFeatures);
	// author
    std::swap(author, other.author);
	// params
    std::swap(params, other.params);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ModuleDescription::Stub_ModuleDescription()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ModuleDescription::Stub_ModuleDescription(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ModuleDescription::Stub_ModuleDescription(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ModuleDescription::~Stub_ModuleDescription()
{
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::clear()
{
	this->name.reset( new std::string("") );
	this->description.reset( new std::string("") );
	this->version = static_cast<double>(0.0);
	this->moduleID.reset( new std::string("") );
	this->moduleURI.reset( new std::string("") );
	this->APIVersion = static_cast<double>(0.0);
	this->moduleFeatures.reset( new Class_ModuleDescription_moduleFeatures );
	this->configFeatures.reset( new Class_ModuleDescription_configFeatures );
	this->author.reset( new std::string("") );
	this->params.reset( new Class_ModuleDescription_params );
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::parseJson(const char *str)
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
void Stub_ModuleDescription::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

	// name
	if ((value.HasMember("name")) && value["name"].IsString())
	{
		set_name( boost::shared_ptr<std::string>( new std::string( value["name"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'name'");

	// description
	if ((value.HasMember("description")) && value["description"].IsString())
	{
		set_description( boost::shared_ptr<std::string>( new std::string( value["description"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'description'");

	// version
	if ((value.HasMember("version")) && value["version"].IsNumber())
	{
		set_version( value["version"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'version'");

	// moduleID
	if ((value.HasMember("moduleID")) && value["moduleID"].IsString())
	{
		set_moduleID( boost::shared_ptr<std::string>( new std::string( value["moduleID"].GetString() ) ) );
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

	// APIVersion
	if ((value.HasMember("APIVersion")) && value["APIVersion"].IsNumber())
	{
		set_APIVersion( value["APIVersion"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'APIVersion'");

	// moduleFeatures
	if ((value.HasMember("moduleFeatures")) && value["moduleFeatures"].IsObject())
	{
		set_moduleFeatures( boost::shared_ptr<Class_ModuleDescription_moduleFeatures>( new Class_ModuleDescription_moduleFeatures( value["moduleFeatures"] ) ) );
	}
	// configFeatures
	if ((value.HasMember("configFeatures")) && value["configFeatures"].IsObject())
	{
		set_configFeatures( boost::shared_ptr<Class_ModuleDescription_configFeatures>( new Class_ModuleDescription_configFeatures( value["configFeatures"] ) ) );
	}
	// author
	if ((value.HasMember("author")) && value["author"].IsString())
	{
		set_author( boost::shared_ptr<std::string>( new std::string( value["author"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'author'");

	// params
	if ((value.HasMember("params")) && value["params"].IsObject())
	{
		set_params( boost::shared_ptr<Class_ModuleDescription_params>( new Class_ModuleDescription_params( value["params"] ) ) );
	}
}

// --> Do NOT EDIT <--
std::string Stub_ModuleDescription::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ModuleDescription::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ModuleDescription::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // description
		node.AddMember("description", rapidjson::Value().SetString( get_description()->c_str(), allocator), allocator);
	}
	{ // version
		node.AddMember("version", rapidjson::Value().SetDouble( get_version() ), allocator);
	}
	{ // moduleID
		node.AddMember("moduleID", rapidjson::Value().SetString( get_moduleID()->c_str(), allocator), allocator);
	}
	{ // moduleURI
		node.AddMember("moduleURI", rapidjson::Value().SetString( get_moduleURI()->c_str(), allocator), allocator);
	}
	{ // APIVersion
		node.AddMember("APIVersion", rapidjson::Value().SetDouble( get_APIVersion() ), allocator);
	}
	{ // moduleFeatures
		node.AddMember("moduleFeatures", get_moduleFeatures()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // configFeatures
		node.AddMember("configFeatures", get_configFeatures()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // author
		node.AddMember("author", rapidjson::Value().SetString( get_author()->c_str(), allocator), allocator);
	}
	{ // params
		node.AddMember("params", get_params()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleDescription::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleDescription::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleDescription::get_description() const
{
	return( this->description );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleDescription::getconst_description() const
{
	return( boost::static_pointer_cast<const std::string>(this->description) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_description(boost::shared_ptr<std::string> value)
{
	this->description = value;
}

// --> Do NOT EDIT <--
double Stub_ModuleDescription::get_version() const
{
	return( this->version );
}

// --> Do NOT EDIT <--
const double Stub_ModuleDescription::getconst_version() const
{
	return( this->version );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_version(double value)
{
	this->version = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleDescription::get_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleDescription::getconst_moduleID() const
{
	return( boost::static_pointer_cast<const std::string>(this->moduleID) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_moduleID(boost::shared_ptr<std::string> value)
{
	this->moduleID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleDescription::get_moduleURI() const
{
	return( this->moduleURI );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleDescription::getconst_moduleURI() const
{
	return( boost::static_pointer_cast<const std::string>(this->moduleURI) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_moduleURI(boost::shared_ptr<std::string> value)
{
	this->moduleURI = value;
}

// --> Do NOT EDIT <--
double Stub_ModuleDescription::get_APIVersion() const
{
	return( this->APIVersion );
}

// --> Do NOT EDIT <--
const double Stub_ModuleDescription::getconst_APIVersion() const
{
	return( this->APIVersion );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_APIVersion(double value)
{
	this->APIVersion = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_ModuleDescription_moduleFeatures> Stub_ModuleDescription::get_moduleFeatures() const
{
	return( this->moduleFeatures );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_ModuleDescription_moduleFeatures> Stub_ModuleDescription::getconst_moduleFeatures() const
{
	return( boost::static_pointer_cast<const Class_ModuleDescription_moduleFeatures>(this->moduleFeatures) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_moduleFeatures(boost::shared_ptr<Class_ModuleDescription_moduleFeatures> value)
{
	this->moduleFeatures = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_ModuleDescription_configFeatures> Stub_ModuleDescription::get_configFeatures() const
{
	return( this->configFeatures );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_ModuleDescription_configFeatures> Stub_ModuleDescription::getconst_configFeatures() const
{
	return( boost::static_pointer_cast<const Class_ModuleDescription_configFeatures>(this->configFeatures) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_configFeatures(boost::shared_ptr<Class_ModuleDescription_configFeatures> value)
{
	this->configFeatures = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleDescription::get_author() const
{
	return( this->author );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleDescription::getconst_author() const
{
	return( boost::static_pointer_cast<const std::string>(this->author) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_author(boost::shared_ptr<std::string> value)
{
	this->author = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_ModuleDescription_params> Stub_ModuleDescription::get_params() const
{
	return( this->params );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_ModuleDescription_params> Stub_ModuleDescription::getconst_params() const
{
	return( boost::static_pointer_cast<const Class_ModuleDescription_params>(this->params) );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_params(boost::shared_ptr<Class_ModuleDescription_params> value)
{
	this->params = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ModuleDescription::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_ModuleDescription::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_ModuleDescription::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_ModuleDescription::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_ModuleDescription::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace ConnectedVision