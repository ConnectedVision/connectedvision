/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IConnectedVisionModule.h>
#include <Module/Module_BaseClass.h>



//#include "WinDef.h" 
typedef unsigned char       BYTE;

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

class SyntheticVideoModule_priv;

class SyntheticVideoModule: public Module_BaseClass
{
public:
	SyntheticVideoModule();
	virtual ~SyntheticVideoModule();

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

public:
	boost::shared_ptr<SyntheticVideoModule_priv> priv;

protected:
	// data access
	virtual void prepareStores();
	
	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);

	// overwrite control functions
	virtual void start(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void stop(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void reset(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void recover(boost::shared_ptr<const Class_generic_config> constConfig);

};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision