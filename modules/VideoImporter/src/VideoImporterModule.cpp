/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <time.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include "VideoImporterModule.h"
#include "VideoImporterModule_priv.h"
#include "VideoImporter_ModuleDescription.h"
#include "VideoImporterWorker.h"

#include "InputPin_VideoImporter_input_Trigger.h"

#include "./VideoImport_FFmpeg/VideoImport_FFmpeg.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

using namespace std;
using namespace ConnectedVision;

/**
 * module constructor
 */
VideoImporterModule::VideoImporterModule() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
{
	priv.reset( new VideoImporterModule_priv() );
	if (!priv)
	{
		throw std::runtime_error("error creating private implementation of module");
	}
}

VideoImporterModule::~VideoImporterModule()
{
	boost::mutex::scoped_lock(priv->mutexVideoImportMap);

	for ( auto it = priv->videoImportMap.begin() ; it != priv->videoImportMap.end(); it++ )
	{
		auto vi = it->second;
		
		if (vi->pVideoImportFFmpeg)
		{
			vi->pVideoImportFFmpeg->freeResources();
			vi->pVideoImportFFmpeg.reset();	
		}
	}

	priv->videoImportMap.clear();
}

/**
 * init module
 *
 * @param server  module server
 */
void VideoImporterModule::initModule( IModuleEnvironment *env ) 
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
void VideoImporterModule::releaseModule() 
{
	LOG_SCOPE;

	// call parent init
	ConnectedVisionModule::releaseModule();
}

/**
 * generate input pin
 *
 * @return input pin
 */
boost::shared_ptr<IConnectedVisionInputPin> VideoImporterModule::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if(pinID == InputPin_VideoImporter_input_Trigger::PinID())
	{
		return boost::make_shared<InputPin_VideoImporter_input_Trigger>(this->env, pinID);
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 *  generate output pin
 *
 * @return output pin
 */
boost::shared_ptr<IConnectedVisionOutputPin > VideoImporterModule::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	if ( pinID == "VideoMetadata" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new VideoDataOutputPin( this, VIDEOIMPORT_FFMPEG_COLORSPACE_YUV420, "application/json", VideoImporterModule_priv::FileMetadataEncoder ) );
	}
	else if ( pinID == "FrameMetadata" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new VideoDataOutputPin( this, VIDEOIMPORT_FFMPEG_COLORSPACE_YUV420, "application/json", VideoImporterModule_priv::FrameMetadataEncoder ) );
	}
	else if ( pinID == "RAWYUV420-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new VideoDataOutputPin( this, VIDEOIMPORT_FFMPEG_COLORSPACE_YUV420, "image/rawyuv420", VideoImporterModule_priv::RAWEncoder ) );
	}
	else if ( pinID == "RAWBGR24-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new VideoDataOutputPin( this, VIDEOIMPORT_FFMPEG_COLORSPACE_BGR24, "image/rawbgr24", VideoImporterModule_priv::RAWEncoder ) );
	}
	else if ( pinID == "RAWRGB24-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new VideoDataOutputPin( this, VIDEOIMPORT_FFMPEG_COLORSPACE_RGB24, "image/rawrgb24", VideoImporterModule_priv::RAWEncoder ) );
	}
	else if ( pinID == "PNG-Image" )
	{
		return boost::shared_ptr<IConnectedVisionOutputPin>( new VideoDataOutputPin( this, VIDEOIMPORT_FFMPEG_COLORSPACE_BGR24, "image/png", VideoImporterModule_priv::PngEncoder ) );
	}

	throw ConnectedVision::runtime_error("invalid pinID: " + pinID);
}

/**
 * prepare module specific stores
 */
void VideoImporterModule::prepareStores() 
{
}


