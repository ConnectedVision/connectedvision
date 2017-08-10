/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef MixIn_IDataAllocator_def
#define MixIn_IDataAllocator_def

#include "TestHelper_DataHandling.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

MIXIN_PARAMS(MixIn_IDataAllocator)
{
	IDataAllocator<TestDataClass>* allocator;
};


}} // namespace scope

#endif // MixIn_IDataAllocator_def