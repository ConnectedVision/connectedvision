/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_Manager_Basic_def
#define Store_Manager_Basic_def

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
 * store manager handles all stores over all configs / workers
 *
 * The basic store manager keeps a map of all active stores (configs) and
 * discards stores when they are no longer in use.
 */
template <IConnectedVisionDataClass TDataClass>
class Store_Manager_Basic : public IStore_Manager<TDataClass>
{
public:

	/**
	* constructor
	*/
	Store_Manager_Basic(
		ConnectedVision::shared_ptr< IStore_ReadWrite_Factory<TDataClass> > storeFactory	///< [in] store factory
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Basic() {}

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

	/**
	* purge all unused stores in the store map
	*/
	virtual void purgeStore();

 protected:

	/**
	* do parameter check and init store manager
	*/
	virtual void init();

	/**
	* purge all unused stores in the store map
	*/
	virtual void purgeStore(
		const ConnectedVision::Lock &lock		///< [in] prove that store map is locked
	);

	ConnectedVision::mutex mapMutex;
	std::map< id_t, shared_ptr<IStore_ReadWrite<TDataClass>> > storeMap;

	const ConnectedVision::shared_ptr< IStore_ReadWrite_Factory<TDataClass> > storeFactory;

};

}}

// include source code: template inclusion model
#include "Store_Manager_Basic.cpp"

#endif // Store_Manager_Basic_def


