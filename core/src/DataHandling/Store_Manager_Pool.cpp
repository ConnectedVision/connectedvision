/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Manager_Pool_code
#define Store_Manager_Pool_code

#include "Store_Manager_Pool.h"
#include <ConnectedVision_Thread.h>

namespace ConnectedVision 
{ namespace DataHandling
{

template <IConnectedVisionDataClass TDataClass>
Store_Manager_Pool<TDataClass>::Store_Manager_Pool(const int64_t storeCount, ConnectedVision::shared_ptr< IStore_ReadWrite_Factory<TDataClass> > storeFactory) :
	storeCount(storeCount), 
	storeFactory( storeFactory )
{
	this->init();
}

template <IConnectedVisionDataClass TDataClass>
void Store_Manager_Pool<TDataClass>::init()
{
	if ( this->storeCount <= 0 )
		throw ConnectedVision::runtime_error("negative storeCount");
	if ( !this->storeFactory )
		throw ConnectedVision::runtime_error("factory is not initialized");

	this->storeMap.clear();
	this->creationIndex = 0;
}



template <IConnectedVisionDataClass TDataClass>
shared_ptr< IStore_Read<TDataClass> > Store_Manager_Pool<TDataClass>::getReadStore(const id_t configID)
{
	ConnectedVision::Lock lock(this->mapMutex);

	// search configID in map
	auto it = this->storeMap.find(configID);
	if ( it != this->storeMap.end() )
	{
		return boost::dynamic_pointer_cast< IStore_Read<TDataClass> >( it->second.store );
	}

	// remove unused store from map
	this->purgeStore(lock);

	// add new store to map
	StoreStruct storeStruct = this->createStore(configID);
	this->storeMap.insert( std::pair<id_t, StoreStruct>(configID, storeStruct) );
	return boost::dynamic_pointer_cast< IStore_Read<TDataClass> >( storeStruct.store );
}

template <IConnectedVisionDataClass TDataClass>
shared_ptr< IStore_ReadWrite<TDataClass> > Store_Manager_Pool<TDataClass>::getReadWriteStore(const id_t configID)
{
	ConnectedVision::Lock lock(this->mapMutex);

	// search configID in map
	auto it = this->storeMap.find(configID);
	if ( it != this->storeMap.end() )
	{
		return it->second.store;
	}

	// remove unused store from map
	this->purgeStore(lock);

	// add new store to map
	StoreStruct storeStruct = this->createStore(configID);
	this->storeMap.insert( std::pair<id_t, StoreStruct>(configID, storeStruct) );
	return storeStruct.store;
}

template <IConnectedVisionDataClass TDataClass>
void Store_Manager_Pool<TDataClass>::purgeStore(const ConnectedVision::Lock &lock)
{
	while ( storeMap.size() >= (unsigned)this->storeCount )
	{
		// find oldest store map entry without an active writer 
		auto remove = this->storeMap.end();
		uint64_t minIndex = this->creationIndex;
		for ( auto it = this->storeMap.begin(); it != this->storeMap.end(); ++it)
		{
			auto &s = it->second;
			if ( s.store.unique() && s.creationIndex <= minIndex )
			{
				minIndex = s.creationIndex;
				remove = it;
			}
		}

		if ( remove != this->storeMap.end() )
		{
			// remove entry
			this->storeMap.erase( remove );
		}
		else
		{
			// no such entry found
			throw ConnectedVision::runtime_error("no free space in storeMap");
		}
	}
}

template <IConnectedVisionDataClass TDataClass>
typename Store_Manager_Pool<TDataClass>::StoreStruct Store_Manager_Pool<TDataClass>::createStore(const id_t configID)
{
	Store_Manager_Pool<TDataClass>::StoreStruct storeStruct;
	storeStruct.store = this->storeFactory->create(configID);
	storeStruct.creationIndex = ++creationIndex;
	return storeStruct;
}

}} // namespace scope

#endif // Store_Manager_Pool_code