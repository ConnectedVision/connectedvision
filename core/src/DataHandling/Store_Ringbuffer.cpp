/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Ringbuffer_code
#define Store_Ringbuffer_code
//#ifdef Store_Ringbuffer_def

#include "Store_Ringbuffer.h"
#include "DataAllocator_Primitive.h"
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace ConnectedVision 
{ namespace DataHandling
{

#define MUTEX_TIMEOUT					10
#define CREATE_READ_LOCK(lock, mutex)	Store_Ringbuffer<TDataClass>::ReadLock (lock)((mutex), boost::get_system_time() + boost::posix_time::milliseconds(MUTEX_TIMEOUT) ); \
										if ( !(lock) ) throw ConnectedVision::runtime_error("mutex cannot be locked (timeout)");
#define CREATE_WRITE_LOCK(lock, mutex)	Store_Ringbuffer<TDataClass>::WriteLock (lock)((mutex), boost::get_system_time() + boost::posix_time::milliseconds(MUTEX_TIMEOUT) ); \
										if ( !(lock) ) throw ConnectedVision::runtime_error("mutex cannot be locked (timeout)");

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Store_Ringbuffer
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <IConnectedVisionDataClass TDataClass>
Store_Ringbuffer<TDataClass>::Store_Ringbuffer(const ConnectedVision::id_t& configID, const int64_t size) :
	configID(configID),
	bufferSize(size), 
	container((size_t)size), 
	dataAllocator( ConnectedVision::make_shared< DataAllocator_Primitive<TDataClass> >() )
{
	this->init();
}

template <IConnectedVisionDataClass TDataClass>
Store_Ringbuffer<TDataClass>::Store_Ringbuffer(const ConnectedVision::id_t& configID, const int64_t size, ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > allocator) :
	configID(configID),
	bufferSize(size), 
	container((size_t)size), 
	dataAllocator( allocator )
{
	if ( !dataAllocator )
		throw ConnectedVision::runtime_error("allocator is not initialized");
	this->init();
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<TDataClass> Store_Ringbuffer<TDataClass>::create()
{
	ConnectedVision::shared_ptr<TDataClass> data = dataAllocator->create();
	if ( data )
	{
		data->set_configID( this->configID );
	}
	return data;
}


template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<const TDataClass> Store_Ringbuffer<TDataClass>::make_const(ConnectedVision::shared_ptr<TDataClass>& data) const
{
	return dataAllocator->make_const(data);
}
		
template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer<TDataClass>::initiateRelease(ConnectedVision::shared_ptr<const TDataClass>& dataConst)
{
	dataAllocator->initiateRelease(dataConst);
}

template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer<TDataClass>::init()
{
	CREATE_WRITE_LOCK(lock, containerMutex);

	// clear lookup tables
	idLookup.clear();
	timestampLookup.clear();

	// reset all elements in container
	for (auto it = this->container.begin(); it != this->container.end(); ++it)
	{
		it->reset();
	}

	// buffer handling
	this->bufferFirstPos = -1;
	this->bufferLastPos = -1;

	// indizes
	this->startIndex = 0;
	this->firstIndex = -1;
	this->lastIndex = -1;
}

template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer<TDataClass>::rebuildLookup(typename Store_Ringbuffer<TDataClass>::WriteLock& lock)
{
	// clear lookup tables
	idLookup.clear();
	timestampLookup.clear();

	if ( this->bufferFirstPos < 0 )
		return;

	// fill lookup tables
	size_t pos = this->bufferFirstPos;
	int64_t remaining = this->lastIndex - this->firstIndex +1;
	while ( remaining > 0 )
	{
		auto& dataRef = this->container.at(pos);

		// id lookup
		this->idLookup[ dataRef->getconst_id() ] = &dataRef;
		// timestamp lookup
		this->timestampLookup.insert( std::pair<timestamp_t, element_t*>(dataRef->getconst_timestamp(), &dataRef) );

		pos = (pos + 1) % this->bufferSize; // wrap around ring buffer
		remaining--;
	}
}

template <IConnectedVisionDataClass TDataClass>
typename Store_Ringbuffer<TDataClass>::Stats Store_Ringbuffer<TDataClass>::getStats() const
{
	Store_Ringbuffer<TDataClass>::Stats stats;

	// lock data container
	CREATE_READ_LOCK(lock, containerMutex);

	stats.size = this->container.size();
	if ( this->bufferFirstPos >= 0 )
	{
		stats.entriesUsed = this->bufferLastPos - this->bufferFirstPos +1;
		if ( stats.entriesUsed <= 0 )
			stats.entriesUsed += stats.size;
	}
	else
		stats.entriesUsed = 0;

	stats.firstIndex = this->firstIndex;
	stats.lastIndex = this->lastIndex;

	if ( this->bufferFirstPos < 0 )
	{
		// container is empty
		stats.firstTimestamp = -1;
		stats.lastTimestamp = -1;
	}
	else
	{
		// get actual timestamps from data objects
		stats.firstTimestamp = (*this->timestampLookup.begin()->second)->getconst_timestamp();
		stats.lastTimestamp = (*this->timestampLookup.rbegin()->second)->getconst_timestamp();
	}

	return stats;	// If the return type equals the definded return type exactly, the object is moved instead of copied.
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::id_t Store_Ringbuffer<TDataClass>::save_const( const ConnectedVision::shared_ptr<const TDataClass>& data)
{
	if ( !data )
		throw ConnectedVision::runtime_error("try to save NULL object");

	// check object ID
	if ( data->getconst_id() == ID_NULL )
		throw ConnectedVision::runtime_error("object ID is not set");

	// check configID
	if ( this->configID != data->getconst_configID() )
	{
		throw ConnectedVision::runtime_error( "configID not set correctly for object ID: " + IDToStr(data->getconst_id()) + 
									" was set to: " + IDToStr(data->getconst_configID()) +
									" should be: " + IDToStr(this->configID) );
	}

	// lock data container
	CREATE_WRITE_LOCK(lock, containerMutex);

#ifdef _DEBUG
	// check external locking
	if ( lock.mutex() != &this->containerMutex )
		throw ConnectedVision::runtime_error("wrong mutex locked");
#endif

	// test id to be unique
	auto it = this->idLookup.find( data->getconst_id() );
	if ( it != this->idLookup.end() )
	{
		// element with same ID is already in ringbuffer -> overwrite
		auto& oldDataRef = *it->second;

		// add new element to container
		*it->second = data;

		// update lookup tables
		auto& dataRef = *it->second;
		// id lookup
		this->idLookup[ dataRef->getconst_id() ] = &dataRef;
		// timestamp lookup
		std::pair<typename timestampLookup_t::const_iterator, typename timestampLookup_t::const_iterator> range = this->timestampLookup.equal_range( oldDataRef->getconst_timestamp() );
		for ( auto it = range.first; it != range.second;) // we cannot increment the iterator in the for() statement, since we have to do it before we remove any elements
		{
			if ( it->second == NULL || it->second == &oldDataRef || !(*it->second) )
			{
				// remove the corresponding element only, and not remove all elements with that timestamp
				auto tmp = it; // make copy of iterator to safely remove element
				++it;
				this->timestampLookup.erase( tmp );
			}
			else
			{
				// this was not the element to be removed -> increment iterator
				++it;
			}
		}
		this->timestampLookup.insert( std::pair<timestamp_t, element_t*>(dataRef->getconst_timestamp(), &dataRef) );

		return dataRef->getconst_id();
	}

	// calculate position of new element
	int64_t pos = (this->bufferLastPos + 1) % this->bufferSize; // wrap around ring buffer

	// remove old element first
	// update lookup tables
	auto& oldDataRef = this->container.at((size_t)pos);
	if ( oldDataRef )
	{
		this->firstIndex++;
		this->bufferFirstPos = (this->bufferFirstPos + 1) % this->bufferSize; // wrap around ring buffer

		// id lookup
		this->idLookup.erase( oldDataRef->getconst_id() );

		// timestamp lookup
		std::pair<typename timestampLookup_t::const_iterator, typename timestampLookup_t::const_iterator> range = this->timestampLookup.equal_range( oldDataRef->getconst_timestamp() );
		for ( auto it = range.first; it != range.second;) // we cannot increment the iterator in the for() statement, since we have to do it before we remove any elements
		{
			if ( it->second == NULL || it->second == &oldDataRef || !(*it->second) )
			{
				// remove the corresponding element only, and not remove all elements with that timestamp
				auto tmp = it; // make copy of iterator to safely remove element
				++it;
				this->timestampLookup.erase( tmp );
			}
			else
			{
				// this was not the element to be removed -> increment iterator
				++it;
			}
		}
	}

	// add new element to container
	this->container.at((size_t)pos) = data;

	// bookkeeping of container
	this->bufferLastPos = pos;
	if ( this->bufferFirstPos < 0 )
		this->bufferFirstPos = pos;
	if ( this->firstIndex < 0 || this->lastIndex < 0 ) 
	{
		this->firstIndex = this->startIndex;
		this->lastIndex = this->startIndex;
	}
	else
	{
		this->lastIndex++;
	}

	// update lookup tables
	auto& dataRef = this->container.at((size_t)pos);
	// id lookup
	this->idLookup[ dataRef->getconst_id() ] = &dataRef;
	// timestamp lookup
	this->timestampLookup.insert( std::pair<timestamp_t, element_t*>(dataRef->getconst_timestamp(), &dataRef) );

	// return ID
	return dataRef->getconst_id();
}

template <IConnectedVisionDataClass TDataClass>
std::vector<ConnectedVision::id_t> Store_Ringbuffer<TDataClass>::save_constVector(const std::vector< ConnectedVision::shared_ptr<const TDataClass> >& dataContainer)
{
	std::vector<ConnectedVision::id_t> idList;
	for ( auto it = dataContainer.begin(); it != dataContainer.end(); ++it)
	{
		this->save_const( *it );
		idList.push_back( (*it)->getconst_id() );
	}

	return idList;
}

template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer<TDataClass>::resetIndex(const int64_t index)
{ 
	this->deleteAll();

	// set start index
	this->startIndex = index;
};

template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer<TDataClass>::deleteAll()
{ 
	this->init();
};

template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer<TDataClass>::deleteByID(const ConnectedVision::id_t& id)
{ 
	// lock data container
	CREATE_WRITE_LOCK(lock, containerMutex);

#ifdef _DEBUG
	// check external locking
	if ( lock.mutex() != &this->containerMutex )
		throw ConnectedVision::runtime_error("wrong mutex locked");
#endif

	// find element in ringbuffer
	int64_t pos = this->bufferFirstPos;
	int64_t oldPos = -1;
	int64_t remaining = this->lastIndex - this->firstIndex +1;
	bool found = false;
	while ( remaining > 0 && !found )
	{
		if ( this->container.at((size_t)pos)->getconst_id() == id )
		{
			found = true;
		}
		else
		{
			oldPos = pos;
			pos = (pos + 1) % this->bufferSize; // wrap around ring buffer
		}
		remaining--;
	}
	if ( !found )
	{
		// nothing to do
		return;
	}

	if ( this->bufferFirstPos == this->bufferLastPos )
	{
		// we delete the only element
		this->init();
		return;
	}

	// return to allocator
	this->initiateRelease( this->container.at((size_t)pos) );

	// move other elements
	while ( remaining > 0 )
	{
		oldPos = pos;
		pos = (pos + 1) % this->bufferSize; // wrap around ring buffer
		this->container.at((size_t)oldPos) = this->container.at((size_t)pos);
		remaining--;
	}

	// release remains from last moved element
	this->container.at((size_t)pos).reset();

	// position update
	this->bufferLastPos = oldPos;

	// index update
	this->lastIndex--;

	// update lookup tables
	this->rebuildLookup(lock);
}

template <IConnectedVisionDataClass TDataClass>
DataRange Store_Ringbuffer<TDataClass>::getDataRange() const
{
	DataRange range;
	auto stats = getStats();
	range.indexStart = stats.firstIndex; //this->firstIndex;
	range.indexEnd = stats.lastIndex; //this->lastIndex;
	range.timestampStart = stats.firstTimestamp;
	range.timestampEnd = stats.lastTimestamp;
	return(range);
}

template <IConnectedVisionDataClass TDataClass>
const ConnectedVision::id_t& Store_Ringbuffer<TDataClass>::getConfigID() const
{
	return this->configID;
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<const TDataClass> Store_Ringbuffer<TDataClass>::getByID(const ConnectedVision::id_t& id)
{
	ConnectedVision::shared_ptr<const TDataClass> ret;

	// lock data container
	// (Even for index calculation, it does no good if we calculate outdated position data.)
	CREATE_READ_LOCK(lock, containerMutex);

	auto it = idLookup.find(id);
	if ( it == idLookup.end() )
	{
		ret.reset();
		return ret;
	}

	// return data element
	ret = *it->second;
	return ret;
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<const TDataClass> Store_Ringbuffer<TDataClass>::getByIndex(const int64_t index)
{
	ConnectedVision::shared_ptr<const TDataClass> ret;

	// lock data container
	// (Even for index calculation, it does no good if we calculate outdated position data.)
	CREATE_READ_LOCK(lock, containerMutex);

	// do range check
	if ( index < this->firstIndex || index > this->lastIndex )
	{
		ret.reset();
		return ret;
	}

	// compute offset to ringbuffer index
	int64_t off = index - this->firstIndex;

	// compute position in ringbuffer
	int64_t pos = (this->bufferFirstPos + off) % container.size();

	// return container element
	ret = container.at((size_t)pos);
	return ret;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< ConnectedVision::shared_ptr<const TDataClass> > Store_Ringbuffer<TDataClass>::getByIndexRange(const int64_t start, const int64_t end)
{
	// sanity check
	if ( start > end )
		throw ConnectedVision::runtime_error("Store_Ringbuffer<TDataClass>::getByIndexRange: start index (" + intToStr(start) + ") is greather than end index (" + intToStr(end) + ")");

	// reserve return vector
	std::vector< ConnectedVision::shared_ptr<const TDataClass> > results;
	results.reserve( (size_t)(end - start +1) );

	// lock data container
	// (Even for index calculation, it does no good if we calculate outdated position data.)
	CREATE_READ_LOCK(lock, this->containerMutex);

	// do range check
	if ( end < this->firstIndex || start > this->lastIndex )
	{
		results.clear();
		return results;
	}

	int64_t size = this->container.size();

	// compute ringbuffer start position
	int64_t startPos = start - this->firstIndex;
	if ( startPos < 0 )
		startPos = 0;
	startPos += this->bufferFirstPos;
	if ( startPos >= size )
		startPos -= size;

	// compute ringbuffer end position
	int64_t endPos = end - this->firstIndex;
	endPos += this->bufferFirstPos;
	if ( end > this->lastIndex )
		endPos = this->bufferLastPos;
	if ( endPos >= size )
		endPos -= size;

	// return container element
	if ( startPos > endPos )
	{
		// wrapped ring buffer
		results.insert(results.end(), this->container.begin() + (size_t)startPos, this->container.end() );
		results.insert(results.end(), this->container.begin(), this->container.begin() + (size_t)endPos +1);
	}
	else
	{
		// straight forward
		results.insert(results.end(), this->container.begin() + (size_t)startPos, this->container.begin() + (size_t)endPos +1);
	}
	return results;
}

template <IConnectedVisionDataClass TDataClass>
std::vector<ConnectedVision::id_t> Store_Ringbuffer<TDataClass>::getIDList()
{
	std::vector<ConnectedVision::id_t> idList;

	// lock data container
	// (Even for index calculation, it does no good if we calculate outdated position data.)
	CREATE_READ_LOCK(lock, this->containerMutex);

	if ( this->bufferFirstPos < 0 )
		return idList;

	int64_t i = this->bufferFirstPos;
	idList.push_back( this->container.at((size_t)i)->getconst_id() );
	do
	{
		// increment index and wrap around ringbuffer
		i++;
		if ( i >= this->bufferSize )
			i = 0;

		ConnectedVision::shared_ptr<const TDataClass>& data = this->container.at((size_t)i);
		idList.push_back( data->getconst_id() );
	}
	while ( i != this->bufferLastPos );

	return idList;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< ConnectedVision::shared_ptr<const TDataClass>> Store_Ringbuffer<TDataClass>::getByTimestamp(const timestamp_t time)
{
	std::vector< ConnectedVision::shared_ptr<const TDataClass>> results;

	// lock data container
	// (Even for index calculation, it does no good if we calculate outdated position data.)
	CREATE_READ_LOCK(lock, containerMutex);

	// find all elements with given timestamp
	std::pair<typename timestampLookup_t::const_iterator, typename timestampLookup_t::const_iterator> range = this->timestampLookup.equal_range( time );
	for ( auto it = range.first; it != range.second; ++it)
	{
		results.push_back(*it->second);
	}

	// return data element
	return results;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< ConnectedVision::shared_ptr<const TDataClass>> Store_Ringbuffer<TDataClass>::getBeforeTimestamp(const timestamp_t beforeTime)
{
	// lock data container
	CREATE_READ_LOCK(lock, containerMutex);

	std::vector< ConnectedVision::shared_ptr<const TDataClass>> results;
	if ( this->bufferFirstPos < 0 )
	{
		// container is empty
		return results;
	}

	// find timestamp before
	auto it = this->timestampLookup.lower_bound( beforeTime );

	// walk back until we find an element before
	auto end = it;
	
	if ( it == this->timestampLookup.end() )
		--it;
	
	// determine the element / end of the range of elements with the first timestamp before the timestamp
	while ( it != this->timestampLookup.begin() && (*it->second)->getconst_timestamp() >= beforeTime)
	{
		end = it;
		--it;
	};
	
	if ( (*it->second)->getconst_timestamp() >= beforeTime )
		return results; // not found
	
	// determine the element / start of the range of elements with the first timestamp before the timestamp
	auto start = it;
	timestamp_t time = (*start->second)->getconst_timestamp();
	while ( time == (*it->second)->getconst_timestamp() )
	{
		start = it;
		if ( it != this->timestampLookup.begin() )
		{
			--it;
		}
		else
			break;
	}

	// make results vector
	for ( it = start; it != end; ++it)
	{
		results.push_back(*it->second);
	}

	// return empty vector
	return results;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< ConnectedVision::shared_ptr<const TDataClass>> Store_Ringbuffer<TDataClass>::getAfterTimestamp(const timestamp_t afterTime)
{
	// lock data container
	CREATE_READ_LOCK(lock, containerMutex);

	std::vector< ConnectedVision::shared_ptr<const TDataClass>> results;
	auto it = this->timestampLookup.upper_bound( afterTime );
	if ( it != this->timestampLookup.end() )
	{
		timestamp_t time = (*it->second)->getconst_timestamp();
		
		while ( it != this->timestampLookup.end() && time == (*it->second)->getconst_timestamp() )
		{
			results.push_back(*it->second);
			++it;
		}
	}

	// return data element
	return results;
}

template <IConnectedVisionDataClass TDataClass>
std::vector< ConnectedVision::shared_ptr<const TDataClass>> Store_Ringbuffer<TDataClass>::getAllInTimespan(const timestamp_t startTime, const timestamp_t endTime)
{
	// sanity check
	if ( startTime > endTime )
		throw ConnectedVision::runtime_error("Store_Ringbuffer<TDataClass>::getAllInTimespan: start time (" + intToStr(startTime) + ") is greather than end time (" + intToStr(endTime) + ")");

	// lock data container
	CREATE_READ_LOCK(lock, containerMutex);

	std::vector< ConnectedVision::shared_ptr<const TDataClass>> results;

	// find timestamp before
	auto it = this->timestampLookup.lower_bound( startTime );
	if ( it != this->timestampLookup.end() )
	{
		while ( it != this->timestampLookup.end() && (*it->second)->getconst_timestamp() <= endTime )
		{
			results.push_back(*it->second);
			++it;
		}
	}

	// return data element
	return results;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Store_Ringbuffer_Factory
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <IConnectedVisionDataClass TDataClass>
Store_Ringbuffer_Factory<TDataClass>::Store_Ringbuffer_Factory(const int64_t ringbufferSize) :
	ringbufferSize(ringbufferSize),
	dataAllocator( ConnectedVision::make_shared< DataAllocator_Primitive<TDataClass> >() )
{
	this->init();
}

template <IConnectedVisionDataClass TDataClass>
Store_Ringbuffer_Factory<TDataClass>::Store_Ringbuffer_Factory(const int64_t ringbufferSize, ConnectedVision::shared_ptr< IDataAllocator<TDataClass> > allocator) :
	ringbufferSize(ringbufferSize),
	dataAllocator( allocator )
{
	this->init();
}

template <IConnectedVisionDataClass TDataClass>
void Store_Ringbuffer_Factory<TDataClass>::init()
{
	if ( ringbufferSize <= 0 )
		throw ConnectedVision::runtime_error("ringbufferSize may not be zero or negative");
	if ( !dataAllocator )
		throw ConnectedVision::runtime_error("allocator is not initialized");
}


template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr< IStore_ReadWrite<TDataClass> > Store_Ringbuffer_Factory<TDataClass>::create(const ConnectedVision::id_t configID)
{
	return boost::static_pointer_cast< IStore_ReadWrite<TDataClass> >(ConnectedVision::make_shared< Store_Ringbuffer<TDataClass> >(configID, this->ringbufferSize, this->dataAllocator));
}

}} // namespace scope

//#endif // Store_Ringbuffer_def
#endif // Store_Ringbuffer_code
