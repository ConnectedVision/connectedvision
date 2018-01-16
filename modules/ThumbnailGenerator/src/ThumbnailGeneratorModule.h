/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>

#include <IConnectedVisionModule.h>
#include <Module/Module_BaseClass.h>



namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

class ThumbnailGeneratorModule: public Module_BaseClass
{
public:
	ThumbnailGeneratorModule();

public:
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
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision