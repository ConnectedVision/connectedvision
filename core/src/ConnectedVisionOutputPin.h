/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <boost/shared_ptr.hpp>

#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"

#include <ConnectedVision.h>
#include <IStore.h>
#include <IStoreCV.h>
#include <IConnectedVisionModule.h>

namespace ConnectedVision
{

/**
 *
 */
template <class TDataObject>
class ConnectedVisionOutputPin : public IConnectedVisionOutputPin
{
public:
	ConnectedVisionOutputPin(boost::shared_ptr< Store::IStoreCV<TDataObject> > dataStore);

	virtual ~ConnectedVisionOutputPin();

	virtual void init(const std::string& configStr);

	virtual int getByID(const id_t id, ConnectedVisionResponse &response);
	virtual int getByIndex(const int64_t index, ConnectedVisionResponse &response);
	virtual int getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response);
	virtual int getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response);

protected:

	boost::shared_ptr< Store::IStoreCV<TDataObject> > dataStore;
	Class_generic_config config;
};

} // namespace ConnectedVision

// include source code: template inclusion model
#include "ConnectedVisionOutputPin.cpp"