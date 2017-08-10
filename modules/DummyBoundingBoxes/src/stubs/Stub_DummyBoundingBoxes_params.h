// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DummyBoundingBoxes_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


// include child classes
#include "../Class_DummyBoundingBoxes_params_boundingBoxStart.h"
#include "../Class_DummyBoundingBoxes_params_boundingBoxEnd.h"

#ifndef Stub_DummyBoundingBoxes_params_def
#define Stub_DummyBoundingBoxes_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {

/**
 * stub class for: Class_DummyBoundingBoxes_params
 * 
 * module: DummyBoundingBoxes
 * description: Dummy Bounding Box Generator configuration
 */
class Stub_DummyBoundingBoxes_params {

public:
	Stub_DummyBoundingBoxes_params();
	Stub_DummyBoundingBoxes_params(const Stub_DummyBoundingBoxes_params& other);
	Stub_DummyBoundingBoxes_params(const rapidjson::Value& value);
	Stub_DummyBoundingBoxes_params(const std::string& str);
	virtual ~Stub_DummyBoundingBoxes_params();
	Stub_DummyBoundingBoxes_params &operator =(const Stub_DummyBoundingBoxes_params& other);
	Stub_DummyBoundingBoxes_params &operator =(Stub_DummyBoundingBoxes_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* count - number of bounding boxes to be generated (interpolated) */
	virtual int64_t get_count() const;
	virtual const int64_t getconst_count() const;
	virtual void set_count(int64_t value);

	/* boundingBoxStart - first bounding box data at start of video */
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> get_boundingBoxStart() const;
	virtual const boost::shared_ptr<const Class_DummyBoundingBoxes_params_boundingBoxStart> getconst_boundingBoxStart() const;
	virtual void set_boundingBoxStart(boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> value);
	virtual void set_boundingBoxStart(const Class_DummyBoundingBoxes_params_boundingBoxStart &value) { boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> ptr = boost::make_shared<Class_DummyBoundingBoxes_params_boundingBoxStart>(value); set_boundingBoxStart(ptr); };
	virtual void set_boundingBoxStart(const rapidjson::Value& value) { boundingBoxStart->parseJson( value ); };

	/* timestampStart - timestamp of first bounding box data at start of video */
	virtual ConnectedVision::timestamp_t get_timestampStart() const;
	virtual const ConnectedVision::timestamp_t getconst_timestampStart() const;
	virtual void set_timestampStart(ConnectedVision::timestamp_t value);

	/* boundingBoxEnd - last bounding box data at end of video */
	virtual boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd> get_boundingBoxEnd() const;
	virtual const boost::shared_ptr<const Class_DummyBoundingBoxes_params_boundingBoxEnd> getconst_boundingBoxEnd() const;
	virtual void set_boundingBoxEnd(boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd> value);
	virtual void set_boundingBoxEnd(const Class_DummyBoundingBoxes_params_boundingBoxEnd &value) { boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd> ptr = boost::make_shared<Class_DummyBoundingBoxes_params_boundingBoxEnd>(value); set_boundingBoxEnd(ptr); };
	virtual void set_boundingBoxEnd(const rapidjson::Value& value) { boundingBoxEnd->parseJson( value ); };

	/* timestampEnd - timestamp of last bounding box data at end of video */
	virtual ConnectedVision::timestamp_t get_timestampEnd() const;
	virtual const ConnectedVision::timestamp_t getconst_timestampEnd() const;
	virtual void set_timestampEnd(ConnectedVision::timestamp_t value);

	/* delay - processing delay */
	virtual int64_t get_delay() const;
	virtual const int64_t getconst_delay() const;
	virtual void set_delay(int64_t value);

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

	/** number of bounding boxes to be generated (interpolated) */
	int64_t count;
	
	/** first bounding box data at start of video */
	boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxStart> boundingBoxStart;
	
	/** timestamp of first bounding box data at start of video */
	ConnectedVision::timestamp_t timestampStart;
	
	/** last bounding box data at end of video */
	boost::shared_ptr<Class_DummyBoundingBoxes_params_boundingBoxEnd> boundingBoxEnd;
	
	/** timestamp of last bounding box data at end of video */
	ConnectedVision::timestamp_t timestampEnd;
	
	/** processing delay */
	int64_t delay;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DummyBoundingBoxes_params_def