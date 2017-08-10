/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** ModuleSource_REST_BaseClass.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef ModuleSource_REST_BaseClass_def
#define ModuleSource_REST_BaseClass_def

#include <string>
#include <vector>

#include "general.h"
#include <IModuleSource.h>

namespace ConnectedVision
{

class ModuleSource_REST_BaseClass : public IModuleSource
{

public:
	ModuleSource_REST_BaseClass();
	virtual ~ModuleSource_REST_BaseClass();

	/**
	 * initialize data source
	 *
	 * The data source has to be initialized for every (re-)connection to an output pin of another module.
	 *
	 * @param moduleURI		URI of connected (source) module - The module connected to the input pin of the current module.
	 * @param configID		configID of chain entry - The config corresponding to the source module.
	 */
	virtual void init(const std::string &moduleURI, const id_t &configID);

	virtual boost::shared_ptr<Class_generic_status> getStatus();

	virtual boost::shared_ptr<Class_generic_config> getConfig();

protected:
	std::string moduleURI;
	id_t configID;
};

} // namespace ConnectedVision

#endif // ModuleSource_REST_BaseClass_def


