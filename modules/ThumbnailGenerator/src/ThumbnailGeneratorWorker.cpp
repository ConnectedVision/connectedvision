/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <string>
#include <time.h>

#include <helper.h>

#include "ThumbnailGeneratorWorker.h"

#include <Module/InputPins/InputPin_PNG.h>
#include "Class_ThumbnailGenerator_params.h"
#include "InputPin_ThumbnailGenerator_input_BoundingBox.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

using namespace std;

/**
 * actual algorithm worker thread function
 */
void ThumbnailGeneratorWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();

	LOG_SCOPE_CONFIG(configID);
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module.getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status = statusStore->getByID(configID)->copy();

	try
	{
		// read config params
		Class_ThumbnailGenerator_params params;
		params.parseJson(config->get_params());

		// init PNG input pin
		boost::shared_ptr<InputPin_PNG> pngInputPin = boost::dynamic_pointer_cast<InputPin_PNG>(this->module.getInputPin(this->config, InputPin_PNG::PinID()));
		pngInputPin->start();

		// init bounding box input pin
		boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox> boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module.getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));
		boundingBoxInputPin->start();

		Class_generic_status boundingBoxStatusPrev;
		Class_generic_status pngStatusPrev;

		Class_generic_status boundingBoxStatus;
		Class_generic_status pngStatus;

		do
		{
			// get status of input pins
			try
			{
				boundingBoxStatus = boundingBoxInputPin->getStatus();
				pngStatus = pngInputPin->getStatus();
			}
			catch(...)
			{
				sleep_ms(100);
				continue;
			}

			boost::shared_ptr<Class_generic_status_stableResults> boundingBoxStableResults = boundingBoxStatus.find_stableResultsByPinID(boundingBoxInputPin->getOutputPinID());
			boost::shared_ptr<Class_generic_status_stableResults> pngStableResults = pngStatus.find_stableResultsByPinID(pngInputPin->getOutputPinID());

			// update the status
			if(boundingBoxStatus.get_systemTimeProcessing() != boundingBoxStatusPrev.get_systemTimeProcessing() || pngStatus.get_systemTimeProcessing() != pngStatusPrev.get_systemTimeProcessing())
			{
				// bounding box overlay
				Class_generic_status_stableResults_p boundingBoxOverlayStableResults = status->find_stableResultsByPinID("BoundingBoxOverlay");
				boundingBoxOverlayStableResults->set_indexStart(pngStableResults->get_indexStart());
				boundingBoxOverlayStableResults->set_indexEnd(pngStableResults->get_indexEnd());
				boundingBoxOverlayStableResults->set_timestampStart(pngStableResults->get_timestampStart());
				boundingBoxOverlayStableResults->set_timestampEnd(pngStableResults->get_timestampEnd());
				status->set_stableResultsByPinID(boundingBoxOverlayStableResults, "BoundingBoxOverlay");

				// bounding box overlay thumbnail
				Class_generic_status_stableResults_p BoundingBoxOverlayThumbnailStableResults = status->find_stableResultsByPinID("BoundingBoxOverlayThumbnail");
				BoundingBoxOverlayThumbnailStableResults->set_indexStart(pngStableResults->get_indexStart());
				BoundingBoxOverlayThumbnailStableResults->set_indexEnd(pngStableResults->get_indexEnd());
				BoundingBoxOverlayThumbnailStableResults->set_timestampStart(pngStableResults->get_timestampStart());
				BoundingBoxOverlayThumbnailStableResults->set_timestampEnd(pngStableResults->get_timestampEnd());
				status->set_stableResultsByPinID(BoundingBoxOverlayThumbnailStableResults, "BoundingBoxOverlayThumbnail");

				// cropped image 
				Class_generic_status_stableResults_p croppedImageStableResults = status->find_stableResultsByPinID("CroppedImage");
				croppedImageStableResults->set_indexStart(boundingBoxStableResults->get_indexStart());
				croppedImageStableResults->set_indexEnd(boundingBoxStableResults->get_indexEnd());
				croppedImageStableResults->set_timestampStart(boundingBoxStableResults->get_timestampStart());
				croppedImageStableResults->set_timestampEnd(boundingBoxStableResults->get_timestampEnd());
				status->set_stableResultsByPinID(croppedImageStableResults, "CroppedImage");

				// cropped image thumbnail
				Class_generic_status_stableResults_p croppedImageThumbnailStableResults = status->find_stableResultsByPinID("CroppedImageThumbnail");
				croppedImageThumbnailStableResults->set_indexStart(boundingBoxStableResults->get_indexStart());
				croppedImageThumbnailStableResults->set_indexEnd(boundingBoxStableResults->get_indexEnd());
				croppedImageThumbnailStableResults->set_timestampStart(boundingBoxStableResults->get_timestampStart());
				croppedImageThumbnailStableResults->set_timestampEnd(boundingBoxStableResults->get_timestampEnd());
				status->set_stableResultsByPinID(croppedImageThumbnailStableResults, "CroppedImageThumbnail");

				status->set_progress(1.0);
				timestamp_t t = sysTime();
				status->set_estimatedFinishTime(t);
				status->set_systemTimeProcessing(t);

				statusStore->save_copy(status);

				boundingBoxStatusPrev = boundingBoxStatus;
				pngStatusPrev = pngStatus;
			}

			// update the status every x seconds, i.e. sleep for this time
			if((boundingBoxStatus.is_status_running() || pngStatus.is_status_running()) && this->controller.intermediateContinueCheck())
			{
				sleep_ms(1000);
			}
		}
		while((boundingBoxStatus.is_status_running() || pngStatus.is_status_running()) && this->controller.nextIterationStep());

		// worker has finished
		if(this->controller.intermediateContinueCheck() && boundingBoxStatus.is_status_finished() && pngStatus.is_status_finished())
		{
			status->set_status_finished();
			LOG_INFO_CONFIG("worker finished", configID);
		}
		// worker hase been stopped
		else if(!this->controller.intermediateContinueCheck() || boundingBoxStatus.is_status_stopped() || pngStatus.is_status_stopped())
		{
			status->set_status_stopped();
			status->set_progress(0.0);
			LOG_INFO_CONFIG("worker forced to stop", configID);
		}
		// error
		else
		{
			status->set_status_error();
			status->set_progress(0.0);

			string str;

			if(boundingBoxStatus.is_status_error())
			{
				str += "bounding boxes input pin error message: " + *boundingBoxStatus.get_message();
			}

			if(pngStatus.is_status_error())
			{
				str += "PNG image input pin error message: " + *pngStatus.get_message();
			}

			if(!str.empty())
			{
				status->set_message(str);
			}

			status->set_estimatedFinishTime(-1);
			LOG_INFO_CONFIG("worker error" + *status->get_message(), configID);
		}

		statusStore->save_copy(status);
	}
	catch(std::runtime_error& e)
	{
		status->set_status_error();
		status->set_progress(0.0);
		status->set_message(e.what());
		status->set_systemTimeProcessing(sysTime());
		status->set_estimatedFinishTime(-1);
		statusStore->save_copy(status);
	}	
	catch(...)
	{
		status->set_status_error();
		status->set_progress(0.0);
		status->set_message("unknown exception");
		status->set_systemTimeProcessing(sysTime());
		status->set_estimatedFinishTime(-1);
		statusStore->save_copy(status);
	}
}

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision