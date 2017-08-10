/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_Ringbuffer_def
#define Store_Ringbuffer_def

#include <stdint.h>
#include <string>
#include <iterator>
#include <vector>
#include <map>
#include <boost/thread.hpp>

#include <general.h>
#include <IStore.h>

#define IConnectedVisionDataClass	class


namespace ConnectedVision 
{ namespace DataHandling
{

	/**
		This ring-buffer class has the following features:
			- dynamically initialization / allocation of data objects (until ring-buffer is filled)
			- dynamically resizable
			- thread-safe

		The data objects have to implement the following functions: (see: shared-pointer)
			- simple public constructor (without any parameters)
			- public copy constructor 
			- reset() function: resetting the internal state of the object, but do not necessarily need to free pre-allocated resources (e.g. memory buffers, ...)
	*/
	template <IConnectedVisionDataClass TDataClass>
	class Store_Ringbuffer : public IStore_ReadWrite<TDataClass>
	{
	public:

		typedef boost::shared_lock<boost::shared_mutex>	ReadLock;
		typedef boost::unique_lock<boost::shared_mutex>	WriteLock;
	
		struct Stats {
			int64_t size;
			int64_t entriesAllocated;
			int64_t entriesUsed;

			int64_t firstIndex;
			int64_t lastIndex;

			timestamp_t firstTimestamp;
			timestamp_t lastTimestamp;
		};

		/**
		* constructor
		*	uses DataAllocator_Primitive (new / delete for every object request)
		*/
		Store_Ringbuffer(
			const ConnectedVision::id_t& configID,	///< [in] configID
			const int64_t size		///< [in] number of maximal elements in ring buffer
		);

		/**
		* constructor
		*/
		Store_Ringbuffer(
			const ConnectedVision::id_t& configID,	///< [in] configID
			const int64_t size, 												///< [in] number of maximal elements in ring buffer
			ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > allocator	///< [in] data allocator / factory and deallocator / reuse
		);

		/**
		* virtual destructor
		*/
		virtual ~Store_Ringbuffer() {};

		/**
		* factory function for data objects
		* each call:
		*  1. creates or reuses a data object
		*  2. calls the clear() function of the data object (even for newly created objects)
		*		The clear function of the data object clears all data and content, but does not release any memory or resources.
		*
		* @return shared pointer to data object
		*/
		virtual ConnectedVision::shared_ptr<TDataClass> create();


		/**
		* convert a writable data object to a read-only data object
		*
		* @thows std::runtime if object has multiple users
		* @return shared pointer to read-only data object
		*/
		virtual ConnectedVision::shared_ptr<const TDataClass> make_const(
			ConnectedVision::shared_ptr<TDataClass>& data	///< [in] shared pointer to a writeable data object (ownership is moved)
		) const;
		
		
		/**
		* explicitely releas allocated object
		* This function returns the ownership of an object to the allocator.
		*/
		virtual void initiateRelease(
			ConnectedVision::shared_ptr<const TDataClass>& dataConst ///< [in] shared pointer to read-only data object (ownership is moved)
		);

		/**
		* get ring buffer status
		* 
		* @return status and statistics
		*/
		Stats getStats() const;


		// ConnectedVision Store functions

		/**
		* save a single element
		* uses the element directly, since it is guaranteed, that it is read only
		* add a new element to the end of the ring buffer, 
		* it is possible that one or more previous elements are removed from the ringbuffer
		*/
		virtual ConnectedVision::id_t save_const(
			const ConnectedVision::shared_ptr<const TDataClass>& data	///< [in] data object
		);

		/**
		* add a vector of new elements to the end of the ring buffer, 
		* it is possible that one or more previous elements are removed from the ringbuffer
		*
		* @return vector of object IDs
		*/
		virtual std::vector<id_t> save_constVector(
			const std::vector< ConnectedVision::shared_ptr<const TDataClass> >& dataContainer	///< [in] vector of shared pointers to read-only data objects
		);

		/**
		 * get list of all IDs in ringbuffer
		 *
		 * @return ids
		 */
		virtual std::vector<id_t> getIDList();

		/**
		 * get the data range of the store
		 * 
		 * @return DataRange object with index and timespan range
		 */
		virtual DataRange getDataRange() const;

		/**
		 * get configID of store
		 *
		 * @return current configID of store
		 */
		virtual const ConnectedVision::id_t& getConfigID() const;

		/**
		* get a single element by ID
		*/
		virtual ConnectedVision::shared_ptr<const TDataClass> getByID(
			const ConnectedVision::id_t& id	///< [in] object ID
		);

		/**
		 * get element by index
		 */
		virtual ConnectedVision::shared_ptr<const TDataClass> getByIndex(
			const int64_t index	///< [in] sequence index of object (this is not the internal position in the ringbuffer)
		);

		/**
		 * get elements by index range
		 */
		virtual std::vector< ConnectedVision::shared_ptr<const TDataClass> > getByIndexRange(
			const int64_t start,	///< [in] sequence start index (this is not the internal position in the ringbuffer)
			const int64_t end		///< [in] sequence end index (this is not the internal position in the ringbuffer)
		);


		/**
		* get multiple objects by timestamp
		*/
		virtual std::vector< ConnectedVision::shared_ptr<const TDataClass> > getByTimestamp(
			const timestamp_t timestamp	///< [in] timestamp of objects
		);

		/**
		* get multiple objects at previous timestamp
		*/
		virtual std::vector< ConnectedVision::shared_ptr<const TDataClass> > getBeforeTimestamp(
			const timestamp_t timestamp	///< [in] next time after timestamp of objects
		);

		/**
		* get multiple objects at next timestamp
		*/
		virtual std::vector< ConnectedVision::shared_ptr<const TDataClass> > getAfterTimestamp(
			const timestamp_t timestamp	///< [in] previous time before timestamp of objects
		);

		/**
		* get multiple objects by index range
		*/
		virtual std::vector< ConnectedVision::shared_ptr<const TDataClass> > getAllInTimespan(
			const timestamp_t start,	///< start of search time span
			const timestamp_t end		///< end of search time span
		);

		/**
		* delete all objects in ringbuffer
		*/
		virtual void deleteAll();

		/**
		 * delete a single object by ID
		 */
		virtual void deleteByID (	
			const ConnectedVision::id_t& id	///< [in] object ID
		);

		/**
		 * set index to specified start value
		 *
		 * Deletes all data previously stored in store.
		 */
		virtual void resetIndex (	
			const int64_t index	///< [in] sequence index of object (this is not the internal position in the ringbuffer)
		);

	protected:
		typedef ConnectedVision::shared_ptr<const TDataClass> element_t;
		typedef std::multimap<timestamp_t, element_t*> timestampLookup_t;

		/**
		* clear all entries in ringbuffer
		*/
		void init();

		/**
		* rebuild lookup tables
		*/
		void rebuildLookup(WriteLock& lock);

		const id_t configID;

		mutable boost::shared_mutex containerMutex;
		/// container holding the actual data
		std::vector<element_t> container;

		// queue handling
		int64_t bufferSize;
		int64_t bufferFirstPos;
		int64_t bufferLastPos;

		/// mapping ID to actual data elements
		std::map<ConnectedVision::id_t, element_t*> idLookup;

		/// mapping timestamp to actual data elements
		timestampLookup_t timestampLookup;

		int64_t startIndex; ///< start index of container
		int64_t firstIndex; ///< index of first element in container
		int64_t lastIndex; ///< index of last element in container

		const ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > dataAllocator;
	};


	/**
	* factory for Store_Ringbuffer
	*/
	template <IConnectedVisionDataClass TDataClass>
	class Store_Ringbuffer_Factory : public IStore_ReadWrite_Factory<TDataClass>
	{
	public:
		/**
		* constructor
		*	uses DataAllocator_Primitive (new / delete for every object request)
		*/
		Store_Ringbuffer_Factory(
			const int64_t ringbufferSize 										///< [in] number of maximal elements in ring buffer
		);

		/**
		* constructor
		*/
		Store_Ringbuffer_Factory(
			const int64_t ringbufferSize, 										///< [in] number of maximal elements in ring buffer
			ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > allocator	///< [in] data allocator / factory and deallocator / reuse
		);
	
		/**
		* virtual desctuctor
		*/
		virtual ~Store_Ringbuffer_Factory() {};

		/**
		* creates a new store
		*/
		virtual shared_ptr< IStore_ReadWrite<TDataClass> > create(
			const ConnectedVision::id_t configID	= ID_NULL	///< [in] config ID of requested store (optional)
		);

	protected:
		/**
		* init factory
		*/
		void init();

		const int64_t ringbufferSize;
		const ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > dataAllocator;
	};


}}

// include source code: template inclusion model
#include "Store_Ringbuffer.cpp"

#endif // Store_Ringbuffer_def


