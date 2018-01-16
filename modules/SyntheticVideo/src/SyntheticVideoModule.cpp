/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <opencv2/opencv.hpp>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include "SyntheticVideoModule.h"
#include "SyntheticVideoModule_priv.h"
#include "SyntheticVideo_ModuleDescription.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

using namespace std;

/**
 * module constructor
 */
SyntheticVideoModule::SyntheticVideoModule() : Module_BaseClass(_moduleDescription, _inputPinDescription, _outputPinDescription)
{
	priv.reset( new SyntheticVideoModule_priv() );
	if (!priv)
	{
		throw std::runtime_error("error creating private implementation of module");
	}
}

SyntheticVideoModule::~SyntheticVideoModule()
{
	priv->syntheticVideoMap.clear();
}


/**
 * prepare module specific stores
 */
void SyntheticVideoModule::prepareStores() 
{
}

/**
 * generate input pin
 *
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> SyntheticVideoModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > SyntheticVideoModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( pinID == "VideoMetadata" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new SyntheticVideoDataOutputPin( this, 0, "application/json", SyntheticVideoModule_priv::VideoMetadataEncoder ) );
	}
	else if ( pinID == "FrameMetadata" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new SyntheticVideoDataOutputPin( this, 0, "application/json", SyntheticVideoModule_priv::FrameMetadataEncoder ) );
	}
	else if ( pinID == "RAWYUV420-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new SyntheticVideoDataOutputPin( this, 0, "image/rawyuv420", SyntheticVideoModule_priv::RAWEncoder ) );
	}
	else if ( pinID == "RAWBGR24-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new SyntheticVideoDataOutputPin( this, 1, "image/rawbgr24", SyntheticVideoModule_priv::RAWEncoder ) );
	}
	else if ( pinID == "RAWRGB24-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new SyntheticVideoDataOutputPin( this, 2, "image/rawrgb24", SyntheticVideoModule_priv::RAWEncoder ) );
	}
	else if ( pinID == "PNG-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new SyntheticVideoDataOutputPin( this, 1, "image/png", SyntheticVideoModule_priv::PngEncoder ) );
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 * create algorithm worker object
 *
 * @param env	ConnectedVision module environment
 * @param db	SQLite DB
 * @param config	job / config
 *
 * @return new algorithm worker object
 */
std::unique_ptr<IWorker> SyntheticVideoModule::createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config) 
{
	// create worker instance
	std::unique_ptr<IWorker> ptr;

	return ptr;
}

/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void SyntheticVideoModule::deleteAllData(const id_t configID)
{
	// nothing to do
}


/**
 * start processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void SyntheticVideoModule::start(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );


	Class_SyntheticVideo_params configParams;	
	configParams.parseJson( constConfig->get_params() );


	uint64_t endIndex = configParams.get_numberOfFrames() -1;
	double fps = configParams.get_fps();
	timestamp_t startTime = configParams.get_recordingDateTime();
	timestamp_t endTime = startTime + (timestamp_t)( endIndex * 1000.0 / fps );


	// set status to finished
	auto status = ConnectedVision::make_shared<Class_generic_status>();
	status->set_id(constConfig->get_id());
	status->set_status_finished();
	status->set_progress(1.0);
	Class_generic_status_stableResults stableResults;
	stableResults.set_indexStart( 0 );
	stableResults.set_indexEnd( endIndex );
	stableResults.set_timestampStart( startTime );
	stableResults.set_timestampEnd( endTime );
	status->set_stableResultsByPinID( stableResults, "VideoMetadata" );
	status->set_stableResultsByPinID( stableResults, "FrameMetadata" );
	status->set_stableResultsByPinID( stableResults, "RAWYUV420-Image" );
	status->set_stableResultsByPinID( stableResults, "RAWBGR24-Image" );
	status->set_stableResultsByPinID( stableResults, "RAWRGB24-Image" );
	status->set_stableResultsByPinID( stableResults, "PNG-Image" );
	status->set_estimatedFinishTime( 0 );
	status->set_systemTimeProcessing( sysTime() );
	status->set_startTime( status->getconst_systemTimeProcessing() );
	this->statusStore->save_move(status);
}

/**
 * stop processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void SyntheticVideoModule::stop(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// nothing to do
}

/**
 * revocer of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void SyntheticVideoModule::recover(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// reset
	this->reset(constConfig);
}

/**
 * reset processing of a configChain
 *
 *  This function can be overwritten to execute a module specific procedure.
 *
 * @param[in] config	configChain
 * @param[in] status	config status
 */
void SyntheticVideoModule::reset(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// set status to init
	auto status = ConnectedVision::make_shared<Class_generic_status>();
	status->set_id(constConfig->get_id());
	status->set_status_init();
	status->set_progress(1.0);
	Class_generic_status_stableResults stableResults;
	stableResults.set_indexStart( 0 );
	stableResults.set_indexEnd( -1 );
	stableResults.set_timestampStart( 0 );
	stableResults.set_timestampEnd( -1 );
	status->set_stableResultsByPinID( stableResults, "VideoMetadata" );
	status->set_stableResultsByPinID( stableResults, "FrameMetadata" );
	status->set_stableResultsByPinID( stableResults, "RAWYUV420-Image" );
	status->set_stableResultsByPinID( stableResults, "RAWBGR24-Image" );
	status->set_stableResultsByPinID( stableResults, "RAWRGB24-Image" );
	status->set_stableResultsByPinID( stableResults, "PNG-Image" );
	status->set_estimatedFinishTime( -1 );
	status->set_systemTimeProcessing( sysTime() );
	this->statusStore->save_move(status);

}

void SyntheticVideoModule_priv::prepareVideoHandle(Class_generic_config &config)
{
	SyntheticVideo_init(config);
}

std::string SyntheticVideoModule_priv::VideoMetadataEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace)
{
	Class_SyntheticVideo_output_VideoMetadata sv_Video_Data;
			
	sv_Video_Data.set_id(intToStr(syntheticVideo->framenumber));
	sv_Video_Data.set_configID(configID);
	sv_Video_Data.set_filename(syntheticVideo->filename);
	sv_Video_Data.set_timestamp(syntheticVideo->startTime);
	sv_Video_Data.set_lasttimestamp(syntheticVideo->endTime);			
	sv_Video_Data.set_width(syntheticVideo->width);
	sv_Video_Data.set_height(syntheticVideo->height);
	sv_Video_Data.set_numberofframes(syntheticVideo->numFrames);
	sv_Video_Data.set_fps(syntheticVideo->fps);		
	
	std::string data = sv_Video_Data.toJsonStr();
	
	return data;
}

std::string SyntheticVideoModule_priv::FrameMetadataEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace)
{
	Class_SyntheticVideo_output_FrameMetadata sv_Frame_Data;
			
	sv_Frame_Data.set_id(intToStr(syntheticVideo->framenumber));
	sv_Frame_Data.set_configID(configID);
	sv_Frame_Data.set_timestamp(syntheticVideo->timestamp);			
	sv_Frame_Data.set_framenumber(syntheticVideo->framenumber);
	sv_Frame_Data.set_width(syntheticVideo->width);
	sv_Frame_Data.set_height(syntheticVideo->height);
	
	std::string data = sv_Frame_Data.toJsonStr();
	
	return data;
}

