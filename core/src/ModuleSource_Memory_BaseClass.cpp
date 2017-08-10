/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** ModuleSource_Memory_BaseClass.cpp
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#include "ModuleSource_Memory_BaseClass.h"

#include <IModuleEnvironment.h>
#include "HTTP/HTTPXClient.h"

namespace ConnectedVision {

/**
 * Constructor
 */
ModuleSource_Memory_BaseClass::ModuleSource_Memory_BaseClass()
{
}


/**
 * Desctuctor
 */
ModuleSource_Memory_BaseClass::~ModuleSource_Memory_BaseClass()
{

}

/**
 * initialize data source
 */
void ModuleSource_Memory_BaseClass::init(const IModuleEnvironment *pEnv, const id_t &moduleID, const id_t &configID)
{
	pModule = pEnv->getModule(moduleID);	

	if (pModule != NULL) // if module is present in module dispatcher (will be NULL if module runs on different host)
	{
		this->moduleID = moduleID;
		this->configID = configID;
	}
}

boost::shared_ptr<Class_generic_status> ModuleSource_Memory_BaseClass::getStatus()
{
	ConnectedVisionResponse response;

	if (pModule == NULL)
	{
		throw ConnectedVision::runtime_error("getStatus(): pModule is null");
	}

	pModule->getStatus(configID, response);

	boost::shared_ptr<Class_generic_status> status = responseToData<Class_generic_status>(response);

	return(status);
}


boost::shared_ptr<Class_generic_config> ModuleSource_Memory_BaseClass::getConfig()
{
	ConnectedVisionResponse response;

	if (pModule == NULL)
	{
		throw ConnectedVision::runtime_error("getStatus(): pModule is null");
	}

	pModule->getConfig(configID, response);

	boost::shared_ptr<Class_generic_config> config = responseToData<Class_generic_config>(response);

	return(config);
}



/**
 * map response data to data objects
 *
 * @param responseStr	response as ConnectedVisionResponse
 *
 * @return vector of data objects
 */
template <class T>
boost::shared_ptr<T> ModuleSource_Memory_BaseClass::responseToData(ConnectedVisionResponse &response)
{
	boost::shared_ptr<T> obj(new T());

	if (response.contentType == "application/json")
	{
		rapidjson::Document json;
		if (json.Parse<0>( response.getContentConst().c_str() ).HasParseError() )
		{
			std::string error = "error in ModuleSource_Memory_BaseClass::responseToData(): parse error of JSON Object: " + response.getContentConst() + "(" + rapidjson::GetParseError_En(json.GetParseError()) + " at " + intToStr( json.GetErrorOffset() );
			throw ConnectedVision::runtime_error( error );
		}
		else if ( json.IsObject() )
		{
			obj->parseJson( json );
		}
		else
		{
			throw ConnectedVision::runtime_error( "error in ModuleSource_Memory_BaseClass::responseToData(): no valid JSON: " + response.getContentConst());
		}
	}
	else
	{
		throw ConnectedVision::runtime_error( "error in ModuleSource_Memory_BaseClass::responseToData(): no JSON format: " + response.getContentConst());
	}

	return obj;
}

} // namespace ConnectedVision