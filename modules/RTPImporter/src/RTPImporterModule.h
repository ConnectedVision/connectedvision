/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#ifdef _WIN32
#include <winsock2.h>
#else
	typedef void* HANDLE;
#endif

#include <string>
#include <unordered_map>

#include <IConnectedVisionModule.h>
#include <Module/Module_BaseClass.h>


#include "Class_RTPImporter_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

class RTPImporterModule: public Module_BaseClass
{
	friend class RTPImporterWorker;

public:
	RTPImporterModule();

	// worker
	virtual std::unique_ptr<IWorker> createWorker(
		IWorkerControllerCallbacks &controller,									///< reference to worker controller
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
	);


	// data handling
	virtual void deleteAllData(
		const id_t configID		///< [in] config ID of data to be deleted
	);

	//FIXME: Lookup workers by RTP-Handle
	static std::unordered_map<HANDLE,boost::shared_ptr<IWorker>> umHandleWorker;
	static boost::shared_mutex umHandleWorker_access;

protected:
	// data access
	virtual void prepareStores();

	// store manager of output images
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<Class_RTPImporter_output_FrameMetadata> > storeManagerImages;

	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);

};

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision