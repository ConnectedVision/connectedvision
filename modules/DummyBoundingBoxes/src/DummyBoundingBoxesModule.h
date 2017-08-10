/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IConnectedVisionModule.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>

#include "Class_DummyBoundingBoxes_output_Detections.h"
#include "Class_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

class DummyBoundingBoxesModule_priv;

class DummyBoundingBoxesModule: public ConnectedVisionModule
{
friend class DummyBoundingBoxesWorker;
public:
	DummyBoundingBoxesModule();

public:
	// module init / release
	virtual void initModule( IModuleEnvironment *env );
	virtual void releaseModule();

	// worker
	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config);

	// data handling
	virtual void deleteResults(const boost::shared_ptr<const Class_generic_config> config);

protected:
	// data access
	virtual void prepareStores();

	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);

protected:
	// data store
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<Class_DummyBoundingBoxes_output_Detections> > detectionsStoreManager;
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<Class_DummyBoundingBoxes_output_ObjectData> > objectsStoreManager;
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision