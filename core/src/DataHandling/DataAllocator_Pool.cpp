/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef DataAllocator_Pool_code
#define DataAllocator_Pool_code

#include "DataAllocator_Pool.h"

namespace ConnectedVision 
{ namespace DataHandling
{
template <IConnectedVisionDataClass TDataClass>
DataAllocator_Pool<TDataClass>::DataAllocator_Pool(const int64_t size) :
	size( size )
{
	Lock lock(this->allocatorMutex);

	// build up pending list
	this->allocatedElements.clear();
	this->pendingElements.clear();
	for ( int i = 0; i < size; ++i )
	{
		ConnectedVision::shared_ptr<TDataClass> data = ConnectedVision::make_shared<TDataClass>();
		data->clear();
		ConnectedVision::shared_ptr<const TDataClass> dataConst = this->make_const(data);
		this->allocatedElements.insert(dataConst);
		this->pendingElements.insert(dataConst);
	}
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<TDataClass> DataAllocator_Pool<TDataClass>::create()
{
	Lock lock(this->allocatorMutex);

	// find first available element in pending list
	auto it = this->pendingElements.begin();
	while ( it != this->pendingElements.end() )
	{
		if ( it->use_count() == 2 ) // // 1 (for the pending list) + 1 (for the allocated elements list)
		{
			ConnectedVision::shared_ptr<TDataClass> data = this->make_writeable( *it );
			data->clear(); // reset the data object, not the pointer!
			this->pendingElements.erase(it);
			return data;
		}
		++it;
	}

	// search in allocated list if someone forgot to call initiateRelease()
	auto itAlloc = this->allocatedElements.begin();
	while ( itAlloc != this->allocatedElements.end() )
	{
		if ( itAlloc->use_count() == 1 ) // use only if there is just the pointer in the allocated list
		{
			ConnectedVision::shared_ptr<TDataClass> data = this->make_writeable( *itAlloc );
			data->clear(); // reset the data object, not the pointer!
			return data;
		}
		++itAlloc;
	}

	// not found, return NULL pointer // TODO throw exception ??????????????????????????????????????????????????????????????
	ConnectedVision::shared_ptr<TDataClass> data;
	return data;
}


template <IConnectedVisionDataClass TDataClass>
void DataAllocator_Pool<TDataClass>::initiateRelease(ConnectedVision::shared_ptr<const TDataClass>& dataConst)
{
	Lock lock(this->allocatorMutex);

	// is element in pool
	auto itAlloc = this->allocatedElements.find(dataConst);
	if ( itAlloc == this->allocatedElements.end() )
	{
		// this object does not belong to the pool
		// just reset the pointer
		dataConst.reset();
		return;
	}

	auto it = this->pendingElements.find(dataConst);
	if ( it != this->pendingElements.end() )
	{
		// object is already in pending list
		// just reset the pointer
		dataConst.reset();
		return;
	}

	// add to pending list
	this->pendingElements.insert(std::move(dataConst));
}


template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<const TDataClass> DataAllocator_Pool<TDataClass>::make_const(ConnectedVision::shared_ptr<TDataClass>& data) const
{
	if ( data.use_count() > 2 ) // 1 (for the pointer itself) + 1 (for the allocated elements list)
		throw ConnectedVision::runtime_error("save_move(): cannot move pointer if object is already shared");

	// move pointer inside ringbuffer
	// We need to make sure that the object inside the ringbuffer cannot be modified any more.
	ConnectedVision::shared_ptr<const TDataClass> constData( std::move(data) );

	return constData;
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<TDataClass> DataAllocator_Pool<TDataClass>::make_writeable(const ConnectedVision::shared_ptr<const TDataClass>& dataConst) const
{
	ConnectedVision::shared_ptr<TDataClass> data = boost::const_pointer_cast<TDataClass>(dataConst);

	return data;
}
}} // namespace scope

#endif // DataAllocator_Pool_code
