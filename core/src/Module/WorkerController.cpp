/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/thread/thread.hpp>
#include <boost/thread/thread_guard.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>

#include <unordered_set>

#include "WorkerController.h"

#include "ConnectedVision_Thread.h"
#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"
#include "DataHandling/Store_Ringbuffer.h"
#include "Module/Module_BaseClass.h"


namespace ConnectedVision {
namespace Module {

namespace WorkerCommand {

	void CommandStart::execute()
	{
		// start new worker if status is init or stopped
		if ( workerThreadProgress == WorkerThreadProgress::Init || workerThreadProgress == WorkerThreadProgress::Stopped )
		{
			// reset workerThreadProgress
			this->workerThreadProgress.reset( WorkerThreadProgress::Starting );

			// wait until worker is running
			this->workerThreadProgress.wait_until( WorkerThreadProgress::Running );
		}
	}

	void CommandStop::execute()
	{
		// is worker running
		if ( this->workerThreadProgress == WorkerThreadProgress::Running )
		{
			// signal to stop
			this->workerThreadProgress = WorkerThreadProgress::Stopping;

			// wait until worker.run() has returned and cleanup has started (with timeout)
			if ( !this->workerThreadProgress.wait_until(WorkerThreadProgress::Cleanup, this->workerTimeout) )
			{
				// interrupt uncooperative worker
				this->workerThread.interrupt();
			}

			// wait until cleanup has finished
			this->workerThreadProgress.wait_until(WorkerThreadProgress::Stopped);
		}
	}

	void CommandReset::execute()
	{
		// make sure that worker is stopped
		this->stopCmd->execute();

		// signal to reset
		this->workerThreadProgress = WorkerThreadProgress::Resetting;

		// wait for resetting to finish
		this->workerThreadProgress.wait_while(WorkerThreadProgress::Resetting);	// expected progress: Init
	}

	void CommandRecover::execute()
	{
		// is config / worker in error mode
		if ( this->workerThreadProgress == WorkerThreadProgress::Error )
		{
			// signal to recover
			this->workerThreadProgress = WorkerThreadProgress::Recovering;

			// wait for recover to finish
			this->workerThreadProgress.wait_while(WorkerThreadProgress::Recovering);	// expected progress: Stopped or Error (if recovering is not possible)
		}
	}

	void CommandTerminate::execute()
	{
		// make sure that worker is stopped
		stopCmd->execute();

		this->progressBeforeTermination = this->workerThreadProgress;

		// set termination flag
		this->workerThreadProgress = WorkerThreadProgress::Terminating;

		// wait until workerThread destructor is finished
		this->workerThreadProgress.wait_until(WorkerThreadProgress::Terminated);	// TODO: set Terminated as last action in ~WorkerThread() destructor
	}
}	// namespace WorkerCommand

WorkerController::WorkerController(
	const id_t &configID,
	ConnectedVision::Module::IModule &module,
	ConnectedVision::Module::IWorkerFactory &workerFactory,
	const timestamp_t workerTimeout
) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout), workerThreadProgress(WorkerThreadProgress::Finished)
{
	// init worker manager
	this->init(configID);
}

WorkerController::WorkerController(		
	const Class_generic_config &configOrig,
	ConnectedVision::Module::IModule &module,
	ConnectedVision::Module::IWorkerFactory &workerFactory,
	const timestamp_t workerTimeout
) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout), workerThreadProgress(WorkerThreadProgress::Finished)
{
	// save config and get shared pointer to const config
	auto config = this->saveConfig(configOrig, module);

	// init worker manager
	this->init(config->getconst_configID());
}


WorkerController::~WorkerController()
{
	// terminate controller and worker thread
	auto stopCmd = ConnectedVision::make_shared<WorkerCommand::CommandStop>( this->workerThreadProgress, this->workerThread, this->workerTimeout );
	ConnectedVision::shared_ptr<WorkerCommand::ICommand> terminateCmd = boost::dynamic_pointer_cast<WorkerCommand::ICommand>(ConnectedVision::make_shared<WorkerCommand::CommandTerminate>( this->workerThreadProgress, this->progressBeforeTermination, stopCmd ));
	commandQueue.push( terminateCmd );

	// wait for the threads to terminate before destroying the class
	// (This should be done before any other clean-up of the destructor.)
	this->workerThread.join();
	this->controllerThread.join();

	// remove from instance list
	this->module.unregisterWorkerInstance(this->configID, this);
}

bool WorkerController::activeWorker() const
{
	auto progress = this->workerThreadProgress.get();
	bool active = progress >= WorkerThreadProgress::Starting && progress < WorkerThreadProgress::Stopped;
	return ( active );
}

ConnectedVision::shared_ptr<const Class_generic_status> WorkerController::start() 
{
	// enqueue start command
	ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdStart = boost::dynamic_pointer_cast<WorkerCommand::ICommand>(ConnectedVision::make_shared<WorkerCommand::CommandStart>(this->workerThreadProgress));
	commandQueue.push( cmdStart );

	return this->getStatus();
}

ConnectedVision::shared_ptr<const Class_generic_status> WorkerController::stop()
{
	// enqueue stop command
	ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdStop = boost::dynamic_pointer_cast<WorkerCommand::ICommand>(ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerThreadProgress, this->workerThread, this->workerTimeout));
	commandQueue.push( cmdStop );

	return this->getStatus();
}
	
ConnectedVision::shared_ptr<const Class_generic_status> WorkerController::reset()
{
	// enqueue reset command
	auto cmdStop = ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerThreadProgress, this->workerThread, this->workerTimeout);
	ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdReset = boost::dynamic_pointer_cast<WorkerCommand::ICommand>(ConnectedVision::make_shared<WorkerCommand::CommandReset>(this->workerThreadProgress, cmdStop));
	commandQueue.push( cmdReset );

	return this->getStatus();
}

ConnectedVision::shared_ptr<const Class_generic_status> WorkerController::recover()
{
	// enqueue recover command
	ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdRecover = boost::dynamic_pointer_cast<WorkerCommand::ICommand>(ConnectedVision::make_shared<WorkerCommand::CommandRecover>(this->workerThreadProgress));
	commandQueue.push( cmdRecover );

	return this->getStatus();
}

ConnectedVision::shared_ptr<const Class_generic_status> WorkerController::getStatus()
{
	// get current status according to worker progress
	auto statusConst = this->statusStore->getByID(this->configID);
	if ( !statusConst )
		return statusConst;
	auto status = statusConst->copy();

	// get progress
	WorkerThreadProgress::WorkerThreadProgress progress = this->workerThreadProgress.get();
	if ( progress == WorkerThreadProgress::Terminating || progress == WorkerThreadProgress::Terminated )
		progress = this->progressBeforeTermination;
	// get status from progress
	auto progressToStatus = mapProgressToStatus(progress);

	// cache status, but do not write status while worker is running
	if ( progress >= WorkerThreadProgress::Starting && progress < WorkerThreadProgress::Stopped )
	{
		// was status changed manually?
		if ( status->is_status_na() )
		{
			// update according to worker progress
			status->set_status( progressToStatus );
		}
		return this->statusStore->make_const( status );
	}
	else
	{
		// return directly if status didn't change or worker is running
		if ( status->is_status( progressToStatus ) )
			return statusConst;
		
		// update according to worker progress
		status->set_status( progressToStatus );

		// save status and return
		statusConst = this->statusStore->make_const( status );
		this->statusStore->save_const( statusConst );
		return statusConst;
	}
}

ConnectedVision::shared_ptr<const Class_generic_config> WorkerController::getConfig()
{
	return this->configStore->getByID(this->configID);
}

bool WorkerController::intermediateContinueCheck() const
{
	return (workerThreadProgress == WorkerThreadProgress::Running);
}

bool WorkerController::nextIterationStep()
{
	// for now, there is nothing else to do than just check if we are not stopped
	return intermediateContinueCheck();
}

void WorkerController::controllerThreadFunction()
{
	try
	{
		// loop until destructor sets terminate flag
		while ( this->workerThreadProgress < WorkerThreadProgress::Terminating )
		{
			// wait for new command in queue
			auto cmd = this->commandQueue.pop_wait();

			// execute command
			cmd->execute();
		}
	}
	catch (std::exception &e)
	{
		// TODO Log exception
		std::cout << "CORE PANIC: [Exception in controller thread command] " << e.what();

		// terminate to worker
		this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
		this->workerThread.interrupt();
		exit(1);
	}
}

void WorkerController::workerThreadFunction()
{

	// thread loop
	try
	{
		for(;;)
		{
			bool error = false;
			auto progress = this->workerThreadProgress.get();
			switch (progress)
			{
				case WorkerThreadProgress::Undefined:
				case WorkerThreadProgress::Init:
				case WorkerThreadProgress::Stopping:
				case WorkerThreadProgress::Stopped:				
				case WorkerThreadProgress::Finished:
				case WorkerThreadProgress::Error:
					// update status (saves status to store if changed, updates cache (if used))
					this->getStatus();

					// ignore and wait for next progress
					break;

				case WorkerThreadProgress::Terminating:
				case WorkerThreadProgress::Terminated:
					// exit if terminate flag is set
					progress = WorkerThreadProgress::Terminated; this->workerThreadProgress = progress; // update internal progress and set workerThreadProgress

					// update status (saves status to store if changed, updates cache (if used))
					this->getStatus();

					return;

				case WorkerThreadProgress::Starting:
					try
					{
						// invalid status in store
						auto status = this->getStatus()->copy();
						status->set_message("");
						status->set_status_na();
						this->statusStore->save_move( status );

						// make sure that workerThread / Cleanup is not interrupted (-> boost::this_thread::disable_interruption)
						boost::this_thread::disable_interruption interrupt_disabler;

						// create worker
						this->worker = std::move(this->workerFactory.createWorker(*this, this->getConfig()));
						if ( worker )
						{
							try
							{
								// start worker
								this->workerThreadProgress = WorkerThreadProgress::Running;

								// update status (saves status to store if changed, updates cache (if used))
								// note: important to be done before worker->run() is invoked
								this->getStatus();

								boost::this_thread::restore_interruption interrupt_enabler(interrupt_disabler);
								worker->run();
							}
							catch (boost::thread_interrupted)
							{
								error = true;
								std::cout << "[Exception worker.run() did not return on stop request in time -> interrupted after timeout] ";
							}
							catch (std::exception e)
							{
								// TODO Log exception
								error = true;
								std::cout << "[Exception in worker.run()] " << e.what();
							}
							bool stopped = !this->intermediateContinueCheck();	// was worker forced to stop?

							// clean up worker -> destroy worker
							this->workerThreadProgress = WorkerThreadProgress::Cleanup;
							worker.reset();

							// get status from store (not this->getStatus()!!! since it would overwrite db status with getStatusFromProgress())
							auto statusConst = this->statusStore->getByID(this->configID);
							// set status
							if ( error || statusConst->is_status_error() ) // check for both internal error (e.g. worker threw exception) and error from status stored in db (error manually set by worker)
								progress = WorkerThreadProgress::Error;
							else if ( stopped )
								progress = WorkerThreadProgress::Stopped;
							else
								progress = WorkerThreadProgress::Finished;
						} 
						else 
						{
							std::cout << "creating worker failed [moduleID: "<< this->module.getModuleID() << "]" << std::endl;
							// module has no worker -> skip running
							progress = WorkerThreadProgress::Finished;
						}

						// finally set workerThreadProgress
						this->workerThreadProgress = progress;
					}
					catch (std::exception e)
					{
						// TODO Log exception
						std::cout << "CORE PANIC: [Exception in worker thread] " << e.what();

						// terminate
						this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
						exit(1);
					}
					break;


				case WorkerThreadProgress::Resetting:
					// reset config / delete all data of config
					{
						// make sure that workerThread / Cleanup is not interrupted (-> boost::this_thread::disable_interruption di;)
						boost::this_thread::disable_interruption interrupt_disabler;

						// reset status message and progress
						auto status = this->getStatus()->copy();
						status->set_message("");
						status->set_progress(0.0);

						// delete result data
						try
						{
							module.deleteAllData(this->configID);	// one thread (workerThread) is writing / deleting data
						}
						catch (...)	// ignore exceptions while deleting data
						{}
						status->resetStableResults();

						// save status
						auto statusConst = this->statusStore->make_const( status );
						this->statusStore->save_const( statusConst );

						// reset progress to init
						progress = WorkerThreadProgress::Init; this->workerThreadProgress.reset(progress); // update internal progress and (re)set workerThreadProgress
					}
					break;

				case WorkerThreadProgress::Recovering:
					// recover config
					{
						// make sure that workerThread / Cleanup is not interrupted (-> boost::this_thread::disable_interruption di;)
						boost::this_thread::disable_interruption interrupt_disabler;

						if ( this->module.processConfigRecover( this->configID ) ) 	// one thread (workerThread) is writing / deleting data
							progress = WorkerThreadProgress::Stopped;
						else
							progress = WorkerThreadProgress::Error;
						this->workerThreadProgress.reset(progress); // update internal progress and (re)set workerThreadProgress

						// update status (saves status to store if changed, updates cache (if used))
						this->getStatus();
					}
					break;


				default:
					std::cout << "CORE PANIC: [worker thread] unexpected worker progress in thread loop: " << progress;
					this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
					exit(1);
			}

			// wait on change of worker progress (must be interruptable!)
			this->workerThreadProgress.wait_while(progress);
		}
	}
	catch (std::exception &e)
	{
		// TODO Log exception
		std::cout << "CORE PANIC: [Exception in controller thread command] " << e.what();

		// terminate to worker
		this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
		this->workerThread.interrupt();
		exit(1);
	}
}

