/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVision_Exceptions_def
#define ConnectedVision_Exceptions_def

#include "ErrorHandling/Exception_CallStack.h"

#include <system_error>

namespace ConnectedVision { 
	/*
	* wrapper with call stack extension for std exceptions
	*/
	typedef ErrorHandling::Exception_CallStack<std::runtime_error> runtime_error;
	typedef ErrorHandling::Exception_CallStack<std::range_error> range_error;
	typedef ErrorHandling::Exception_CallStack<std::overflow_error> overflow_error;
	typedef ErrorHandling::Exception_CallStack<std::underflow_error> underflow_error;
	typedef ErrorHandling::Exception_CallStack<std::system_error> system_error;

	typedef ErrorHandling::Exception_CallStack<std::logic_error> logic_error;
	typedef ErrorHandling::Exception_CallStack<std::domain_error> domain_error;
	typedef ErrorHandling::Exception_CallStack<std::invalid_argument> invalid_argument;
	typedef ErrorHandling::Exception_CallStack<std::length_error> length_error;
	typedef ErrorHandling::Exception_CallStack<std::out_of_range> out_of_range;

	/**
	 * standard exception for config errors
	 */
	class config_runtime_error : public ConnectedVision::runtime_error
	{
	public:
		config_runtime_error( const std::string &str ) : ConnectedVision::runtime_error( str ) {}
	};

	/**
	 * standard exception for status errors
	 */
	class status_runtime_error : public ConnectedVision::runtime_error
	{
	public:
		status_runtime_error( const std::string &str ) : ConnectedVision::runtime_error( str ) {}
	};

} // namespace ConnectedVision


#endif // ConnectedVision_Exceptions_def