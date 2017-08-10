/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_Manager_Dynamic_def
#define Store_Manager_Dynamic_def

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

template <IConnectedVisionDataClass TDataClass>
class IStore_Manager_Dynamic_Selector
{
public:

	/**
	* select the store manager for a given config
	*
	* @return store manager for config
	*/
	virtual shared_ptr< IStore_Manager<TDataClass> > selectStoreManager(
		const id_t configID		///< [in] config ID of requested store
	) = 0;
};

/**
 * store manager handles all stores over all configs / workers
 *
 * The basic store manager keeps a map of all active stores (configs) and
 * discards stores when they are no longer in use.
 */
template <IConnectedVisionDataClass TDataClass>
class Store_Manager_Dynamic : public IStore_Manager<TDataClass>
{
public:

	/**
	* constructor
	*/
	Store_Manager_Dynamic(
		shared_ptr< IStore_Manager_Dynamic_Selector<TDataClass> > selector	///< [in] selector class instance
	);

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Dynamic() {}

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

	/// selector class instance
	shared_ptr< IStore_Manager_Dynamic_Selector<TDataClass> > selector;
};

}}

// include source code: template inclusion model
#include "Store_Manager_Dynamic.cpp"

#endif // Store_Manager_Dynamic_def


