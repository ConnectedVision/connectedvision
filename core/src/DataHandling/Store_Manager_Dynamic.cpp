/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Manager_Dynamic_code
#define Store_Manager_Dynamic_code

#include <list>

#include "Store_Manager_Dynamic.h"

namespace ConnectedVision 
{ namespace DataHandling
{

template <IConnectedVisionDataClass TDataClass>
Store_Manager_Dynamic<TDataClass>::Store_Manager_Dynamic( shared_ptr< IStore_Manager_Dynamic_Selector<TDataClass> > selector ) :
	selector( selector )
{

}

template <IConnectedVisionDataClass TDataClass>
shared_ptr< IStore_Read<TDataClass> > Store_Manager_Dynamic<TDataClass>::getReadStore(const id_t configID)
{
	shared_ptr<IStore_Manager<TDataClass>> storeManager = this->selector->selectStoreManager( configID );
	return storeManager->getReadStore( configID );
}

template <IConnectedVisionDataClass TDataClass>
shared_ptr< IStore_ReadWrite<TDataClass> > Store_Manager_Dynamic<TDataClass>::getReadWriteStore(const id_t configID)
{
	shared_ptr<IStore_Manager<TDataClass>> storeManager = this->selector->selectStoreManager( configID );
	return storeManager->getReadWriteStore( configID );
}


}} // namespace scope

#endif // Store_Manager_Dynamic_code