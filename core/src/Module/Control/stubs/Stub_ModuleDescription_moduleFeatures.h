/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_ModuleDescription_moduleFeatures.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_ModuleDescription_moduleFeatures_def
#define Stub_ModuleDescription_moduleFeatures_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_ModuleDescription_moduleFeatures
 * 
 * module: 
 * description: JSON schema of module features
 */
class Stub_ModuleDescription_moduleFeatures {

public:
	Stub_ModuleDescription_moduleFeatures();
	Stub_ModuleDescription_moduleFeatures(const Stub_ModuleDescription_moduleFeatures& other);
	Stub_ModuleDescription_moduleFeatures(const rapidjson::Value& value);
	Stub_ModuleDescription_moduleFeatures(const std::string& str);
	virtual ~Stub_ModuleDescription_moduleFeatures();
	Stub_ModuleDescription_moduleFeatures &operator =(const Stub_ModuleDescription_moduleFeatures& other);
	Stub_ModuleDescription_moduleFeatures &operator =(Stub_ModuleDescription_moduleFeatures&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* supportsLive - The module does support live configurations. */
	virtual bool get_supportsLive() const;
	virtual const bool getconst_supportsLive() const;
	virtual void set_supportsLive(bool value);

	/* supportsResume - The module does support resuming of stopped configurations. */
	virtual bool get_supportsResume() const;
	virtual const bool getconst_supportsResume() const;
	virtual void set_supportsResume(bool value);

	/* supportsDynamicParameters - The module does support dynamic parameters. */
	virtual bool get_supportsDynamicParameters() const;
	virtual const bool getconst_supportsDynamicParameters() const;
	virtual void set_supportsDynamicParameters(bool value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** The module does support live configurations. */
	bool supportsLive;
	
	/** The module does support resuming of stopped configurations. */
	bool supportsResume;
	
	/** The module does support dynamic parameters. */
	bool supportsDynamicParameters;
	
};

} // namespace ConnectedVision

#endif // Stub_ModuleDescription_moduleFeatures_def