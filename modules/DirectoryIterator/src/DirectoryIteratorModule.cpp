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

// _moduleDescription, _inputPinDescription, _outputPinDescription are static strings from "DirectoryIterator_ModuleDescription.h" (auto generated header)
DirectoryIteratorModule::DirectoryIteratorModule() : Module_BaseClass(_moduleDescription, _inputPinDescription, _outputPinDescription)
{
}


void DirectoryIteratorModule::releaseModule() 
{
	// reset store managers
	this->storeManagerFileMetadata.reset();	
}


std::unique_ptr<IWorker> DirectoryIteratorModule::createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config)
{
	// create worker instance
	std::unique_ptr<IWorker> ptr( new DirectoryIteratorWorker(*this, controller, config) );

	return ptr;
}

void DirectoryIteratorModule::deleteAllData(const id_t configID)
{
	// delete all results for configID
	this->storeManagerFileMetadata->getReadWriteStore(configID)->deleteAll();
}

void DirectoryIteratorModule::prepareStores() 
{

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



} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision