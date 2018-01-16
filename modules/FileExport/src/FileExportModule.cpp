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

#include <boost/lexical_cast.hpp>

#include "FileExportModule.h"
#include "FileExportWorker.h"

#include "InputPin_ArbitraryData.h"

#include "FileExportTriggerOutputPin.h"
#include "FileExport_ModuleDescription.h"

namespace ConnectedVision {
namespace Module {
namespace FileExport {

using namespace std;


/**
 * generate input pin
 *
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> FileExportModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( pinID == InputPin_ArbitraryData::PinID() )
	{
		return boost::shared_ptr<IConnectedVisionInputPin>( new InputPin_ArbitraryData(this->env, pinID, this) );
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > FileExportModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( pinID == FileExportTriggerOutputPin::PinID() )
	{
		/* 
			dummy output pin (see output pin description)
			Use the auto generated meta-data output pin.
		*/
		return boost::shared_ptr<IConnectedVisionOutputPin>( new FileExportTriggerOutputPin( this->env, this ) );

	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

std::unique_ptr<IWorker> FileExportModule::createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config) 
{
	// create worker instance
	std::unique_ptr<IWorker> ptr( new FileExportWorker(*this, controller, config) );

	return ptr;
}

/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void FileExportModule::deleteAllData(const id_t configID)
{
	// nothing to do
}

boost::shared_ptr<IWorker> FileExportModule::getWorkerByConfigID(const id_t configID)
{
	std::vector< boost::shared_ptr<IWorker> > workers = this->getRunningWorkers();
	if (workers.size() > 0)
	{
		for (std::vector< boost::shared_ptr<IWorker> >::iterator it = workers.begin(); it != workers.end(); ++it) 
		{
			if ((*it)->getID() == configID)
			{
				return(*it);
			}
		}
	}
	throw ConnectedVision::runtime_error("did not find running IConnectedVisionAlgorithmWorker with config id" + boost::lexical_cast<std::string>(configID));
}

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision