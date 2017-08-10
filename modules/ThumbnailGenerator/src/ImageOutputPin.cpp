/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <fstream>
#include <iostream>
#include <numeric>
#include <sstream>
#include <sstream>
#include <string>
#include <vector>

#include "ImageOutputPin.h"
#include <Module/InputPins/InputPin_PNG.h>

#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>
using namespace boost::timer;

#include <opencv2/opencv.hpp>

#include "Class_ThumbnailGenerator_params.h"
#include "InputPin_ThumbnailGenerator_input_BoundingBox.h"
#include "InputPin_ThumbnailGenerator_input_ImageMetadata.h"
//#include "InputPin_ThumbnailGenerator_input_Polyline.h"

// template include guard
#ifndef ImageOutputPin_def
#define ImageOutputPin_def

namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

using namespace std;
using namespace ConnectedVision::HTTP;


ImageOutputPin::ImageOutputPin(ThumbnailGeneratorModule *module, ModificationType modificationType, bool thumbnailMode)
{
	this->module = module;
	this->modificationType = modificationType;
	this->thumbnailMode = thumbnailMode;
}



ImageOutputPin::~ImageOutputPin(void)
{
}



/**
 * init output pin with config
 *
 * @param[in] configStr			config chain
 *
 * @return status code (analog to HTTP codes)
 */
void ImageOutputPin::init(const std::string& configStr)
{
	this->config.parseJson(configStr.c_str());
}



/**
* Converts the specified color from normalized RGB [0.0, 1.0] to OpenCV BGR [0, 255].
*
* @param[in] The normalized RGB color [0.0, 1.0].
*
* @return The OpenCV BGR [0, 255].
*/
cv::Scalar ImageOutputPin::convert(cv::Scalar color)
{
	return cv::Scalar(255.0 * color[2], 255.0 * color[1], 255.0 * color[0]);
}



/**
* Converts a module bounding box object from fractional coordinates to an OpenCV rectangle in pixel coordinates.
*
* @param[in] srcBoundingBox The source bounding box (fractional coordinates).
* @param[in] image The image to which the size of the bounding box is adapted.
*
* @return The bounding box in pixel coordinates.
*/
cv::Rect ImageOutputPin::convert(const boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox_boundingBox> srcBoundingBox, const cv::Mat& image)
{
	// define the srcBoundingBox
	int left = max(0.0, (double)image.cols * srcBoundingBox->get_left());
	int right = min((double)image.cols, (double)image.cols * srcBoundingBox->get_right());
	int bottom = min((double)image.rows, (double)image.rows * srcBoundingBox->get_bottom());
	int top = max(0.0, (double)image.rows * srcBoundingBox->get_top());

	int width = right - left;
	int height = bottom - top;

	cv::Rect dstRect(left, top, width, height);

	return dstRect;
}



/**
* Converts a vector of bounding boxes from fractional coordinates to pixel coordinates.
*
* @param[in] srcBoundingBoxes The source bounding boxes (fractional coordinates).
* @param[in] image The image to which the size of the bounding boxes are adapted.
*
* @return The bounding boxes in pixel coordinates.
*/
std::vector<cv::Rect> ImageOutputPin::convert(const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> srcBoundingBoxes, const cv::Mat& image)
{
	vector<cv::Rect> dstBoundingBoxes(srcBoundingBoxes.size());

	for(int i = 0; i < srcBoundingBoxes.size(); i++)
	{
		dstBoundingBoxes[i] = convert(srcBoundingBoxes.at(i)->get_boundingBox(), image);
	}

	return dstBoundingBoxes;
}



///**
//* Converts a module coordinate from fractional coordinates to pixel coordinates.
//*
//* @param[in] coordinate The source coordinate (fractional coordinates).
//* @param[in] image The image to which the size of the bounding boxes are adapted.
//*
//* @return The coordinate in pixel coordinates.
//*/
//cv::Point ImageOutputPin::convert(const boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline_coordinates> coordinate, const cv::Mat& image)
//{
//	cv::Point point;
//
//	point.x = max(0.0, (double)image.cols * coordinate->get_x());
//	point.y = max(0.0, (double)image.rows * coordinate->get_y());
//
//	return point;
//}



///**
//* Converts a module polyline object from fractional coordinates to a vector of OpenCV points in pixel coordinates.
//*
//* @param[in] polyline The source polyline (fractional coordinates).
//* @param[in] image The image to which the size of the polyline is adapted.
//*
//* @return The polyline in pixel coordinates.
//*/
//std::vector<cv::Point> ImageOutputPin::convert(const boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline> polyline, const cv::Mat& image)
//{
//	boost::shared_ptr<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline_coordinates>>> coordinates = polyline->get_coordinates();
//	vector<cv::Point> dstPolyline;
//
//	for(int i = 0; i < coordinates->size(); i++)
//	{
//		boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline_coordinates> coordinate = coordinates->at(i);
//
//		dstPolyline.push_back(this->convert(coordinate, image));
//	}
//
//	return dstPolyline;
//}



/**
* Creates a thumbnail version of an image.
*
* @param[in] image The input image.
*
* @return The thumbnail image.
*/
cv::Mat ImageOutputPin::createThumbnail(const cv::Mat& image)
{
	// <todo> get the thumbnail height from the config
	int dstHeight = 2.0 * 150.0;
	int dstWidth = ((double)dstHeight / (double)image.rows) * (double)image.cols;

	cv::Mat dstImage;
	cv::resize(image, dstImage, cv::Size(dstWidth, dstHeight), 0.0, 0.0, cv::INTER_CUBIC);
		
	return dstImage;
}



/**
* Crops an image according to the specified rectangular region.
*
* @param[in] image The input image.
* @param[in] rectangle The rectangular region used for cropping.
*
* @return The cropped image.
*/
cv::Mat ImageOutputPin::crop(const cv::Mat& image, cv::Rect rectangle)
{
	return image(rectangle).clone();
}



/**
* Crops an image according to the specified rectangular region.
*
* @param[in] image The input image.
* @param[in] boundingBoxes The rectangluar regions to crop.
* @param[out] response requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int ImageOutputPin::crop(const cv::Mat& image, const boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox> boundingBox, ConnectedVisionResponse &response)
{
	cv::Rect rectangle = this->convert(boundingBox->get_boundingBox(), image);

	cv::Mat croppedImage = this->crop(image, rectangle);

	if(this->thumbnailMode)
	{
		cv::Mat thumbnail = this->createThumbnail(croppedImage);
		return this->encode(thumbnail, response);
	}
	else
	{
		return this->encode(croppedImage, response);
	}
}



/**
* Encodes an image according to the specified image format.
*
* @param[in] image The source image.
* @param[in] imageFormat The image format (OpenCV imencode format style).
*
* @return status code (analog to HTTP codes)
*/
boost::shared_ptr<std::string> ImageOutputPin::encode(const cv::Mat& image, std::string imageFormat)
{
	// imencode() causes an error when returning from the current to the calling (parent) method if it is not allocated at all or insufficient space has been allocated
	// using 2 times the total number of array values was sufficient at least for color PNG and JPG images
	vector<unsigned char> dstImageVec(image.total() * 2);

	cv::imencode(imageFormat, image, dstImageVec);

	boost::shared_ptr<string> dstImageStr = boost::shared_ptr<string>(new string(reinterpret_cast<char*>(&dstImageVec[0]), dstImageVec.size()));

	return dstImageStr;
}



/**
* Encodes an image according to the specified image format, sets the response content and returns a status code.
*
* @param[in] image The source image
* @param[out] response requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int ImageOutputPin::encode(const cv::Mat& image, ConnectedVisionResponse& response)
{
	string extension;
	string mimeType;

	Class_ThumbnailGenerator_params params;
	params.parseJson(this->config.get_params());

	if(params.is_imageFormat_JPEG())
	{
		extension = ".jpg";
		mimeType = "image/jpeg";
	}
	else if(params.is_imageFormat_PNG())
	{
		extension = ".png";
		mimeType = "image/png";
	}
	else
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + " unsupported image format: " + *params.get_imageFormat());
	}

	boost::shared_ptr<string> dstImageStr;

	try
	{
		dstImageStr = this->encode(image, extension);
	}
	catch(std::runtime_error& e)
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + " failed to encode image (" + e.what() + ")");
	}

	//cout << "image size: " << (int)((double)dstImageVec.size() / pow(2.0, 10)) << "KB ";

	response.setContentType(mimeType);
	response.setContent(*dstImageStr);

	return HTTP_Status_OK;
}



/**
* Decodes an image (e.g. JPEG, PNG, TIFF, etc.).
*
* @param[in] imageData The encoded image data.
*
* @return The decoded image.
*/
cv::Mat ImageOutputPin::decode(const boost::shared_ptr<std::string> imageData)
{
	vector<char> vec(imageData->c_str(), imageData->c_str() + imageData->size());
	cv::Mat mat = cv::imdecode(cv::Mat(vec), CV_LOAD_IMAGE_ANYCOLOR);
	return mat;
}



/**
* Modifies an image (cropping or bounding box overlay).
*
* @param[in] imageData The encoded image data.
* @param[in] boundingBoxes The rectangular region used for cropping or bounding box overlay.
* @param[out] response requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int ImageOutputPin::modify(const boost::shared_ptr<std::string> imageData, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes, ConnectedVisionResponse &response)
{
	cv::Mat image = this->decode(imageData);

	if(this->modificationType == ImageOutputPin::ModificationType::BoundingBoxOverlay)
	{
		return this->overlay(image, boundingBoxes, response);
	}
	else if(this->modificationType == ImageOutputPin::ModificationType::Cropping)
	{
		if(boundingBoxes.size() > 1)
		{
			return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + " cropping does not support more than 1 bounding box for a single request (# boxes provided: " + intToStr(boundingBoxes.size()) + ")");
		}

		return this->crop(image, boundingBoxes.at(0), response);
	}
	else
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + " unsupported value for modification type: " + intToStr(this->modificationType));
	}
}



///**
//* Modifies an image (polyline overlay).
//*
//* @param[in] imageData The encoded image data.
//* @param[in] polylines The polylines used for polyline overlay.
//* @param[out] response requested data or error response
//*
//* @return status code (analog to HTTP codes)
//*/
//int ImageOutputPin::modify(const boost::shared_ptr<std::string> imageData, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines, ConnectedVisionResponse &response)
//{
//	cv::Mat image = this->decode(imageData);
//
//	if(this->modificationType == ImageOutputPin::ModificationType::PolylineOverlay)
//	{
//		return this->overlay(image, polylines, response);
//	}
//	else
//	{
//		return writeError(response, HTTP_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + " unsupported value for modification type: " + intToStr(this->modificationType));
//	}
//}



/**
* Overlays an image with a rectangle.
*
* @param[in] image The input image.
* @param[in] rectangle The rectangle.
* @param[in] color The line color (R,G,B [0.0, 1.0]).
* @param[in] lineWidth The line with.
*
* @return The overlayed image.
*/
cv::Mat ImageOutputPin::overlay(const cv::Mat& image, cv::Rect rectangle, cv::Scalar color, int lineWidth)
{
	cv::Mat dst = image.clone();
	cv::Scalar c = this->convert(color);
	cv::rectangle(dst, rectangle, c, lineWidth, CV_AA);

	return dst;
}



/**
* Overlays an image with a polyline.
*
* @param[in] image The input image.
* @param[in] points The polyline.
* @param[in] color The line color (R,G,B [0.0, 1.0]).
* @param[in] lineWidth The line with.
*
* @return The overlayed image.
*/
cv::Mat ImageOutputPin::overlay(const cv::Mat& image, const std::vector<cv::Point> points, cv::Scalar color, int lineWidth)
{
	cv::Mat dst = image.clone();
	cv::Scalar c = this->convert(color);
	cv::polylines(dst, points, false, c, lineWidth, CV_AA);

	return dst;
}



/**
* Overlays an image with bounding boxes.
*
* @param[in] image The input image.
* @param[in] boundingBoxes The rectangular regions used for the overlay.
* @param[out] response requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int ImageOutputPin::overlay(const cv::Mat& image, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes, ConnectedVisionResponse &response)
{
	cv::Mat tempImage;

	if(this->thumbnailMode)
	{
		tempImage = this->createThumbnail(image);
	}
	else
	{
		tempImage = image.clone();
	}

	cv::Mat dstImage;

	if(boundingBoxes.empty())
	{
		dstImage = tempImage;
	}
	else
	{
		Class_ThumbnailGenerator_params params;
		params.parseJson(this->config.get_params());
		cv::Scalar color(params.get_lineColor()->get_R(), params.get_lineColor()->get_G(), params.get_lineColor()->get_B());

		int lineWidth = params.get_lineWidth();

		// avoid cloning for the simple case of less than 2 bounding boxes
		if(boundingBoxes.size() < 2)
		{
			cv::Rect rectangle = this->convert(boundingBoxes.at(0)->get_boundingBox(), tempImage);
			dstImage = this->overlay(tempImage, rectangle, color, lineWidth);
		}
		else
		{
			vector<cv::Mat> images(2);

			images[0] = image.clone();

			for(int i = 0; i < boundingBoxes.size(); i++)
			{
				cv::Rect rectangle = this->convert(boundingBoxes.at(i)->get_boundingBox(), image);

				int iSrc = i % 2;
				int iDst = (i + 1) % 2;
				images[iDst] = this->overlay(images[iSrc], rectangle, color, lineWidth);
			}

			int iSrc = boundingBoxes.size() % 2;
			dstImage = images[iSrc].clone();
		}
	}

	return this->encode(dstImage, response);
}



///**
//* Overlays an image with polylines.
//*
//* @param[in] image The input image.
//* @param[in] polylines The polylines used for the overlay.
//* @param[out] response requested data or error response
//*
//* @return status code (analog to HTTP codes)
//*/
//int ImageOutputPin::overlay(const cv::Mat& image, const std::vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines, ConnectedVisionResponse &response)
//{
//	cv::Mat tempImage;
//
//	if(this->thumbnailMode)
//	{
//		tempImage = this->createThumbnail(image);
//	}
//	else
//	{
//		tempImage = image.clone();
//	}
//
//	cv::Mat dstImage;
//
//	Class_ThumbnailGenerator_params params;
//	params.parseJson(this->config.get_params());
//	cv::Scalar color(params.get_lineColor()->get_R(), params.get_lineColor()->get_G(), params.get_lineColor()->get_B());
//
//	int lineWidth = params.get_lineWidth();
//
//	// avoid cloning the image for the simple case of less than 2 polylines
//	if(polylines.size() < 2)
//	{
//		vector<cv::Point> points = this->convert(polylines.at(0), tempImage);
//		dstImage = this->overlay(tempImage, points, color, lineWidth);
//	}
//	// in case of two or more polylines, alternate the role of the two image buffers so that one acts as source while the other is the destination
//	else
//	{
//		vector<cv::Mat> images(2);
//
//		images[0] = image.clone();
//
//		for(int i = 0; i < polylines.size(); i++)
//		{
//			vector<cv::Point> points = this->convert(polylines.at(i), image);
//
//			int iSrc = i % 2;
//			int iDst = (i + 1) % 2;
//			images[iDst] = this->overlay(images[iSrc], points, color, lineWidth);
//		}
//
//		int iSrc = polylines.size() % 2;
//		dstImage = images[iSrc].clone();
//	}
//
//	return this->encode(dstImage, response);
//}



/**
 * get data from module by ID
 *
 * @param[in] id			ID of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getByID(const id_t id, ConnectedVisionResponse &response)
{
	// <todo> remove after framework bug has been fixed
	int maxAttempts = 5;

	try
	{
		// PNG image input pin
		boost::shared_ptr<InputPin_PNG> pngInputPin = boost::dynamic_pointer_cast<InputPin_PNG>(this->module->getInputPin(this->config, InputPin_PNG::PinID()));
		boost::shared_ptr<string> imageData;

		// bounding box overlay: id refers to image ID
		if(this->modificationType == ImageOutputPin::ModificationType::BoundingBoxOverlay)
		{
			// image metadata input pin
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata> imageMetadataInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_ImageMetadata>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_ImageMetadata::PinID()));

			// bounding box input pin
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox> boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));

			// request image
			imageData.reset(new std::string(pngInputPin->getByID(id)->getconst()));

			// request image metadata timestamp
			timestamp_t timestamp = imageMetadataInputPin->getByID(id)->get_timestamp();

			// request bounding boxes
			// <todo> remove after framework bug has been fixed
			// boundingBoxInputPin->getByTimestamp(...) takes more than 1 second even in release mode for returning a single result out of ~1000 DB rows
			// sometimes it even fails -> retry querying the object at max maxAttempts times
			//vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes = boundingBoxInputPin->getByTimestamp(timestamp);
			vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes = requeryByTimestamp<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox>>(boundingBoxInputPin, timestamp, maxAttempts);

			return this->modify(imageData, boundingBoxes, response);
		}
		// cropping: id refers to bounding box ID
		else if(this->modificationType == ImageOutputPin::ModificationType::Cropping)
		{
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox> boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));

			// request bounding box
			vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes;
			boundingBoxes.push_back(boundingBoxInputPin->getByID(id));

			// request image
			imageData.reset(new std::string(pngInputPin->getByTimestamp(boundingBoxes.front()->get_timestamp()).at(0)->getconst()));

			return this->modify(imageData, boundingBoxes, response);
		}
		//// polyline overlay: id refers to image ID
		//else if(this->modificationType == ImageOutputPin::ModificationType::PolylineOverlay)
		//{
		//	// image metadata input pin
		//	boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata> imageMetadataInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_ImageMetadata>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_ImageMetadata::PinID()));

		//	//// bounding box input pin
		//	//boost::shared_ptr<InputPin_ThumbnailGenerator_input_Polyline> polylineInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_Polyline>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_Polyline::PinID()));

		//	// request image
		//	imageData = pngInputPin->getByID(id);

		//	// request image metadata
		//	timestamp_t timestamp = imageMetadataInputPin->getByID(id)->get_timestamp();

		//	// request polylines
		//	//vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines = polylineInputPin->getByTimestamp(timestamp);
		//	vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines;

		//	return this->modify(imageData, polylines, response);
		//}
		else
		{
			return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByID() unsupported value for modification type: " + intToStr(this->modificationType));
		}
	}
	catch (std::runtime_error& e)
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByID() error: " + string(e.what()));
	}
}



/**
 * get data from module by index
 *
 * @param[in] index			index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	//cpu_timer timer;

	try 
	{
		// <todo> remove after framework bug has been fixed
		int maxAttempts = 5;

		// boundig box overlay: index refers to image index
		if(this->modificationType == ImageOutputPin::ModificationType::BoundingBoxOverlay)
		{
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata> imageMetadataInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_ImageMetadata>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_ImageMetadata::PinID()));

			// request image metadata
			// <todo> remove after framework bug has been fixed
			// imageMetadataInputPin->getByIndex(...) sometimes fails (returns null pointer)
			// therefore try requerying the object up to maxAttempts times
			boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata> imageMetadata = requeryByIndex<boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata>>(imageMetadataInputPin, index, maxAttempts);
			//boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata> imageMetadata = imageMetadataInputPin->getByIndex(index);

			if(!imageMetadata)
			{
				return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByIndex() image metadata object null for index " + boost::lexical_cast<string>(index));
			}
			
			return this->getByID(imageMetadata->get_id(), response);
		}
		// cropping: index refers to bounding box index
		else if(this->modificationType == ImageOutputPin::ModificationType::Cropping)
		{
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox> boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));

			// request bounding box
			// <todo> remove after framework bug has been fixed
			// boundingBoxInputPin->getByIndex(...) takes more than 1 second even in release mode for returning a single result out of ~1000 DB rows
			// sometimes it even fails -> retry querying the object at max maxAttempts times
			boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox> boundingBox = requeryByIndex<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox>>(boundingBoxInputPin, index, maxAttempts);
			//boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox> boundingBox = boundingBoxInputPin->getByIndex(index);

			if(!boundingBox)
			{
				return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByIndex() bounding box object null for index " + boost::lexical_cast<string>(index));
			}

			return this->getByID(boundingBox->get_id(), response);
		}
		//// polyline overlay: index refers to image index
		//else if(this->modificationType == ImageOutputPin::ModificationType::PolylineOverlay)
		//{
		//	boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata> imageMetadataInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_ImageMetadata>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_ImageMetadata::PinID()));
		//	//boost::shared_ptr<InputPin_ThumbnailGenerator_input_Polyline> polylineInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_Polyline>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_Polyline::PinID()));

		//	// request image
		//	imageData = pngInputPin->getByIndex(index);

		//	// request image metadata
		//	timestamp_t timestamp = imageMetadataInputPin->getByIndex(index)->get_timestamp();

		//	// request polylines
		//	//vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines = polylineInputPin->getByTimestamp(timestamp);

		//	// <todo> use real polyline input data when dynamic input pins have been implemented in framework
		//	boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline> polyline(new Class_ThumbnailGenerator_input_Polyline());

		//	int n = 10;

		//	vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline_coordinates>> coordinates;

		//	LARGE_INTEGER cicles;
		//	QueryPerformanceCounter(&cicles);
		//	srand(cicles.QuadPart);

		//	for(int i = 0; i < n; i++)
		//	{
		//		boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline_coordinates> coordinate(new Class_ThumbnailGenerator_input_Polyline_coordinates());

		//		//double x = (double)(i + 1) / (double)n;
		//		#undef max
		//		double x = (double)(rand() % 1000) / 1000.0;
		//		coordinate->set_x(x);
		//		
		//		//double y = x * x;
		//		double y = (double)(rand() % 1000) / 1000.0;
		//		coordinate->set_y(y);

		//		//cout << x << " " << y << endl;

		//		coordinates.push_back(coordinate);
		//	}

		//	polyline->set_coordinates(coordinates);

		//	vector<boost::shared_ptr<Class_ThumbnailGenerator_input_Polyline>> polylines;
		//	polylines.push_back(polyline);

		//	return this->modify(imageData, polylines, response);
		//}
		else
		{
			return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByIndex() unsupported value for modification type: " + intToStr(this->modificationType));
		}
	}
	catch(std::runtime_error& e)
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByIndex() error: " + string(e.what()));
	}
}



/**
 * get data from module by index range
 *
 * @param[in] start			first index of requested data
 * @param[in] end			last index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByIndexRange() is not implemented");
}



/**
 * get data from module by timestamp
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// <todo> remove after framework bug has been fixed
		int maxAttempts = 5;

		// boundig box overlay: timestamp refers to image timestamp
		if(this->modificationType == ImageOutputPin::ModificationType::BoundingBoxOverlay)
		{
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata> imageMetadataInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_ImageMetadata>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_ImageMetadata::PinID()));

			// request image metadata
			// <todo> remove after framework bug has been fixed
			// imageMetadataInputPin->getByTimestamp(...) sometimes fails (returns null pointer)
			// therefore try requerying the object up to maxAttempts times
			vector<boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata>> imageMetadata = requeryByTimestamp<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata>>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata>>(imageMetadataInputPin, timestamp, maxAttempts);
			//vector<boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata>> imageMetadata = imageMetadataInputPin->getByTimestamp(timestamp);

			if(imageMetadata.empty())
			{
				return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByTimestamp() image metadata object null for timestamp " + boost::lexical_cast<string>(timestamp));
			}
			
			return this->getByID(imageMetadata[0]->get_id(), response);
		}
		else if(this->modificationType == ImageOutputPin::ModificationType::Cropping)
		{
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox> boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));

			// request bounding boxes
			// <todo> remove after framework bug has been fixed
			// boundingBoxInputPin->getByTimestamp(...) takes more than 1 second even in release mode for returning a single result out of ~1000 DB rows
			// sometimes it even fails -> retry querying the object at max maxAttempts times
			vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes = requeryByTimestamp<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox>>(boundingBoxInputPin, timestamp, maxAttempts);
			//vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes = boundingBoxInputPin->getByTimestamp(timestamp);

			if(boundingBoxes.empty())
			{
				return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByTimestamp() bounding box object null for timestamp " + boost::lexical_cast<string>(timestamp));
			}

			return this->getByID(boundingBoxes[0]->get_id(), response);
		}
		else
		{
			return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByTimestamp() unsupported value for modification type: " + intToStr(this->modificationType));
		}
	}
	catch(std::runtime_error& e)
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getByTimestamp() error: " + string(e.what()));
	}
}



/**
 * get data from module by timestamp before
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		// <todo> remove after framework bug has been fixed
		int maxAttempts = 5;

		// boundig box overlay: timestamp refers to image timestamp
		if(this->modificationType == ImageOutputPin::ModificationType::BoundingBoxOverlay)
		{
			auto imageMetadataInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_ImageMetadata>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_ImageMetadata::PinID()));
			auto boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));

			// request bounding boxes
			// <todo> remove after framework bug has been fixed
			// boundingBoxInputPin->getBeforeTimestamp(...) takes more than 1 second even in release mode for returning a single result out of ~1000 DB rows
			// sometimes it even fails -> retry querying the object at max maxAttempts times
			auto imageMetadata = requeryBeforeTimestamp<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata>>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata>>(imageMetadataInputPin, timestamp, maxAttempts);

			if(imageMetadata.empty())
			{
				return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getBeforeTimestamp() image metadata object null before timestamp " + boost::lexical_cast<string>(timestamp));
			}

			auto stableResults = boundingBoxInputPin->getStableResults();
			timestamp_t boxEndTime = stableResults.get_timestampEnd();

			// There may already be a new image at the image input pin but it may not have been processed yet by the module providing the bounding box data.
			// Therefore use the image whose timestamp is equal to or smaller than the bounding box stable results end timestamp.
			// There may not exist a bounding box for the stable results end timestamp since the end timestamp only represents the latest processed image. This image may have resulted in zero bounding boxes.
			if(boxEndTime < imageMetadata[0]->get_timestamp())
			{
				timestamp_t ts = boxEndTime + 1;
				imageMetadata = requeryBeforeTimestamp<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_ImageMetadata>>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_ImageMetadata>>(imageMetadataInputPin, ts, maxAttempts);

				if(imageMetadata.empty())
				{
					return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getBeforeTimestamp() image metadata object null before timestamp " + boost::lexical_cast<string>(ts));
				}
			}

			return this->getByID(imageMetadata[0]->get_id(), response);
		}
		else if(this->modificationType == ImageOutputPin::ModificationType::Cropping)
		{
			boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox> boundingBoxInputPin = boost::dynamic_pointer_cast<InputPin_ThumbnailGenerator_input_BoundingBox>(this->module->getInputPin(this->config, InputPin_ThumbnailGenerator_input_BoundingBox::PinID()));

			// request bounding boxes
			// <todo> remove after framework bug has been fixed
			// boundingBoxInputPin->getBeforeTimestamp(...) takes more than 1 second even in release mode for returning a single result out of ~1000 DB rows
			// sometimes it even fails -> retry querying the object at max maxAttempts times
			vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes = requeryBeforeTimestamp<vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>>, boost::shared_ptr<InputPin_ThumbnailGenerator_input_BoundingBox>>(boundingBoxInputPin, timestamp, maxAttempts);
			//vector<boost::shared_ptr<Class_ThumbnailGenerator_input_BoundingBox>> boundingBoxes = boundingBoxInputPin->getBeforeTimestamp(timestamp);

			if(boundingBoxes.empty())
			{
				return writeError(response, HTTP_Status_NOT_FOUND, this->module->getModuleID(), ImageOutputPin::PinID() + "::getBeforeTimestamp() bounding box object null for timestamp " + boost::lexical_cast<string>(timestamp));
			}

			return this->getByID(boundingBoxes[0]->get_id(), response);
		}
		else
		{
			return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getBeforeTimestamp() unsupported value for modification type: " + intToStr(this->modificationType));
		}
	}
	catch(std::runtime_error& e)
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getBeforeTimestamp() error: " + string(e.what()));
	}
}



/**
 * get data from module by timestamp after
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try 
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getAfterTimestamp() is not implemented");
	}
	catch (std::runtime_error& e)
	{
		return writeError(response, HTTP_Status_ERROR, this->module->getModuleID(), ImageOutputPin::PinID() + "::getAfterTimestamp() error: " + string(e.what()));
	}
}



/**
 * get data from module by time span
 *
 * @param[in] start			first timestamp of requested data
 * @param[in] end			last timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int ImageOutputPin::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{
	// Decrement start time to make sure to get an image for the exact start time if existing.
	// getAfterTimestamp() returns the image AFTER the given time.
	return getAfterTimestamp(start - 1, response);
}

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // ImageOutputPin_def