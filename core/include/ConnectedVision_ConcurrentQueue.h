/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVision_ConcurrentQueue_def
#define ConnectedVision_ConcurrentQueue_def

#include <queue>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include "ConnectedVision_Thread.h"

namespace ConnectedVision {

	/**
	* thread-safe wrapper for std::queue
	*
	* see https://www.justsoftwaresolutions.co.uk/threading/implementing-a-thread-safe-queue-using-condition-variables.html
	*/
	template<class T>
	class ConcurrentQueue
	{
	public:
		/**
		* Insert element
		*
		* Inserts a new element at the end of the queue, after its current last element.
		*/
		void push(
			T const& data	///< element to append to queue
		)
		{
			boost::unique_lock<boost::mutex> lock(this->mutex);
			this->queue.push(data);
			this->cond.notify_one();
		}

		/**
		* Test whether container is empty
		*
		* Returns whether the queue is empty: i.e. whether its size is zero.
		*/
		bool empty() const
		{
			boost::unique_lock<boost::mutex> lock(this->mutex);
			return this->queue.empty();
		}

		/**
		* wait until there is at least one element in the queue and fetch it
		*
		* Removes the next element in the queue, effectively reducing its size by one.
		* The element removed is the "oldest" element in the queue whose value can be retrieved by calling member queue::front.
		*/
		bool pop_wait(
			T& data,					///< reference to return data
			const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
		)
		{
			boost::unique_lock<boost::mutex> lock(this->mutex);
			if ( timeout )
			{
				if ( !this->cond.wait_for(lock, boost::chrono::milliseconds(timeout), [this](){ return !this->queue.empty(); }) )
					return false;
			}
			else
			{
				this->cond.wait(lock, [this](){ return !this->queue.empty(); });
			}

			// fetch element from queue
			data = this->queue.front();
			this->queue.pop();

			return true;
		}

	protected:
		mutable boost::mutex mutex;
		std::queue<T> queue;
		boost::condition_variable cond;
	};

} // namespace scope

#endif // ConnectedVision_ConcurrentQueue_def
