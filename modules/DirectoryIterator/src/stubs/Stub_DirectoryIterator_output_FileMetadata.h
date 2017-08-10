// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DirectoryIterator_output_FileMetadata.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_DirectoryIterator_output_FileMetadata_def
#define Stub_DirectoryIterator_output_FileMetadata_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
 * stub class for: Class_DirectoryIterator_output_FileMetadata
 * 
 * module: Directory Iterator
 * description: The file metadata.
 */
class Stub_DirectoryIterator_output_FileMetadata {

public:
	Stub_DirectoryIterator_output_FileMetadata();
	Stub_DirectoryIterator_output_FileMetadata(const Stub_DirectoryIterator_output_FileMetadata& other);
	Stub_DirectoryIterator_output_FileMetadata(const rapidjson::Value& value);
	Stub_DirectoryIterator_output_FileMetadata(const std::string& str);
	virtual ~Stub_DirectoryIterator_output_FileMetadata();
	Stub_DirectoryIterator_output_FileMetadata &operator =(const Stub_DirectoryIterator_output_FileMetadata& other);
	Stub_DirectoryIterator_output_FileMetadata &operator =(Stub_DirectoryIterator_output_FileMetadata&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - file ID */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* configID - job / config ID */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* timestamp - timestamp */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* filePath - absolute file path */
	virtual boost::shared_ptr<std::string> get_filePath() const;
	virtual const boost::shared_ptr<const std::string> getconst_filePath() const;
	virtual void set_filePath(boost::shared_ptr<std::string> value);
	virtual void set_filePath(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_filePath(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** file ID */
	ConnectedVision::id_t id;
	
	/** job / config ID */
	ConnectedVision::id_t configID;
	
	/** timestamp */
	ConnectedVision::timestamp_t timestamp;
	
	/** absolute file path */
	boost::shared_ptr<std::string> filePath;
	
};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DirectoryIterator_output_FileMetadata_def