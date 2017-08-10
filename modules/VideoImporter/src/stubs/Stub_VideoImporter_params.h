// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_VideoImporter_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_VideoImporter_params_def
#define Stub_VideoImporter_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

/**
 * stub class for: Class_VideoImporter_params
 * 
 * module: VideoImporter
 * description: 
 */
class Stub_VideoImporter_params {

public:
	Stub_VideoImporter_params();
	Stub_VideoImporter_params(const Stub_VideoImporter_params& other);
	Stub_VideoImporter_params(const rapidjson::Value& value);
	Stub_VideoImporter_params(const std::string& str);
	virtual ~Stub_VideoImporter_params();
	Stub_VideoImporter_params &operator =(const Stub_VideoImporter_params& other);
	Stub_VideoImporter_params &operator =(Stub_VideoImporter_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* filename - network path to video file */
	virtual boost::shared_ptr<std::string> get_filename() const;
	virtual const boost::shared_ptr<const std::string> getconst_filename() const;
	virtual void set_filename(boost::shared_ptr<std::string> value);
	virtual void set_filename(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_filename(ptr); };

	/* deinterlaceMode - deinterlace mode (modes are: 'AUTO' ... deinterlaces dependent on the interlaced flag of the video source, 'FORCE' ... forces deinterlacing, 'OFF' ... disables deinterlacing */
	virtual boost::shared_ptr<std::string> get_deinterlaceMode() const;
	virtual const boost::shared_ptr<const std::string> getconst_deinterlaceMode() const;
	virtual void set_deinterlaceMode(boost::shared_ptr<std::string> value);
	virtual void set_deinterlaceMode(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_deinterlaceMode(ptr); };
	// enum functions
	virtual bool is_deinterlaceMode(const boost::shared_ptr<std::string>& value) const;
	const static boost::shared_ptr<std::string> deinterlaceMode_AUTO;
	virtual bool is_deinterlaceMode_AUTO() const { return is_deinterlaceMode( Stub_VideoImporter_params::deinterlaceMode_AUTO ); }
	virtual void set_deinterlaceMode_AUTO() { set_deinterlaceMode ( Stub_VideoImporter_params::deinterlaceMode_AUTO ); }
	const static boost::shared_ptr<std::string> deinterlaceMode_FORCE;
	virtual bool is_deinterlaceMode_FORCE() const { return is_deinterlaceMode( Stub_VideoImporter_params::deinterlaceMode_FORCE ); }
	virtual void set_deinterlaceMode_FORCE() { set_deinterlaceMode ( Stub_VideoImporter_params::deinterlaceMode_FORCE ); }
	const static boost::shared_ptr<std::string> deinterlaceMode_OFF;
	virtual bool is_deinterlaceMode_OFF() const { return is_deinterlaceMode( Stub_VideoImporter_params::deinterlaceMode_OFF ); }
	virtual void set_deinterlaceMode_OFF() { set_deinterlaceMode ( Stub_VideoImporter_params::deinterlaceMode_OFF ); }

	/* recordingDateTime - recording date (start time of video) */
	virtual ConnectedVision::timestamp_t get_recordingDateTime() const;
	virtual const ConnectedVision::timestamp_t getconst_recordingDateTime() const;
	virtual void set_recordingDateTime(ConnectedVision::timestamp_t value);

	/* timestampStart - stable results start time (only considred when Trigger input pin is connected) */
	virtual ConnectedVision::timestamp_t get_timestampStart() const;
	virtual const ConnectedVision::timestamp_t getconst_timestampStart() const;
	virtual void set_timestampStart(ConnectedVision::timestamp_t value);

	/* configID - virtual config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - virtual timestamp */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** network path to video file */
	boost::shared_ptr<std::string> filename;
	
	/** deinterlace mode (modes are: 'AUTO' ... deinterlaces dependent on the interlaced flag of the video source, 'FORCE' ... forces deinterlacing, 'OFF' ... disables deinterlacing */
	boost::shared_ptr<std::string> deinterlaceMode;
	
	/** recording date (start time of video) */
	ConnectedVision::timestamp_t recordingDateTime;
	
	/** stable results start time (only considred when Trigger input pin is connected) */
	ConnectedVision::timestamp_t timestampStart;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_VideoImporter_params_def