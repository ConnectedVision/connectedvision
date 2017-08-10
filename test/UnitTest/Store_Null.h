/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Null_def
#define Store_Null_def

#include <IStore.h>


namespace ConnectedVision {
namespace DataHandling {

/**
 * adds a cache to a write store
 *
 * implementing IStore_ReadWrite interface
 */
template<class TDataClass>
class Store_Null : public IStore_ReadWrite<TDataClass>
{
public:
	Store_Null() {}

	virtual ~Store_Null() {}


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
};


}} // namespace scope

// include source code: template inclusion model
#include "Store_Null.cpp"

#endif // Store_Null_def