/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_RTPImporter_output_FrameMetadata.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef Class_RTPImporter_output_FrameMetadata_def
#define Class_RTPImporter_output_FrameMetadata_def

#include "stubs/Stub_RTPImporter_output_FrameMetadata.h"

#include <opencv2/opencv.hpp>


namespace ConnectedVision { 
namespace Module { 
namespace RTPImporter { 


// if you want to extend the auto-generated class, enable the line below
#define Class_RTPImporter_output_FrameMetadata_extended

#ifdef Class_RTPImporter_output_FrameMetadata_extended
/**
 * Class_RTPImporter_output_FrameMetadata
 * 
 * module: RTP stream receiver module
 * description: frame meta data
 */
class Class_RTPImporter_output_FrameMetadata : public Stub_RTPImporter_output_FrameMetadata {

public:
	Class_RTPImporter_output_FrameMetadata() {};
	Class_RTPImporter_output_FrameMetadata(const ::rapidjson::Value& value) : Stub_RTPImporter_output_FrameMetadata(value) {};
	Class_RTPImporter_output_FrameMetadata(const std::string& str) : Stub_RTPImporter_output_FrameMetadata(str) {};
	virtual ~Class_RTPImporter_output_FrameMetadata() {};

	static std::string selectPNGImage(const Class_RTPImporter_output_FrameMetadata &obj)
	{
		return obj.getPNGImage();
	}

	virtual std::string getPNGImage() const
	{
		std::vector<unsigned char> buffer;
		// encode image according to extension and return as char array
		cv::imencode(".png", this->image, buffer);
		std::string png (reinterpret_cast<char*>(buffer.data()), buffer.size());
		return png;
	}

	cv::Mat image;	///< image

};
typedef boost::shared_ptr<Class_RTPImporter_output_FrameMetadata> Class_RTPImporter_output_FrameMetadata_p;
#endif // Class_RTPImporter_output_FrameMetadata_extended

} // namespace RTPImporter 
} // namespace Module 
} // namespace ConnectedVision 

#include "stubs/Class_RTPImporter_output_FrameMetadata_Default.h"

#endif // Class_RTPImporter_output_FrameMetadata_def