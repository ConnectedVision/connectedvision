/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Cache_code
#define Store_Cache_code

#include "Store_Cache.h"

namespace ConnectedVision {
namespace DataHandling {

#define STORE_CACHE_MUTEX_TIMEOUT				10
#define STORE_CACHE_CREATE_LOCK(_lock, _mutex)	Store_Cache<TDataClass>::CacheLock (_lock)((_mutex), boost::get_system_time() + boost::posix_time::milliseconds(STORE_CACHE_MUTEX_TIMEOUT) ); \
									if ( !(_lock) ) throw ConnectedVision::runtime_error("mutex cannot be locked (timeout)");

template<class TDataClass>
Store_Cache<TDataClass>::Store_Cache(const id_t& configID, const int64_t cacheSize, const shared_ptr< IStore_ReadWrite<TDataClass> > baseStore) :
	configID(configID), cacheSize(cacheSize), baseStore(baseStore)
{
}

template<class TDataClass>
Store_Cache<TDataClass>::~Store_Cache()
{
	this->cacheFlush();
}

template<class TDataClass>
shared_ptr<TDataClass> Store_Cache<TDataClass>::create()
{
	return this->baseStore->create();
}

template<class TDataClass>
shared_ptr<const TDataClass> Store_Cache<TDataClass>::make_const(shared_ptr<TDataClass>& data) const
{
	return this->baseStore->make_const(data);
}
		
template<class TDataClass>
void Store_Cache<TDataClass>::initiateRelease(shared_ptr<const TDataClass>& dataConst)
{
	this->baseStore->initiateRelease(dataConst);
}

template<class TDataClass>
DataRange Store_Cache<TDataClass>::getDataRange() const
{
// FIXME	this->cacheFlush();

	// TODO
	return this->baseStore->getDataRange();
}

template<class TDataClass>
const id_t& Store_Cache<TDataClass>::getConfigID() const
{
	return this->baseStore->getConfigID();
}

template<class TDataClass>
shared_ptr<const TDataClass> Store_Cache<TDataClass>::getByID(const id_t& id)
{
	// search in cache (use scoped lock)
	{
		STORE_CACHE_CREATE_LOCK(lock, cacheMutex);
		auto it = this->cache.find( id );
		if ( it != this->cache.end() )
		{
			// use cache
			shared_ptr<const TDataClass> ptr = it->second.data;	// make copy of shared pointer to explicitly increase use-count
			return ptr;
		}
	}

	// fetch from base store
	shared_ptr<const TDataClass> data = this->baseStore->getByID(id);
	if ( data )
	{
		// since we unlocked the cache in the meantime, we need to check the cache again
		STORE_CACHE_CREATE_LOCK(lock, cacheMutex);

		auto it = this->cache.find( id );
		if ( it != this->cache.end() )
		{
			// cache has been updated -> use cache
			shared_ptr<const TDataClass> ptr = it->second.data;	// make copy of shared pointer to explicitly increase use-count
			return ptr;
		}

		// add to cache
		cacheAdd(data, false, lock);
	}

	return data;
}

template<class TDataClass>
shared_ptr<const TDataClass> Store_Cache<TDataClass>::getByIndex(const int64_t index)
{
	this->cacheFlush();
	// TODO
	return this->baseStore->getByIndex(index);
	// TODO
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Cache<TDataClass>::getByIndexRange(const int64_t start,	const int64_t end)
{
	this->cacheFlush();
		// TODO
	return this->baseStore->getByIndexRange(start, end);
	// TODO
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Cache<TDataClass>::getByTimestamp(const timestamp_t timestamp)
{
	this->cacheFlush();
		// TODO
	return this->baseStore->getByTimestamp(timestamp);
	// TODO
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Cache<TDataClass>::getBeforeTimestamp(const timestamp_t timestamp)
{
	this->cacheFlush();
	// TODO
	return this->baseStore->getBeforeTimestamp(timestamp);
	// TODO
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Cache<TDataClass>::getAfterTimestamp(const timestamp_t timestamp)
{
	this->cacheFlush();
	// TODO
	return this->baseStore->getAfterTimestamp(timestamp);
	// TODO
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Cache<TDataClass>::getAllInTimespan(const timestamp_t start, const timestamp_t end)
{
	this->cacheFlush();
	// TODO
	return this->baseStore->getAllInTimespan(start, end);
	// TODO
}

template<class TDataClass>
std::vector< id_t > Store_Cache<TDataClass>::getIDList()
{
	this->cacheFlush();
	// TODO
	return this->baseStore->getIDList();
	// TODO
}

template<class TDataClass>
id_t Store_Cache<TDataClass>::save_const(const shared_ptr<const TDataClass>& data)
{
	shared_ptr<const TDataClass> writeThroughData;

	// write strategy		
	if ( this->write_through( data ) )
		writeThroughData = data;

	// save write through data
	if ( writeThroughData )
	{
		this->baseStore->save_const( writeThroughData );
	}
	
	// add to cache
	id_t id = data->getconst_id();
	this->cacheAdd(data, true);

	return id;
}

template<class TDataClass>
std::vector<id_t> Store_Cache<TDataClass>::save_constVector(const std::vector< shared_ptr<const TDataClass> >& dataList)
{
	std::vector<id_t> ids;
	std::vector< shared_ptr<const TDataClass> > writeThroughData;

	// write strategy
	for (auto it = dataList.begin(); it != dataList.end(); ++it )
	{
		auto& data = *it;
		if ( this->write_through( data ) )
			writeThroughData.push_back( data );
	}

	// save write through data
	if ( !writeThroughData.empty() )
	{
		std::vector<id_t> writeThroughIDs = this->baseStore->save_constVector( writeThroughData );

		// merge ids
		ids.reserve( ids.size() + writeThroughIDs.size() );
		ids.insert( ids.end(), writeThroughIDs.begin(), writeThroughIDs.end() );
	}

	// add to cache
	STORE_CACHE_CREATE_LOCK(lock, cacheMutex);
	for (auto it = dataList.begin(); it != dataList.end(); ++it )
	{
		auto& data = *it;
		this->cacheAdd(data, true, lock);
	}

	return ids;
}

template<class TDataClass>
void Store_Cache<TDataClass>::deleteAll()
{
	this->cacheFlush();
	// TODO
	return this->baseStore->deleteAll();
	// TODO
}

template<class TDataClass>
void Store_Cache<TDataClass>::deleteByID (const id_t& id)
{
	this->cacheFlush();
	// TODO
	return this->baseStore->deleteByID(id);
	// TODO
}

template<class TDataClass>
Store_Cache<TDataClass>::CacheItem::CacheItem() :
	modified(false)	
{ 
	timestamp = sysTime();
}

template<class TDataClass>
Store_Cache<TDataClass>::CacheItem::CacheItem(ConnectedVision::shared_ptr<const TDataClass> data, bool modified) :
	data(data), modified(modified) 
{ 
	timestamp = sysTime();
}

template<class TDataClass>
void Store_Cache<TDataClass>::cacheFlush()
{
	STORE_CACHE_CREATE_LOCK(lock, cacheMutex);

	// nothing to do on empty cache
	if ( this->cache.empty() )
		return;

	std::vector< shared_ptr<const TDataClass> > writeData;
	writeData.reserve( this->cache.size() );

	// add to cache
	for (auto it = this->cache.begin(); it != this->cache.end(); ++it )
	{
		if ( it->second.modified )
			writeData.push_back( it->second.data );
	}

	// save data
	this->baseStore->save_constVector( writeData );

	// clear cache
	this->cache.clear();
}

template<class TDataClass>
void Store_Cache<TDataClass>::cacheEvict(CacheLock& lock)
{
	// nothing to do on empty cache
	if ( this->cache.empty() )
		return;

	// search least recently used
	auto least = this->cache.begin();
	for( auto it = this->cache.begin(); it != this->cache.end(); ++it )
	{
		if ( it->second.timestamp < least->second.timestamp )
			least = it;
	}

	// save data
	this->baseStore->save_const( least->second.data );

	// remove least
	this->cache.erase( least );
}

template<class TDataClass>
void Store_Cache<TDataClass>::cacheAdd(const shared_ptr<const TDataClass>& data, bool modified)
{
	STORE_CACHE_CREATE_LOCK(lock, cacheMutex);
	return this->cacheAdd(data, modified, lock);
}

template<class TDataClass>
void Store_Cache<TDataClass>::cacheAdd(const shared_ptr<const TDataClass>& data, bool modified, CacheLock& lock)
{
	id_t id = data->getconst_id();

	// search cache for existing entry
	auto it = this->cache.find( id );

	// check for new entry
	if ( it != this->cache.end() )
	{
		// already in cache
		it->second.modified = modified;
		it->second.data = data;
		it->second.timestamp = sysTime();
	}
	else
	{
		// test capacity 
		if ( this->cache.size() >= (uint64_t)this->cacheSize )
			cacheEvict(lock);

		// add to cache
		this->cache.insert( std::make_pair(id, CacheItem(data, modified)) );
	}
}

}} // namespace scope

#endif // Store_Cache_code