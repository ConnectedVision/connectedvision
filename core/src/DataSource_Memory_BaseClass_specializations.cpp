/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DataSource_Memory_BaseClass_specializations_impl
#define DataSource_Memory_BaseClass_specializations_impl

#include "DataSource_Memory_BaseClass.h"

#include <IConnectedVisionModule.h>
#include <IModuleEnvironment.h>
#include <IHTTPAbstraction.h>

#include <exception>

namespace ConnectedVision {

/**
 * map response data to data objects (Class_RawData specialization)
 *
 * @param response response as ConnectedVisionResponse
 *
 * @return vector of data objects
 */
template<> std::vector< boost::shared_ptr<Class_RawData> > DataSource_Memory_BaseClass<Class_RawData>::responseToData(ConnectedVisionResponse &response)
{
	std::vector< boost::shared_ptr<Class_RawData> > objs;

	boost::shared_ptr<Class_RawData> obj( new Class_RawData );
	obj->set( response.getContentConst() );
	objs.push_back( obj );	

	return objs;
}

} // namespace ConnectedVision

#endif // DataSource_Memory_BaseClass_specializations_impl