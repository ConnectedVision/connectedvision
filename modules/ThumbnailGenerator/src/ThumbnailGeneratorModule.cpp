/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>


#include "ThumbnailGeneratorModule.h"
#include "ThumbnailGeneratorWorker.h"

#include <Module/InputPins/InputPin_PNG.h>
#include "ImageOutputPin.h"

#include "ThumbnailGenerator_ModuleDescription.h"

#include "InputPin_ThumbnailGenerator_input_BoundingBox.h"
#include "InputPin_ThumbnailGenerator_input_ImageMetadata.h"
//#include "InputPin_ThumbnailGenerator_input_Polyline.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

using namespace std;


/**
 * module constructor
 */
ThumbnailGeneratorModule::ThumbnailGeneratorModule() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}

/**
 * init module
 *
 * @param server  module server
 */
void ThumbnailGeneratorModule::initModule( IModuleEnvironment *env )
{
	LOG_SCOPE;

	// clean up module before init
	this->releaseModule();

	// call parent init
	ConnectedVisionModule::initModule(env);
}

/**
 * destroy module
 *
 * @param server  module server
 */
void ThumbnailGeneratorModule::releaseModule() 
{
	LOG_SCOPE;

	// call parent init
	ConnectedVisionModule::releaseModule();

	// clean-up
}

/**
 * prepare module specific stores
 */
void ThumbnailGeneratorModule::prepareStores() 
{
}

/**
 * generate input pin
 *
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> ThumbnailGeneratorModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if (pinID == InputPin_PNG::PinID())
	{
		return boost::shared_ptr<IConnectedVisionInputPin>(new InputPin_PNG(this->env, pinID));
	}
	else if (pinID == InputPin_ThumbnailGenerator_input_ImageMetadata::PinID())
	{
		return boost::shared_ptr<IConnectedVisionInputPin>(new InputPin_ThumbnailGenerator_input_ImageMetadata(this->env, pinID));
	}
	else if (pinID == InputPin_ThumbnailGenerator_input_BoundingBox::PinID())
	{
		return boost::shared_ptr<IConnectedVisionInputPin>(new InputPin_ThumbnailGenerator_input_BoundingBox(this->env, pinID));
	}
	//else if (pinID == InputPin_ThumbnailGenerator_input_Polyline::PinID())
	//{
	//	return boost::shared_ptr<IConnectedVisionInputPin>(new InputPin_ThumbnailGenerator_input_Polyline(this->env, pinID));
	//}

	throw ConnectedVision::runtime_error("generateInputPin() invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > ThumbnailGeneratorModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if (pinID == "BoundingBoxOverlay")
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>(new ImageOutputPin(this, ImageOutputPin::ModificationType::BoundingBoxOverlay, false));
	}
	else if (pinID == "BoundingBoxOverlayThumbnail")
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>(new ImageOutputPin(this, ImageOutputPin::ModificationType::BoundingBoxOverlay, true));
	}
	else if (pinID == "CroppedImage")
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>(new ImageOutputPin(this, ImageOutputPin::ModificationType::Cropping, false));
	}
	else if (pinID == "CroppedImageThumbnail")
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>(new ImageOutputPin(this, ImageOutputPin::ModificationType::Cropping, true));
	}
	//else if (pinID == "PolylineOverlay")
	//{
	//	return boost::shared_ptr<IConnectedVisionOutputPin>(new ImageOutputPin(this, ImageOutputPin::ModificationType::PolylineOverlay, false));
	//}
	//else if (pinID == "PolylineOverlayThumbnail")
	//{
	//	return boost::shared_ptr<IConnectedVisionOutputPin>(new ImageOutputPin(this, ImageOutputPin::ModificationType::PolylineOverlay, true));
	//}

	throw ConnectedVision::runtime_error("generateOutputPin() invalid pinID: " + pinID);
}


/**
 * create algorithm worker object
 *
 * @param env	ConnectedVision module environment
 * @param config	job / config
 *
 * @return new algorithm worker object
 */
boost::shared_ptr<IConnectedVisionAlgorithmWorker> ThumbnailGeneratorModule::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	return boost::shared_ptr<IConnectedVisionAlgorithmWorker>( new ThumbnailGeneratorWorker(env, this, config) );
}

/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void ThumbnailGeneratorModule::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	// nothing to do
}

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision