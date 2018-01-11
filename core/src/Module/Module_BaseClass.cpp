/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/regex.hpp>

#include "helper.h"

#include <IDataClassJSON.h>
#include "ConnectedVisionInputPin.h"

#include "Module_BaseClass.h"
#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_moduleStatus.h"

#include <opencv2/core/core.hpp> // needed for module logo
#include <opencv2/highgui/highgui.hpp> // needed for module logo

using namespace std;
using namespace ConnectedVision;
using namespace ConnectedVision::HTTP;
using namespace ConnectedVision::Module;

#define LOG_CONFIG( level, msg, configID )	{ this->log()->write( (level), this->logName, std::string(__FUNCTION__) + std::string("()@") + ConnectedVision::intToStr(__LINE__), (msg), (configID) ); }
#define LOG_DEBUG_CONFIG( msg, configID )	LOG_CONFIG( Logging::Debug, msg, configID )
#define LOG_INFO_CONFIG( msg, configID )	LOG_CONFIG( Logging::Info, msg, configID )
#define LOG_WARN_CONFIG( msg, configID )	LOG_CONFIG( Logging::Warning, msg, configID )
#define LOG_ERROR_CONFIG( msg, configID )	LOG_CONFIG( Logging::Error, msg, configID )
#define LOG_FATAL_CONFIG( msg, configID )	LOG_CONFIG( Logging::Fatal, msg, configID )
#define LOG_SCOPE_CONFIG( configID )		Logging::LoggingScope _log_scope( this->log(), Logging::Debug, this->logName, std::string(__FUNCTION__) + std::string("()@") + ConnectedVision::intToStr(__LINE__), ( configID ) );

/**
 * module constructor
 */
Module_BaseClass::Module_BaseClass(const char moduleDescription[], const char inputPinDescription[], const char outputPinDescription[]) :
	ready(false), env(NULL), workerTimeout(5000)
{
	initModuleDescription( moduleDescription, NULL, NULL, "" );
	initInputPinDescription( inputPinDescription );
	initOutputPinDescription( outputPinDescription );

	this->logName = this->moduleID;

	this->statusStore.reset();
	this->configStore.reset();

	this->defaultParameters.SetNull();
}

/**
 * module constructor
 */
Module_BaseClass::~Module_BaseClass()
{
	// LOG is not valid in destructor

	this->releaseModule();
}

/**
 * connect to SQLite
 *
 *	if the DB does not exits, it's created on-the-fly
 */
void Module_BaseClass::connectDB() 
{
	LOG_SCOPE;

	std::string path( this->env->getDataPath()+"/"+this->getModuleID()+"/" );
	std::string dbFile( path + "/" + this->getModuleID()+".db" );

	if ( !boost::filesystem::is_directory( path ) )
	{
		// create directory
		boost::filesystem::create_directories( path );
	}

	int createFlag = 0;
	if( !boost::filesystem::exists( dbFile ) )
		createFlag = SQLITE_OPEN_CREATE;

	// open DB
	this->dbConn.init( dbFile, createFlag );
}

/**
 * init module
 *
 * @param server  module server
 */
void Module_BaseClass::initModule( IModuleEnvironment *env ) 
{ 
	LOG_SCOPE;
	
	try
	{
		Module_BaseClass::releaseModule();
		this->env = env;

		// update module URI
		this->moduleURI = env->getModuleURL("", this->getModuleID() );
		initModuleDescription( this->moduleDescription.c_str(), NULL, NULL, this->moduleURI.c_str() );

		// connect to DB
		connectDB();


		// connect to status and config store
		this->statusStore = ConnectedVision::make_shared<ConnectedVision::DataHandling::Store_SQLite_generic_status>( ID_NULL, this->dbConn );
		this->configStore = ConnectedVision::make_shared<ConnectedVision::DataHandling::Store_SQLite_generic_config>( ID_NULL, this->dbConn );

		// connect to custom stores
		prepareStores();

		// create input pin pool
		this->inputPinsPool.clear();
		for (std::vector<pinID_t>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
		{
			this->inputPinsPool.insert( std::pair< pinID_t, boost::shared_ptr<InputPinPool_t> >(*it, boost::shared_ptr<InputPinPool_t>( new InputPinPool_t() )) );
		}

		// create output pin pool		
		this->outputPinsPool.clear();
		const std::vector<pinID_t>& outputPinIDs = getOutputPinIDs();
		for (std::vector<pinID_t>::const_iterator it = outputPinIDs.begin(); it != outputPinIDs.end(); ++it)
		{
			this->outputPinsPool.insert( std::pair< pinID_t, boost::shared_ptr<OutputPinPool_t> >(*it, boost::shared_ptr<OutputPinPool_t>( new OutputPinPool_t() )) );
		}

		// build rapidjson object with default parameters
		if (defaultParameters.IsNull()) // lazy creation
		{
			rapidjson::Value currentDescriptionParameterValue(moduleDescriptionJSON, moduleDescriptionJSON.GetAllocator());

			// navigate to params sub-object
			if (moduleDescriptionJSON.HasMember("params"))
			{
				currentDescriptionParameterValue = currentDescriptionParameterValue["params"];
			}
			else
			{
				throw ConnectedVision::runtime_error(std::string("parse error of module description (no object called \"params\" found)! "));
			}
			
			if (currentDescriptionParameterValue.HasMember("type"))
			{
				if (std::string(currentDescriptionParameterValue["type"].GetString()) == "object")
				{
					// navigate to params/properties sub-object
					if (currentDescriptionParameterValue.HasMember("properties"))
					{
						currentDescriptionParameterValue = currentDescriptionParameterValue["properties"];
					}
					else
					{
						throw ConnectedVision::runtime_error(std::string("parse error of module description (no object called \"params/properties\" found)! "));
					}

					defaultParameters.SetObject();
				}
				else
				{
					throw ConnectedVision::runtime_error(std::string("error: params in module description must be of type \"object\"! "));
				}
			}
			this->getDefaultParametersRecursiveAsRapidjson(currentDescriptionParameterValue, defaultParameters, moduleDescriptionJSON.GetAllocator());
		}

		// abort zombi configurations
		vector<id_t> list = this->configStore->getIDList();
		for (auto it = list.begin(); it != list.end(); ++it) 
		{
			auto constStatus = this->statusStore->getByID( *it );
			if ( constStatus && constStatus->is_status_running() )
			{
				// clone status to make it writeable
				ConnectedVision::shared_ptr<Class_generic_status> status = constStatus->copy();
				status->set_status_error();
				status->set_message("module was aborted during computation");
				this->statusStore->save_move(status);
			}
		}


		LOG_INFO("module: " + this->getModuleName() + " ready");
		this->ready = true;
	}
	catch(std::runtime_error& e)
	{
		LOG_ERROR( e.what() );
	}

	
}

/**
 * destroy module
 *
 * @param server  module server
 */
void Module_BaseClass::releaseModule() 
{
	// stop module
	if ( !this->ready )
		return;
	this->ready = false;

	// make sure not to log if module has already been released
	LOG_SCOPE;

	// clear worker controller map
	this->mapWorkerControllers.clear();

	// destroy input pins
	this->inputPinsPool.clear();

	// destroy output pins
	this->outputPinsPool.clear();

	this->statusStore.reset();
	this->configStore.reset();

	this->dbConn.free();
	this->env = NULL;

	LOG_INFO("module released");

	
}

/**
 * get input pins
 *
 * @param configID	config
 *
 * @return input pins
 */
boost::shared_ptr< IConnectedVisionInputPin > Module_BaseClass::getInputPin(const id_t configID, const std::string pinID)
{
	LOG_SCOPE_CONFIG( configID );

	//id_t resolvedConfigID = resolvePotentialAliasID(configID);

	boost::shared_ptr<const Class_generic_config > config( this->configStore->getByID(configID) );
	if ( !config )
	{
		return boost::shared_ptr< IConnectedVisionInputPin >();
	}

	
	return getInputPin(*config, pinID);
}

/**
 * get input pins
 * If the pinID is an indexed pin ID, i.e. it consists of non-numeric characters followed by a period character and a number and the index parameter does not equal -1 then index parameter is used instead of the index encoded in the pinID.
 * If the pinID is a typed pin ID, i.e. it only consits of non-numeric characters and the the index parameter equals -1 then the value 0 is used as index.
 *
 * @param config	config
 * @param pinID		pin ID 
 * @param index		pin index
 *
 * @return input pins
 */
boost::shared_ptr< IConnectedVisionInputPin > Module_BaseClass::getInputPin(const Class_generic_config &config, const pinID_t pinID, int index)
{
	id_t configID = config.get_id();
	LOG_SCOPE_CONFIG( configID );

	if ( !this->ready )
		throw ConnectedVision::runtime_error("module not ready");

	//id_t resolvedConfigID = resolvePotentialAliasID(configID);

	// if pinID has .x && index != -1 -> use index variable instead of index form pinID
	// if pinID has .x && index == -1 -> index = x
	// if pinID !has .x && index == -1 -> index = 0
	pinID_t pinIdTyped = getTypedPinID(pinID);

	if(index == -1)
	{
		index = getIndex(pinID);
	}
	
	pinID_t pinIdIndexed = getIndexedPinID(pinIdTyped, index);

	boost::shared_ptr< IConnectedVisionInputPin > inPin;
	try
	{
		if(this->inputPinsPool.find(pinIdTyped) == this->inputPinsPool.end())
		{
			throw ConnectedVision::runtime_error("Cannot find input pin for pin ID " + pinIdTyped + ". Check if the pin is declared in the JSON input description, if the corresponding autogenerated source code files exist and if the pin gets initialized in the " + this->moduleID + "Module::generateInputPin() method.");
		}

		boost::shared_ptr< InputPinPool_t > inputPinPool = this->inputPinsPool[pinIdTyped];

		if ( !inputPinPool )
		{
			throw ConnectedVision::runtime_error("Input pin for pin ID " + pinIdTyped + " is null. Check if the pin is declared in the JSON input description, if the corresponding autogenerated source code files exist and if the pin gets initialized in the " + this->moduleID + "Module::generateInputPin() method.");
		}

		// request configured input pins vector from pool
		if ( configID != ID_NULL )
		{
			inPin = inputPinPool->request(configID + intToStr(index)); // unique lookup key for pool: resolvedConfigID + index
			if ( inPin )
			{
				// sanity check
				if ( !inPin->getID().empty() )
				{
					LOG_INFO_CONFIG("pre-configured pin found", configID);
					return inPin;
				}
			}
		}

		if ( !inPin )
		{
			// request anonymous input pins vector from pool
			inPin = inputPinPool->request();
		}

		if ( !inPin )
		{
			// allocate new input pin
			inPin = this->generateInputPin(pinIdTyped);
			inputPinPool->add( inPin, ID_NULL );
		}

		if ( inPin )
		{
			// init input pins
			LOG_INFO_CONFIG("configured pin with configChain[" + pinIdIndexed + "]", configID);
			boost::shared_ptr<Class_generic_config_chain> conn = config.getSubConfigConnectionByInputPin( pinIdIndexed );

			if(!conn)
			{
				throw ConnectedVision::runtime_error("failed to get sub-config chain for pin ID \"" + pinIdIndexed + "\"");
			}

			inPin->init(configID, conn, pinIdIndexed);
			inputPinPool->remap( inPin, configID + intToStr(index));
		}
	}
	catch (const std::exception& e) 
	{
		(void) e;	// avoid compiler warning
		LOG_ERROR_CONFIG("input pin not found", configID);
		inPin.reset();
		throw;	// rethrow exception
	}
	
	if ( !inPin )
	{
		throw ConnectedVision::runtime_error("cannot allocate input pin: " + pinIdIndexed + " for config ID: " + configID);
	}

	return inPin;
}


/**
 * get output pins
 *
 * @param configID	config
 *
 * @return output pins
 */
boost::shared_ptr< IConnectedVisionOutputPin > Module_BaseClass::getOutputPin(const id_t configID, const pinID_t pinID)
{
	LOG_SCOPE_CONFIG( configID );

	if ( !this->ready )
		throw ConnectedVision::runtime_error("module not ready");

	if (!this->configStore)
	{
		throw ConnectedVision::runtime_error("module not ready (configStore)");
	}

	id_t resolvedConfigID = resolvePotentialAliasID(configID);

	boost::shared_ptr<const Class_generic_config > config( this->configStore->getByID(resolvedConfigID) );
	if ( !config )
	{
		
		return boost::shared_ptr< IConnectedVisionOutputPin >();
	}
	
	return getOutputPin(*config, pinID);
}

/**
 * get output pins
 *
 * @param config	config
 *
 * @return output pins
 */
boost::shared_ptr< IConnectedVisionOutputPin > Module_BaseClass::getOutputPin(const Class_generic_config &config, const std::string pinID)
{
	id_t configID = config.get_id();
	LOG_SCOPE_CONFIG( configID );

	if ( !this->ready )
		throw ConnectedVision::runtime_error("module not ready");
	
	id_t resolvedConfigID = resolvePotentialAliasID(configID);

	boost::shared_ptr< IConnectedVisionOutputPin > outPin;

	try
	{
		if(this->outputPinsPool.find(pinID) == this->outputPinsPool.end())
		{
			throw ConnectedVision::runtime_error("Cannot find output pin for pin ID \"" + pinID + "\". Check if the pin is declared in the JSON output description, if the corresponding autogenerated source code files exist and if the pin gets initialized in the " + this->moduleID + "Module::generateOutputPin() method.");
		}

		boost::shared_ptr< OutputPinPool_t > outputPinPool = this->outputPinsPool[ pinID ];

		if ( !outputPinPool )
		{
			throw ConnectedVision::runtime_error("Cannot find output pin for pin ID \"" + pinID + "\". Check if the pin is declared in the JSON output description, if the corresponding autogenerated source code files exist and if the pin gets initialized in the " + this->moduleID + "Module::generateOutputPin() method.");
		}

		// request configured output pins vector from pool
		outPin = outputPinPool->request( resolvedConfigID );
		if ( outPin )
		{
			// sanity check
			// if ( !outPin->getID().empty() ) TODO -> add getID() to IConnectedVisionOutputPin
			{
				LOG_INFO_CONFIG("pre-configured pin found", resolvedConfigID);
				return outPin;
			}
		}

		if ( !outPin )
		{
			// request anonymous output pins vector from pool
			outPin = outputPinPool->request();
		}

		if ( !outPin )
		{
			// allocate new output pin
			outPin = this->generateOutputPin(pinID);
			outputPinPool->add( outPin, ID_NULL );
		}

		if ( outPin )
		{
			// init output pins
			LOG_INFO_CONFIG("configured pin with configChain[" + pinID + "]", resolvedConfigID);
			outPin->init( config.toJson() );
			outputPinPool->remap( outPin, resolvedConfigID );
		}
	}
	catch (const std::exception& e)
	{
		(void) e;	// avoid compiler warning
		LOG_ERROR_CONFIG("output pin not found", resolvedConfigID);
		outPin.reset();
		throw;	// rethrow exception
	}
	
	if ( !outPin )
	{
		throw ConnectedVision::runtime_error("cannot allocate output pin: " + pinID + " for config ID: " + resolvedConfigID);
	}

	return outPin;
}

/**
 * parse module description and init private member
 *
 * @param[in]  moduleDescription			description
 *
 */
void Module_BaseClass::initModuleDescription(const char moduleDescription[], const char moduleName[], const char moduleID[], const char moduleURI[])
{
	if (this->moduleDescriptionJSON.Parse<0>( moduleDescription ).HasParseError())
	{
		throw ConnectedVision::runtime_error( string("ERROR: JSON parse error: ") + rapidjson::GetParseError_En(this->moduleDescriptionJSON.GetParseError()) + " @ " + intToStr(this->moduleDescriptionJSON.GetErrorOffset()) );
	}

	// handle module name
	if ( moduleName )
	{
		// set module name
		this->moduleDescriptionJSON["name"].SetString(moduleID, this->moduleDescriptionJSON.GetAllocator());
	}
	else
	{
		// read module name
		this->moduleName = "";
		if ( this->moduleDescriptionJSON["name"].IsString() )
			this->moduleName = this->moduleDescriptionJSON["name"].GetString();
		if ( this->moduleName.empty() )
			throw ConnectedVision::runtime_error("name not found in moduleDescription");
	}

	// handle module ID
	if ( moduleID )
	{
		// set module ID
		this->moduleDescriptionJSON["moduleID"].SetString(moduleID, this->moduleDescriptionJSON.GetAllocator());
	}
	else
	{
		// read module ID
		this->moduleID = "";
		if ( this->moduleDescriptionJSON["moduleID"].IsString() )
			this->moduleID = this->moduleDescriptionJSON["moduleID"].GetString();
		if ( this->moduleID.empty() )
			throw ConnectedVision::runtime_error("moduleID not defined in moduleDescription");
	}

	// handle module URI
	if ( moduleID )
	{
		// set module URI
		this->moduleDescriptionJSON["moduleURI"].SetString(moduleURI, this->moduleDescriptionJSON.GetAllocator());
	}

	//////////////// [block start] ensure sanity of params inside module description and add missing "dynamic" field for parameters ////////////////
	// sanity is violated if a non-dynamic fields inside a dynamic object/array
	rapidjson::Value currentDescriptionParameterValue(this->moduleDescriptionJSON, this->moduleDescriptionJSON.GetAllocator());

	if (!this->moduleDescriptionJSON.HasMember("params"))
	{
		throw ConnectedVision::runtime_error(std::string("error: module description has invalid format (member \"params\" was not found)! "));
	}

	if (this->moduleDescriptionJSON["params"].HasMember("properties"))
	{
		// navigate to params sub-object
		currentDescriptionParameterValue = this->moduleDescriptionJSON["params"]["properties"];
	
		// do the sanity test recursively
		// ensure in case of object "params" being declared as "dynamic" as whole that all sub-elements are dynamic
		if ( (this->moduleDescriptionJSON["params"].HasMember("dynamic")) && (this->moduleDescriptionJSON["params"]["dynamic"].GetBool()) )
		{
			testDynamicParameterSanityAndUpdate(currentDescriptionParameterValue, true);
		}
		else // otherwise the individual elements can have field "dynamic" set to false
		{
			testDynamicParameterSanityAndUpdate(currentDescriptionParameterValue, false);
		}

		this->moduleDescriptionJSON["params"]["properties"] = currentDescriptionParameterValue; // don't forget to move changes into moduleDescriptionJSON since we only worked on a copy
		//////////////// [block end] ensure sanity of params inside module description and add missing "dynamic" field for parameters ////////////////

		// build parameter description object to allow easier and more convenient processing later on
		this->parameterDesc = boost::make_shared<std::map<std::string, ParameterDescTreeNode>>();
		buildParameterDescriptionRecursive(moduleDescriptionJSON["params"]["properties"], this->parameterDesc);
	}

	// convert module description to string (pretty formatted)
	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	this->moduleDescriptionJSON.Accept(writer);

	this->moduleDescription = s.GetString();
}

/**
* get the number of instances of the specified pin for the specified config
*
* @param pinID typed pin ID (without index value)
* @param config	configuration chain
*
* @return number of instances of the specified pin for the specified config
*/
int Module_BaseClass::getInputPinCount(const Class_generic_config& config, const pinID_t pinID)
{
	const auto chain = config.getconst_chain();

	int indexMax = -1;
	int indexCount = 0;
	const pinID_t pinIdTyped = getTypedPinID(pinID);
	
	for(std::vector<boost::shared_ptr<Class_generic_config_chain>>::const_iterator iChain = chain->begin(); iChain != chain->end(); iChain++)
	{
		const auto& connections = (*iChain)->getconst_connections();
		for(auto itConnection = connections->begin(); itConnection != connections->end(); itConnection++)
		{
			const boost::shared_ptr<Class_generic_config_chain_connections>& conn = *itConnection;
			const pinID_t connectionPinID = *conn->get_inputPinID();

			const pinID_t connectionPinIDTyped = getTypedPinID(connectionPinID);

			if(pinIdTyped == connectionPinIDTyped)
			{
				indexMax = max(indexMax, getIndex(connectionPinID));
				indexCount++;
			}
		}
	}

	if((indexMax + 1) != indexCount)
	{
		throw ConnectedVision::runtime_error("the input pins of type \"" + pinIdTyped + "\" have no continuous index sequence (.0, .1, .2, ...)");
	}

	return indexCount;
}



int Module_BaseClass::getInputPinCount(const boost::shared_ptr<const Class_generic_config> config, const pinID_t pinID)
{
	if(!config)
	{
		throw ConnectedVision::runtime_error("the specified config parameter is null");
	}

	return this->getInputPinCount(*config, pinID);
}



/**
 * parse inputPin description and init private member
 *
 * @param[in]  moduleDescription			description
 *
 */
void Module_BaseClass::initInputPinDescription(const char inputPinDescription[])
{
	rapidjson::Document inputPinDescriptionJSON;
	if (inputPinDescriptionJSON.Parse<0>( inputPinDescription ).HasParseError())
	{
		throw ConnectedVision::runtime_error( string("ERROR: JSON parse error: ") + rapidjson::GetParseError_En(inputPinDescriptionJSON.GetParseError()) + " @ " + intToStr(inputPinDescriptionJSON.GetErrorOffset()) );
	}

	if ( !inputPinDescriptionJSON.IsArray() )
	{
		throw ConnectedVision::runtime_error( "input pin description is malformed (not an array)" );
	}

	this->inputPinDescriptions.clear();
	this->inputPinIDs.clear();
	for (rapidjson::SizeType i = 0; i < inputPinDescriptionJSON.Size(); i++)
	{
		auto pinDescription = boost::make_shared<Class_PinDescription>(inputPinDescriptionJSON[i]);
		this->checkInputPinDescription(pinDescription);
		this->inputPinDescriptions.push_back( pinDescription );
		id_t pinID( *pinDescription->get_id() );
		this->inputPinIDs.push_back(pinID);
	}

	this->inputPinDescription = inputPinDescription;
}

/**
 * parse outputPin description and init private member
 *
 * @param[in]  moduleDescription			description
 *
 */
void Module_BaseClass::initOutputPinDescription(const char outputPinDescription[])
{
	rapidjson::Document outputPinDescriptionJSON;
	if (outputPinDescriptionJSON.Parse<0>( outputPinDescription ).HasParseError())
	{
		throw ConnectedVision::runtime_error( string("ERROR: JSON parse error: ") + rapidjson::GetParseError_En(outputPinDescriptionJSON.GetParseError()) + " @ " + intToStr(outputPinDescriptionJSON.GetErrorOffset()) );
	}

	if ( !outputPinDescriptionJSON.IsArray() )
	{
		throw ConnectedVision::runtime_error( "output pin description is malformed (not an array)" );
	}

	this->outputPinDescriptions.clear();
	this->outputPinIDs.clear();
	for (rapidjson::SizeType i = 0; i < outputPinDescriptionJSON.Size(); i++)
	{
		auto pinDescription = boost::make_shared<Class_PinDescription>(outputPinDescriptionJSON[i]);
		this->outputPinDescriptions.push_back( pinDescription );
		id_t pinID( *pinDescription->get_id() );
		this->outputPinIDs.push_back(pinID);
	}

	this->outputPinDescription = outputPinDescription;
}


/**
 * get module description
 *
 * @param[out] response		module description
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getModuleDescription(ConnectedVisionResponse &response)
{
	LOG_SCOPE

	response.setContentType("application/json");
	response.setContent( this->moduleDescription );

	return HTTP_Status_OK;
}

/**
 * get input pin descriptions
 *
 * @param[out] response		input pin descriptions
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getInputDescription(ConnectedVisionResponse &response)
{
	LOG_SCOPE

	response.setContentType("application/json");
	response.setContent( this->inputPinDescription );

	return HTTP_Status_OK;
}

/**
 * get output pin descriptions
 *
 * @param[out] response		input pin descriptions
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getOutputDescription(ConnectedVisionResponse &response)
{
	LOG_SCOPE

	response.setContentType("application/json");
	response.setContent( this->outputPinDescription );

	return HTTP_Status_OK;
}

/**
 * config list
 *
 * @param[out] response		list of stored configuration IDs / jobs
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getConfigList(ConnectedVisionResponse &response)
{
	LOG_SCOPE

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	try 
	{
		string data = "[\n";
		vector<id_t> list = configStore->getIDList();
		for (auto it = list.begin(); it!=list.end(); ++it)
		{
			if ( it != list.begin() )
				data += ",\n";
			data += "\"" + *it + "\"";
		}
		data += "\n]";
		response.setContentType("application/json");
		response.setContent( data );

		return HTTP_Status_OK;
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

/**
 * get detailed config list (id, name and aliasIDs)
 *
 * @param[out] response		list of stored configuration IDs / jobs
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getConfigListDetailed(ConnectedVisionResponse &response)
{
	LOG_SCOPE

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	try 
	{
		string data = "[\n";
		vector<id_t> list = configStore->getIDList();
		for (auto it = list.begin(); it!=list.end(); ++it)
		{
			boost::shared_ptr<const Class_generic_config> config(configStore->getByID(*it));
			if (!config) // if a configID from the list of IDs cannot be read, the list got corrupted somehow
			{
				throw std::runtime_error("data consistancy error (one element of the list of config IDs could not be read from store)");
			}

			if ( it != list.begin() )
				data += ",\n";
			data += "\t{\n\t\t\"id\": \"" + *it + "\",\n\t\t\"name\": \"" + *config->getconst_name() + "\",\n\t\t\"aliasIDs\": [";

			auto listAliasIDs = config->getconst_aliasID();
			for (auto itAliasID = listAliasIDs->begin(); itAliasID!=listAliasIDs->end(); ++itAliasID)
			{
				if ( itAliasID != listAliasIDs->begin() )
					data += ",";
				data += "\n\t\t\t{\n\t\t\t\t\"id\": \"" + *(*itAliasID)->getconst_id() + "\",\n\t\t\t\t\"timestamp\": \"" + boost::lexical_cast<string>((*itAliasID)->getconst_timestamp()) + "\"\n\t\t\t}";
			}
			if (listAliasIDs->size())
			{
				data += "\n\t\t";
			}
			data += "],\n";
			data += "\t\t\"commandList\": {\n";
			data += "\t\t\t\"config\":\t\"" + *config->getconst_moduleURI() + "/" + *it + "/config" + "\",\n";
			data += "\t\t\t\"status\":\t\"" + *config->getconst_moduleURI() + "/" + *it + "/status" + "\",\n";
			data += "\t\t\t\"reset\":\t\"" + *config->getconst_moduleURI() + "/" + *it + "/control/reset" + "\",\n";
			data += "\t\t\t\"resetThis\":\t\"" + *config->getconst_moduleURI() + "/" + *it + "/control/resetThis" + "\",\n";
			data += "\t\t\t\"start\":\t\"" + *config->getconst_moduleURI() + "/" + *it + "/control/start" + "\",\n";
			data += "\t\t\t\"stop\":\t\t\"" + *config->getconst_moduleURI() + "/" + *it + "/control/stop" + "\",\n";
			data += "\t\t\t\"stopThis\":\t\"" + *config->getconst_moduleURI() + "/" + *it + "/control/stopThis" + "\"\n";
			data += "\t\t}\n";
			data += "\t}\n";
		}
		data += "]";
		response.setContentType("application/json");
		response.setContent( data );

		return HTTP_Status_OK;
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

/**
 * module general status
 *
 * @param[out] response		module status
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getModuleStatus(ConnectedVisionResponse &response)
{
	LOG_SCOPE

	try 
	{
		// get object from Store
		Class_generic_moduleStatus moduelStatus;
		
		moduelStatus.set_name( this->getModuleName() );
		moduelStatus.set_moduleID( this->getModuleID() );

		// is module initialized?
		if ( this->ready )
		{
			moduelStatus.set_moduleStatus_up();

			// determine running configs / workers
			auto listRunningConfigs = this->mapWorkerControllers.filter( [](const ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &item) -> id_t
				{
					if ( item->activeWorker() )
						return item->getConfigID();
					else
						return ID_NULL;
				}, ID_NULL);


			// determine waiting configs / workers
			// TODO remove waiting workers list from module status

			// determine finished configs / workers
			// TODO add finished workers list to module status

		}
		else
		{
			moduelStatus.set_moduleStatus_down();
		}

		// return JSON string
		response.setContentType("application/json");
		response.setContent( moduelStatus.toJsonStr() );

		return HTTP_Status_OK;
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

/**
 * get configuration / job chain
 *
 * @param[in] configID		ID of configuration / job
 * @param[out] response		config
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getConfig(const id_t configID, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	try 
	{
		// get object from Store
		boost::shared_ptr<const Class_generic_config> config = configStore->getByID(resolvedConfigID);
		if ( config )
		{
			// return JSON string
			response.setContentType("application/json");
			response.setContent( config->toJsonStr() );

			return HTTP_Status_OK;
		}
		else
		{
			// not found
			return writeErrorLog(response, HTTP_Status_NOT_FOUND, "getConfig: config not found");
		}
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

void Module_BaseClass::setLogoPNG(const BufferLogoPNG &logoPNG)
{
	cv::_InputArray input(logoPNG.pBufferLogoAsPNG, logoPNG.sizeBufferLogoAsPNG);
	this->logo = boost::make_shared<cv::Mat>(cv::imdecode(input, cv::IMREAD_COLOR));
}

bool Module_BaseClass::isSetLogo()
{
	return(this->logo != nullptr); // returns true if shared pointer is set, otherwise false
}

int Module_BaseClass::getModuleLogo(ConnectedVisionResponse &response)
{
	if (this->logo)
	{
		vector<uchar> v_char;
		cv::imencode(".png", *this->logo, v_char);
	
		cv::Mat encoded(v_char);
		std::string content (reinterpret_cast<char*>(encoded.data), v_char.size());

		response.setContentType("image/png");
		response.setContent(content);
		return ConnectedVision::HTTP::HTTP_Status_OK;
	}
	else
	{
		ConnectedVision::HTTP::EnumHTTPStatus status = ConnectedVision::HTTP::HTTP_Status_NOT_FOUND;
		writeError(response, status, id_t("Module_BaseClass::getModuleLogo"), string("module logo was not set"));		
		return status;
	}
}

/**
 * get configuration summary as HTML code
 *
 * @param[in] configID		ID of configuration / job
 * @param[out] response		config
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getConfigHTMLsummary(const id_t configID, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	try 
	{
		// get object from Store
		boost::shared_ptr<const Class_generic_config> config = configStore->getByID(resolvedConfigID);
		if ( config )
		{
			// return JSON string
			response.setContentType("text/html");
			response.setContent( this->getConfigHTMLsummary(*this, *config) );

			return HTTP_Status_OK;
		}
		else
		{
			// not found
			return writeErrorLog(response, HTTP_Status_NOT_FOUND, "getConfig: config not found");
		}
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

std::string Module_BaseClass::getConfigHTMLsummary(Module_BaseClass &module, const Class_generic_config &config)
{
	string result;

	string configID = config.getconst_id();
	string moduleID = module.getModuleID();
	string commandUri, command;

	string configUri = "/" + moduleID + "/" + configID + "/";
	result += "<p><li><a href='" + configUri + "config'>" + configID + "</a>";
				
	auto storeStatus = module.getStatusStore();
	if (!storeStatus)
	{
		throw ConnectedVision::runtime_error("error: could not retrieve status store! ");
	}
	auto status = storeStatus->getByID(configID);
	if (!status)
	{
		throw ConnectedVision::runtime_error("error: could not retrieve status! ");
	}
	storeStatus.reset();

	result += " - belonging to module ";

	// create belonging module config list overview link
	result += "<a href='/" + moduleID + "/configListOverview" + "'>" + moduleID + "</a>";

	string statusString = *status->getconst_status();
	result += " - status:\t";
	if (statusString.compare("running") == 0)
	{
		result += "<span style='background-color:lawngreen;'>" + statusString + "</span>";
	}
	else if (statusString.compare("error") == 0)
	{
		result += "<span style='background-color:red;'>" + statusString + "</span>";
	}
	else if (statusString.compare("init") == 0)
	{
		result += "<span style='background-color:lightblue;'>" + statusString + "</span>";
	}
	else if (statusString.compare("stopped") == 0)
	{
		result += "<span style='background-color:silver;'>" + statusString + "</span>";
	}
	else
	{
		result += statusString;
	}

	result += "<br>";

	command = "config?cmd=DELETE";
	commandUri = configUri + command;
	std::string queryString = "Are you sure you want to delete config with configID";
	queryString += configID;
	queryString += " with all chained configs (if possible)?";
	result += "\t[<a href='" + commandUri + "' onclick='return confirm(\"" + queryString + "\")'>" + "delete" + "</a>]\t";

	command = "configOnlyThis?cmd=DELETE";
	commandUri = configUri + command;
	queryString = "Are you sure you want to delete config with configID ";
	queryString += configID;
	queryString += " without chained configs?";
	result += "\t[<a href='" + commandUri + "' onclick='return confirm(\"" + queryString + "\")'>" + "deleteOnlyThis" + "</a>]\t";


	result += "<br>";
			
	result += "name: " + *config.getconst_name() + "<br>";
	result += "description: " + *config.getconst_description() + "<br>";
			
	result += "aliasIDs: ";
	auto listAliasIDs = config.getconst_aliasID();
	for (auto itAliasID = listAliasIDs->begin(); itAliasID!=listAliasIDs->end(); ++itAliasID)
	{
		id_t resolvedConfigID = module.resolvePotentialAliasID(*(*itAliasID)->getconst_id());
		if ( itAliasID != listAliasIDs->begin() )
			result += ",\t";
		if (configID == resolvedConfigID)
		{
			result += "{\"" + *(*itAliasID)->getconst_id() + "\"}\tlinked";
		}
		else
		{
			result += "{\"" + *(*itAliasID)->getconst_id() + "\"}\tlinked to config <a href='/" + moduleID + "/" + resolvedConfigID + "/config" + "'>" + resolvedConfigID + "</a>";
		}
	}
	if (listAliasIDs->size() == 0)
	{
		result += "none";
	}
	result += "<br>";

	command = "config";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "status";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "params";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "control/reset";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "control/resetThis";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "control/start";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "control/stop";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	command = "control/stopThis";
	commandUri = configUri + command;
	result += "\t[<a href='" + commandUri + "'>" + command + "</a>]\t";

	result += "</li></p>";	


	//input pin list
	/*
	result += "<details><summary>Input Pins<br></summary>";
	result += "pin1<br>";
	result += "pin2<br>";
	result += "pin3<br>";
	result += "</details><br>";
	*/

	result += "<script type=\"text/javascript\"> function switchInputPins_" + moduleID + "_" + configID + "(){ if (document.getElementById(\"InputPins_" + moduleID + "_" + configID + "\").style.display==\"none\"){ document.getElementById(\"InputPins_" + moduleID + "_" + configID + "\").style.display=\"\"; } else { document.getElementById(\"InputPins_" + moduleID + "_" + configID + "\").style.display=\"none\"; } } </script>";
	result += "<input type='checkbox' value='' onclick='javascript:switchInputPins_" + moduleID + "_" + configID + "()'>show Input Pins";
	result += "<div id='InputPins_" + moduleID + "_" + configID + "' style='display: none'><ul>";

	auto inputPinIDs = module.getInputPinIDs();
	for (auto it = inputPinIDs.begin(); it!=inputPinIDs.end(); ++it)
	{
		auto pinID = (*it);
		int countInputPins = module.getInputPinCount(config, pinID);
		for (int i=0; i < countInputPins; i++)
		{
			auto inputPin = module.getInputPin(config, pinID, i);
			try
			{
				auto predecessorConfig = inputPin->getConfig();
				result += "<li>" + inputPin->getInputPinID();
				if (countInputPins>1)
				{
					result += "." + boost::lexical_cast<string>(i);							
				}
				result += ":\tconnected to ";
				result += "<a href='/" + predecessorConfig.getconst_moduleID() + "/" + predecessorConfig.getconst_id()  + "/config" + "'>" + predecessorConfig.getconst_id() + "</a>";
				result += " - <a href='/" + predecessorConfig.getconst_moduleID() + "/" + predecessorConfig.getconst_id()  + "/configSummary" + "'> configSummary </a>";
				result += "</li>";
			}
			catch (std::exception)
			{
				result += "<li>" + inputPin->getInputPinID();
				if (countInputPins>1)
				{
					result += "." + boost::lexical_cast<string>(i);							
				}
				result += ":\t";
				result += "<span style='background-color:red; color:white;'>connection not available</span>";
				result += "</li>";
			}
		}
	}
	if (inputPinIDs.size() == 0)
	{
		result += "no Input Pins<br>";
	}

	result += "</ul></div><br>";


	// output pin list
	result += "<script type=\"text/javascript\"> function switchOutputPins_" + moduleID + "_" + configID + "(){ if (document.getElementById(\"OutputPins_" + moduleID + "_" + configID + "\").style.display==\"none\"){ document.getElementById(\"OutputPins_" + moduleID + "_" + configID + "\").style.display=\"\"; } else { document.getElementById(\"OutputPins_" + moduleID + "_" + configID + "\").style.display=\"none\"; } } </script>";
	result += "<input type='checkbox' value='' onclick='javascript:switchOutputPins_" + moduleID + "_" + configID + "()'>show Output Pins";
	result += "<div id='OutputPins_" + moduleID + "_" + configID + "' style='display: none'><ul>";

	auto outputPinIDs = module.getOutputPinIDs();
	for (auto it = outputPinIDs.begin(); it!=outputPinIDs.end(); ++it)
	{
		auto pinID = (*it);
		result += "<li>" + pinID + ":\t" + "<a href='/" + moduleID + "/" + configID + "/" + pinID + "/newest'> newest </a></li>";			
	}
	if (outputPinIDs.size() == 0)
	{
		result += "no Output Pins<br>";
	}

	result += "</ul></div><br>";

	return(result);
}

/**
 * get configuration / job status chain
 *
 * @param[in]  config		configuration chain
 * @param[out] response		status as JSON string
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::getStatus(const id_t configID, ConnectedVisionResponse& response)
{
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	try 
	{
		// get object from Store
		auto statusConst = this->statusStore->getByID(resolvedConfigID);
		auto configConst = this->configStore->getByID(resolvedConfigID);

		if ( statusConst && configConst )
		{
			auto status = statusConst->copy();
	
			// prepare own status
			status->set_moduleID( getModuleID() );

			// request status chain
			vector<boost::shared_ptr<string>> statusChain;
			
			for(std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
			{
				pinID_t pinID = *it;
				int inputPinCount = this->getInputPinCount(configConst, pinID);

				for(int iPin = 0; iPin < inputPinCount; iPin++)
				{
					boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*configConst, pinID, iPin);
					
					///@TODO handle optional input pins
					try
					{
						if ( !inPin )
							throw ConnectedVision::runtime_error("pin pool is full");
						Class_generic_status s = inPin->getStatus();
						boost::shared_ptr< string > str( new string(s.toJsonStr()) );
						statusChain.push_back( str );
					}
					catch (std::runtime_error& e)
					{
						return writeErrorLog(response, HTTP_Status_ERROR, "cannot get status chain for pin: " + pinID + " (" + e.what() + ")" );
					}
				}
			}
			status->set_chain( statusChain );


			// return JSON string
			response.setContentType("application/json");
			response.setContent( status->toJsonStr() );

			return HTTP_Status_OK;
		}
		else
		{
				// not found
			return writeErrorLog(response, HTTP_Status_NOT_FOUND, "getStatus: config not found");
		}
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

/**
 * delete configuration / job chain
 *
 * @param[in] configID		ID of configuration / job
 * @param[out] response		config
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::deleteConfig(const id_t configID, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );
	
	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "deleteConfig: module not ready" );

	/*
	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}
	*/

	try 
	{
		// get config from store and clone it to make it writeable
		auto configConst = this->configStore->getByID(configID);
		if ( configConst )
		{
			auto config = configConst->copy();

			// delete config chain
			boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> deletedChain = config->get_chain();
			std::vector<boost::shared_ptr<Class_generic_config_chain>>::iterator it;
			for (it = deletedChain->begin(); it != deletedChain->end(); ++it)
			{
				boost::shared_ptr<Class_generic_config_chain>& deletedChainItem = *it;

				// use first connections
				// all following connections are for the same module and would trigger it multiple times
				const boost::shared_ptr<Class_generic_config_chain_connections>& conn = deletedChainItem->getconst_connections(0);
				const pinID_t& inputPinID = *conn->getconst_inputPinID();

				// set config for input pin
				try
				{
					boost::shared_ptr< IConnectedVisionInputPin > inPin = this->getInputPin( *config, inputPinID );
					std::string deletedConfig = inPin->deleteConfig().toJsonStr();	// delete sub config and get deleted config as string
					deletedChainItem->set_config( deletedConfig );	// update chain item with deleted config (deletedChainItem is a reference to an chain item
				}
				catch (std::runtime_error& e)
				{
					string error = "{ \"status\": \"error\", \"error\": \"cannot delete config chain for pin: " + inputPinID + " (" + e.what() + ") \" }";
					deletedChainItem->set_config( error );
				}	
			}
			config->set_chain( deletedChain );	// set chain to return values from sub config delete command

			return this->deleteConfigOnlyThis(configID, response);
		}
		else
		{
			// not found
			return writeErrorLog(response, HTTP_Status_NOT_FOUND, "deleteConfig: config not found");
		}
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

/**
 * delete only this configuration (only this specific config without subconfigs that are part of its chain)
 *
 * @param[in] configID		ID of configuration
 * @param[out] response		config
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::deleteConfigOnlyThis(const id_t configID, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );
	
	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "deleteConfigOnlyThis: module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	try 
	{
		// get config from Store
		boost::shared_ptr<const Class_generic_config> config( this->configStore->getByID(resolvedConfigID) );
		if ( config )
		{
			// delete DB results
			this->deleteResults( config );

			// delete status
			this->statusStore->deleteByID( resolvedConfigID );

			// delete config
			this->configStore->deleteByID( resolvedConfigID );

			// return JSON string
			response.setContentType("application/json");
			response.setContent( config->toJsonStr() );
			return HTTP_Status_OK;
		}
		else
		{
			// not found
			return writeErrorLog(response, HTTP_Status_NOT_FOUND, "deleteConfigOnlyThis: config not found");
		}
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}


/**
 * Ensure that the config is valid. I.e. check if the number of connected input pins is in the range of the pin description min and max values. If not, then an error is thrown.
 *
 * @param[in] config	configuration chain
 *
 */
void Module_BaseClass::checkConfig(const Class_generic_config &config)
{
	for(size_t i = 0; i < this->inputPinDescriptions.size(); i++)
	{
		boost::shared_ptr<Class_PinDescription> desc = this->inputPinDescriptions.at(i);
		id_t pinID = id_t(*desc->get_id());
		int pinCount = this->getInputPinCount(config, pinID);

		if(pinCount > desc->get_maxPinCount())
		{
			throw ConnectedVision::runtime_error("The number of connected input pins for pin ID " + pinID + " (" + intToStr(pinCount) + ") is greater than the input pin description max pin count (" + intToStr(desc->get_maxPinCount()) + ").");
		}

		if(pinCount < desc->get_minPinCount())
		{
			string str = "The number of connected input pins for pin ID " + pinID + "  (" + intToStr(pinCount) + ") is smaller than the input pin description min pin count (" + intToStr(desc->get_minPinCount()) + ").";

			if(pinCount == 0)
			{
				str += " Check if the module config contains all required chain elements with correspondigly defined connections from the output pins of preceding module to the input pins of this module.";
			}

			throw ConnectedVision::runtime_error(str);
		}
	}

	// check the specified input pins for invalid pin IDs
	auto chains = config.get_chain();

	for(int i = 0; i < chains->size(); i++)
	{
		auto connections = chains->at(i)->get_connections();

		for(int j = 0; j < connections->size(); j++)
		{
			auto pinID = pinID_t(*connections->at(j)->get_inputPinID());
			this->checkInputPinID(pinID);
		}
	}

	// check if moduleFeatures/supportsDynamicParameters and configFeatures/allowDynamicParameters configuration is allowed
	bool supportsDynamicParameters = false;
	if (this->moduleDescriptionJSON.HasMember("moduleFeatures"))
	{
		if (this->moduleDescriptionJSON["moduleFeatures"].IsObject())
		{
			if (this->moduleDescriptionJSON["moduleFeatures"].HasMember("supportsDynamicParameters"))
			{
				if (this->moduleDescriptionJSON["moduleFeatures"]["supportsDynamicParameters"].IsBool())
				{
					supportsDynamicParameters = this->moduleDescriptionJSON["moduleFeatures"]["supportsDynamicParameters"].GetBool();
				}
				else
				{
					throw ConnectedVision::runtime_error( string("error: ill-formated module description: \"moduleFeatures/supportsDynamicParameters\" is no bool value! "));
				}
			}
		}
		else
		{
			throw ConnectedVision::runtime_error( string("error: ill-formated module description: member \"moduleFeatures\" is no JSON object! "));
		}
	}
	if (config.getconst_configFeatures()->getconst_allowDynamicParameters() && (!supportsDynamicParameters))
	{
		throw ConnectedVision::runtime_error( string("error in module description: member \"moduleFeatures/supportsDynamicParameters\" is false but trying to create a config with \"configFeatures/allowDynamicParameters\". This is not allowed! "));
	}	


	rapidjson::Document params;
	if (params.Parse<0>(config.getconst_params()->c_str()).HasParseError())
	{
		throw ConnectedVision::runtime_error( string("ERROR: JSON parse error: ") + rapidjson::GetParseError_En(this->moduleDescriptionJSON.GetParseError()) + " @ " + intToStr(this->moduleDescriptionJSON.GetErrorOffset()) );
	}

	if (!this->defaultParameters.IsNull()) // if params object is empty defaultParameters is null and thus merging with the provided params does not work, so skip this step
	{
		// merge params object with default params
		rapidjson::Value mergedParameters;
		extendJsonObject(defaultParameters, params, mergedParameters, params.GetAllocator());
		params.CopyFrom(mergedParameters, params.GetAllocator());
	}

	rapidjson::Document initialParams;
	if (initialParams.Parse<0>(config.getconst_initialParams()->c_str()).HasParseError())
	{
		throw ConnectedVision::runtime_error( string("ERROR: JSON parse error: ") + rapidjson::GetParseError_En(this->moduleDescriptionJSON.GetParseError()) + " @ " + intToStr(this->moduleDescriptionJSON.GetErrorOffset()) );
	}

	if (!this->defaultParameters.IsNull()) // if params object is empty defaultParameters is null and thus merging with the provided params does not work, so skip this step
	{
		// merge initialParams object with default params
		rapidjson::Value mergedInitialParameters;
		extendJsonObject(defaultParameters, initialParams, mergedInitialParameters, initialParams.GetAllocator());
		initialParams.CopyFrom(mergedInitialParameters, initialParams.GetAllocator());
	}

	 // if parameterDesc == NULL <-> params: {}, initialParams: {} -> only invoke functioncheckRequiredParameters and checkRecursivelyIfParameterValueExistsInModuleDescription if != NULL
	if (parameterDesc != NULL)
	{
		// check params for required parameters and type and if all provided fields are known according to module description

		// check if all required parameters are present and if the type of all parameters is correct
		checkRecursivelyRequiredParametersAndType(this->parameterDesc, params);

		// check if all provided members and submembers in the parameter object are known (as defined by the module description)
		checkRecursivelyIfParameterValueExistsInModuleDescription(this->parameterDesc, params);


		// check initialParams for required parameters and type and if all provided fields are known according to module description 

		// check if all required parameters are present and if the type of all parameters is correct
		checkRecursivelyRequiredParametersAndType(this->parameterDesc, initialParams);

		// check if all provided members and submembers in the parameter object are known (as defined by the module description)
		checkRecursivelyIfParameterValueExistsInModuleDescription(this->parameterDesc, initialParams);

		checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(this->parameterDesc, initialParams, params, config.getconst_configFeatures()->getconst_allowDynamicParameters() && (supportsDynamicParameters));
	}	
}

void Module_BaseClass::checkValueType(const rapidjson::Value &value, const ParameterValueType &type)
{
	if ( (type == ParameterValueType::Integer64) && (!value.IsInt64()) )
	{
		throw ConnectedVision::runtime_error(std::string("wrong value type: integer expected but different type found! "));
	}
	else if ( (type == ParameterValueType::Number) && (!value.IsNumber()) )
	{
		throw ConnectedVision::runtime_error(std::string("wrong value type: number expected but different type found! "));
	}
	else if ( (type == ParameterValueType::String) && (!value.IsString()) )
	{
		throw ConnectedVision::runtime_error(std::string("wrong value type: string expected but different type found! "));
	}
	else if ( (type == ParameterValueType::Boolean) && (!value.IsBool()) )
	{
		throw ConnectedVision::runtime_error(std::string("wrong value type: bool expected but different type found! "));
	}
	else if (type == ParameterValueType::Unsupported)
	{
		throw ConnectedVision::runtime_error(std::string("a value in the module description is of unsupported type! "));
	}
	else if((!value.IsString()) && (!value.IsInt64()) && (!value.IsNumber()) && (!value.IsBool()) && (!value.IsObject()) && (!value.IsArray()))
	{
		throw ConnectedVision::runtime_error(std::string("value type is of unsupported type! "));
	}
}

void Module_BaseClass::checkRecursivelyRequiredParametersAndType(const boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> &parameterDescTreeNode, const rapidjson::Value &currentParameterNode)
{
	if (!currentParameterNode.IsObject())
	{
		throw ConnectedVision::runtime_error(std::string("parameter value error: object was expected but missing! "));
	}

	if (!parameterDescTreeNode)
	{
		throw ConnectedVision::runtime_error(std::string("parameterDescTreeNode was NULL! "));
	}

	// for every element of parameter description tree at current tree node
	for (auto itDesc = parameterDescTreeNode->begin(); itDesc != parameterDescTreeNode->end(); ++itDesc)
	{
		std::string name = itDesc->first;

		// test if target parameter value has member (parameter) with matching name
		if (currentParameterNode.HasMember(name.c_str()))
		{
			const rapidjson::Value &value = currentParameterNode[name.c_str()];
			if (itDesc->second.pSubObject)
			{
				checkRecursivelyRequiredParametersAndType(itDesc->second.pSubObject, value);
			}
			else if (itDesc->second.pSubArray)
			{
				checkRecursivelyRequiredParametersAndType(itDesc->second.pSubArray, value);
			}

			// check if value type is supported in ConnectedVision
			checkValueType(value, itDesc->second.type);
		}
		else
		{
			if (itDesc->second.required)
			{
				throw ConnectedVision::runtime_error(std::string("required parameter " + name + " was not found in provided parameter value! "));
			}
		}
	}
}

void Module_BaseClass::checkRecursivelyRequiredParametersAndType(const boost::shared_ptr<ParameterDescTreeNode> &parameterDescTreeNode, const rapidjson::Value &currentParameterNode)
{
	if (!currentParameterNode.IsArray())
	{
		throw ConnectedVision::runtime_error(std::string("parameter value error: array was expected but missing! "));
	}

	if (parameterDescTreeNode->required)
	{
		if (currentParameterNode.Size() <= 0)
		{
			throw ConnectedVision::runtime_error(std::string("parameter: array is empty but is required to have elements since array items were defined as required in parameter description in the module description! "));
		}
	}
	
	for (auto it = currentParameterNode.Begin(); it != currentParameterNode.End(); ++it)
	{
		if (parameterDescTreeNode->pSubObject)
		{
			if (it->IsObject())
			{
				checkRecursivelyRequiredParametersAndType(parameterDescTreeNode->pSubObject, *it);
			}
			else
			{
				throw ConnectedVision::runtime_error(std::string("parameter: array elements expected to be of type object but weren't! "));
			}
		}		
		if (parameterDescTreeNode->pSubArray)
		{
			if (it->IsArray())
			{
				checkRecursivelyRequiredParametersAndType(parameterDescTreeNode->pSubArray, *it);
			}
			else
			{
				throw ConnectedVision::runtime_error(std::string("parameter: array elements expected to be of type array but weren't! "));
			}
		}
		else
		{
			if (parameterDescTreeNode->required)
			{
				// check if value type is supported in ConnectedVision
				checkValueType(*it, parameterDescTreeNode->type);
			}
		}
	}
}

void Module_BaseClass::testDynamicParameterSanityAndUpdate(rapidjson::Value &node, bool expectDynamicValueToBeTrue, bool inSubArray)
{
	for (auto it = node.MemberBegin(); it != node.MemberEnd(); ++it)
	{		
		rapidjson::Value *pElem;
		if (inSubArray)
		{
			pElem = &node;
		}
		else
		{
			pElem = &it->value;
		}

		if (pElem->HasMember("type"))
		{
			if (std::string((*pElem)["type"].GetString()) == "object") // object handling
			{
				if (pElem->HasMember("dynamic"))
				{
					if ((*pElem)["dynamic"].IsBool())
					{
						if ((*pElem)["dynamic"].GetBool())
						{
							if (pElem->HasMember("properties"))
							{
								testDynamicParameterSanityAndUpdate((*pElem)["properties"], true);
							}
							else
							{
								throw ConnectedVision::runtime_error(std::string("member \"properties\" is missing inside an object! "));
							}	
						}
						else
						{
							if (expectDynamicValueToBeTrue)
							{
								throw ConnectedVision::runtime_error(std::string("parse error of module description (a parameter is specified as non-dynamic which is inside a dynamic parameter object)! "));
							}	
							testDynamicParameterSanityAndUpdate((*pElem)["properties"], false);
						}
					}
					else
					{
						throw ConnectedVision::runtime_error(std::string("parse error of module description (bool value expected for member \"dynamic\")! "));
					}
				}
				else // if "dynamic" member was not found
				{
					testDynamicParameterSanityAndUpdate((*pElem)["properties"], expectDynamicValueToBeTrue, false);

					// append "dynamic" member
					pElem->AddMember("dynamic", expectDynamicValueToBeTrue, this->moduleDescriptionJSON.GetAllocator());
						
					if (inSubArray)  // if in sub-array pElem points to node, so AddMember() did invalidate the iterator
					{
						break; // so leave loop since we are done anyway
					}
				}
			}
			else if (std::string((*pElem)["type"].GetString()) == "array") // array handling
			{
				if (pElem->HasMember("dynamic"))
				{
					if ((*pElem)["dynamic"].IsBool())
					{
						if (!(*pElem)["dynamic"].GetBool())
						{
							if (expectDynamicValueToBeTrue)
							{
								throw ConnectedVision::runtime_error(std::string("parse error of module description (a parameter is specified as non-dynamic which is inside a dynamic array)! "));
							}
							testDynamicParameterSanityAndUpdate((*pElem)["items"], false, true);
						}
						else
						{
							testDynamicParameterSanityAndUpdate((*pElem)["items"], true, true);
						}
					}
					else
					{
						throw ConnectedVision::runtime_error(std::string("parse error of module description (bool value expected for member \"dynamic\")! "));
					}
				}
				else // if "dynamic" member was not found
				{				
					testDynamicParameterSanityAndUpdate((*pElem)["items"], expectDynamicValueToBeTrue, true);

					// append "dynamic" member
					pElem->AddMember("dynamic", expectDynamicValueToBeTrue, this->moduleDescriptionJSON.GetAllocator());

					if (inSubArray)  // if in sub-array pElem points to node, so AddMember() did invalidate the iterator
					{
						break; // so leave loop since we are done anyway
					}
				}
			}
			else // handling of other types
			{
				if (pElem->HasMember("dynamic"))
				{
					if ((*pElem)["dynamic"].IsBool())
					{
						if ((!(*pElem)["dynamic"].GetBool()) && (expectDynamicValueToBeTrue))
						{
							throw ConnectedVision::runtime_error(std::string("parse error of module description (a parameter is specified as non-dynamic which is inside a dynamic object or array)! "));
						}						
					}
					else
					{
						throw ConnectedVision::runtime_error(std::string("parse error of module description (bool value expected for member \"dynamic\")! "));
					}
				}
				else
				{
					// append "dynamic" member				
					pElem->AddMember("dynamic", expectDynamicValueToBeTrue, this->moduleDescriptionJSON.GetAllocator());

					if (inSubArray)  // if in sub-array pElem points to node, so AddMember() did invalidate the iterator
					{
						break; // so leave loop since we are done anyway
					}
				}
			}
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("parse error of module description (one or more parameters are missing member \"type\")! "));
		}
	}
}

/**
* recursively build the parameter description object
* this function variant is used to process sub-objects
*/
void Module_BaseClass::buildParameterDescriptionRecursive(const rapidjson::Value &node, boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> pTreeNode)
{	
	for (auto it = node.MemberBegin(); it != node.MemberEnd(); ++it)
	{
		ParameterDescTreeNode newTreeNode;
		
		if (it->value.HasMember("dynamic"))
		{
			newTreeNode.dynamic = it->value["dynamic"].GetBool();
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("member \"dynamic\" missing! Parameter description tree was not built up correctly! "));
		}

		if (it->value.HasMember("required"))
		{
			newTreeNode.required = it->value["required"].GetBool();
		}
		else
		{
			newTreeNode.required = false;
		}

		if (std::string(it->value["type"].GetString()) == "object") // object handling
		{
			boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> pSubObject = boost::make_shared<std::map<std::string, ParameterDescTreeNode>>();
			buildParameterDescriptionRecursive(it->value["properties"], pSubObject);
			newTreeNode.pSubObject = pSubObject;
			newTreeNode.type = ParameterValueType::Object;
		}
		else if (std::string(it->value["type"].GetString()) == "array") // array handling
		{
			boost::shared_ptr<ParameterDescTreeNode> pSubArray = boost::make_shared<ParameterDescTreeNode>();
			rapidjson::Value tmp(it->value["items"], this->moduleDescriptionJSON.GetAllocator());
			buildParameterDescriptionRecursive(tmp, pSubArray);
			newTreeNode.pSubArray = pSubArray;
			newTreeNode.type = ParameterValueType::Array;
		}
		else if (std::string(it->value["type"].GetString()) == "integer")
		{
			newTreeNode.type = ParameterValueType::Integer64;
		}
		else if (std::string(it->value["type"].GetString()) == "number")
		{
			newTreeNode.type = ParameterValueType::Number;
		}
		else if (std::string(it->value["type"].GetString()) == "string")
		{
			newTreeNode.type = ParameterValueType::String;
		}
		else if (std::string(it->value["type"].GetString()) == "boolean")
		{
			newTreeNode.type = ParameterValueType::Boolean;
		}
		else
		{
			newTreeNode.type = ParameterValueType::Unsupported;
		}
		
		pTreeNode->insert(make_pair(it->name.GetString(), newTreeNode));
	}
}

/**
* recursively build the parameter description object
* this function variant is used to process sub-arrays
*/
void Module_BaseClass::buildParameterDescriptionRecursive(const rapidjson::Value &node, boost::shared_ptr<ParameterDescTreeNode> pTreeNode)
{
	if (node.HasMember("dynamic"))
	{
		pTreeNode->dynamic = node["dynamic"].GetBool();
	}
	else
	{
		throw ConnectedVision::runtime_error(std::string("member \"dynamic\" missing! Parameter description tree was not built up correctly! "));
	}

	if (node.HasMember("required"))
	{
		pTreeNode->required = node["required"].GetBool();
	}
	else
	{
		pTreeNode->required = false;
	}
		
	if (std::string(node["type"].GetString()) == "object") // object handling
	{
		boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> pSubObject = boost::make_shared<std::map<std::string, ParameterDescTreeNode>>();
		buildParameterDescriptionRecursive(node["properties"], pSubObject);
		pTreeNode->pSubObject = pSubObject;
		pTreeNode->type = ParameterValueType::Object;
	}
	else if (std::string(node["type"].GetString()) == "array") // array handling
	{
		boost::shared_ptr<ParameterDescTreeNode> pSubArray = boost::make_shared<ParameterDescTreeNode>();
		buildParameterDescriptionRecursive(node["items"], pSubArray);
		pTreeNode->pSubArray = pSubArray;
		pTreeNode->type = ParameterValueType::Array;
	}
	else if (std::string(node["type"].GetString()) == "integer")
	{
		pTreeNode->type = ParameterValueType::Integer64;
	}
	else if (std::string(node["type"].GetString()) == "number")
	{
		pTreeNode->type = ParameterValueType::Number;
	}
	else if (std::string(node["type"].GetString()) == "string")
	{
		pTreeNode->type = ParameterValueType::String;
	}
	else if (std::string(node["type"].GetString()) == "boolean")
	{
		pTreeNode->type = ParameterValueType::Boolean;
	}
	else
	{
		pTreeNode->type = ParameterValueType::Unsupported;
	}
}

Module_BaseClass::ParameterDescriptionNodeInfo Module_BaseClass::queryParameterDescriptionInfo(const std::string parameterPath)
{
	std::vector<std::string> parameterPathElements;
	boost::split(parameterPathElements, parameterPath, boost::is_any_of("/"));

	std::map<std::string, ParameterDescTreeNode> *pCurrentMap = this->parameterDesc.get();
	for (int i = 0; i < parameterPathElements.size(); ++i)
	{
		auto found = pCurrentMap->find(parameterPathElements.at(i));
		if (found != pCurrentMap->end())
		{
			if (i < parameterPathElements.size() - 1)
			{
				if (found->second.pSubObject)
				{
					pCurrentMap = found->second.pSubObject.get();
				}
				else if (found->second.pSubArray)
				{
					//pCurrentMap = found->second.pSubArray->pSubObject.get();
					throw ConnectedVision::runtime_error(std::string("error: (sub-)array found which is not the last element in parameterPath (this is currently not allowed)! "));
				}
				else
				{
					throw ConnectedVision::runtime_error(std::string("error: an element in parameterPath was expected to be a (sub-)object or (sub-)array but seems to be a plain value! "));
				}
			}
			else
			{
				Module_BaseClass::ParameterDescriptionNodeInfo nodeInfo;
				if (found->second.pSubObject)
				{
					nodeInfo.type = found->second.type;
					nodeInfo.dynamic = found->second.dynamic;
					nodeInfo.dynamicItems = false;
					nodeInfo.required = found->second.required;					
				}
				else if (found->second.pSubArray)
				{
					nodeInfo.type = found->second.type;
					nodeInfo.dynamic = found->second.dynamic;
					nodeInfo.dynamicItems = found->second.pSubArray->dynamic;
					nodeInfo.required = found->second.required;
				}
				else
				{
					nodeInfo.type = found->second.type;
					nodeInfo.dynamic = found->second.dynamic;
					nodeInfo.dynamicItems = false;
					nodeInfo.required = found->second.required;				
				}
				return (nodeInfo);
			}
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("error: queried parameter was not found! "));
		}
	}
	throw ConnectedVision::runtime_error(std::string("error: queried parameter was not found! "));
}

/**
 * Ensure that the pin ID is valid. I.e. check if there is a period character after the pin ID followed by non-numerical characters.
 *
 * @param[in] config	configuration chain
 *
 */
void Module_BaseClass::checkInputPinID(const pinID_t pinID)
{
	/*
	regex meaning (also see https://regex101.com/):

	"^"					... start of line
	"[^\\.]+"			... everything except "." and at least 1 character
	"\\."				... exactly 1x "."
	"(.*([^0-9]+).*)*"	... everything that contains at least one non-digit character
	"$"					... end of line

	*/
	boost::regex re = boost::regex("^[^\\.]+\\.(.*([^0-9]+).*)*$");
	boost::smatch matches;

	if(boost::regex_match(pinID, matches, re))
	{
		throw ConnectedVision::runtime_error("invalid pin ID: \"" + pinID + "\" (the period character after the pin ID may only be followed by an integer)");
	}
}

/**
 * Ensure that the pin description is valid. I.e. check if the min pin count is not smaller than 0.
 */
void Module_BaseClass::checkInputPinDescription(const boost::shared_ptr<Class_PinDescription> description)
{
	if(description->get_minPinCount() < 0)
	{
		throw ConnectedVision::runtime_error("min pin count for pin ID " + *description->get_id() + " must not be smaller than 0");
	}
}

/** 
 * get a list of configIDs of this Connected Vision module which have the specified aliasID assigned,
 * the return list is ordered by aliasID creation timestamp in descending order 
 *
 * @param[in] aliasID	the aliasID string used as search parameter
 * @return	list of configIDs (of this module) which have the specified aliasID assigned, ordered by aliasID creation timestamp in descending order
 */
std::vector<ConnectedVision::id_t> Module_BaseClass::getConfigIDsByAliasID(std::string aliasID)
{
	struct SortStructConfigID // custom structure used for sort mechanism: a configID with its corresponding aliasID creation timestamp
	{
		ConnectedVision::id_t configID;
		timestamp_t aliasIDcreationTimestamp;
	};
	std::vector<SortStructConfigID> listSortStruct;

	struct CompareClass { // custom compare class used for std::sort algorithm (returns true if first config claimed aliasID more recently than second config)
		bool operator() (SortStructConfigID i, SortStructConfigID j) { return (i.aliasIDcreationTimestamp > j.aliasIDcreationTimestamp); }
	} comp;


	std::vector<id_t> listIDs = configStore->getIDList();
	for (size_t i = 0; i < listIDs.size(); i++) // for every config
	{
		boost::shared_ptr<const Class_generic_config> config = configStore->getByID(listIDs[i]);
		if (!config)
		{
			throw std::runtime_error("error: config returned from configStore is null");
		}

		const auto listAliasID = config->getconst_aliasID(); // get aliasID list
		for (auto it = listAliasID->begin(); it != listAliasID->end(); ++it ) // for every aliasID in this list
		{
			auto &aliasElement = *it;
			if (*aliasElement->getconst_id() == aliasID) // test if it is equal to the aliasID provided as function parameter
			{
				// if so create a temporary sort structure element with this configID and the corresponding aliasID creation timestamp
				SortStructConfigID element;
				element.configID = config->getconst_id();
				element.aliasIDcreationTimestamp = aliasElement->getconst_timestamp();
				listSortStruct.push_back(element); // and push this element into a list of sort structure elements
			}
		}
	}
	
	std::sort(listSortStruct.begin(), listSortStruct.end(), comp); // sort this list with the custom compare class

	// construct the output list containing only the configIDs in the right order
	std::vector<id_t> matchingAndSortedIDs;
	for (size_t i = 0; i < listSortStruct.size(); i++)
	{
		matchingAndSortedIDs.push_back(listSortStruct.at(i).configID);
	}

	return(matchingAndSortedIDs);
}

/** 
 * resolves the given configID (aliasID resolving in case provided configID string is actually an aliasID) and returns it
 *
 * @param[in] inputID	the ID as string (either a configID or an aliasID) that needs to be resolved
 * @return	the resolved configID
 */
ConnectedVision::id_t Module_BaseClass::resolvePotentialAliasID(const std::string &inputID)
{
	bool isAliasID = false;

	std::string truncatedID; // aliasID without prefix ("aliasID=" or "AliasID=") and postfix (".n")

	int indexPostFix = -1; // the index provided as postfix if present, -1 ... not specified

	// test if config exists (for performance reasons this is done first, to prevent unnecessary string parsing for aliasIDs
	boost::shared_ptr<const Class_generic_config> config = configStore->getByID(inputID);
	if (config) // if it is found, it is not an aliasID
	{
		return(inputID); // return inputID 
	}
	
	size_t posPrefix = inputID.find("aliasID=");
	if (posPrefix==string::npos)
	{
		posPrefix = inputID.find("AliasID=");
	}
	
	if (posPrefix!=string::npos)
	{
		if (posPrefix==0) // "aliasID=" or "AliasID=" substring found at string starting position (position 0)
		{
			isAliasID = true;
			posPrefix = 8; // set start position for truncation to character after prefix "aliasID=" (8 characters to omit, so set to string index position 9)
		}
		else
		{
			throw ConnectedVision::runtime_error("query aliasID malformed (prefix does not start at position 0)");
		}
	}
	else
	{
		posPrefix = 0; // set start position for truncation to first character of string
	}
	
	size_t posPostfix = inputID.find_last_of("."); // if not found posPostfix will be string::npos (end of string), intended behaviour since it will then be correct input for substr function

	if (posPostfix != inputID.find_first_of("."))
	{
		throw ConnectedVision::runtime_error("query aliasID malformed (postfix ambiguous due to multiple colons in aliasID string)");
	}

	if (posPostfix != string::npos)
	{
		isAliasID = true;
		std::string indexAsString = inputID.substr(posPostfix+1, string::npos);
		//boost::shared_ptr<std::string> indexAsString(new std::string(inputID.substr(posPostfix+1, string::npos)));
		try
		{
			indexPostFix = boost::lexical_cast<int>(indexAsString);
		}
		catch (std::exception& )
		{
			throw ConnectedVision::runtime_error("query aliasID malformed (postfix is not a valid number)");
		}
	}
	
	if (isAliasID)
	{
		size_t length; // used as second parameter for substr function
		if (posPostfix != string::npos)
			length = posPostfix - posPrefix; // end position (posPostfix) minus start position (posPrefix)
		else
			length = string::npos; // if not found indicate this to substr function
		truncatedID = inputID.substr(posPrefix, length); // cut away prefix and postfix from string

		if (truncatedID == "")
		{
			throw ConnectedVision::runtime_error("the supplied aliasID must not be empty");
		}

		std::vector<id_t> listConfigIDs = this->getConfigIDsByAliasID(truncatedID);

		if (listConfigIDs.size() == 0)
		{
			throw ConnectedVision::runtime_error("the queried aliasID was not found (aliasID: " + truncatedID + ")");
		}

		if (indexPostFix!=-1) // if postfix index was provided
		{
			if (listConfigIDs.size() > (size_t)indexPostFix)
			{
				return(listConfigIDs.at(indexPostFix)); // return configID of config that claimed the aliasID most recently
			}
			else
			{
				throw ConnectedVision::runtime_error("the queried aliasID with the specified (n+1)-(st/nd/th) youngest creation timestamp does not exist (for n=" + boost::lexical_cast<string>(indexPostFix) + ")");
			}
		}
		else
		{
			return(listConfigIDs.at(0)); // return configID of config that claimed the aliasID most recently
		}
	}
	else
	{
		std::vector<id_t> listConfigIDs = this->getConfigIDsByAliasID(inputID); // use inputID as aliasID and see if it is found
		if (listConfigIDs.size() > 0)
		{
			return(listConfigIDs.at(0)); // return configID of config that claimed the aliasID most recently
		}
		else
		{
			return(inputID); // if not found return inputID (important for config create and delete process)
		}
	}
}

/** 
 * updates (and merges) aliasID list of provided config with (potential already existing) config
 * (timestamps of aliasIDs provided with config set command will be updated)
 *
 * @param[in] configID		ID of configuration / job
 */
void Module_BaseClass::updateAliasIDs(boost::shared_ptr<Class_generic_config> config)
{
	boost::shared_ptr<const Class_generic_config> oldConfig = configStore->getByID(config->getconst_id());
	boost::shared_ptr< std::vector< boost::shared_ptr< Class_generic_config_aliasID > > > newAliasIDs = config->get_aliasID();

	timestamp_t creationTimestamp = sysTime();

	// delete empty aliasIDs (empty strings as id value) from new aliasID list (in-place in new aliasID list)
	// also delete aliasIDs which contain one of these characters: "/", "\\" (escaped backslash), "."
	// also delete aliasIDs which contain a substring "aliasID=" or "AliasID="
	for (int32_t iNew=(int32_t)newAliasIDs->size() - 1; iNew >= 0; iNew--)
	{
		std::string candidateAliasID = *newAliasIDs->at(iNew)->getconst_id();

		if ((candidateAliasID == "") ||
			(candidateAliasID.find_first_of("/\\.") != std::string::npos) ||
			(candidateAliasID.find("aliasID=") != std::string::npos) ||
			(candidateAliasID.find("AliasID=") != std::string::npos))
		{
			newAliasIDs->erase(newAliasIDs->begin() + iNew);
		}
	}

	// update all creation timestamp of new aliasIDs (in-place in new aliasID list)
	for (size_t iNew=0; iNew < newAliasIDs->size(); iNew++)
	{
		newAliasIDs->at(iNew)->set_timestamp(creationTimestamp);
	}

	if (oldConfig)
	{
		boost::shared_ptr< std::vector< boost::shared_ptr< Class_generic_config_aliasID > > > oldAliasIDs = oldConfig->get_aliasID();

		size_t sizeNewAliasIDsBeforeAppend = newAliasIDs->size(); // do not condider old configs that were already appended with push_back()

		for (size_t iOld=0; iOld < oldAliasIDs->size(); iOld++)
		{
			bool found = false;

			std::string aliasIDfromOld = *(oldAliasIDs->at(iOld)->getconst_id());
			for (int iNew=0; iNew < sizeNewAliasIDsBeforeAppend; iNew++) // do not condider old configs that were already appended with push_back()
			{
				std::string aliasIDfromNew = *(newAliasIDs->at(iNew)->getconst_id());

				if (aliasIDfromNew == aliasIDfromOld)
				{
					found = true;
				}
			}

			if (!found) // if this old aliasID was not found in list of new aliasIDs: add it to new aliasID list (but do not update the creation timestamp)
			{
				newAliasIDs->push_back(oldAliasIDs->at(iOld));
			}
		}
	}

	config->set_aliasID(newAliasIDs);

}

/**
 * set configuration / job chain
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] configStr		as JSON string encoded configuration chain
 * @param[out] response		config
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::setConfig(const id_t configIDConst, const std::string& configStr, ConnectedVisionResponse &response)
{
	id_t configID = configIDConst;
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	/**@TODO setConfig()
		- calculate ID with MD5
	*/
	try 
	{
		// parse config
		ConnectedVision::shared_ptr<Class_generic_config> config(new Class_generic_config);
		config->parseJson( configStr.c_str() );

		// overwrite module data
		config->set_moduleID( getModuleID() );

		// validate config
		checkConfig( *config );

		// set config chain
		boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_config_chain>>> chain = config->get_chain();
		std::vector<boost::shared_ptr<Class_generic_config_chain>>::iterator it;
		for (it = chain->begin(); it != chain->end(); ++it)
		{
			boost::shared_ptr<Class_generic_config_chain>& chainItem = *it;

			// use first connections
			// all following connections are for the same module and would trigger it multiple times
			const boost::shared_ptr<Class_generic_config_chain_connections>& conn = chainItem->getconst_connections(0);
			const pinID_t& inputPinID = *conn->getconst_inputPinID();

			// set config for input pin
			try
			{
				boost::shared_ptr< IConnectedVisionInputPin > inPin = this->getInputPin( *config, inputPinID );
				const Class_generic_config& c = inPin->setConfig(configID, config->getSubConfigConnectionByInputPin(inputPinID), inputPinID);
				chainItem->set_config( c.toJsonStr() );
			}
			catch (std::runtime_error& e)
			{
				string error = "{ \"status\": \"error\", \"error\": \"cannot set config chain for input pin: " + inputPinID + " (" + e.what() + ") \" }";
				chainItem->set_config( error );
			}	
		}
		config->set_chain( chain );

		// generate ID
		config->compute_id();

		if ( configID == "0" || configID == ID_NULL )
		{
			// use generated ID
			configID = config->get_id();
		}

		if ( configID != config->get_id() )
		{
			// Bad Request --> HTTP Code: 400
			return writeErrorLog(response, 400, "config ID mismatch");
		}

		updateAliasIDs(config);

		// save config
		config->set_id( configID );
		auto constConfig = this->configStore->make_const( config );
		this->configStore->save_const( constConfig );

		// set initial status
		auto constStatus = statusStore->getByID(configID);
		if ( !constStatus )
		{
			// create new status
			ConnectedVision::shared_ptr<Class_generic_status> status( new Class_generic_status( constConfig->get_id(), constConfig->get_moduleID(), *constConfig->get_moduleURI(), this->getOutputPinIDs() ) );
			status->set_id( configID );
			this->statusStore->save_move( status );
		}


		// return config
		return getConfig(configID, response);
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		return writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}
}

/**
 * send control command to module
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] command		command: start, stop, reset
 * @param[in] senderID		ID of sender (successor module)
 * @param[out] response		status of configuration / job
 *
 * @return status code (analog to HTTP codes)
 */
int Module_BaseClass::control(const id_t configID, const std::string& command, const id_t senderID, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	int httpCode = 0;

	if ( !statusStore || !configStore )
	{
		return writeErrorLog(response, HTTP_Status_ERROR, "not init" );
	}

	try 
	{
		// read status and config
		boost::shared_ptr< const Class_generic_config > config = configStore->getByID(resolvedConfigID);
		if ( !config )
		{
			// not found
			httpCode = writeErrorLog(response, HTTP_Status_NOT_FOUND, "control: config not found");
		}

		// config has been loaded -> get worker controller for config, or init new controller
		ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> workerController;
		try
		{
			workerController = mapWorkerControllers.at(resolvedConfigID);
		}
		catch (...)
		{
			// create new worker instance that is automatically registered via registerWorkerInstance()
			// multiple calls to this control() function and thus potential race conditions will be handled
			// because constructor of WorkerController will fail due to out_of_range exception (duplicate configID for map)
			// and the new operation will not be completed (roll-back)
			new ConnectedVision::Module::WorkerController(resolvedConfigID, *this, *this, this->workerTimeout);

			// re-fetch worker controller from mat to avoid racing conditions
			 workerController = mapWorkerControllers.at(resolvedConfigID);

			 if ( !workerController )
			 {
				 throw std::runtime_error("CORE PANIC: cannot create worker controller");
			 }
		}
		
		// handle command
		if ( command == "start" )
		{
			// make sure that config chain has been set
			for (std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
			{
				///@TODO handle optional input pins
				pinID_t pinID = *it;
				int inputPinCount = this->getInputPinCount(config, pinID);

				for(int iPin = 0; iPin < inputPinCount; iPin++)
				{
					pinID_t pinIDIndexed = getIndexedPinID(pinID, iPin);
					boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*config, pinIDIndexed);

					try
					{
						inPin->getConfig();
					}
					catch (NotFound_exception& e)
					{
						(void)e; // suppress unreferenced variable warning
						// set config and retry
						inPin->setConfig(resolvedConfigID, config->getSubConfigConnectionByInputPin(pinIDIndexed), pinIDIndexed);
					}

///////////////////////////////// MIGRATION FIX-ME  is sub-config started somewhere else ? ////////////////
					// start previous config
					inPin->start();
				}
			}

			if (senderID!=ID_NULL) // additional info: the id can be ID_NULL if no senderID was specified in url (e.g. a gui will issue a stop command without a senderID)
			{
				runningSuccessorList.insert(make_pair(senderID, true)); // a successor module sent the start command, so add it in the running successor list
			}

			// start processing
			this->start(workerController);

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else if ( command == "stop" )
		{
			runningSuccessorList.erase(senderID); // delete senderID from running successor list

			if (runningSuccessorList.size() == 0) // if no more successor module depends on this module's output
			{
				// stop processing
				this->stop(workerController);
			}
			boost::shared_ptr< const Class_generic_status > status = statusStore->getByID(resolvedConfigID);

			// if this module is stopped (not running) propagate to predecessors in chain, otherwise stop propagation
			if ( !status->is_status_running() )
			{
				// process chain (this has to be done AFTER the worker thread has finished)
				for (std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
				{
					///@TODO handle optional input pins
					pinID_t pinID = *it;
					int inputPinCount = this->getInputPinCount(config, pinID);

					for(int iPin = 0; iPin < inputPinCount; iPin++)
					{
						pinID_t pinIDIndexed = getIndexedPinID(pinID, iPin);
						boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*config, pinIDIndexed);

						try
						{
							Class_generic_status childStatus = inPin->stop();
						}
						catch (NotFound_exception& e)
						{
							(void)e; // suppress unreferenced variable warning
							// set config and retry
							inPin->setConfig(resolvedConfigID, config->getSubConfigConnectionByInputPin(pinIDIndexed), pinIDIndexed);
							inPin->stop();
						}
						catch (std::runtime_error& ) {}
					}
				}
			}

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else if ( command == "recover" )
		{
			// process chain
			for (std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
			{
				///@TODO handle optional input pins
				pinID_t pinID = *it;
				int inputPinCount = this->getInputPinCount(config, pinID);

				for(int iPin = 0; iPin < inputPinCount; iPin++)
				{
					pinID_t pinIDIndexed = getIndexedPinID(pinID, iPin);
					boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*config, pinIDIndexed);

					try
					{
						inPin->recover();
					}
					catch (NotFound_exception& e)
					{
						(void)e; // suppress unreferenced variable warning
						// set config and retry
						inPin->setConfig(resolvedConfigID, config->getSubConfigConnectionByInputPin(pinIDIndexed), pinIDIndexed);
						inPin->recover();
					}
					catch (std::runtime_error& ) {}
				}
			}

			// recover from error
			this->recover(workerController);

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else if ( command == "reset" )
		{
			runningSuccessorList.erase(senderID); // delete senderID from running successor list

			if (runningSuccessorList.size() == 0) // if no more successor module depends on this module's output
			{
				// reset processing
				this->reset(workerController);
			}
			boost::shared_ptr< const Class_generic_status > status = statusStore->getByID(resolvedConfigID);

			// if this module is reseted (not running) propagate to predecessors in chain, otherwise stop propagation
			if ( !status->is_status_running() )
			{
				// propagate reset to chain
				for (std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
				{
					///@TODO handle optional input pins
					pinID_t pinID = *it;
					int inputPinCount = this->getInputPinCount(config, pinID);

					for(int iPin = 0; iPin < inputPinCount; iPin++)
					{
						pinID_t pinIDIndexed = getIndexedPinID(pinID, iPin);
						boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*config, pinIDIndexed);

						try
						{
							inPin->reset();
						}
						catch (NotFound_exception& e)
						{
							(void)e; // suppress unreferenced variable warning
							// set config and retry
							inPin->setConfig(resolvedConfigID, config->getSubConfigConnectionByInputPin(pinIDIndexed), pinIDIndexed);
							inPin->reset();
						}
						catch (std::runtime_error& ) {}
					}
				}
			}

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else if ( command == "stopThis" )
		{
			runningSuccessorList.clear();

			// stop config
			this->stop(workerController);
			boost::shared_ptr< const Class_generic_status > status = statusStore->getByID(resolvedConfigID);

			// if this module is stopped (not running) notify to predecessors in chain, otherwise stop propagation
			if ( !status->is_status_running() )
			{
				// process chain (this has to be done AFTER the worker thread has finished)
				for (std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
				{
					///@TODO handle optional input pins
					pinID_t pinID = *it;
					int inputPinCount = this->getInputPinCount(config, pinID);

					for(int iPin = 0; iPin < inputPinCount; iPin++)
					{
						pinID_t pinIDIndexed = getIndexedPinID(pinID, iPin);
						boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*config, pinIDIndexed);

						try
						{
							Class_generic_status childStatus = inPin->notifyStop();
						}
						catch (NotFound_exception& e)
						{
							(void)e; // suppress unreferenced variable warning
							// set config and retry
							inPin->setConfig(resolvedConfigID, config->getSubConfigConnectionByInputPin(pinIDIndexed), pinIDIndexed);
							inPin->stop();
						}
						catch (std::runtime_error& ) {}
					}
				}
			}

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else if ( command == "resetThis" )
		{
			runningSuccessorList.clear();

			// reset config
			this->reset(workerController);
			boost::shared_ptr< const Class_generic_status > status = statusStore->getByID(resolvedConfigID);

			// if this module is reseted (not running) notify to predecessors in chain, otherwise stop propagation
			if ( !status->is_status_running() )
			{
				// propagate reset to chain
				for (std::vector<std::string>::const_iterator it = this->inputPinIDs.begin(); it != this->inputPinIDs.end(); ++it)
				{
					///@TODO handle optional input pins
					pinID_t pinID = *it;
					int inputPinCount = this->getInputPinCount(config, pinID);

					for(int iPin = 0; iPin < inputPinCount; iPin++)
					{
						pinID_t pinIDIndexed = getIndexedPinID(pinID, iPin);
						boost::shared_ptr<IConnectedVisionInputPin> inPin = this->getInputPin(*config, pinIDIndexed);

						try
						{
							Class_generic_status childStatus = inPin->notifyStop();
						}
						catch (NotFound_exception& e)
						{
							(void)e; // suppress unreferenced variable warning
							// set config and retry
							inPin->setConfig(resolvedConfigID, config->getSubConfigConnectionByInputPin(pinIDIndexed), pinIDIndexed);
							inPin->reset();
						}
						catch (std::runtime_error& ) {}
					}
				}
			}

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else if ( command == "notifyStop" )
		{
			runningSuccessorList.erase(senderID); // delete senderID from running successor list

			httpCode = this->getStatus(resolvedConfigID, response);
		}
		else
		{
			// not found
			httpCode = writeErrorLog(response, HTTP_Status_NOT_FOUND, "unknown control command");
		}
		
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		httpCode = writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}


	return httpCode;
}

int Module_BaseClass::processParameterCommand(const id_t configID, const std::string& command, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	int httpCode = HTTP_Status_OK;

	try
	{
		size_t posFoundCharacterEqual = command.find_first_of('=', 0);
		if (posFoundCharacterEqual != string::npos) // set command branch
		{
			std::string parameterPath = command.substr(0, posFoundCharacterEqual);
			std::string parameterValue = command.substr(posFoundCharacterEqual+1, string::npos);
			if (parameterValue.compare("initial") == 0)
			{
				resetParameterToInitialValue(resolvedConfigID, parameterPath, response);
			}
			else
			{
				setDynamicParameter(resolvedConfigID, parameterPath, parameterValue, response);
			}
		}
		else // get command branch
		{
			std::string parameterPath = command;
			getDynamicParameter(resolvedConfigID, parameterPath, response);
		}
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		httpCode = writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}

	return httpCode;
}

int Module_BaseClass::processParameterCommand(const id_t configID, const std::string& command, const std::string& payload, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( configID );

	// is module initialized?
	if ( !this->ready )
		return writeErrorLog(response, HTTP_Status_ERROR, "module not ready" );

	id_t resolvedConfigID;
	try 
	{
		resolvedConfigID = resolvePotentialAliasID(configID);
	}
	catch (std::runtime_error& e)
	{
		return writeErrorLog(response, HTTP_Status_ERROR, std::string("error in resolvePotentialAliasID() function: (") + e.what() + ")" );
	}

	int httpCode = HTTP_Status_OK;

	try
	{		
		std::string parameterPath = command;
		std::string parameterValue = payload;
		if (parameterValue.compare("initial") == 0)
		{
			resetParameterToInitialValue(resolvedConfigID, parameterPath, response);
		}
		else
		{
			setDynamicParameter(resolvedConfigID, parameterPath, parameterValue, response);
		}
	}
	catch (std::runtime_error& e)
	{
		// internal server error
		httpCode = writeErrorLog(response, HTTP_Status_ERROR, string(e.what()) );
	}

	return httpCode;
}


boost::shared_ptr<std::string> Module_BaseClass::getUpdatedParams(const id_t configID)
{
	boost::shared_ptr<std::string> params;
	try
	{
		auto oldCachedConfigParameters = this->mapCachedConfigParameters.at(configID);
		return boost::make_shared<std::string>(oldCachedConfigParameters);
	}
	catch (std::out_of_range)
	{
		// do nothing - and go to next commands
	}

	auto config = this->getConfigStore()->getByID(configID);
	params = config->get_params();
	this->mapCachedConfigParameters.insertUpdate(std::pair<std::string, std::string>(configID, *params));

	return(params);
}

void Module_BaseClass::getDefaultParametersRecursiveAsRapidjson(const rapidjson::Value &currentNodeInModuleDescription, rapidjson::Value &defaultParameterNode, rapidjson::Value::AllocatorType &allocator)
{
	for (auto it = currentNodeInModuleDescription.MemberBegin(); it != currentNodeInModuleDescription.MemberEnd(); it++)
	{
		if (it->value.IsObject())
		{
			if (it->value.HasMember("type"))
			{
				if (it->value["type"] == "object")
				{
					if (it->value.HasMember("properties"))
					{
						rapidjson::Value::StringRefType memberName(it->name.GetString());
						rapidjson::Value object(rapidjson::Value().SetObject(), allocator);						
						rapidjson::Value currentValue(it->value["properties"], allocator);
						getDefaultParametersRecursiveAsRapidjson(currentValue, object, allocator);
						defaultParameterNode.AddMember(memberName, object, allocator);
					}
					else
					{
						throw ConnectedVision::runtime_error(std::string("error: member \"properties\" expected but not found in json object! "));
					}
				}
				else if (it->value["type"] == "array")
				{
					rapidjson::Value::StringRefType memberName(it->name.GetString());
					if (it->value.HasMember("default")) // only if it has a default value (and thus is a non-required parameter)
					{
						if (it->value["default"].IsArray()) // check if the default value is an array (as expected)
						{
							rapidjson::Value defaultArray(it->value["default"], allocator);		
							defaultParameterNode.AddMember(memberName, defaultArray, allocator);
						}
						else
						{
							throw ConnectedVision::runtime_error(std::string("error: array expected in member \"default\" but not found! "));
						}
					}
				}
				else
				{
					if (it->value.HasMember("default"))
					{
						rapidjson::Value::StringRefType memberName(it->name.GetString());						
						rapidjson::Value currentValue(it->value["default"], allocator);
						defaultParameterNode.AddMember(memberName, currentValue, allocator);
					}
				}
			}
			else
			{
				throw ConnectedVision::runtime_error(std::string("error: type field missing in object " + std::string(it->name.GetString()) + "! "));
			}
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("error: object expected but not found " + std::string(it->name.GetString()) + " was not found in module description! "));
		}
	}
}

void Module_BaseClass::setDynamicParameter(const std::string& parameterPath, const rapidjson::Value &parameterValue, rapidjson::Document &documentParams)
{
	std::vector<std::string> parameterPathElements;
	boost::split(parameterPathElements, parameterPath, boost::is_any_of("/"));

	rapidjson::Value value(parameterValue, documentParams.GetAllocator());

	rapidjson::Value *pCurrentParameterNode = &documentParams;
	for (auto it = parameterPathElements.begin(); it != parameterPathElements.end(); ++it)
	{
		if (!pCurrentParameterNode->IsObject())
		{
			throw ConnectedVision::runtime_error(std::string("parse error of JSON object params: parameter node is no json object (trying to access parameter with name " + *it + " failed! "));
		}
		if (pCurrentParameterNode->HasMember(it->c_str()))
		{
			pCurrentParameterNode = &((*pCurrentParameterNode)[it->c_str()]);
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("parse error of JSON object params: parameter node with name " + *it + " was not found! "));
		}
	}

	Module_BaseClass::ParameterDescriptionNodeInfo parameterDescInfo = queryParameterDescriptionInfo(parameterPath);

	boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> pNodeCurrentInParameterDescTree = this->parameterDesc;
	for (auto it = parameterPathElements.begin(); it != parameterPathElements.end(); ++it)
	{
		if (pNodeCurrentInParameterDescTree->at(it->c_str()).pSubObject)
		{
			pNodeCurrentInParameterDescTree = pNodeCurrentInParameterDescTree->at(it->c_str()).pSubObject;
		}
		else if (pNodeCurrentInParameterDescTree->at(it->c_str()).pSubArray)
		{
			auto itCopy = it;
			itCopy++;
			if (itCopy != parameterPathElements.end())
			{
				throw ConnectedVision::runtime_error(std::string("illegal set operation - the parameter path specifying the target parameter seems to point to an element inside an array which is not allowed! "));
			}			
		}
	}

	if (parameterDescInfo.type == Module_BaseClass::ParameterValueType::Object)
	{
		if (!value.IsObject())
		{
			throw ConnectedVision::runtime_error(std::string("parameter is no json object!"));
		}
		if (!parameterDescInfo.dynamic)
		{
			throw ConnectedVision::runtime_error(std::string("illegal set operation - the targeted parameter object was not declared as dynamic! "));
		}

		checkRecursivelyRequiredParametersAndType(pNodeCurrentInParameterDescTree, parameterValue);
	}
	else if (parameterDescInfo.type == Module_BaseClass::ParameterValueType::Array)
	{
		if (!value.IsArray())
		{
			throw ConnectedVision::runtime_error(std::string("parameter is no json array!"));
		}
		if ( (!parameterDescInfo.dynamic) && (value.Size() != pCurrentParameterNode->Size()) )
		{
			throw ConnectedVision::runtime_error(std::string("illegal set operation - the array container was not declared as dynamic, but setting the desired json array parameter value would result in a change of the number of array elements! "));
		}
		if (!parameterDescInfo.dynamicItems)
		{
			throw ConnectedVision::runtime_error(std::string("illegal set operation - the targeted parameter array items were not declared as dynamic! "));
		}

		checkRecursivelyRequiredParametersAndType(pNodeCurrentInParameterDescTree->at(parameterPathElements.rbegin()->c_str()).pSubArray, parameterValue);
	}
	else
	{
		if (!parameterDescInfo.dynamic)
		{
			throw ConnectedVision::runtime_error(std::string("illegal set operation - the targeted parameter was not declared as dynamic! "));
		}

		// check if value type is supported in ConnectedVision
		checkValueType(value, parameterDescInfo.type);		
	}

	if (parameterDescInfo.type == ParameterValueType::Object)
	{
		checkRecursivelyIfParameterValueExistsInModuleDescription(pNodeCurrentInParameterDescTree, parameterValue);
	}

	*pCurrentParameterNode = value;
}

void Module_BaseClass::checkRecursivelyIfParameterValueExistsInModuleDescription(const boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> &parameterDescTreeNode, const rapidjson::Value &currentParameterNode)
{
	for (auto it = currentParameterNode.MemberBegin(); it != currentParameterNode.MemberEnd(); ++it)
	{
		std::string name = it->name.GetString();
		auto found = parameterDescTreeNode->find(name);
		if (found != parameterDescTreeNode->end())
		{
			if (found->second.type == ParameterValueType::Object)
			{
				checkRecursivelyIfParameterValueExistsInModuleDescription(found->second.pSubObject, it->value);
			}
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("illegal set operation - the parameter with name " + name + " is unknown! No such parameter was defined in parameter description in the module description! "));
		}
	}
}

void Module_BaseClass::checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(const boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> &parameterDescTreeNode, const rapidjson::Value &currentInitialParameterNode, const rapidjson::Value &currentParameterNode, bool moduleAndconfigSupportDynamicParameters)
{
	for (auto it = parameterDescTreeNode->cbegin(); it != parameterDescTreeNode->cend(); ++it)
	{
		std::string name = it->first;		

		if (!currentInitialParameterNode.HasMember(name.c_str())) // no parameter with this name in intialParams object
		{
			if (it->second.required == true) // if required - this implies a problem
			{
				throw ConnectedVision::runtime_error(std::string("initial (sub-)parameter " + name + " expected but missing! "));
			}
			else // otherwise ok, so just skip parameter
			{
				continue;
			}
		}

		if (!currentParameterNode.HasMember(name.c_str())) // no parameter with this name in params object
		{
			if (it->second.required == true) // if required - this implies a problem
			{
				throw ConnectedVision::runtime_error(std::string("(sub-)parameter " + name + " expected but missing! "));
			}
			else // otherwise ok, so just skip parameter
			{
				continue;
			}
		}

		const rapidjson::Value &initialParameterValue = currentInitialParameterNode[name.c_str()];
		const rapidjson::Value &parameterValue = currentParameterNode[name.c_str()];

		switch (it->second.type)
		{
		case ParameterValueType::Boolean:			
			if (initialParameterValue.GetBool() != parameterValue.GetBool())
			{
				if (it->second.dynamic == false)
				{
					throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)parameter " + name + " is different in initialParams and params object! "));
				}
				else if (moduleAndconfigSupportDynamicParameters == false)
				{
					throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: parameter " + name + " is different in initialParams and params object! "));
				}
			}
			break;
		case ParameterValueType::Integer64:
			if (initialParameterValue.GetInt64() != parameterValue.GetInt64())
			{
				if (it->second.dynamic == false)
				{
					throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)parameter " + name + " is different in initialParams and params object! "));
				}
				else if (moduleAndconfigSupportDynamicParameters == false)
				{
					throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: parameter " + name + " is different in initialParams and params object! "));
				}
			}
			break;
		case ParameterValueType::Number:
			if (initialParameterValue.GetDouble() != parameterValue.GetDouble())
			{
				if (it->second.dynamic == false)
				{
					throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)parameter " + name + " is different in initialParams and params object! "));
				}
				else if (moduleAndconfigSupportDynamicParameters == false)
				{
					throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: parameter " + name + " is different in initialParams and params object! "));
				}
			}
			break;
		case ParameterValueType::String:
			if (std::string(initialParameterValue.GetString()) != std::string(parameterValue.GetString()))
			{
				if (it->second.dynamic == false)
				{
					throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)parameter " + name + " is different in initialParams and params object! "));
				}
				else if (moduleAndconfigSupportDynamicParameters == false)
				{
					throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: parameter " + name + " is different in initialParams and params object! "));
				}
			}
			break;
		case ParameterValueType::Object:
			checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(it->second.pSubObject, initialParameterValue, parameterValue, moduleAndconfigSupportDynamicParameters);
			break;
		case ParameterValueType::Array:
			if (!initialParameterValue.IsArray())
			{
				throw ConnectedVision::runtime_error(std::string("initial non-dynamic (sub-)parameter " + name + " was expected to be an array but it was of different type! "));
			}

			if (!parameterValue.IsArray())
			{
				throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)parameter " + name + " was expected to be an array but it was of different type! "));
			}			
			
			if (moduleAndconfigSupportDynamicParameters == false)
			{
				if (initialParameterValue.Size() != parameterValue.Size())
				{
					throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: number of array items is different in initialParams and params object! "));
				}
			}

			if (it->second.dynamic == false)
			{
				if (initialParameterValue.Size() != parameterValue.Size())
				{
					throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)parameter " + name + " was expected to be an constant size array but the provided arrays in params and initialParams differ in size! "));
				}

				for (rapidjson::SizeType i = 0; i < initialParameterValue.Size(); ++i)			
				{
					if (initialParameterValue.Size() != parameterValue.Size())
					{
						throw ConnectedVision::runtime_error(std::string("number of array items is different in initialParams and params object! "));
					}

					const rapidjson::Value &arrayItemInitialParams = initialParameterValue[i];
					const rapidjson::Value &arrayItemParams = parameterValue[i];

					std::string tmpstr1 = jsonToStr(arrayItemInitialParams);
					std::string tmpstr2 = jsonToStr(arrayItemParams);

					checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(it->second.pSubArray, arrayItemInitialParams, arrayItemParams, moduleAndconfigSupportDynamicParameters);
				}
			}
			else
			{
				if ((initialParameterValue.Size() != parameterValue.Size()) && (moduleAndconfigSupportDynamicParameters == false))
				{
					throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: parameter " + name + " is different in initialParams and params object! "));
				}
			}

			break;
		}		
	}
}

