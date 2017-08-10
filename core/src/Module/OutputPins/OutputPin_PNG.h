/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef OutputPin_PNG_def
#define OutputPin_PNG_def

#include "OutputPin_Generic.h"

namespace ConnectedVision {
namespace OutputPins {

/**
 * Connected Vision OutputPin for PNG images
 *
 * @note This OutputPin requires a (static) function getting / converting the appropriate PNG image from the data object.
 *			function signature:
 *			- std::string (*F)(const TDataClass&)
 */
template <class TDataClass>
class OutputPin_PNG : public OutputPin_Generic<TDataClass>
{
public:
	/**
	* constructor
	*/
	OutputPin_PNG(
		ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager,	///< [in] data store manager
		std::string (*getPNGImage)(const TDataClass&)	///< selector / getter function of the data object to read the PNG encoded image
	);

	/**
	* virtual destructor
	*/
	virtual ~OutputPin_PNG();

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

	/// selector / getter function of the data object to read the PNG encoded image
	std::string (*getPNGImage)(const TDataClass&);
};

}} // namespace scope

// include source code: template inclusion model
#include "OutputPin_PNG.cpp"

#endif // OutputPin_PNG_def