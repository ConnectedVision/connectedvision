/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IConnectedVisionModule.h>
#include <Module/Module_BaseClass.h>


#include "Class_DummyBoundingBoxes_output_Detections.h"
#include "Class_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

class DummyBoundingBoxesModule_priv;

class DummyBoundingBoxesModule: public Module_BaseClass
{
friend class DummyBoundingBoxesWorker;
public:
	DummyBoundingBoxesModule();

public:
	// module init / release
	virtual void initModule( IModuleEnvironment *env );
	virtual void releaseModule();

	// worker
	virtual std::unique_ptr<IWorker> createWorker(
		IWorkerControllerCallbacks &controller,									///< reference to worker controller
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
	);
	// data handling
	virtual void deleteAllData(
		const id_t configID		///< [in] config ID of data to be deleted
	);

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