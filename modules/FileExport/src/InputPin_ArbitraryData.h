/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** InputPin_ArbitraryData.h
**
** written by Michael Rauter
** 
*******************************************************/

#pragma once

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include <IConnectedVisionModule.h>
#include <ConnectedVisionInputPin.h>

#include "IDataSource.h"
#include <Module/Control/Class_RawData.h>

#include "FileExportModule.h"

namespace ConnectedVision {
namespace Module {
namespace FileExport {

/**
 *
 */
class FileExportModule::InputPin_ArbitraryData : public ConnectedVisionInputPinData<Class_RawData>
{
public:
	static const pinID_t PinID() { return "data"; };

	InputPin_ArbitraryData(IModuleEnvironment *env, const pinID_t& inputPinID, FileExportModule* pModule);
	virtual ~InputPin_ArbitraryData();

	//virtual void init(const id_t parentConfigID, const std::string& configStr, const pinID_t& outputPinID);
	/*
	virtual boost::shared_ptr<string> getByID(const id_t id);
	virtual boost::shared_ptr<string> getByIndex(const int64_t index);
	virtual boost::shared_ptr<string> getByTimestamp(const timestamp_t timestamp);
	virtual boost::shared_ptr<string> getBeforeTimestamp(const timestamp_t timestamp);
	virtual boost::shared_ptr<string> getAfterTimestamp(const timestamp_t timestamp);
	*/
protected:
	/**
	 * get multiple objects from RESTfull service
	 *	This function is OPTIONAL.
	 *
	 * @param restURL	full REST URL of request
	 */
	//virtual boost::shared_ptr<string> requestData(const std::string restURL ) const;

	//IDataSource<Class_RawData>* getDataSource();

	FileExportModule *pModule;

	//IDataSource<Class_RawData> *pDataSource;
};

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision