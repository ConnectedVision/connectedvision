/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/scoped_ptr.hpp>

#include <helper.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include "SkeletonModule.h"
#include "SkeletonWorker.h"
#include "Class_Skeleton_params.h"
#include <Module/Control/Class_RawData.h>
#include <Module/InputPins/InputPin_PNG.h>
#include "InputPin_Skeleton_input_Detections.h"
#include "OutputPin_Skeleton_output_Average.h"
#include "Class_Skeleton_output_Average.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define ENABLE_RESUME	1
#define ENABLE_BULKSAVE	1

namespace ConnectedVision {
namespace Module {
namespace Skeleton {

using namespace std;
using namespace ConnectedVision;
using namespace ConnectedVision::DataHandling;

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

	// find last processed index
	auto stableResults = status->find_stableResultsByPinID( OutputPin_Skeleton_output_Average::PinID() ); // search by output pin ID

#if ENABLE_RESUME
	index = stableResults->get_indexEnd() + 1;
#else
	// If your algorithm does NOT support RESUME, you must reset the config status and delete old results from the DB.
	// reset status
	status->resetStableResults();
	// delete previous results
	this->module->deleteResults( this->config );
#endif

	// update status timestamps
	status->set_estimatedFinishTime( sysTime() + 1000 ); // TODO: how long do we need?
	status->set_systemTimeProcessing( sysTime() );
	statusStore->save_copy(status);

	try
	{
		// start algorithm

		// read config params (if your module does not support/have dynamic parameters one can get them before worker loop)
		//Class_Skeleton_params params;
		//params.parseJson( this->config->get_params() ); // directly from config object

		// get input pins
		// PNG input
		ConnectedVision::shared_ptr<InputPin_PNG> inputPngPin = boost::dynamic_pointer_cast<InputPin_PNG>( this->module->getInputPin( this->config, InputPin_PNG::PinID() ) ); // get input pin from pool and cast to PNG pin
		auto pngStatus = inputPngPin->start(); // start previous module and get current status

		// Detections input
		ConnectedVision::shared_ptr<InputPin_Skeleton_input_Detections> inputDetectionsPin = boost::dynamic_pointer_cast<InputPin_Skeleton_input_Detections>( this->module->getInputPin( this->config, InputPin_Skeleton_input_Detections::PinID() ) ); // get input pin from pool and cast to Detections pin
		auto inputDetectionsStatus = inputDetectionsPin->start(); // start previous module and get current status
		pinID_t inputDetectionsOutputPinID = inputDetectionsPin->getOutputPinID(); // map input pin ID to output pin ID
		auto inputDetectionsStableResults = inputDetectionsStatus.find_stableResultsByPinID( inputDetectionsOutputPinID );

// TODO --> additional input pins come HERE! <--

		// get output store
		// Average store
		auto storeAverage = dynamic_cast<SkeletonModule *>(this->module)->storeManagerAverage->getReadWriteStore(configID);

// TODO --> additional stores / output pins come HERE! <--


#if ENABLE_BULKSAVE
		// prepare bulk save vector
		std::vector< ConnectedVision::shared_ptr<const Class_Skeleton_output_Average> > average_vec;
#endif

		// start processing small chunks of data.
		LOG_INFO_CONFIG("start processing", configID);

		do
		{
			// read config params (if your module does support/have dynamic parameters get them here inside worker loop on every iteration with function module->getUpdatedParams(configID))
			Class_Skeleton_params params;
			params.parseJson( this->module->getUpdatedParams(this->config->getconst_id()) );

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
					throw std::runtime_error("Detections not found for index: " + intToStr(index) );
				}

				// get image (querying end timestamp - 1 returns the data object with a timestamp equal to or greater than the specified timestamp)
				boost::shared_ptr<Class_RawData> pngRawData = inputPngPin->getAfterTimestamp( detections->get_timestamp() - 1 ).at(0);
				auto pngImg = boost::make_shared<std::string>(pngRawData->getconst());

				if ( pngImg->find("PNG") != 1 )
				{
					string message = "data after time " + intToStr(detections->get_timestamp() - 1) + " is not a PNG image";
					LOG_WARN_CONFIG(message, configID);
					throw std::runtime_error(message + " (" + *pngImg + ")");
				}

// TODO --> do some algorithmic work HERE! <--

				// call algorithmic sub routing
				boost::shared_ptr< IDataAllocator<Class_Skeleton_output_Average> > allocator = storeAverage; // we just need the allocator and not the whole store (this conversion could also be done implicitly)
				auto outputAverage = this->computeAverage( detections, pngImg, allocator );

#if !(ENABLE_BULKSAVE)
				// save results
				storeAverage->save_move( outputAverage );

				// No bulk save, so we can update the status immediately. Otherwise, wait until the result data are saved
				statusStore->save_copy(status);

				// update status
				stableResults->importFromStore( *storeAverage );
				status->set_stableResultsByPinID( stableResults, OutputPin_Skeleton_output_Average::PinID() );
#else
				// prepare vector
				average_vec.push_back(outputAverage);
#endif
				
				// compute progress
				double progress = 0.0;
				
				if(inputDetectionsStableResults->getconst_indexEnd() > -1)
				{
					progress = static_cast<double>(max(int64_t(1), index - inputDetectionsStableResults->getconst_indexStart()));
					progress /= static_cast<double>(max(int64_t(1), inputDetectionsStableResults->getconst_indexEnd() - inputDetectionsStableResults->getconst_indexStart()));
				}

				status->set_progress(progress);

				// compute ETA (we will finish when the previous module is ready)
				status->set_estimatedFinishTime( inputDetectionsStatus.get_estimatedFinishTime() );
				status->set_systemTimeProcessing( sysTime() );

			}

#if ENABLE_BULKSAVE
			storeAverage->save_constVector(average_vec);

			stableResults->importFromStore( *storeAverage );
			status->set_stableResultsByPinID( stableResults, OutputPin_Skeleton_output_Average::PinID() );
			statusStore->save_copy(status);
#endif

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


ConnectedVision::shared_ptr<const Class_Skeleton_output_Average> SkeletonWorker::computeAverage(
	boost::shared_ptr<Class_Skeleton_input_Detections> detections, 
	boost::shared_ptr<std::string> pngImg,
	boost::shared_ptr< ConnectedVision::DataHandling::IDataAllocator<Class_Skeleton_output_Average> > allocator )
{

// TODO --> do some algorithmic work HERE! <--
	/*
		YES, you need to do some real programming here :-)
	*/

	boost::shared_ptr<Class_Skeleton_input_Detections_boundingBox> bb = detections->get_boundingBox();

	// decode PNG image
	unsigned int width, height, step, bytesPerPixel;

	cv::_InputArray input(pngImg->c_str(), pngImg->size());
	cv::Mat decodedImage = cv::imdecode(input, cv::IMREAD_COLOR);
	if ( decodedImage.data == NULL )   
	{
		throw std::runtime_error("error decoding png data");
	}
	
	unsigned char *image = decodedImage.data;
	width = decodedImage.cols;
	height = decodedImage.rows;
	step = decodedImage.step1();
	bytesPerPixel = decodedImage.step[1];

	auto average = allocator->create();

	// compute average color
	Class_Skeleton_output_Average_color color;
	int32_t red = 0;
	int32_t green = 0;
	int32_t blue = 0;
	int64_t size = (int64_t)( ( bb->get_bottom() - bb->get_top() )*height * ( bb->get_right() - bb->get_left() )*width );
	// loop over bounding-box
	for ( int y = (int)(bb->get_top()*height ); y <= (int)(bb->get_bottom()*height ); y++  )
	{
		for ( int x = (int)(bb->get_left()*width); x <= (int)(bb->get_right()*width); x++ )
		{
			unsigned char *ptr = image +  y * step + x * bytesPerPixel;
			red += ptr[0];
			green += ptr[1];
			blue += ptr[2];
		}
	}
	// final calculation
	if ( size > 0 )
	{
		color.set_R( red / size );
		color.set_G( green / size );
		color.set_B( blue / size );
	}

	// set output data
	average->set_id( detections->get_id() );
	average->set_timestamp( detections->get_timestamp() );
	// set average color
	average->set_color( color );

	return allocator->make_const(average);
}

}}} // namespace