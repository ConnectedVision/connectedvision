/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#error("TODO remove this file !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/thread/mutex.hpp>
#include <boost/thread/shared_mutex.hpp>

#include <time.h>

#include <rapidjson/document.h>

#include "ConnectedVisionAlgorithmDispatcher.h"
#include "Module/Module_BaseClass.h"

#include "Module/Control/Store_SQLite_generic_status.h"

namespace ConnectedVision {

using namespace std;

ConnectedVisionAlgorithmDispatcher::ConnectedVisionAlgorithmDispatcher(IModuleEnvironment *env, IConnectedVisionWorkerFactory *workerFactory, ConnectedVision::Module::IModule* module)
{
	this->env = env;
	this->workerFactory = workerFactory;
	this->module = module;
}

ConnectedVisionAlgorithmDispatcher::~ConnectedVisionAlgorithmDispatcher()
{
	// remove all worker threads
	boost::shared_ptr<IConnectedVisionAlgorithmWorker> worker;

	boost::unique_lock<boost::shared_mutex> uniqueWriteLock(mutexWorkerList); // unique lock (write lock)

	/*
	for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = this->workers.begin(); it!=this->workers.end(); ++it) 
	{
		worker = *it;
		worker->initiateStop();
	}
	*/

	for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = this->queue.begin(); it!=this->queue.end(); ++it) 
	{
		worker = *it;
		try
		{
			worker->stop();
		}
		catch (...)
		{
			// die silently
		}
	}
	for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = this->workers.begin(); it!=this->workers.end(); ++it) 
	{
		worker = *it;
		try
		{
			worker->stop();
		}
		catch (...)
		{
			// die silently
		}
	}

	uniqueWriteLock.unlock(); // release write lock
}


/**
 * start a specific config / job
 *
 * @param config config chain of job
 */
void ConnectedVisionAlgorithmDispatcher::start( boost::shared_ptr<const Class_generic_config> config )
{
	// search running threads
	id_t configID = config->get_id();
	
	// mutexCriticalSectionWorkerCreation prevents different/parallel create requests for a worker (several requests for the same configID) to
	// create more than one worker thread, which could otherwise happen e.g.: when several different configs are created in parallel which
	// have the same subconfig in their chain - this subconfig might then lead to several threads created for the same configID otherwise
	boost::mutex::scoped_lock lockCriticalSectionWorkerCreation(mutexCriticalSectionWorkerCreation);

	boost::shared_lock<boost::shared_mutex> sharedReadLock(mutexWorkerList); // shared lock (read lock)

	boost::shared_ptr<IConnectedVisionAlgorithmWorker> worker;
	for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = this->workers.begin(); it!=this->workers.end(); ++it) 
	{
		boost::shared_ptr<IConnectedVisionAlgorithmWorker> w = *it;
		if ( configID == w->getID() )
		{
			worker = w;
			break;
		}
	}

	sharedReadLock.unlock(); // release read lock

	if ( !worker )
	{
		// start new worker thread
		if ( workerFactory )
		{
			try 
			{
				worker = workerFactory->createWorker(env, config);
			}
			catch (std::exception &e)
			{
/* TODO
				// get config ID
				id_t configID = config->getconst_id();

				// get status
				auto statusStore = this->module->getStatusStore();
				boost::shared_ptr<Class_generic_status> status = statusStore->getByID(configID)->copy();
			
				status->set_status_error();
				status->set_message( e.what() );
				status->set_systemTimeProcessing( sysTime() );
				status->set_estimatedFinishTime( -1 );
				statusStore->save_copy(status);
*/
				throw ConnectedVision::runtime_error("cannot create worker (module name: " + config->get_moduleID() + " - config: " + config->getconst_id() + " - original exception message: \"" + e.what() +"\")");
			}
		}
		if ( !worker )
		{
			throw ConnectedVision::runtime_error("cannot create worker (module name: " + config->get_moduleID() + " - config: " + config->getconst_id() +")");
		}

		boost::unique_lock<boost::shared_mutex> uniqueWriteLock(mutexWorkerList); // unique lock (write lock)
		this->workers.push_back( worker );
		uniqueWriteLock.unlock(); // release write lock

	}	

	lockCriticalSectionWorkerCreation.unlock();

	// start, if already running start has no effect
	worker->start();

	cleanup();
}

/**
 * stop / abort a specific config / job
 *
 * @param config config chain of job
 */
void ConnectedVisionAlgorithmDispatcher::stop( boost::shared_ptr<const Class_generic_config> config )
{
	boost::shared_lock<boost::shared_mutex> sharedReadLock(mutexWorkerList); // shared lock (read lock)

	// search running threads
	id_t configID = config->get_id();
	for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = this->workers.begin(); it < this->workers.end(); ++it) 
	{
		if ( configID == (*it)->getID() )
		{
			boost::shared_ptr<IConnectedVisionAlgorithmWorker> worker = *it;
			worker->stop();
			break; 
		}
	}

	sharedReadLock.unlock(); // release read lock

	cleanup();
}

/**
 * reset a specific config / job
 *
 * @param config config chain of job
 */
void ConnectedVisionAlgorithmDispatcher::reset( boost::shared_ptr<const Class_generic_config> config )
{
	id_t configID = config->get_id();
	stop(config);

	// create new status
	auto statusStore = workerFactory->getModule()->getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status( new Class_generic_status(configID, config->get_moduleID(), *config->get_moduleURI(), this->module->getOutputPinIDs()) );
	statusStore->save_move(status);

	cleanup();
}

/**
 * recover a specific config / job from error state
 *
 * @param config config chain of job
 */
void ConnectedVisionAlgorithmDispatcher::recover( boost::shared_ptr<const Class_generic_config> config )
{
	id_t configID = config->get_id();
	stop(config);

	auto statusStore = workerFactory->getModule()->getStatusStore();
	auto constStatus = statusStore->getByID(configID);
	if ( !constStatus )
	{
		throw ConnectedVision::runtime_error("status not found");
	}
	// clone status to make it writeable
	ConnectedVision::shared_ptr<Class_generic_status> status = constStatus->copy();
	status->set_status_stopped();
	status->set_id( configID );
	statusStore->save_move(status);

	cleanup();
}


/**
 * clean up workes list
 *
 * remove finished workers
 */
void ConnectedVisionAlgorithmDispatcher::cleanup()
{
	boost::unique_lock<boost::shared_mutex> uniqueWriteLock(mutexWorkerList); // unique lock (write lock)

	for (std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >::iterator it = this->workers.begin(); it != this->workers.end(); ) 
	{
		boost::shared_ptr<IConnectedVisionAlgorithmWorker> worker = *it;
		if ( !worker->isRunning() )
		{
			this->workers.erase(it);
			it = this->workers.begin();
		}
		else
			it++;
	}

	uniqueWriteLock.unlock(); // release write lock
}

/**
 * get list of currently active worker threads
 *
 * @return running workers
 */
std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >  ConnectedVisionAlgorithmDispatcher::getRunningWorkers()
{
	cleanup();

	boost::shared_lock<boost::shared_mutex> sharedReadLock(mutexWorkerList); // shared lock (read lock)
	return this->workers;
	sharedReadLock.unlock(); // release read lock
}

/**
 * get list of currently active worker threads
 *
 * @return waiting workers
 */
std::vector< boost::shared_ptr<IConnectedVisionAlgorithmWorker> >  ConnectedVisionAlgorithmDispatcher::getWaitingWorkers()
{
	return this->queue;
}

} // namespace ConnectedVision