/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef OutputPin_Generic_code
#define OutputPin_Generic_code

#include "OutputPin_Generic.h"

#include <HTTP/HTTPTools.h>
#include <Module/Control/Class_generic_config.h>


namespace ConnectedVision {
namespace OutputPins {

template <class TDataClass>
OutputPin_Generic<TDataClass>::OutputPin_Generic(ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager) :
	dataStoreManager( dataStoreManager )
{
	if ( !dataStoreManager )
		throw ConnectedVision::runtime_error( "invalid dataStoreManager" );

	configID = ID_NULL;
}


template <class TDataClass>
OutputPin_Generic<TDataClass>::~OutputPin_Generic(void)
{
}

template <class TDataClass>
void OutputPin_Generic<TDataClass>::init(const std::string& configStr)
{
	Class_generic_config config;
	config.parseJson( configStr.c_str() );
	this->configID = config.getconst_id();

	// free data store before trying to get new one to allow releasing shared pointer (pointer is hold by output pin (this class) AND storemap)
	this->dataStore.reset();

	// get actual store
	this->dataStore = this->dataStoreManager->getReadStore( this->configID );
	if ( !this->dataStore )
		throw ConnectedVision::runtime_error( "cannot get read store for configID: " + IDToStr(this->configID) );
}


template <class TDataClass>
id_t OutputPin_Generic<TDataClass>::get_configID()
{
	return this->configID;
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getByID(const id_t id, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		auto obj = this->dataStore->getByID(id);

		// encode and write object
		return this->packSingleObject(obj, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		auto obj = dataStore->getByIndex(index);
		
		// encode and write object
		return this->packSingleObject(obj, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		auto objs = dataStore->getByIndexRange(start, end);

		// any data found?
		if ( objs.size() == 0 )
		{
			// not found
			return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), "not found");
		}

		// encode and write objects
		return this->packMultipleObjects(objs, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		auto objs = dataStore->getByTimestamp(timestamp);

		// any data found?
		if ( objs.size() == 0 )
		{
			// not found
			return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), "not found");
		}

		// encode and write objects
		return this->packMultipleObjects(objs, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		auto objs = dataStore->getBeforeTimestamp(timestamp);

		// any data found?
		if ( objs.size() == 0 )
		{
			// not found
			return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), "not found");
		}

		// encode and write objects
		return this->packMultipleObjects(objs, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// get object from Store
		auto objs = dataStore->getAfterTimestamp(timestamp);

		// any data found?
		if ( objs.size() == 0 )
		{
			// not found
			return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), "not found");
		}

		// encode and write objects
		return this->packMultipleObjects(objs, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

template <class TDataClass>
int OutputPin_Generic<TDataClass>::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{
	try 
	{
		// is request within data range
		auto dataRange = dataStore->getDataRange();
		if ( start > dataRange.timestampEnd || end < dataRange.timestampStart )
		{
			// not found
			return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), "not found");
		}


		// get object from Store
		auto objs = dataStore->getAllInTimespan(start, end);

		// encode and write objects
		return this->packMultipleObjects(objs, response);
	}
	catch (config_runtime_error& e)
	{
		// config not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
	catch (ConnectedVision::runtime_error& e)
	{
		// internal server error
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("OutputPin_Generic<>"), std::string(e.what()) );
	}
}

}} // namespace scope

#endif // OutputPin_code
