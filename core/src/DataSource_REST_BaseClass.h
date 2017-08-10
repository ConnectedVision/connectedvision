/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** DataSource_REST_BaseClass.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef DataSource_REST_BaseClass_def
#define DataSource_REST_BaseClass_def

#include <string>
#include <vector>

#include "general.h"
#include <IDataSource.h>

namespace ConnectedVision
{

template <class TDataObject>
class DataSource_REST_BaseClass : public IDataSource< TDataObject >
{

public:
	DataSource_REST_BaseClass();
	virtual ~DataSource_REST_BaseClass();

	/**
	 * initialize data source
	 *
	 * The data source has to be initialized for every (re-)connection to an output pin of another module.
	 *
	 * @param moduleURI		URI of connected (source) module - The module connected to the input pin of the current module.
	 * @param configID		configID of chain entry - The config corresponding to the source module.
	 * @param outputPinID	pin ID of connected output Pin
	 */
	virtual void init(const std::string &moduleURI, const id_t &configID, const pinID_t &outputPinID);


	/**
	 * get a single object by ID
	 *	This function is MANDATORY.
	 *
	 * @param id			object ID
	 */
	virtual boost::shared_ptr<TDataObject> getByID(const id_t id);

	/**
	 * get a single object by index
	 *	This function is MANDATORY.
	 *
	 * @param index			object index
	 */
	virtual boost::shared_ptr<TDataObject> getByIndex(const int64_t index);

	/**
	 * get multiple objects by index range
	 *	This function is OPTIONAL.
	 *
	 * @param start			index of first object
	 * @param end			index of last object
	 */
	virtual std::vector< boost::shared_ptr<TDataObject> > getByIndexRange(const int64_t start, const int64_t end);

	/**
	 * get multiple objects by timestamp
	 *	This function is OPTIONAL.
	 *
	 * @param timestamp		timestamp
	 */
	virtual std::vector< boost::shared_ptr<TDataObject> > getByTimestamp(const timestamp_t timestamp);

	/**
	 * get multiple objects at previous timestamp
	 *	This function is OPTIONAL.
	 *
	 * @param timestamp		timestamp
	 */
	virtual std::vector< boost::shared_ptr<TDataObject> > getBeforeTimestamp(const timestamp_t timestamp);

	/**
	 * get multiple objects at next timestamp
	 *	This function is OPTIONAL.
	 *
	 * @param timestamp		timestamp
	 */
	virtual std::vector< boost::shared_ptr<TDataObject> > getAfterTimestamp(const timestamp_t timestamp);

	/**
	 * get multiple objects by index range
	 *	This function is OPTIONAL.
	 *
	 * @param start			start of search time span
	 * @param end			end of search time span
	 */
	virtual std::vector< boost::shared_ptr<TDataObject> > getAllInTimespan(const timestamp_t start, const timestamp_t end);

protected:
	
	/**
	 * get multiple objects from RESTfull service
	 *
	 * @param restURL	full REST URL of request
	 */
	virtual std::vector< boost::shared_ptr<TDataObject> > requestObjs(const std::string restURL ) const;

	std::string moduleURI;
	id_t configID;
	pinID_t outputPinID;
};

} // namespace ConnectedVision

#endif // DataSource_REST_BaseClass_def

// include source code: template inclusion model
#include "DataSource_REST_BaseClass.cpp"

