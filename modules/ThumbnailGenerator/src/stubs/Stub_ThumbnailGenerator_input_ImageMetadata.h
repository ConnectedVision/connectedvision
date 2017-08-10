// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ThumbnailGenerator_input_ImageMetadata.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ThumbnailGenerator_input_ImageMetadata_def
#define Stub_ThumbnailGenerator_input_ImageMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace ThumbnailGenerator {

/**
 * stub class for: Class_ThumbnailGenerator_input_ImageMetadata
 * 
 * module: Thumbnail Generator
 * description: image metadata
 */
class Stub_ThumbnailGenerator_input_ImageMetadata {

public:
	Stub_ThumbnailGenerator_input_ImageMetadata();
	Stub_ThumbnailGenerator_input_ImageMetadata(const Stub_ThumbnailGenerator_input_ImageMetadata& other);
	Stub_ThumbnailGenerator_input_ImageMetadata(const rapidjson::Value& value);
	Stub_ThumbnailGenerator_input_ImageMetadata(const std::string& str);
	virtual ~Stub_ThumbnailGenerator_input_ImageMetadata();
	Stub_ThumbnailGenerator_input_ImageMetadata &operator =(const Stub_ThumbnailGenerator_input_ImageMetadata& other);
	Stub_ThumbnailGenerator_input_ImageMetadata &operator =(Stub_ThumbnailGenerator_input_ImageMetadata&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - ID */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* configID - job / config ID */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** ID */
	ConnectedVision::id_t id;
	
	/** job / config ID */
	ConnectedVision::id_t configID;
	
	/** timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace ThumbnailGenerator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_ThumbnailGenerator_input_ImageMetadata_def