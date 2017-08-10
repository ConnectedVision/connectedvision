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

std::unordered_map<HANDLE,boost::shared_ptr<IConnectedVisionAlgorithmWorker>> RTPImporterModule::umHandleWorker;
boost::shared_mutex  RTPImporterModule::umHandleWorker_access;
/**
 * module constructor
 */
RTPImporterModule::RTPImporterModule() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}

/**
 * init module
 *
 * @param env  Connected Vision Module environment
 */
void RTPImporterModule::initModule( IModuleEnvironment *env ) 
{
	LOG_SCOPE;

	// clean up module before init
	releaseModule();

	// call parent init
	ConnectedVisionModule::initModule(env);
	// No own resources in this module at the current state
}

/**
 * destroy module
 *
 */
void RTPImporterModule::releaseModule() 
{
	LOG_SCOPE;

	// call parent release
	ConnectedVisionModule::releaseModule();
	// No own resources in this module at the current state.
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

/**
 * create algorithm worker object
 *
 * @param env	ConnectedVision module environment
 * @param config	job / config
 *
 * @return new algorithm worker object
 */
boost::shared_ptr<IConnectedVisionAlgorithmWorker> RTPImporterModule::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE;

// TODO --> create your worker object HERE! <--
	return (boost::shared_ptr<IConnectedVisionAlgorithmWorker>(new RTPImporterWorker(env, this, config)));
}
/**
 * find the worker object for a given configuration.
 *
 * @param configID	configuration identification
 *
 * @return Reference to the given worker Object (dynamic_cast if you need access to local custom members) 
 */
boost::shared_ptr<IConnectedVisionAlgorithmWorker> RTPImporterModule::getWorkerByConfigID(const id_t configID)
{
	std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> > workers = algoDispatcher->getRunningWorkers();
	if (workers.size() > 0)
	{
		for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = workers.begin(); it != workers.end(); ++it) 
		{
			if ((*it)->getID() == configID)
			{
				return(*it);
			}
		}
	}
	throw ConnectedVision::runtime_error("did not find running IConnectedVisionAlgorithmWorker with config id" + IDToStr(configID));
}
/**
 * deletes results in a specific database of the given configuration
 *
 * @param config	The configuration of which results shall be deleted.
 *
 */
void RTPImporterModule::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	id_t configID = config->get_id();
	LOG_SCOPE_CONFIG( configID );

	// delete all results for configID
	this->storeManagerImages->getReadWriteStore( config->getconst_id() )->deleteAll();
}

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision