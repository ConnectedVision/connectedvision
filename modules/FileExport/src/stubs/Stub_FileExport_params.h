// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_FileExport_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_FileExport_params_def
#define Stub_FileExport_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace FileExport {

/**
 * stub class for: Class_FileExport_params
 * 
 * module: FileExport
 * description: 
 */
class Stub_FileExport_params {

public:
	Stub_FileExport_params();
	Stub_FileExport_params(const Stub_FileExport_params& other);
	Stub_FileExport_params(const rapidjson::Value& value);
	Stub_FileExport_params(const std::string& str);
	virtual ~Stub_FileExport_params();
	Stub_FileExport_params &operator =(const Stub_FileExport_params& other);
	Stub_FileExport_params &operator =(Stub_FileExport_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* filepath_format - specification of filepath (path + filename) of target output file, there are several reserved character sequences defined to allow folders and filenames to change over time and have identifiers in them, these special reserved character sequences are:[timestamp],[index],[identifier],etc. */
	virtual boost::shared_ptr<std::string> get_filepath_format() const;
	virtual const boost::shared_ptr<const std::string> getconst_filepath_format() const;
	virtual void set_filepath_format(boost::shared_ptr<std::string> value);
	virtual void set_filepath_format(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_filepath_format(ptr); };

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

	/** specification of filepath (path + filename) of target output file, there are several reserved character sequences defined to allow folders and filenames to change over time and have identifiers in them, these special reserved character sequences are:[timestamp],[index],[identifier],etc. */
	boost::shared_ptr<std::string> filepath_format;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_FileExport_params_def