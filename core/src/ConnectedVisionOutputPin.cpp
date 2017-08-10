/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVisionOutputPin_code
#define ConnectedVisionOutputPin_code

#include <IDataClassJSON.h>
#include "ConnectedVisionOutputPin.h"
#include "HTTP/HTTPXClient.h"

#include "helper.h"

#include <sstream>
#include <string>
#include <vector>

namespace ConnectedVision {

template <class TDataObject>
ConnectedVisionOutputPin<TDataObject>::ConnectedVisionOutputPin(boost::shared_ptr< Store::IStoreCV<TDataObject> > dataStore) :
	dataStore( dataStore )
{
	if ( !dataStore )
		throw ConnectedVision::runtime_error( "invalid dataStore" );
}

template <class TDataObject>
ConnectedVisionOutputPin<TDataObject>::~ConnectedVisionOutputPin(void)
{

}

template <class TDataObject>
void ConnectedVisionOutputPin<TDataObject>::init(const std::string& configStr)
{
	this->config.parseJson( configStr.c_str() );
}

/**
 * get data from module by ID
 *
 * @param[in] id			ID of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getByID(const id_t id, ConnectedVisionResponse &response)
{
	TDataObject obj;
	try 
	{
		// get object from Store
		obj = dataStore->getByID(this->config.get_id(), id);
		if ( obj )
		{
			// return JSON string
			response.setContentType("application/json");
			response.setContent( obj->toJsonStr() );
			return HTTP::HTTP_Status_OK;
		}
		else
		{

			// not found
			return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), "not found");
		}
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

/**
 * get data from module by index
 *
 * @param[in] index			index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	try 
	{
		if ( index < 0 )
		{ 
			return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), "invalid index (index < 0)");
		}

		// get object from Store
		std::vector<TDataObject> objs = dataStore->getByIndexRange(this->config.get_id(), index, index);
		if ( objs.size() == 1 )
		{
			// return JSON string
			response.setContentType("application/json");
			response.setContent( objs[0]->toJsonStr() );
			return HTTP::HTTP_Status_OK;
		}
		else
		{

			// not found
			return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), "not found");
		}
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

/**
 * get data from module by index range
 *
 * @param[in] start			first index of requested data
 * @param[in] end			last index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	if ( start < 0 )
	{ 
		return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), "invalid start index (start < 0)");
	}

	if ( end < start )
	{ 
		return writeError(response, HTTP::HTTP_Status_NOT_FOUND, id_t("ConnectedVisionOutputPin<>"), "invalid end index (end < start)");
	}

	try
	{
		// get object from Store
		std::string data = "[\n";
		std::vector<TDataObject> objs = dataStore->getByIndexRange(this->config.get_id(), start, end);
		for (typename std::vector<TDataObject>::iterator it = objs.begin(); it!=objs.end(); ++it)
		{
			if ( it != objs.begin() )
				data += ",\n";
			data += (*it)->toJsonStr();
		}
		data += "\n]";
		response.setContentType("application/json");
		response.setContent( data );
		return HTTP::HTTP_Status_OK;
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

/**
 * get data from module by timestamp
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		std::string data = "[\n";
		std::vector<TDataObject> objs = dataStore->getByTimestamp(this->config.get_id(), timestamp);
		for (typename std::vector<TDataObject>::iterator it = objs.begin(); it!=objs.end(); ++it)
		{
			if ( it != objs.begin() )
				data += ",\n";
			data += (*it)->toJsonStr();
		}
		data += "\n]";
		response.setContentType("application/json");
		response.setContent( data );
		return HTTP::HTTP_Status_OK;
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

/**
 * get data from module by timestamp before
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		std::string data = "[\n";
		std::vector<TDataObject> objs = dataStore->getBeforeTimestamp(this->config.get_id(), timestamp);
		for (typename std::vector<TDataObject>::iterator it = objs.begin(); it!=objs.end(); ++it)
		{
			if ( it != objs.begin() )
				data += ",\n";
			data += (*it)->toJsonStr();
		}
		data += "\n]";
		response.setContentType("application/json");
		response.setContent( data );
		return HTTP::HTTP_Status_OK;
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

/**
 * get data from module by timestamp after
 *
 * @param[in] this->config.get_id()		ID of configuration / job
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		std::string data = "[\n";
		std::vector<TDataObject> objs = dataStore->getAfterTimestamp(this->config.get_id(), timestamp);
		for (typename std::vector<TDataObject>::iterator it = objs.begin(); it!=objs.end(); ++it)
		{
			if ( it != objs.begin() )
				data += ",\n";
			data += (*it)->toJsonStr();
		}
		data += "\n]";
		response.setContentType("application/json");
		response.setContent( data );
		return HTTP::HTTP_Status_OK;
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

/**
 * get data from module by time span
 *
 * @param[in] start			first timestamp of requested data
 * @param[in] end			last timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
template <class TDataObject>
int ConnectedVisionOutputPin<TDataObject>::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		std::string data = "[\n";
		std::vector<TDataObject> objs = dataStore->getAllInTimespan(this->config.get_id(), start, end);
		for (typename std::vector<TDataObject>::iterator it = objs.begin(); it!=objs.end(); ++it)
		{
			if ( it != objs.begin() )
				data += ",\n";
			data += (*it)->toJsonStr();
		}
		data += "\n]";
		response.setContentType("application/json");
		response.setContent( data );
		return HTTP::HTTP_Status_OK;
	}
	catch (std::exception& e)
	{
		// internal server error
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t("ConnectedVisionOutputPin<>"), std::string(e.what()) );
	}
}

} // namespace ConnectedVision

#endif // ConnectedVisionOutputPin_code