void Module_BaseClass::checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(const boost::shared_ptr<ParameterDescTreeNode> parameterDescTreeNode, const rapidjson::Value &currentInitialParameterNode, const rapidjson::Value &currentParameterNode, bool moduleAndconfigSupportDynamicParameters)
{
	const rapidjson::Value &initialParameterValue = currentInitialParameterNode;
	const rapidjson::Value &parameterValue = currentParameterNode;

	if (parameterDescTreeNode->type == ParameterValueType::Object) // object handling
	{
		checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(parameterDescTreeNode->pSubObject, currentInitialParameterNode, currentParameterNode, moduleAndconfigSupportDynamicParameters);
	}
	else if (parameterDescTreeNode->type == ParameterValueType::Array) // array handling
	{
		if (moduleAndconfigSupportDynamicParameters == false)
		{
			if (initialParameterValue.Size() != parameterValue.Size())
			{
				throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: number of array items is different in initialParams and params object! "));
			}
		}

		if (parameterDescTreeNode->dynamic == false)
		{
			if (initialParameterValue.Size() != parameterValue.Size())
			{
				throw ConnectedVision::runtime_error(std::string("non-dynamic (sub-)array-parameter was expected to be an constant size array but the provided arrays in params and initialParams differ in size! "));
			}
		}
		else
		{
			if ((initialParameterValue.Size() != parameterValue.Size()) && (moduleAndconfigSupportDynamicParameters == false))
			{
				throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: a sub-array-parameter is different in initialParams and params object! "));
			}
		}
		for (rapidjson::SizeType i = 0; i < initialParameterValue.Size(); ++i)			
		{
			const rapidjson::Value &arrayItemInitialParams = initialParameterValue[i];
			const rapidjson::Value &arrayItemParams = parameterValue[i];
			checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(parameterDescTreeNode->pSubArray, arrayItemInitialParams, arrayItemParams, moduleAndconfigSupportDynamicParameters);
		}
	}
	else if (parameterDescTreeNode->type == ParameterValueType::Integer64)
	{
		if ((!initialParameterValue.IsInt64()) || (!parameterValue.IsInt64()))
		{
			throw ConnectedVision::runtime_error(std::string("array element of type int64 expected but it was of different type! "));
		}

		if (initialParameterValue.GetInt64() != parameterValue.GetInt64())
		{
			if (parameterDescTreeNode->dynamic == false)
			{
				throw ConnectedVision::runtime_error(std::string("non-dynamic array element of integer type of a array-parameter differs between initialParams and params object! "));
			}
			if (moduleAndconfigSupportDynamicParameters == false)
			{
				throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: a parameter is different in initialParams and params object! "));
			}
		}
	}
	else if (parameterDescTreeNode->type == ParameterValueType::Number)
	{
		if ((!initialParameterValue.IsNumber()) || (!parameterValue.IsNumber()))
		{
			throw ConnectedVision::runtime_error(std::string("array element of type number expected but it was of different type! "));
		}

		if (initialParameterValue.GetDouble() != parameterValue.GetDouble())
		{
			if (parameterDescTreeNode->dynamic == false)
			{
				throw ConnectedVision::runtime_error(std::string("non-dynamic array element of number type of a array-parameter differs between initialParams and params object! "));
			}
			if (moduleAndconfigSupportDynamicParameters == false)
			{
				throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: a parameter is different in initialParams and params object! "));
			}			
		}
	}
	else if (parameterDescTreeNode->type == ParameterValueType::String)
	{
		if ((!initialParameterValue.IsString()) || (!parameterValue.IsString()))
		{
			throw ConnectedVision::runtime_error(std::string("array element of type string expected but it was of different type! "));
		}

		if (std::string(initialParameterValue.GetString()) != std::string(parameterValue.GetString()))
		{
			if (parameterDescTreeNode->dynamic == false)
			{
				throw ConnectedVision::runtime_error(std::string("non-dynamic array element of string type of a array-parameter differs between initialParams and params object! "));
			}
			if (moduleAndconfigSupportDynamicParameters == false)
			{
				throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: a parameter is different in initialParams and params object! "));
			}			
		}
	}
	else if (parameterDescTreeNode->type == ParameterValueType::Boolean)
	{
		if ((!initialParameterValue.IsBool()) || (!parameterValue.IsBool()))
		{
			throw ConnectedVision::runtime_error(std::string("array element of type boolean expected but it was of different type! "));
		}

		if (initialParameterValue.GetBool() != parameterValue.GetBool())
		{
			if (parameterDescTreeNode->dynamic == false)
			{
				throw ConnectedVision::runtime_error(std::string("non-dynamic array element of boolean type of a array-parameter differs between initialParams and params object! "));
			}
			if (moduleAndconfigSupportDynamicParameters == false)
			{
				throw ConnectedVision::runtime_error(std::string("module or this specific config does not support dynamic parameters: a parameter is different in initialParams and params object! "));
			}			
		}
	}
	else if (parameterDescTreeNode->type == ParameterValueType::Unsupported)
	{
		throw ConnectedVision::runtime_error(std::string("(sub-)parameter is of unknown type! "));
	}
}

void Module_BaseClass::setDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, const std::string& parameterValue, ConnectedVisionResponse &response)
{		
	// get config
	boost::shared_ptr< const Class_generic_config > config = configStore->getByID(resolvedConfigID);
	if (!config)
	{
		throw ConnectedVision::runtime_error(std::string("error: config with configID " + resolvedConfigID + " was not found! "));	
	}

	// check if module supports dynamic parameters
	bool moduleSupportsDynamicParameters = false;
	auto itModuleFeatures = this->moduleDescriptionJSON.FindMember("moduleFeatures");
	if (itModuleFeatures != this->moduleDescriptionJSON.MemberEnd())
	{
		auto itSupports = itModuleFeatures->value.FindMember("supportsDynamicParameters");
		if (itSupports != this->moduleDescriptionJSON.MemberEnd())
		{
			moduleSupportsDynamicParameters = itSupports->value.GetBool();
		}
	}   
	if (!moduleSupportsDynamicParameters)
	{
		throw ConnectedVision::runtime_error(std::string("error: illegal set parameter operation - module does not support dynamic parameters! "));
	}

	// check if dynamic parameters were activated for this config
	if (!config->getconst_configFeatures()->getconst_allowDynamicParameters())
	{
		throw ConnectedVision::runtime_error(std::string("error: illegal set parameter operation - dynamic parameters are not allowed for this config (the member \"allowDynamicParamaters\" in the config description object \"configFeatures\" was either not set or set to false)! "));
	}

	// parse params of config (the parsed object will be updated with the parameter of interest)
	rapidjson::Document documentParams;
	if (documentParams.Parse<0>(config->getconst_params()->c_str()).HasParseError())
	{
		throw ConnectedVision::runtime_error(std::string("parse error of JSON object params! "));
	}

	// merge params object with default params
	rapidjson::Value mergedParameters;
	extendJsonObject(defaultParameters, documentParams, mergedParameters, documentParams.GetAllocator());
	documentParams.CopyFrom(mergedParameters, documentParams.GetAllocator());

	// convert function parameter parameterValue from string to rapidjson::Document
	rapidjson::Document valueDocument;
	if (valueDocument.Parse<0>( parameterValue.c_str() ).HasParseError())
	{
		throw ConnectedVision::runtime_error( string("ERROR: JSON parse error when parsing target parameter value: ") + rapidjson::GetParseError_En(valueDocument.GetParseError()) + " @ " + intToStr(valueDocument.GetErrorOffset()) );
	}

	rapidjson::Value currentParameterValue(mergedParameters, documentParams.GetAllocator());

	if (parameterPath == "") // if global parameter object (with global the "params" object inside the module description is meant) was set by command "parameter/={...}"
	{
		if (!this->moduleDescriptionJSON.HasMember("params"))
		{
			throw ConnectedVision::runtime_error(std::string("module description is of invalid format! \"params\" member was missing! "));
		}

		// params object in module description must have member "dynamic" and it has to be true
		if ((this->moduleDescriptionJSON["params"].HasMember("dynamic")) && (this->moduleDescriptionJSON["params"]["dynamic"].GetBool()))
		{
			// try to set all parameters inside global params object
			try
			{
				// for every sub-parameter inside the module description
				for (auto it = parameterDesc->cbegin(); it != parameterDesc->cend(); ++it)
				{	
					Module_BaseClass::ParameterDescriptionNodeInfo parameterDescInfo = queryParameterDescriptionInfo(it->first);
					if (!valueDocument.HasMember(it->first.c_str()))
					{						
						if (parameterDescInfo.required)
						{
							throw ConnectedVision::runtime_error(std::string("parse error of JSON object params: parameter node with name " + it->first + " was not found! "));
						}
						
						if (!parameterDescInfo.dynamic)
						{
							// in fact one should never get in here if dynamic parameter sanity of module description was checked correctly in function initModuleDescription
							throw ConnectedVision::runtime_error(std::string("parse error of JSON object params: parameter node with name " + it->first + " was expected to be dynamic but was not declared as such! "));
						}

						if ((parameterDescInfo.type == Module_BaseClass::ParameterValueType::Array) && (!parameterDescInfo.dynamicItems))
						{
							// in fact one should never get in here if dynamic parameter sanity of module description was checked correctly in function initModuleDescription
							throw ConnectedVision::runtime_error(std::string("parse error of JSON object params: parameter node with name " + it->first + " is dynamic array container but has array items that were not declared as dynamic! "));
						}
					}
					else
					{
						// set the current sub-parameter					
						setDynamicParameter(it->first, valueDocument[it->first.c_str()], documentParams);
					}
				}
			}
			catch (std::runtime_error& e)
			{
				throw ConnectedVision::runtime_error(std::string("an error occurred when trying to set global params object: ") + std::string(e.what()) + std::string(" - ! "));
			}
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("error: global params object was not declared as dynamic! "));
		}
	}
	else // if specific parameter was set by command "parameter/xyz={...}"
	{
		// set the parameter of interest
		setDynamicParameter(parameterPath, valueDocument, documentParams);
	}

	// update config
	ConnectedVision::shared_ptr< Class_generic_config > updatedConfig;
	updatedConfig = config->copy();
	updatedConfig->set_params(jsonToStr(documentParams));

	// store the updated params in the map for cached config parameters	
	this->mapCachedConfigParameters.insertUpdate(std::pair<std::string, std::string>(resolvedConfigID, *updatedConfig->get_params()));

	// overwrite existing config in store
	this->configStore->save_move(updatedConfig);

	// return JSON string (by invocing function getDynamicParameter)
	getDynamicParameter(resolvedConfigID, parameterPath, response);
}

void Module_BaseClass::getDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, ConnectedVisionResponse &response)
{
	std::string parameterAsString;

	std::vector<std::string> parameterPathElements;
	boost::split(parameterPathElements, parameterPath, boost::is_any_of("/"));
	// if last character of parameterPath is "/", delete the last element of parameterPathElements since it is empty
	if (parameterPathElements.rbegin()->compare("") == 0)
	{
		parameterPathElements.pop_back();
	}

	boost::shared_ptr< const Class_generic_config > config = configStore->getByID(resolvedConfigID);	
	if (!config)
	{
		throw ConnectedVision::runtime_error(std::string("error: config with configID " + resolvedConfigID + " was not found! "));	
	}

	boost::shared_ptr<const std::string> params = config->getconst_params();

	// -------------------------- build rapidjson params object with default values set for optional parameters --------------------------	
	rapidjson::Document documentParams;
	if (documentParams.Parse<0>(params->c_str()).HasParseError())
	{
		throw ConnectedVision::runtime_error(std::string("parse error of JSON object params! "));
	}

	rapidjson::Value currentParameterValue(documentParams, documentParams.GetAllocator());

	// merge params object with default params
	rapidjson::Value mergedParameters;
	extendJsonObject(defaultParameters, currentParameterValue, mergedParameters, documentParams.GetAllocator());

	// navigate to queried parameter (rapidjson sub-object)
	for (auto it = parameterPathElements.begin(); it != parameterPathElements.end(); ++it)
	{
		if (!mergedParameters.IsObject())
		{
			throw ConnectedVision::runtime_error(std::string("error when merging params: parameter node is no json object (trying to access parameter with name " + *it + " failed! "));
		}
		if (mergedParameters.HasMember(it->c_str()))
		{
			mergedParameters = mergedParameters[it->c_str()];
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("error: parameter with name " + parameterPath + " does not exist! "));		
		}
	}

	// convert rapidjson object to JSON string (pretty formatted)
	rapidjson::StringBuffer s;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	mergedParameters.Accept(writer);

	// return JSON string
	response.setContentType("application/json");
	response.setContent(s.GetString());
}

void Module_BaseClass::resetParameterToInitialValue(const id_t resolvedConfigID, const std::string& parameterPath, ConnectedVisionResponse &response)
{
	std::vector<std::string> parameterPathElements;
	boost::split(parameterPathElements, parameterPath, boost::is_any_of("/"));
	// if last character of parameterPath is "/", delete the last element of parameterPathElements since it is empty
	if (parameterPathElements.rbegin()->compare("") == 0)
	{
		parameterPathElements.pop_back();
	}

	boost::shared_ptr< const Class_generic_config > config = configStore->getByID(resolvedConfigID);	
	if (!config)
	{
		throw ConnectedVision::runtime_error(std::string("error: config with configID " + resolvedConfigID + " was not found! "));	
	}
	
	boost::shared_ptr<const std::string> initialParams = config->getconst_initialParams();
	boost::shared_ptr<const std::string> params = config->getconst_params();

	// -------------------------- get rapidjson initialParams object --------------------------	
	rapidjson::Document documentInitialParams;
	if (documentInitialParams.Parse<0>(initialParams->c_str()).HasParseError())
	{
		throw ConnectedVision::runtime_error(std::string("parse error of JSON object initialParams! "));
	}

	// merge initialParams object with default params
	rapidjson::Value mergedInitialParameters;
	extendJsonObject(defaultParameters, documentInitialParams, mergedInitialParameters, documentInitialParams.GetAllocator());
	documentInitialParams.CopyFrom(mergedInitialParameters, documentInitialParams.GetAllocator());

	// -------------------------- get rapidjson params object --------------------------	
	rapidjson::Document documentParams;
	if (documentParams.Parse<0>(params->c_str()).HasParseError())
	{
		throw ConnectedVision::runtime_error(std::string("parse error of JSON object params! "));
	}

	// merge params object with default params
	rapidjson::Value mergedParameters;
	extendJsonObject(defaultParameters, documentParams, mergedParameters, documentParams.GetAllocator());
	documentParams.CopyFrom(mergedParameters, documentParams.GetAllocator());
	
	rapidjson::Value *pCurrentParameterNode = &documentParams;
	rapidjson::Value *pCurrentInitialParameterNode = &documentInitialParams;

	// navigate to queried parameter (rapidjson sub-object)
	for (auto it = parameterPathElements.begin(); it != parameterPathElements.end(); ++it)
	{
		if (!pCurrentInitialParameterNode->IsObject())
		{
			throw ConnectedVision::runtime_error(std::string("error when retrieving initialParams: parameter node is no json object (trying to access parameter with name " + *it + " failed! "));
		}
		if (pCurrentInitialParameterNode->HasMember(it->c_str()))
		{
			pCurrentInitialParameterNode = &((*pCurrentInitialParameterNode)[it->c_str()]);
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("error: parameter in initialParams with name " + parameterPath + " does not exist! "));		
		}

		if (!pCurrentParameterNode->IsObject())
		{
			throw ConnectedVision::runtime_error(std::string("error when retrieving params: parameter node is no json object (trying to access parameter with name " + *it + " failed! "));
		}
		if (pCurrentParameterNode->HasMember(it->c_str()))
		{
			pCurrentParameterNode = &((*pCurrentParameterNode)[it->c_str()]);
		}
		else
		{
			throw ConnectedVision::runtime_error(std::string("error: parameter in params with name " + parameterPath + " does not exist! "));		
		}
	}
		
	rapidjson::Value newValue(*pCurrentInitialParameterNode, documentParams.GetAllocator());
	*pCurrentParameterNode = newValue;

	// update config
	ConnectedVision::shared_ptr< Class_generic_config > updatedConfig;
	updatedConfig = config->copy();
	updatedConfig->set_params(jsonToStr(documentParams));

	// store the updated params in the map for cached config parameters	
	this->mapCachedConfigParameters.insertUpdate(std::pair<std::string, std::string>(resolvedConfigID, *updatedConfig->get_params()));

	// overwrite existing config in store
	this->configStore->save_move(updatedConfig);

	// return JSON string (by invocing function getDynamicParameter)
	getDynamicParameter(resolvedConfigID, parameterPath, response);
}

/**
 * start processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] workerController	worker controller of the config to be started
 */
void Module_BaseClass::start(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController)
{
	LOG_SCOPE_CONFIG( workerController->getConfigID() );
	
	workerController->start();
}

/**
 * stop processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void Module_BaseClass::stop(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController)
{
	LOG_SCOPE_CONFIG( workerController->getConfigID() );
	
	workerController->stop();

	// delete the cached config parameters
	this->mapCachedConfigParameters.erase( workerController->getConfigID() );
}

/**
 * revocer of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void Module_BaseClass::recover(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController)
{
	LOG_SCOPE_CONFIG( workerController->getConfigID() );
	
	workerController->recover();
}

/**
 * reset processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void Module_BaseClass::reset(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController)
{
	LOG_SCOPE_CONFIG( workerController->getConfigID() );

	workerController->reset();
}


void Module_BaseClass::registerWorkerInstance(const id_t configID, ConnectedVision::Module::IWorkerControllerCallbacks *workerController)
{
	ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> ptr;
	ptr.reset(dynamic_cast<ConnectedVision::Module::WorkerController*>(workerController));
	auto pair = std::pair<id_t, ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController>>(configID, ptr);
	this->mapWorkerControllers.insert(pair);
	// insert() may fail intentionally in case of a racing-condition and may throw out_of_range exception which is essential
	// for the worker controller constructor.
}
void Module_BaseClass::unregisterWorkerInstance(const id_t configID, ConnectedVision::Module::IWorkerControllerCallbacks *workerController)
{
	try
	{
		auto ptr = this->mapWorkerControllers.at(configID);
		if ( ptr.get() == workerController )
		{
			this->mapWorkerControllers.erase(configID, ptr);
		}
	}
	catch (...)
	{
		// ignore
	}
}



/**
 * create error response and write it to log
 *
 * @param [out] response	ConnectedVision response
 * @param [in]  status		HTTP error code
 * @param [in]  error		error message
 *
 * @return HTTP error code
 */
int Module_BaseClass::writeErrorLog(ConnectedVisionResponse &response, int status, std::string error)
{
	LOG_ERROR( error );

	return writeError(response, status, this->moduleID, error);
}

/**
 * get log writer
 *
 * @return log writer
 */
boost::shared_ptr<Logging::ILogWriter> Module_BaseClass::log() const
{
	if ( this->env ) 
	{
		return this->env->log(); 
	}
	else 
	{
		boost::shared_ptr<Logging::ILogWriter> log( new Logging::LogWriterNULL() );
		return log;
	}
}
