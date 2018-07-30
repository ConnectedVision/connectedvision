/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/thread/thread.hpp>
#include <boost/thread/thread_guard.hpp> 
#include <boost/date_time/posix_time/posix_time.hpp>

#include <unordered_set>
#include "ConnectedVision_Thread.h"
#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"
#include "DataHandling/Store_Ringbuffer.h"
#include "Module/Module_BaseClass.h"

#ifndef WorkerController_def
#define WorkerController_def

namespace ConnectedVision {
namespace Module {


#define CHECK_INSTANCE_SINGLETON

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
		virtual void execute();

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
		virtual void execute();

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
			const ConnectedVision::shared_ptr<CommandStop> &stopCmd				///< stop command
		) :	workerThreadProgress(workerThreadProgress), stopCmd(stopCmd) {}
		virtual ~CommandReset() {}
		virtual void execute();

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress>& workerThreadProgress;
		ConnectedVision::shared_ptr<CommandStop> stopCmd;
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
		virtual void execute();

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
			const ConnectedVision::shared_ptr<CommandStop> &stopCmd										///< stop command
		) : workerThreadProgress(workerThreadProgress), progressBeforeTermination(progressBeforeTermination), stopCmd(stopCmd) {}
		virtual ~CommandTerminate() {}
		virtual void execute();

	protected:
		thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> &workerThreadProgress;
		boost::atomic<WorkerThreadProgress::WorkerThreadProgress> &progressBeforeTermination;
		ConnectedVision::shared_ptr<CommandStop> stopCmd;
	};

	/**
	* command queue for worker commands
	*/
	typedef ConnectedVision::thread_safe_queue< ConnectedVision::shared_ptr<WorkerCommand::ICommand> > CommandQueue;
}

class WorkerController : public IWorkerControllerCallbacks
{
public:
	typedef boost::unique_lock<boost::mutex> Lock;

	/**
		constructor for existing config, access by configID
	*/
	WorkerController(		
		const id_t &configID,																///< config chain ID
		ConnectedVision::Module::IModule &module,											///< ConnectedVision module
		ConnectedVision::Module::IWorkerFactory &workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to stop cooperatively
	);

	/**
		constructor for new config, config(-chain) is saved to data store
	*/
	WorkerController(		
		const Class_generic_config &configOrig,												///< config chain
		ConnectedVision::Module::IModule &module,											///< module
		ConnectedVision::Module::IWorkerFactory &workerFactory,	///< worker factory
		const timestamp_t workerTimeout = 5000												///< timeout to wait for worker to stop cooperatively
	);

	virtual ~WorkerController();


	/**
	* test if the worker for this config is running
	*
	* @return true if running
	*/
	bool activeWorker() const;

	/**
	* start the worker for a given config
	*
	* If there is already an existing worker, this function does nothing.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> start();

	/**
	* stop the worker of a specific config chain, if the config is running
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> stop();
	
	/**
	* resets the current config
	*
	* If the config is running, it is stopped in advance.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> reset();

	/**
	* revocer the current config
	*
	* Only configs in error state can be recovered.
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> recover();

	/**
	* get status of config chain
	*
	* @returns current config status
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_status> getStatus();

	/**
	* get current config
	*
	* @returns current config
	*/
	virtual ConnectedVision::shared_ptr<const Class_generic_config> getConfig();

	/**
	* get current config ID
	*
	* @returns current config ID
	*/
	const id_t getConfigID() const { return this->configID; }


	/**
	* get shared pointer to active worker
	* @warning may return NULL pointer
	* @warning Caller must take care of synchronization on his own, when using this pointer!
	*
	* This function will return a pointer for currently running workers only.
	* -> If workerThreadProgress is "Running" one can expect a valid worker pointer.
	*
	* @returns active worker
	*/
	ConnectedVision::shared_ptr<ConnectedVision::Module::IWorker> getWorker() const { return this->worker; }


	// IWorkerControllerCallbacks

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
	virtual bool intermediateContinueCheck() const;

	/**
	* Inform the worker controller that one computation iteration step (e.g. frame) has been finished,
	* and ask to continue with the next computation.
	*
	* @note This function has to be thread-safe!
	*
	* @return true if worker should continue
	*/
	virtual bool nextIterationStep();


protected:

	void controllerThreadFunction();

	void workerThreadFunction();

	shared_ptr<const Class_generic_config> saveConfig(
		const Class_generic_config& configOrig,												///< config chain
		ConnectedVision::Module::IModule& module											///< module
	);


	/**
	* init Worker Manager
	*	- load / create status
	*/
	void init(
		id_t configID ///< config ID
	);

	/**
	* maps worker progress to config status
	*
	* @return config status string
	*/
	static const boost::shared_ptr<std::string> mapProgressToStatus(WorkerThreadProgress::WorkerThreadProgress progress);

	/**
	* maps config status to worker progress
	*
	* @return worker progress
	*/
	static const WorkerThreadProgress::WorkerThreadProgress mapStatusToProgress(ConnectedVision::shared_ptr<Class_generic_status> status);

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
	boost::shared_ptr<boost::thread_guard<boost::interrupt_and_join_if_joinable>> controllerThreadGuard;

	// worker
	thread_safe_progress<WorkerThreadProgress::WorkerThreadProgress> workerThreadProgress;
	boost::thread workerThread;
	boost::shared_ptr<boost::thread_guard<boost::interrupt_and_join_if_joinable>> workerThreadGuard;

	ConnectedVision::Module::IWorkerFactory &workerFactory;
	timestamp_t workerTimeout;
	boost::atomic<WorkerThreadProgress::WorkerThreadProgress> progressBeforeTermination;
	ConnectedVision::shared_ptr<ConnectedVision::Module::IWorker> worker;
};


}} // namespace

#endif // WorkerController_def