/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "RTPImporterWorker.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include "RTPImporterModule.h"
#include "RTPImporter_ModuleDescription.h"

#include <DataHandling/Store_Manager_Ringbuffer_Pool.h>
#include "OutputPin_FrameMetadata.h"
#include "OutputPin_FramePNG.h"

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

using namespace std;

std::unordered_map<HANDLE,boost::shared_ptr<IWorker>> RTPImporterModule::umHandleWorker;
boost::shared_mutex  RTPImporterModule::umHandleWorker_access;
/**
 * module constructor
 */
RTPImporterModule::RTPImporterModule() : Module_BaseClass(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}


/**
 * prepare module specific stores
 */
void RTPImporterModule::prepareStores() 
{
	LOG_SCOPE;

	// store manager of output images
	this->storeManagerImages = ConnectedVision::make_shared< ConnectedVision::DataHandling::Store_Manager_Ringbuffer_Pool< Class_RTPImporter_output_FrameMetadata > >(
		5,		// number of stores in manager
		50,		// number of element slots in ringbuffer
		260		// total number of available objects (for all ring buffers)
	);
}

/**
 * generate input pin
 *
 * Since this module does not have any input PINs this function will throw runtime_errors only.
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> RTPImporterModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	throw runtime_error("invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * Returns an runtime_error if the pinID is not implemented. Otherwise an RTPImageOutputPin will be returned.
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > RTPImporterModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( OutputPin_FrameMetadata::hasPinID(pinID) )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new OutputPin_FrameMetadata( this->storeManagerImages ) );
	}
	else if ( OutputPin_FramePNG::hasPinID(pinID) )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new OutputPin_FramePNG( this->storeManagerImages ) );
	}

	throw runtime_error("invalid pinID: " + pinID);
}

std::unique_ptr<IWorker> RTPImporterModule::createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config) 
{
	// create worker instance
	std::unique_ptr<IWorker> ptr( new RTPImporterWorker(*this, controller, config) );

	return ptr;
}

/**
 * deletes results in a specific database of the given configuration
 *
 * @param config	The configuration of which results shall be deleted.
 *
 */
void RTPImporterModule::deleteAllData(const id_t configID)
{
	// delete all results for configID
	this->storeManagerImages->getReadWriteStore( configID )->deleteAll();
}

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision