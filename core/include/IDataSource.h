/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** IDataSource.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef IDataSource_def
#define IDataSource_def

#include <boost/shared_ptr.hpp>

#include "general.h"
#include "ConnectedVision_Exceptions.h"

namespace ConnectedVision
{

/**
 * data source interface
 */
template <class TDataObject>
class IDataSource
{
public:
	/**
		* get a single object by ID
		*	This function is MANDATORY.
		*
		* @param configID		ID of associated config
		* @param id			object ID
		*/
	virtual boost::shared_ptr<TDataObject> getByID(const id_t id) = 0;

	/**
		* get a single object by index
		*	This function is MANDATORY.
		*
		* @param configID		ID of associated config
		* @param index			object index
		*/
	virtual boost::shared_ptr<TDataObject> getByIndex(const int64_t index) = 0;

	/**
		* get multiple objects by index range
		*	This function is MANDATORY.
		*
		* @param configID		ID of associated config
		* @param start			index of first object
		* @param end			index of last object
		*/
	virtual std::vector< boost::shared_ptr<TDataObject> > getByIndexRange(const int64_t start, const int64_t end) { throw ConnectedVision::runtime_error("getByIndexRange() not implemented"); };

	/**
		* get multiple objects by timestamp
		*	This function is OPTIONAL.
		*
		* @param configID		ID of associated config
		* @param timestamp		timestamp
		*/
	virtual std::vector< boost::shared_ptr<TDataObject> > getByTimestamp(const timestamp_t timestamp) { throw ConnectedVision::runtime_error("getByTimestamp() not implemented"); };

	/**
		* get multiple objects at previous timestamp
		*	This function is OPTIONAL.
		*
		* @param configID		ID of associated config
		* @param timestamp		timestamp
		*/
	virtual std::vector< boost::shared_ptr<TDataObject> > getBeforeTimestamp(const timestamp_t timestamp) { throw ConnectedVision::runtime_error("getBeforeTimestamp() not implemented"); };

	/**
		* get multiple objects at next timestamp
		*	This function is OPTIONAL.
		*
		* @param configID		ID of associated config
		* @param timestamp		timestamp
		*/
	virtual std::vector< boost::shared_ptr<TDataObject> > getAfterTimestamp(const timestamp_t timestamp) { throw ConnectedVision::runtime_error("getAfterTimestamp() not implemented"); };

	/**
		* get multiple objects by index range
		*	This function is OPTIONAL.
		*
		* @param configID		ID of associated config
		* @param start			start of search time span
		* @param end			end of search time span
		*/
	virtual std::vector< boost::shared_ptr<TDataObject> > getAllInTimespan(const timestamp_t start, const timestamp_t end) { throw ConnectedVision::runtime_error("getAllInTimespan() not implemented"); };
};

} // namespace ConnectedVision

#endif // IDataSource_def
