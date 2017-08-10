/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_Manager_Pool_def
#define Store_Manager_Pool_def

#include <stdint.h>
#include <string>
#include <iterator>
#include <vector>
#include <map>
#include <boost/thread.hpp>

#include <general.h>
#include <IStore.h>
#include <ConnectedVision_Thread.h>

#define IConnectedVisionDataClass	class

namespace ConnectedVision 
{ namespace DataHandling
{

/**
 * store manager handles all stores over all configs / workers
 *
 * The pool manager keeps a pool of active and recently used stores (configs).
 * Unused stores are kept in the pool until the space is required by a newly created store.
 */
template <IConnectedVisionDataClass TDataClass>
class Store_Manager_Pool : public IStore_Manager<TDataClass>
{
public:

	/**
	* constructor
	*/
	Store_Manager_Pool(
		const int64_t storeCount,			///< [in] number of stores in manager
		ConnectedVision::shared_ptr< IStore_ReadWrite_Factory<TDataClass> > storeFactory	///< [in] store factory
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Pool() {}

	/**
	* get a reader store for a given config
	* @note This function is MANDATORY.
	*/
	virtual shared_ptr< IStore_Read<TDataClass> > getReadStore(
		const id_t configID		///< [in] config ID of requested store
	);

	/**
		* get a reader/writer store for a given config
		* @note This function is MANDATORY.
		*/
	virtual shared_ptr< IStore_ReadWrite<TDataClass> > getReadWriteStore(
		const id_t configID		///< [in] config ID of requested store
	);

 protected:

	/**
	* internal structure of store map
	*/
	typedef struct
	{
		uint64_t creationIndex;
		shared_ptr<IStore_ReadWrite<TDataClass>> store;
	} StoreStruct;
	uint64_t creationIndex;

	/**
	* do parameter check and init store manager
	*/
	virtual void init();

	/**
	* purge oldest store which is strictly not used
	* Ensure that there is one free entry in the store map.
	* If the store map has a free space, this function will do nothing.
	*/
	virtual void purgeStore(
		const ConnectedVision::Lock &lock		///< [in] prove that store map is locked
	);

	/**
	* create new store
	*
	* @return read and write store pointers
	*/
	virtual StoreStruct createStore(
		const id_t configID		///< [in] config ID of requested store
	);

	ConnectedVision::mutex mapMutex;
	std::map< id_t, StoreStruct > storeMap;

	const int64_t storeCount;
	const ConnectedVision::shared_ptr< IStore_ReadWrite_Factory<TDataClass> > storeFactory;

};

}}

// include source code: template inclusion model
#include "Store_Manager_Pool.cpp"

#endif // Store_Manager_Pool_def