std::string SyntheticVideoModule_priv::RAWEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace)
{
	std::string data;
	
	switch ( colorSpace )
    {
		case 0:
			data = std::string(reinterpret_cast<char*>(syntheticVideo->yuv_img)
													 , syntheticVideo->width * syntheticVideo->height * 3 / 2);
			break;
		case 1:
			data = std::string(reinterpret_cast<char*>(syntheticVideo->bgr_img->data)
													 , syntheticVideo->width * syntheticVideo->height * 3);
			break;
		case 2:
			data = std::string(reinterpret_cast<char*>(syntheticVideo->rgb_img->data)
													 , syntheticVideo->width * syntheticVideo->height * 3);
			break;
		default:
			data = std::string(reinterpret_cast<char*>(syntheticVideo->rgb_img->data)
													 , syntheticVideo->width * syntheticVideo->height * 3);
			break;
	}

	return data;
}

std::string SyntheticVideoModule_priv::PngEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace)
{
	vector<unsigned char> v_char;
	cv::imencode(".png", *syntheticVideo->bgr_img, v_char);
	
	cv::Mat encoded(v_char);
	std::string data (reinterpret_cast<char*>(encoded.data), v_char.size());
		
	return data;
}

void SyntheticVideoModule_priv::RGB2Yuv420p(BYTE *yuv, BYTE *rgb, unsigned width, unsigned height)
{
    unsigned image_size = width * height;
    unsigned upos = image_size;
    unsigned vpos = upos + upos / 4;
    unsigned i = 0;

    for( unsigned line = 0; line < height; ++line )
    {
        if( !(line % 2) )
        {
            for( unsigned x = 0; x < width; x += 2 )
            {
                BYTE r = rgb[3 * i];
                BYTE g = rgb[3 * i + 1];
                BYTE b = rgb[3 * i + 2];

                yuv[i++] = ((66*r + 129*g + 25*b) >> 8) + 16;

                yuv[upos++] = ((-38*r + -74*g + 112*b) >> 8) + 128;
                yuv[vpos++] = ((112*r + -94*g + -18*b) >> 8) + 128;

                r = rgb[3 * i];
                g = rgb[3 * i + 1];
                b = rgb[3 * i + 2];

                yuv[i++] = ((66*r + 129*g + 25*b) >> 8) + 16;
            }
        }
        else
        {
            for( unsigned x = 0; x < width; x += 1 )
            {
                BYTE r = rgb[3 * i];
                BYTE g = rgb[3 * i + 1];
                BYTE b = rgb[3 * i + 2];

                yuv[i++] = ((66*r + 129*g + 25*b) >> 8) + 16;
            }
        }
    }

/*
{
	FILE *mDatei;
	char dateiname [256];
		
	sprintf(dateiname, "c:/temp/test.raw");
	mDatei = fopen(dateiname, "wb");
	
	fwrite(rgb, 1, 3 * width * height, mDatei);

	fclose(mDatei);
}
*/
}

///@TODO MUTEX init function
int SyntheticVideoModule_priv::SyntheticVideo_init(Class_generic_config config)
{
	int nRet = 0;
	std::map<id_t,SyntheticVideo>::iterator it;

	it = syntheticVideoMap.find(config.get_id());

	if (it != syntheticVideoMap.end())
	{
		return 0;
	}

	SyntheticVideo svideo;

	Class_SyntheticVideo_params configParams;	
	configParams.parseJson( config.get_params() );
	svideo.filename = "This is a synthetic video!";

	svideo.numFrames = configParams.get_numberOfFrames();
	svideo.width = configParams.get_width();
	svideo.height = configParams.get_height();
	svideo.startTime = configParams.get_recordingDateTime();
	svideo.fps = configParams.get_fps();
	svideo.avgFramedist = 1000.0 / svideo.fps;
	svideo.endTime = svideo.startTime + (timestamp_t)((svideo.numFrames - 1) * svideo.avgFramedist);
	svideo.backgroundColor = cv::Scalar((unsigned)configParams.get_bgColor()->get_R()
									   ,(unsigned)configParams.get_bgColor()->get_G()
									   ,(unsigned)configParams.get_bgColor()->get_B());
	svideo.osdTextColor = cv::Scalar((unsigned)configParams.get_osdTextColor()->get_R()
								    ,(unsigned)configParams.get_osdTextColor()->get_G()
								    ,(unsigned)configParams.get_osdTextColor()->get_B());
	svideo.foregroundColor = cv::Scalar((unsigned)configParams.get_fgColor()->get_R()
									   ,(unsigned)configParams.get_fgColor()->get_G()
									   ,(unsigned)configParams.get_fgColor()->get_B());
	svideo.sizeOfObject = configParams.get_sizeOfObject();
	svideo.rgb_img = new cv::Mat(cv::Size(svideo.width,svideo.height), CV_8UC3, cv::Scalar(0xFF, 0xFF, 0xFF));
	svideo.bgr_img = new cv::Mat(cv::Size(svideo.width,svideo.height), CV_8UC3, cv::Scalar(0xFF, 0xFF, 0xFF));
	svideo.yuv_img = (BYTE *)malloc(svideo.width*svideo.height*3/2);
	
	syntheticVideoMap[config.get_id()] = svideo;
	
	return nRet;
}

int SyntheticVideoModule_priv::SyntheticVideo_goToFrameNumber(const id_t configID, const int64_t index, unsigned int colorspace)
{
	int nRet = 0;
	unsigned rgbSize, yuvSize, hsvSize;

	std::map<id_t,SyntheticVideo>::iterator it;

	it = syntheticVideoMap.find(configID);
	
	if (it != syntheticVideoMap.end()
		&& (0 <= index)
		&& (index <= (it->second.numFrames - 1)))
	{
		SyntheticVideo svideo = it->second;

		rgbSize = svideo.height * svideo.width * 3;
		yuvSize = svideo.height * svideo.width * 3 / 2;
		hsvSize = rgbSize;

		int a = 0;
		int b = 0;
		cv::Point p0;
		cv::Point p1;
		cv::Point p2;

		svideo.rgb_img->setTo(svideo.backgroundColor);
		std::stringstream st;
		st << index;
		cv::putText(*(svideo.rgb_img), st.str(), cv::Point(svideo.width*0.1, svideo.height*0.9), CV_FONT_HERSHEY_SIMPLEX, 1.0, svideo.osdTextColor, 2, CV_AA, false);


		p0.x = ((index * ((float)(svideo.width+svideo.sizeOfObject+2)/(float)svideo.numFrames))-(svideo.sizeOfObject/2+1));
		p0.y = svideo.height/2;
		
		p1.x = std::max(p0.x-(svideo.sizeOfObject/2), -1);
		p1.y = p0.y-(svideo.sizeOfObject/2);
		
		p2.x = std::min(p0.x+(svideo.sizeOfObject/2),(int)(svideo.width+1));
		p2.y = p0.y+(svideo.sizeOfObject/2);
		
		cv::rectangle(*(svideo.rgb_img), p1, p2, svideo.foregroundColor, CV_FILLED, 8, 0);
		
		cv::cvtColor(*(svideo.rgb_img), *(svideo.bgr_img), CV_RGB2BGR);
		this->RGB2Yuv420p(svideo.yuv_img, svideo.rgb_img->data, svideo.width, svideo.height);

		it->second.framenumber = index;
		it->second.timestamp = svideo.startTime + (timestamp_t)(index * svideo.avgFramedist);
	}
	else
	{
		nRet = -1;
	}

	return nRet;
}

int SyntheticVideoModule_priv::SyntheticVideo_goToTimestamp(const id_t configID, const int64_t timestamp, unsigned int colorspace)
{
	int nRet = 0;
	
	std::map<id_t,SyntheticVideo>::iterator it;

	it = syntheticVideoMap.find(configID);
	
	if (it != syntheticVideoMap.end())
	{
		SyntheticVideo svideo = it->second;

		int64_t index = (int64_t)((timestamp - svideo.startTime) / svideo.avgFramedist);		
		nRet = SyntheticVideo_goToFrameNumber(configID, index, colorspace);
	}

	return nRet;
}

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision