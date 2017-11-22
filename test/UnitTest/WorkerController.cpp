/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <unordered_set>
#include "ConnectedVision_Thread.h"
#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"
#include "DataHandling/Store_Ringbuffer.h"
#include "Module/Module_BaseClass.h"

namespace ConnectedVision {
namespace Module {

/**

http://plantuml.com/plantuml/form

@startuml

@enduml
*/

#define CHECK_INSTANCE_SINGLETON

// TODO: driver: WorkerThreadProgress, ConfigStatus gets status from WorkerThreadProgress
/*
namespace ConfigStatus { 
	enum ConfigStatus {init, starting, running, stopping, stopped, finished, error, recovering, resetting};
}	// wrap in namespace to avoid ambiguity of enums
*/

namespace WorkerThreadProgress { 
	enum WorkerThreadProgress {Undefined, Init, Starting, Running, Stopping, Cleanup, Stopped, Finished, Error, Recovering, Resetting, Terminating, Terminated};
}	// wrap in namespace to avoid ambiguity of enums

namespace WorkerCommand {
	
	/**
	* Worker Command Interface
	*/
	class ICommand {
	public:
		virtual void execute() = 0;
	};

	/**
	* Start Command
	*/
	class CommandStart : public ICommand {
	public:
		CommandStart(
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress	///< reference to thread safe worker progress
		) :	workerThreadProgress(workerThreadProgress) {}
		virtual ~CommandStart() {}

		virtual void execute()
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

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress;
	};

	/**
	* Stop Command
	*/
	class CommandStop : public ICommand {
	public:
		CommandStop(
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress,	///< reference to thread safe worker progress
			boost::thread& workerThread,															///< reference to worker thread
			const timestamp_t workerTimeout															///< timeout to wait for worker to stop cooperatively
		) :	workerThreadProgress(workerThreadProgress), workerThread(workerThread), workerTimeout(workerTimeout) {}
		virtual ~CommandStop() {}

		virtual void execute()
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
					this->workerThread.interrupt();	// TODO in workerThread class: make sure that workerThread / Cleanup is not interrupted (-> boost::this_thread::disable_interruption di;)
				}

				// wait until cleanup has finished
				this->workerThreadProgress.wait_until(WorkerThreadProgress::Stopped);
			}
		}

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress;
		boost::thread& workerThread;
		const timestamp_t workerTimeout;
	};

	/**
	* Reset Command
	*/
	class CommandReset : public ICommand {
	public:
		CommandReset(
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress,	///< reference to thread safe worker progress
			const CommandStop stopCmd				///< stop command
		) :	workerThreadProgress(workerThreadProgress), stopCmd(stopCmd) {}
		virtual ~CommandReset() {}

		virtual void execute()
		{
			// make sure that worker is stopped
			stopCmd.execute();

			// signal to reset
			this->workerThreadProgress = WorkerThreadProgress::Resetting;

			// reset config / delete all data of config
// TODO move into workerThread:			module.deleteAllData( configID );
// -> so only one thread (workerThread) is writing / deleting data

			// wait for resetting to finish
			this->workerThreadProgress.wait_while(WorkerThreadProgress::Resetting);	// expected progress: Init
		}

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress;
		CommandStop stopCmd;
	};

	/**
	* Recover Command
	*/
	class CommandRecover : public ICommand {
	public:
		CommandRecover(
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress	///< reference to thread safe worker progress
		) :	workerThreadProgress(workerThreadProgress) {}
		virtual ~CommandRecover() {}

		virtual void execute()
		{
			// is config / worker in error mode
			if ( this->workerThreadProgress == WorkerThreadProgress::Error )
			{
				// signal to recover
				this->workerThreadProgress = WorkerThreadProgress::Recovering;

				// recover config
	/* TODO move into workerThread:
				if ( module.recover( configID ) )
					this->workerStatus = ConfigStatus::stopped;
				else
					this->workerStatus = ConfigStatus::error;
*/
	// -> so only one thread (workerThread) is writing / deleting data

				// wait for recover to finish
				this->workerThreadProgress.wait_while(WorkerThreadProgress::Recovering);	// expected progress: Init, Stopped or Error (if recovering is not possible)
			}
		}

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress;
	};


	/**
	* Terminate Command
	*/
	class CommandTerminate : public ICommand {
	public:
		CommandTerminate(
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress,	///< reference to thread safe worker progress
			boost::atomic<WorkerThreadProgress::WorkerThreadProgress> &progressBeforeTermination, ///< reference to progress before terminate in worker controller
			const CommandStop stopCmd										///< stop command
		) : workerThreadProgress(workerThreadProgress), progressBeforeTermination(progressBeforeTermination), stopCmd(stopCmd) {}
		virtual ~CommandTerminate() {}

		virtual void execute()
		{
			// make sure that worker is stopped
			stopCmd.execute();

			this->progressBeforeTermination = this->workerThreadProgress;

			// set termination flag
			this->workerThreadProgress = WorkerThreadProgress::Terminating;

			// wait until workerThread destructor is finished
			this->workerThreadProgress.wait_until(WorkerThreadProgress::Terminated);	// TODO: set Terminated as last action in ~WorkerThread() destructor
		}

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress;
		boost::atomic<WorkerThreadProgress::WorkerThreadProgress> &progressBeforeTermination;
		CommandStop stopCmd;
	};

	/**
	* command queue for worker commands
	*/
	class CommandQueue : public ConnectedVision::thread_safe_queue< WorkerCommand::ICommand >
	{
	public:
		CommandQueue() {}
		virtual ~CommandQueue() {}

// TODO Warum eigene Implementierung????
/*
		void push(
			const ConnectedVision::shared_ptr<WorkerCommand::ICommand>& cmd	///< command to be pushed to queue
		) {
			ConnectedVision::thread_safe_queue< ConnectedVision::shared_ptr<WorkerCommand::ICommand> >::push(cmd);
		}
*/
	};
}

class WorkerController : public IWorkerController
{
public:
	typedef boost::unique_lock<boost::mutex> Lock;

	/**
		constructor for existing config, access by configID
	*/
	WorkerController(		
		const id_t& configID,																///< config chain ID
		ConnectedVision::Module::IModule& module,											///< ConnectedVision module
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to stop cooperatively
	) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout), workerThreadProgress(WorkerThreadProgress::Finished)
	{
		// load config
		auto config = this->loadConfig(configID, module);

		// init worker manager
		this->init(config);
	}

	/**
		constructor for new config, config(-chain) is saved to data store
	*/
	WorkerController(		
		const Class_generic_config& configOrig,												///< config chain
		ConnectedVision::Module::IModule& module,											///< module
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to stop cooperatively
	) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout), workerThreadProgress(WorkerThreadProgress::Finished)
	{
		// save config and get shared pointer to const config
		auto config = this->saveConfig(configOrig, module);
		
		// init worker manager
		this->init(configConst);
	}


	virtual ~WorkerController()
	{
		// terminate controller and worker thread
		auto stopCmd = WorkerCommand::CommandStop( this->workerThreadProgress, this->workerThread, this->workerTimeout );
		auto terminateCmd = WorkerCommand::CommandTerminate( this->workerThreadProgress, this->progressBeforeTermination, stopCmd );
		commandQueue.push( terminateCmd );

		// wait for the threads to terminate before destroying the class
		// (This should be done before any other clean-up of the destructor.)
		this->workerThread.join();
		this->controllerThread.join();

		// remove from instance list
		if ( this->configConst )
			this->module.unregisterWorkerInstance(this->configConst->getconst_configID(), this);
	}

	/**
	* test if the worker for this config is running
	*
	* @return true if running
	*/
	bool activeWorker() const
	{
		auto progress = this->workerThreadProgress.get();
		return ( progress >= WorkerThreadProgress::Starting && progress <= WorkerThreadProgress::Stopped );
	}


	/**
	* maps worker progress to config status
	*
	* @return config status string
	*/
	const boost::shared_ptr<std::string> getStatusFromProgress(WorkerThreadProgress::WorkerThreadProgress progress = WorkerThreadProgress::Undefined) const
	{
		if ( progress == WorkerThreadProgress::Undefined ) // default path / call from outside
		{
			progress = this->workerThreadProgress.get();
		}
		else // recursive call from inside
		{
			if ( progress == WorkerThreadProgress::Terminating || progress == WorkerThreadProgress::Terminated )
				throw ConnectedVision::invalid_argument("[WorkerController] infinitive recursive loop detected");
		}

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
				return getStatusFromProgress(this->progressBeforeTermination); // recursive call
			default:
				return Class_generic_status::status_error;
		}
	}


	/**
	* start the worker for a given config
	*
	* If there is already an existing worker, this function does nothing.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> start() 
	{
		// enqueue start command
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdStart = 
			ConnectedVision::make_shared<WorkerCommand::CommandStart>(this->workerStatus, this->workerThreadProgress);
		commandQueue.push( cmdStart );

		return this->getStatus();
	}

	/**
	* stop the worker of a specific config chain, if the config is running
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> stop()
	{
		// enqueue stop command
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdStop = 
			ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerStatus, this->workerThreadProgress, this->workerThread, this->workerTimeout);
		commandQueue.push( cmdStop );

		return this->getStatus();
	}
	
	/**
	* resets the current config
	*
	* If the config is running, it is stopped in advance.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> reset()
	{
		// stop command
		auto cmdStop = 
			ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerStatus, this->workerThreadProgress, this->workerThread, this->workerTimeout);

		// reset command
		id_t configID = this->configConst->getconst_id();
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdReset = 
			ConnectedVision::make_shared<WorkerCommand::CommandReset>(this->module, configID, this->workerStatus, cmdStop);

		// enqueue reset command
		commandQueue.push( cmdReset );

		return this->getStatus();
	}

	/**
	* revocer the current config
	*
	* Only configs in error state can be recovered.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> recover()
	{
		// stop command
		id_t configID = this->configConst->getconst_id();
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmd = 
				ConnectedVision::make_shared<WorkerCommand::CommandRecover>(this->module, configID, this->workerStatus);

		// enqueue reset command
		commandQueue.push( cmd );

		return this->getStatus();
	}

	/**
	* get status of config chain
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> getStatus()
	{
		// TODO short status
		auto status = this->statusObj->copy();
		auto commandQueue = boost::make_shared<	std::vector< boost::shared_ptr<std::string> > >();

// TODO		commandQueue = this->commandQueue;

		status->set_commandQueue(commandQueue);

		this->statusConst = this->statusStore->make_const( status );
		return this->statusConst;
	}

	/**
	* get current config
	*
	* @returns current config
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_config> getConfig()
	{
		return this->configConst;
	}

	// WorkerController functions

	/**
	* should the worker continue running
	*
	* This function can be called multiple times during one (long) computation step without any side effects.
	* It explicitely does NOT trigger any status or progress update.
	*
	* @note This function has to be thread-safe!
	*
	* @return continue working
	*/
	virtual bool intermediateContinueCheck() const
	{
		return (workerThreadProgress == WorkerThreadProgress::Running);
	}

	/**
	* Inform the worker controller that one computation iteration step (e.g. frame) has been finished,
	* and ask to continue with the next computation.
	*
	* @note This function has to be thread-safe!
	*
	* @return true if worker should continue
	*/
	virtual bool nextIterationStep()
	{
		return intermediateContinueCheck();
	}


