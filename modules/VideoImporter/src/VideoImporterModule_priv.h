/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>
#include <map>

#include <ConnectedVisionModule.h>

#include "VideoDataOutputPin.h"

#include "Class_VideoImporter_params.h"
#include "Class_VideoImporter_output_VideoMetadata.h"
#include "Class_VideoImporter_output_FrameMetadata.h"

#include "./VideoImport_FFmpeg/VideoImport_FFmpeg.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

class VideoImport
{
public:
	std::string	m_Filename;
	ConnectedVision::shared_ptr<VideoImport_FFmpeg> pVideoImportFFmpeg;
	int64_t m_RecordingDateTime;
	VideoImport_FFmpeg::DEINTERLACEMODE deinterlaceMode;
	VideoImport_FFmpeg::VideoImport_FFmpeg_MetaData m_MetaData;
	VideoImport_FFmpeg::VideoImport_FFmpeg_Frame m_Frame;
	boost::mutex m_mutex;
};

class VideoImporterModule_priv
{
public:
	std::map<id_t, boost::shared_ptr<VideoImport>> videoImportMap;
	boost::mutex mutexVideoImportMap;

	virtual void VideoImport_init(const Class_generic_config config);
	virtual void VideoImport_goToFrameNumber(const id_t configID, const int64_t index, unsigned int colorspace);
	virtual void VideoImport_goToTimestamp(const id_t configID, const int64_t timestamp, unsigned int colorspace);

	static std::string FileMetadataEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace);
	static std::string FrameMetadataEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace);
	static std::string RAWEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace);
	static std::string PngEncoder(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace);
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision
