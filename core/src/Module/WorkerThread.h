/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef WorkerThread_def
#define WorkerThread_def

#include <ConnectedVision_Thread.h>
#include <IConnectedVisionModule.h>

namespace ConnectedVision {
namespace Module {

namespace ThreadState { 
	enum ThreadState {NA = 0, Init, Startup, Running, Stopping, Stopped, Interrupt, Finished, Error}; 
	static std::string toString(const ThreadState &state)
	{
		static const char* ThreadStateName[] = {"NA", "Init", "Startup", "Running", "Stopping", "Stopped", "Interrupt", "Finished", "Error"};
		return std::string(ThreadStateName[state]);
	}
}	// wrap in namespace to avoid ambiguity of enums

/**

The WorkerThread class is responsible for wrapping and executing the Worker in a dedicated thread:
 - create a thread for the worker
 - construct the actual worker instance
 - run the worker
 - synchronication between worker (thread) and module (thread)
 - error handling
 
@note used patterns:
 - MEDIATOR between worker and module -> to avoid threading problems



http://plantuml.com/plantuml/form

@startuml

title worker life-cycle \n

participant ":WorkerThread \n <<IWorkerController>>" as WorkerThread
box "\nthread"
participant "thread function" as thread
participant ":Worker \n <<IWorker>>" as Worker
end box
participant ":WorkerFactory \n <<IWorkerFactory>>" as WorkerFactory
participant "stop watchdog" as watchdog

legend
The color coding is used to indicate in which thread a function is executed.
endlegend

== create WorkerThread ==

 -> WorkerThread : <<create>>
activate WorkerThread
rnote right WorkerThread : setState = Init\ncurrentState = Init
create thread
WorkerThread --> thread : create thread()
activate thread #orange
hnote right WorkerThread: wait_until(currentState::Startup)
rnote over thread : setState = Startup\ncurrentState = Startup
WorkerThread <-- thread : currentState::Startup
 <<- WorkerThread
deactivate WorkerThread

thread -> WorkerFactory : createWorker(&WorkerThread)
deactivate thread
activate WorkerFactory #orange
create Worker
WorkerFactory -> Worker : <<create>>(&WorkerThread)
deactivate WorkerFactory
activate Worker #orange
|||
WorkerFactory <<- Worker
deactivate Worker
activate WorkerFactory #orange
thread <<- WorkerFactory 
deactivate WorkerFactory 
activate thread #orange

rnote over  thread : setState = Running\ncurrentState = Running
thread -> Worker : run()
deactivate thread 
activate Worker #orange
|||
...

== finished Worker ==
|||
Worker -> WorkerThread: nextIterationStep()
activate WorkerThread #orange
Worker <<- WorkerThread: true
deactivate WorkerThread
...
thread <<- Worker
deactivate Worker
activate thread #orange
note over thread : setState is Running
rnote over thread : currentState = Finished
WorkerThread <-- thread : currentState::Finished
deactivate thread
...

== stop Worker <wait> ==
Worker \\--]
activate Worker #orange
|||
 -> WorkerThread : stop_wait
activate WorkerThread
WorkerThread -> WorkerThread : stop_async()
activate WorkerThread
note right WorkerThread: see stop Worker <async>\n(setState = Stopping)
WorkerThread <<- WorkerThread
deactivate WorkerThread
hnote right WorkerThread: wait_until(currentState::Stopped)
...
thread <<- Worker
deactivate Worker
activate thread #orange
WorkerThread <-- thread : currentState::Stopped
deactivate thread
 <<- WorkerThread
deactivate WorkerThread
...

== stop Worker <async> ==
Worker \\--]
activate Worker #orange
|||
 -> WorkerThread : stop_async
activate WorkerThread
rnote right WorkerThread : setState = Stopping
create watchdog
WorkerThread --> watchdog: start watchdog
activate watchdog #red
 <<- WorkerThread
deactivate WorkerThread
...
alt cooperative worker
hnote over watchdog: wait_until(currentState::Stopped)
Worker -> WorkerThread: nextIterationStep()
activate WorkerThread #orange
note right WorkerThread : setState is Stopping
rnote right WorkerThread : currentState = Stopping
Worker <<- WorkerThread: false
deactivate WorkerThread
note right Worker : stop worker cooperatively
thread <<- Worker
deactivate Worker
activate thread #orange
note over thread : setState is not Running
rnote over thread : currentState = Stopped
thread --> watchdog : currentState::Stopped
WorkerThread <-- thread : currentState::Stopped
deactivate watchdog
deactivate thread
|||
else uncooperative worker
Worker \\--]
activate Worker #orange
activate watchdog #red
|||
note over watchdog: watchdog timeout
watchdog --> Worker : <<interrupt>>
note right Worker: forced stop
deactivate watchdog
thread <<- Worker: <<interrupt exception>>
deactivate Worker
activate thread #orange
rnote over thread : currentState = Interrupt
WorkerThread <-- thread : currentState::Interrupt
deactivate thread
|||
end
...

== exception in Worker ==
Worker \\--]
activate Worker #orange
|||
Worker --> Worker : <<exception>>
thread <<- Worker : <<exception>>
deactivate Worker
activate thread #orange
rnote over thread : currentState = Error
WorkerThread <-- thread : currentState::Error
deactivate thread
|||
...

== destroy WorkerThread ==
 -> WorkerThread : <<destroy>>
activate WorkerThread
WorkerThread -> WorkerThread : stop_async()
activate WorkerThread
note right WorkerThread: see stop Worker <async>
WorkerThread <<- WorkerThread
deactivate WorkerThread
WorkerThread -> thread : <<join>>
activate thread #orange
thread -> Worker : <<destroy>
activate Worker #orange
thread <<- Worker
destroy Worker
WorkerThread <<- thread
destroy thread
WorkerThread -> watchdog : <<join>>
activate watchdog #red
WorkerThread <<- watchdog
destroy watchdog 
|||

 <<- WorkerThread
destroy WorkerThread

@enduml
*/

class WorkerThread : IWorkerControllerCallbacks
{
public:
	typedef ThreadState::ThreadState ThreadState;

	/**
	* constructor <async>
	*
	* Start a new thread for the worker. 
	* The thread will automatically create a new worker and calls the run() function.
	*/
	WorkerThread(		
		const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory,	///< [in] worker factory
		const ConnectedVision::shared_ptr<const Class_generic_config> config,		///< [in] config for worker
		const timestamp_t workerTimeout = 5000										///< timeout to wait for worker to 
																					///		- start a new thread 
																					///		- stop, before forcing an interrupt
	);

	/** 
	* desctuctor 
	* Stops the worker thread and waits until the worker thread is destroyed.
	*/
	~WorkerThread();

	/**
	* send stop signal to worker <async>
	* Force worker to stop after workerTimeout.
	*/
	void stop_async();

	/**
	* send stop signal to worker and wait until worker has stopped
	* Force worker to stop after workerTimeout.
	*/
	void stop_wait();

	/**
	* test if the worker is still running 
	* @note The thread may still be active before and after the worker is actually running.
	*
	* @return true if running
	*/
	bool isRunning() const;

	/**
	* wait until current thread state has reached the specified state
	*
	* @return true if state was reached / false on timeout
	*/
	inline bool wait_until(
		const thread_safe_progress<ThreadState>& target,	///< state to wait for
		const int64_t timeout = 0		///< timeout in milliseconds (default: wait for ever)
	) const
	{
		return this->currentState.wait_until(target, timeout);
	}

	/**
	* get current thread state
	*/
	inline const thread_safe_progress<ThreadState>& getCurrentState() const
	{
		return this->currentState;
	}

	/**
	* get target thread state
	*/
	inline const thread_safe_progress<ThreadState>& getSetState() const
	{
		return this->setState;
	}

	/**
	* should the worker continue running
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

	/**
	* thread main function
	*
	* - create the actual worker instance (ThreadState::Startup)
	* - call worker run() (ThreadState::WorkerRunning)
	*
	*/
	void threadFunction();

	// worker handling
	const ConnectedVision::shared_ptr</* TODO const */IWorkerFactory> workerFactory;
	const ConnectedVision::shared_ptr<const Class_generic_config> config;

	// actual thread
	boost::thread thread;
	
	// thread state
	thread_safe_progress<ThreadState> setState;
	thread_safe_progress<ThreadState> currentState;

	// thread handling
	const timestamp_t workerTimeout;

	// stop watchdog
	typedef boost::unique_lock<boost::mutex> Lock;
	boost::thread stopWatchdog;
	boost::mutex stopWatchdogMutex;
	void stopWatchdogFunction();
};

}} // namespace scope

#endif // WorkerThread_def