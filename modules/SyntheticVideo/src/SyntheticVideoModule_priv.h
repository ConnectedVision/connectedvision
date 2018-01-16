/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>
#include <map>



#include <Module/Module_BaseClass.h>

#include "SyntheticVideoDataOutputPin.h"

#include "Class_SyntheticVideo_params.h"
#include "Class_SyntheticVideo_output_VideoMetadata.h"
#include "Class_SyntheticVideo_output_FrameMetadata.h"

#include "opencv/cv.h"
#include "opencv/highgui.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

class SyntheticVideo
{
public:
	std::string		filename;
	int64_t			numFrames;
	int64_t			width;
	int64_t			height;
	timestamp_t		startTime;
	timestamp_t		endTime;
	double			fps;
	timestamp_t		avgFramedist;
	timestamp_t		timestamp;
	int64_t			framenumber;
	cv::Mat*		rgb_img;
	cv::Mat*		bgr_img;
	BYTE*			yuv_img;
	cv::Scalar		backgroundColor;
	cv::Scalar		osdTextColor;
	cv::Scalar		foregroundColor;
	int				sizeOfObject;
};

class SyntheticVideoModule_priv
{
public:
	std::map<id_t,SyntheticVideo> syntheticVideoMap;

	virtual int SyntheticVideo_init(Class_generic_config config);
	virtual int SyntheticVideo_goToFrameNumber(const id_t configID, const int64_t index, unsigned int colorspace);
	virtual int SyntheticVideo_goToTimestamp(const id_t configID, const int64_t timestamp, unsigned int colorspace);
	
	virtual void prepareVideoHandle(Class_generic_config &config);

	static std::string VideoMetadataEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace);
	static std::string FrameMetadataEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace);
	static std::string RAWEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace);
	static std::string PngEncoder(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace);

	static void RGB2Yuv420p(BYTE *yuv, BYTE *rgb, unsigned width, unsigned height);
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision