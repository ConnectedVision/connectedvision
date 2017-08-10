// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_FileExport_output_FileExportTrigger.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_FileExport_output_FileExportTrigger_def
#define Stub_FileExport_output_FileExportTrigger_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace FileExport {

/**
 * stub class for: Class_FileExport_output_FileExportTrigger
 * 
 * module: FileExport
 * description: output pin used as trigger for file export of data elements available at the input pin with matching timestamp or id
 */
class Stub_FileExport_output_FileExportTrigger {

public:
	Stub_FileExport_output_FileExportTrigger();
	Stub_FileExport_output_FileExportTrigger(const Stub_FileExport_output_FileExportTrigger& other);
	Stub_FileExport_output_FileExportTrigger(const rapidjson::Value& value);
	Stub_FileExport_output_FileExportTrigger(const std::string& str);
	virtual ~Stub_FileExport_output_FileExportTrigger();
	Stub_FileExport_output_FileExportTrigger &operator =(const Stub_FileExport_output_FileExportTrigger& other);
	Stub_FileExport_output_FileExportTrigger &operator =(Stub_FileExport_output_FileExportTrigger&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* timestamp - timestamp of data element triggered for file export */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* configID - virtual config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** timestamp of data element triggered for file export */
	ConnectedVision::timestamp_t timestamp;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
};

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_FileExport_output_FileExportTrigger_def