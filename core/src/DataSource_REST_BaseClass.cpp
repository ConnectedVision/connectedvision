/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DataSource_REST_BaseClass_impl
#define DataSource_REST_BaseClass_impl

#include <sstream>
#include <exception>
#include <rapidjson/error/en.h>

#include "DataSource_REST_BaseClass.h"
#include "HTTP/HTTPXClient.h"

namespace ConnectedVision {

/**
 * Constructor
 */
template <class TDataObject>
DataSource_REST_BaseClass<TDataObject>::DataSource_REST_BaseClass()
{
}


/**
 * Desctuctor
 */
template <class TDataObject>
DataSource_REST_BaseClass<TDataObject>::~DataSource_REST_BaseClass()
{

}

/**
 * initialize data source
 *
 * The data source has to be initialized for every (re-)connection to an output pin of another module.
 *
 * @param moduleURI		URI of connected (source) module - The module connected to the input pin of the current module.
 * @param configID		configID of chain entry - The config corresponding to the source module.
 * @param outputPinID	pin ID of connected output Pin
 */
template <class TDataObject>
void DataSource_REST_BaseClass<TDataObject>::init(const std::string &moduleURI,	const id_t &configID, const pinID_t &outputPinID)
{
	this->moduleURI = moduleURI;

	// make sure that url ends with '/'
	if ( this->moduleURI.at( this->moduleURI.length()-1 ) != '/' )
		this->moduleURI += "/";

	this->configID = configID;
	this->outputPinID = outputPinID;
}

/**
 * get multiple objects from RESTfull service
 *
 * @param restmoduleURI	full REST moduleURI of request
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_REST_BaseClass<TDataObject>::requestObjs(const std::string restmoduleURI ) const
{
	std::vector< boost::shared_ptr<TDataObject> > objs;

	ConnectedVision::HTTP::HTTPClientRequest request;
	request.setUri(restmoduleURI);
	request.setMethod(ConnectedVision::HTTP::HTTP_Method_GET);
	
	ConnectedVision::HTTP::HTTPResponse response;

	ConnectedVision::HTTP::HTTPXClient::performHttpxRequest(request, response);

	//// process answer
	std::string body = response.content.getContentConst();

	ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
	if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
	{
		throw ConnectedVision::runtime_error( body );
	}

	if ( code == ConnectedVision::HTTP::HTTP_Status_OK )
	{
		std::string contentType = response.content.getContentTypeConst();
		if (contentType == "application/json")
		{
			rapidjson::Document json;
			if (json.Parse<0>( body.c_str() ).HasParseError() )
			{
				std::string error = "parse error of JSON Object: " + body + "(" + rapidjson::GetParseError_En(json.GetParseError()) + " at " + intToStr( json.GetErrorOffset() );
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
				throw ConnectedVision::runtime_error( "no valid JSON: " + body);
			}
		}
		else
		{
			boost::shared_ptr<TDataObject> obj( new TDataObject );
			obj->parseJson( body );									// TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			objs.push_back( obj );
		}
	}
	else if ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND )
	{
		throw ConnectedVision::runtime_error( body );
	}
	return objs;
}


/**
 * get a single object by ID
 *
 * @param id			object ID
 */
template <class TDataObject>
boost::shared_ptr<TDataObject> DataSource_REST_BaseClass<TDataObject>::getByID(const id_t id)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/id/" << id;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );

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
boost::shared_ptr<TDataObject> DataSource_REST_BaseClass<TDataObject>::getByIndex(const int64_t index)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/index/" << index;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );

	if ( objs.size() == 1 )
		return objs[0];
	else if ( objs.size() == 0 )
		return boost::shared_ptr<TDataObject>();
	else
		throw ConnectedVision::runtime_error( "getByIndex(): multiple results found (index: " + intToStr(index) + ")" );
}


/**
 * get multiple objects by index range
 *
 * @param start			index of first object
 * @param end			index of last object
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_REST_BaseClass<TDataObject>::getByIndexRange(const int64_t start, const int64_t end)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/index/" << start << "/" << end;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );
	return requestObjs( restmoduleURI.str() );
}


/**
 * get multiple objects by timestamp
 *
 * @param timestamp		timestamp
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_REST_BaseClass<TDataObject>::getByTimestamp(const timestamp_t timestamp)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/time/" << timestamp;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );
	return requestObjs( restmoduleURI.str() );
}


/**
 * get multiple objects at previous timestamp
 *
 * @param timestamp		timestamp
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_REST_BaseClass<TDataObject>::getBeforeTimestamp(const timestamp_t timestamp)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/beforetime/" << timestamp;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );
	return requestObjs( restmoduleURI.str() );
}

/**
 * get multiple objects at next timestamp
 *
 * @param timestamp		timestamp
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_REST_BaseClass<TDataObject>::getAfterTimestamp(const timestamp_t timestamp)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/aftertime/" << timestamp;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );
	return requestObjs( restmoduleURI.str() );
}

/**
 * get multiple objects by time range
 *
 * @param start			start of search time span
 * @param end			end of search time span
 */
template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > DataSource_REST_BaseClass<TDataObject>::getAllInTimespan(const timestamp_t start, const timestamp_t end)
{
	std::stringstream restmoduleURI;
	restmoduleURI << moduleURI << configID << "/" << outputPinID << "/time/" << start << "/" << end;
	std::vector< boost::shared_ptr<TDataObject> > objs( requestObjs( restmoduleURI.str() ) );
	return requestObjs( restmoduleURI.str() );
}

} // namespace ConnectedVision

#endif // DataSource_REST_BaseClass_impl