shared_ptr<const Class_generic_config> WorkerController::saveConfig(
	const Class_generic_config& configOrig,
	ConnectedVision::Module::IModule& module
	)
{
	auto configStore = this->module.getConfigStore();
	if ( !configStore )
		throw ConnectedVision::invalid_argument("[WorkerController] invalid configStore (null pointer)");

	// copy original config
	auto config = ConnectedVision::make_shared<Class_generic_config>( configOrig );
		
	// compute id
	config->compute_id();

	// save config to store
	shared_ptr<const Class_generic_config> configConst = configStore->make_const(config);
	configStore->save_const(configConst);

	return configConst;
}


void WorkerController::init(id_t configID)
{
	// intentional set to error: if progressBeforeTermination is used in getStatusFromProgress() before it is set in CommandTerminate execute()
	progressBeforeTermination = WorkerThreadProgress::Error;

	// get config
	this->configID = configID;
	if ( this->configID.empty() )
		throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config has no ID");
	this->configStore = this->module.getConfigStore();
	if ( !this->configStore )
		throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config store");
	auto configConst = this->configStore->getByID(this->configID);
	if ( !configConst )
		throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config (null pointer)");

	// init command queue
	commandQueue.clear();

	// set progress according to config status
	this->statusStore = this->module.getStatusStore();
	if ( !this->statusStore )
		throw ConnectedVision::invalid_argument("[WorkerController] invalid statusStore (null pointer)");

	// read status from store
	auto statusConst = statusStore->getByID(this->configID);
	if ( !statusConst )
	{
		// create new status
		statusConst = boost::make_shared<Class_generic_status>(this->configID, this->module.getModuleID(), this->module.getModuleURI(), this->module.getOutputPinIDs());
		statusStore->save_const( statusConst );
	}

	// set internal worker progress / status
	if ( statusConst->is_status_init() )
		workerThreadProgress.reset( WorkerThreadProgress::Init );
	else if ( statusConst->is_status_stopped() )
		workerThreadProgress.reset( WorkerThreadProgress::Stopped );
	else if ( statusConst->is_status_finished() )
		workerThreadProgress.reset( WorkerThreadProgress::Finished );
	else
		workerThreadProgress.reset( WorkerThreadProgress::Error );

	// start controller thread
	this->controllerThread = boost::thread(&WorkerController::controllerThreadFunction, this);
	this->controllerThreadGuard = boost::make_shared<boost::thread_guard<boost::interrupt_and_join_if_joinable>>(this->controllerThread);

	// start worker thread
	this->workerThread = boost::thread(&WorkerController::workerThreadFunction, this);
	this->workerThreadGuard = boost::make_shared<boost::thread_guard<boost::interrupt_and_join_if_joinable>>(this->workerThread);

	// notify module about new worker instance (may fail with intended out_of_range exception in case of a race condition)
	// so the calling constructor which invokes this init() function will also throw
	// (and eventually enforcing a single WorkerController instance for each config ID)
	this->module.registerWorkerInstance(this->configID, this);
}

const boost::shared_ptr<std::string> WorkerController::mapProgressToStatus(WorkerThreadProgress::WorkerThreadProgress progress)
{
	switch ( progress )
	{
		case WorkerThreadProgress::Init:
			return Class_generic_status::status_init;
		case WorkerThreadProgress::Starting:
			return Class_generic_status::status_starting;
		case WorkerThreadProgress::Running:
			return Class_generic_status::status_running;
		case WorkerThreadProgress::Stopping:
		case WorkerThreadProgress::Cleanup:
			return Class_generic_status::status_stopping;
		case WorkerThreadProgress::Stopped:
			return Class_generic_status::status_stopped;
		case WorkerThreadProgress::Finished:
			return Class_generic_status::status_finished;
		case WorkerThreadProgress::Recovering:
			return Class_generic_status::status_recovering;
		case WorkerThreadProgress::Resetting:
			return Class_generic_status::status_resetting;
		case WorkerThreadProgress::Terminating:
		case WorkerThreadProgress::Terminated:
			throw ConnectedVision::invalid_argument("[WorkerController] progress: terminate can not be mapped to status");
		default:
			return Class_generic_status::status_error;
	}
}

const WorkerThreadProgress::WorkerThreadProgress WorkerController::mapStatusToProgress(ConnectedVision::shared_ptr<Class_generic_status> status)
{
	if ( !status )
		return WorkerThreadProgress::Undefined;

	if ( status->is_status( Class_generic_status::status_init ) )
		return WorkerThreadProgress::Init;
	if ( status->is_status( Class_generic_status::status_starting ) )
		return WorkerThreadProgress::Starting;
	if ( status->is_status( Class_generic_status::status_running ) )
		return WorkerThreadProgress::Running;
	if ( status->is_status( Class_generic_status::status_stopping ) )
		return WorkerThreadProgress::Stopping;
	if ( status->is_status( Class_generic_status::status_stopped ) )
		return WorkerThreadProgress::Stopped;
	if ( status->is_status( Class_generic_status::status_finished ) )
		return WorkerThreadProgress::Finished;
	if ( status->is_status( Class_generic_status::status_recovering ) )
		return WorkerThreadProgress::Recovering;
	if ( status->is_status( Class_generic_status::status_resetting ) )
		return WorkerThreadProgress::Resetting;
	if ( status->is_status( Class_generic_status::status_error ) )
		return WorkerThreadProgress::Error;

	return WorkerThreadProgress::Undefined;
}

}} // namespace
