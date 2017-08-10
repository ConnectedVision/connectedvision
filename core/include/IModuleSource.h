/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** IModuleSource.h
**
** written by Michael Rauter and Stephan Veigl
** 
*******************************************************/

#ifndef IModuleSource_def
#define IModuleSource_def

#include <boost/shared_ptr.hpp>

#include "general.h"

#include <Module/Control/Class_generic_status.h>
#include <Module/Control/Class_generic_config.h>

namespace ConnectedVision
{

/**
 * module source interface (module source is a abstraction layer class to provide memory shortcut mechanism for module specific information)
 */
class IModuleSource
{
public:
	virtual boost::shared_ptr<Class_generic_status> getStatus() = 0;

	virtual boost::shared_ptr<Class_generic_config> getConfig() = 0;
};

} // namespace ConnectedVision

#endif // IModuleSource_def