/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Exception_CallSatck_def
#define Exception_CallSatck_def

/**
@note
	based on the "stacktrace" project by Ethan Tira-Thompson, Fredrik Orderud.
	http://stacktrace.sourceforge.net/
	stacktrace is licenced under BSD licence (http://www.opensource.org/licenses/bsd-license.php) 
*/

#include <stdexcept>
#include <iostream>
#include <string>
#include <memory> // std::shared_ptr
#include <ErrorHandling/CallStack.h>

namespace ConnectedVision {
namespace ErrorHandling {

class Exception_BaseClass_CallStack
{
public:
	Exception_BaseClass_CallStack() {
		if ( isCallStackEnabled() )
		{
			auto tmp = new CallStack(); // do not use make_shared<> since it will add to the stack
			// make shared pointer from call stack
			this->stack.reset(tmp);
		}
	}
	virtual ~Exception_BaseClass_CallStack () {}
	std::shared_ptr<const CallStack> getStack() const { 
		if ( this->stack )
			return this->stack;
		else
			throw std::runtime_error("stack is NULL");
	}

	static const bool isCallStackEnabled() { return Exception_BaseClass_CallStack::callStackEnabled; }
	static void setCallStackEnabled(const bool enabled) { Exception_BaseClass_CallStack::callStackEnabled = enabled; }
	

	static bool printToStdOut;

protected:
	static bool callStackEnabled;
	std::shared_ptr<CallStack> stack;	///< call stack instance

};

/** Template for stack-augmented exception classes. */
template<class T>
class Exception_CallStack : public T, public Exception_BaseClass_CallStack
{
public:
    Exception_CallStack(const std::string &msg) : T(msg), Exception_BaseClass_CallStack() 
	{
		// print to console
		if ( Exception_BaseClass_CallStack::printToStdOut )
		{
			std::cout << this->what(true) << std::endl << std::flush;
		}
	}

    virtual ~Exception_CallStack () throw() {}

    virtual const char *what() const throw()
	{
		return what(true);
	}

    virtual const char *what(bool appendCallStack) const throw() 
	{
        if (appendCallStack) {
            // concatenate message with stack trace
			if ( buffer.empty() )
			{
				buffer = std::string(T::what());
				if ( stack)
					buffer += "\ncall stack:\n" + stack->to_string();
			}
            return buffer.c_str();
        } else {
            return T::what();
        }
    }

protected:
	mutable std::string buffer; // needs to be a class member, so we can return a pointer to its content
};

}} // namespace stacktrace

#endif // Exception_CallSatck_def
