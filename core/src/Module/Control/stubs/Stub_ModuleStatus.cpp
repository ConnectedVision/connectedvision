/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleStatus.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_ModuleStatus.h"
#include "../Class_ModuleStatus.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {

const boost::shared_ptr<std::string> Stub_ModuleStatus::moduleStatus_na = boost::make_shared<std::string>("n/a");
const boost::shared_ptr<std::string> Stub_ModuleStatus::moduleStatus_up = boost::make_shared<std::string>("up");
const boost::shared_ptr<std::string> Stub_ModuleStatus::moduleStatus_down = boost::make_shared<std::string>("down");



// --> Do NOT EDIT <--
/* copy constructors */
Stub_ModuleStatus::Stub_ModuleStatus(const Stub_ModuleStatus& other)
{
	// TODO: other.readLock
	// name
	if ( other.name ) 
		name = boost::make_shared<std::string>(*other.name);
	// moduleID
	moduleID = other.moduleID;
	// moduleStatus
	if ( other.moduleStatus ) 
		moduleStatus = boost::make_shared<std::string>(*other.moduleStatus);
	// configsRunning
	{
		const auto& n0 = other.configsRunning;
		auto a0 = boost::make_shared<std::vector<ConnectedVision::id_t>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			a0->at(i0) = n0->at(i0);
		}
		configsRunning = a0;
	}
	// configsWaiting
	{
		const auto& n0 = other.configsWaiting;
		auto a0 = boost::make_shared<std::vector<ConnectedVision::id_t>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			a0->at(i0) = n0->at(i0);
		}
		configsWaiting = a0;
	}
	// configID
	configID = other.configID;
	// timestamp
	timestamp = other.timestamp;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_ModuleStatus& Stub_ModuleStatus::operator =(const Stub_ModuleStatus& other)
{
	Stub_ModuleStatus tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_ModuleStatus& Stub_ModuleStatus::operator =(Stub_ModuleStatus&& other) noexcept
{
	// name
    std::swap(name, other.name);
	// moduleID
    std::swap(moduleID, other.moduleID);
	// moduleStatus
    std::swap(moduleStatus, other.moduleStatus);
	// configsRunning
    std::swap(configsRunning, other.configsRunning);
	// configsWaiting
    std::swap(configsWaiting, other.configsWaiting);
	// configID
    std::swap(configID, other.configID);
	// timestamp
    std::swap(timestamp, other.timestamp);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_ModuleStatus::Stub_ModuleStatus()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_ModuleStatus::Stub_ModuleStatus(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_ModuleStatus::Stub_ModuleStatus(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_ModuleStatus::~Stub_ModuleStatus()
{
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::clear()
{
	this->name.reset( new std::string("") );
	this->moduleID = "";
	this->moduleStatus.reset( new std::string("") );
	this->configsRunning.reset( new std::vector<ConnectedVision::id_t> );
	this->configsWaiting.reset( new std::vector<ConnectedVision::id_t> );
	this->configID = "";
	this->timestamp = 0;
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::parseJson(const char *str)
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
void Stub_ModuleStatus::parseJson(const rapidjson::Value& value)
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

	// moduleID
	if ((value.HasMember("moduleID")) && value["moduleID"].IsString())
	{
		set_moduleID( ConnectedVision::strToID( value["moduleID"].GetString() ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'moduleID'");

	// moduleStatus
	if ((value.HasMember("moduleStatus")) && value["moduleStatus"].IsString())
	{
		set_moduleStatus( boost::shared_ptr<std::string>( new std::string( value["moduleStatus"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'moduleStatus'");

	// configsRunning
	if ((value.HasMember("configsRunning")) && value["configsRunning"].IsArray())
	{
		const rapidjson::Value& n0 = value["configsRunning"];
		boost::shared_ptr<std::vector<ConnectedVision::id_t>> a0( new std::vector<ConnectedVision::id_t>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = ConnectedVision::strToID( n0[i0].GetString() );
		}
		set_configsRunning( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'configsRunning'");

	// configsWaiting
	if ((value.HasMember("configsWaiting")) && value["configsWaiting"].IsArray())
	{
		const rapidjson::Value& n0 = value["configsWaiting"];
		boost::shared_ptr<std::vector<ConnectedVision::id_t>> a0( new std::vector<ConnectedVision::id_t>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = ConnectedVision::strToID( n0[i0].GetString() );
		}
		set_configsWaiting( a0 );
	}
}

// --> Do NOT EDIT <--
std::string Stub_ModuleStatus::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_ModuleStatus::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_ModuleStatus::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // name
		node.AddMember("name", rapidjson::Value().SetString( get_name()->c_str(), allocator), allocator);
	}
	{ // moduleID
		node.AddMember("moduleID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_moduleID() ), allocator), allocator);
	}
	{ // moduleStatus
		node.AddMember("moduleStatus", rapidjson::Value().SetString( get_moduleStatus()->c_str(), allocator), allocator);
	}
	{ // configsRunning
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<ConnectedVision::id_t>>&& a0 = get_configsRunning(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add ID
			n0.PushBack(rapidjson::Value().SetString( ConnectedVision::IDToChar( a0->at(i0) ), allocator), allocator);
		}
		node.AddMember("configsRunning", n0, allocator);
	}
	{ // configsWaiting
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<ConnectedVision::id_t>>&& a0 = get_configsWaiting(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add ID
			n0.PushBack(rapidjson::Value().SetString( ConnectedVision::IDToChar( a0->at(i0) ), allocator), allocator);
		}
		node.AddMember("configsWaiting", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleStatus::get_name() const
{
	return( this->name );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleStatus::getconst_name() const
{
	return( boost::static_pointer_cast<const std::string>(this->name) );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_name(boost::shared_ptr<std::string> value)
{
	this->name = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ModuleStatus::get_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_ModuleStatus::getconst_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_moduleID(ConnectedVision::id_t value)
{
	this->moduleID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_ModuleStatus::get_moduleStatus() const
{
	return( this->moduleStatus );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_ModuleStatus::getconst_moduleStatus() const
{
	return( boost::static_pointer_cast<const std::string>(this->moduleStatus) );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_moduleStatus(boost::shared_ptr<std::string> value)
{
	this->moduleStatus = value;
}

// --> Do NOT EDIT <--
bool Stub_ModuleStatus::is_moduleStatus(const boost::shared_ptr<std::string> &value) const
{
	return ( (*this->moduleStatus) == (*value) );
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<ConnectedVision::id_t>> Stub_ModuleStatus::get_configsRunning() const
{
	return( this->configsRunning );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<ConnectedVision::id_t>> Stub_ModuleStatus::getconst_configsRunning() const
{
	return( boost::static_pointer_cast<const std::vector<ConnectedVision::id_t>>(this->configsRunning) );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_configsRunning(boost::shared_ptr<std::vector<ConnectedVision::id_t>> value)
{
	this->configsRunning = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ModuleStatus::get_configsRunning(int index) const
{
	return( this->configsRunning->at(index) );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t& Stub_ModuleStatus::getconst_configsRunning(int index) const
{
	return( this->configsRunning->at(index) );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::add_configsRunning(ConnectedVision::id_t value)
{
	this->configsRunning->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<ConnectedVision::id_t>> Stub_ModuleStatus::get_configsWaiting() const
{
	return( this->configsWaiting );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<ConnectedVision::id_t>> Stub_ModuleStatus::getconst_configsWaiting() const
{
	return( boost::static_pointer_cast<const std::vector<ConnectedVision::id_t>>(this->configsWaiting) );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_configsWaiting(boost::shared_ptr<std::vector<ConnectedVision::id_t>> value)
{
	this->configsWaiting = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ModuleStatus::get_configsWaiting(int index) const
{
	return( this->configsWaiting->at(index) );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t& Stub_ModuleStatus::getconst_configsWaiting(int index) const
{
	return( this->configsWaiting->at(index) );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::add_configsWaiting(ConnectedVision::id_t value)
{
	this->configsWaiting->push_back(value);
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_ModuleStatus::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_ModuleStatus::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_ModuleStatus::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_ModuleStatus::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_ModuleStatus::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}


} // namespace ConnectedVision