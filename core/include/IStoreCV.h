/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef IStoreCV_def
#define IStoreCV_def

#include "IStore.h"

namespace ConnectedVision
{
namespace Store
{
	template <class TDataObject>
	/**
	 * generic data storage interface
	 */
	class IStoreCV
	{
	public:
		virtual ~IStoreCV() {};

		/**
		 * save a single object
		 *	This function is MANDATORY.
		 *
		 * @param configID		ID of associated config
		 * @param obj			data object
		 */
		virtual id_t save(const id_t configID, TDataObject obj) = 0;

		/**
		 * save multiple objects as bulk save
		 *	This function is MANDATORY.
		 *
		 * @param configID		ID of associated config
		 * @param objs			vector data object
		 */
		virtual std::vector<id_t> saveVector(const id_t configID, std::vector<TDataObject> objs) = 0;



		/**
		 * get a single object by ID
		 *	This function is MANDATORY.
		 *
		 * @param configID		ID of associated config
		 * @param id			object ID
		 */
		virtual TDataObject getByID(const id_t configID, const id_t id) = 0;

		/**
		 * get a single object by index
		 *	This function is MANDATORY.
		 *
		 * @param configID		ID of associated config
		 * @param index			object index
		 */
		virtual TDataObject getByIndex(const id_t configID, int64_t index) = 0;

		/**
		 * get multiple objects by index range
		 *	This function is MANDATORY.
		 *
		 * @param configID		ID of associated config
		 * @param start			index of first object
		 * @param end			index of last object
		 */
		virtual std::vector< TDataObject > getByIndexRange(const id_t configID, int64_t start, int64_t end) = 0;

		/**
		 * get multiple objects by timestamp
		 *	This function is OPTIONAL.
		 *
		 * @param configID		ID of associated config
		 * @param timestamp		timestamp
		 */
		virtual std::vector< TDataObject > getByTimestamp(const id_t configID, const timestamp_t timestamp) { throw ConnectedVision::runtime_error("getByTimestamp() not implemented"); };

		/**
		 * get multiple objects at previous timestamp
		 *	This function is OPTIONAL.
		 *
		 * @param configID		ID of associated config
		 * @param timestamp		timestamp
		 */
		virtual std::vector< TDataObject > getBeforeTimestamp(const id_t configID, const timestamp_t timestamp) { throw ConnectedVision::runtime_error("getBeforeTimestamp() not implemented"); };

		/**
		 * get multiple objects at next timestamp
		 *	This function is OPTIONAL.
		 *
		 * @param configID		ID of associated config
		 * @param timestamp		timestamp
		 */
		virtual std::vector< TDataObject > getAfterTimestamp(const id_t configID, const timestamp_t timestamp) { throw ConnectedVision::runtime_error("getAfterTimestamp() not implemented"); };

		/**
		 * get multiple objects by index range
		 *	This function is OPTIONAL.
		 *
		 * @param configID		ID of associated config
		 * @param start			start of search time span
		 * @param end			end of search time span
		 */
		virtual std::vector< TDataObject > getAllInTimespan(const id_t configID, const timestamp_t start, const timestamp_t end) { throw ConnectedVision::runtime_error("getAllInTimespan() not implemented"); };


		/**
		 * delete all objects associated with a config
		 *	This function is MANDATORY.
		 *
		 * @param configID		ID of associated config
		 */
		virtual void deleteAll(const id_t configID) = 0;

	};

}
} // namespace ConnectedVision

#endif // IStore_def


