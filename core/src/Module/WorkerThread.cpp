/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "WorkerThread.h"

namespace ConnectedVision {
namespace Module {

WorkerThread::WorkerThread(		
	const ConnectedVision::shared_ptr<IWorkerFactory> workerFactory,
	const ConnectedVision::shared_ptr<const Class_generic_config> config,
	const timestamp_t workerTimeout
) :  workerFactory(workerFactory), config(config), workerTimeout(workerTimeout),
		setState(ThreadState::Init), currentState(ThreadState::Init)
{
	if ( !workerFactory )
		throw ConnectedVision::invalid_argument("[WorkerThread] workerFactory is NULL");
	if ( workerTimeout <= 0 )
		throw ConnectedVision::invalid_argument("[WorkerThread] workerTimeout is 0");

	// start thread
	// (This should always be the last line in the constructor.)
	this->thread = boost::thread(&WorkerThread::threadFunction, this);

	// wait for thread to start
	this->currentState.wait_until(ThreadState::Startup, this->workerTimeout);
}

WorkerThread::~WorkerThread()
{
	// nicely request the worker to stop
	this->stop_async();

	// wait for the thread to terminate before destroying the class
	// (This should be done before any other clean-up of the destructor.)
	this->thread.join();

	// clean up stop Watchdog
	this->stopWatchdog.join();
}

void WorkerThread::stop_async()
{
	try
	{
		// try to set setState to Stopping
		this->setState = ThreadState::Stopping;

		// start a stop watchdog thread
		Lock lock(this->stopWatchdogMutex);
		if ( !this->stopWatchdog.joinable() )
			this->stopWatchdog = boost::thread(&WorkerThread::stopWatchdogFunction, this);
	}
	catch (ConnectedVision::sequence_exception&)
	{
		// this exception is OK
		// worker is already stopped -> setState is advanced of Stopping, so never mind
	}
}

void WorkerThread::stop_wait()
{
	// send async stop wignal
	this->stop_async();

	// wait for worker to stop
	this->currentState.wait_until(ThreadState::Stopped);
}

bool WorkerThread::intermediateContinueCheck() const
{
	return (this->setState < ThreadState::Stopping);
}

bool WorkerThread::nextIterationStep()
{
	bool go = this->intermediateContinueCheck();

	// set current thread state to shutdown implicitly
	try
	{
		if ( !go )
			this->currentState = ThreadState::Stopping;
	}
	catch (ConnectedVision::sequence_exception&) { /* ignore sequence error at this point */ }
	
	return go;
}

bool WorkerThread::isRunning() const
{
	auto state = this->currentState.get();
	bool running = (state >= ThreadState::Startup) && (state <= ThreadState::Stopping);
	return running;

#if 0 
	// This code snipped does not require an intrusive running variable,
	// but it is not suitable for a const function since try_join_for()
	// counts as write access.
	bool finished = this->thread.try_join_for( boost::chrono::milliseconds(0) );
	if ( !finished )
	{
		bool running = this->thread.joinable();
		return running;
	}
	return !finished;
#endif
}

void WorkerThread::threadFunction()
{
	std::unique_ptr<IWorker> worker;

	// wrap the thread functionality in a try-catch block
	try
	{
		this->setState = ThreadState::Startup;
		this->currentState = ThreadState::Startup;

		worker = this->workerFactory->createWorker(*this, config);
	}
	catch (ConnectedVision::sequence_exception&) { /* ignore sequence error at this point */  }

	// check that worker was created successfully
	if ( !worker )
	{
		try	{ this->currentState = ThreadState::Error; }
		catch (ConnectedVision::sequence_exception&) { /* ignore sequence error at this point */ }
		return;
	}

	try
	{

		this->setState = ThreadState::Running;
		this->currentState = ThreadState::Running;

		// actually run worker
		worker->run();

		if ( this->setState == ThreadState::Running )
			this->currentState = ThreadState::Finished;
		else
			this->currentState = ThreadState::Stopped;
	}
	catch (boost::thread_interrupted&)
	{
		// thread was interrupted, this is expected
		try	{ this->currentState = ThreadState::Interrupt; }
		catch (ConnectedVision::sequence_exception&) { /* ignore sequence error at this point */ }
	}
	catch (ConnectedVision::sequence_exception&)
	{
		// error in thread state sequence, so worker was stopped
		try	{ this->currentState = ThreadState::Stopped; }
		catch (ConnectedVision::sequence_exception&) { /* ignore sequence error at this point */ }
	}
	catch (std::exception&)
	{
		// an unhandled exception reached this point, this constitutes an error
		try	{ this->currentState = ThreadState::Error; }
		catch (ConnectedVision::sequence_exception&) { /* ignore sequence error at this point */ }
	}
}

void WorkerThread::stopWatchdogFunction()
{
	try
	{
		// wait for timeout and send an interrupt to worker thread
		if ( this->currentState.wait_until(ThreadState::Stopped, this->workerTimeout) )
		{
			// the worker thread was kind enought to stop before we need to force it
			// we are finished
		}
		else
		{
			// force worker to stop -> send interrupt
			// send interrupt to thread
			this->thread.interrupt();
		}
	}
	catch (...)
	{
		// ignore all exceptions and interrupts
	}
}


}} // namespace scope
