/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "WorkerDispatcher.h"

namespace ConnectedVision {
namespace Module {


WorkerDispatcher::WorkerDispatcher(
		const ConnectedVision::shared_ptr<IWorkerFactory> workerFactory,	///< [in] worker factory
		const timestamp_t workerStopTimeout									///< [in] timeout to wait for worker to stop, befor forcing an interrupt
) : workerFactory(workerFactory), workerStopTimeout(workerStopTimeout)
{
	if ( !workerFactory )
		throw ConnectedVision::invalid_argument("[WorkerDispatcher] workerFactory is NULL");

}

WorkerDispatcher::~WorkerDispatcher()
{
}

void WorkerDispatcher::start( 
	const boost::shared_ptr<const Class_generic_config> config	///< [in] config chain
)
{
	Lock lock(this->mutex);

	// check if we have this config already in the worker list
	if ( this->workers.find( config->getconst_id() ) != this->workers.end() )
	{
		// nothing to do
		return;
	}

	// create and start new worker thread
	std::unique_ptr<WorkerThread> worker( new WorkerThread(this->workerFactory, config, workerStopTimeout) );
		
	// add worker to worker thread list
	this->workers.insert( std::make_pair( config->getconst_id(), std::move(worker) ) );

	// remove not running workers
	cleanupWorkerList(lock);
}


void WorkerDispatcher::stop(
	const id_t& configID	///< [in] config chain ID
)
{ 
	Lock lock(this->mutex);

	// check if we have this config already in the worker list
	auto it = this->workers.find( configID );
	if ( it == this->workers.end() )
	{
		// nothing to do
		return;
	}

	// send stop to worker thread;
	auto& workerThread = workers.begin()->second;
	workerThread->stop_async();

	// remove not running workers
	cleanupWorkerList(lock);
}

std::vector<id_t> WorkerDispatcher::getRunningWorkerIDs()
{ 
	Lock lock(this->mutex);

	// remove not running workers
	cleanupWorkerList(lock);

	// build id List
	std::vector<id_t> idList;
	for(auto it = this->workers.cbegin(); it != this->workers.cend(); ++it)
	{
		if ( it->second->isRunning() )
			idList.push_back( it->first );
	}

	return idList;
}

void WorkerDispatcher::cleanupWorkerList(
	Lock& lock	///< [in] prove that the calling function has a valid lock
)
{ 
#if _DEBUG
	if ( !lock.owns_lock() )
		throw ConnectedVision::logic_error("[WorkerDispatcher] worker list is expected to be locked");
#endif

	// walk through worker list
	for(auto next = this->workers.cbegin(); next != this->workers.cend();)
	{
		auto it = next;
		next++;
		if ( it->second->getCurrentState() > ThreadState::Stopping )
		{
			// remove from worker list
			this->workers.erase(it);
		}
	}
}

}} // namespace scope
