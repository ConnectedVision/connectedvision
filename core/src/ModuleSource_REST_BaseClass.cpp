/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** ModuleSource_REST_BaseClass.cpp
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#include <sstream>
#include <exception>

#include "ModuleSource_REST_BaseClass.h"
//#include "ConnectedVisionInputPin.h"
#include "HTTP/HTTPXClient.h"

using namespace ConnectedVision;

/**
 * Constructor
 */
ModuleSource_REST_BaseClass::ModuleSource_REST_BaseClass()
{
}


/**
 * Desctuctor
 */
ModuleSource_REST_BaseClass::~ModuleSource_REST_BaseClass()
{

}


/**
 * initialize data source
 *
 * The data source has to be initialized for every (re-)connection to an output pin of another module.
 *
 * @param moduleURI		URI of connected (source) module - The module connected to the input pin of the current module.
 * @param configID		configID of chain entry - The config corresponding to the source module.
 */
void ModuleSource_REST_BaseClass::init(const std::string &moduleURI, const id_t &configID)
{
	this->moduleURI = moduleURI;

	// make sure that url ends with '/'
	if ( this->moduleURI.at( this->moduleURI.length()-1 ) != '/' )
		this->moduleURI += "/";

	this->configID = configID;
}

boost::shared_ptr<Class_generic_status> ModuleSource_REST_BaseClass::getStatus()
{
	boost::shared_ptr<Class_generic_status> status(new Class_generic_status());
	status->clear();
	
	std::string uri = moduleURI + configID + "/status";

	ConnectedVision::HTTP::HTTPClientRequest request;
	request.setUri(uri);
	request.setMethod(ConnectedVision::HTTP::HTTP_Method_GET);
	
	ConnectedVision::HTTP::HTTPResponse response;

	HTTP::HTTPXClient::performHttpxRequest(request, response);

	//// process answer
	
	ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
	if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
	{
		throw ::ConnectedVision::runtime_error( response.content.getContentConst() );
	}

	status->parseJson( response.content.getContentConst() );

	return status;
}

boost::shared_ptr<Class_generic_config> ModuleSource_REST_BaseClass::getConfig()
{
	boost::shared_ptr<Class_generic_config> config(new Class_generic_config());
	config->clear();
	
	std::string uri = moduleURI + configID + "/config";

	ConnectedVision::HTTP::HTTPClientRequest request;
	request.setUri(uri);
	request.setMethod(ConnectedVision::HTTP::HTTP_Method_GET);
	
	ConnectedVision::HTTP::HTTPResponse response;

	HTTP::HTTPXClient::performHttpxRequest(request, response);

	//// process answer
	
	ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
	if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
	{
		throw ::ConnectedVision::runtime_error( response.content.getContentConst() );
	}

	config->parseJson( response.content.getContentConst() );

	return(config);
}
