// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_DirectoryIterator_params.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_DirectoryIterator_params_def
#define Stub_DirectoryIterator_params_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
 * stub class for: Class_DirectoryIterator_params
 * 
 * module: Directory Iterator
 * description: 
 */
class Stub_DirectoryIterator_params {

public:
	Stub_DirectoryIterator_params();
	Stub_DirectoryIterator_params(const Stub_DirectoryIterator_params& other);
	Stub_DirectoryIterator_params(const rapidjson::Value& value);
	Stub_DirectoryIterator_params(const std::string& str);
	virtual ~Stub_DirectoryIterator_params();
	Stub_DirectoryIterator_params &operator =(const Stub_DirectoryIterator_params& other);
	Stub_DirectoryIterator_params &operator =(Stub_DirectoryIterator_params&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* rootDirectory - root directory */
	virtual boost::shared_ptr<std::string> get_rootDirectory() const;
	virtual const boost::shared_ptr<const std::string> getconst_rootDirectory() const;
	virtual void set_rootDirectory(boost::shared_ptr<std::string> value);
	virtual void set_rootDirectory(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_rootDirectory(ptr); };

	/* fileTypes - file types to process */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> get_fileTypes() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> getconst_fileTypes() const;
	virtual void set_fileTypes(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value);
	virtual void set_fileTypes(const std::vector<boost::shared_ptr<std::string>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>(value); set_fileTypes(ptr); };
	// array functions
	virtual boost::shared_ptr<std::string> get_fileTypes(int index) const;
	virtual const boost::shared_ptr<std::string>& getconst_fileTypes(int index) const;
	virtual void add_fileTypes(boost::shared_ptr<std::string> value);
	virtual void add_fileTypes(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); add_fileTypes(ptr); };

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

	/** root directory */
	boost::shared_ptr<std::string> rootDirectory;
	
	/** file types to process */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> fileTypes;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // Stub_DirectoryIterator_params_def