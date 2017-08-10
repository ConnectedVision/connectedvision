/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DataAllocator_Primitive_def
#define DataAllocator_Primitive_def

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
class DataAllocator_Primitive : public IDataAllocator<TDataClass>
{
public:
	DataAllocator_Primitive() {};

	/**
	* This is the simplest possible implementation of the create() function.
	* Each call 
	*  1. allocates a new object and 
	*  2. calls the clear() function of the data class
	*		The clear function of the data object clears all data and content, but does not release any memory or resources.
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
};

}}

// include source code: template inclusion model
#include "DataAllocator_Primitive.cpp"

#endif // DataAllocator_Primitive_def


