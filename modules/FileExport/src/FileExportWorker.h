/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** FileExportWorker.h
**
** written by Michael Rauter
** 
*******************************************************/

#pragma once

#include <IModuleEnvironment.h>
#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>
#include <ConnectedVisionAlgorithmWorker.h>

#include "FileExportModule.h"

#include "Class_FileExport_params.h"
#include "Class_FileExport_output_FileExportTrigger.h"

#include <queue>
#include <vector>
#include <boost/thread.hpp>

#define NUM_MAX_REQUEST_RETRIES 5

namespace ConnectedVision {
namespace Module {
namespace FileExport {

/**
* worker class of file export module
*/
class FileExportWorker : public ConnectedVisionAlgorithmWorker
{
	friend class FileExportModule;
	friend class FileExportTriggerOutputPin;
public:
	/**
	* constructor of FileExportWorker
	* @params env a pointer to @ref IModuleEnvironment (inherited from constructor of class ConnectedVisionAlgorithmWorker), pointer to environment
	* @params module a pointer to @ref ConnectedVisionModule (inherited from constructor of class ConnectedVisionAlgorithmWorker), pointer to module
	* @params config a boost shared pointer of @ref Class_generic_config (inherited from constructor of class ConnectedVisionAlgorithmWorker), boost shared pointer to module config
	*/
	FileExportWorker(IModuleEnvironment *env, ConnectedVisionModule *module, boost::shared_ptr<const Class_generic_config> config);

	/**
	* destructor of FileExportWorker
	*/
	~FileExportWorker();

	virtual void stop(); // overwrite stop function

protected:
	/**
	* inherited function (from class ConnectedVisionAlgorithmWorker) is overwritten and implements the functionality of the module implementation
	*/
	virtual void run();

private:
	
	/*
	* an ExportJob defines information needed to perform file export of data elements in worker thread
	*/
	struct ExportJob
	{
		/*
		* enumeration of types of a query (timestamp, identifier, index, ...)
		*/
		enum QueryType
		{
			QueryByTimestamp,
			QueryBeforeTimestamp,
			QueryAfterTimestamp,
			QueryByID,
			QueryByIndex
		};
		

		std::string outputFilename; ///< target output filename for file export
		//std::string requestToInputPin; ///< rest request to be sent to input pin
		
		ExportJob::QueryType queryType; ///< type of the query (timestamp, identifier, index, ...)
		timestamp_t timestampForQuery; ///< timestamp to be used for input pin query in case of timestamp-based query
		std::string identifierForQuery; ///< string to be used for input pin query in case of identifier-based query
		int64_t indexForQuery; ///< index to be used for input pin query in case of index-based query

		int numberOfUnsuccessfulRequestTries; ///< the number of (consecutive) tries for the request that were unsuccessful
	};

	struct FilepathFormatDescriptorElement
	{
		enum EnumTypeFilepathFormatDescriptorElement
		{
			TYPE_STRING,
			TYPE_PLACEHOLDER,
		};

		EnumTypeFilepathFormatDescriptorElement typeFilepathFormatDescriptorElement;
		std::string elementString;
	};

	void vecFilepathFormatDescriptorAppendStaticString(const std::string &stringToAppend, std::vector<FilepathFormatDescriptorElement> &vecFilepathFormatDescriptor);
	void parseAndProcessFilepathComponent(const std::string &stringComponentToParse, std::vector<FilepathFormatDescriptorElement> &vecFilepathFormatDescriptor);	
	std::string getFilepathFromFilepathFormatDescriptor(std::vector<FilepathFormatDescriptorElement> &vecFilepathFormatDescriptor, FileExportWorker::ExportJob &exportJobInfo);

	std::vector<FilepathFormatDescriptorElement> vecOutputPathDescriptor;
	std::vector<FilepathFormatDescriptorElement> vecOutputFilenameDescriptor;
	
	bool isConstantOutputPath;




	Class_FileExport_params params; ///< module config parameters

	std::queue<ExportJob> exportJobList; ///< export job list (actually implemented as queue) - output pin works as trigger for file exports and will fill this queue with data elements for export
	boost::mutex mutexExportJobList; ///< synchronization of different thread accessed to export job list is done via this mutex

	boost::condition_variable condExportJoblist; ///< used to signalize worker thread that new work is waiting to be processed (that a new export job was added by trigger output pin)

	int64_t exportElementRunningUniqueID; ///< running unique id for exported elements
};

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision