/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef OutputPin_PNG_code
#define OutputPin_PNG_code

#include "OutputPin_PNG.h"
#include <HTTP/HTTPTools.h>

namespace ConnectedVision {
namespace OutputPins {

template <class TDataClass>
OutputPin_PNG<TDataClass>::OutputPin_PNG(ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager, std::string (*getPNGImage)(const TDataClass&) ) :
	OutputPin_Generic<TDataClass>( dataStoreManager ), getPNGImage( getPNGImage )
{
}

template <class TDataClass>
OutputPin_PNG<TDataClass>::~OutputPin_PNG(void)
{
}

template <class TDataClass>
ConnectedVision::HTTP::EnumHTTPStatus OutputPin_PNG<TDataClass>::packSingleObject(const ConnectedVision::shared_ptr<const TDataClass> &obj, ConnectedVisionResponse &response)
{
	if ( obj )
	{
		response.setContentType("image/png");

		// return PNG as string
		response.setContent( getPNGImage(*obj) ); // use selector function

		return ConnectedVision::HTTP::HTTP_Status_OK;
	}
	else
	{
		// not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin<>"), "not found");
	}
}

template <class TDataClass>
ConnectedVision::HTTP::EnumHTTPStatus OutputPin_PNG<TDataClass>::packMultipleObjects(const std::vector<ConnectedVision::shared_ptr<const TDataClass>> &objs, ConnectedVisionResponse &response)
{
	if ( !objs.size() )
	{
		// not found
		return writeErrorResponse(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("OutputPin<>"), "not found");
	}

	return this->packSingleObject(objs.at(0), response);
}

} // namespace OutputPins
} // namespace ConnectedVision

#endif // OutputPin_PNG_code