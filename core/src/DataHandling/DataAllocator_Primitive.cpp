/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef DataAllocator_Primitive_code
#define DataAllocator_Primitive_code

#include "DataAllocator_Primitive.h"

namespace ConnectedVision 
{ namespace DataHandling
{

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<TDataClass> DataAllocator_Primitive<TDataClass>::create()
{
	ConnectedVision::shared_ptr<TDataClass> data = ConnectedVision::make_shared<TDataClass>();
	data->clear(); // reset the data object, not the pointer!
	return data;
}


template <IConnectedVisionDataClass TDataClass>
void DataAllocator_Primitive<TDataClass>::initiateRelease(ConnectedVision::shared_ptr<const TDataClass>& data)
{
	data.reset();
}

template <IConnectedVisionDataClass TDataClass>
ConnectedVision::shared_ptr<const TDataClass> DataAllocator_Primitive<TDataClass>::make_const(ConnectedVision::shared_ptr<TDataClass>& data) const
{
	if ( data.use_count() > 1 )
		throw ConnectedVision::runtime_error("save_move(): cannot move pointer if object is already shared");

	// move pointer inside ringbuffer
	// We need to make sure that the object inside the ringbuffer cannot be modified any more.
	const ConnectedVision::shared_ptr<const TDataClass> constData( std::move(data) );

	return constData;
}


}} // namespace scope


#endif // DataAllocator_Primitive_code