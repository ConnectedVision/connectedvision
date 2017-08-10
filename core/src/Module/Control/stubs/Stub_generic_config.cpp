/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_config.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_config.h"
#include "../Class_generic_config.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {




// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_config::Stub_generic_config(const Stub_generic_config& other)
{
	// TODO: other.readLock
	// id
	id = other.id;
	// timestamp
	timestamp = other.timestamp;
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// description
	if ( other.description ) 
		description = boost::make_shared<std::string>(*other.description);
	// aliasID
	{
		const auto& n0 = other.aliasID;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<Class_generic_config_aliasID>( *n0->at(i0) );
		}
		aliasID = a0;
	}
	// version
	version = other.version;
	// moduleID
	moduleID = other.moduleID;
	// moduleURI
	if ( other.moduleURI ) 
		moduleURI = boost::make_shared<std::string>(*other.moduleURI);
	// configFeatures
	if ( other.configFeatures ) 
		configFeatures = boost::make_shared<Class_generic_config_configFeatures>(*other.configFeatures);
	// callback
	if ( other.callback ) 
		callback = boost::make_shared<Class_generic_config_callback>(*other.callback);
	// params
	if ( other.params ) 
		params = boost::make_shared<std::string>(*other.params);
	// initialParams
	if ( other.initialParams ) 
		initialParams = boost::make_shared<std::string>(*other.initialParams);
	// chain
	{
		const auto& n0 = other.chain;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_config_chain>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<Class_generic_config_chain>( *n0->at(i0) );
		}
		chain = a0;
	}
	// configID
	configID = other.configID;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_config& Stub_generic_config::operator =(const Stub_generic_config& other)
{
	Stub_generic_config tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_config& Stub_generic_config::operator =(Stub_generic_config&& other) noexcept
{
	// id
    std::swap(id, other.id);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// name
    std::swap(name, other.name);
	// description
    std::swap(description, other.description);
	// aliasID
    std::swap(aliasID, other.aliasID);
	// version
    std::swap(version, other.version);
	// moduleID
    std::swap(moduleID, other.moduleID);
	// moduleURI
    std::swap(moduleURI, other.moduleURI);
	// configFeatures
    std::swap(configFeatures, other.configFeatures);
	// callback
    std::swap(callback, other.callback);
	// params
    std::swap(params, other.params);
	// initialParams
    std::swap(initialParams, other.initialParams);
	// chain
    std::swap(chain, other.chain);
	// configID
    std::swap(configID, other.configID);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_config::Stub_generic_config()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_config::Stub_generic_config(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_config::Stub_generic_config(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_config::~Stub_generic_config()
{
}

// --> Do NOT EDIT <--
void Stub_generic_config::clear()
{
	this->id = "";
	this->timestamp = 0;
	this->name.reset( new std::string("") );
	this->description.reset( new std::string("") );
	this->aliasID.reset( new std::vector<boost::shared_ptr<Class_generic_config_aliasID>> );
	this->version = static_cast<int64_t>(0);
	this->moduleID = "";
	this->moduleURI.reset( new std::string("") );
	this->configFeatures.reset( new Class_generic_config_configFeatures );
	this->callback.reset( new Class_generic_config_callback );
	this->params.reset( new std::string("") );
	this->initialParams.reset( new std::string("") );
	this->chain.reset( new std::vector<boost::shared_ptr<Class_generic_config_chain>> );
	this->configID = "";
}

// --> Do NOT EDIT <--
void Stub_generic_config::parseJson(const char *str)
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
void Stub_generic_config::parseJson(const rapidjson::Value& value)
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

	// timestamp
	if ((value.HasMember("timestamp")) && value["timestamp"].IsInt64())
	{
		set_timestamp( value["timestamp"].GetInt64() );
	}
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

	// aliasID
	if ((value.HasMember("aliasID")) && value["aliasID"].IsArray())
	{
		const rapidjson::Value& n0 = value["aliasID"];
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> a0( new std::vector<boost::shared_ptr<Class_generic_config_aliasID>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<Class_generic_config_aliasID>( new Class_generic_config_aliasID( n0[i0] ) );
		}
		set_aliasID( a0 );
	}
	// version
	if ((value.HasMember("version")) && value["version"].IsInt64())
	{
		set_version( value["version"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'version'");

	// moduleID
	if ((value.HasMember("moduleID")) && value["moduleID"].IsString())
	{
		set_moduleID( ConnectedVision::strToID( value["moduleID"].GetString() ) );
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

	// configFeatures
	if ((value.HasMember("configFeatures")) && value["configFeatures"].IsObject())
	{
		set_configFeatures( boost::shared_ptr<Class_generic_config_configFeatures>( new Class_generic_config_configFeatures( value["configFeatures"] ) ) );
	}
	// callback
	if ((value.HasMember("callback")) && value["callback"].IsObject())
	{
		set_callback( boost::shared_ptr<Class_generic_config_callback>( new Class_generic_config_callback( value["callback"] ) ) );
	}
	// params
	if ((value.HasMember("params")) && ( value["params"].IsObject() || value["params"].IsArray() || value["params"].IsInt64() || value["params"].IsNumber() || value["params"].IsBool() ))
	{
		set_params( boost::shared_ptr<std::string>( new std::string( ConnectedVision::jsonToStr(value["params"]) ) ) );
	}
	// initialParams
	if ((value.HasMember("initialParams")) && ( value["initialParams"].IsObject() || value["initialParams"].IsArray() || value["initialParams"].IsInt64() || value["initialParams"].IsNumber() || value["initialParams"].IsBool() ))
	{
		set_initialParams( boost::shared_ptr<std::string>( new std::string( ConnectedVision::jsonToStr(value["initialParams"]) ) ) );
	}
	// chain
	if ((value.HasMember("chain")) && value["chain"].IsArray())
	{
		const rapidjson::Value& n0 = value["chain"];
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> a0( new std::vector<boost::shared_ptr<Class_generic_config_chain>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<Class_generic_config_chain>( new Class_generic_config_chain( n0[i0] ) );
		}
		set_chain( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'chain'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_config::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_config::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_config::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_id() ), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // description
		node.AddMember("description", rapidjson::Value().SetString( get_description()->c_str(), allocator), allocator);
	}
	{ // aliasID
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>>&& a0 = get_aliasID(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final dimension of array, add actual value
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				n0.PushBack(a0->at(i0)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
			}
		}
		node.AddMember("aliasID", n0, allocator);
	}
	{ // version
		node.AddMember("version", rapidjson::Value().SetInt64( get_version() ), allocator);
	}
	{ // moduleID
		node.AddMember("moduleID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_moduleID() ), allocator), allocator);
	}
	{ // moduleURI
		node.AddMember("moduleURI", rapidjson::Value().SetString( get_moduleURI()->c_str(), allocator), allocator);
	}
	{ // configFeatures
		node.AddMember("configFeatures", get_configFeatures()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // callback
		node.AddMember("callback", get_callback()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // params
		rapidjson::Document doc(&allocator);
		doc.Parse<0>( get_params()->c_str() );
		node.AddMember("params", static_cast<rapidjson::Value&>(doc), allocator);
	}
	{ // initialParams
		rapidjson::Document doc(&allocator);
		doc.Parse<0>( get_initialParams()->c_str() );
		node.AddMember("initialParams", static_cast<rapidjson::Value&>(doc), allocator);
	}
	{ // chain
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>>&& a0 = get_chain(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final dimension of array, add actual value
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				n0.PushBack(a0->at(i0)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
			}
		}
		node.AddMember("chain", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_config::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_config::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_config::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_config::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config::get_description() const
{
	return( this->description );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config::getconst_description() const
{
	return( boost::static_pointer_cast<const std::string>(this->description) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_description(boost::shared_ptr<std::string> value)
{
	this->description = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> Stub_generic_config::get_aliasID() const
{
	return( this->aliasID );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> Stub_generic_config::getconst_aliasID() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<Class_generic_config_aliasID>>>(this->aliasID) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_aliasID(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_aliasID>>> value)
{
	this->aliasID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_config_aliasID> Stub_generic_config::get_aliasID(int index) const
{
	return( this->aliasID->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<Class_generic_config_aliasID>& Stub_generic_config::getconst_aliasID(int index) const
{
	return( this->aliasID->at(index) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::add_aliasID(boost::shared_ptr<Class_generic_config_aliasID> value)
{
	this->aliasID->push_back(value);
}

// --> Do NOT EDIT <--
int64_t Stub_generic_config::get_version() const
{
	return( this->version );
}

// --> Do NOT EDIT <--
const int64_t Stub_generic_config::getconst_version() const
{
	return( this->version );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_version(int64_t value)
{
	this->version = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_config::get_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_config::getconst_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_moduleID(ConnectedVision::id_t value)
{
	this->moduleID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config::get_moduleURI() const
{
	return( this->moduleURI );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config::getconst_moduleURI() const
{
	return( boost::static_pointer_cast<const std::string>(this->moduleURI) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_moduleURI(boost::shared_ptr<std::string> value)
{
	this->moduleURI = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_config_configFeatures> Stub_generic_config::get_configFeatures() const
{
	return( this->configFeatures );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_generic_config_configFeatures> Stub_generic_config::getconst_configFeatures() const
{
	return( boost::static_pointer_cast<const Class_generic_config_configFeatures>(this->configFeatures) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_configFeatures(boost::shared_ptr<Class_generic_config_configFeatures> value)
{
	this->configFeatures = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_config_callback> Stub_generic_config::get_callback() const
{
	return( this->callback );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_generic_config_callback> Stub_generic_config::getconst_callback() const
{
	return( boost::static_pointer_cast<const Class_generic_config_callback>(this->callback) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_callback(boost::shared_ptr<Class_generic_config_callback> value)
{
	this->callback = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config::get_params() const
{
	return( this->params );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config::getconst_params() const
{
	return( boost::static_pointer_cast<const std::string>(this->params) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_params(boost::shared_ptr<std::string> value)
{
	this->params = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_config::get_initialParams() const
{
	return( this->initialParams );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_config::getconst_initialParams() const
{
	return( boost::static_pointer_cast<const std::string>(this->initialParams) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_initialParams(boost::shared_ptr<std::string> value)
{
	this->initialParams = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> Stub_generic_config::get_chain() const
{
	return( this->chain );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_config_chain>>> Stub_generic_config::getconst_chain() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<Class_generic_config_chain>>>(this->chain) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_chain(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> value)
{
	this->chain = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_config_chain> Stub_generic_config::get_chain(int index) const
{
	return( this->chain->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<Class_generic_config_chain>& Stub_generic_config::getconst_chain(int index) const
{
	return( this->chain->at(index) );
}

// --> Do NOT EDIT <--
void Stub_generic_config::add_chain(boost::shared_ptr<Class_generic_config_chain> value)
{
	this->chain->push_back(value);
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_config::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_config::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_generic_config::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}


} // namespace ConnectedVision