protected:

	void controllerThreadFunction()
	{
		try
		{
			// loop until destructor sets terminate flag
			while ( this->workerThreadProgress.get() != WorkerThreadProgress::Terminate )
			{
				// wait for new command in queue
				auto cmd = this->commandQueue.pop_wait();

				// execute command
				cmd->execute();
			}
		}
		catch (...)
		{
			// ignore
		}
	}

	void workerThreadFunction()
	{
		// thread loop
		for(;;)
		{
			bool error = false;
			bool stopped = false;

			// wait for progress to change
			try
			{
				this->workerThreadProgress.wait_while( WorkerThreadProgress::Finished );
			}
			catch (boost::thread_interrupted&)
			{
				// ignore
			}
			
			auto progress = this->workerThreadProgress.get();

			// exit if terminate flag is set
			if ( progress == WorkerThreadProgress::Terminate )
				break;

			if ( progress == WorkerThreadProgress::Starting )
			{
				try
				{
					// create worker
					this->workerStatus = ConfigStatus::starting;
					auto worker = this->workerFactory->createWorker(*this, this->configConst);

					// start worker
					this->workerThreadProgress = WorkerThreadProgress::Running;
					this->workerStatus = ConfigStatus::running;

					try
					{
						worker->run();
					}
					catch(...)
					{
						error = true;
					}

					// clean up worker
					this->workerThreadProgress = WorkerThreadProgress::Cleanup;
					this->workerStatus = ConfigStatus::stopping;
					stopped = !this->intermediateContinueCheck();

					// destroy worker
					worker.reset();
				}
				catch (...)
				{
					error = true;
				}

				// set status
				if ( error )
					this->workerStatus = ConfigStatus::error;
				else if ( stopped )
					this->workerStatus = ConfigStatus::stopped;
				else
					this->workerStatus = ConfigStatus::finished;
			}

			// wait for next worker
			this->workerThreadProgress = WorkerThreadProgress::Finished;
		}
	}

	shared_ptr<const Class_generic_config> loadConfig(
		const id_t& configID,																///< config chain ID
		ConnectedVision::Module::IModule& module											///< ConnectedVision module
		)
	{
		auto configStore = this->module.getConfigStore();
		if ( !configStore )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid configStore (null pointer)");

		// load config from store
		shared_ptr<const Class_generic_config> config = configStore->getByID(configID);
		if ( !config )
			throw ConnectedVision::invalid_argument("[WorkerController] cannot find config with config id: " + configID);

		return config;
	}

	shared_ptr<const Class_generic_config> saveConfig(
		const Class_generic_config& configOrig,												///< config chain
		ConnectedVision::Module::IModule& module											///< module
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

	/**
	* init Worker Manager
	*	- load / create status
	*/
	void init(
		ConnectedVision::shared_ptr<const Class_generic_config> config ///< config object
	)
	{
		// intentional set to error: if progressBeforeTermination is used in getStatusFromProgress() before it is set in CommandTerminate execute()
		progressBeforeTermination = WorkerThreadProgress::Error;

		if ( !this->workerFactory )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid workerFactory (null pointer)");

		// set config
		if ( !config )
			throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config (null pointer)");
		id_t configID = config->getconst_id();
		if ( configID.empty() )
			throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config has no ID");

		// set member config
		this->configConst = config;

		this->module.registerWorkerInstance(configID, this); // TODO module ->	throw ConnectedVision::runtime_error("[WorkerController] there is already an instance for config: " + IDToStr(configID) );

		try
		{
			// init command queue
			commandQueue.clear();

			// set progress according to config status
			auto statusStore = this->module.getStatusStore();
			if ( !statusStore )
				throw ConnectedVision::invalid_argument("[WorkerController] invalid statusStore (null pointer)");

			// read status from store
			auto statusConst = statusStore->getByID(configID);
			if ( !statusConst )
			{
				// create new status
				statusConst = boost::make_shared<Class_generic_status>(config->getconst_id(), module.getModuleID(), module.getModuleURI(), this->module.getOutputPinIDs());
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

			// start worker thread
			this->workerThread = boost::thread(&WorkerController::workerThreadFunction, this);
		}
		catch (...)
		{
			// remove from instance list
			this->module.unregisterWorkerInstance(configID, this);

			// rethrow
			throw;
		}
	}

	// module
	ConnectedVision::Module::IModule& module;

	// config
	ConnectedVision::shared_ptr<const Class_generic_config> configConst;

	// command
	WorkerCommand::CommandQueue commandQueue;
	boost::thread controllerThread;


	// worker
	thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> workerThreadProgress;
	boost::thread workerThread;
	const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory;
	timestamp_t workerTimeout;


public:
	// spy functions
	const ConfigStatus::ConfigStatus spy_workerStatus() { return this->workerStatus.load(); }
	const thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &spy_workerThreadProgress() { return this->workerThreadProgress; }

	boost::atomic<WorkerThreadProgress::WorkerThreadProgress> progressBeforeTermination;

};


}} // namespace