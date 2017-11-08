/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "VideoImport_FFmpeg.h"

#include <time.h>
#include <string>
#include <string.h> // for memcpy
#include <stdio.h>
#include <limits.h> // LLONG_MAX define

#include <boost/lexical_cast.hpp>

#ifdef _WIN32
	#define NULL 0
#endif

VideoImport_FFmpeg::VideoImport_FFmpeg(const char filename[], int64_t recordingDateTime, DEINTERLACEMODE deinterlacemode) :
	picYUV420(NULL),
	picBGR24(NULL),
	picRGB24(NULL),
	cSwScaleYUV420P(NULL),
	cSwScaleBGR24(NULL),
	cSwScaleRGB24(NULL)
{
	Decoder::DecoderParams decoderParams;
	switch (deinterlacemode)
	{
	case DEINTERLACEMODE_AUTO:
		decoderParams.deinterlaceMode = Decoder::DECODER_DEINTERLACEMODE_AUTO;
		break;
	case DEINTERLACEMODE_FORCE:
		decoderParams.deinterlaceMode = Decoder::DECODER_DEINTERLACEMODE_FORCE;
		break;
	case DEINTERLACEMODE_OFF:
		decoderParams.deinterlaceMode = Decoder::DECODER_DEINTERLACEMODE_OFF;
		break;
	default:
		throw std::runtime_error("error in constructor of VideoImport_FFmpeg: unknown deinterlace mode was provided as function parameter");
		break;
	}
	decoder.setDecoderParams(decoderParams);
	
	containerDemuxer.registerParentInstance(this);
	containerDemuxer.open(filename);
	containerDemuxer.registerDecoder(&decoder);

	decoder.registerContainterDemuxerParent(&containerDemuxer);

	decoder.open();

	AVFormatContext *pFormatCtx = containerDemuxer.getFormatCtx();
		
	AVRational timebase = pFormatCtx->streams[0]->time_base;
	AVRational framerate = pFormatCtx->streams[0]->r_frame_rate;
	
	fps = (double)framerate.num / (double)framerate.den;
	double time_base = (double)timebase.num / (double)timebase.den;

	frameDist = 1000.0 / fps;

	numberOfFrames = pFormatCtx->streams[0]->nb_frames;
	if (numberOfFrames == 0) // some videos (e.g. webm) might have no nb_frames specified (see https://stackoverflow.com/questions/32532122/finding-duration-number-of-frames-of-webm-using-ffmpeg-libavformat)
	{
		// do fallback then
		numberOfFrames = (int64_t)(pFormatCtx->duration * fps / AV_TIME_BASE);
	}

	StartTime = recordingDateTime; // get AVI file time - and convert from microseconds to milliseconds
	LengthTime = (int64_t)((numberOfFrames - 1) * frameDist * 1000);
	EndTime    = StartTime + LengthTime;
		
	//// important so that frame width and height is known
	//int64_t timestamp = 0;
	//bool goToResult = containerDemuxer.goToFrame(timestamp, &decodedFrame);

	actual_timestamp = StartTime;
	latestFrameIndexRequested = LLONG_MIN;
}

VideoImport_FFmpeg::VideoImport_FFmpeg(const char filename[])
{
	VideoImport_FFmpeg(filename, 0);
}

VideoImport_FFmpeg::~VideoImport_FFmpeg()
{
}

void VideoImport_FFmpeg::freeResources()
{
	if (picYUV420)
	{
		delete[](this->picYUV420->data[0]);
		av_frame_unref(picYUV420);
		picYUV420 = NULL;
	}
	if (picBGR24)
	{
		delete[](this->picBGR24->data[0]);
		av_frame_unref(picBGR24);
		picBGR24 = NULL;
	}
	if (picRGB24)
	{
		delete[](this->picRGB24->data[0]);
		av_frame_unref(picRGB24);
		picRGB24 = NULL;
	}

	if (cSwScaleYUV420P)
	{
		sws_freeContext(cSwScaleYUV420P);
	}
	if (cSwScaleBGR24)
	{
		sws_freeContext(cSwScaleBGR24);
	}
	if (cSwScaleRGB24)
	{
		sws_freeContext(cSwScaleRGB24);
	}

	decoder.freeFilters();
	decoder.close();
	containerDemuxer.close();
}

