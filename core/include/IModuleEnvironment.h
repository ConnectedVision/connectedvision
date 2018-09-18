/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef IModuleEnvironment_def
#define IModuleEnvironment_def

#include <boost/shared_ptr.hpp>

#include "Module/Control/Class_HostStatus.h"
#include "Module/Module_BaseClass.h"
#include "ILogging.h"

namespace ConnectedVision
{
class IModuleEnvironment : public Logging::ILogable {
public:
	IModuleEnvironment() : _log(new Logging::LogWriterNULL()) {}
	virtual ~IModuleEnvironment() {}

	////////////////////////////////////////////////////////////
	// module functions

	/**
	* register module
	*/
	virtual void registerModule( 
		boost::shared_ptr<Module::IModule> module ///< module instance
	) = 0;

	/**
	* get module by module ID
	*
	* @return module instance
	*/
	virtual boost::shared_ptr<Module::IModule> getModule(
		std::string moduleID	///< module ID
	) const = 0;


	/**
	* get module by module ID
	*
	* @return current module URL
	*/
	virtual std::string getModuleURL(
		std::string serverAddress,	///< server base URL including protocol and port, e.g.: "http://example.com:2020" (optional as "")
		std::string moduleID		///< module ID
	) const = 0;


	////////////////////////////////////////////////////////////
	// server functions

	/**
	* get root data path
	*
	* @return path to server root data
	*/
	virtual std::string getDataPath() const = 0;

	/**
	* get server status
	*
	* @return status
	*/
	virtual Class_HostStatus getHostStatus() = 0;

	////////////////////////////////////////////////////////////
	// logging functions

	/**
	* get log instance
	*
	* @return log writer
	*/
	inline boost::shared_ptr<Logging::ILogWriter> log() const 
	{ return _log; };

	/**
	* set log instance
	*/
	void setLogWriter(
		boost::shared_ptr<Logging::ILogWriter> log	///< log writer
	) { if ( log ) this->_log = log; };

private:
	/// log writer
	boost::shared_ptr<Logging::ILogWriter> _log;

};

} // namespace ConnectedVision

#endif // IModuleEnvironment_def