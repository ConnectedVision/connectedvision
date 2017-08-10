/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef OutputPin_JSON_code
#define OutputPin_JSON_code

#include "OutputPin_JSON.h"
#include <HTTP/HTTPTools.h>

namespace ConnectedVision {
namespace OutputPins {

template <class TDataClass>
OutputPin_JSON<TDataClass>::OutputPin_JSON(ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager) :
	OutputPin_Generic<TDataClass>( dataStoreManager )
{
}


template <class TDataClass>
OutputPin_JSON<TDataClass>::~OutputPin_JSON(void)
{
}

template <class TDataClass>
ConnectedVision::HTTP::EnumHTTPStatus OutputPin_JSON<TDataClass>::packSingleObject(const ConnectedVision::shared_ptr<const TDataClass> &obj, ConnectedVisionResponse &response)
{
	if ( obj )
	{
		response.setContentType("application/json");

		// return JSON string
		response.setContent( obj->toJsonStr() );

		return ConnectedVision::HTTP::HTTP_Status_OK;
	}
	else
	{
		// not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin_JSON<>"), "not found");
	}
}

template <class TDataClass>
ConnectedVision::HTTP::EnumHTTPStatus OutputPin_JSON<TDataClass>::packMultipleObjects(const std::vector<ConnectedVision::shared_ptr<const TDataClass>> &objs, ConnectedVisionResponse &response)
{
	response.setContentType("application/json");

	// build JSON array
	std::string data = "[\n";
	for (auto it = objs.cbegin(); it!=objs.cend(); ++it)
	{
		if ( it != objs.cbegin() )
			data += ",\n";
		data += (*it)->toJsonStr();
	}
	data += "\n]";
	response.setContent( data );

	return ConnectedVision::HTTP::HTTP_Status_OK;
}

} // namespace OutputPins
} // namespace scope

#endif // OutputPin_JSON_code