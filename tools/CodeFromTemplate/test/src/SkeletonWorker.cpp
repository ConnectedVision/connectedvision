#include <helper.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include "SkeletonModule.h"
#include "SkeletonWorker.h"
#include "Class_Skeleton_params.h"

#include "InputPin_Skeleton_input_Detections.h"
#include "OutputPin_Skeleton_output_Average.h"
#include "Class_Skeleton_output_Average.h"

namespace ConnectedVision {
namespace test {

using namespace std;
using namespace ConnectedVision;

void SkeletonWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();
	int64_t index = 0;

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module->getStatusStore();
	auto status = statusStore->getByID(configID)->copy();

	// if your algorithm does NOT support RESUME, you must reset the config status and delete old results from the store
	// reset status
	status->resetStableResults();
	// delete previous results
	this->module->deleteResults( this->config );

	// update status timestamps
	status->set_estimatedFinishTime( sysTime() + 1000 ); // TODO: how long do we need?
	status->set_systemTimeProcessing( sysTime() );
	statusStore->save_copy(status);

	try
	{
		// start algorithm

		// read config params
		Class_Skeleton_params params;
		params.parseJson( this->config->get_params() );

		// get input pins
		// Detections input
		ConnectedVision::shared_ptr<InputPin_Skeleton_input_Detections> inputDetectionsPin = boost::dynamic_pointer_cast<InputPin_Skeleton_input_Detections>( this->module->getInputPin( this->config, InputPin_Skeleton_input_Detections::PinID() ) ); // get input pin from pool and cast to Detections pin
		auto inputDetectionsStatus = inputDetectionsPin->start(); // start previous module and get current status
		pinID_t inputDetectionsOutputPinID = inputDetectionsPin->getOutputPinID(); // map input pin ID to output pin ID
		auto inputDetectionsStableResults = inputDetectionsStatus.find_stableResultsByPinID( inputDetectionsOutputPinID );

// TODO --> additional input pins come HERE! <--

		// get output store
		// Average store
		auto outputAverageStore = dynamic_cast<SkeletonModule *>(this->module)->storeManagerAverage->getReadWriteStore(configID);

// TODO --> additional stores / output pins come HERE! <--

		// reset stable results
		status->set_stableResultsByPinID( Class_generic_status_stableResults::createFromStore(*outputAverageStore), OutputPin_Skeleton_output_Average::PinID() );

		// start processing small chunks of data.
		LOG_INFO_CONFIG("start processing", configID);

		do
		{
			// get status from previous module
			inputDetectionsStatus = inputDetectionsPin->getStatus();
			inputDetectionsStableResults = inputDetectionsStatus.find_stableResultsByPinID( inputDetectionsOutputPinID );

			// if there is no new input data, then wait for some time and try again
			if ( inputDetectionsStatus.is_status_running() && index > inputDetectionsStableResults->getconst_indexEnd() && this->go )
			{
				this->sleep_ms( 1000 );
				continue;
			}

			// process all data we got so far
			for (; index <= inputDetectionsStableResults->getconst_indexEnd() && this->go; ++index)
			{
				// get Detections data
				auto detections = inputDetectionsPin->getByIndex( index );

				if ( !detections )
				{
					throw ConnectedVision::runtime_error("Detections not found for index: " + intToStr(index) );
				}

				// get other data
				timestamp_t time = detections->getconst_timestamp();

				// prepare output objects
				auto outputAverage = outputAverageStore->create();

// TODO --> do some algorithmic work HERE! <--
// YES YOU HAVE TO WRITE SOME CODE YOUR OWN ...!
// NOW IS THE TIME AND HERE IS THE PLACE!

				// save results
				outputAverageStore->save_move( outputAverage );

				// update status
				// compute stable results for Average
				status->set_stableResultsByPinID( Class_generic_status_stableResults::createFromStore(*outputAverageStore), OutputPin_Skeleton_output_Average::PinID() );

				// compute progress
				double progress = 0.0;

				if(inputDetectionsStableResults->getconst_indexEnd() > -1)
				{
					progress = static_cast<double>(max(int64_t(1), index - inputDetectionsStableResults->getconst_indexStart()));
					progress /= static_cast<double>(max(int64_t(1), inputDetectionsStableResults->getconst_indexEnd() - inputDetectionsStableResults->getconst_indexStart()));
				}

				status->set_progress(progress);

				// compute ETA (we will finish when the previous module is finished)
				status->set_estimatedFinishTime( inputDetectionsStatus.get_estimatedFinishTime() );
				status->set_systemTimeProcessing( sysTime() );

				// No bulk save, so we can update the status immediately. Otherwise, wait until the result data are saved
				statusStore->save_copy(status);
			}

		} while ( inputDetectionsStatus.is_status_running() && this->go ); // do-while there is input data to process

		// update status
		status->set_estimatedFinishTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );

		if ( this->go )
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

} // namespace test
} // namespace ConnectedVision