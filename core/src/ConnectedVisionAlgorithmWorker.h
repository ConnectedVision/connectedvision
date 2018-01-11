/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#error("TODO remove this file !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

#pragma once

#include <string>
#include <sqlite3.h>

#include <boost/shared_ptr.hpp>
//#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/thread.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/assign/list_of.hpp>

#include "IModuleEnvironment.h"
#include "Module/Module_BaseClass.h"
#include "ConnectedVisionAlgorithmDispatcher.h"

#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"

namespace ConnectedVision
{

#define timeout(x)	( boost::get_system_time()+ boost::posix_time::milliseconds( (x) ) )

#define MIN_WAIT_TIME	300		///< minimal time to wait until requery previous module [ms]
#define MAX_WAIT_TIME	3000	///< maximal time to wait until requery previous module [ms]
	

typedef boost::interprocess::scoped_lock<boost::timed_mutex> scoped_prepare_lock;

class ConnectedVisionAlgorithmWorker : public IConnectedVisionAlgorithmWorker, public Logging::ILogable
{
public:
	ConnectedVisionAlgorithmWorker(IModuleEnvironment *env, Module_BaseClass *module, boost::shared_ptr<const Class_generic_config> config);
    virtual ~ConnectedVisionAlgorithmWorker();

	virtual id_t getID();

	virtual void start();
	virtual void stop();
	virtual bool isRunning();

	virtual Module_BaseClass* getModule() { return module; }; 

	virtual boost::shared_ptr<Logging::ILogWriter> log() const;

protected:
	virtual void prepare();
	virtual void run() = 0;

	bool waitForInputs(const std::vector<boost::shared_ptr< IConnectedVisionInputPin >>& inputPins);

	static void sleep_ms(int ms);

	boost::shared_ptr<boost::thread> t;
	IModuleEnvironment *env;
	Module_BaseClass *module;
	boost::shared_ptr<Class_generic_config> config;

	volatile bool go;		///< Used to control thread instance. Set to false to stop / abort computation.
	boost::recursive_timed_mutex mutex;
};

} // namespace ConnectedVision