void VideoImporterModule::checkConfig(const Class_generic_config &config)
{
	// call parent function
	ConnectedVisionModule::checkConfig(config);

	// make sure that file is readable
	Class_VideoImporter_params configParams;	
	configParams.parseJson( config.get_params() );
	std::string filename = *configParams.getconst_filename();
	FILE *file = fopen(filename.c_str(), "rb");
	if ( file ) 
	{
		fclose(file);
	} 
	else 
	{
		throw ConnectedVision::runtime_error("[VideoImporterModule] cannot read file: " + filename);
	} 
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
boost::shared_ptr<IConnectedVisionAlgorithmWorker> VideoImporterModule::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	return boost::make_shared<VideoImporterWorker>(env, this, config);
}


/**
 * delete results of a config chain
 *
 * @param config	config chain
 */
void VideoImporterModule::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->get_id() );

	// nothing to do
}


/**
 * Initializes the specified config and returns the resulting status object with the final stable results information.
 *
 * @param config The config.
 *
 * @return The stable results.
 */
ConnectedVision::shared_ptr<Class_generic_status> VideoImporterModule::init(boost::shared_ptr<const Class_generic_config> constConfig)
{
	LOG_SCOPE_CONFIG( constConfig->get_id() );

	// get the video metadata for determining the number of frames and the end timestamp
	this->priv->VideoImport_init(*constConfig);
	
	boost::shared_ptr<ConnectedVision::Module::VideoImporter::VideoImport> vi;
	{
		boost::mutex::scoped_lock(priv->mutexVideoImportMap);
		vi = priv->videoImportMap.begin()->second;
	}
	
	int nFrames = vi->m_MetaData.numberOfFrames;
	timestamp_t timestampStart = vi->m_MetaData.startTime;
	timestamp_t timestampEnd = vi->m_MetaData.endTime;

	// set status to finished
	auto status = this->statusStore->create();
	status->set_id( constConfig->get_id());
	status->set_status_finished();
	status->set_progress(1.0);
	
	Class_generic_status_stableResults stableResults;
	stableResults.set_indexStart( 0 );
	stableResults.set_indexEnd( nFrames - 1 );
	stableResults.set_timestampStart( timestampStart );
	stableResults.set_timestampEnd( timestampEnd );
	
	status->set_stableResultsByPinID( stableResults, "VideoMetadata" );
	status->set_stableResultsByPinID( stableResults, "FrameMetadata" );
	status->set_stableResultsByPinID( stableResults, "RAWYUV420-Image" );
	status->set_stableResultsByPinID( stableResults, "RAWBGR24-Image" );
	status->set_stableResultsByPinID( stableResults, "RAWRGB24-Image" );
	status->set_stableResultsByPinID( stableResults, "PNG-Image" );

	status->set_estimatedFinishTime( 0 );
	status->set_systemTimeProcessing( sysTime() );

	return status;
}

std::string VideoImporterModule_priv::FileMetadataEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace)
{
	Class_VideoImporter_output_VideoMetadata vi_File_Data;
			
	vi_File_Data.set_id("VideoMetadata");
	vi_File_Data.set_configID(configID);
	vi_File_Data.set_filename(videoImport->m_Filename);
	vi_File_Data.set_timestamp(videoImport->m_MetaData.startTime);
	vi_File_Data.set_lasttimestamp(videoImport->m_MetaData.endTime);			
	vi_File_Data.set_width(videoImport->m_MetaData.width);
	vi_File_Data.set_height(videoImport->m_MetaData.height);
	vi_File_Data.set_numberofframes(videoImport->m_MetaData.numberOfFrames);
	vi_File_Data.set_fps(videoImport->m_MetaData.fps);		
	
	std::string data = vi_File_Data.toJsonStr();
	
	return data;
}

std::string VideoImporterModule_priv::FrameMetadataEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace)
{
	Class_VideoImporter_output_FrameMetadata vi_Frame_Data;
	
	std::string strFrameNumber = boost::lexical_cast<std::string>(videoImport->m_Frame.framenumber);
	
	vi_Frame_Data.set_id(strFrameNumber.c_str());
	vi_Frame_Data.set_configID(configID);
	vi_Frame_Data.set_timestamp(videoImport->m_Frame.timestamp);			
	vi_Frame_Data.set_framenumber(videoImport->m_Frame.framenumber);
	vi_Frame_Data.set_width(videoImport->m_Frame.width);
	vi_Frame_Data.set_height(videoImport->m_Frame.height);
	
	std::string data = vi_Frame_Data.toJsonStr();
	
	return data;
}

std::string VideoImporterModule_priv::RAWEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace)
{
	std::string data;
	
	if (colorSpace == VIDEOIMPORT_FFMPEG_COLORSPACE_YUV420)
	{
		data = std::string(reinterpret_cast<char*>(videoImport->m_Frame.data)
												 , videoImport->m_Frame.width * videoImport->m_Frame.height * 3 / 2);
	}
	else
	{
		data = std::string(reinterpret_cast<char*>(videoImport->m_Frame.data)
												 , videoImport->m_Frame.width * videoImport->m_Frame.height * 3);
	}

	return data;
}

std::string VideoImporterModule_priv::PngEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace)
{
	boost::shared_ptr<cv::Mat> pImageMat = boost::make_shared<cv::Mat>(videoImport->m_Frame.height, videoImport->m_Frame.width, CV_8UC3, videoImport->m_Frame.data, 3*videoImport->m_Frame.width);	

	vector<unsigned char> v_char;
	cv::imencode(".png", *pImageMat, v_char);
	
	cv::Mat encoded(v_char);
	std::string data (reinterpret_cast<char*>(encoded.data), v_char.size());
	
	return data;
}

void VideoImporterModule_priv::VideoImport_init(const Class_generic_config config)
{
	boost::mutex::scoped_lock(mutexVideoImportMap);

	auto it = videoImportMap.find(config.get_id());

	if (it != videoImportMap.end())
	{
		return;
	}

	auto vimport = boost::make_shared<VideoImport>();
		
	Class_VideoImporter_params configParams;	
	configParams.parseJson( config.get_params() );
	vimport->m_Filename = *configParams.get_filename();

	vimport->m_RecordingDateTime = configParams.get_recordingDateTime();

	if (*configParams.getconst_deinterlaceMode() == *configParams.deinterlaceMode_AUTO)
	{
		vimport->deinterlaceMode = VideoImport_FFmpeg::DEINTERLACEMODE_AUTO;
	}
	else if (*configParams.getconst_deinterlaceMode() == *configParams.deinterlaceMode_FORCE)
	{
		vimport->deinterlaceMode = VideoImport_FFmpeg::DEINTERLACEMODE_FORCE;
	}
	else if (*configParams.getconst_deinterlaceMode() == *configParams.deinterlaceMode_OFF)
	{
		vimport->deinterlaceMode = VideoImport_FFmpeg::DEINTERLACEMODE_OFF;
	}
	else
	{
		throw std::runtime_error("error in VideoImporterModule_priv::VideoImport_init: deinterlacing mode unknown - please check config params field 'deinterlaceMode' for validity");
	}

	std::string filename = "" + vimport->m_Filename;
	vimport->pVideoImportFFmpeg = ConnectedVision::make_shared<VideoImport_FFmpeg>(filename.c_str(), vimport->m_RecordingDateTime, vimport->deinterlaceMode);

	vimport->pVideoImportFFmpeg->getMetaData(&vimport->m_MetaData);
	
	videoImportMap[config.get_id()] = vimport;
}

void VideoImporterModule_priv::VideoImport_goToFrameNumber(const id_t configID, const int64_t index, unsigned int colorspace)
{
	boost::mutex::scoped_lock(mutexVideoImportMap);
	auto it = videoImportMap.find(configID);
	
	if (it != videoImportMap.end())
	{
		it->second->pVideoImportFFmpeg->goToFrameNumber((unsigned int)index, colorspace, &it->second->m_Frame);
	}
}

void VideoImporterModule_priv::VideoImport_goToTimestamp(const id_t configID, const int64_t timestamp, unsigned int colorspace)
{
	boost::mutex::scoped_lock(mutexVideoImportMap);
	auto it = videoImportMap.find(configID);
	
	if (it != videoImportMap.end())
	{
		it->second->pVideoImportFFmpeg->goToTimestamp(timestamp, colorspace, &it->second->m_Frame);
	}
}

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision
