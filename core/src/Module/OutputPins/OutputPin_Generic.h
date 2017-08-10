/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef OutputPin_Generic_def
#define OutputPin_Generic_def

#include <IConnectedVisionModule.h>
#include <IStore.h>
#include <IHTTPAbstraction.h>

#include <ConnectedVision.h>

namespace ConnectedVision {
namespace OutputPins {

/**
 * Connected Vision generic output pin
 *
 * @note: used patterns:
 *	- [Template Method Pattern] The OutputPin_Generic implements the Template Pattern with two hook methods to be overweitten: packSingleObject(), packMultipleObjects()
 *		(https://en.wikipedia.org/wiki/Template_method_pattern)
 *
 *	packSingleObject()		...	encodes and packs a single object
 *	packMultipleObjects()	...	encodes and packs a list of objects
 */
template <class TDataClass>
class OutputPin_Generic : public IConnectedVisionOutputPin
{
public:

	/**
	* constructor
	*/
	OutputPin_Generic(
		ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager	///< [in] data store manager
	);

	/**
	* virtual destructor
	*/
	virtual ~OutputPin_Generic();


	/**
	* initialize output store for specific config
	*/
	virtual void init(
		const std::string& configStr	///< [in] config as JSON string
	);

	/**
	* get the config ID, the output pin is currently configured for
	*
	* @return config ID
	*/
	id_t get_configID();

	/**
	* get data by ID
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getByID(
		const id_t id,						///< [in]	id of requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);
	
	/**
	* get data by time span
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getByIndex(
		const int64_t index,				///< [in]	index of requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);

	/**
	* get data by index range
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getByIndexRange(
		const int64_t start,				///< [in]	first index of requested data
		const int64_t end,					///< [in]	last index of requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);

	/**
	* get data by timestamp
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getByTimestamp(
		const timestamp_t timestamp,		///< [in]	timestamp of requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);


	/**
	* get data for timestamp just before given time
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getBeforeTimestamp(
		const timestamp_t timestamp,		///< [in]	timestamp after requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);

	/**
	* get data for timestamp just after given time
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getAfterTimestamp(
		const timestamp_t timestamp,		///< [in]	timestamp before requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);

	/**
	* get data by time span
	*
	* @return status code (analog to HTTP codes)
	*/
	virtual int getAllInTimespan(
		const timestamp_t start,			///< [in]	first timestamp of requested data
		const timestamp_t end,				///< [in]	last timestamp of requested data
		ConnectedVisionResponse &response	///< [out]	requested data or error response
	);

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
	) = 0;

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
	) = 0;

	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<TDataClass> > dataStoreManager;
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Read<TDataClass> > dataStore;
	id_t configID;
};

}} // namespace scope

// include source code: template inclusion model
#include "OutputPin_Generic.cpp"

#endif // OutputPin_Generic_def