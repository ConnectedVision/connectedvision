/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>


#include "FileImporterModule.h"

#include "FileOutputPin.h"
#include "FileImporter_ModuleDescription.h"

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

using namespace std;

/**
 * module constructor
 */
FileImporterModule::FileImporterModule() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}

/**
 * init module
 *
 * @param server  module server
 */
void FileImporterModule::initModule( IModuleEnvironment *env ) 
{ 
	LOG_SCOPE;

	// clean up module before init
	this->releaseModule();

	// call parent init
	ConnectedVisionModule::initModule(env);
}

/**
 * destroy module
 *
 * @param server  module server
 */
void FileImporterModule::releaseModule() 
{
	LOG_SCOPE;

	// call parent init
	ConnectedVisionModule::releaseModule();
}

/**
 * prepare module specific stores
 */
void FileImporterModule::prepareStores() 
{
	// module specific stores
}

/**
 * generate input pin
 *
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> FileImporterModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > FileImporterModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( pinID == FileOutputPin::PinID() )
	{
		/* 
			dummy output pin (see output pin description)
			Use the auto generated meta-data output pin.
		*/
		return boost::shared_ptr<IConnectedVisionOutputPin>( new FileOutputPin( this->env ) );

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
boost::shared_ptr<IConnectedVisionAlgorithmWorker> FileImporterModule::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	// this module does not use Workers
	return boost::shared_ptr<IConnectedVisionAlgorithmWorker>();
}

/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void FileImporterModule::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	// nothing to do
}

/**
 * start processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void FileImporterModule::start(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// set status to finished
	auto status = ConnectedVision::make_shared<Class_generic_status>();
	status->set_id(constConfig->get_id());
	status->set_status_finished();
	status->set_progress( 1.0 );
	Class_generic_status_stableResults stableResults;
	stableResults.set_indexStart( 0 );
	stableResults.set_indexEnd( 0 );
	stableResults.set_timestampStart( 0 );
	stableResults.set_timestampEnd( 0 );
	status->set_stableResultsByPinID( stableResults, FileOutputPin::PinID() );
	status->set_estimatedFinishTime( 0 );
	status->set_systemTimeProcessing( sysTime() );
	
	statusStore->save_move(status);
}

/**
 * stop processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void FileImporterModule::stop(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// nothing to do
}

/**
 * revocer of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void FileImporterModule::recover(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// reset
	this->reset(constConfig);
}

/**
 * reset processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void FileImporterModule::reset(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// set status to init
	auto status = ConnectedVision::make_shared<Class_generic_status>();
	status->set_id(constConfig->get_id());
	status->set_status_init();
	status->set_progress( 1.0 );
	Class_generic_status_stableResults stableResults;
	stableResults.set_indexStart( 0 );
	stableResults.set_indexEnd( -1 );
	stableResults.set_timestampStart( 0 );
	stableResults.set_timestampEnd( -1 );
	status->set_stableResultsByPinID( stableResults, FileOutputPin::PinID() );
	status->set_estimatedFinishTime( -1 );
	status->set_systemTimeProcessing( sysTime() );
	
	statusStore->save_move(status);
}

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision