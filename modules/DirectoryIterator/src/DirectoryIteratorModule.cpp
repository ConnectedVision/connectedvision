/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <Module/OutputPins/OutputPin_JSON.h>

#include "DirectoryIteratorModule.h"
#include "DirectoryIteratorWorker.h"

#include "DirectoryIterator_ModuleDescription.h"

#include "OutputPin_DirectoryIterator_output_FileMetadata.h"
#include "OutputPin_DirectoryIterator_output_BinaryData.h"
#include "Class_DirectoryIterator_output_FileMetadata.h"
#include "Store_Manager_SQLite_DirectoryIterator_output_FileMetadata.h"
#include "Store_Manager_Ringbuffer_DirectoryIterator_output_FileMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

#define STORE_USE_RINGBUFFER 0

using namespace ConnectedVision;

DirectoryIteratorModule::DirectoryIteratorModule() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
{
}

void DirectoryIteratorModule::initModule(IModuleEnvironment *env) 
{
	LOG_SCOPE;

	// clean up module before init
	releaseModule();

	// call parent init
	ConnectedVisionModule::initModule(env);
}

void DirectoryIteratorModule::releaseModule() 
{
	LOG_SCOPE;

	// call parent release
	ConnectedVisionModule::releaseModule();

	// reset store managers
	this->storeManagerFileMetadata.reset();	
}

void DirectoryIteratorModule::prepareStores() 
{
	LOG_SCOPE;

	// module specific stores
#if STORE_USE_RINGBUFFER
	this->storeManagerFileMetadata = ConnectedVision::make_shared<Store_Manager_Ringbuffer_DirectoryIterator_output_FileMetadata>(
		10,			// number of stores in manager
		1000,		// number of element slots in ringbuffer
		10010		// total number of available objects (for all ring buffers)
	);
#else
	this->storeManagerFileMetadata = ConnectedVision::make_shared<DataHandling::Store_Manager_SQLite_DirectoryIterator_output_FileMetadata>(this->getDB());
#endif

}

boost::shared_ptr<IConnectedVisionInputPin> DirectoryIteratorModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	throw ConnectedVision::runtime_error("failed to generate input pin (invalid pin ID: " + pinID + ")");
}

boost::shared_ptr<IConnectedVisionOutputPin > DirectoryIteratorModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if(OutputPin_DirectoryIterator_output_FileMetadata::hasPinID(pinID))
	{
		return boost::make_shared<OutputPins::OutputPin_JSON<Class_DirectoryIterator_output_FileMetadata>>(this->storeManagerFileMetadata);
	}
	else if(OutputPin_DirectoryIterator_output_BinaryData::hasPinID(pinID))
	{
		return boost::make_shared<OutputPin_DirectoryIterator_output_BinaryData>(this);
	}

	throw ConnectedVision::runtime_error("failed to generate output pin (invalid pin ID: " + pinID + ")");
}

boost::shared_ptr<IConnectedVisionAlgorithmWorker> DirectoryIteratorModule::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE;

	// create worker instance
	return boost::make_shared<DirectoryIteratorWorker>(env, this, config);
}

void DirectoryIteratorModule::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG(config->getconst_id());

	// delete all results for configID
	this->storeManagerFileMetadata->getReadWriteStore(config->getconst_id())->deleteAll();
}

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision