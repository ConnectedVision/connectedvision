/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 

#include <unordered_set>
#include "ConnectedVision_Thread.h"
#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"
#include "DataHandling/Store_Ringbuffer.h"
#include "Module/Module_BaseClass.h"


namespace ConnectedVision {
namespace Module {

#ifndef __FUNCTION_NAME__
    #ifdef _MSC_VER   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__  
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__ 
    #endif
#endif

static std__mutex DEBUG_mutex;

//#define DEBUG(msg)	 {std::cout <<__FILE__<<"@"<< __LINE__<<": " << msg << std::endl << std::flush;}
#define DEBUG(msg)	 { std__unique_lock DEBUG_lock(DEBUG_mutex); std::cout << boost::lexical_cast<std::string>(boost::this_thread::get_id()) << "@" << std::dec << __LINE__ <<": " << msg << std::endl << std::flush;}
//#define DEBUG()
#define TEST_MUTEX {int xxx; for (xxx = 0; xxx < 10000000; xxx++) if ( this->workerThreadProgress.mutex.try_lock() ) { this->workerThreadProgress.mutex.unlock(); break; } if ( xxx == 10000000 ) DEBUG("mutex locked !!!");}

/**

http://plantuml.com/plantuml/form

@startuml

@enduml
*/

#define CHECK_INSTANCE_SINGLETON

namespace WorkerThreadProgress { 
	enum WorkerThreadProgress {Undefined, Init, Starting, Running, Stopping, Cleanup, Stopped, Finished, Error, Recovering, Resetting, Terminating, Terminated};
}	// wrap in namespace to avoid ambiguity of enums


class DEBUG_thread_safe_progress
{
public:
	/**
	* construct and initialize
	*
	* A thread safe variable must be initialized!
	*/
	DEBUG_thread_safe_progress(
		const WorkerThreadProgress::WorkerThreadProgress& val	///< initial value
	) : value(val), reset_count(0) {
// TODO		DEBUG("default constructor");
	}

	/**
	* copy constructor
	*/
	DEBUG_thread_safe_progress(const DEBUG_thread_safe_progress& other) : value(other.get()), reset_count(0) {
// TODO		DEBUG("copy constructor");
	}

	/**
	* assignment
	*/
	DEBUG_thread_safe_progress& operator= (const DEBUG_thread_safe_progress& other) throw(sequence_exception) { this->set( other.get() ); }

	/**
	* assignment is a setter shortcut
	*/
	DEBUG_thread_safe_progress& operator= (const WorkerThreadProgress::WorkerThreadProgress& val) throw(sequence_exception) { this->set(val); return *this; }

	/**
	* typecast to raw data type is a getter shortcut
	*/
	operator WorkerThreadProgress::WorkerThreadProgress() const { return this->get(); }

	/**
	* compare value
	*/
	bool operator== (WorkerThreadProgress::WorkerThreadProgress const& val)
	{
		boost::unique_lock<boost::mutex> lock(this->mutex);
		bool b = (this->value == val);
		return b;
	}

	/**
	* get value (thread safe)
	* @thread-safe
	*/
	WorkerThreadProgress::WorkerThreadProgress get() const
	{
		std__unique_lock lock(this->mutex);
		WorkerThreadProgress::WorkerThreadProgress value( this->value );
		return value;
	}
	
	/**
	* reset value (thread safe)
	* @thread-safe
	*/
	void reset(
		const WorkerThreadProgress::WorkerThreadProgress& newVal	///< new value
	) {
		DEBUG("reset lock");
		std__unique_lock lock(this->mutex);
		DEBUG("locked");
		if ( newVal < this->value )
			this->reset_count++;
		DEBUG("reset: " << newVal << " old: " << this->value);
		this->value = newVal;
		this->cond.notify_all();
	}

