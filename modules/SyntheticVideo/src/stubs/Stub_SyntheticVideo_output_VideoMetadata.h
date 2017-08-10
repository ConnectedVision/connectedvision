// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_SyntheticVideo_output_VideoMetadata.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_SyntheticVideo_output_VideoMetadata_def
#define Stub_SyntheticVideo_output_VideoMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

/**
 * stub class for: Class_SyntheticVideo_output_VideoMetadata
 * 
 * module: SyntheticVideo
 * description: synthetic video meta data
 */
class Stub_SyntheticVideo_output_VideoMetadata {

public:
	Stub_SyntheticVideo_output_VideoMetadata();
	Stub_SyntheticVideo_output_VideoMetadata(const Stub_SyntheticVideo_output_VideoMetadata& other);
	Stub_SyntheticVideo_output_VideoMetadata(const rapidjson::Value& value);
	Stub_SyntheticVideo_output_VideoMetadata(const std::string& str);
	virtual ~Stub_SyntheticVideo_output_VideoMetadata();
	Stub_SyntheticVideo_output_VideoMetadata &operator =(const Stub_SyntheticVideo_output_VideoMetadata& other);
	Stub_SyntheticVideo_output_VideoMetadata &operator =(Stub_SyntheticVideo_output_VideoMetadata&& other) noexcept;

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

	/* filename - filename */
	virtual boost::shared_ptr<std::string> get_filename() const;
	virtual const boost::shared_ptr<const std::string> getconst_filename() const;
	virtual void set_filename(boost::shared_ptr<std::string> value);
	virtual void set_filename(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_filename(ptr); };

	/* timestamp - start time */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* lasttimestamp - end time */
	virtual ConnectedVision::timestamp_t get_lasttimestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_lasttimestamp() const;
	virtual void set_lasttimestamp(ConnectedVision::timestamp_t value);

	/* width - width of video in pixels */
	virtual int64_t get_width() const;
	virtual const int64_t getconst_width() const;
	virtual void set_width(int64_t value);

	/* height - height of video in pixels */
	virtual int64_t get_height() const;
	virtual const int64_t getconst_height() const;
	virtual void set_height(int64_t value);

	/* numberofframes - number of frames in video */
	virtual int64_t get_numberofframes() const;
	virtual const int64_t getconst_numberofframes() const;
	virtual void set_numberofframes(int64_t value);

	/* fps - number of frames per second */
	virtual double get_fps() const;
	virtual const double getconst_fps() const;
	virtual void set_fps(double value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** Object ID */
	ConnectedVision::id_t id;
	
	/** job / config ID */
	ConnectedVision::id_t configID;
	
	/** filename */
	boost::shared_ptr<std::string> filename;
	
	/** start time */
	ConnectedVision::timestamp_t timestamp;
	
	/** end time */
	ConnectedVision::timestamp_t lasttimestamp;
	
	/** width of video in pixels */
	int64_t width;
	
	/** height of video in pixels */
	int64_t height;
	
	/** number of frames in video */
	int64_t numberofframes;
	
	/** number of frames per second */
	double fps;
	
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_SyntheticVideo_output_VideoMetadata_def