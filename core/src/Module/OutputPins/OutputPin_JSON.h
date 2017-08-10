/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef OutputPin_JSON_def
#define OutputPin_JSON_def

#include "OutputPin_Generic.h"

namespace ConnectedVision {
namespace OutputPins {

/**
 * Connected Vision OutputPin for meta data (JSON encoded)
 *
 * @note This OutputPin assumes that the TDataClass data object has a toJsonStr() function returning the meta data as JSON encoded string.
 *			function signature:
 *			- std::string toJsonStr() const;
 */
template <class TDataClass>
class OutputPin_JSON : public OutputPin_Generic<TDataClass>
{
public:
	/**
	* constructor
	*/
	OutputPin_JSON(
		ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager	///< [in] data store manager
	);

	/**
	* virtual destructor
	*/
	virtual ~OutputPin_JSON();

protected:

	/** 
	* encodes actual data and writes them to @ref response 
	*	this function is invoked by the getByXXX() functions
	* @note The default implementation assumes that the data object has a toJsonStr() function
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual ConnectedVision::HTTP::EnumHTTPStatus packSingleObject(
		const ConnectedVision::shared_ptr<const TDataClass> &obj,		///< [in] requested data object
		ConnectedVisionResponse &response					///< [out] reference to the ConnectedVisionResponse - results are written into this response
	);

	/** 
	* encodes actual data and writes them to @ref response 
	*	this function is invoked by the getByXXX() functions
	* @note The default implementation assumes that the data object has a toJsonStr() function
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual ConnectedVision::HTTP::EnumHTTPStatus packMultipleObjects(
		const std::vector<ConnectedVision::shared_ptr<const TDataClass>> &objs,	///< [in] requested data object
		ConnectedVisionResponse &response								///< [out] reference to the ConnectedVisionResponse - results are written into this response
	);
};

}} // namespace scope

// include source code: template inclusion model
#include "OutputPin_JSON.cpp"

#endif // OutputPin_JSON_def