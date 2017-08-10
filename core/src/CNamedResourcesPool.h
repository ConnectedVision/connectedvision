/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef CNamedResourcesPool_def
#define CNamedResourcesPool_def

#include <IConnectedVisionModule.h>

#include <limits>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

#ifdef _WIN32
	//#include <BaseTsd.h>
	typedef signed int          INT32, *PINT32;
	typedef unsigned int        UINT32, *PUINT32;
	#define MAXUINT32   ((UINT32)~((UINT32)0))
	#define MAXINT32    ((INT32)(MAXUINT32 >> 1))
#endif

namespace ConnectedVision {

class CNamedResourcesPool_exception : public ConnectedVision::runtime_error
{
public:
	CNamedResourcesPool_exception( const std::string &str ) : ConnectedVision::runtime_error( str ) {}
};

template <typename T_resource>
class CNamedResourcesData
{
public:
	CNamedResourcesData( T_resource* const ptr ) : ptr( ptr ), ticksLastRequest( 0 ) {};
	CNamedResourcesData( boost::shared_ptr< T_resource > const ptr ) : ptr( ptr ), ticksLastRequest( 0 ) {};

public:
	boost::shared_ptr< T_resource > ptr;
	int ticksLastRequest;
};


template <typename T_key, typename T_resource>
class CNamedResourcesPool
{
public:
	#ifdef _WIN32
		const static uint32_t maxTickCount = (MAXINT32 - 1);
	#else
		const static uint32_t maxTickCount = (std::numeric_limits<uint32_t>::max() - 1);
	#endif

public:
	CNamedResourcesPool();
    virtual ~CNamedResourcesPool();

	virtual void clear();
	virtual void add( T_resource *resource, T_key key );
	virtual void add( boost::shared_ptr< T_resource > resource, T_key key );

	virtual boost::shared_ptr< T_resource > request();
	virtual boost::shared_ptr< T_resource > request( T_key key );

	virtual void remap( boost::shared_ptr< T_resource > ptr, T_key key );

	virtual void remove( boost::shared_ptr< T_resource > ptr );

protected:
	int tickcount;
	boost::timed_mutex mutex;

	virtual  boost::shared_ptr< T_resource > searchFree( typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator begin, typename std::multimap< T_key, CNamedResourcesData<T_resource> >::iterator end );
	virtual void resetTicks();

	typename std::multimap< T_key, CNamedResourcesData<T_resource> > resourceMap;

};

} // namespace ConnectedVision

// include source code: template inclusion model
#include "CNamedResourcesPool.cpp"

#endif // CNamedResourcesPool_def