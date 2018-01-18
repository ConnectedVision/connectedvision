/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>

#include <IConnectedVisionModule.h>
#include <Module/Module_BaseClass.h>



namespace ConnectedVision {
namespace Module {
namespace FileExport {

class FileExportModule: public Module_BaseClass
{
	friend class FileExportTriggerOutputPin;
public:
	class InputPin_ArbitraryData;

public:
	/**
	 * module constructor
	 */
	FileExportModule();

	virtual std::unique_ptr<IWorker> createWorker(
		IWorkerControllerCallbacks &controller,									///< reference to worker controller
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
	);

	/**
	 * delete results of a config chain
	 *
	 * @param config	config chain
	 */
	virtual void deleteAllData(
		const id_t configID		///< [in] config ID of data to be deleted
	);

	virtual int control(const id_t configID, const std::string& command, const id_t senderID, ConnectedVisionResponse &response);

protected:
	// data access
	virtual void prepareStores() {}

	/**
	 * generate input pin
	 *
	 * @return input pin
	 */
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);

	/**
	 *  generate output pin
	 *
	 * @return output pin
	 */
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);
};

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision