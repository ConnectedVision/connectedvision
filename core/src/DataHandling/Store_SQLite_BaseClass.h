/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_SQLite_BaseClass_def
#define Store_SQLite_BaseClass_def

#include <stdint.h>
#include <string>
#include <iterator>
#include <vector>
#include <sqlite3.h>
#include <boost/thread.hpp>
#include <DBConnection.h>

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
	class Store_SQLite_BaseClass : public IStore_ReadWrite<TDataClass>
	{
	public:

		/**
		 * construct and initialise store
		 */
		Store_SQLite_BaseClass(
			const id_t& configID,						///< [in] config ID (if configID == ID_NULL store is used for all configs in table)
			DBConnection& db,							///< [in] DB connection object
			const std::string &tableName, 				///< [in] name of table in DB
			const std::vector<std::string> columnDesc 	///< [in] array of column names
		);

		/**
		* virtual destructor
		*/
		virtual ~Store_SQLite_BaseClass() {};

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
			shared_ptr<TDataClass>& data	///< [in] shared pointer to a writeable data object (ownership is moved)
		) const;
		
		
		/**
		* explicitely releas allocated object
		* This function returns the ownership of an object to the allocator.
		*/
		virtual void initiateRelease(
			shared_ptr<const TDataClass>& dataConst ///< [in] shared pointer to read-only data object (ownership is moved)
		);

		// ConnectedVision Store functions

		/**
		* save a single object
		* uses the element directly, since it is guaranteed, that it is read only
		*/
		virtual id_t save_const( 
			const shared_ptr<const TDataClass>& data	///< [in] data object
		);

		/**
		* save vector of objects
		*
		* @return vector of object IDs
		*/
		virtual std::vector<id_t> save_constVector(
			const std::vector< shared_ptr<const TDataClass> >& data	///< [in] vector of shared pointers to read-only data objects
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
		virtual const id_t& getConfigID() const;


		/**
		* get a single element by ID
		*/
		virtual shared_ptr<const TDataClass> getByID(
			const id_t& id	///< [in] object ID
		);

		/**
		 * get element by index
		 */
		virtual shared_ptr<const TDataClass> getByIndex(
			const int64_t index	///< [in] sequence index of object (this is not the internal position in the ringbuffer)
		);

		/**
		 * get elements by index range
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getByIndexRange(
			const int64_t start,	///< [in] sequence start index (this is not the internal position in the ringbuffer)
			const int64_t end		///< [in] sequence end index (this is not the internal position in the ringbuffer)
		);


		/**
		* get multiple objects by timestamp
		*/
		virtual std::vector< shared_ptr<const TDataClass> > getByTimestamp(
			const timestamp_t timestamp	///< [in] timestamp of objects
		);

		/**
		* get multiple objects at previous timestamp
		*/
		virtual std::vector< shared_ptr<const TDataClass> > getBeforeTimestamp(
			const timestamp_t timestamp	///< [in] next time after timestamp of objects
		);

		/**
		* get multiple objects at next timestamp
		*/
		virtual std::vector< shared_ptr<const TDataClass> > getAfterTimestamp(
			const timestamp_t timestamp	///< [in] previous time before timestamp of objects
		);

		/**
		* get multiple objects by index range
		*/
		virtual std::vector< shared_ptr<const TDataClass> > getAllInTimespan(
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
			const id_t& id	///< [in] object ID
		);

	protected:

		id_t configID;

		/**
		 * get generic objects by filter
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getByFilter(
			const std::vector< Store::FilterEntry > filterList, 	///< [in] list of filter entries
			const std::vector< Store::SortEntry > sortList = std::vector< Store::SortEntry >(), 	///< [in] list of sort order entries (optional)
			const int64_t resultsStartIndex = 0, 					///< [in] index of first returned result objects (optionel / 0 = from start)
			const int64_t resultsNumber = -1						///< [in] maximum number of returned result objects (optionel / -1 = all after start index)
		);

		/**
		 * delete all objects associated with a config
		 */
		virtual void deleteByFilter(
			const std::vector< Store::FilterEntry > filterList	///< [in] list of filter entries
		);

		/**
		* read Object from DB
		* @note This function is MANDATORY.
		*
		*	Read table colum fields to object member variables. 
		*	Call sqlite3_step() to read all sub/child objects.
		*
		* @return SQLite return code
		*/
		virtual int readObject(
			sqlite3_stmt *stmt,					///< [in] pre-executed SQLite statement
			shared_ptr<const TDataClass>& obj,	///< [out] data object read from DB
			sqlite3 *db							///< [in] SQLite DB object
		) = 0;

		/**
		* write Object to DB
		* @note This function is MANDATORY.
		*
		*	Bind object member variables to table colum fields. 
		*	This function has to write the whole objects, 
		*	i.e. ti has to loop over all sub/child object bind them and call sqlite3_step() for each row.
		*
		* @return SQLite return code
		*/
		virtual int writeObject(
			sqlite3_stmt *stmt,							///< [in] prepared SQLite statement
			const shared_ptr<const TDataClass>& obj,	///< [in] data object read from DB
			sqlite3 *db,								///< [in] SQLite DB object
			const int64_t sortID						///< [in] unique index of object
		) = 0;

		/**
		* append object internal sort criteria to list
		* @note This function is MANDATORY.
		*/
		virtual void appendObjectGrouping(
			std::vector< Store::SortEntry >& sortList ///< [in/out] list of sort criteria for table rows
		) const = 0;

		/**
		* get name of internal sort criteria column
		* @note This function is MANDATORY.
		*
		* @return column name
		*/
		virtual const std::string objectKey() const = 0;

		std::string tableName;
		std::string columnNames;
		std::string columnBindIdx;
		DBConnection& dbConn;

		const ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > dataAllocator;

	private:

		void appendSort(std::string& sql, const std::vector<Store::SortEntry>& sortList) const;
		void appendFilter(std::string& sql, const std::vector<Store::FilterEntry>& filterList, int& bindIdx) const;
		void bindFilter(sqlite3_stmt *stmt, const std::vector<Store::FilterEntry>& filterList, int& bindIdx) const;

		virtual std::vector<id_t> getIDList(sqlite3 *db) const;

		/**
		* save vector of elements
		*
		* @return vector of object IDs
		*/
		virtual std::vector<id_t> save_constVector(
			const std::vector< shared_ptr<const TDataClass> >& objs,	///< [in] vector of shared pointers to read-only data objects
			sqlite3 *db											///< [in] SQLite DB object
		);


		/**
		* get generic objects by filter
		*/
		virtual std::vector< shared_ptr<const TDataClass> > getByFilter(
			std::vector< Store::FilterEntry > filterList,	///< [in] list of filter entries
			std::vector< Store::SortEntry > sortList,		///< [in] list of sort order entries
			const int64_t resultsStartIndex,					///< [in] index of first returned result objects (optionel / 0 = from start)
			const int64_t resultsNumber,						///< [in] maximum number of returned result objects (optionel / -1 = all after start index)
			sqlite3 *db											///< [in] SQLite DB object
		);

		virtual void deleteByFilter(const std::vector< Store::FilterEntry > filterList, sqlite3 *db);


	};

}} // namespace scope

#endif // Store_SQLite_BaseClass_def

// include source code: template inclusion model
#include "Store_SQLite_BaseClass.cpp"



