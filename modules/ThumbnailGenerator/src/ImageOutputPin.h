/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <sqlite3.h>

#include <opencv/cv.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include <IConnectedVisionModule.h>
#include "ThumbnailGeneratorModule.h"

#include "Class_ThumbnailGenerator_input_BoundingBox.h"
//#include "Class_ThumbnailGenerator_input_Polyline.h"

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 *
 */
class ImageOutputPin : public IConnectedVisionOutputPin
{
public:
	enum ModificationType { BoundingBoxOverlay, Cropping };
	//enum ModificationType { BoundingBoxOverlay, Cropping, PolylineOverlay };

	static const pinID_t PinID() { return "ImageOutputPin"; };
	
	ImageOutputPin(ThumbnailGeneratorModule *module, ModificationType modificationType, bool thumbnailMode);

	virtual ~ImageOutputPin();

	virtual void init(const std::string& configStr);

	virtual int getByID(const id_t id, ConnectedVisionResponse &response);

	virtual int getByIndex(const int64_t index, ConnectedVisionResponse &response);
	virtual int getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response);

	virtual int getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response);

protected:
	cv::Scalar convert(cv::Scalar color);

	cv::Rect convert(const boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> srcBoundingBox, const cv::Mat& image);

	std::vector<cv::Rect> convert(const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> srcBoundingBoxes, const cv::Mat& image);

	//cv::Point convert(const boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline_coordinates> coordinate, const cv::Mat& image);

	//std::vector<cv::Point> convert(const boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline> polyline, const cv::Mat& image);

	cv::Mat createThumbnail(const cv::Mat& image);

	cv::Mat crop(const cv::Mat& image, cv::Rect rectangle);

	int crop(const cv::Mat& image, const boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox> boundingBox, ConnectedVisionResponse &response);

	cv::Mat decode(const boost::shared_ptr<std::string> imageData);

	int encode(const cv::Mat& image, ConnectedVisionResponse& response);

	boost::shared_ptr<std::string> encode(const cv::Mat& image, std::string imageFormat);

	int modify(const boost::shared_ptr<std::string> imageDataStr, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes, ConnectedVisionResponse &response);

	//int modify(const boost::shared_ptr<std::string> imageData, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines, ConnectedVisionResponse &response);

	cv::Mat overlay(const cv::Mat& image, cv::Rect rectangle, const cv::Scalar color, int lineWidth);

	cv::Mat overlay(const cv::Mat& image, const std::vector<cv::Point> points, cv::Scalar color, int lineWidth);

	int overlay(const cv::Mat& image, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes, ConnectedVisionResponse &response);

	//int overlay(const cv::Mat& image, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines, ConnectedVisionResponse &response);

	template <class T, class U> static T requeryBeforeTimestamp(U inputPin, const timestamp_t timestamp, int maxAttempts);

	template <class T, class U> static T requeryByIndex(U inputPin, const int64_t index, int maxAttempts);

	template <class T, class U> static T requeryByTimestamp(U inputPin, const timestamp_t timestamp, int maxAttempts);

	ThumbnailGeneratorModule *module;
	Class_generic_config config;
	ModificationType modificationType;
	bool thumbnailMode;
};



/**
* Workaround helper method for querying data from input pin before timestamp to avoid bug in framework where sometimes a null reference is returned when querying an existing object from the input pin.
*
* @param[in] inputPin The input pin.
* @param[in] timestamp The timestamp.
* @param[in] maxAttempts The maximum number of attempts before returning a null reference of the object.
*
* @return The object instance or null a reference if it could not be retrieved.
*
*/
template <class T, class U> T ImageOutputPin::requeryBeforeTimestamp(U inputPin, const timestamp_t timestamp, int maxAttempts)
{
	T instance;
	Class_generic_status_stableResults stableResults = inputPin->getStableResults();

	int i = 0;

	while(instance.empty() && i < maxAttempts)
	{
		try
		{
			instance = inputPin->getBeforeTimestamp(timestamp);
		}
		catch(...)
		{
		}

		if(instance.empty())
		{
			boost::this_thread::sleep(boost::posix_time::milliseconds(10));
		}

		i++;
	}

	return instance;
}



/**
* Workaround helper method for querying data from input pin by index to avoid bug in framework where sometimes a null reference is returned when querying an existing object from the input pin.
*
* @param[in] inputPin The input pin.
* @param[in] index The index.
* @param[in] maxAttempts The maximum number of attempts before returning a null reference of the object.
*
* @return The object instance or null a reference if it could not be retrieved.
*
*/
template <class T, class U> T ImageOutputPin::requeryByIndex(U inputPin, const int64_t index, int maxAttempts)
{
	T instance;
	Class_generic_status_stableResults stableResults = inputPin->getStableResults();

	if(stableResults.get_indexStart() <= index && index <= stableResults.get_indexEnd())
	{
		int i = 0;

		while(!instance && i < maxAttempts)
		{
			try
			{
				instance = inputPin->getByIndex(index);
			}
			catch(...)
			{
			}

			if(!instance)
			{
				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			}

			i++;
		}
	}

	return instance;
}



/**
* Workaround helper method for querying data from input pin by timestamp to avoid bug in framework where sometimes a null reference is returned when querying an existing object from the input pin.
*
* @param[in] inputPin The input pin.
* @param[in] timestamp The timestamp.
* @param[in] maxAttempts The maximum number of attempts before returning a null reference of the object.
*
* @return The object instance or null a reference if it could not be retrieved.
*
*/
template <class T, class U> T ImageOutputPin::requeryByTimestamp(U inputPin, const timestamp_t timestamp, int maxAttempts)
{
	T instance;
	Class_generic_status_stableResults stableResults = inputPin->getStableResults();

	if(stableResults.get_timestampStart() <= timestamp && timestamp <= stableResults.get_timestampEnd())
	{
		int i = 0;

		while(instance.empty() && i < maxAttempts)
		{
			try
			{
				instance = inputPin->getByTimestamp(timestamp);
			}
			catch(...)
			{
			}

			if(instance.empty())
			{
				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
			}

			i++;
		}
	}

	return instance;
}

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision