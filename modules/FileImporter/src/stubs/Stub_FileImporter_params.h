// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_FileImporter_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_FileImporter_params_def
#define Stub_FileImporter_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace FileImporter {

/**
 * stub class for: Class_FileImporter_params
 * 
 * module: FileImporter
 * description: 
 */
class Stub_FileImporter_params {

public:
	Stub_FileImporter_params();
	Stub_FileImporter_params(const Stub_FileImporter_params& other);
	Stub_FileImporter_params(const rapidjson::Value& value);
	Stub_FileImporter_params(const std::string& str);
	virtual ~Stub_FileImporter_params();
	Stub_FileImporter_params &operator =(const Stub_FileImporter_params& other);
	Stub_FileImporter_params &operator =(Stub_FileImporter_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* filename - network path to file */
	virtual boost::shared_ptr<std::string> get_filename() const;
	virtual const boost::shared_ptr<const std::string> getconst_filename() const;
	virtual void set_filename(boost::shared_ptr<std::string> value);
	virtual void set_filename(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_filename(ptr); };

	/* mimeType - mime type of file */
	virtual boost::shared_ptr<std::string> get_mimeType() const;
	virtual const boost::shared_ptr<const std::string> getconst_mimeType() const;
	virtual void set_mimeType(boost::shared_ptr<std::string> value);
	virtual void set_mimeType(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_mimeType(ptr); };

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

	/** network path to file */
	boost::shared_ptr<std::string> filename;
	
	/** mime type of file */
	boost::shared_ptr<std::string> mimeType;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_FileImporter_params_def