void VideoImport_FFmpeg::getMetaData(VideoImport_FFmpeg_MetaData *metaData)
{  
	if (!metaData)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::getMetaData(): parameter metaData was NULL");
	}

	metaData->width          = this->containerDemuxer.getFormatCtx()->streams[0]->codecpar->width;
	metaData->height         = this->containerDemuxer.getFormatCtx()->streams[0]->codecpar->height;
	metaData->numberOfFrames = this->numberOfFrames;
	metaData->fps			 = this->fps;
	metaData->startTime		 = this->StartTime;
	metaData->endTime		 = this->EndTime;
}

void VideoImport_FFmpeg::goToTimestamp(int64_t timestamp, int numCsp, VideoImport_FFmpeg_Frame *frame)
{
	if (!frame)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::goToTimestamp(): parameter frame was NULL");
	}
	
	AVRational timebase = this->containerDemuxer.getFormatCtx()->streams[0]->time_base;
	double time_base = (double)timebase.num / (double)timebase.den;
	AVStream *stream = this->containerDemuxer.getFormatCtx()->streams[0];
	int64_t duration = (int64_t)(this->containerDemuxer.getFormatCtx()->duration * fps / AV_TIME_BASE);
	int64_t maxTimestamp = (int64_t)(((duration) / ((double)timebase.den / (double)timebase.num / this->fps) - 1) * this->frameDist);

	int64_t timestampMilliSeconds;
	if (timestamp - StartTime < maxTimestamp) //LLONG_MAX / 1000) // check for value overflow and prevent it
	{
		timestampMilliSeconds =  (timestamp - StartTime) / 1000;
	}
	else
	{
		timestampMilliSeconds = maxTimestamp; //LLONG_MAX - (int64_t)(frameDist * 1000) / 2; // since there is a + frameDist / 2 operation on timestamp in function containerDemuxer.goToFrame later
	}

	containerDemuxer.goToFrame(timestampMilliSeconds, &decodedFrame);
	
	latestFrameIndexRequested = (int64_t)(double(containerDemuxer.getVideoPacket().dts - stream->first_dts) / ((double)timebase.den / (double)timebase.num / this->fps));
	actual_timestamp = StartTime + (int64_t)(latestFrameIndexRequested * frameDist) * 1000; // *1000 ... milliseconds to microseconds, StartTime already in microseconds

	convertFrame(&decodedFrame, numCsp, frame);
}

void VideoImport_FFmpeg::goToFrameNumber(unsigned int frameNr, int numCsp, VideoImport_FFmpeg_Frame *frame)
{
	if (!frame)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::goToFrameNumber(): parameter frame was NULL");
	}

	AVRational timebase = this->containerDemuxer.getFormatCtx()->streams[0]->time_base;
	double time_base = (double)timebase.num / (double)timebase.den;
	AVStream *stream = this->containerDemuxer.getFormatCtx()->streams[0];

	int64_t timestampMilliSeconds =  (int64_t)(StartTime / 1000 + frameNr * frameDist);

	AVFormatContext *pFormatCtx = containerDemuxer.getFormatCtx();
	
	if (frameNr > numberOfFrames - 1)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::goToFrameNumber(): requested frame was not found");
	}

	int64_t dist = (int64_t)frameNr - latestFrameIndexRequested;

	switch (dist)
	{
		case 0:
			break;
		case 1:
			containerDemuxer.nextFrame(&decodedFrame);
			break;
		default:
			containerDemuxer.goToFrame(timestampMilliSeconds, &decodedFrame);
	}
		
	latestFrameIndexRequested = (int64_t)(double(containerDemuxer.getVideoPacket().dts - stream->first_dts) / ((double)timebase.den / (double)timebase.num / this->fps));
	actual_timestamp = StartTime + (int64_t)(latestFrameIndexRequested * frameDist) * 1000; // *1000 ... milliseconds to microseconds, StartTime already in microseconds

	convertFrame(&decodedFrame, numCsp, frame);
}

void VideoImport_FFmpeg::getNextFrame(int numCsp, VideoImport_FFmpeg_Frame *frame)
{
	if (!frame)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::getNextFrame(): parameter frame was NULL");
	}

	AVRational timebase = this->containerDemuxer.getFormatCtx()->streams[0]->time_base;
	double time_base = (double)timebase.num / (double)timebase.den;
	AVStream *stream = this->containerDemuxer.getFormatCtx()->streams[0];
	
	containerDemuxer.nextFrame(&decodedFrame);

	latestFrameIndexRequested = (int64_t)(double(containerDemuxer.getVideoPacket().dts - stream->first_dts) / ((double)timebase.den / (double)timebase.num / this->fps));
	actual_timestamp = StartTime + (int64_t)(latestFrameIndexRequested * frameDist) * 1000; // *1000 ... milliseconds to microseconds, StartTime already in microseconds

	convertFrame(&decodedFrame, numCsp, frame);
}

void VideoImport_FFmpeg::convertFrame(AVFrame *frame, int numCspDesired, VideoImport_FFmpeg_Frame *convertedFrame)
{	
	AVFrame *pFrame = NULL;
	if (numCspDesired == VIDEOIMPORT_FFMPEG_COLORSPACE_YUV420)
	{
		if (!picYUV420)
		{
			picYUV420 = av_frame_alloc();
			picYUV420->data[0] =  new unsigned char[3 * frame->width * frame->height / 2];
			picYUV420->width = frame->width;
			picYUV420->height = frame->height;
			int offset = frame->width * frame->height;
			picYUV420->data[1] = picYUV420->data[0] + offset;
			offset += frame->width * frame->height / 4;
			picYUV420->data[2] = picYUV420->data[0] + offset;
			picYUV420->linesize[0] = frame->linesize[0];
			picYUV420->linesize[1] = frame->linesize[1];
			picYUV420->linesize[2] = frame->linesize[2];
		}
		
		if (!cSwScaleYUV420P)
		{
			cSwScaleYUV420P = sws_getContext(frame->width, frame->height, this->decoder.getCodecCtx()->pix_fmt, frame->width, frame->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
		}

		int nRet = sws_scale(cSwScaleYUV420P, frame->data, frame->linesize, 0, frame->height,
			this->picYUV420->data, this->picYUV420->linesize);

		if (nRet < 0)
		{
			throw std::runtime_error("error in function VideoImport_FFmpeg::convertFrame: color conversion to AV_PIX_FMT_YUV420P failed");
		}		

		pFrame = this->picYUV420;
	}
	else if (numCspDesired == VIDEOIMPORT_FFMPEG_COLORSPACE_BGR24)
	{
		if (!picBGR24)
		{
			picBGR24 = av_frame_alloc();
			picBGR24->data[0] = new unsigned char[3 * frame->width * frame->height];
			picBGR24->data[1] = NULL;
			picBGR24->data[2] = NULL;
			picBGR24->linesize[0] = 3 * frame->width;
			picBGR24->linesize[1] = 0;
			picBGR24->linesize[2] = 0;
			picBGR24->width = frame->width;
			picBGR24->height = frame->height;
		}

		if (!cSwScaleBGR24)
		{
			cSwScaleBGR24 = sws_getContext(frame->width, frame->height, this->decoder.getCodecCtx()->pix_fmt, frame->width, frame->height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
		}

		int nRet = sws_scale(cSwScaleBGR24, frame->data, frame->linesize, 0, frame->height,
			this->picBGR24->data, this->picBGR24->linesize);

		if (nRet < 0)
		{
			throw std::runtime_error("error in function VideoImport_FFmpeg::convertFrame: color conversion to AV_PIX_FMT_BGR24 failed");
		}

		pFrame = this->picBGR24;
	}
	else if (numCspDesired == VIDEOIMPORT_FFMPEG_COLORSPACE_RGB24)
	{
		if (!picRGB24)
		{
			picRGB24 = av_frame_alloc();
			picRGB24->data[0] = new unsigned char[3 * frame->width * frame->height];
			picRGB24->data[1] = NULL;
			picRGB24->data[2] = NULL;
			picRGB24->linesize[0] = 3 * frame->width;
			picRGB24->linesize[1] = 0;
			picRGB24->linesize[2] = 0;
			picRGB24->width = frame->width;
			picRGB24->height = frame->height;
		}

		if (!cSwScaleRGB24)
		{
			cSwScaleRGB24 = sws_getContext(frame->width, frame->height, this->decoder.getCodecCtx()->pix_fmt, frame->width, frame->height, AV_PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);
		}

		int nRet = sws_scale(cSwScaleRGB24, frame->data, frame->linesize, 0, frame->height,
			this->picRGB24->data, this->picRGB24->linesize);

		if (nRet < 0)
		{
			throw std::runtime_error("error in function VideoImport_FFmpeg::convertFrame: color conversion to AV_PIX_FMT_RGB24 failed");
		}

		pFrame = this->picRGB24;
	}

	convertedFrame->width = pFrame->width;
	convertedFrame->height = pFrame->height;
	convertedFrame->timestamp   =  this->actual_timestamp;
	convertedFrame->framenumber =  this->latestFrameIndexRequested;
	convertedFrame->data        =  pFrame->data[0];
	convertedFrame->compression =  numCspDesired;
}

VideoImport_FFmpeg::ContainerDemuxer::ContainerDemuxer() : pFormatCtx(NULL), nTimeAudio(0), pDecoder(NULL)
{
	av_init_packet(&this->packetVideo);
}

VideoImport_FFmpeg::ContainerDemuxer::~ContainerDemuxer()
{
}

void VideoImport_FFmpeg::ContainerDemuxer::registerParentInstance(VideoImport_FFmpeg *pParent)
{
	this->pParent = pParent;
}

void VideoImport_FFmpeg::ContainerDemuxer::registerDecoder(Decoder *pDecoder)
{
	this->pDecoder = pDecoder;
}

void VideoImport_FFmpeg::ContainerDemuxer::open(const char *strFilename)
{
	int nRet = 0;

	//init
	av_register_all();

	//open input video file 
	nRet = avformat_open_input(&this->pFormatCtx, strFilename, NULL, 0);
	if (nRet < 0)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::ContainerDemuxer::open: file not found");
	}

	//get the streams
	nRet = avformat_find_stream_info(this->pFormatCtx, NULL);
	if ((nRet < 0) || (this->pFormatCtx->nb_streams == 0))
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::ContainerDemuxer::open: no stream found");
	}

	//output to console
	av_dump_format(this->pFormatCtx, 0, strFilename, false);
}

bool VideoImport_FFmpeg::ContainerDemuxer::seekKeyFrame(int64_t timestamp)
{
	AVRational timebase = this->getFormatCtx()->streams[0]->time_base;
	double time_base = (double)timebase.num / (double)timebase.den;

	int64_t first_dts = this->getFormatCtx()->streams[0]->first_dts;

	int64_t timestampConverted = (int64_t)((double)timestamp / this->pParent->frameDist) * ((double)timebase.den / (double)timebase.num / this->pParent->fps) + first_dts;	

	int64_t request_timestamp = (AV_TIME_BASE / ((double)timebase.den / (double)timebase.num)) * timestampConverted;

	avcodec_flush_buffers(this->pDecoder->getCodecCtx());

	int x = av_seek_frame(this->pFormatCtx, -1, (int64_t)(request_timestamp), AVSEEK_FLAG_BACKWARD);
	
	//if backward search for key-frame is not successful, search forward
	if (x < 0)
		x = av_seek_frame(this->pFormatCtx, -1, (int64_t)(request_timestamp), 0);	

	avcodec_flush_buffers(this->pDecoder->getCodecCtx());

	return true;
}

bool VideoImport_FFmpeg::ContainerDemuxer::goToFrame(int64_t timestamp, AVFrame *decodedFrame)
{	
	int64_t first_dts = this->getFormatCtx()->streams[0]->first_dts;

	AVRational timebase = this->getFormatCtx()->streams[0]->time_base;
	double time_base = (double)timebase.num / (double)timebase.den;	

	bool frameFound = this->seekKeyFrame(timestamp);
	if (!frameFound)
		return(false);

	if (this->packetVideo.stream_index != 0)
	{
		throw std::runtime_error("error in function VideoImport_FFmpeg::ContainerDemuxer::goToFrame: video stream expected but not found");
	}
	
	bool success = nextFrame(decodedFrame);
	
	while((success) && ((this->packetVideo.dts - first_dts) * time_base * 1000 < timestamp)) //  * 1000... sec to msec
	{
		success = nextFrame(decodedFrame);
	}

	return(success);
}

bool VideoImport_FFmpeg::ContainerDemuxer::nextFrame(AVFrame *decodedFrame)
{
	bool frameFound = false;

	int ret = AVERROR(EAGAIN);
	while (ret == AVERROR(EAGAIN))
	{
		frameFound = this->readNext();
		if (!frameFound)
			return(false);
		ret = pDecoder->decode(decodedFrame);
	}

	return(true);
}

bool VideoImport_FFmpeg::ContainerDemuxer::readNext()
{
	int nRet = 0;
	bool hasVideoPacket = false;
	AVPacket newPacket;		
	
	while (!hasVideoPacket)
	{
		nRet = av_read_frame(this->pFormatCtx, &newPacket);
		if(nRet < 0)
		{
			av_packet_unref(&newPacket);
			return(false);
		}

		av_packet_unref(&this->packetVideo);
		this->packetVideo = newPacket;

		if (this->packetVideo.stream_index != 0)
		{
			hasVideoPacket = false;	
		}
		else
		{
			hasVideoPacket = true;
		}
	}

	return(true);
}

void VideoImport_FFmpeg::ContainerDemuxer::close()
{
	av_packet_unref(&this->packetVideo);
	avformat_close_input(&this->pFormatCtx);	
}


VideoImport_FFmpeg::Decoder::Decoder() : pFilterGraph(NULL), pContainerDemuxerParent(NULL)
{
	memset(&decoderParams, 0, sizeof(DecoderParams));
}

VideoImport_FFmpeg::Decoder::~Decoder()
{
}

void VideoImport_FFmpeg::Decoder::registerContainterDemuxerParent(ContainerDemuxer *pContainerDemuxer)
{
	this->pContainerDemuxerParent = pContainerDemuxer;
}

void VideoImport_FFmpeg::Decoder::setDecoderParams(const DecoderParams &decoderParams)
{
	this->decoderParams = decoderParams;
}

void VideoImport_FFmpeg::Decoder::open()
{
    avcodec_register_all();
	av_register_all();
    avfilter_register_all();

	this->codecCtx = NULL;
	this->codec = NULL;
	this->picture = NULL;
		
	av_init_packet(&this->avpkt);

	this->codec = avcodec_find_decoder(this->pContainerDemuxerParent->getFormatCtx()->streams[0]->codecpar->codec_id);
    if (!this->codec)
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::open(): function avcodec_find_decoder() failed");

	this->codecCtx = avcodec_alloc_context3(this->codec);

	avcodec_parameters_to_context(this->codecCtx, this->pContainerDemuxerParent->getFormatCtx()->streams[0]->codecpar);

    this->picture = av_frame_alloc();

	if (avcodec_open2(this->codecCtx, this->codec, NULL) < 0) 
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::open(): function avcodec_open2() failed");
}


void VideoImport_FFmpeg::Decoder::initFilters()
{
	if (pFilterGraph)
		return;

    char args[512];
    int ret;
    AVFilter *buffersrc  = avfilter_get_by_name("buffer");
    AVFilter *buffersink = avfilter_get_by_name("buffersink");
	//enum AVPixelFormat pix_fmts[] = { AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };
    AVBufferSinkParams *buffersink_params;
    this->pFilterGraph = avfilter_graph_alloc();

#ifdef _WIN32
    sprintf_s(args, sizeof(args),
            "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
            this->codecCtx->width, this->codecCtx->height, this->codecCtx->pix_fmt,
            this->codecCtx->time_base.num, this->codecCtx->time_base.den,
            this->codecCtx->sample_aspect_ratio.num, this->codecCtx->sample_aspect_ratio.den);
#else
    snprintf(args, sizeof(args),
            "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
            this->codecCtx->width, this->codecCtx->height, this->codecCtx->pix_fmt,
            this->codecCtx->time_base.num, this->codecCtx->time_base.den,
            this->codecCtx->sample_aspect_ratio.num, this->codecCtx->sample_aspect_ratio.den);
#endif
    ret = avfilter_graph_create_filter(&this->pBufferSrcCtx, buffersrc, "in", args, NULL, this->pFilterGraph);
    if (ret < 0) {
        //av_log(NULL, AV_LOG_ERROR, "Cannot create buffer source\n");
		freeFilters();
        throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_graph_create_filter failed");
    }
    /* buffer video sink: to terminate the filter chain. */
    buffersink_params = av_buffersink_params_alloc();
    buffersink_params->pixel_fmts = &this->codecCtx->pix_fmt; //pix_fmts
    ret = avfilter_graph_create_filter(&this->pBufferSinkCtx, buffersink, "out", NULL, buffersink_params, this->pFilterGraph);
    av_free(buffersink_params);
    if (ret < 0) {
        //av_log(NULL, AV_LOG_ERROR, "Cannot create buffer sink\n");
		freeFilters();
        throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function av_free failed");
    }

	AVFilterContext *filterContextDeinterlace;
	// Find the deinterlacing filter
	AVFilter *filterDeinterlace = avfilter_get_by_name("w3fdif");
	if (!filterDeinterlace)
	{
		freeFilters();
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_get_by_name failed");
	}

	// Create the filter context with deinterlacing filter
	filterContextDeinterlace = avfilter_graph_alloc_filter(this->pFilterGraph, filterDeinterlace, NULL);
	if (!filterContextDeinterlace)
	{
		freeFilters();
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_graph_alloc_filter failed");
	}

	// Init the deinterlacing filter (tested: "w3fdif" with "simple" and "complex" options, "yadif" with "1:-1" option, w3fdif seems to give the best results
	if ((ret = avfilter_init_str(filterContextDeinterlace, "complex")) < 0)
	{
		freeFilters();
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_init_str failed");
	}

    if ((ret = avfilter_link(pBufferSrcCtx, 0, filterContextDeinterlace, 0)) < 0)
	{
		freeFilters();
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_link failed");
	}

    if ((ret = avfilter_link(filterContextDeinterlace, 0, pBufferSinkCtx, 0)) < 0)
	{
		freeFilters();
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_link failed");
	}

    if ((ret = avfilter_graph_config(this->pFilterGraph, NULL)) < 0)
    {
		freeFilters();
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::initFilters(): function avfilter_graph_config failed");
	}
}

void VideoImport_FFmpeg::Decoder::freeFilters()
{
	if (this->pFilterGraph)
	{
		avfilter_graph_free(&this->pFilterGraph);
		this->pFilterGraph = NULL;
	}
}

int VideoImport_FFmpeg::Decoder::decode(AVFrame *pFrame)
{
	if (!pFrame)
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::decode(): parameter pFrame is NULL");
	if (!pFrame->data)
		throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::decode(): problem with parameter pFrame: pFrame->data is NULL");

	int len = 0;

	av_packet_unref(&this->avpkt);

	this->avpkt.size = this->pContainerDemuxerParent->getVideoPacket().size;
	this->avpkt.data = this->pContainerDemuxerParent->getVideoPacket().data;

	len = avcodec_send_packet(this->codecCtx, &this->avpkt);
	if (len < 0) 
	{
		std::string errorMsg = "error in function VideoImport_FFmpeg::Decoder::decode(): Error while decoding frame " + boost::lexical_cast<std::string>(this->pContainerDemuxerParent->getVideoPacket().dts);
		throw std::runtime_error(errorMsg);		
	}

	av_frame_unref(this->picture);

	int ret = avcodec_receive_frame(this->codecCtx, this->picture);
	if (ret >= 0) 
	{		
		if ( ((this->picture->interlaced_frame) && (this->decoderParams.deinterlaceMode == Decoder::DECODER_DEINTERLACEMODE_AUTO)) ||
			 (this->decoderParams.deinterlaceMode == Decoder::DECODER_DEINTERLACEMODE_FORCE) )
		{
			this->initFilters();

			// push the decoded frame into the filtergraph
			if (av_buffersrc_add_frame_flags(this->pBufferSrcCtx, this->picture, AV_BUFFERSRC_FLAG_KEEP_REF) < 0) {				
				freeFilters();
				throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::decode(): function av_buffersrc_add_frame_flags failed");
			}
			// pull filtered (deinterlaced) frame from the filtergraph (actually it is a try to pull)
			while (1) // get frame from buffersink as long as there are new frames
			{
				AVFrame *filt_frame = av_frame_alloc();
				ret = av_buffersink_get_frame(this->pBufferSinkCtx, filt_frame);

				if (ret >= 0)
				{
					// result AVFrame picture becomes the new filtered frame, get rid of the old
					av_frame_unref(this->picture);
					this->picture = filt_frame;					
				}
				else if (ret == AVERROR(EAGAIN)) // latest frame read was last (newest)
				{
					// since it is already in picture - do nothing except cleanup and break loop
					av_frame_unref(filt_frame);
					break;
				}
				else			
				{
					av_frame_unref(filt_frame);
					freeFilters();
					throw std::runtime_error("error in function VideoImport_FFmpeg::Decoder::decode(): function av_buffersink_get_frame failed");
				}
			}
		}

		memcpy(pFrame, this->picture, sizeof(AVFrame));

		//this->avpkt.size -= len;
		//this->avpkt.data += len;
	}
	return(ret);
}

void VideoImport_FFmpeg::Decoder::close()
{
	avcodec_close(this->codecCtx);
	av_packet_unref(&this->avpkt);
    av_frame_unref(this->picture);
	av_free(this->codecCtx);
}
