/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DataAllocator_Pool_def
#define DataAllocator_Pool_def

#include <set>
#include <boost/thread.hpp>

#include <general.h>
#include <IStore.h>

#define IConnectedVisionDataClass	class


namespace ConnectedVision 
{ namespace DataHandling
{

/**
	data class allocator and pool management
*/
template <IConnectedVisionDataClass TDataClass>
class DataAllocator_Pool : public IDataAllocator<TDataClass>
{
public:
	/**
	* constructor
	*
	*	All objects are pre-allocated and initialized (with the object clear() function) in the constructor. (RAII)
	*/
	DataAllocator_Pool(
		const int64_t size	///< number of objects to be created in pool
	);

	/**
	* creates a new or reuses an existing data object
	*
	*	1. search the pending list for a reuseable object
	*	2. search all allocated objects for orphan (not correctly released) objects
	*	If an object was found it is cleared and marked as writeable to be reused.
	*
	* @return shared pointer to new data object
	*/
	virtual ConnectedVision::shared_ptr<TDataClass> create();


	/**
	* explicitely release allocated object
	* This function returns the ownership of an object to the allocator.
	*/
	virtual void initiateRelease(
		ConnectedVision::shared_ptr<const TDataClass>& dataConst ///< [in/moved] shared pointer to read-only data object (ownership is moved)
	);

	/**
	* convert a writable data object to a read-only data object
	*
	* @thow std::runtime if object is still hold by a writer
	*
	* @return read-only data object
	*/
	virtual ConnectedVision::shared_ptr<const TDataClass> make_const(
		ConnectedVision::shared_ptr<TDataClass>& data	///< [in/moved] writeable data object (ownership is moved)
	) const;

protected:
	/**
	* convert a read-only data object to a writeable data object
	* The purpose of this function is to prepare an object from the object pool to be re-used..
	*
	* @return writeable data object
	*/
	ConnectedVision::shared_ptr<TDataClass> make_writeable(
		const ConnectedVision::shared_ptr<const TDataClass>& dataConst	///< [in/moved] read-only data object (ownership is moved)
	) const;

	/// total number of elements to be created
	const int64_t size;

	/// list of all allocated / created elements
	std::set< ConnectedVision::shared_ptr<const TDataClass> > allocatedElements;

	/// list of elements marked as released
	std::set< ConnectedVision::shared_ptr<const TDataClass> > pendingElements;

	/// general mutex for element lists
	ConnectedVision::mutex allocatorMutex;
};

}}

// include source code: template inclusion model
#include "DataAllocator_Pool.cpp"

#endif // DataAllocator_Pool_def


