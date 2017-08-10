/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVision_def
#define ConnectedVision_def

// time handling
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "ConnectedVision_SmartPointer.h"
#include "ConnectedVision_Exceptions.h"
#include "ConnectedVision_Thread.h"

namespace ConnectedVision
{

	static const boost::posix_time::ptime ptime_epoch( boost::gregorian::date(1970,1,1) ); 
	static inline int64_t sysTime()	
	{ return (boost::posix_time::microsec_clock::universal_time() - ptime_epoch).total_milliseconds(); }

} // namespace ConnectedVision

#endif // ConnectedVision_def
