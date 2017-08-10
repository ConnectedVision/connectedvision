/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** ModuleSource_Memory_BaseClass.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef ModuleSource_Memory_BaseClass_def
#define ModuleSource_Memory_BaseClass_def

//#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <rapidjson/error/en.h>

#include "general.h"
#include <IModuleSource.h>
#include <IConnectedVisionModule.h>

namespace ConnectedVision
{

class ModuleSource_Memory_BaseClass : public IModuleSource
{

public:
	ModuleSource_Memory_BaseClass();
	virtual ~ModuleSource_Memory_BaseClass();

	/**
	 * initialize data source
	 *
	 * The data source has to be initialized for every (re-)connection to an output pin of another module.
	 *
	 * @param pEnv			pointer to module environment / Connected Vision Host
	 * @param moduleID		ID of connected (source) module - The module connected to the input pin of the current module.
	 * @param configID		configID of chain entry - The config corresponding to the source module.
	 */
	virtual void init(const IModuleEnvironment *pEnv, const id_t &moduleID, const id_t &configID);

	virtual boost::shared_ptr<Class_generic_status> getStatus();

	virtual boost::shared_ptr<Class_generic_config> getConfig();

protected:
	template <class T>
	boost::shared_ptr<T> responseToData(ConnectedVisionResponse &response);

	boost::shared_ptr<IConnectedVisionModule> pModule;
	id_t moduleID;
	id_t configID;
};

} // namespace ConnectedVision

#endif // ModuleSource_Memory_BaseClass_def


