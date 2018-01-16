/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <helper.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include "VideoImporterModule.h"
#include "VideoImporterWorker.h"
#include "Class_VideoImporter_params.h"

#include "InputPin_VideoImporter_input_Trigger.h"
#include "OutputPin_VideoImporter_output_VideoMetadata.h"
#include "Class_VideoImporter_output_VideoMetadata.h"
#include "OutputPin_VideoImporter_output_FrameMetadata.h"
#include "Class_VideoImporter_output_FrameMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

using namespace std;
using namespace ConnectedVision;



/**
* Updates the status.
*
* @param statusStore The status store.
* @param status The status to update.
* @param stableResults The stable results template to apply to all output pins.
* @param resultsCount The number of new results since the last status update for triggering the computation of the average compuation duration.
*/
static void updateStatus(ConnectedVision::shared_ptr<ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status>> statusStore, ConnectedVision::shared_ptr<Class_generic_status> status, ConnectedVision::shared_ptr<Class_generic_status_stableResults> stableResults, int64_t resultsCount)
{
	status->set_stableResultsByPinID(stableResults, OutputPin_VideoImporter_output_VideoMetadata::PinID());
	status->set_stableResultsByPinID(stableResults, OutputPin_VideoImporter_output_FrameMetadata::PinID());
	status->set_stableResultsByPinID(stableResults, "RAWYUV420-Image");
	status->set_stableResultsByPinID(stableResults, "RAWBGR24-Image");
	status->set_stableResultsByPinID(stableResults, "RAWRGB24-Image");
	status->set_stableResultsByPinID(stableResults, "PNG-Image");

	// update the systemTimeProcessing variable according to the number of results since the last status update in order to compute the average computation duration
	for(int64_t i = 0; i < resultsCount; i++)
	{
		status->set_systemTimeProcessing(sysTime());
	}

	statusStore->save_copy(status);
}



/**
* Parses the specified JSON data and returns a valid FrameMetadata object upon success or throws an exception in case of an error.
*
* @param data The JSON data to parse.
*
* @return The FrameMetadata object.
*/
static boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> parseFrameMetadata(const std::string& data)
{
	auto metadata = boost::make_shared<Class_VideoImporter_output_FrameMetadata>();
	metadata->parseJson(data);
	return metadata;
}



/**
* Returns the FrameMetadata output object for the specified index or throws an exception in case of an error.
*
* @param pin The output pin.
* @param index The output pin index.
*
* @return The FrameMetadata output obect.
*/
static boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> getFrameMetadataByIndex(boost::shared_ptr<IConnectedVisionOutputPin> pin, int64_t index)
{
	auto response = boost::make_shared<ConnectedVisionResponse>();
	pin->getByIndex(index, *response);
	boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> metadata;
	
	string errorMessage = "failed to query FrameMetadata output pin by index " + intToStr(index);

	try
	{
		metadata = parseFrameMetadata(response->getContentConst());
	}
	catch(const exception& e)
	{
		throw ConnectedVision::runtime_error(errorMessage + " (error: " + e.what() + ")");
	}

	if(!metadata)
	{
		throw ConnectedVision::runtime_error(errorMessage + " (metadata object is null)");
	}

	return metadata;
}



/**
* Returns the FrameMetadata output objects after the specified timestamp or throws an exception in case of an error.
*
* @param pin The output pin.
* @param timestamp The output pin timestamp.
*
* @return The FrameMetadata output obects vector.
*/
static std::vector<boost::shared_ptr<Class_VideoImporter_output_FrameMetadata>> getFrameMetadataAfterTimestamp(boost::shared_ptr<IConnectedVisionOutputPin> pin, timestamp_t timestamp)
{
	auto response = boost::make_shared<ConnectedVisionResponse>();
	pin->getAfterTimestamp(timestamp, *response);
	
	vector<boost::shared_ptr<Class_VideoImporter_output_FrameMetadata>> vec;
	rapidjson::Document elements;

	if(elements.Parse<0>(response->getContentConst().c_str()).HasParseError())
	{
		return vec;
	}

	for(rapidjson::SizeType i = 0; i < elements.Size(); i++)
	{
		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		elements[i].Accept(writer);
		string element(buffer.GetString());

		boost::shared_ptr<Class_VideoImporter_output_FrameMetadata> metadata;
		string errorMessage = "failed to query FrameMetadata output pin after time " + intToStr(timestamp);

		try
		{
			metadata = parseFrameMetadata(element);
		}
		catch(const exception& e)
		{
			throw ConnectedVision::runtime_error(errorMessage + " (" + e.what() + ")");
		}

		if(!metadata)
		{
			throw ConnectedVision::runtime_error(errorMessage + " (metadata object is null)");
		}

		vec.push_back(metadata);
	}

	return vec;
}



void VideoImporterWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module.getStatusStore();
	auto status = statusStore->getByID(configID)->copy();

	try
	{
		status = this->module.init(this->config);

		// start algorithm

		// read config params
		Class_VideoImporter_params params;
		params.parseJson( this->config->get_params() );

		// get input pins
		// Trigger input
		ConnectedVision::shared_ptr<InputPin_VideoImporter_input_Trigger> inputTriggerPin;
		
		// start the Trigger input pin if it is connected
		if(this->module.getInputPinCount(this->config, InputPin_VideoImporter_input_Trigger::PinID()) > 0)
		{
			inputTriggerPin = boost::dynamic_pointer_cast<InputPin_VideoImporter_input_Trigger>(this->module.getInputPin(this->config, InputPin_VideoImporter_input_Trigger::PinID()));
		}

		// start processing small chunks of data.
		LOG_INFO_CONFIG("start processing", configID);

		if(inputTriggerPin)
		{
			inputTriggerPin->start();

			auto metadataOutputPin = this->module.getOutputPin(config, OutputPin_VideoImporter_output_FrameMetadata::PinID());

			// make a backup of the finished stable results
			auto stableResultsFinished = status->find_stableResultsByPinID(OutputPin_VideoImporter_output_FrameMetadata::PinID());

			// reset the stable results
			auto stableResults = ConnectedVision::make_shared<Class_generic_status_stableResults>();
			stableResults->set_indexStart(-1);
			stableResults->set_indexEnd(-1);
			stableResults->set_timestampStart(-1);
			stableResults->set_timestampEnd(-1);

			status->set_estimatedFinishTime(sysTime() + 1000);
			status->set_progress(0.0);
			status->set_status_running();
			
			updateStatus(statusStore, status, stableResults, 1);

			int64_t triggerIndexEnd = -1;
			int64_t triggerIndexEndPrev = -1;
			auto inputTriggerStatus = inputTriggerPin->getStatus();

			auto frameMetadataVec = getFrameMetadataAfterTimestamp(metadataOutputPin, params.get_timestampStart() - 1);

			if(frameMetadataVec.empty())
			{
				throw ConnectedVision::runtime_error("failed to query FrameMetadata output pin after time " + intToStr(params.get_timestampStart() - 1) + " (vector is empty)");
			}

			int64_t indexStart = frameMetadataVec.front()->get_framenumber();
			int64_t indexEnd = min(indexStart + triggerIndexEnd, stableResultsFinished->get_indexEnd());
			timestamp_t timestampStart = frameMetadataVec.front()->get_timestamp();

			while(inputTriggerStatus.is_status_running() && (indexEnd < 0 || indexEnd < stableResultsFinished->get_indexEnd()) && this->controller.nextIterationStep())
			{
				bool newResultsFlag = false;

				do
				{
					inputTriggerStatus = inputTriggerPin->getStatus();
					newResultsFlag = triggerIndexEnd < inputTriggerStatus.get_stableResults()->back()->get_indexEnd();

					if(!newResultsFlag)
					{
						sleep_ms(10);
					}
				}
				while(!newResultsFlag && inputTriggerStatus.is_status_running() && this->controller.intermediateContinueCheck());

				// get the newest Trigger input end index
				triggerIndexEndPrev = triggerIndexEnd;
				triggerIndexEnd = inputTriggerStatus.get_stableResults()->back()->get_indexEnd();

				// get the timestamp of the result for the last index
				indexEnd = min(indexStart + triggerIndexEnd, stableResultsFinished->get_indexEnd());
				auto metadata = getFrameMetadataByIndex(metadataOutputPin, indexEnd);

				if(indexEnd != metadata->get_framenumber())
				{
					throw ConnectedVision::runtime_error("computed index (" + intToStr(indexEnd) + ") does not match frame number (" + intToStr(metadata->get_framenumber()) + ")");
				}

				// update the stable results
				if(stableResults->get_indexStart() < 0)
				{
					stableResults->set_indexStart(indexStart);
					stableResults->set_timestampStart(timestampStart);
				}

				stableResults->set_indexEnd(indexEnd);
				stableResults->set_timestampEnd(metadata->get_timestamp());

				// compute the progress
				status->set_progress(static_cast<double>(indexEnd - indexStart) / static_cast<double>(stableResultsFinished->get_indexEnd() - indexStart + static_cast<int64_t>(1)));

				// compute the estimated finish time
				timestamp_t acd = status->get_qualityOfService()->get_compuationDurationAverage();

				// if the average computation duration is undefined, then assume a fixed duration of 1000ms
				if(acd == -1)
				{
					acd = 1000;
				}

				int64_t remainingResultsCount = int64_t(stableResultsFinished->get_indexEnd() - triggerIndexEnd);
				status->set_estimatedFinishTime(sysTime() + timestamp_t(remainingResultsCount) * acd);

				updateStatus(statusStore, status, stableResults, triggerIndexEnd - triggerIndexEndPrev);
			}

			inputTriggerPin->stop();
		}

		// update status
		status->set_estimatedFinishTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );

		if ( this->controller.intermediateContinueCheck() )
		{
			// worker has finished
			status->set_progress( 1.0 );
			status->set_status_finished();
			LOG_INFO_CONFIG("worker finished", configID);
		}
		else
		{
			// worker has been stopped
			status->set_status_stopped();
			LOG_INFO_CONFIG("worker forced to stop", configID);
		}

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
		// 	last resort, before crash
	}
}

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision