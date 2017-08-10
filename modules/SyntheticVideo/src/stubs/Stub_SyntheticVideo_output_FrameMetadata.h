// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_SyntheticVideo_output_FrameMetadata.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_SyntheticVideo_output_FrameMetadata_def
#define Stub_SyntheticVideo_output_FrameMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

/**
 * stub class for: Class_SyntheticVideo_output_FrameMetadata
 * 
 * module: SyntheticVideo
 * description: synthetic frame meta data
 */
class Stub_SyntheticVideo_output_FrameMetadata {

public:
	Stub_SyntheticVideo_output_FrameMetadata();
	Stub_SyntheticVideo_output_FrameMetadata(const Stub_SyntheticVideo_output_FrameMetadata& other);
	Stub_SyntheticVideo_output_FrameMetadata(const rapidjson::Value& value);
	Stub_SyntheticVideo_output_FrameMetadata(const std::string& str);
	virtual ~Stub_SyntheticVideo_output_FrameMetadata();
	Stub_SyntheticVideo_output_FrameMetadata &operator =(const Stub_SyntheticVideo_output_FrameMetadata& other);
	Stub_SyntheticVideo_output_FrameMetadata &operator =(Stub_SyntheticVideo_output_FrameMetadata&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - Object ID */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* configID - job / config ID */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - start time */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* framenumber - frame number */
	virtual int64_t get_framenumber() const;
	virtual const int64_t getconst_framenumber() const;
	virtual void set_framenumber(int64_t value);

	/* width - width of frame in pixels */
	virtual int64_t get_width() const;
	virtual const int64_t getconst_width() const;
	virtual void set_width(int64_t value);

	/* height - height of frame in pixels */
	virtual int64_t get_height() const;
	virtual const int64_t getconst_height() const;
	virtual void set_height(int64_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** Object ID */
	ConnectedVision::id_t id;
	
	/** job / config ID */
	ConnectedVision::id_t configID;
	
	/** start time */
	ConnectedVision::timestamp_t timestamp;
	
	/** frame number */
	int64_t framenumber;
	
	/** width of frame in pixels */
	int64_t width;
	
	/** height of frame in pixels */
	int64_t height;
	
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_SyntheticVideo_output_FrameMetadata_def