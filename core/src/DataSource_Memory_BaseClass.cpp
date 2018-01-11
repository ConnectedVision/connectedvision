/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DataSource_Memory_BaseClass_impl
#define DataSource_Memory_BaseClass_impl

#include "DataSource_Memory_BaseClass.h"

#include <IConnectedVisionModule.h>
#include <IModuleEnvironment.h>
#include <IHTTPAbstraction.h>

#include <exception>

namespace ConnectedVision {

/**
 * Constructor
 */
template <class TDataObject>
DataSource_Memory_BaseClass<TDataObject>::DataSource_Memory_BaseClass()
{
	this->initFlag = false;
}


/**
 * Desctuctor
 */
template <class TDataObject>
DataSource_Memory_BaseClass<TDataObject>::~DataSource_Memory_BaseClass()
{

}

/**
 * initialize data source
 */
template <class TDataObject>
void DataSource_Memory_BaseClass<TDataObject>::init(const IModuleEnvironment *pEnv, const id_t &moduleID, const id_t &configID, const pinID_t &outputPinID)
{
	// store params for later usage
	this->pEnv = pEnv;
	this->moduleID = moduleID;
	this->configID = configID;
	this->outputPinID = outputPinID;

	// get current output pin
	boost::shared_ptr<ConnectedVision::Module::IModule> pModule = pEnv->getModule(moduleID);
	if (pModule != NULL)
	{
		this->pOutputPin = pModule->getOutputPin(configID, outputPinID);
	}
	else
	{
		this->pOutputPin.reset();
	}

	this->initFlag = true;
}

template <class TDataObject>
boost::shared_ptr<IConnectedVisionOutputPin> DataSource_Memory_BaseClass<TDataObject>::getOutputPin()
{
	// do we already have a valid output pin?
	if ( this->pOutputPin )
		return this->pOutputPin;
	
	// try to re-init output pin
	this->init(this->pEnv, this->moduleID, this->configID, this->outputPinID);

	// re-check output pin
	if ( !this->pOutputPin )
		throw ConnectedVision::runtime_error("DataSource_Memory_BaseClass<TDataObject>::getOutputPin(): pOutputPin was null");

	return this->pOutputPin;
}

/**
 * get a single object by ID
 *
 * @param id			object ID
 */
template <class TDataObject>
boost::shared_ptr<TDataObject> DataSource_Memory_BaseClass<TDataObject>::getByID(const id_t id)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getByID(id, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getByID(): error code: " + intToStr(httpCode) );
	
	std::vector< boost::shared_ptr<TDataObject> > objs = this->responseToData( response );
	if ( objs.size() == 1 )
		return objs[0];
	else if ( objs.size() == 0 )
		return boost::shared_ptr<TDataObject>();
	else
		throw ConnectedVision::runtime_error("getByID(): multiple results found (id: " + IDToStr(id) + ")");
}


/**
 * get a single object by index
 *
 * @param index			object index
 */
template <class TDataObject>
boost::shared_ptr<TDataObject> DataSource_Memory_BaseClass<TDataObject>::getByIndex(const int64_t index)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getByIndex(index, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getByIndex(): error code: " + intToStr(httpCode) );
	
	std::vector< boost::shared_ptr<TDataObject> > objs = this->responseToData( response );
	if ( objs.size() == 1 )
		return objs[0];
	else if ( objs.size() == 0 )
		return boost::shared_ptr<TDataObject>();
	else
		throw ConnectedVision::runtime_error("getByIndex(): multiple results found (index: " + intToStr(index) + ")");
}


/**
 * get multiple objects by index range
 *
 * @param start			index of first object
 * @param end			index of last object
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_Memory_BaseClass<TDataObject>::getByIndexRange(const int64_t start, const int64_t end)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getByIndexRange(start, end, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getByIndexRange(): error code: " + intToStr(httpCode) );
	
	return this->responseToData( response );
}


/**
 * get multiple objects by timestamp
 *
 * @param timestamp		timestamp
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_Memory_BaseClass<TDataObject>::getByTimestamp(const timestamp_t timestamp)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getByTimestamp(timestamp, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getByTimestamp(): error code: " + intToStr(httpCode) );
	
	return this->responseToData( response );
}


/**
 * get multiple objects at previous timestamp
 *
 * @param timestamp		timestamp
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_Memory_BaseClass<TDataObject>::getBeforeTimestamp(const timestamp_t timestamp)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getBeforeTimestamp(timestamp, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getBeforeTimestamp(): error code: " + intToStr(httpCode) );
	
	return this->responseToData( response );
}

/**
 * get multiple objects at next timestamp
 *
 * @param timestamp		timestamp
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_Memory_BaseClass<TDataObject>::getAfterTimestamp(const timestamp_t timestamp)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getAfterTimestamp(timestamp, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getAfterTimestamp(): error code: " + intToStr(httpCode) );
	
	return this->responseToData( response );
}

/**
 * get multiple objects by time range
 *
 * @param start			start of search time span
 * @param end			end of search time span
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_Memory_BaseClass<TDataObject>::getAllInTimespan(const timestamp_t start, const timestamp_t end)
{
	ConnectedVisionResponse response;
	auto pOutputPinScope = this->getOutputPin();	// make local copy of OutputPin shared_pointer to avoid mutexes

	int httpCode = pOutputPinScope->getAllInTimespan(start, end, response);
	if ( httpCode != HTTP::HTTP_Status_OK )
		throw ConnectedVision::runtime_error( "getAllInTimespan(): error code: " + intToStr(httpCode) );
	
	return this->responseToData( response );
}

/**
	* map response data to data objects
	*
	* @param response response as ConnectedVisionResponse
	*
	* @return vector of data objects
	*/
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_Memory_BaseClass<TDataObject>::responseToData(ConnectedVisionResponse &response)
{
	std::vector< boost::shared_ptr<TDataObject> > objs;

	if (response.contentType == "application/json")
	{
		rapidjson::Document json;
		if (json.Parse<0>( response.getContentConst().c_str() ).HasParseError() )
		{
			//std::string error = "parse error of JSON Object: " + response.getContentConst() + std::string("(") + rapidjson::GetParseError_En(json.GetParseError()) + std::string(" at ") + ConnectedVision::intToStr( json.GetErrorOffset()) + std::string(")");
			std::string error = rapidjson::GetParseError_En(json.GetParseError());
			throw ConnectedVision::runtime_error( error );
		}

		if ( json.IsArray() )
		{
			for ( rapidjson::SizeType i = 0; i < json.Size(); i++ )
			{
				boost::shared_ptr<TDataObject> obj( new TDataObject );
				obj->parseJson( json[i] );
				objs.push_back( obj );
			}
		}
		else if ( json.IsObject() )
		{
			boost::shared_ptr<TDataObject> obj( new TDataObject );
			obj->parseJson( json );
			objs.push_back( obj );
		}
		else
		{
			throw ConnectedVision::runtime_error( "no valid JSON: " + response.getContentConst());
		}
	}
	else
	{
		boost::shared_ptr<TDataObject> obj( new TDataObject );
		obj->parseJson( response.getContentConst() );									// TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		objs.push_back( obj );
	}

	return objs;
}	

} // namespace ConnectedVision

#endif // DataSource_Memory_BaseClass_impl