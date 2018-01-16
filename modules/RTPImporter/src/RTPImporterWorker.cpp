/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "RTPImporterWorker.h"

#include <string>
#include <regex>
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

RTPImporterWorker::RTPImporterWorker(RTPImporterModule &module,	IWorkerControllerCallbacks &controller,	ConnectedVision::shared_ptr<const Class_generic_config> config) :
	Worker_BaseClass(module, controller, config), module(module)
{
	this->imgConvertCtx	= NULL;
	this->codecCtx = NULL;
	this->formatCtx = NULL;
	this->pic = NULL;
	this->picrgb = NULL;
	this->pictureSrc = NULL;
	this->pictureDst = NULL;

#ifdef DISABLE_FFMPEG_LOG_MESSAGES
	av_log_set_level(AV_LOG_QUIET);
#else
	#ifdef ENABLE_FFMPEG_LOG_DEBUG_MESSAGES
		av_log_set_level(AV_LOG_DEBUG);
	#endif
#endif

};


void RTPImporterWorker::initResources()
{
	char *pParamRtpUrl;

	this->freeResources();

	this->formatCtx = avformat_alloc_context();
	this->codecCtx = avcodec_alloc_context3(NULL);

	av_register_all();
	avformat_network_init();

#ifdef _DEBUG
#ifdef ENABLE_FFMPEG_CUSTOM_LOG_CALLBACK
	av_log_set_callback(&log_callback);
#endif
#endif
}

void RTPImporterWorker::freeResources()
{
	// clean up contexts
	if (this->imgConvertCtx)
	{
		sws_freeContext(this->imgConvertCtx);
		this->imgConvertCtx = NULL;
	}

	if (this->codecCtx)
	{
		avcodec_close(this->codecCtx);
		avcodec_free_context(&this->codecCtx);
		this->codecCtx = NULL;
	}

	if (this->formatCtx)
	{
		avformat_free_context(this->formatCtx);
		this->formatCtx = NULL;
	}

	// free frame structures
	if(this->pic)
	{
		av_frame_free(&this->pic);
		this->pic = NULL;
	}

	if(this->picrgb)
	{
		av_frame_free(&this->picrgb);
		this->picrgb = NULL;
	}
	
	// free frame data buffers
	if(this->pictureSrc)
	{
		av_free(this->pictureSrc);
		this->pictureSrc = NULL;
	}

	if(this->pictureDst)
	{
		av_free(this->pictureDst);
		this->pictureDst = NULL;
	}
}


