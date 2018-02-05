/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IConnectedVisionModule.h>
#include <Module/Module_BaseClass.h>



namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

class VideoImporterModule_priv;

class VideoImporterModule: public Module_BaseClass
{
public:
	VideoImporterModule();
	virtual ~VideoImporterModule();

	// worker
	virtual std::unique_ptr<IWorker> createWorker(
		IWorkerControllerCallbacks &controller,									///< reference to worker controller
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
	);

	// data handling
	virtual void deleteAllData(
		const id_t configID		///< [in] config ID of data to be deleted
	);

	ConnectedVision::shared_ptr<Class_generic_status> init(boost::shared_ptr<const Class_generic_config> constConfig);

	boost::shared_ptr<VideoImporterModule_priv> priv;

protected:
	// data access
	virtual void prepareStores();

	/**
	 * Ensure that the config is valid. 
	 * I.e. check that the file is readable, the number of connected input pins is in the range of the pin description min and max values. 
	 * If not, then an error is thrown.
	 */
	virtual void checkConfig(
		const Class_generic_config &config	///< [in] config	configuration chain
	);
	
	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision