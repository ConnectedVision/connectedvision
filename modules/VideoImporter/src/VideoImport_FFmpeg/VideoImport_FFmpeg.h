/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef __VIDEOIMPORT_FFMPEG_H__
#define __VIDEOIMPORT_FFMPEG_H__

#include <stdint.h>
#include <inttypes.h>

extern "C"
{
	#include <libavformat/avformat.h>
	#include <libavcodec/avcodec.h>
	#include <libavutil/mathematics.h>
	#include <libswscale/swscale.h>
	#include <libavutil/rational.h>
	#include <libavutil/avutil.h>
	#include <libavfilter/buffersink.h>
	#include <libavfilter/buffersrc.h>
	#include <libavfilter/avfilter.h>
}

#define VIDEOIMPORT_FFMPEG_COLORSPACE_YUV420 0
#define VIDEOIMPORT_FFMPEG_COLORSPACE_BGR24  1
#define VIDEOIMPORT_FFMPEG_COLORSPACE_RGB24  2

typedef void* HANDLE;

class VideoImport_FFmpeg
{
public:
	typedef void* VideoImport_FFmpeg_Handle;

	typedef enum {
		DEINTERLACEMODE_AUTO,
		DEINTERLACEMODE_FORCE,
		DEINTERLACEMODE_OFF,
	} DEINTERLACEMODE;

	/**
	 * video meta data structure
	 */
	typedef struct {
		int width; ///< width of frame in pixels
		int height; ///< height of frame in pixels
		int64_t numberOfFrames;	///< number of frames of video
		double fps;	///< frames per second of video
		int64_t startTime;	///< timestamp of start frame of video
		int64_t endTime; ///< timestamp of end frame of video
	} VideoImport_FFmpeg_MetaData;

	/**
	 * single video frame
	 */
	typedef struct {
		int width; ///< width of frame [pixel]
		int height;	///< height of frame [pixel]
		int64_t timestamp;	///< timestamp of frame
		int64_t framenumber; ///< number of frame
		int compression; ///< image format / compression (0: YUV 4:2:0 raw images, 1: BGR interleaved, 2: RGB interleaved)
		unsigned char *data; ///< image data
	} VideoImport_FFmpeg_Frame;

	/**
	* constructor variant of VideoImport_FFmpeg class
	*
	* @param [in] filename	name of the video file to load
	*
	*/
	VideoImport_FFmpeg(const char filename[]);

	/**
	* constructor variant of VideoImport_FFmpeg class
	*
	* @param [in] filename name of the video file to load
	* @param [in] recordingDateTime the start timestamp of the video
	* @param [in] deinterlacemode the deinterlace mode to be used
	*	
	*/
	VideoImport_FFmpeg(const char filename[], int64_t recordingDateTime, DEINTERLACEMODE deinterlacemode = DEINTERLACEMODE_AUTO);

	/**
	* destructor of VideoImport_FFmpeg class
	*/
	virtual ~VideoImport_FFmpeg();

	/**
	* frees resources allocated while using instance of VideoImport_FFmpeg class
	*/
	void freeResources();

	/**
	* get meta data of connected video source
	*
	* @see VideoImport_FFmpeg_MetaData
	*	
	* @param [out] metaData	meta information about video
	*
	*/
	void getMetaData(VideoImport_FFmpeg_MetaData *metaData);

	/**
	* set image pointer to closest frame to timestamp and retrieve image
	*
	* @param [in] timestamp	the timestamp of the desired frame
	* @param [in] numCspDesired number identifier of desired colorspace
	* @param [out] frame fetched frame
	*
	*/
	void goToTimestamp(int64_t timestamp, int numCspDesired, VideoImport_FFmpeg_Frame *frame);

	/**
	* set image pointer to closest frame to timestamp and retrieve image
	*
	* @param [in] frameNr the frame number of the desired frame
	* @param [in] numCspDesired number identifier of desired colorspace
	* @param [out] frame decoded frame
	*
	*/
	void goToFrameNumber(unsigned int frameNr, int numCspDesired, VideoImport_FFmpeg_Frame *frame);

	/**
	* get next frame from image buffer
	*
	* @param [in] numCspDesired number identifier of desired colorspace
	* @param [out] frame		fetched frame
	*
	*/
	void getNextFrame(int numCspDesired, VideoImport_FFmpeg_Frame *frame);

private:
	class ContainerDemuxer;

	class Decoder
	{
	public:
		typedef enum {
			DECODER_DEINTERLACEMODE_AUTO,
			DECODER_DEINTERLACEMODE_FORCE,
			DECODER_DEINTERLACEMODE_OFF,
		} DECODER_DEINTERLACEMODE;


		typedef struct {
			DECODER_DEINTERLACEMODE deinterlaceMode;
		} DecoderParams;

		Decoder();
		virtual ~Decoder();

		void registerContainterDemuxerParent(ContainerDemuxer *pContainerDemuxer);
		void setDecoderParams(const DecoderParams &decoderParams);
		void open();		
		void initFilters();
		void freeFilters();
		int decode(AVFrame *pFrame);
		void close();

		AVCodecContext* getCodecCtx() const { return(codecCtx); };

	private:
		DecoderParams decoderParams;
		AVCodec *codec;
		AVCodecContext *codecCtx;
		AVFrame *picture;
		AVPacket avpkt;
		AVCodecID codecID;

		ContainerDemuxer *pContainerDemuxerParent;

		AVFilterGraph *pFilterGraph;
		AVFilterContext *pBufferSinkCtx;
		AVFilterContext *pBufferSrcCtx;
		bool filterInit;
	};

	class ContainerDemuxer
	{
	public:
		ContainerDemuxer();
		virtual ~ContainerDemuxer();

		void registerParentInstance(VideoImport_FFmpeg *pParent);
		/**
		*
		* registers the used decoder instance
		*		
		* @param pDecoder pointer to the used decoder
		*
		*/
		void registerDecoder(Decoder *pDecoder);

		/**
		*
		* opens a file (container) for reading
		*		
		* @param strFilename full path name of the file to open
		*
		*/
		void open(const char *strFilename);

		/**
		*
		* reads video frame packet at a given timestamp
		*
		* @param [in] timestamp the timestamp of the desired frame
		* @param [out] decodedFrame the decoded frame
		* @returns true if a new frame was found
		*/
		bool goToFrame(int64_t timestamp, AVFrame *decodedFrame);

		/**
		*
		* reads the next video frame or audio packet (what comes first)
		*
		* @param [out] decodedFrame the decoded frame
		* @returns true if a new frame was found
		*/
		bool nextFrame(AVFrame *decodedFrame);

		/** 
		*
		* cleans up and destroys the given demux instance
		*
		*/
		void close();

		AVFormatContext* getFormatCtx() const { return(pFormatCtx); };

		AVPacket getVideoPacket() const { return(packetVideo); };

	private:
		/**
		*
		* seeks the nearest keyframe video frame at a given timestamp (first backward search, then if no keyframe was found forward search)
		*
		* @param [in] timestamp the timestamp used for searching next key frame
		* @returns true if a frame was found
		*/
		bool seekKeyFrame(int64_t timestamp);

		/**
		*
		* reads the next video frame or audio packet (what comes first)
		*		
		* @return returns true on successful read of video frame
		*
		*/
		bool readNext();

		VideoImport_FFmpeg *pParent;

		Decoder *pDecoder;

		AVFormatContext *pFormatCtx;
		AVPacket packetVideo;
		AVPacket pktAudio;
		int64_t nTimeVideo;
		int64_t nTimeAudio;
	};

	Decoder decoder;
	ContainerDemuxer containerDemuxer;
	
	AVFrame decodedFrame;

	int64_t StartTime;
	int64_t EndTime;
	int64_t LengthTime;
	double fps;	
	int64_t numberOfFrames;
	double frameDist;
	int64_t actual_timestamp;
	int64_t latestFrameIndexRequested;

	AVFrame *picYUV420;
	AVFrame *picBGR24;
	AVFrame *picRGB24;

	SwsContext *cSwScaleYUV420P;
	SwsContext *cSwScaleBGR24;
	SwsContext *cSwScaleRGB24;

	void convertFrame(AVFrame *frame, int numCspDesired, VideoImport_FFmpeg_Frame *convertedFrame);
};

#endif //__VIDEOIMPORT_FFMPEG_H__