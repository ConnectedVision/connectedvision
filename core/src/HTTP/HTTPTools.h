/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef HTTPTools_def
#define HTTPTools_def

#include <IHTTPAbstraction.h>

#include <boost/algorithm/string/replace.hpp>

namespace ConnectedVision {
namespace HTTP {

	/**
	* generate error response
	*
	* @return status code (analog to HTTP codes)
	*/
	static inline EnumHTTPStatus writeErrorResponse(
		ConnectedVisionResponse &response,	///< [out]	requested data or error response
		EnumHTTPStatus status,				///< [in]	error status
		const id_t &moduleID,						///< [in]	module or component name / ID
		std::string error					///< [in]	error message
	) {

		response.setContentType("application/json");
		error = boost::replace_all_copy( error, "\"", "'");
		boost::replace_all( error, "\n", "");	boost::replace_all( error, "\r", "");
		response.setContent( "{ \"status\": " + intToStr(status) + ", \"moduleID\": \"" + moduleID + "\"" + ", \"error\": \"" + error + "\"}" );

		return status;
	}

}} // namespace

#endif // HTTPTools_def
