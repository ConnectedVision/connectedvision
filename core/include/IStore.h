/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef IStore_def
#define IStore_def

#include <vector>

#include <general.h>

#include <ConnectedVision.h>

namespace ConnectedVision
{

namespace Store
{
	namespace Op { enum Operation { NA, EQUAL, NOTEQUAL, SMALLER, SMALLEREQUAL, GREATEREQUAL, GREATER, INLIST, NOTINLIST }; }
	namespace Type { enum Type { NA, STRING, INTEGER, DOUBLE }; }
	namespace Order { enum Order { ASC, DESC }; }

	/**
	 *	data storage filter request
	 */
	class FilterEntry
	{
	public:
		std::string name;			///< member variable name
		Op::Operation operation;	///< filter operation
		Type::Type type;			///< type of value or column
		std::string valueString;	///< value to be compared with (used if type is STRING)
		std::vector<std::string> vectorString;	///< value to be compared with (used if type is STRING)
		int64_t valueInteger;		///< value to be compared with (used if type is INTEGER)
		std::vector<int64_t> vectorInteger;		///< value to be compared with (used if type is INTEGER)
		double valueDouble;			///< value to be compared with (used if type is DOUBLE)
		std::vector<double> vectorDouble;			///< value to be compared with (used if type is DOUBLE)

		/**
		 * string constructor
		 */
		FilterEntry(std::string name, Op::Operation operation, std::string value)
		{
			clear();
			this->name = name;
			this->operation = operation;
			this->type = Type::STRING;
			this->valueString = value;
		}

		/**
		 * bool constructor
		 */
		FilterEntry(std::string name, Op::Operation operation, bool value)
		{
			clear();
			this->name = name;
			this->operation = operation;
			this->type = Type::STRING;
			this->valueInteger = value ? 1 : 0;
		}

		/**
		 * integer constructor
		 */
		FilterEntry(std::string name, Op::Operation operation, int64_t value)
		{
			clear();
			this->name = name;
			this->operation = operation;
			this->type = Type::INTEGER;
			this->valueInteger = value;
		}

		/**
		 * double constructor
		 */
		FilterEntry(std::string name, Op::Operation operation, double value)
		{
			clear();
			this->name = name;
			this->operation = operation;
			this->type = Type::DOUBLE;
			this->valueDouble = value;
		}

		/**
		 * clear & reset object
		 */
		void clear()
		{
			this->name.clear();
			this->operation = Op::NA;
			this->type = Type::NA;
			this->valueString.clear();
			this->vectorString.clear();
			this->valueInteger = 0;
			this->vectorInteger.clear();
			this->valueDouble = 0.0;
			this->vectorDouble.clear();
		};
	};

	/**
	 *	data storage sort request
	 */
	class SortEntry
	{
	public:
		std::string name;			///< member variable name
		Order::Order order;	///< filter operation

		/**
		 * constructor
		 */
		SortEntry(std::string name, Order::Order order)
		{
			clear();
			this->name = name;
			this->order = order;
		}

		/**
		 * default constructor
		 */
		SortEntry()
		{
			clear();
		}

		/**
		 * clear & reset object
		 */
		void clear()
		{
			this->name.clear();
			this->order = Order::ASC;
		};
	};

	template <class TDataClassObject>
	/**
	 * generic data storage interface
	 */
	class IStore 
	{
	public:
		virtual ~IStore() {};

		/**
		 * save a single object
		 *	This function is MANDATORY.
		 *
		 * @param obj			data object
		 */
		virtual id_t save(TDataClassObject obj) = 0;

		/**
		 * save multiple objects as bulk save
		 *	This function is MANDATORY.
		 *
		 * @param objs			vector data object
		 */
		virtual std::vector<id_t> saveVector(std::vector<TDataClassObject> objs) = 0;

		/**
		 * get generic objects by filter
		 *	This function is MANDATORY.
		 *
		 * @param resultsStartIndex		index of first returned result objects (0 = from start)
		 * @param resultsNumber			maximum number of returned result objects (optionel / -1 = all after start index)
		 */
		virtual std::vector< TDataClassObject > getByIndex(const int64_t resultsStartIndex, const int64_t resultsNumber = 1) = 0;

		/**
		 * get generic objects by filter
		 *	This function is MANDATORY.
		 *
		 * @param id		object ID
		 *
		 * @return shared pointer to object (NULL if not found)
		 */
		virtual TDataClassObject getByID(const id_t id) = 0;

