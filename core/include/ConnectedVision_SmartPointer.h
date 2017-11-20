/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVision_SmartPointer_def
#define ConnectedVision_SmartPointer_def

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include "ConnectedVision_Exceptions.h"

namespace ConnectedVision { 
	/**
	* exception indicating the use of a wrong reference (e.g. NULL pointer)
	*/
	typedef ConnectedVision::runtime_error illegal_reference;

	/**
	* ConnectedVision shared pointer wrapper
	*/
	template <class T>
	class shared_ptr : public boost::shared_ptr<T>
	{
	public:
		/** 
		* default constructor
		*/
		shared_ptr() : boost::shared_ptr<T>() {}
		/** 
		* initialization constructor
		*/
		shared_ptr(T *ptr) : boost::shared_ptr<T>(ptr) {}
		/**
		* copy constructor
		*/
		shared_ptr(
			const shared_ptr<T>& other	///< [in] object to be copied
		) : boost::shared_ptr<T>(other) {}
		/**
		* copy constructor
		*/
		shared_ptr(
			const boost::shared_ptr<T>& other	///< [in] object to be copied
		) : boost::shared_ptr<T>(other) {}
		/**
		* move constructor
		*/
		shared_ptr(
			shared_ptr<T>&& other	///< [in] object to be moved
		) : boost::shared_ptr<T>(std::move(other)) {}
		/**
		* virtual destructor
		*/
		virtual ~shared_ptr() {};
		/**
		* dereferencing with NULL pointer check
		*/
		T* operator->() const {
			if ( this->get() == NULL )
				throw illegal_reference("pointer is NULL");
			return boost::shared_ptr<T>::operator->();
		}
		/**
		* copy assignment operator
		*/
		shared_ptr& operator=(
			const shared_ptr<T>& other	///< [in] object to be moved
		) {			
			shared_ptr<T> tmp(other); // re-use copy-constructor
			*this = std::move(tmp); // re-use move-assignment
			return *this;
		}
		/**
		* copy assignment operator
		*/
		shared_ptr& operator=(
			const boost::shared_ptr<T>& other	///< [in] object to be moved
		) {			
			boost::shared_ptr<T> tmp(other); // re-use copy-constructor
			*this = std::move(tmp); // re-use move-assignment
			return *this;
		}
		/**
		* move assignment operator
		*/
		shared_ptr& operator=(
			shared_ptr<T>&& other	///< [in] object to be moved
		) {
			if (this != &other)
			{
				boost::shared_ptr<T>::operator=( std::move(other) );
			}
			return *this;			
		}
		/**
		* move assignment operator
		*/
		shared_ptr& operator=(
			boost::shared_ptr<T>&& other	///< [in] object to be moved
		) {
			if (this != &other)
			{
				boost::shared_ptr<T>::operator=( std::move(other) );
			}
			return *this;			
		}

	};

	/**
	* Create object within shared pointer
	*
	* @TODO: efficient implementation of make_shared() 
	*		- avoid memory leaks (e.g. from exceptions in constructor)
	*		- combine allocation of the shared object and the object's descriptor into just one allocation
	*/
	template<class T>
	shared_ptr<T> make_shared()
	{
		T* obj = NULL;
		try
		{
			obj = new T();
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A>
	shared_ptr<T> make_shared(const A &a1)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A1>
	shared_ptr<T> make_shared(A1 &a1)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A, typename A2>
	shared_ptr<T> make_shared(const A &a1, A2 &&a2)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1, a2);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A1, typename A2>
	shared_ptr<T> make_shared(A1 &&a1, A2 &&a2)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1, a2);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A, typename A2, typename A3>
	shared_ptr<T> make_shared(const A &a1, A2 &&a2, A3 &&a3)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1, a2, a3);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A1, typename A2, typename A3>
	shared_ptr<T> make_shared(A1 &&a1, A2 &&a2, A3 &&a3)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1, a2, a3);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A, typename A2, typename A3, typename A4>
	typename shared_ptr<T> make_shared(const A &a1, A2 &&a2, A3 &&a3, A4 &&a4)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1, a2, a3, a4);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

	template<class T, typename A1, typename A2, typename A3, typename A4>
	typename shared_ptr<T> make_shared(A1 &&a1, A2 &&a2, A3 &&a3, A4 &&a4)
	{
		T* obj = NULL;
		try
		{
			obj = new T(a1, a2, a3, a4);
			shared_ptr<T> ptr(obj);
			return ptr;
		}
		catch (...)
		{
			if ( obj )
				delete obj;
		}
		return shared_ptr<T>();
	}

} // namespace scope

#endif // ConnectedVision_SmartPointer_def
