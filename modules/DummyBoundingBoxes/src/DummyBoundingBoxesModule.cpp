/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

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

#include "Store_Manager_SQLite_DummyBoundingBoxes_output_Detections.h"
#include "Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData.h"

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
DummyBoundingBoxesModule::DummyBoundingBoxesModule() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
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
	ConnectedVisionModule::initModule(env);
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
	ConnectedVisionModule::releaseModule();

	// module specific clean-up
	this->detectionsStoreManager.reset();
}

/**
 * prepare module specific stores
 */
void DummyBoundingBoxesModule::prepareStores() 
{
	LOG_SCOPE;

	// module specific stores
	this->detectionsStoreManager = ConnectedVision::make_shared<DataHandling::Store_Manager_SQLite_DummyBoundingBoxes_output_Detections>( this->getDB() );
	this->objectsStoreManager = ConnectedVision::make_shared<DataHandling::Store_Manager_SQLite_DummyBoundingBoxes_output_ObjectData>( this->getDB() );
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


/**
 * create algorithm worker object
 *
 * @param env	ConnectedVision module environment
 * @param db	SQLite DB
 * @param config	job / config
 *
 * @return new algorithm worker object
 */
boost::shared_ptr<IConnectedVisionAlgorithmWorker> DummyBoundingBoxesModule::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	return boost::shared_ptr<IConnectedVisionAlgorithmWorker>( new DummyBoundingBoxesWorker(env, this, config) );
}

/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void DummyBoundingBoxesModule::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	// delete all results for configID
	auto detectionsStore = this->detectionsStoreManager->getReadWriteStore( config->getconst_id() );
	detectionsStore->deleteAll();
	auto objectsStore = this->objectsStoreManager->getReadWriteStore( config->getconst_id() );
	objectsStore->deleteAll();
}

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision