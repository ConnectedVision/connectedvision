/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_status.cpp
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "Stub_generic_status.h"
#include "../Class_generic_status.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {

const boost::shared_ptr<std::string> Stub_generic_status::status_na = boost::make_shared<std::string>("n/a");
const boost::shared_ptr<std::string> Stub_generic_status::status_init = boost::make_shared<std::string>("init");
const boost::shared_ptr<std::string> Stub_generic_status::status_starting = boost::make_shared<std::string>("starting");
const boost::shared_ptr<std::string> Stub_generic_status::status_running = boost::make_shared<std::string>("running");
const boost::shared_ptr<std::string> Stub_generic_status::status_stopping = boost::make_shared<std::string>("stopping");
const boost::shared_ptr<std::string> Stub_generic_status::status_stopped = boost::make_shared<std::string>("stopped");
const boost::shared_ptr<std::string> Stub_generic_status::status_finished = boost::make_shared<std::string>("finished");
const boost::shared_ptr<std::string> Stub_generic_status::status_error = boost::make_shared<std::string>("error");
const boost::shared_ptr<std::string> Stub_generic_status::status_recovering = boost::make_shared<std::string>("recovering");
const boost::shared_ptr<std::string> Stub_generic_status::status_reseting = boost::make_shared<std::string>("reseting");



// --> Do NOT EDIT <--
/* copy constructors */
Stub_generic_status::Stub_generic_status(const Stub_generic_status& other)
{
	// TODO: other.readLock
	// id
	id = other.id;
	// timestamp
	timestamp = other.timestamp;
	// moduleID
	moduleID = other.moduleID;
	// moduleURI
	if ( other.moduleURI ) 
		moduleURI = boost::make_shared<std::string>(*other.moduleURI);
	// commandQueue
	{
		const auto& n0 = other.commandQueue;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<std::string>( *n0->at(i0) );
		}
		commandQueue = a0;
	}
	// status
	if ( other.status ) 
		status = boost::make_shared<std::string>(*other.status);
	// message
	if ( other.message ) 
		message = boost::make_shared<std::string>(*other.message);
	// progress
	progress = other.progress;
	// startTime
	startTime = other.startTime;
	// systemTimeProcessing
	systemTimeProcessing = other.systemTimeProcessing;
	// estimatedFinishTime
	estimatedFinishTime = other.estimatedFinishTime;
	// qualityOfService
	if ( other.qualityOfService ) 
		qualityOfService = boost::make_shared<Class_generic_status_qualityOfService>(*other.qualityOfService);
	// stableResults
	{
		const auto& n0 = other.stableResults;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<Class_generic_status_stableResults>( *n0->at(i0) );
		}
		stableResults = a0;
	}
	// chain
	{
		const auto& n0 = other.chain;
		auto a0 = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>( (n0->size()) );
		for (size_t i0 = 0; i0 < n0->size(); ++i0)
		{
			if ( n0->at(i0) )
				a0->at(i0) = boost::make_shared<std::string>( *n0->at(i0) );
		}
		chain = a0;
	}
	// configID
	configID = other.configID;
}

// --> Do NOT EDIT <--
/* copy assignment operator */
Stub_generic_status& Stub_generic_status::operator =(const Stub_generic_status& other)
{
	Stub_generic_status tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
Stub_generic_status& Stub_generic_status::operator =(Stub_generic_status&& other) noexcept
{
	// id
    std::swap(id, other.id);
	// timestamp
    std::swap(timestamp, other.timestamp);
	// moduleID
    std::swap(moduleID, other.moduleID);
	// moduleURI
    std::swap(moduleURI, other.moduleURI);
	// commandQueue
    std::swap(commandQueue, other.commandQueue);
	// status
    std::swap(status, other.status);
	// message
    std::swap(message, other.message);
	// progress
    std::swap(progress, other.progress);
	// startTime
    std::swap(startTime, other.startTime);
	// systemTimeProcessing
    std::swap(systemTimeProcessing, other.systemTimeProcessing);
	// estimatedFinishTime
    std::swap(estimatedFinishTime, other.estimatedFinishTime);
	// qualityOfService
    std::swap(qualityOfService, other.qualityOfService);
	// stableResults
    std::swap(stableResults, other.stableResults);
	// chain
    std::swap(chain, other.chain);
	// configID
    std::swap(configID, other.configID);

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
Stub_generic_status::Stub_generic_status()
{
	clear();
}

// --> Do NOT EDIT <--
Stub_generic_status::Stub_generic_status(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
Stub_generic_status::Stub_generic_status(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
Stub_generic_status::~Stub_generic_status()
{
}

// --> Do NOT EDIT <--
void Stub_generic_status::clear()
{
	this->id = "";
	this->timestamp = 0;
	this->moduleID = "";
	this->moduleURI.reset( new std::string("") );
	this->commandQueue.reset( new std::vector<boost::shared_ptr<std::string>> );
	this->status.reset( new std::string("n/a") );
	this->message.reset( new std::string("") );
	this->progress = static_cast<double>(0);
	this->startTime = -1;
	this->systemTimeProcessing = -1;
	this->estimatedFinishTime = -1;
	this->qualityOfService.reset( new Class_generic_status_qualityOfService );
	this->stableResults.reset( new std::vector<boost::shared_ptr<Class_generic_status_stableResults>> );
	this->chain.reset( new std::vector<boost::shared_ptr<std::string>> );
	this->configID = "";
}

// --> Do NOT EDIT <--
void Stub_generic_status::parseJson(const char *str)
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
void Stub_generic_status::parseJson(const rapidjson::Value& value)
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

	// commandQueue
	if ((value.HasMember("commandQueue")) && value["commandQueue"].IsArray())
	{
		const rapidjson::Value& n0 = value["commandQueue"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> a0( new std::vector<boost::shared_ptr<std::string>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<std::string>( new std::string( n0[i0].GetString() ) );
		}
		set_commandQueue( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'commandQueue'");

	// status
	if ((value.HasMember("status")) && value["status"].IsString())
	{
		set_status( boost::shared_ptr<std::string>( new std::string( value["status"].GetString() ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'status'");

	// message
	if ((value.HasMember("message")) && value["message"].IsString())
	{
		set_message( boost::shared_ptr<std::string>( new std::string( value["message"].GetString() ) ) );
	}
	// progress
	if ((value.HasMember("progress")) && value["progress"].IsNumber())
	{
		set_progress( value["progress"].GetDouble() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'progress'");

	// startTime
	if ((value.HasMember("startTime")) && value["startTime"].IsInt64())
	{
		set_startTime( value["startTime"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'startTime'");

	// systemTimeProcessing
	if ((value.HasMember("systemTimeProcessing")) && value["systemTimeProcessing"].IsInt64())
	{
		set_systemTimeProcessing( value["systemTimeProcessing"].GetInt64() );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'systemTimeProcessing'");

	// estimatedFinishTime
	if ((value.HasMember("estimatedFinishTime")) && value["estimatedFinishTime"].IsInt64())
	{
		set_estimatedFinishTime( value["estimatedFinishTime"].GetInt64() );
	}
	// qualityOfService
	if ((value.HasMember("qualityOfService")) && value["qualityOfService"].IsObject())
	{
		set_qualityOfService( boost::shared_ptr<Class_generic_status_qualityOfService>( new Class_generic_status_qualityOfService( value["qualityOfService"] ) ) );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'qualityOfService'");

	// stableResults
	if ((value.HasMember("stableResults")) && value["stableResults"].IsArray())
	{
		const rapidjson::Value& n0 = value["stableResults"];
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> a0( new std::vector<boost::shared_ptr<Class_generic_status_stableResults>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<Class_generic_status_stableResults>( new Class_generic_status_stableResults( n0[i0] ) );
		}
		set_stableResults( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'stableResults'");

	// chain
	if ((value.HasMember("chain")) && value["chain"].IsArray())
	{
		const rapidjson::Value& n0 = value["chain"];
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> a0( new std::vector<boost::shared_ptr<std::string>>(n0.Size()) );
		for (rapidjson::SizeType i0 = 0; i0 < n0.Size(); i0++)
		{
			a0->at(i0) = boost::shared_ptr<std::string>( new std::string( ConnectedVision::jsonToStr(n0[i0]) ) );
		}
		set_chain( a0 );
	}
	else
		throw ConnectedVision::runtime_error( "required member is missing: 'chain'");

}

// --> Do NOT EDIT <--
std::string Stub_generic_status::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string Stub_generic_status::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& Stub_generic_status::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
	{ // id
		node.AddMember("id", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_id() ), allocator), allocator);
	}
	{ // timestamp
		node.AddMember("timestamp", rapidjson::Value().SetInt64( get_timestamp() ), allocator);
	}
	{ // moduleID
		node.AddMember("moduleID", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_moduleID() ), allocator), allocator);
	}
	{ // moduleURI
		node.AddMember("moduleURI", rapidjson::Value().SetString( get_moduleURI()->c_str(), allocator), allocator);
	}
	{ // commandQueue
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a0 = get_commandQueue(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add string
			n0.PushBack(rapidjson::Value().SetString( a0->at(i0)->c_str(), allocator), allocator);
		}
		node.AddMember("commandQueue", n0, allocator);
	}
	{ // status
		node.AddMember("status", rapidjson::Value().SetString( get_status()->c_str(), allocator), allocator);
	}
	{ // message
		node.AddMember("message", rapidjson::Value().SetString( get_message()->c_str(), allocator), allocator);
	}
	{ // progress
		node.AddMember("progress", rapidjson::Value().SetDouble( get_progress() ), allocator);
	}
	{ // startTime
		node.AddMember("startTime", rapidjson::Value().SetInt64( get_startTime() ), allocator);
	}
	{ // systemTimeProcessing
		node.AddMember("systemTimeProcessing", rapidjson::Value().SetInt64( get_systemTimeProcessing() ), allocator);
	}
	{ // estimatedFinishTime
		node.AddMember("estimatedFinishTime", rapidjson::Value().SetInt64( get_estimatedFinishTime() ), allocator);
	}
	{ // qualityOfService
		node.AddMember("qualityOfService", get_qualityOfService()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
	}
	{ // stableResults
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>>&& a0 = get_stableResults(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final dimension of array, add actual value
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				n0.PushBack(a0->at(i0)->toJson( rapidjson::Value().SetObject(), allocator), allocator);
			}
		}
		node.AddMember("stableResults", n0, allocator);
	}
	{ // chain
		rapidjson::Value n0; n0.SetArray();
		boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a0 = get_chain(); // rvalue reference for const functions
		for (size_t i0 = 0; i0 < a0->size(); i0++)
		{
			// process array level 0
			// final level of array, add raw data
			if ( a0->at(i0) )	// ensure that we have no NULL pointer
			{
				rapidjson::Document doc(&allocator);
				doc.Parse<0>( a0->at(i0)->c_str() );
				n0.PushBack(static_cast<rapidjson::Value&>(doc), allocator);
			}
		}
		node.AddMember("chain", n0, allocator);
	}
	return node;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_status::get_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_status::getconst_id() const
{
	return( this->id );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_id(ConnectedVision::id_t value)
{
	this->id = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status::get_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status::getconst_timestamp() const
{
	return( this->timestamp );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_timestamp(ConnectedVision::timestamp_t value)
{
	this->timestamp = value;
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_status::get_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_status::getconst_moduleID() const
{
	return( this->moduleID );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_moduleID(ConnectedVision::id_t value)
{
	this->moduleID = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_status::get_moduleURI() const
{
	return( this->moduleURI );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_status::getconst_moduleURI() const
{
	return( boost::static_pointer_cast<const std::string>(this->moduleURI) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_moduleURI(boost::shared_ptr<std::string> value)
{
	this->moduleURI = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> Stub_generic_status::get_commandQueue() const
{
	return( this->commandQueue );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> Stub_generic_status::getconst_commandQueue() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::string>>>(this->commandQueue) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_commandQueue(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value)
{
	this->commandQueue = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_status::get_commandQueue(int index) const
{
	return( this->commandQueue->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::string>& Stub_generic_status::getconst_commandQueue(int index) const
{
	return( this->commandQueue->at(index) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::add_commandQueue(boost::shared_ptr<std::string> value)
{
	this->commandQueue->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_status::get_status() const
{
	return( this->status );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_status::getconst_status() const
{
	return( boost::static_pointer_cast<const std::string>(this->status) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_status(boost::shared_ptr<std::string> value)
{
	this->status = value;
}

// --> Do NOT EDIT <--
bool Stub_generic_status::is_status(const boost::shared_ptr<std::string> &value) const
{
	return ( (*this->status) == (*value) );
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_status::get_message() const
{
	return( this->message );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::string> Stub_generic_status::getconst_message() const
{
	return( boost::static_pointer_cast<const std::string>(this->message) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_message(boost::shared_ptr<std::string> value)
{
	this->message = value;
}

// --> Do NOT EDIT <--
double Stub_generic_status::get_progress() const
{
	return( this->progress );
}

// --> Do NOT EDIT <--
const double Stub_generic_status::getconst_progress() const
{
	return( this->progress );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_progress(double value)
{
	this->progress = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status::get_startTime() const
{
	return( this->startTime );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status::getconst_startTime() const
{
	return( this->startTime );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_startTime(ConnectedVision::timestamp_t value)
{
	this->startTime = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status::get_systemTimeProcessing() const
{
	return( this->systemTimeProcessing );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status::getconst_systemTimeProcessing() const
{
	return( this->systemTimeProcessing );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_systemTimeProcessing(ConnectedVision::timestamp_t value)
{
	this->systemTimeProcessing = value;
}

// --> Do NOT EDIT <--
ConnectedVision::timestamp_t Stub_generic_status::get_estimatedFinishTime() const
{
	return( this->estimatedFinishTime );
}

// --> Do NOT EDIT <--
const ConnectedVision::timestamp_t Stub_generic_status::getconst_estimatedFinishTime() const
{
	return( this->estimatedFinishTime );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_estimatedFinishTime(ConnectedVision::timestamp_t value)
{
	this->estimatedFinishTime = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_status_qualityOfService> Stub_generic_status::get_qualityOfService() const
{
	return( this->qualityOfService );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const Class_generic_status_qualityOfService> Stub_generic_status::getconst_qualityOfService() const
{
	return( boost::static_pointer_cast<const Class_generic_status_qualityOfService>(this->qualityOfService) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_qualityOfService(boost::shared_ptr<Class_generic_status_qualityOfService> value)
{
	this->qualityOfService = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> Stub_generic_status::get_stableResults() const
{
	return( this->stableResults );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> Stub_generic_status::getconst_stableResults() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<Class_generic_status_stableResults>>>(this->stableResults) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_stableResults(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> value)
{
	this->stableResults = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<Class_generic_status_stableResults> Stub_generic_status::get_stableResults(int index) const
{
	return( this->stableResults->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<Class_generic_status_stableResults>& Stub_generic_status::getconst_stableResults(int index) const
{
	return( this->stableResults->at(index) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::add_stableResults(boost::shared_ptr<Class_generic_status_stableResults> value)
{
	this->stableResults->push_back(value);
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> Stub_generic_status::get_chain() const
{
	return( this->chain );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> Stub_generic_status::getconst_chain() const
{
	return( boost::static_pointer_cast<const std::vector<boost::shared_ptr<std::string>>>(this->chain) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_chain(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value)
{
	this->chain = value;
}

// --> Do NOT EDIT <--
boost::shared_ptr<std::string> Stub_generic_status::get_chain(int index) const
{
	return( this->chain->at(index) );
}

// --> Do NOT EDIT <--
const boost::shared_ptr<std::string>& Stub_generic_status::getconst_chain(int index) const
{
	return( this->chain->at(index) );
}

// --> Do NOT EDIT <--
void Stub_generic_status::add_chain(boost::shared_ptr<std::string> value)
{
	this->chain->push_back(value);
}

// --> Do NOT EDIT <--
ConnectedVision::id_t Stub_generic_status::get_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
const ConnectedVision::id_t Stub_generic_status::getconst_configID() const
{
	return( this->configID );
}

// --> Do NOT EDIT <--
void Stub_generic_status::set_configID(ConnectedVision::id_t value)
{
	this->configID = value;
}


} // namespace ConnectedVision