	/**
	* set value (thread safe)
	* @thread-safe
	*/
	void set(
		const WorkerThreadProgress::WorkerThreadProgress& newVal	///< new value
	) throw(sequence_exception)
	{
		DEBUG("set lock");
		std__unique_lock lock(this->mutex);
		DEBUG("locked");
		// test if new value is greater than old one
		if ( newVal < this->value )
			throw sequence_exception("DEBUG_thread_safe_progress::set() progress has to be strictly growing, given value was less than stored value");

		if ( newVal > this->value )
		{
			// update value
			DEBUG("set: " << newVal << " old: " << this->value);
			this->value = newVal;
			this->cond.notify_all();
		}
	}

	/**
	* wait for state to be reached (thread safe)
	* @thread-safe
	*
	* This function waits until the internal state has reached or is beond the spezified target state.
	*
	* @return true if state was reached / false on timeout
	*/
	bool wait_until(
		const WorkerThreadProgress::WorkerThreadProgress& target,			///< state to wait for
		const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
	) const throw(sequence_exception)
	{
		// avoid pitfalls of condition variables
		// see https://www.justsoftwaresolutions.co.uk/threading/condition-variable-spurious-wakes.html
		// for a lamda function introduction
		// see http://blog.smartbear.com/c-plus-plus/c11-tutorial-lambda-expressions-the-nuts-and-bolts-of-functional-programming/

		std__unique_lock lock(this->mutex);
		DEBUG("wait_until: " << target);
		if ( this->value >= target )
		{
			return true;	// the state is reached already
		}
		auto _reset_count = this->reset_count;
		if ( timeout )
		{
			// TODO change wait_for -> wait_until
			return this->cond.wait_for(lock, boost::chrono::milliseconds(timeout), [&]() throw(sequence_exception) -> bool
			{ 
				if ( this->reset_count != _reset_count )
					throw sequence_exception("DEBUG_thread_safe_progress::wait_until() progress was reset while waiting for a given value to be reached");

				DEBUG("wait_until wake: " << this->value << " >= " << target);
				return (this->value >= target); 
			});
		}
		else
		{

			this->cond.wait(lock, [&]() throw(sequence_exception) -> bool
			{ 
				//if ( this->reset_count != _reset_count )
				//	throw sequence_exception("DEBUG_thread_safe_progress::wait_until() progress was reset while waiting for a given value to be reached");
					
				DEBUG("wait_until wake: " << this->value << " > " << target);
				return (this->value >= target); 
			});

			/*
			bool cond = false;
			while(!cond)
			{
				lock.unlock();
				boost::this_thread::sleep(boost::posix_time::milliseconds(10));
				lock.lock();
				cond = (this->value >= target);
			}
			*/
			DEBUG("wait_until returned");

			return true;	// we have no timeout, so every return means that the state was reached
		}
	}

	/**
	* wait for state to change (thread safe)
	* @thread-safe
	*
	* This function waits while the internal state is equal to the given state.
	*
	* @return true if state was changed / false on timeout
	*/
	bool wait_while(
		const WorkerThreadProgress::WorkerThreadProgress& state,				///< state to be checked
		const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
	) const
	{
		DEBUG("wait_while lock");
		boost::unique_lock<boost::mutex> lock(this->mutex);
		DEBUG("wait_while: " << state);
		if ( this->value != state )
		{
			return true;	// the state is changed already
		}
		if ( timeout )
		{
			return this->cond.wait_for(lock, boost::chrono::milliseconds(timeout), [&](){ return (this->value != state); });
		}
		else
		{
			this->cond.wait(lock, [&]() -> bool{
				DEBUG("wait_while wake: " << this->value << " != " << state);
				return (this->value != state); 
			});
			DEBUG("wait_while returned");
			return true;	// we have no timeout, so every return means that the state was changed
		}
	}


	/**
	* wait for state to become a given value (thread safe)
	* @thread-safe
	*
	* This function waits while the internal state is not equal to the given state.
	*
	* @return true if state was changed / false on timeout
	*/
	bool wait_equal(
		const WorkerThreadProgress::WorkerThreadProgress& state,				///< state to be checked
		const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
	) const
	{
		boost::unique_lock<boost::mutex> lock(this->mutex);
		DEBUG("wait_equal: " << state);
		if ( this->value == state )
		{
				
			return true;	// the state is already reached
		}
		if ( timeout )
		{
			return this->cond.wait_for(lock, boost::chrono::milliseconds(timeout), [&](){ return (this->value == state); });
		}
		else
		{
			this->cond.wait(lock, [&](){ return (this->value == state); });
				
			return true;	// we have no timeout, so every return means that the state has been reached
		}
	}

// protected:
	mutable std__condition_variable cond;
	mutable std__mutex mutex;
	WorkerThreadProgress::WorkerThreadProgress value;
	int reset_count;
};



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
			DEBUG_thread_safe_progress &workerThreadProgress	///< reference to thread safe worker progress
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
		DEBUG_thread_safe_progress &workerThreadProgress;
	};

	/**
	* Stop Command
	*/
	class CommandStop : public ICommand {
	public:
		CommandStop(
			DEBUG_thread_safe_progress& workerThreadProgress,	///< reference to thread safe worker progress
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
					this->workerThread.interrupt();
				}

				// wait until cleanup has finished
				this->workerThreadProgress.wait_until(WorkerThreadProgress::Stopped);
			}
		}

	protected:
		DEBUG_thread_safe_progress& workerThreadProgress;
		boost::thread& workerThread;
		const timestamp_t workerTimeout;
	};

	/**
	* Reset Command
	*/
	class CommandReset : public ICommand {
	public:
		CommandReset(
			DEBUG_thread_safe_progress& workerThreadProgress,	///< reference to thread safe worker progress
			const ConnectedVision::shared_ptr<CommandStop> &stopCmd				///< stop command
		) :	workerThreadProgress(workerThreadProgress), stopCmd(stopCmd) {}
		virtual ~CommandReset() {}

		virtual void execute()
		{
			// make sure that worker is stopped
			this->stopCmd->execute();

			// signal to reset
			this->workerThreadProgress = WorkerThreadProgress::Resetting;

			// wait for resetting to finish
			this->workerThreadProgress.wait_while(WorkerThreadProgress::Resetting);	// expected progress: Init
		}

	protected:
		DEBUG_thread_safe_progress& workerThreadProgress;
		ConnectedVision::shared_ptr<CommandStop> stopCmd;
	};

	/**
	* Recover Command
	*/
	class CommandRecover : public ICommand {
	public:
		CommandRecover(
			DEBUG_thread_safe_progress& workerThreadProgress	///< reference to thread safe worker progress
		) :	workerThreadProgress(workerThreadProgress) {}
		virtual ~CommandRecover() {}

		virtual void execute()
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

	protected:
		DEBUG_thread_safe_progress& workerThreadProgress;
	};


	/**
	* Terminate Command
	*/
	class CommandTerminate : public ICommand {
	public:
		CommandTerminate(
			DEBUG_thread_safe_progress &workerThreadProgress,	///< reference to thread safe worker progress
			boost::atomic<WorkerThreadProgress::WorkerThreadProgress> &progressBeforeTermination, ///< reference to progress before terminate in worker controller
			const ConnectedVision::shared_ptr<CommandStop> &stopCmd										///< stop command
		) : workerThreadProgress(workerThreadProgress), progressBeforeTermination(progressBeforeTermination), stopCmd(stopCmd) {}
		virtual ~CommandTerminate() {}

		virtual void execute()
		{
			// make sure that worker is stopped
			stopCmd->execute();

			this->progressBeforeTermination = this->workerThreadProgress;

			// set termination flag
			this->workerThreadProgress = WorkerThreadProgress::Terminating;

			// wait until workerThread destructor is finished
			this->workerThreadProgress.wait_until(WorkerThreadProgress::Terminated);	// TODO: set Terminated as last action in ~WorkerThread() destructor
		}

	protected:
		DEBUG_thread_safe_progress &workerThreadProgress;
		boost::atomic<WorkerThreadProgress::WorkerThreadProgress> &progressBeforeTermination;
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
		// init worker manager
		this->init(configID);
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
		this->init(config->getconst_configID());
	}


	virtual ~WorkerController()
	{
// TODO		DEBUG("<enter>");
		// terminate controller and worker thread
		auto stopCmd = ConnectedVision::make_shared<WorkerCommand::CommandStop>( this->workerThreadProgress, this->workerThread, this->workerTimeout );
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> terminateCmd = ConnectedVision::make_shared<WorkerCommand::CommandTerminate>( this->workerThreadProgress, this->progressBeforeTermination, stopCmd );
		commandQueue.push( terminateCmd );
// TODO		DEBUG("terminateCmd enqued");

		// wait for the threads to terminate before destroying the class
		// (This should be done before any other clean-up of the destructor.)
// TODO		DEBUG("workerThread joining ...");
		this->workerThread.join();
// TODO		DEBUG("controllerThread joining ...");
		this->controllerThread.join();

		// remove from instance list
// TODO		DEBUG("unregisterWorkerInstance");
		this->module.unregisterWorkerInstance(this->configID, this);

// TODO		DEBUG("<exit>");
	}

	/**
	* test if the worker for this config is running
	*
	* @return true if running
	*/
	bool activeWorker() const
	{
		auto progress = this->workerThreadProgress.get();
		bool active = progress >= WorkerThreadProgress::Starting && progress < WorkerThreadProgress::Stopped;
		return ( active );
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
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdStart = ConnectedVision::make_shared<WorkerCommand::CommandStart>(this->workerThreadProgress);
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
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdStop = ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerThreadProgress, this->workerThread, this->workerTimeout);
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
		// enqueue reset command
		auto cmdStop = ConnectedVision::make_shared<WorkerCommand::CommandStop>(this->workerThreadProgress, this->workerThread, this->workerTimeout);
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdReset = ConnectedVision::make_shared<WorkerCommand::CommandReset>(this->workerThreadProgress, cmdStop);
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
		// enqueue recover command
		ConnectedVision::shared_ptr<WorkerCommand::ICommand> cmdRecover = ConnectedVision::make_shared<WorkerCommand::CommandRecover>(this->workerThreadProgress);
		commandQueue.push( cmdRecover );

		return this->getStatus();
	}

	/**
	* get status of config chain
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> getStatus()
	{
		// get status and current status according to worker progress
		auto statusConst = this->statusStore->getByID(this->configID);
		auto status = statusConst->copy();
		auto statusProgress = this->getStatusFromProgress();

		// return directly if status didn't change
		if ( status->is_status( statusProgress ) )
			return statusConst;

		// update according to worker progress
		status->set_status( statusProgress );
		
		// save status and return
		statusConst = this->statusStore->make_const( status );
		this->statusStore->save_const( statusConst );
		return statusConst;
	}

	/**
	* get current config
	*
	* @returns current config
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_config> getConfig()
	{
		return this->configStore->getByID(this->configID);
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
		// for now, there is nothing else to do than just check if we are not stopped
		return intermediateContinueCheck();
	}


protected:

	void controllerThreadFunction()
	{
		try
		{
			DEBUG("controllerThreadFunction");
			// loop until destructor sets terminate flag
			while ( this->workerThreadProgress < WorkerThreadProgress::Terminating )
			{
				// wait for new command in queue
				auto cmd = this->commandQueue.pop_wait();

				// execute command
				TEST_MUTEX;
				cmd->execute();
				TEST_MUTEX;
			}
		}
		catch (std::exception e)
		{
			// TODO Log exception
			std::cout << "CORE PANIC: [Exception in controller thread command] " << e.what();

			// terminate to worker
			this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
			this->workerThread.interrupt();
			return;
		}
	}

	void workerThreadFunction()
	{
		// TODO in workerThread class: make sure that workerThread / Cleanup is not interrupted (-> boost::this_thread::disable_interruption di;)
		boost::this_thread::disable_interruption interrupt_disabler;

		// thread loop
		DEBUG("workerThreadFunction");
		for(;;)
		{
			bool error = false;
TEST_MUTEX;
			auto progress = this->workerThreadProgress.get();
			DEBUG("got: " << progress);
TEST_MUTEX;			switch (progress)
			{
				case WorkerThreadProgress::Undefined:
				case WorkerThreadProgress::Init:
				case WorkerThreadProgress::Stopped:
				case WorkerThreadProgress::Finished:
				case WorkerThreadProgress::Error:
					// ignore and wait for next progress
					break;

				case WorkerThreadProgress::Terminating:
				case WorkerThreadProgress::Terminated:
					// exit if terminate flag is set
					progress = WorkerThreadProgress::Terminated; this->workerThreadProgress = progress; // update internal progress and set workerThreadProgress
					return;

				case WorkerThreadProgress::Starting:
					try
					{
						DEBUG("createWorker");
TEST_MUTEX;			
						// create worker
						auto worker = this->workerFactory->createWorker(*this, this->getConfig());
						DEBUG("worker created");
TEST_MUTEX;						// start worker
						try
						{
TEST_MUTEX;
							this->workerThreadProgress = WorkerThreadProgress::Running;
TEST_MUTEX;
							DEBUG("interrupt_enabler");
							boost::this_thread::restore_interruption interrupt_enabler(interrupt_disabler);
							DEBUG("run");
							worker->run();
						}
						catch (boost::thread_interrupted e)
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


						// set status
						if ( error )
							progress = WorkerThreadProgress::Error;
						else if ( stopped )
							progress = WorkerThreadProgress::Stopped;
						else
							progress = WorkerThreadProgress::Finished;
						this->workerThreadProgress = progress;

					}
					catch (std::exception e)
					{
						// TODO Log exception
						std::cout << "CORE PANIC: [Exception in controller thread command] " << e.what();

						// terminate
						this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
						return;
					}
					break;


				case WorkerThreadProgress::Resetting:
					// reset config / delete all data of config
					module.deleteAllData( this->configID );	// one thread (workerThread) is writing / deleting data
					progress = WorkerThreadProgress::Init; this->workerThreadProgress.reset(progress); // update internal progress and (re)set workerThreadProgress
					break;

				case WorkerThreadProgress::Recovering:
					// recover config
					if ( this->module.processConfigRecover( this->configID ) ) 	// one thread (workerThread) is writing / deleting data
						progress = WorkerThreadProgress::Stopped;
					else
						progress = WorkerThreadProgress::Error;
					this->workerThreadProgress.reset(progress); // update internal progress and (re)set workerThreadProgress
					break;


				default:
					std::cout << "CORE PANIC: [worker thread] unexpected worker progress in thread loop: " << progress;
					this->workerThreadProgress.reset(WorkerThreadProgress::Terminated);
					return;
			}

TEST_MUTEX;

			// wait on change of worker progress
			this->workerThreadProgress.wait_while(progress);

TEST_MUTEX;
		}
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
		id_t configID ///< config ID
	)
	{
		// intentional set to error: if progressBeforeTermination is used in getStatusFromProgress() before it is set in CommandTerminate execute()
		progressBeforeTermination = WorkerThreadProgress::Error;

		if ( !this->workerFactory )
			throw ConnectedVision::invalid_argument("[WorkerController] invalid workerFactory (null pointer)");

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

		// start worker thread
		this->workerThread = boost::thread(&WorkerController::workerThreadFunction, this);

		// notify module about new worker instance
		this->module.registerWorkerInstance(this->configID, this); // TODO module ->	throw ConnectedVision::runtime_error("[WorkerController] there is already an instance for config: " + IDToStr(configID) );
		DEBUG("init finished");
	}

	// module
	ConnectedVision::Module::IModule& module;

	// config
	id_t configID;
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > configStore;

	// status
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > statusStore;

	// command
	WorkerCommand::CommandQueue commandQueue;
	boost::thread controllerThread;


	// worker
	DEBUG_thread_safe_progress workerThreadProgress;
	boost::thread workerThread;
	const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory;
	timestamp_t workerTimeout;


public:
	// spy functions
	const DEBUG_thread_safe_progress &spy_workerThreadProgress() { return this->workerThreadProgress; }

	boost::atomic<WorkerThreadProgress::WorkerThreadProgress> progressBeforeTermination;

};


}} // namespace