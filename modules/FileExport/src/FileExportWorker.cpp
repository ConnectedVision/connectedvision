/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** FileExportWorker.cpp
**
** written by Michael Rauter
** 
*******************************************************/

#include <string>
#include <fstream>
#include <time.h>

#include <helper.h>

#include <boost/shared_ptr.hpp>
#include <boost/numeric/conversion/bounds.hpp>
#include <boost/limits.hpp>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/chrono.hpp>
#include <boost/algorithm/string/replace.hpp>


#include "FileExportModule.h"
#include "FileExportWorker.h"
#include "InputPin_ArbitraryData.h"

namespace ConnectedVision {
namespace Module {
namespace FileExport {

using namespace std;

#define DEFAULT_DESIGNATED_RINGBUFFER_MEMORY_IN_BYTES 250000000

FileExportWorker::FileExportWorker(IModuleEnvironment *env, ConnectedVisionModule *module, boost::shared_ptr<const Class_generic_config> config) : 
	ConnectedVisionAlgorithmWorker(env, module, config)
{
	exportElementRunningUniqueID = 0;
}

FileExportWorker::~FileExportWorker()
{
}

void FileExportWorker::stop()
{
	this->go = false;
	boost::mutex::scoped_lock scoped_lock(this->mutexExportJobList);
	this->condExportJoblist.notify_one();
	scoped_lock.unlock();

	ConnectedVisionAlgorithmWorker::stop();
}


void FileExportWorker::vecFilepathFormatDescriptorAppendStaticString(const std::string &stringToAppend, std::vector<FilepathFormatDescriptorElement> &vecFilepathFormatDescriptor)
{
	if (vecFilepathFormatDescriptor.size()>0)
	{
		FilepathFormatDescriptorElement *pElement = &vecFilepathFormatDescriptor.back();
		if (pElement->typeFilepathFormatDescriptorElement == FilepathFormatDescriptorElement::TYPE_STRING)
		{
			pElement->elementString += stringToAppend;
			return;
		}
	}

	FilepathFormatDescriptorElement element;
	element.typeFilepathFormatDescriptorElement = FilepathFormatDescriptorElement::TYPE_STRING;
	element.elementString = stringToAppend;
	vecFilepathFormatDescriptor.push_back(element);
}

void FileExportWorker::parseAndProcessFilepathComponent(const std::string &stringComponentToParse, std::vector<FilepathFormatDescriptorElement> &vecFilepathFormatDescriptor)
{
	size_t pos;
	std::string tmpString = stringComponentToParse;
	while(tmpString.size()>0)
	{
		if (tmpString.at(0) == '[')
		{
			if (tmpString.at(1) == '[')
			{
				vecFilepathFormatDescriptorAppendStaticString("[", vecFilepathFormatDescriptor);
				tmpString = tmpString.substr(2, string::npos);
			}
			else
			{
				pos = tmpString.find_first_of("]");
				if (pos != string::npos)
				{
					FilepathFormatDescriptorElement element;
					element.typeFilepathFormatDescriptorElement = FilepathFormatDescriptorElement::TYPE_PLACEHOLDER;
					element.elementString = tmpString.substr(0, pos+1);
					vecFilepathFormatDescriptor.push_back(element);
					tmpString = tmpString.substr(pos+1, string::npos);
				}
				else
				{
					throw ConnectedVision::runtime_error("bad filepath format: no closing ']' was found to previously opening '['");
				}
			}
		}
		else if (tmpString.at(0) == ']')
		{
			if (tmpString.at(1) == ']')
			{
				vecFilepathFormatDescriptorAppendStaticString("]", vecFilepathFormatDescriptor);
				tmpString = tmpString.substr(2, string::npos);
			}
			else
			{
				throw ConnectedVision::runtime_error("bad filepath format: closing ']' was found but no matching previous opened '['");
			}
		}
		else
		{
			pos = tmpString.find_first_of("[]");
			vecFilepathFormatDescriptorAppendStaticString(tmpString.substr(0, pos), vecFilepathFormatDescriptor);
			if (pos != string::npos)
			{
				tmpString = tmpString.substr(pos, string::npos);
			}
			else
			{
				tmpString = "";
			}
		}
	}
}

std::string FileExportWorker::getFilepathFromFilepathFormatDescriptor(std::vector<FilepathFormatDescriptorElement> &vecFilepathFormatDescriptor, FileExportWorker::ExportJob &exportJobInfo)
{
	std::string outputPath = "";
	for (unsigned int i=0; i<vecFilepathFormatDescriptor.size(); i++)
	{
		FilepathFormatDescriptorElement *pElement = &vecFilepathFormatDescriptor.at(i);
		if (pElement->typeFilepathFormatDescriptorElement == FilepathFormatDescriptorElement::TYPE_STRING)
		{
			outputPath += pElement->elementString;
		}
		else if (pElement->typeFilepathFormatDescriptorElement == FilepathFormatDescriptorElement::TYPE_PLACEHOLDER)
		{
			if (pElement->elementString.compare("[timestamp]") == 0)
			{
				if (exportJobInfo.queryType == ExportJob::QueryByTimestamp)
				{
					outputPath += boost::lexical_cast<std::string>(exportJobInfo.timestampForQuery);
				}
			}
			else if (pElement->elementString.compare("[index]") == 0)
			{
				if (exportJobInfo.queryType == ExportJob::QueryByIndex)
				{
					outputPath += boost::lexical_cast<std::string>(exportJobInfo.indexForQuery);
				}
			}
			else if (pElement->elementString.compare("[identifier]") == 0)
			{
				if (exportJobInfo.queryType == ExportJob::QueryByID)
				{
					outputPath += boost::lexical_cast<std::string>(exportJobInfo.identifierForQuery);
				}
			}
			else if ((pElement->elementString.substr(0,19).compare("[uniqueRunningIndex") == 0)&&(pElement->elementString.at(pElement->elementString.length()-1)==']'))
			{
				if (pElement->elementString.at(19) == '.')
				{
					std::string tmpString = pElement->elementString.substr(20,string::npos); // omitting '.' character
					tmpString = tmpString.substr(0, tmpString.length()-1);
					if (tmpString.compare("") != 0)
					{
						int numDigits = boost::lexical_cast<int>(tmpString);
						std::ostringstream streamDigits;
						streamDigits << std::setfill('0') << std::setw(numDigits) << exportElementRunningUniqueID;
						outputPath += streamDigits.str();
					}
				}
				else
				{
						int numDigits = 8;
						std::ostringstream streamDigits;
						streamDigits << std::setfill('0') << std::setw(numDigits) << exportElementRunningUniqueID;
						outputPath += streamDigits.str();
				}
			}
			else if (pElement->elementString.compare("[year]") == 0)
			{
				time_t now = time(0);
				struct tm tstruct;
#ifdef _WIN32
				localtime_s(&tstruct, &now);
#else
				localtime_r(&now, &tstruct);
#endif
				outputPath += boost::lexical_cast<std::string>(1900 + tstruct.tm_year);
			}
			else if (pElement->elementString.compare("[month]") == 0)
			{
				time_t now = time(0);
				struct tm tstruct;
#ifdef _WIN32
				localtime_s(&tstruct, &now);
#else
				localtime_r(&now, &tstruct);
#endif
				outputPath += boost::lexical_cast<std::string>(tstruct.tm_mon + 1); // convert 0-11 to 1-12
			}
			else if (pElement->elementString.compare("[day]") == 0)
			{
				time_t now = time(0);
				struct tm tstruct;
#ifdef _WIN32
				localtime_s(&tstruct, &now);
#else
				localtime_r(&now, &tstruct);
#endif
				outputPath += boost::lexical_cast<std::string>(tstruct.tm_mday);
			}
			else if (pElement->elementString.compare("[hour]") == 0)
			{
				time_t now = time(0);
				struct tm tstruct;
#ifdef _WIN32
				localtime_s(&tstruct, &now);
#else
				localtime_r(&now, &tstruct);
#endif
				outputPath += boost::lexical_cast<std::string>(tstruct.tm_hour);
			}
			else if (pElement->elementString.compare("[minute]") == 0)
			{
				time_t now = time(0);
				struct tm tstruct;
#ifdef _WIN32
				localtime_s(&tstruct, &now);
#else
				localtime_r(&now, &tstruct);
#endif
				outputPath += boost::lexical_cast<std::string>(tstruct.tm_min);
			}
			else if (pElement->elementString.compare("[second]") == 0)
			{
				time_t now = time(0);
				struct tm tstruct;
#ifdef _WIN32
				localtime_s(&tstruct, &now);
#else
				localtime_r(&now, &tstruct);
#endif
				outputPath += boost::lexical_cast<std::string>(tstruct.tm_sec);
			}
		}
	}
	return(outputPath);
}

/**
 * actual algorithm worker thread function
 */
void FileExportWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module->getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status = statusStore->getByID(configID)->copy();

	// If your algorithm does NOT support RESUME, you must reset the config status and delete old results from the DB.
	// reset status
	status->resetStableResults();
	// delete previous results
	this->module->deleteResults( this->config );

	// update status timestamps
	status->set_estimatedFinishTime( -1 ); // how long do we need?
	status->set_systemTimeProcessing( sysTime() );

	try
	{
		// read config params
		params.parseJson( config->get_params() );

		std::string filepathToParse = *params.get_filepath_format();

		std::string outputPathFormat;
		std::string outputFilenameFormat;

		int pathSeparatiorPos = filepathToParse.find_last_of("/\\"); // search for last backslash or slash (split filename from path)
		if (pathSeparatiorPos != string::npos) // if found (directory of zip archive != working directory -> ) 
		{						
			outputPathFormat = filepathToParse.substr(0, pathSeparatiorPos+1);
			outputFilenameFormat = filepathToParse.substr(pathSeparatiorPos+1, string::npos);
		}
		else
		{						
			outputPathFormat = "";
			outputFilenameFormat = filepathToParse;
		}

		parseAndProcessFilepathComponent(outputPathFormat, vecOutputPathDescriptor);
		parseAndProcessFilepathComponent(outputFilenameFormat, vecOutputFilenameDescriptor);

		/*
		vecOutputPathDescriptor.clear();
		vecOutputFilenameDescriptor.clear();
		parseAndProcessFilepathComponent("./testOutput/", vecOutputPathDescriptor);
		parseAndProcessFilepathComponent("test_img_[year]-[month]-[day]_[uniqueRunningIndex.5].png", vecOutputFilenameDescriptor);
		//parseAndProcessFilepathComponent("test_img_[year]-[month].[day].:[hour]:[minute]:[second].png", vecOutputFilenameDescriptor);
		//parseAndProcessFilepathComponent("test[[output]][timestamp]_img.png", vecOutputFilenameDescriptor);
		//parseAndProcessFilepathComponent("test[[output]][uniqueRunningIndex.5]_img.png", vecOutputFilenameDescriptor);
		*/

		isConstantOutputPath = true;
		for (unsigned int i=0; i<vecOutputPathDescriptor.size(); i++)
		{
			if (vecOutputPathDescriptor.at(i).typeFilepathFormatDescriptorElement ==  FilepathFormatDescriptorElement::TYPE_PLACEHOLDER)
			{
				isConstantOutputPath = false;
				break;
			}
		}

		if (isConstantOutputPath == true) // if output path is constant, create directory now (once)
		{
			std::string outputPath = "";
			for (unsigned int i=0; i<vecOutputPathDescriptor.size(); i++)
			{
				outputPath += vecOutputPathDescriptor.at(i).elementString;
			}
			boost::filesystem::create_directories(outputPath);
		}


		// start inputpin for data
		boost::shared_ptr<FileExportModule::InputPin_ArbitraryData> inputPin_data = boost::dynamic_pointer_cast<FileExportModule::InputPin_ArbitraryData>( this->module->getInputPin( this->config, FileExportModule::InputPin_ArbitraryData::PinID() ) );
		Class_generic_status dataStatus = inputPin_data->start();



		LOG_INFO_CONFIG("start processing", configID);
		do
		{
			boost::shared_ptr<Class_RawData> data;
			bool doFileExport = false;

			FileExportWorker::ExportJob job;
			{ // scoped lock context
				//boost::lock_guard<boost::mutex> scoped_lock(mutexExportJobList);
				boost::mutex::scoped_lock scoped_lock(mutexExportJobList);

				if (this->exportJobList.size()==0)
				{
					condExportJoblist.wait(scoped_lock);
					if (!go)
					{
						break;
					}
				}

				if (this->exportJobList.size()>0)
				{
					FileExportWorker::ExportJob &refJob = this->exportJobList.front(); // get reference (since job.numberOfUnsuccessfulRequestTries will be possibly changed)
					//this->exportJobList.pop();

					try
					{
						switch(refJob.queryType)
						{
						case ExportJob::QueryByID:
							data = inputPin_data->getByID(refJob.identifierForQuery);
							break;
						case ExportJob::QueryByIndex:
							data = inputPin_data->getByIndex(refJob.indexForQuery);
							break;
						case ExportJob::QueryByTimestamp:
							data = inputPin_data->getByTimestamp(refJob.timestampForQuery).at(0);
							break;
						case ExportJob::QueryBeforeTimestamp:
							data = inputPin_data->getBeforeTimestamp(refJob.timestampForQuery).at(0);
							break;
						case ExportJob::QueryAfterTimestamp:
							data = inputPin_data->getAfterTimestamp(refJob.timestampForQuery).at(0);
							break;
						default:
							throw std::runtime_error("error in FileExportWorker::run(): job query type not implemented");
						}

						this->exportJobList.pop();
						
						doFileExport = true;
					}
					catch (...) // if something went wrong when doing the data query (exportJobList.pop() was not done and so the data request is issued again on next iteration)
					{
						refJob.numberOfUnsuccessfulRequestTries++;
						if (refJob.numberOfUnsuccessfulRequestTries>NUM_MAX_REQUEST_RETRIES)
						{
							this->exportJobList.pop();
							exportElementRunningUniqueID++; // increase running unique id - this is important since we want to be able to have several parallel file export modules and want them to be synchronized (in terms of this id), so requests must not desync the id of several modules
						}
					}

					job = refJob; // make copy (will be needed as read-only outside of mutex lock scope)
				}
			}

			if (doFileExport == true) // it is done here (afterwards) so the scoped lock on the mutex can be released before file operation starts
			{
				if (data)
				{
					std::string path = this->getFilepathFromFilepathFormatDescriptor(vecOutputPathDescriptor, job);
					/*if ((path.at(path.length()-1) != '/')&&(path.at(path.length()-1) != '\\'))
					{
						path += '/';
					}*/
					if (isConstantOutputPath == false)
					{
						boost::filesystem::create_directories(path);
					}
					std::string filepath = path + this->getFilepathFromFilepathFormatDescriptor(vecOutputFilenameDescriptor, job);
					std::ofstream outFile(filepath, ios::binary);
					outFile << data->getconst();
					outFile.flush();
					outFile.close();
					exportElementRunningUniqueID++;
				}
			}

			// update status
			//stableResultsImagesMetadata->set_indexEnd( 0 ); // TODO: frame index
			//stableResultsImagesMetadata->set_timestampEnd( currentTimeStampOfLatestFrame ); // TODO
							
			// compute progress
			status->set_progress( 1.0f );

			status->set_systemTimeProcessing( sysTime() );

			statusStore->save_copy(status);
			
		} while (go);

		// update status
		status->set_estimatedFinishTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );
		// worker has finished
		status->set_progress( 0.0f );
		status->set_status_stopped();
		LOG_INFO_CONFIG("worker stopped", configID);
		statusStore->save_copy(status);
	}
	catch (const std::exception& e)
	{
		try
		{
			LOG_ERROR_CONFIG( e.what(), configID);
			
			status->set_status_error();
			status->set_message( e.what() );
			status->set_systemTimeProcessing( sysTime() );
			status->set_estimatedFinishTime( -1 );
			statusStore->save_copy(status);
		}
		catch (...)
		{
				// what can we do now???
		}
	}
	catch (...)
	{
			// what can we do now???
	}
}

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision