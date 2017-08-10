/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/**
@note
	based on the "stacktrace" project by Ethan Tira-Thompson, Fredrik Orderud.
	http://stacktrace.sourceforge.net/
	stacktrace is licenced under BSD licence (http://www.opensource.org/licenses/bsd-license.php)

	see http://stupefydeveloper.blogspot.com/2008/10/cc-call-stack.html 
*/

/* Liux/gcc implementation of the CallStack class. */
#ifdef __GNUC__

#include <stdio.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "CallStack.h"

namespace ConnectedVision {
namespace ErrorHandling {

#define MAX_DEPTH 32

CallStack::CallStack () {
    using namespace abi;

    // retrieve call-stack
    void * trace[MAX_DEPTH];
    int stack_depth = backtrace(trace, MAX_DEPTH);

    for (int i = 1; i < stack_depth; i++) {
        Dl_info dlinfo;
        if(!dladdr(trace[i], &dlinfo))
            break;

        const char * symname = dlinfo.dli_sname;

        int    status;
        char * demangled = abi::__cxa_demangle(symname, NULL, 0, &status);
        if(status == 0 && demangled)
            symname = demangled;

        //printf("entry: %s, %s\n", dlinfo.dli_fname, symname);

        // store entry to stack
        if (symname) {
			std::string functionName = symname;
			// discard stacktrace namespace
			if ( functionName.find("CallStack::") == std::string::npos && functionName.find("CallStack<") == std::string::npos )
			{
				CallStack::Entry e;
				e.file     = dlinfo.dli_fname;
				e.line     = 0; // unsupported
				e.addr     = (size_t)dlinfo.dli_saddr;
				e.function = symname;
				entries.push_back(e);
			}
        } else {
        	// cannot get function name
			CallStack::Entry e;
			e.file     = dlinfo.dli_fname;
			e.line     = 0; // unsupported
			e.addr     = (size_t)dlinfo.dli_saddr;
			e.function = "";
			entries.push_back(e);
        }

        if (demangled)
            free(demangled);
    }
}

CallStack::~CallStack () throw() {
    // automatic cleanup
}

}} // namespace

#endif // __GNUC__
