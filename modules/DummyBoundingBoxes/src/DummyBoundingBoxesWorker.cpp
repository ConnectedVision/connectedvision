/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <string>
#include <time.h>

#include <helper.h>

#include "DummyBoundingBoxesWorker.h"

#include "Class_DummyBoundingBoxes_params.h"
#include "InputPin_DummyBoundingBoxes_input_Trigger.h"
#include "OutputPin_DummyBoundingBoxes_output_Detections.h"
#include "OutputPin_DummyBoundingBoxes_output_ObjectData.h"

namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

using namespace std;

/**
 * actual algorithm worker thread function
 */
void DummyBoundingBoxesWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module.getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status = statusStore->getByID(configID)->copy();

	// find last processed index
	auto detectionsStableResults = ConnectedVision::make_shared<Class_generic_status_stableResults>();
	auto objectsStableResults = ConnectedVision::make_shared<Class_generic_status_stableResults>();

	try
	{
		// start algorithm

		// read config params
		Class_DummyBoundingBoxes_params params;
		params.parseJson( this->config->get_params() );

		// start the trigger input pin if it is connected
		ConnectedVision::shared_ptr<InputPin_DummyBoundingBoxes_input_Trigger> triggerInputPin;
		
		if(this->module.getInputPinCount(this->config, InputPin_DummyBoundingBoxes_input_Trigger::PinID()) > 0)
		{
			triggerInputPin = boost::dynamic_pointer_cast<InputPin_DummyBoundingBoxes_input_Trigger>(this->module.getInputPin(this->config, InputPin_DummyBoundingBoxes_input_Trigger::PinID()));
			triggerInputPin->start();
		}

		// get output stores
		auto detectionsStore = this->module.detectionsStoreManager->getReadWriteStore(configID);
		detectionsStore->deleteAll();
		detectionsStableResults->importFromStore( *detectionsStore );
		auto objectsStore = this->module.objectsStoreManager->getReadWriteStore(configID);
		objectsStore->deleteAll();
		objectsStableResults->importFromStore( *objectsStore );

		// interpolate bounding boxes
		LOG_INFO_CONFIG("start processing", configID);
		
		double f = 0;
		double dtop = params.get_boundingBoxEnd()->get_top() - params.get_boundingBoxStart()->get_top();
		double dleft = params.get_boundingBoxEnd()->get_left() - params.get_boundingBoxStart()->get_left();
		double dbottom = params.get_boundingBoxEnd()->get_bottom() - params.get_boundingBoxStart()->get_bottom();
		double dright = params.get_boundingBoxEnd()->get_right() - params.get_boundingBoxStart()->get_right();
		timestamp_t stime = params.get_timestampStart();
		timestamp_t dtime = params.get_timestampEnd() - params.get_timestampStart();

		// reset status
		status->set_estimatedFinishTime( sysTime() +1000 );
		status->set_systemTimeProcessing( sysTime() );
		statusStore->save_copy(status);

		auto object = objectsStore->create();
		object->set_id( "1" );
		object->set_objectID( "1" );
		object->set_timestamp( stime );

		int indexEnd = -1;
		
		for (int64_t idx = 0; idx < params.get_count() && this->controller.nextIterationStep(); idx++)
		{
			if(triggerInputPin)
			{
				Class_generic_status triggerInputPinStatus = triggerInputPin->getStatus();
				bool newResultsFlag = false;

				do
				{
					newResultsFlag = indexEnd < triggerInputPinStatus.get_stableResults()->back()->get_indexEnd();

					if(!newResultsFlag)
					{
						sleep_ms(100);
					}

					triggerInputPinStatus = triggerInputPin->getStatus();
				}
				while(triggerInputPinStatus.is_status_running() && !newResultsFlag && this->controller.nextIterationStep());

				indexEnd = triggerInputPinStatus.get_stableResults()->back()->get_indexEnd();
			}

			// compute factor according to index
			if ( params.get_count() > 1 )
				f = (double)idx / ( (params.get_count()-1) );
			else
				f = 1;

			// new detection object
			auto detection = detectionsStore->create();
			detection->set_id( intToStr(idx+1) );
			detection->set_objectID( "1" );
			detection->set_timestamp( stime + round_int64(dtime * f) );
			
			// set boundingBox object 
			auto boundingBox = Class_DummyBoundingBoxes_output_Detections_boundingBox_p( new Class_DummyBoundingBoxes_output_Detections_boundingBox() );
			boundingBox->set_top( params.get_boundingBoxStart()->get_top() + dtop * f );
			boundingBox->set_left( params.get_boundingBoxStart()->get_left() + dleft * f );
			boundingBox->set_bottom( params.get_boundingBoxStart()->get_bottom() + dbottom * f );
			boundingBox->set_right( params.get_boundingBoxStart()->get_right() + dright * f );
			detection->set_boundingBox( boundingBox );

			// set basePoint object 
			auto basePoint = Class_DummyBoundingBoxes_output_Detections_basePoint_p( new Class_DummyBoundingBoxes_output_Detections_basePoint() );
			basePoint->set_x( (boundingBox->get_left() + boundingBox->get_right()) / 2);
			basePoint->set_y( (boundingBox->get_top() + boundingBox->get_bottom()) / 2);
			detection->set_basePoint( basePoint );

			// set object data detections;
			std::string json = detection->toJson();
			Class_DummyBoundingBoxes_output_ObjectData_detections d(json);
			object->add_detections(d);

			// save detection
			LOG_INFO_CONFIG("save detection: #" + intToStr(idx), configID);
			detectionsStore->save_move(detection);


			// update status
			detectionsStableResults->importFromStore( *detectionsStore );
			status->set_stableResultsByPinID( detectionsStableResults, OutputPin_DummyBoundingBoxes_output_Detections::PinID() );

			status->set_progress( f );
			auto dt = round_int64( (params.get_delay()+100) * (1.0 - f) );
			status->set_estimatedFinishTime( sysTime() + dt );
			status->set_systemTimeProcessing( sysTime() );
			statusStore->save_copy(status);

			// simulate long run time
			if ( params.get_delay() )
			{
				dt = round_int64( (params.get_delay() * 1000) / params.get_count() );
				sleep_ms( dt );
			}
		}
		// save object
		LOG_INFO_CONFIG("save object: #" + IDToStr(object->getconst_id()), configID);
		objectsStore->save_move(object);

		// algorithm finished -> do finalization

		// update status
		detectionsStableResults->importFromStore( *detectionsStore );
		status->set_stableResultsByPinID( detectionsStableResults, OutputPin_DummyBoundingBoxes_output_Detections::PinID() );
		objectsStableResults->importFromStore( *objectsStore );
		status->set_stableResultsByPinID( objectsStableResults, OutputPin_DummyBoundingBoxes_output_ObjectData::PinID() );
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
			// worker hase been stopped
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


}

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision