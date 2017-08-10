/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "RTPImporterWorker.h"

#include <string>
#include <time.h>

#include <helper.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>


#include "RTPImporterModule.h"
#include "Class_RTPImporter_params.h"

#include "OutputPin_FrameMetadata.h"
#include "OutputPin_FramePNG.h"

#include <opencv2/opencv.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

extern "C"
{
	#include <libavutil/rational.h>
	#include <libavutil/avutil.h>
	#include <libavutil/imgutils.h>
}

namespace ConnectedVision {
namespace Module {
namespace RTPImporter {

using namespace std;

//#define ENABLE_FFMPEG_CUSTOM_LOG_CALLBACK
#define DISABLE_FFMPEG_LOG_MESSAGES
//#define ENABLE_FFMPEG_LOG_DEBUG_MESSAGES
#ifdef ENABLE_FFMPEG_CUSTOM_LOG_CALLBACK
void log_callback(void *ptr, int level, const char *fmt, va_list vargs)
{
// this callback can be used to forward FFMPEG log messages to a custom logger
   static char message[8192];
   const char *module = NULL;

    if (ptr)
    {
        AVClass *avc = *(AVClass**) ptr;
        module = avc->item_name(ptr);
    }
   vsnprintf_s(message, sizeof(message), fmt, vargs);

   std::cout << "LOG: " << message << std::endl;
}
#endif

RTPImporterWorker::RTPImporterWorker(IModuleEnvironment *env, ConnectedVisionModule *module, boost::shared_ptr<const Class_generic_config> config) :
ConnectedVisionAlgorithmWorker(env, module, config)
{
	params.parseJson(config->get_params());

	imgConvertCtx	= NULL;
	codecCtx		= NULL;
	formatCtx		= NULL;

#ifdef DISABLE_FFMPEG_LOG_MESSAGES
	av_log_set_level(AV_LOG_QUIET);
#else
	#ifdef ENABLE_FFMPEG_LOG_DEBUG_MESSAGES
		av_log_set_level(AV_LOG_DEBUG);
	#endif
#endif

};

void RTPImporterWorker::start()
{
	ConnectedVisionAlgorithmWorker::start();
}

void RTPImporterWorker::stop()
{
	ConnectedVisionAlgorithmWorker::stop();
}

void RTPImporterWorker::initResources()
{
	char *pParamRtpUrl;

	freeResources();

	formatCtx = avformat_alloc_context();
	codecCtx = avcodec_alloc_context3(NULL);

	av_register_all();
	avformat_network_init();

#ifdef _DEBUG
#ifdef ENABLE_FFMPEG_CUSTOM_LOG_CALLBACK
	av_log_set_callback(&log_callback);
#endif
#endif

	pParamRtpUrl = (char *)params.getconst_url()->data();

	if (! ((strstr(pParamRtpUrl, "rtsp://")) || (strstr(pParamRtpUrl, "RTSP://")) ) )
	{
		throw std::runtime_error("No RTSP url");
	}

	rcvdGOPs.set_capacity(5);
}

void RTPImporterWorker::freeResources()
{
	// clean up contexts
	if (imgConvertCtx)
	{
		sws_freeContext(imgConvertCtx);
		imgConvertCtx = NULL;
	}

	if (codecCtx)
	{
		avcodec_close(codecCtx);
		avcodec_free_context(&codecCtx);
		codecCtx = NULL;
	}

	if (formatCtx)
	{
		avformat_free_context(formatCtx);
		formatCtx = NULL;
	}

	rcvdGOPs.clear();
}


/**
* actual algorithm worker thread function
*/
void RTPImporterWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();
	timestamp_t tstamp = 0, oldtstamp = 0;
	uint32_t encoderErrors = 0;
	char* rtspUrl = (char *)params.getconst_url()->data();
	unsigned int frameCnt = 0;
	unsigned int videoFrameCnt = 0;
	unsigned int decodedPicCnt = 0;
	unsigned int decoderErrorCnt = 0;
	AVPacket packet;
	AVStream *stream = NULL;
	AVRational av_timeBase_Q = {1, AV_TIME_BASE};


	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module->getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status = statusStore->getByID(configID)->copy();
	boost::shared_ptr<Class_generic_status_stableResults> stableResults = status->find_stableResultsByPinID( OutputPin_FrameMetadata::PinID() );

	// get images store
	auto storeImages = dynamic_cast<RTPImporterModule *>(this->module)->storeManagerImages->getReadWriteStore(configID);


	try
	{
		status->resetStableResults();
		// delete previous results
		this->module->deleteResults( this->config );

		// update status timestamps
		status->set_estimatedFinishTime( -1 ); // how long do we need?
		status->set_systemTimeProcessing( sysTime() );
		status->set_progress( 0.0 );

		initResources();

		// open input file (or rtsp url in our case)
		if(avformat_open_input(&formatCtx, rtspUrl, NULL, NULL) != 0){
			throw std::runtime_error("RTPImporter: Could not open RTSP Url");
		}

		// setup RTSP and find information necessary for decoding stream
		if(avformat_find_stream_info(formatCtx,NULL) < 0){
			throw std::runtime_error("RTPImporter: Could not find stream info");
		}

		//search video stream index (to allow demultiplexing/ignoring audio packets)
		for(unsigned int i =0;i<formatCtx->nb_streams;i++){
			if(formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
				videoStreamIndex = i;
		}

		av_init_packet(&packet);
		// send RTSP play command
		av_read_play(formatCtx);

		// find correct codec and allocate codec context
		stream = formatCtx->streams[videoStreamIndex];
		AVCodec *codec = NULL;
		codec = avcodec_find_decoder(stream->codecpar->codec_id);    
		if (!codec) 
		{
			throw std::runtime_error("RTPImporter: Could find codec for stream");
		}
		avcodec_get_context_defaults3(codecCtx, codec);
	
		avcodec_parameters_to_context(codecCtx, stream->codecpar);		

		if (avcodec_open2(codecCtx, codec, NULL) < 0) 
		{
			throw std::runtime_error("RTPImporter: Could not open codec");
		}

		// allocate scaling context (scaling method also performs the colorspace conversion)
		imgConvertCtx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt, codecCtx->width, codecCtx->height,
			AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

	} catch(std::exception &e)
	{
		freeResources();

		try
		{
			LOG_ERROR_CONFIG( e.what(), configID);

			status->set_status_error();
			status->set_message( e.what() );
			status->set_systemTimeProcessing( sysTime() );
			status->set_estimatedFinishTime( -1 );
			statusStore->save_copy(status);
		} catch(...)
		{
		}

		return;
	}


	// allocate source and destination frame structures and data buffers
	int sizeSrc				= av_image_get_buffer_size(AV_PIX_FMT_YUV420P, codecCtx->width, codecCtx->height, 1);
	int sizeDst				= av_image_get_buffer_size(AV_PIX_FMT_BGR24, codecCtx->width, codecCtx->height, 1);
	uint8_t* pictureDst		= (uint8_t*)(av_malloc(sizeDst));
	uint8_t* pictureSrc		= (uint8_t*)(av_malloc(sizeSrc));
	AVFrame* pic			= av_frame_alloc();
	AVFrame* picrgb			= av_frame_alloc();

	// associate data buffers with frame structures
	av_image_fill_arrays(pic->data, pic->linesize, pictureSrc, AV_PIX_FMT_YUV420P,codecCtx->width, codecCtx->height, 1);
	av_image_fill_arrays(picrgb->data, picrgb->linesize, pictureDst, AV_PIX_FMT_BGR24, codecCtx->width, codecCtx->height, 1);

	// read one frame into packet struct
	while (av_read_frame(formatCtx,&packet) >=0  && go)
	{
		frameCnt++;
			
		// only act on video frames
		if (packet.stream_index == videoStreamIndex)
		{
			videoFrameCnt++;

			// decode and retrieve image from frame			
			int result = avcodec_send_packet(codecCtx, &packet);
			if (result < 0)
			{
				decoderErrorCnt++;
			}

			int ret = avcodec_receive_frame(codecCtx, pic);
			if (ret >= 0) 
			{
				// picture was decoded 
				decodedPicCnt++;

				// take timestamp for decoded frame
				oldtstamp = tstamp;

				/*
				// TODO av_frame_get_best_effort_timestamp() does not seem to work
				auto pts = av_frame_get_best_effort_timestamp (pic);
				tstamp = av_rescale_q(pts, stream->time_base, av_timeBase_Q ); // timestamp is now in microseconds.
				*/
				tstamp = sysTime();
						
				// do the color space conversions
				sws_scale(imgConvertCtx, pic->data, pic->linesize, 0, codecCtx->height, picrgb->data, picrgb->linesize);
				picrgb->width	= pic->width;   // copy the sizes because sws_scale doesn't touch the frame structs, once would probably suffice
				picrgb->height	= pic->height;

				// generate OpenCV matrix from image that is put into the ring buffer
				cv::Mat matBGR(picrgb->height, picrgb->width, CV_8UC3, picrgb->data[0], picrgb->linesize[0]);
				{
					// get data container from ring buffer
					auto data = storeImages->create();
					if (!data)
					{
						throw ConnectedVision::runtime_error("error: storeImages->create() failed (null pointer returned)...");
					}
					data->set_id( boost::lexical_cast<id_t>(tstamp) );
					data->set_timestamp( tstamp );

					// write image
					data->image = matBGR.clone();

					// write meta data
					data->set_framenumber( decodedPicCnt -1 );
					data->set_encerrors( decoderErrorCnt );
					data->set_height(picrgb->height);
					data->set_width(picrgb->width);
					if( oldtstamp )
						data->set_framediff(std::abs(tstamp - oldtstamp));
					else
						data->set_framediff(0);

					// save to store
					storeImages->save_move( data );

					// update status
					stableResults->importFromStore( *storeImages );
					status->set_stableResultsByPinID( stableResults, OutputPin_FramePNG::PinID() );
					status->set_stableResultsByPinID( stableResults, OutputPin_FrameMetadata::PinID() );
							
					// FIXME
					// compute progress
					status->set_progress( 0.0 );

					// compute ETA (we will finish when the prev. module is ready)
					// FIXME status->set_estimatedFinishTime( detectionStatus.get_estimatedFinishTime() );
					status->set_systemTimeProcessing( sysTime() );

					// save status
					statusStore->save_copy(status);				
				}
			}
		}
		// clean up received packet
		av_packet_unref(&packet);
		av_init_packet(&packet);
	}

	av_read_pause(formatCtx);
	avformat_close_input(&formatCtx);

	// free data buffers and frame structures
	av_frame_free(&pic);
	av_frame_free(&picrgb);
	av_free(pictureSrc);
	av_free(pictureDst);




	try
	{
		status->set_estimatedFinishTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );
		// worker has finished
		status->set_progress( 1.0 );
		status->set_status_finished();
		LOG_INFO_CONFIG("worker stopped", configID);
		statusStore->save_copy(status);
	} catch(...)
	{
	}

	freeResources();
}

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision