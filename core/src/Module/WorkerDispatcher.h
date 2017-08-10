/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef WorkerDispatcher_def
#define WorkerDispatcher_def

#include <unordered_map>

#include <IConnectedVisionModule.h>

#include "WorkerThread.h"

namespace ConnectedVision {
namespace Module {

class WorkerDispatcher : public IWorkerDispatcher
{
public:

	/**
	* constructor
	*/
	WorkerDispatcher(
		const ConnectedVision::shared_ptr<IWorkerFactory> workerFactory,	///< [in] worker factory
		const timestamp_t workerStopTimeout = 5000							///< [in] timeout to wait for worker to stop, befor forcing an interrupt
	);

	/**
	* virtual destructor
	*/
    virtual ~WorkerDispatcher();

	/**
	* start the worker for a given config
	*
	* If there is already an existing worker, this function does nothing.
	*/
	virtual void start( 
		const boost::shared_ptr<const Class_generic_config> config	///< [in] config chain
	);

	/**
	* stop the worker of a specific config chain
	*/
	virtual void stop(
		const id_t& configID	///< [in] config chain ID
	);

	/**
	* get IDs of currently running workers
	*
	* @return config IDs of currently active workers
	*/
	virtual std::vector<id_t> getRunningWorkerIDs();

protected:

	/**
	* remove stopped and finished workers from thread list
	*/
	virtual void cleanupWorkerList(
		Lock& lock	///< [in] prove that the calling function has a valid lock
	);

	// worker handling
	const ConnectedVision::shared_ptr<IWorkerFactory> workerFactory;
	IConnectedVisionModule* module; 
	
	// worker thread list
	std::unordered_map<id_t, std::unique_ptr<WorkerThread> > workers;	// all worker threads are stopped when cleaning up this workers map in the destructor
	mutable ConnectedVision::mutex mutex; ///< mutex to protect read/write operations on the list of workers

	// thread handling
	const timestamp_t workerStopTimeout;
};

}} // namespace scope

#endif // WorkerDispatcher_def