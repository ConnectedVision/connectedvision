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
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>

#include "Class_RTPImporter_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

class RTPImporterModule: public ConnectedVisionModule
{
	friend class RTPImporterWorker;

public:
	RTPImporterModule();

	// module init / release
	virtual void initModule( IModuleEnvironment *env );
	virtual void releaseModule();

	// worker
	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config);
	//for internal member access in the worker by a OutputPin
	boost::shared_ptr<IConnectedVisionAlgorithmWorker> getWorkerByConfigID(const id_t configID);
	// data handling
	virtual void deleteResults(const boost::shared_ptr<const Class_generic_config> config);

	//FIXME: Lookup workers by RTP-Handle
	static std::unordered_map<HANDLE,boost::shared_ptr<IConnectedVisionAlgorithmWorker>> umHandleWorker;
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