		/**
		 * get generic objects by filter
		 *	This function is MANDATORY.
		 *
		 * @param filterList			list of filter entries
		 * @param sortList				list of sort order entries
		 * @param resultsStartIndex		index of first returned result objects (optionel / 0 = from start)
		 * @param resultsNumber			maximum number of returned result objects (optionel / -1 = all after start index)
		 */
		virtual std::vector< TDataClassObject > getByFilter(const std::vector< Store::FilterEntry > filterList, const std::vector< Store::SortEntry > sortList = std::vector< Store::SortEntry >(), const int64_t resultsStartIndex = 0, const int64_t resultsNumber = -1) = 0;

		/**
		 * delete generic objects by filter
		 *	This function is MANDATORY.
		 *
		 * @param filterList			list of filter entries
		 */
		virtual void deleteByFilter(const std::vector< Store::FilterEntry > filterList) = 0 ;

	};

}

namespace DataHandling {
	
	class DataRange
	{
	public:
		/** start index of the data range */
		int64_t indexStart;
	
		/** end index of the data range */
		int64_t indexEnd;
	
		/** start timestamp of the data range */
		timestamp_t timestampStart;
	
		/** end timestamp of the data range */
		timestamp_t timestampEnd;
	};

	template <class TDataClass>
	class IDataAllocator
	{
	public:
		/**
		* factory function for data objects
		* each call:
		*  1. creates or reuses a data object
		*  2. calls the clear() function of the data object (even for newly created objects)
		*		The clear function of the data object clears all data and content, but does not release any memory or resources.
		*
		* @return shared pointer to data object
		*/
		virtual shared_ptr<TDataClass> create() = 0;


		/**
		* convert a writable data object to a read-only data object
		*
		* @thows std::runtime if object has multiple users
		* @return shared pointer to read-only data object
		*/
		virtual shared_ptr<const TDataClass> make_const(
			shared_ptr<TDataClass>& data	///< [in/moved] shared pointer to a writeable data object (ownership is moved)
		) const = 0;
		
		
		/**
		* explicitely release allocated object
		* This function returns the ownership of an object to the allocator.
		*/
		virtual void initiateRelease(
			shared_ptr<const TDataClass>& dataConst ///< [in/moved] shared pointer to read-only data object (ownership is moved)
		) = 0;


	};

	/**
	 * generic storage reader interface for a dedicated config / worker
	 */
	template <class TDataClass>
	class IStore_Read
	{
	public:
		/**
		* virtual desctuctor
		*/
		virtual ~IStore_Read() {};

		/**
		 * get the data range of the store
		 * @note This function is MANDATORY.
		 * @return DataRange object with index and timespan range
		 */
		virtual DataRange getDataRange() const = 0;

		/**
		 * get configID of store
		 * @note This function is MANDATORY.
		 *
		 * @return current configID of store
		 */
		virtual const id_t& getConfigID() const = 0;

		/**
		 * get a single object by ID
		 * @note This function is MANDATORY.
		 */
		virtual shared_ptr<const TDataClass> getByID (	
			const id_t& id	///< [in] object ID
		) = 0;

		/**
		 * get a single object by index
		 * @note This function is MANDATORY.
		 */
		virtual shared_ptr<const TDataClass> getByIndex(
			const int64_t index	///< [in] object index
		) = 0;

		/**
		 * get multiple objects by index range
		 * @note This function is MANDATORY.
		 *
		 * @return vector to shared pointer of data objects
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getByIndexRange(
			const int64_t start,	///< [in] index of first object 
			const int64_t end		///< [in] index of last object
		) = 0;

		/**
		 * get multiple objects by timestamp
		 * @note This function is MANDATORY.
		 *
		 * @return vector of shared pointers to data objects
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getByTimestamp(
			const timestamp_t timestamp		///< [in] timestamp
		) = 0;

		/**
		 * get multiple objects at previous timestamp
		 * @note This function is MANDATORY.
		 *
		 * @return vector of shared pointers to data objects
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getBeforeTimestamp(
			const timestamp_t timestamp		///< [in] timestamp
		) = 0;

		/**
		 * get multiple objects at next timestamp
		 * @note This function is MANDATORY.
		 *
		 * @return vector of shared pointers to data objects
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getAfterTimestamp(
			const timestamp_t timestamp		///< [in] timestamp
		) = 0;

		/**
		 * get multiple objects by index range
		 * @note This function is MANDATORY.
		 *
		 * @return vector of shared pointers to data objects
		 */
		virtual std::vector< shared_ptr<const TDataClass> > getAllInTimespan(
			const timestamp_t start,		///< [in] start of search time span
			const timestamp_t end			///< [in] end of search time span
		) = 0;

		/**
		 * get list of all IDs in ringbuffer
		 * @note This function is MANDATORY.
		 *
		 * @return ids
		 */
		virtual std::vector<id_t> getIDList() = 0;
	};

	/**
	 * generic storage writer interface for a dedicated config / worker
	 * This interface also inherents the reader interface.
	 */
	template <class TDataClass>
	class IStore_Read_Factory
	{
	public:
		/**
		* virtual desctuctor
		*/
		virtual ~IStore_Read_Factory() {};

		/**
		* creates a new store
		 * @note This function is MANDATORY.
		*/
		shared_ptr< IStore_Read<TDataClass> > create(
			const id_t configID	= ID_NULL	///< [in] config ID of requested store (optional)
		) = 0;
	};

	/**
	 * generic storage writer interface for a dedicated config / worker
	 * This interface also inherents the reader interface.
	 */
	template <class TDataClass>
	class IStore_ReadWrite : public IStore_Read<TDataClass>, public IDataAllocator<TDataClass>
	{
	public:
		/**
		* virtual desctuctor
		*/
		virtual ~IStore_ReadWrite() {};

		/**
		* convert a writable data object to a read-only data object
		*
		* @thows std::runtime if object has multiple users
		* @return shared pointer to read-only data object
		*/
		virtual shared_ptr<const TDataClass> make_const(
			shared_ptr<TDataClass>& data	///< [in] shared pointer to a writeable data object (ownership is moved)
		) const = 0;
		

		/**
		 * save a single object
		 * The ID of the data object has to be set in advance.
		 * @note This function is MANDATORY.
		 *
		 * @return id of saved object
		 */
		virtual id_t save_const(
			const shared_ptr<const TDataClass>& data	///< [in] shared pointer to read-only data object
		) = 0;

		/**
		 * save a single object
		 * The ID of the data object has to be set in advance.
		 * @note This function is MANDATORY.
		 *
		 * @return id of saved object
		 */
		virtual id_t save_move(
			shared_ptr<TDataClass>& data	///< [in] shared pointer data object (ownership is moved)
		)
		{
			return save_const( make_const(data) );
		}

		/**
		 * save a single object
		 * The ID of the data object has to be set in advance.
		 * @note This function is MANDATORY.
		 *
		 * @return id of saved object
		 */
		virtual id_t save_copy(
			shared_ptr<TDataClass>& data	///< [in] shared pointer data object (ownership is moved)
		)
		{
			if ( !data )
				throw ConnectedVision::runtime_error("save_copy() data are NULL");
			ConnectedVision::shared_ptr<TDataClass> clone( new TDataClass( *data ) );
			return save_const( make_const(clone) );
		}

		/**
		 * save multiple objects as bulk save
		 * The ID of the data objects has to be set in advance.
		 * @note This function is MANDATORY.
		 *
		 * @return vector of object IDs
		 */
		virtual std::vector<id_t> save_constVector(
			const std::vector< shared_ptr<const TDataClass> >& data	///< [in] vector of shared pointers to read-only data objects
		) = 0;

		/**
		 * delete all objects in this store
		 * @note This function is MANDATORY.
		 */
		virtual void deleteAll() = 0;

		/**
		 * delete a single object by ID
		 * @note This function is MANDATORY.
		 */
		virtual void deleteByID (	
			const id_t& id	///< [in] object ID
		) = 0;
	};

	/**
	 * generic storage writer interface for a dedicated config / worker
	 * This interface also inherents the reader interface.
	 */
	template <class TDataClass>
	class IStore_ReadWrite_Factory
	{
	public:
		/**
		* virtual desctuctor
		*/
		virtual ~IStore_ReadWrite_Factory() {};

		/**
		* creates a new store
		 * @note This function is MANDATORY.
		*/
		virtual shared_ptr< IStore_ReadWrite<TDataClass> > create(
			const id_t configID	= ID_NULL	///< [in] config ID of requested store (optional)
		) = 0;
	};

	/**
	 * store manager handles all stores over all configs / workers
	 */
	template <class TDataClass>
	class IStore_Manager
	{
	public:
		virtual ~IStore_Manager() {};

		/**
		 * get a reader store for a given config
		 * @note This function is MANDATORY.
		 */
		virtual shared_ptr< IStore_Read<TDataClass> > getReadStore(
			const id_t configID		///< [in] config ID of requested store
		) = 0;

		/**
		 * get a reader/writer store for a given config
		 * @note This function is MANDATORY.
		 */
		virtual shared_ptr< IStore_ReadWrite<TDataClass> > getReadWriteStore(
			const id_t configID		///< [in] config ID of requested store
		) = 0;

	};

} // namespace Store

} // namespace ConnectedVision

#endif // IStore_def
