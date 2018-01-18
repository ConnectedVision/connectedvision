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


FileExportModule::FileExportModule() : Module_BaseClass(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}

boost::shared_ptr<IConnectedVisionInputPin> FileExportModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( pinID == InputPin_ArbitraryData::PinID() )
	{
		return boost::shared_ptr<IConnectedVisionInputPin>( new InputPin_ArbitraryData(this->env, pinID, this) );
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

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


int FileExportModule::control(const id_t configID, const std::string& command, const id_t senderID, ConnectedVisionResponse &response)
{
	int ret = Module_BaseClass::control(configID, command, senderID, response);

	try
	{
		auto ptr = boost::dynamic_pointer_cast<FileExportWorker>(this->getWorker(configID));
		ptr->wakeUpWorker();
	}
	catch (std::out_of_range)
	{
	}

	return(ret);
}

void FileExportModule::deleteAllData(const id_t configID)
{
	// nothing to do
}

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision