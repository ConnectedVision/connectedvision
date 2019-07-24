/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#define USE_RINGBUFFER

#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <boost/shared_ptr.hpp>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include "DummyBoundingBoxes_ModuleDescription.h"

#include "DummyBoundingBoxesModule.h"
#include "DummyBoundingBoxesWorker.h"

#ifdef USE_RINGBUFFER
#include "Store_Manager_Ringbuffer_DummyBoundingBoxes_output_Detections.h"
#include "Store_Manager_Ringbuffer_DummyBoundingBoxes_output_ObjectData.h"
#else
#include "Store_Manager_SQLite_DummyBoundingBoxes_output_Detections.h"
#include "Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData.h"
#endif

#include "InputPin_DummyBoundingBoxes_input_Trigger.h"

#include <Module/OutputPins/OutputPin_JSON.h>
#include "OutputPin_DummyBoundingBoxes_output_Detections.h"
#include "OutputPin_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision { 
namespace Module { 
namespace DummyBoundingBoxes { 


using namespace std;

/**
 * module constructor
 */
DummyBoundingBoxesModule::DummyBoundingBoxesModule() : Module_BaseClass(_moduleDescription, _inputPinDescription, _outputPinDescription)
{
}


/**
 * init module
 *
 * @param server  module server
 */
void DummyBoundingBoxesModule::initModule( IModuleEnvironment *env ) 
{
	LOG_SCOPE;

	// clean up module before init
	releaseModule();

	// call parent init
	Module_BaseClass::initModule(env);
}

/**
 * destroy module
 *
 * @param server  module server
 */
void DummyBoundingBoxesModule::releaseModule() 
{
	LOG_SCOPE;

	// call parent clean-up
	Module_BaseClass::releaseModule();

	// module specific clean-up
	this->detectionsStoreManager.reset();
}

/**
 * prepare module specific stores
 */
void DummyBoundingBoxesModule::prepareStores() 
{
	LOG_SCOPE;

#ifdef USE_RINGBUFFER
	int bufferSize = 100;
	int parallelJobs = 10;
	this->detectionsStoreManager = ConnectedVision::make_shared<DataHandling::Store_Manager_Ringbuffer_DummyBoundingBoxes_output_Detections>(
		parallelJobs,			// number of stores in manager
		bufferSize,		// number of element slots in ringbuffer
		bufferSize * parallelJobs + 1		// total number of available objects (for all ring buffers)
		);
	this->objectsStoreManager = ConnectedVision::make_shared<DataHandling::Store_Manager_Ringbuffer_DummyBoundingBoxes_output_ObjectData>(
		parallelJobs,			// number of stores in manager
		bufferSize,		// number of element slots in ringbuffer
		bufferSize * parallelJobs + 1		// total number of available objects (for all ring buffers)
		);
#else
	// module specific stores
	this->detectionsStoreManager = ConnectedVision::make_shared<DataHandling::Store_Manager_SQLite_DummyBoundingBoxes_output_Detections>( this->getDB() );
	this->objectsStoreManager = ConnectedVision::make_shared<DataHandling::Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData>( this->getDB() );
#endif
}

/**
 * generate input pin
 *
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> DummyBoundingBoxesModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if(pinID == InputPin_DummyBoundingBoxes_input_Trigger::PinID())
	{
		return boost::make_shared<InputPin_DummyBoundingBoxes_input_Trigger>(this->env, pinID);
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > DummyBoundingBoxesModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( OutputPin_DummyBoundingBoxes_output_Detections::hasPinID(pinID) )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new OutputPins::OutputPin_JSON<Class_DummyBoundingBoxes_output_Detections>( this->detectionsStoreManager ) );
	}
	if ( OutputPin_DummyBoundingBoxes_output_ObjectData::hasPinID(pinID) )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new OutputPins::OutputPin_JSON<Class_DummyBoundingBoxes_output_ObjectData>( this->objectsStoreManager ) );
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}


std::unique_ptr<IWorker> DummyBoundingBoxesModule::createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config) 
{
	// create worker instance
	std::unique_ptr<IWorker> ptr( new DummyBoundingBoxesWorker(*this, controller, config) );
	if ( !ptr )
		throw std::runtime_error( "cannot create worker for " + this->moduleName + " / configID: " + config->getconst_configID() );

	return ptr;
}

/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void DummyBoundingBoxesModule::deleteAllData(const id_t configID)
{
	// delete all results for configID
	auto detectionsStore = this->detectionsStoreManager->getReadWriteStore( configID );
	detectionsStore->deleteAll();
	auto objectsStore = this->objectsStoreManager->getReadWriteStore( configID );
	objectsStore->deleteAll();
}

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision