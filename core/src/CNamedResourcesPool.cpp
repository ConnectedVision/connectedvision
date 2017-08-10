/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef CNamedResourcesPool_code
#define CNamedResourcesPool_code

#include "CNamedResourcesPool.h"

#include "helper.h"

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/thread/thread_time.hpp>

namespace ConnectedVision {

typedef boost::interprocess::scoped_lock<boost::timed_mutex> CNamedResourcesPool_lock;
#define timeout(x)	( boost::get_system_time()+ boost::posix_time::milliseconds( (x) ) )

template <typename T_key, typename T_resource>
CNamedResourcesPool<T_key, T_resource>::CNamedResourcesPool()
{
	this->clear();
}

template <typename T_key, typename T_resource>
CNamedResourcesPool<T_key, T_resource>::~CNamedResourcesPool()
{

}

template <typename T_key, typename T_resource>
void CNamedResourcesPool<T_key, T_resource>::clear()
{
	this->resourceMap.clear();
	this->tickcount = 1;
}

template <typename T_key, typename T_resource>
void CNamedResourcesPool<T_key, T_resource>::add( T_resource *resource, T_key key )
{
	CNamedResourcesData<T_resource> data( resource );

	// lock resources pool
	CNamedResourcesPool_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		throw CNamedResourcesPool_exception( "CNamedResourcesPool: cannot lock resources pool (mutex timeout)" );	
	}

	this->resourceMap.insert( std::pair<T_key, CNamedResourcesData<T_resource> > (key, data) );
}

template <typename T_key, typename T_resource>
void CNamedResourcesPool<T_key, T_resource>::add( boost::shared_ptr< T_resource > resource, T_key key )
{
	CNamedResourcesData<T_resource> data( resource );

	// lock resources pool
	CNamedResourcesPool_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		throw CNamedResourcesPool_exception( "CNamedResourcesPool: cannot lock resources pool (mutex timeout)" );	
	}

	this->resourceMap.insert( std::pair<T_key, CNamedResourcesData<T_resource> > (key, data) );
}

template <typename T_key, typename T_resource>
boost::shared_ptr< T_resource > CNamedResourcesPool<T_key, T_resource>::request()
{
	// lock resources pool
	CNamedResourcesPool_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		throw CNamedResourcesPool_exception( "CNamedResourcesPool: cannot lock resources pool (mutex timeout)" );	
	}

	boost::shared_ptr< T_resource > ptr( this->searchFree( this->resourceMap.begin(), this->resourceMap.end() ) );

	lock.unlock();
	return ptr;
}

template <typename T_key, typename T_resource>
boost::shared_ptr< T_resource > CNamedResourcesPool<T_key, T_resource>::request( T_key key )
{
	// lock resources pool
	CNamedResourcesPool_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		throw CNamedResourcesPool_exception( "CNamedResourcesPool: cannot lock resources pool (mutex timeout)" );	
	}

	std::pair< typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator, typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator > range;
	range = this->resourceMap.equal_range( key );
	boost::shared_ptr< T_resource > ptr( this->searchFree( range.first, range.second ) );

	lock.unlock();
	return ptr;
}

template <typename T_key, typename T_resource>
boost::shared_ptr< T_resource > CNamedResourcesPool<T_key, T_resource>::searchFree( typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator begin, typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator end )
{
	// the mutex should be already locked before entering this function
	if ( this->mutex.try_lock() )
	{
		this->mutex.unlock();
		throw CNamedResourcesPool_exception( "CNamedResourcesPool::resetTicks: mutex has to be locked in advance" );	
	}

	typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator it;
	typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator match = end;
	boost::shared_ptr< T_resource > ptr;
	int oldestTickCount = CNamedResourcesPool<T_key, T_resource>::maxTickCount;

	// search all matching resources
    for (it = begin; it != end; ++it)
	{
		// free resource found
		if ( it->second.ptr.use_count() == 1 && it->second.ticksLastRequest <= oldestTickCount )
		{
			match = it;
			oldestTickCount = match->second.ticksLastRequest;
		}
	}

	// free resource found -> increase tickcount
	if ( match != end )
	{
		match->second.ticksLastRequest = this->tickcount;
		ptr = match->second.ptr;
		this->tickcount++;

		if ( this->tickcount >= this->maxTickCount )
			this->resetTicks();
	}

	return ptr;
}

template <typename T_key, typename T_resource>
void CNamedResourcesPool<T_key, T_resource>::resetTicks()
{
	// the mutex should be already locked before entering this function
	if ( this->mutex.try_lock() )
	{
		this->mutex.unlock();
		throw CNamedResourcesPool_exception( "CNamedResourcesPool::resetTicks: mutex has to be locked in advance" );	
	}

	typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator it;
    for (it = this->resourceMap.begin(); it != this->resourceMap.end(); ++it)
	{
		it->second.ticksLastRequest = 0;
	}
	this->tickcount = 1;
}


template <typename T_key, typename T_resource>
void CNamedResourcesPool<T_key, T_resource>::remap( boost::shared_ptr< T_resource > ptr, T_key key )
{
	typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator it;

	// lock resources pool
	CNamedResourcesPool_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		throw CNamedResourcesPool_exception( "CNamedResourcesPool: cannot lock resources pool (mutex timeout)" );	
	}

	// find resource
    for (it = this->resourceMap.begin() ; it != this->resourceMap.end(); ++it)
	{
		CNamedResourcesData<T_resource> data = it->second;

		if ( data.ptr == ptr )
		{
			// resource found
			// remove from map
			this->resourceMap.erase( it );

			// insert at new position
			this->resourceMap.insert( std::pair<T_key, CNamedResourcesData<T_resource> > (key, data) );

			return;
		}
	}

	throw ConnectedVision::out_of_range("not found");
}

template <typename T_key, typename T_resource>
void CNamedResourcesPool<T_key, T_resource>::remove( boost::shared_ptr< T_resource > ptr )
{
	typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator it;

	// lock resources pool
	CNamedResourcesPool_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		throw CNamedResourcesPool_exception( "CNamedResourcesPool: cannot lock resources pool (mutex timeout)" );	
	}

	// find resource
    for (it = this->resourceMap.begin() ; it != this->resourceMap.end(); ++it)
	{
		CNamedResourcesData<T_resource> data = it->second;

		if ( data.ptr == ptr )
		{
			// resource found
			// remove from map
			this->resourceMap.erase( it );

			return;
		}
	}

	throw ConnectedVision::out_of_range("not found");
}

} //namespace ConnectedVision

#endif // CNamedResourcesPool_code