/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Manager_Basic_code
#define Store_Manager_Basic_code

#include <list>

#include "Store_Manager_Basic.h"

#include <ConnectedVision_Thread.h>

namespace ConnectedVision 
{ namespace DataHandling
{
template <IConnectedVisionDataClass TDataClass>
Store_Manager_Basic<TDataClass>::Store_Manager_Basic(ConnectedVision::shared_ptr< IStore_ReadWrite_Factory<TDataClass> > storeFactory) :
	storeFactory( storeFactory )
{
	this->init();
}

template <IConnectedVisionDataClass TDataClass>
void Store_Manager_Basic<TDataClass>::init()
{
	if ( !this->storeFactory )
		throw ConnectedVision::runtime_error("factory is not initialized");

	this->storeMap.clear();
}



template <IConnectedVisionDataClass TDataClass>
shared_ptr< IStore_Read<TDataClass> > Store_Manager_Basic<TDataClass>::getReadStore(const id_t configID)
{
	return boost::dynamic_pointer_cast< IStore_Read<TDataClass> >( this->getReadWriteStore(configID) );
}

template <IConnectedVisionDataClass TDataClass>
shared_ptr< IStore_ReadWrite<TDataClass> > Store_Manager_Basic<TDataClass>::getReadWriteStore(const id_t configID)
{
	ConnectedVision::Lock lock(this->mapMutex);
	shared_ptr< IStore_ReadWrite<TDataClass> > store;

	// search configID in map
	auto it = this->storeMap.find(configID);
	if ( it != this->storeMap.end() )
	{
		store = it->second;
	}

	// remove unused stores from map
	this->purgeStore(lock);

	// add new store to map
	if ( !store )
	{
		store = this->storeFactory->create(configID);
		this->storeMap.insert( std::pair<id_t, shared_ptr<IStore_ReadWrite<TDataClass>> >(configID, store) );
	}

	return store;
}

template <IConnectedVisionDataClass TDataClass>
void Store_Manager_Basic<TDataClass>::purgeStore()
{
	ConnectedVision::Lock lock(this->mapMutex);
	this->purgeStore(lock);
}

template <IConnectedVisionDataClass TDataClass>
void Store_Manager_Basic<TDataClass>::purgeStore(const ConnectedVision::Lock &lock)
{
	// get list of unused stores
	std::list< id_t > unusedStoreConfigIDs;
	for ( auto it = this->storeMap.begin(); it != this->storeMap.end(); ++it)
	{
		auto &s = it->second;
		if ( s.unique() )
		{
			unusedStoreConfigIDs.push_back( it->first );
		}
	}

	// remove unused stores
	for ( auto it = unusedStoreConfigIDs.begin(); it != unusedStoreConfigIDs.end(); ++it )
	{
		this->storeMap.erase( *it );
	}
}

}} // namespace scope

#endif // Store_Manager_Basic_code