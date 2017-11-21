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

namespace ConfigStatus { 
	enum ConfigStatus {init, starting, running, stopping, stopped, finished, error, recovering, resetting};
}	// wrap in namespace to avoid ambiguity of enums

namespace WorkerThreadProgress { 
	enum WorkerThreadProgress {STARTING, RUNNING, STOPPING, CLEANUP, END, TERMINATE}; 
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
			boost::atomic<ConfigStatus::ConfigStatus> &workerStatus,												///< reference to worker status indicator
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress	///< reference to thread safe worker progress
		) :	workerStatus(workerStatus), workerThreadProgress(workerThreadProgress) {}
		virtual ~CommandStart() {}

		virtual void execute()
		{
			// start new worker if status is init or stopped
			auto status = this->workerStatus.load();
			if ( (status == ConfigStatus::init || status == ConfigStatus::stopped ) && 
				( workerThreadProgress == WorkerThreadProgress::END) )
			{
				// reset workerThreadProgress
				this->workerThreadProgress.reset( WorkerThreadProgress::STARTING );

				// wait until worker is running
				this->workerThreadProgress.wait_until( WorkerThreadProgress::RUNNING );
			}
		}

	protected:
		boost::atomic<ConfigStatus::ConfigStatus> &workerStatus;
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress;
	};

	/**
	* Stop Command
	*/
	class CommandStop : public ICommand {
	public:
		CommandStop(
			boost::atomic<ConfigStatus::ConfigStatus>& workerStatus,												///< reference to worker status indicator
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress,	///< reference to thread safe worker progress
			boost::thread& workerThread,															///< reference to worker thread
			const timestamp_t workerTimeout															///< timeout to wait for worker to stop cooperatively
		) :	workerStatus(workerStatus), workerThreadProgress(workerThreadProgress), workerThread(workerThread), workerTimeout(workerTimeout) {}
		virtual ~CommandStop() {}

		virtual void execute()
		{
			// is worker running
			if ( this->workerStatus == ConfigStatus::running )
			{
				// signal to stop
				this->workerStatus = ConfigStatus::stopping;
				this->workerThreadProgress = WorkerThreadProgress::STOPPING;

				// wait until worker has finished
				if ( !this->workerThreadProgress.wait_until(WorkerThreadProgress::END, this->workerTimeout) )
				{
					// interrupt uncooperative worker
					if ( this->workerThreadProgress == WorkerThreadProgress::STOPPING ) // Send interrupt if worker is still in run() methode.
						this->workerThread.interrupt();

					// wait until worker has finished
					this->workerThreadProgress.wait_until(WorkerThreadProgress::END);
				}
			}
		}

	protected:
		boost::atomic<ConfigStatus::ConfigStatus>& workerStatus;
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
			ConnectedVision::Module::IModule &module,						///< module
			const id_t configID,											///< config ID
			boost::atomic<ConfigStatus::ConfigStatus> &workerStatus,		///< reference to worker status indicator
			ConnectedVision::shared_ptr<CommandStop> stopCmd				///< stop command
		) :	workerStatus(workerStatus), module(module), configID(configID), stopCmd(stopCmd) {}
		virtual ~CommandReset() {}

		virtual void execute()
		{
			// make sure that worker is stopped
			stopCmd->execute();

			// set status
			this->workerStatus = ConfigStatus::resetting;

			// reset config / delete all data of config
			module.deleteAllData( configID );
			this->workerStatus = ConfigStatus::init;
		}

	protected:
		boost::atomic<ConfigStatus::ConfigStatus> &workerStatus;
		ConnectedVision::Module::IModule& module;
		const id_t configID;
		ConnectedVision::shared_ptr<CommandStop> stopCmd;
	};

	/**
	* Recover Command
	*/
	class CommandRecover : public ICommand {
	public:
		CommandRecover(
			ConnectedVision::Module::IModule &module,				///< module
			const id_t configID,									///< config ID
			boost::atomic<ConfigStatus::ConfigStatus> &workerStatus				///< reference to worker status indicator
		) :	workerStatus(workerStatus), module(module), configID(configID) {}
		virtual ~CommandRecover() {}

		virtual void execute()
		{
			// is config in error mode
			if ( this->workerStatus == ConfigStatus::error )
			{
				// set status
				this->workerStatus = ConfigStatus::recovering;

				// recover config
				if ( module.recover( configID ) )
					this->workerStatus = ConfigStatus::stopped;
				else
					this->workerStatus = ConfigStatus::error;
			}
		}

	protected:
		boost::atomic<ConfigStatus::ConfigStatus> &workerStatus;
		ConnectedVision::Module::IModule& module;
		const id_t configID;
	};


	/**
	* Terminate Command
	*/
	class CommandTerminate : public ICommand {
	public:
		CommandTerminate(
			thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress,	///< reference to thread safe worker progress
			 ConnectedVision::shared_ptr<CommandStop> stopCmd										///< stop command
		) :		workerThreadProgress(workerThreadProgress), stopCmd(stopCmd) {}
		virtual ~CommandTerminate() {}

		virtual void execute()
		{
			// make sure that worker is stopped
			stopCmd->execute();

			// set termination flag
			workerThreadProgress.set( WorkerThreadProgress::TERMINATE );
		}

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress;
		ConnectedVision::shared_ptr<CommandStop> stopCmd;
	};

	/**
	* command queue for worker commands
	*/
	class CommandQueue : public ConnectedVision::thread_safe_queue< ConnectedVision::shared_ptr<WorkerCommand::ICommand> >
	{
	public:
		CommandQueue() {}
		virtual ~CommandQueue() {}

		void push(
			const ConnectedVision::shared_ptr<WorkerCommand::ICommand>& cmd	///< command to be pushed to queue
		) {
			ConnectedVision::thread_safe_queue< ConnectedVision::shared_ptr<WorkerCommand::ICommand> >::push(cmd);
		}
	};
}

class WorkerController : public IWorkerController
{
public:
	typedef boost::unique_lock<boost::mutex> Lock;

	WorkerController(		
		const id_t& configID,																///< config chain ID
		ConnectedVision::Module::IModule& module,											///< ConnectedVision module
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to stop cooperatively
	) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout), workerThreadProgress(WorkerThreadProgress::END)
	{
		if ( !workerFactory )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid workerFactory (null pointer)");
		auto configStore = this->module.getConfigStore();
		if ( !configStore )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid configStore (null pointer)");

		// load config from store
		auto config = configStore->getByID(configID);
		if ( !config )
			throw ConnectedVision::invalid_argument("[WorkerController] cannot find config with config id: " + configID);

		// init worker manager
		this->init(config);
	}

	WorkerController(		
		const Class_generic_config& configOrig,												///< config chain
		ConnectedVision::Module::IModule& module,											///< module
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to stop cooperatively
	) : module(module), workerFactory(workerFactory), workerTimeout(workerTimeout), workerThreadProgress(WorkerThreadProgress::END)
	{
		if ( !workerFactory )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid workerFactory (null pointer)");
		auto configStore = this->module.getConfigStore();
		if ( !configStore )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid configStore (null pointer)");

		// copy original config
		auto config = ConnectedVision::make_shared<Class_generic_config>( configOrig );
		
		// compute id
		config->compute_id();

		// save config to store
		auto configConst = configStore->make_const(config);
		configStore->save_const(configConst);

		// init worker manager
		this->init(configConst);
	}


	virtual ~WorkerController()
	{
		// terminate controller and worker thread
		auto stopCmd = 
			ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerStatus, this->workerThreadProgress, this->workerThread, this->workerTimeout);
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> terminateCmd = 
			ConnectedVision::make_shared<WorkerCommand::CommandTerminate>( this->workerThreadProgress, stopCmd );
		commandQueue.push( terminateCmd );
		terminateCmd.reset(); stopCmd.reset();


		// wait for the threads to terminate before destroying the class
		// (This should be done before any other clean-up of the destructor.)
		this->controllerThread.join();
		this->workerThread.join();

#ifdef CHECK_INSTANCE_SINGLETON
		// remove from instance list
		{
			Lock instanceLock(this->instanceListMutex);
			if ( this->configConst ) {
				this->instanceList.erase( this->configConst->getconst_id() );
			}
		}
#endif
	}

	/**
	* test if the worker for this config is running
	*
	* @return true if running
	*/
	bool activeWorker() const
	{
		return ( this->workerThreadProgress < WorkerThreadProgress::END );
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
		return (workerThreadProgress == WorkerThreadProgress::RUNNING);
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
			while ( this->workerThreadProgress.get() != WorkerThreadProgress::TERMINATE )
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
				this->workerThreadProgress.wait_while( WorkerThreadProgress::END );
			}
			catch (boost::thread_interrupted&)
			{
				// ignore
			}
			
			auto progress = this->workerThreadProgress.get();

			// exit if terminate flag is set
			if ( progress == WorkerThreadProgress::TERMINATE )
				break;

			if ( progress == WorkerThreadProgress::STARTING )
			{
				try
				{
					// create worker
					this->workerStatus = ConfigStatus::starting;
					auto worker = this->workerFactory->createWorker(*this, this->configConst);

					// start worker
					this->workerThreadProgress = WorkerThreadProgress::RUNNING;
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
					this->workerThreadProgress = WorkerThreadProgress::CLEANUP;
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
			this->workerThreadProgress = WorkerThreadProgress::END;
		}
	}

	/**
	* init Worker Manager
	*	- load / create status
	*/
	void init(
		ConnectedVision::shared_ptr<const Class_generic_config> config ///< config object
	)
	{
		// set config
		if ( !config )
			throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config (null pointer)");
		id_t configID = config->getconst_id();
		if ( configID.empty() )
			throw ConnectedVision::invalid_argument("[WorkerController] init(): invalid config has no ID");
		this->configConst = config;

#ifdef CHECK_INSTANCE_SINGLETON
		// make sure that we have only one instance per config
		{
			Lock instanceLock(this->instanceListMutex);
			bool insert = this->instanceList.insert(configID).second;
			if ( insert == false )
				throw ConnectedVision::runtime_error("[WorkerController] there is already an instance for config: " + IDToStr(configID) );
		}
#endif
		try
		{
			// init status variables
			commandQueue.clear();
			workerThreadProgress.set( WorkerThreadProgress::END );

			// status
			this->statusStore = this->module.getStatusStore();
			if ( !this->statusStore )
				throw ConnectedVision::invalid_argument("[WorkerController] invalid statusStore (null pointer)");

			// read status from store
			auto statusConst = this->statusStore->getByID(configID);
			if ( statusConst )
			{
				this->statusObj = statusConst->copy();
			}
			else
			{
				// create new status
				this->statusObj = boost::make_shared<Class_generic_status>(config->getconst_id(), module.getModuleID(), module.getModuleURI(), this->module.getOutputPinIDs());
				this->statusStore->save_copy( this->statusObj );
			}

			// set internal workerStatus
			if ( this->statusObj->is_status_init() )
				this->workerStatus = ConfigStatus::init;
			else if ( this->statusObj->is_status_stopped() )
				this->workerStatus = ConfigStatus::stopped;
			else if ( this->statusObj->is_status_finished() )
				this->workerStatus = ConfigStatus::finished;
			else
				this->workerStatus = ConfigStatus::error;

			// start controller thread
			this->controllerThread = boost::thread(&WorkerController::controllerThreadFunction, this);

			// start worker thread
			this->workerThread = boost::thread(&WorkerController::workerThreadFunction, this);


		}
		catch (...)
		{
#ifdef CHECK_INSTANCE_SINGLETON
			// remove from instance list
			{
				Lock instanceLock(this->instanceListMutex);
				this->instanceList.erase( configID );
			}
#endif

			// rethrow
			throw;
		}
	}

	// module
	ConnectedVision::Module::IModule& module;

	// config
	ConnectedVision::shared_ptr<const Class_generic_config> configConst;

	// status
	boost::atomic<ConfigStatus::ConfigStatus> workerStatus;
	ConnectedVision::shared_ptr<Class_generic_status> statusObj;
	ConnectedVision::shared_ptr<const Class_generic_status> statusConst;
	mutable boost::mutex statusMutex;
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > statusStore;

	// command
	WorkerCommand::CommandQueue commandQueue;
	boost::thread controllerThread;


	// worker
	thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> workerThreadProgress;
	boost::thread workerThread;
	const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory;
	timestamp_t workerTimeout;


	// config singleton
#ifdef CHECK_INSTANCE_SINGLETON
	static boost::mutex instanceListMutex;
	static std::unordered_set<id_t> instanceList;
#endif

public:
	// spy functions
	const ConfigStatus::ConfigStatus spy_workerStatus() { return this->workerStatus.load(); }
	const thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &spy_workerThreadProgress() { return this->workerThreadProgress; }


};

}} // namespace