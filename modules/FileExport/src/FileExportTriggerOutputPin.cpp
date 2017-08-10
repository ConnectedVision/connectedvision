/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <helper.h>

#include "FileExportWorker.h"
#include "FileExportTriggerOutputPin.h"

#define LOG_SCOPE_CONFIG( configID )		Logging::LoggingScope _log_scope( this->log(), Logging::Debug, this->logName, std::string(__FUNCTION__) + std::string("()@") + ConnectedVision::intToStr(__LINE__), ( configID ) );

namespace ConnectedVision {
namespace Module {
namespace FileExport {

using namespace std;


FileExportTriggerOutputPin::FileExportTriggerOutputPin(IModuleEnvironment *env, FileExportModule *pModule) : env(env)
{
	this->logName = "FileExportTriggerOutputPin";
	this->pModule = pModule;
}


FileExportTriggerOutputPin::~FileExportTriggerOutputPin(void)
{

}

void FileExportTriggerOutputPin::init(const std::string& configStr)
{
	LOG_SCOPE;

	this->config.parseJson( configStr.c_str() );
	this->params.parseJson( this->config.get_params() );
}

/**
 * get data from module by ID
 *
 * @param[in] id			ID of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getByID(const id_t id, ConnectedVisionResponse &response)
{
	id_t configID = this->config.get_id();
	LOG_SCOPE_CONFIG( configID );
	
	boost::shared_ptr<FileExportWorker> pWorker = boost::dynamic_pointer_cast<FileExportWorker>(pModule->getWorkerByConfigID(configID));
	if (pWorker)
	{
		{ // scoped lock context
			boost::lock_guard<boost::mutex> scoped_lock(pWorker->mutexExportJobList);			
			FileExportWorker::ExportJob newJob;
			newJob.queryType = FileExportWorker::ExportJob::QueryByID;
			newJob.identifierForQuery = id;
			newJob.numberOfUnsuccessfulRequestTries = 0;
			pWorker->exportJobList.push(newJob);
			pWorker->condExportJoblist.notify_one();
		}
		//response.setContentType("");
		//response.setContent("file export job added to job list");

		response.setContentType("application/json");
		std::string content = "[\n\"file export job added to job list\"\n]\n";
		response.setContent(content);

		return 200;
	}

	return writeError(response, 500, id_t("FileExportTriggerOutputPin"), "getByID request could not be added to file export job list");	

	/*
	try 
	{
		ifstream ifs( this->params.get_filename()->c_str(), ios::binary | ios::in);
		string data = string( (istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>() ) );

		response.setContentType( *this->params.get_mimeType() );
		response.setContent(data);
		return 200;

	}
	catch (runtime_error& e)
	{
		// internal server error --> HTTP Code: 500
		return writeError(response, 500, id_t("FileExportTriggerOutputPin"), string(e.what()) );
	}
	*/
}


/**
 * get data from module by index
 *
 * @param[in] index			index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	id_t configID = this->config.get_id();
	LOG_SCOPE_CONFIG( configID );
	
	boost::shared_ptr<FileExportWorker> pWorker = boost::dynamic_pointer_cast<FileExportWorker>(pModule->getWorkerByConfigID(configID));
	if (pWorker)
	{
		{ // scoped lock context
			boost::lock_guard<boost::mutex> scoped_lock(pWorker->mutexExportJobList);	
			FileExportWorker::ExportJob newJob;
			newJob.queryType = FileExportWorker::ExportJob::QueryByIndex;
			newJob.indexForQuery = index;
			newJob.numberOfUnsuccessfulRequestTries = 0;
			pWorker->exportJobList.push(newJob);
			pWorker->condExportJoblist.notify_one();
		}
		response.setContentType("application/json");
		std::string content = "[\n\"file export job added to job list\"\n]\n";
		response.setContent(content);
		return 200;
	}

	return writeError(response, 500, id_t("FileExportTriggerOutputPin"), "getByIndex request could not be added to file export job list");	
}

/**
 * get data from module by index range
 *
 * @param[in] start			first index of requested data
 * @param[in] end			last index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	throw ConnectedVision::runtime_error("function getByIndexRange() not implemented for FileExportTriggerOutputPin");
}

/**
 * get data from module by timestamp
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	id_t configID = this->config.get_id();
	LOG_SCOPE_CONFIG( configID );
	
	boost::shared_ptr<FileExportWorker> pWorker = boost::dynamic_pointer_cast<FileExportWorker>(pModule->getWorkerByConfigID(configID));
	if (pWorker)
	{
		{ // scoped lock context
			boost::lock_guard<boost::mutex> scoped_lock(pWorker->mutexExportJobList);	
			FileExportWorker::ExportJob newJob;
			newJob.queryType = FileExportWorker::ExportJob::QueryByTimestamp;
			newJob.timestampForQuery = timestamp;
			newJob.numberOfUnsuccessfulRequestTries = 0;
			pWorker->exportJobList.push(newJob);
			pWorker->condExportJoblist.notify_one();
		}
		response.setContentType("application/json");
		std::string content = "[\n\"file export job added to job list\"\n]\n";
		response.setContent(content);
		return 200;
	}

	return writeError(response, 500, id_t("FileExportTriggerOutputPin"), "getByTimestamp request could not be added to file export job list");
}

/**
 * get data from module by timestamp before
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	id_t configID = this->config.get_id();
	LOG_SCOPE_CONFIG( configID );
	
	boost::shared_ptr<FileExportWorker> pWorker = boost::dynamic_pointer_cast<FileExportWorker>(pModule->getWorkerByConfigID(configID));
	if (pWorker)
	{
		{ // scoped lock context
			boost::lock_guard<boost::mutex> scoped_lock(pWorker->mutexExportJobList);	
			FileExportWorker::ExportJob newJob;
			newJob.queryType = FileExportWorker::ExportJob::QueryBeforeTimestamp;
			newJob.timestampForQuery = timestamp;
			newJob.numberOfUnsuccessfulRequestTries = 0;
			pWorker->exportJobList.push(newJob);
			pWorker->condExportJoblist.notify_one();
		}
		response.setContentType("application/json");
		std::string content = "[\n\"file export job added to job list\"\n]\n";
		response.setContent(content);
		return 200;
	}

	return writeError(response, 500, id_t("FileExportTriggerOutputPin"), "getBeforeTimestamp request could not be added to file export job list");
}

/**
 * get data from module by timestamp after
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	id_t configID = this->config.get_id();
	LOG_SCOPE_CONFIG( configID );
	
	boost::shared_ptr<FileExportWorker> pWorker = boost::dynamic_pointer_cast<FileExportWorker>(pModule->getWorkerByConfigID(configID));
	if (pWorker)
	{
		{ // scoped lock context
			boost::lock_guard<boost::mutex> scoped_lock(pWorker->mutexExportJobList);		
			FileExportWorker::ExportJob newJob;
			newJob.queryType = FileExportWorker::ExportJob::QueryAfterTimestamp;
			newJob.timestampForQuery = timestamp;
			newJob.numberOfUnsuccessfulRequestTries = 0;
			pWorker->exportJobList.push(newJob);
			pWorker->condExportJoblist.notify_one();
		}
		response.setContentType("application/json");
		std::string content = "[\n\"file export job added to job list\"\n]\n";
		response.setContent(content);
		return 200;
	}

	return writeError(response, 500, id_t("FileExportTriggerOutputPin"), "getAfterTimestamp request could not be added to file export job list");
}

/**
 * get data from module by time span
 *
 * @param[in] start			first timestamp of requested data
 * @param[in] end			last timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileExportTriggerOutputPin::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{
	throw ConnectedVision::runtime_error("function getAllInTimespan() not implemented for FileExportTriggerOutputPin");
}

/**
 * get log writer
 *
 * @return log writer
 */
boost::shared_ptr<Logging::ILogWriter> FileExportTriggerOutputPin::log() const
{
	if ( this->env ) 
	{
		return this->env->log(); 
	}
	else 
	{
		boost::shared_ptr<Logging::ILogWriter> log( new Logging::LogWriterNULL() );
		return log;
	}
}

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision