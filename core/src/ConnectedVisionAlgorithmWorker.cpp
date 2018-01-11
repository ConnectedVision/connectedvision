/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <string>
#include <time.h>

#include "helper.h"

#include "ConnectedVisionAlgorithmWorker.h"
#include "Module/Control/Store_SQLite_generic_status.h"
#include "Module/Module_BaseClass.h"


#error("TODO remove this file !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!")

namespace ConnectedVision
{

//typedef boost::interprocess::scoped_lock<boost::recursive_timed_mutex> scoped_lock;
typedef boost::recursive_timed_mutex::scoped_lock scoped_lock;

/**
 * sleep for x milliseconds
 *
 * @param ms	(minimal) time in milliseconts to sleep
 */
void ConnectedVisionAlgorithmWorker::sleep_ms(int ms)
{
	boost::this_thread::sleep( boost::posix_time::milliseconds( ms ) );
}


/**
 * algorithm worker thread constructor
 */
ConnectedVisionAlgorithmWorker::ConnectedVisionAlgorithmWorker(IModuleEnvironment *env, Module_BaseClass *module, boost::shared_ptr<const Class_generic_config> config) :
	env(env), module(module)
{
	this->logName = module->getModuleID();
	LOG_SCOPE;

	// make copy of config
	this->config.reset( new Class_generic_config( *config ) );
	this->t.reset();
}

/**
 * algorithm worker thread deconstructor
 */
ConnectedVisionAlgorithmWorker::~ConnectedVisionAlgorithmWorker()
{
	LOG_SCOPE;

	this->stop();

	if ( this->t )
	{
		// If thread is still running, make sure that it has really terminated.
		// Otherwise it would destroy the environment of the thread while it is still working!
		this->t->join();
		this->t.reset();
	}
}

/**
 * get instance ID
 * 
 * used to check if instance is already in thread list
 *
 * @return ID of instance
 */
ConnectedVision::id_t ConnectedVisionAlgorithmWorker::getID()
{
	LOG_SCOPE;

	// lock function 
	scoped_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		LOG_WARN("cannot lock worker mutex");
		throw ConnectedVision::runtime_error("cannot lock worker mutex");
	}

	return this->config->get_id();
}

/**
 * start algorithm worker thread
 */
void ConnectedVisionAlgorithmWorker::start()
{
	LOG_SCOPE;

	// lock function 
	scoped_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		LOG_WARN("cannot lock worker mutex");
		throw ConnectedVision::runtime_error("cannot lock worker mutex");
	}

	// make sure that worker is not already running, otherwise we have nothing to do
	if ( this->isRunning() )
		return;

	// prepare status
	LOG_INFO("prepare worker thread");
	this->prepare();

	// create and start actual worker thread
	LOG_INFO("start worker thread");
	this->go = true;
	this->t = boost::shared_ptr<boost::thread>( new boost::thread( &ConnectedVisionAlgorithmWorker::run, this ) );
}

/**
 * stop / abort a worker thread
 *
 * This function waits until the worker thread has really finished.
 */
void ConnectedVisionAlgorithmWorker::stop()
{
	LOG_SCOPE;

	// lock function 
	scoped_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		LOG_WARN("cannot lock worker mutex");
		throw ConnectedVision::runtime_error("cannot lock worker mutex");
	}

	this->go = false;

	if ( this->t )
	{
		if ( this->t->timed_join( timeout(10000) ) )
		{
			this->t.reset();
		}
		else
		{
			LOG_ERROR("Worker does not stop. Did you forget to check the GO condition?");
			//throw ConnectedVision::runtime_error("Worker does not stop. Did you forget to check the GO condition?");	
		}
	}
}

/**
 * test if the worker thread is still running
 *
 * @return true if the thread is running
 */
bool ConnectedVisionAlgorithmWorker::isRunning()
{
	LOG_SCOPE;

	// lock function 
	scoped_lock lock(this->mutex, timeout(500) );
	if ( !lock )
	{
		LOG_WARN("cannot lock worker mutex");
		throw ConnectedVision::runtime_error("cannot lock worker mutex");
	}

	if ( this->t )
	{
		bool finished = this->t->timed_join( timeout(0) );
		if ( finished )
		{
			// delelete thread if finished
			this->t.reset();
		}
		return !finished;
	}

	return false;
}


/**
 * prepare config for running
 */
void ConnectedVisionAlgorithmWorker::prepare()
{
	LOG_SCOPE;

	// get config ID
	id_t configID = this->config->get_id();

	// get status
	auto statusStore = this->module->getStatusStore();
	ConnectedVision::shared_ptr<Class_generic_status> status;
	try 
	{
		status = statusStore->getByID(configID)->copy();
	}
	catch (const ConnectedVision::out_of_range &)
	{
		// create new status
		status = Class_generic_status_p( new Class_generic_status( configID, this->config->get_moduleID(), *this->config->get_moduleURI(), this->module->getOutputPinIDs() ) );
	}

	try
	{
		std::vector<std::string> outputPinIDs = this->module->getOutputPinIDs();

		// if new config or config has been reseted we need to reset the status
		// otherwise we try to resume from last known results
		if (( status->is_status_init() ) ||
			( status->get_stableResults()->size() != outputPinIDs.size() ))
		{
		
			// reset status	
			status->resetStableResults(outputPinIDs);
		}

		// set status to running
		status->set_status_running();
		status->set_startTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );
		status->set_estimatedFinishTime(-1);
		status->set_message("");
		status->set_id(configID);
	}
	catch (ConnectedVision::runtime_error& e)
	{
		status->set_status_error();
		status->set_message( e.what() );
		status->set_startTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );
		status->set_estimatedFinishTime( -1 );
		status->set_id(configID);
	}	
	statusStore->save_move(status);

}

/**
 * wait for previous modules to finish
 *
 * @return true if modules are finished correctly
 */
bool ConnectedVisionAlgorithmWorker::waitForInputs(const std::vector<boost::shared_ptr< IConnectedVisionInputPin >>& inputPins)
{
	LOG_SCOPE;

	bool running;
	bool error = false;
	Class_generic_status status;

	// start previous module
	running = false;
	for ( unsigned int i = 0; (i < inputPins.size()) && !error && this->go; i++ )
	{
		status = inputPins[i]->start();
		running = running || status.is_status_running();
		error = error || (!status.is_status_running() && !status.is_status_finished());
	}

	// wait for previous module to finish
	timestamp_t eta = MIN_WAIT_TIME;
	while ( running && !error && this->go )
	{
		if ( eta < MIN_WAIT_TIME )
			eta = MIN_WAIT_TIME;
		if ( eta > MAX_WAIT_TIME )
			eta =  MAX_WAIT_TIME;
		boost::this_thread::sleep( boost::posix_time::milliseconds(eta) );

		// loop all modules
		running = false;
		for ( unsigned int i = 0; (i < inputPins.size()) && !error && this->go; i++ )
		{
			// get status
			status = inputPins[i]->getStatus();

			// get ETA
			timestamp_t t = status.get_estimatedFinishTime() - status.get_systemTimeProcessing();
			if ( t > eta )
				eta = t;

			// evaluate status
			running = running || status.is_status_running();
			error = error || (!status.is_status_running() && !status.is_status_finished());
		}
	}

	// break on error
	if ( error )
	{
		LOG_WARN("one of the previouse modules does not appropriate"); 
		this->go = false;
	}

	return !error;
}

/**
 * get log writer
 *
 * @return log writer
 */
boost::shared_ptr<Logging::ILogWriter> ConnectedVisionAlgorithmWorker::log() const
{
	if ( this->env ) 
	{
		return this->env->log(); 
	}
	else 
	{
		boost::shared_ptr<Logging::ILogWriter> log( new Logging::LogWriterNULL() );
		return log;
	}
}

} // namespace ConnectedVision