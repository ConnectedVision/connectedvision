/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription.h
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
#include "../Class_ModuleDescription_moduleFeatures.h"
#include "../Class_ModuleDescription_configFeatures.h"
#include "../Class_ModuleDescription_params.h"

#ifndef Stub_ModuleDescription_def
#define Stub_ModuleDescription_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_ModuleDescription
 * 
 * module: 
 * description: Module Description Schema
 */
class Stub_ModuleDescription {

public:
	Stub_ModuleDescription();
	Stub_ModuleDescription(const Stub_ModuleDescription& other);
	Stub_ModuleDescription(const rapidjson::Value& value);
	Stub_ModuleDescription(const std::string& str);
	virtual ~Stub_ModuleDescription();
	Stub_ModuleDescription &operator =(const Stub_ModuleDescription& other);
	Stub_ModuleDescription &operator =(Stub_ModuleDescription&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* name - module name */
	virtual boost::shared_ptr<std::string> get_name() const;
	virtual const boost::shared_ptr<const std::string> getconst_name() const;
	virtual void set_name(boost::shared_ptr<std::string> value);
	virtual void set_name(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_name(ptr); };

	/* description - long description of module */
	virtual boost::shared_ptr<std::string> get_description() const;
	virtual const boost::shared_ptr<const std::string> getconst_description() const;
	virtual void set_description(boost::shared_ptr<std::string> value);
	virtual void set_description(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_description(ptr); };

	/* version - version of module */
	virtual double get_version() const;
	virtual const double getconst_version() const;
	virtual void set_version(double value);

	/* moduleID - unique ID of module */
	virtual boost::shared_ptr<std::string> get_moduleID() const;
	virtual const boost::shared_ptr<const std::string> getconst_moduleID() const;
	virtual void set_moduleID(boost::shared_ptr<std::string> value);
	virtual void set_moduleID(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_moduleID(ptr); };

	/* moduleURI - URL of module instance. Will be updated by the module server. */
	virtual boost::shared_ptr<std::string> get_moduleURI() const;
	virtual const boost::shared_ptr<const std::string> getconst_moduleURI() const;
	virtual void set_moduleURI(boost::shared_ptr<std::string> value);
	virtual void set_moduleURI(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_moduleURI(ptr); };

	/* APIVersion - version of supported Connected Vision version */
	virtual double get_APIVersion() const;
	virtual const double getconst_APIVersion() const;
	virtual void set_APIVersion(double value);

	/* moduleFeatures - JSON schema of module features */
	virtual boost::shared_ptr<Class_ModuleDescription_moduleFeatures> get_moduleFeatures() const;
	virtual const boost::shared_ptr<const Class_ModuleDescription_moduleFeatures> getconst_moduleFeatures() const;
	virtual void set_moduleFeatures(boost::shared_ptr<Class_ModuleDescription_moduleFeatures> value);
	virtual void set_moduleFeatures(const Class_ModuleDescription_moduleFeatures &value) { boost::shared_ptr<Class_ModuleDescription_moduleFeatures> ptr = boost::make_shared<Class_ModuleDescription_moduleFeatures>(value); set_moduleFeatures(ptr); };
	virtual void set_moduleFeatures(const rapidjson::Value& value) { moduleFeatures->parseJson( value ); };

	/* configFeatures - JSON schema of features of the config */
	virtual boost::shared_ptr<Class_ModuleDescription_configFeatures> get_configFeatures() const;
	virtual const boost::shared_ptr<const Class_ModuleDescription_configFeatures> getconst_configFeatures() const;
	virtual void set_configFeatures(boost::shared_ptr<Class_ModuleDescription_configFeatures> value);
	virtual void set_configFeatures(const Class_ModuleDescription_configFeatures &value) { boost::shared_ptr<Class_ModuleDescription_configFeatures> ptr = boost::make_shared<Class_ModuleDescription_configFeatures>(value); set_configFeatures(ptr); };
	virtual void set_configFeatures(const rapidjson::Value& value) { configFeatures->parseJson( value ); };

	/* author - author names of email address */
	virtual boost::shared_ptr<std::string> get_author() const;
	virtual const boost::shared_ptr<const std::string> getconst_author() const;
	virtual void set_author(boost::shared_ptr<std::string> value);
	virtual void set_author(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_author(ptr); };

	/* params - JSON schema of parameters */
	virtual boost::shared_ptr<Class_ModuleDescription_params> get_params() const;
	virtual const boost::shared_ptr<const Class_ModuleDescription_params> getconst_params() const;
	virtual void set_params(boost::shared_ptr<Class_ModuleDescription_params> value);
	virtual void set_params(const Class_ModuleDescription_params &value) { boost::shared_ptr<Class_ModuleDescription_params> ptr = boost::make_shared<Class_ModuleDescription_params>(value); set_params(ptr); };
	virtual void set_params(const rapidjson::Value& value) { params->parseJson( value ); };

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

	/** module name */
	boost::shared_ptr<std::string> name;
	
	/** long description of module */
	boost::shared_ptr<std::string> description;
	
	/** version of module */
	double version;
	
	/** unique ID of module */
	boost::shared_ptr<std::string> moduleID;
	
	/** URL of module instance. Will be updated by the module server. */
	boost::shared_ptr<std::string> moduleURI;
	
	/** version of supported Connected Vision version */
	double APIVersion;
	
	/** JSON schema of module features */
	boost::shared_ptr<Class_ModuleDescription_moduleFeatures> moduleFeatures;
	
	/** JSON schema of features of the config */
	boost::shared_ptr<Class_ModuleDescription_configFeatures> configFeatures;
	
	/** author names of email address */
	boost::shared_ptr<std::string> author;
	
	/** JSON schema of parameters */
	boost::shared_ptr<Class_ModuleDescription_params> params;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
	/** virtual timestamp */
	ConnectedVision::timestamp_t timestamp;
	
};

} // namespace ConnectedVision

#endif // Stub_ModuleDescription_def