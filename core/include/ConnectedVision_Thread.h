/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVision_Thread_def
#define ConnectedVision_Thread_def

#include <queue>
#include <map>
#include <stdexcept>
#include <boost/chrono.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>

#include <ILogging.h>
#include "ConnectedVision_Exceptions.h"


namespace ConnectedVision {


	/**
	* wrapper timeout exception
	*/
	class timeout_error : public ConnectedVision::runtime_error
	{
	public:
		timeout_error(const std::string& what_arg) : ConnectedVision::runtime_error(what_arg) {}
	};

	/**
	* wrapper exception for lock
	*/
	class mutex_error : public ConnectedVision::logic_error
	{
	public:
		mutex_error(const std::string& what_arg) : ConnectedVision::logic_error(what_arg) {}
	};

	/**
	* ordering error of a strict sequence
	*/
	class sequence_exception : public ConnectedVision::logic_error
	{
	public:
		sequence_exception(
			const std::string& what_arg	///< The string passed as what_arg has the same content as the value returned by member what().
		) : ConnectedVision::logic_error (what_arg) {}
	};

	// TODO: when changing to C++11 switched to std::mutex
	// for now, boost is used 
	typedef boost::mutex std__mutex;
	typedef boost::unique_lock<boost::mutex> std__unique_lock;
	typedef boost::condition_variable std__condition_variable;

	typedef boost::timed_mutex mutex;
	class unique_lock
	{
	public:
		static const int mutexTimeout = 100;	// mutex timeout in miliseconds
		unique_lock(ConnectedVision::mutex &mutex) : lock(mutex, boost::chrono::milliseconds(mutexTimeout))
		{
			if ( !(lock) ) throw ConnectedVision::mutex_error("mutex cannot be locked (timeout?)");
		}
		inline bool owns_lock() { return lock.owns_lock(); }

	protected:
		boost::unique_lock<ConnectedVision::mutex> lock;
	};
	typedef unique_lock Lock;


	/**
	* thread-safe wrapper for a strictly increasing data element
	* @thread-safe
	*
	* @note The underlying data type has to have an copy consturctor: T(const T&)
	* @note The underlying data type has to have an assignment operator: =
	* @note The underlying data type has to be orderable with operator: <
	*/
	template<class T>
	class thread_safe_progress
	{
	public:
		/**
		* construct and initialize
		*
		* A thread safe variable must be initialized!
		*/
		thread_safe_progress<T>(
			const T& val	///< initial value
		) : value(val), reset_count(0) {
		}

		/**
		* copy constructor
		*/
		thread_safe_progress<T>(const thread_safe_progress<T>& other) : value(other.get()), reset_count(0) {
		}

		/**
		* assignment
		*/
		thread_safe_progress<T>& operator= (const thread_safe_progress<T>& other) throw(sequence_exception) { this->set( other.get() ); }

		/**
		* assignment is a setter shortcut
		*/
		thread_safe_progress<T>& operator= (const T& val) throw(sequence_exception) { this->set(val); return *this; }

		/**
		* typecast to raw data type is a getter shortcut
		*/
		operator T() const { return this->get(); }

		/**
		* compare value
		*/
		bool operator== (T const& val)
		{
			std__unique_lock lock(this->mutex);
			bool b = (this->value == val);
			return b;
		}

		/**
		* get value (thread safe)
		* @thread-safe
		*/
		T get() const
		{
			std__unique_lock lock(this->mutex);
			T value( this->value );
			return value;
		}
	
		/**
		* reset value (thread safe)
		* @thread-safe
		*/
		void reset(
			const T& newVal	///< new value
		) {
			std__unique_lock lock(this->mutex);
			if ( newVal < this->value )
				this->reset_count++;
			this->value = newVal;
			this->cond.notify_all();
		}

		/**
		* set value (thread safe)
		* @thread-safe
		*/
		void set(
			const T& newVal	///< new value
		) throw(sequence_exception)
		{
			std__unique_lock lock(this->mutex);
			// test if new value is greater than old one
			if ( newVal < this->value )
				throw sequence_exception("thread_safe_progress::set() progress has to be strictly growing, given value was less than stored value");

			if ( this->value < newVal )
			{
				// update value
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
			const T& target,			///< state to wait for
			const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
		) const throw(sequence_exception)
		{
			// avoid pitfalls of condition variables
			// see https://www.justsoftwaresolutions.co.uk/threading/condition-variable-spurious-wakes.html
			// for a lamda function introduction
			// see http://blog.smartbear.com/c-plus-plus/c11-tutorial-lambda-expressions-the-nuts-and-bolts-of-functional-programming/

			std__unique_lock lock(this->mutex);
			if ( this->value >= target )
			{
				return true;	// the state is reached already
			}
			auto _reset_count = this->reset_count;
			if ( timeout )
			{
				return this->cond.wait_for(lock, boost::chrono::milliseconds(timeout), [&]() throw(sequence_exception) -> bool
				{ 
					if ( this->reset_count != _reset_count )
						throw sequence_exception("thread_safe_progress::wait_until() progress was reset while waiting for a given value to be reached");
					
					return (this->value >= target); 
				});
			}
			else
			{
				this->cond.wait(lock, [&]() throw(sequence_exception) -> bool
				{ 
					if ( this->reset_count != _reset_count )
						throw sequence_exception("thread_safe_progress::wait_until() progress was reset while waiting for a given value to be reached");
					
					return (this->value >= target); 
				});
				
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
			const T& state,				///< state to be checked
			const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
		) const
		{
			boost::unique_lock<boost::mutex> lock(this->mutex);
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
				this->cond.wait(lock, [&](){ return (this->value != state); });
				
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
			const T& state,				///< state to be checked
			const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
		) const
		{
			boost::unique_lock<boost::mutex> lock(this->mutex);
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

	protected:
		mutable std__condition_variable cond;
		mutable std__mutex mutex;
		T value;
		int reset_count;
	};


	/**
	* thread-safe wrapper for std::queue
	* @thread-safe
	*
	* @note The underlying data type has to have an copy consturctor: T(const T&)
	* @note The underlying data type has to have an assignment operator: =
	*/
	template<class T>
	class thread_safe_queue // : public ConnectedVision::thread_safe_progress<T>
	{
	public:
		typedef boost::unique_lock<boost::mutex> Lock;

		/**
		* default constructor
		*/
		thread_safe_queue()
		{}

		/**
		* size of queue (thread safe)
		* @thread-safe
		*
		* Returns the number of elements in the queue
		*
		* @return number of elements
		*/
		size_t size() const
		{
			std__unique_lock lock(this->mutex);
			return this->q.size();
		}

		/**
		* Test whether container is empty
		*
		* Returns whether the queue is empty: i.e. whether its size is zero.
		*/
		bool empty() const
		{
			std__unique_lock lock(this->mutex);
			return this->q.empty();
		}

		/**
		* Clear content (thread safe)
		* @thread-safe
		*
		* Removes all elements from the queue (which are destroyed), and leaving the queue with a size of 0.
		*/
		void clear()
		{
			std__unique_lock lock(this->mutex);
			while( !this->q.empty() )
			{
				this->q.pop();
			}
		}

		/**
		* Insert element (thread safe)
		* @thread-safe
		*
		* Inserts a new element at the end of the queue, after its current last element. The content of this new element is initialized to val.
		*/
		void push(
			const T& val	///< value to be pushed to queue
		)
		{
			{
				std__unique_lock lock(this->mutex);
				this->q.push(val);
			}

			cond.notify_one();
		}

		/**
		* fetch & pop element from queue (thread safe)
		* @thread-safe
		*
		* Fetches and removes the oldest element from the queue.
		* @throw exception on timeout
		*
		* @return popped value
		*/
		T pop_wait(
			const int64_t timeout = 0	///< timeout in milliseconds (default: wait for ever)
		)
		{
			std__unique_lock lock(this->mutex);

			if ( timeout )
			{
				bool filled = this->cond.wait_for(lock, boost::chrono::milliseconds(timeout), [this](){ return !this->q.empty(); });
				if ( !filled )
					throw timeout_error("pop_wait() timeout");
			}
			else
			{
				this->cond.wait(lock, [this](){ return !this->q.empty(); });
			}

			// fetch and remove element from queue
			T val = std::move(this->q.front());
			this->q.pop();

			return val;    
		}

	protected:
		mutable std__mutex mutex;
		mutable std__condition_variable cond;
		std::queue<T> q;
	};


	/**
	* thread-safe wrapper for std::map
	* @thread-safe
	*
	* @note The underlying data type has to have an copy consturctor: T(const T&)
	* @note The underlying data type has to have an assignment operator: =
	*/
	template<class Key, class T>
	class thread_safe_map
	{
	public:
		/**
		* default constructor
		*/
		thread_safe_map()
		{}

		/**
		* size of map (thread safe)
		* @thread-safe
		*
		* Returns the number of elements in the map
		*
		* @return number of elements
		*/
		size_t size() const
		{
			std__unique_lock lock(this->mutex);
			return this->q.size();
		}

		/**
		* get element in map with key k (thread safe)
		* @thread-safe
		*
		* Returns the desired element in the map with key k
		*
		* @return a copy of the queried elements
		*/
		T at (const Key& k)
		{
			std__unique_lock lock(this->mutex);
			return T(this->q.at(k));
		}

		/**
		* get element in map with key k (thread safe)
		* @thread-safe
		*
		* Returns the desired element in the map with key k
		*
		* @return a copy of the queried elements
		*/
		const T at (const Key& k) const
		{
			std__unique_lock lock(this->mutex);
			return T(this->q.at(k));
		}
		
		/**
		* insert element into map (thread safe)
		* @thread-safe
		*
		* insert element in the map with key k
		*
		* @param val Value to be copied to (or moved as) the inserted element. Member type T is the type of the elements in the container, defined in map as pair<const Key,T>
		*/
		void insert (const std::pair<Key,T>& val)
		{
			std__unique_lock lock(this->mutex);
			this->q.insert(val);
		}

		/**
		* erases an element of map (thread safe)
		* @thread-safe
		*
		* erases an element of the map with key k
		*
		* @param Key of the element to be removed from the map. Member type Key is the type of the elements in the container, defined in map as an alias of its first template parameter (the key).
		*/
		void erase (const Key& k)
		{
			std__unique_lock lock(this->mutex);
			this->q.erase(k);
		}

		/**
		* inserts or updates an element of map (thread safe) - insert if no element with key k is present, otherwise updates
		* @thread-safe
		*
		* inserts or updates an element of the map with key k
		*
		* @param val Value to be inserted or updated. Member type T is the type of the elements in the container, defined in map as pair<const Key,T>
		*/
		void insertUpdate (const std::pair<Key,T>& val)
		{
			std__unique_lock lock(this->mutex);
			typename std::map<Key,T>::iterator it = this->q.find(val.first);
			if (it != this->q.end()) // found
			{
				it->second = val.second;
			}
			else // not found
			{
				this->q.insert(val);
			}
		}

	protected:
		mutable std__mutex mutex;
		mutable std__condition_variable cond;
		std::map<Key,T> q;
	};

} // namespace scope

#endif // ConnectedVision_Thread_def
