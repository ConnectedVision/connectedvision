/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Store_Manager_Ringbuffer_Pool_def
#define Store_Manager_Ringbuffer_Pool_def

#include "DataAllocator_Pool.h"
#include "Store_Ringbuffer.h"
#include "Store_Manager_Pool.h"

#define IConnectedVisionDataClass	class

namespace ConnectedVision 
{ namespace DataHandling
{

/**
	The Store_Manager_Ringbuffer_Pool is derived from the Store_Manager_Pool base class.
	It is instantiated with 
	 - Store_Ringbuffer_Factory: to create ring-buffer stores 
		(Each store is implemented as a searchable ring-buffer. 
		The data classes / ring-buffer elements are allocated via the DataAllocator instance.)
	 - DataAllocator_Pool: as allocator for data classes 
		(The data classes are managed in a global pool and reused if possible.)
 */
template <IConnectedVisionDataClass TDataClass>
class Store_Manager_Ringbuffer_Pool : public Store_Manager_Pool<TDataClass>
{
public:
	/**
	* constructor
	*	pool of ringbuffer stores with a shared object pool
	*/
	Store_Manager_Ringbuffer_Pool(
		const int64_t storeCount,			///< [in] number of stores in manager
		const int64_t ringbufferSize,		///< [in] number of element slots in ringbuffer
		const int64_t poolSize				///< [in] total number of available objects (for all ring buffers)
	) :	Store_Manager_Pool<TDataClass>(
		storeCount,			// number of stores in manager
		boost::dynamic_pointer_cast< IStore_ReadWrite_Factory<TDataClass> >( make_shared< Store_Ringbuffer_Factory<TDataClass> >(	// ringbuffer store factory
			ringbufferSize,	// number of element slots in ringbuffer
			boost::dynamic_pointer_cast< IDataAllocator<TDataClass> >( make_shared< DataAllocator_Pool<TDataClass> >(				// data allocator
				poolSize	// total number of available objects (for all ring buffers)
			))
		))
	) {}

	/*
	* virtual destructor
	*/
	virtual ~Store_Manager_Ringbuffer_Pool() {}
};

}}

#endif // Store_Manager_Ringbuffer_Pool_def


