/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef MixIn_IStore_def
#define MixIn_IStore_def

#include "TestHelper_DataHandling.hpp"
#include "TestHelper_StoreEnvironment.hpp"

namespace ConnectedVision 
{ namespace DataHandling
{

MIXIN_PARAMS(MixIn_IStore)
{
	StoreEnvironment<TestDataClass>* env;
	shared_ptr< IStore_ReadWrite<TestDataClass> > store;
};

}} // namespace scope

#endif // MixIn_IStore_def