/**
* actual algorithm worker thread function
*/
void RTPImporterWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();
	timestamp_t tstamp = 0, oldtstamp = 0;
	//uint32_t encoderErrors = 0;
	//unsigned int frameCnt = 0;
	unsigned int videoFrameCnt = 0;
	unsigned int decodedPicCnt = 0;
	unsigned int decoderErrorCnt = 0;
	AVPacket packet;
	AVStream *stream = NULL;
	//AVRational av_timeBase_Q = {1, AV_TIME_BASE};
	int videoStreamIndex = 0;

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module.getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status = statusStore->getByID(configID)->copy();

	try
	{
		boost::shared_ptr<Class_generic_status_stableResults> stableResults = status->find_stableResultsByPinID( OutputPin_FrameMetadata::PinID() );

		// get images store
		auto storeImages = this->module.storeManagerImages->getReadWriteStore(configID);

		Class_RTPImporter_params params;
		params.parseJson(config->get_params());

		status->resetStableResults();
		// delete previous results
		this->module.deleteAllData(configID);

		// update status timestamps
		status->set_estimatedFinishTime( -1 ); // how long do we need?
		status->set_systemTimeProcessing( sysTime() );
		status->set_progress( 0.0 );

		initResources();

		// check if the URL starts with lower case rtsp://
		if(!regex_match(params.getconst_url()->c_str(), std::regex("^rtsp://.*")))
		{
			throw std::runtime_error("invalid RTSP URL (needs to start with lower case rtsp://)" + *params.getconst_url());
		}

		// open input file (or rtsp url in our case)
		if(avformat_open_input(&this->formatCtx, params.getconst_url()->c_str(), NULL, NULL) != 0){
			throw std::runtime_error("failed to open RTSP URL " + *params.getconst_url());
		}

		// setup RTSP and find information necessary for decoding stream
		if(avformat_find_stream_info(this->formatCtx,NULL) < 0){
			throw std::runtime_error("failed to find stream info");
		}

		//search video stream index (to allow demultiplexing/ignoring audio packets)
		for(unsigned int i =0;i<this->formatCtx->nb_streams;i++){
			if(this->formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
				videoStreamIndex = i;
		}

		av_init_packet(&packet);
		// send RTSP play command
		av_read_play(this->formatCtx);

		// find correct codec and allocate codec context
		stream = this->formatCtx->streams[videoStreamIndex];
		AVCodec *codec = NULL;
		codec = avcodec_find_decoder(stream->codecpar->codec_id);

		if (!codec) 
		{
			throw std::runtime_error("failed to find decoder for stream at index " + intToStr(videoStreamIndex));
		}

		avcodec_get_context_defaults3(this->codecCtx, codec);
	
		avcodec_parameters_to_context(this->codecCtx, stream->codecpar);

		if (avcodec_open2(this->codecCtx, codec, NULL) < 0) 
		{
			throw std::runtime_error("failed to open codec");
		}

		// allocate scaling context (scaling method also performs the colorspace conversion)
		this->imgConvertCtx = sws_getContext(this->codecCtx->width, this->codecCtx->height, this->codecCtx->pix_fmt, this->codecCtx->width, this->codecCtx->height,
			AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);

		// allocate source and destination frame structures and data buffers
		int sizeSrc = av_image_get_buffer_size(AV_PIX_FMT_YUV420P, this->codecCtx->width, this->codecCtx->height, 1);
		int sizeDst = av_image_get_buffer_size(AV_PIX_FMT_BGR24, this->codecCtx->width, this->codecCtx->height, 1);
		this->pictureDst = (uint8_t*)(av_malloc(sizeDst));
		this->pictureSrc = (uint8_t*)(av_malloc(sizeSrc));
		this->pic = av_frame_alloc();
		this->picrgb = av_frame_alloc();

		// associate data buffers with frame structures
		av_image_fill_arrays(this->pic->data, this->pic->linesize, this->pictureSrc, AV_PIX_FMT_YUV420P,this->codecCtx->width, this->codecCtx->height, 1);
		av_image_fill_arrays(this->picrgb->data, this->picrgb->linesize, this->pictureDst, AV_PIX_FMT_BGR24, this->codecCtx->width, this->codecCtx->height, 1);

		// read one frame into packet struct
		while (av_read_frame(this->formatCtx, &packet) >=0  && this->controller.nextIterationStep())
		{
			//frameCnt++;
			
			// only act on video frames
			if (packet.stream_index == videoStreamIndex)
			{
				videoFrameCnt++;

				// decode and retrieve image from frame			
				int result = avcodec_send_packet(this->codecCtx, &packet);
				if (result < 0)
				{
					decoderErrorCnt++;
				}

				int ret = avcodec_receive_frame(this->codecCtx, this->pic);
				if (ret >= 0) 
				{
					// picture was decoded 
					decodedPicCnt++;

					// take timestamp for decoded frame
					oldtstamp = tstamp;

					/*
					// TODO av_frame_get_best_effort_timestamp() does not seem to work
					auto pts = av_frame_get_best_effort_timestamp (this->pic);
					tstamp = av_rescale_q(pts, stream->time_base, av_timeBase_Q ); // timestamp is now in microseconds.
					*/
					tstamp = sysTime();
						
					// do the color space conversions
					sws_scale(this->imgConvertCtx, this->pic->data, this->pic->linesize, 0, this->codecCtx->height, this->picrgb->data, this->picrgb->linesize);
					this->picrgb->width	= this->pic->width;   // copy the sizes because sws_scale doesn't touch the frame structs, once would probably suffice
					this->picrgb->height = this->pic->height;

					// generate OpenCV matrix from image that is put into the ring buffer
					cv::Mat matBGR(this->picrgb->height, this->picrgb->width, CV_8UC3, this->picrgb->data[0], this->picrgb->linesize[0]);
					{
						// get data container from ring buffer
						auto data = storeImages->create();
						
						// if the allocation failed then retry (may occur on weak hardware platform such as Raspberry Pi)
						for(int i = 0; i < 10 && !data; i++)
						{
							sleep_ms(10);
							data = storeImages->create();
						}
					
						if(!data)
						{
							throw ConnectedVision::runtime_error("failed to allocate output store result element");
						}

						data->set_id( boost::lexical_cast<id_t>(tstamp) );
						data->set_timestamp( tstamp );

						// write image
						data->image = matBGR.clone();

						// write meta data
						data->set_framenumber( decodedPicCnt -1 );
						data->set_encerrors( decoderErrorCnt );
						data->set_height(this->picrgb->height);
						data->set_width(this->picrgb->width);
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

		av_read_pause(this->formatCtx);
		avformat_close_input(&this->formatCtx);

		// worker has finished
		status->set_estimatedFinishTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );
		status->set_progress( 1.0 );
		status->set_status_finished();
		LOG_INFO_CONFIG("worker stopped", configID);
		statusStore->save_copy(status);
		
		this->freeResources();
	}
	catch(const std::exception &e)
	{
		try
		{
			this->freeResources();
		}
		catch(...) { }

		try
		{
			LOG_ERROR_CONFIG( e.what(), configID);

			status->set_status_error();
			status->set_message( e.what() );
			status->set_systemTimeProcessing( sysTime() );
			status->set_estimatedFinishTime( -1 );
			statusStore->save_copy(status);
		}
		catch(...) { }
	}
}

} // namespace RTPImporter
} // namespace Module
} // namespace ConnectedVision