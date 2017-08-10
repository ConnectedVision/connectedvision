/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef Store_Cache_def
#define Store_Cache_def

#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#include <IStore.h>

#include <ConnectedVision.h>

namespace ConnectedVision {
namespace DataHandling {

/**
 * adds a cache to a write store
 *
 * implementing IStore_ReadWrite interface
 */
template<class TDataClass>
class Store_Cache : public IStore_ReadWrite<TDataClass>
{
public:
	Store_Cache(
		const id_t& configID,				///< [in] config ID
		const int64_t cacheSize,			///< [in] number of maximal elements in cache
		const shared_ptr< IStore_ReadWrite<TDataClass> > baseStore	///< [in] store to be cached (typically a DB store)
	);

	virtual ~Store_Cache();


	/**
	* factory function for data objects
	* each call:
	*  1. creates or reuses a data object
	*  2. calls the clear() function of the data object (even for newly created objects)
	*		The clear function of the data object clears all data and content, but does not release any memory or resources.
	*
	* @return shared pointer to data object
	*/
	virtual shared_ptr<TDataClass> create();
	
	/**
	* convert a writable data object to a read-only data object
	*
	* @thows std::runtime if object has multiple users
	* @return shared pointer to read-only data object
	*/
	virtual shared_ptr<const TDataClass> make_const(
		shared_ptr<TDataClass>& data	///< [in/moved] shared pointer to a writeable data object (ownership is moved)
	) const;
		
	/**
	* explicitely release allocated object
	* This function returns the ownership of an object to the allocator.
	*/
	virtual void initiateRelease(
		shared_ptr<const TDataClass>& dataConst ///< [in/moved] shared pointer to read-only data object (ownership is moved)
	);

	/**
		* get the data range of the store
		* @note This function is MANDATORY.
		* @return DataRange object with index and timespan range
		*/
	virtual DataRange getDataRange() const;

	/**
		* get configID of store
		*
		* @return current configID of store
		*/
	virtual const id_t& getConfigID() const;

	/**
		* get a single object by ID
		* @note This function is MANDATORY.
		*/
	virtual shared_ptr<const TDataClass> getByID (	
		const id_t& id	///< [in] object ID
	);

	/**
		* get a single object by index
		* @note This function is MANDATORY.
		*/
	virtual shared_ptr<const TDataClass> getByIndex(
		const int64_t index	///< [in] object index
	);

	/**
		* get multiple objects by index range
		* @note This function is MANDATORY.
		*
		* @return vector to shared pointer of data objects
		*/
	virtual std::vector< shared_ptr<const TDataClass> > getByIndexRange(
		const int64_t start,	///< [in] index of first object 
		const int64_t end		///< [in] index of last object
	);

	/**
		* get multiple objects by timestamp
		* @note This function is MANDATORY.
		*
		* @return vector of shared pointers to data objects
		*/
	virtual std::vector< shared_ptr<const TDataClass> > getByTimestamp(
		const timestamp_t timestamp		///< [in] timestamp
	);

	/**
		* get multiple objects at previous timestamp
		* @note This function is MANDATORY.
		*
		* @return vector of shared pointers to data objects
		*/
	virtual std::vector< shared_ptr<const TDataClass> > getBeforeTimestamp(
		const timestamp_t timestamp		///< [in] timestamp
	);

	/**
		* get multiple objects at next timestamp
		* @note This function is MANDATORY.
		*
		* @return vector of shared pointers to data objects
		*/
	virtual std::vector< shared_ptr<const TDataClass> > getAfterTimestamp(
		const timestamp_t timestamp		///< [in] timestamp
	);

	/**
		* get multiple objects by index range
		* @note This function is MANDATORY.
		*
		* @return vector of shared pointers to data objects
		*/
	virtual std::vector< shared_ptr<const TDataClass> > getAllInTimespan(
		const timestamp_t start,		///< [in] start of search time span
		const timestamp_t end			///< [in] end of search time span
	);

	/**
		* get list of all IDs in ringbuffer
		*
		* @return ids
		*/
	virtual std::vector<id_t> getIDList();

	/**
		* save a single object
		* The ID of the data object has to be set in advance.
		* @note This function is MANDATORY.
		*
		* @return id of saved object
		*/
	virtual id_t save_const(
		const shared_ptr<const TDataClass>& data	///< [in] shared pointer to read-only data object
	);

	/**
		* save multiple objects as bulk save
		* The ID of the data objects has to be set in advance.
		* @note This function is MANDATORY.
		*
		* @return vector of object IDs
		*/
	virtual std::vector<id_t> save_constVector(
		const std::vector< shared_ptr<const TDataClass> >& dataList	///< [in] vector of shared pointers to read-only data objects
	);

	/**
		* delete all objects in this store
		* @note This function is MANDATORY.
		*/
	virtual void deleteAll();

	/**
		* delete a single object by ID
		* @note This function is MANDATORY.
		*/
	virtual void deleteByID (	
		const id_t& id	///< [in] object ID
	);


protected:

	typedef boost::unique_lock<boost::timed_mutex> CacheLock;

	struct CacheItem {
		CacheItem();
		CacheItem(ConnectedVision::shared_ptr<const TDataClass> data, bool modified);

		bool modified;
		timestamp_t timestamp;
		ConnectedVision::shared_ptr<const TDataClass> data;
	};

	/**
	 * flush the cache to the base store
	 */
	virtual void cacheFlush ();

	/**
	 * purge the least-recently-used element in the cache  
	 */
	virtual void cacheEvict(CacheLock& lock);

	/**
	 * add element to cache
	 *  If the element already exists, it will be updated.
	 *
	 * @return CacheItem
	 */
	virtual void cacheAdd(
		const shared_ptr<const TDataClass>& data,	///< [in] shared pointer to read-only data object
		bool modified								///< [in] are the data changed compared to the base store, e.g. saved	
	);

	/**
	 * add element to cache
	 *  If the element already exists, it will be updated.
	 *
	 * @return CacheItem
	 */
	virtual void cacheAdd(
		const shared_ptr<const TDataClass>& data,	///< [in] shared pointer to read-only data object
		bool modified,								///< [in] are the data changed compared to the base store, e.g. saved
		CacheLock& lock								///< [in] active cache lock 
	);

	/**
	* Should a data object be written to both, the cache and the base store (write-through)
	* or to the cache only?
	*
	* @return true to enable write-through
	*/
	virtual bool write_through(
		const shared_ptr<const TDataClass>& data	///< [in] shared pointer to read-only data object
	)
	{ return true; }

	// cache
	boost::timed_mutex cacheMutex;
	std::map<id_t, CacheItem> cache;

	const id_t configID;
	const int64_t cacheSize;
	shared_ptr< IStore_ReadWrite<TDataClass> > baseStore;
};


}} // namespace scope

// include source code: template inclusion model
#include "Store_Cache.cpp"

#endif // Store_Cache_def