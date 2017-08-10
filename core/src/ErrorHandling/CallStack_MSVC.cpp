/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/**
@note
	based on the "stacktrace" project by Ethan Tira-Thompson, Fredrik Orderud.
	http://stacktrace.sourceforge.net/
	stacktrace is licenced under BSD licence (http://www.opensource.org/licenses/bsd-license.php) 

	using StackWalker (http://stackwalker.codeplex.com/)
*/

/* Windows (Microsoft visual studio) implementation of the CallStack class. */
#ifdef _WIN32 // also defined in 64bit

#include "CallStack.h"
#include "StackWalker.h"

namespace ConnectedVision {
namespace ErrorHandling {
namespace CallStack_Extension {

/** Adapter class to interfaces with the StackWalker project. */
class StackWalkerAdapter : public StackWalker {
public:
    StackWalkerAdapter () : 
        StackWalker(StackWalker::RetrieveVerbose | StackWalker::SymBuildPath) // do not use public Microsoft-Symbol-Server
    {}
    virtual ~StackWalkerAdapter () {}

protected:

    virtual void OnCallstackEntry (CallstackEntryType /*eType*/, CallstackEntry &entry) {
		if ( !entry.offset )
			return;

		std::string functionName = entry.name;

		// discard stacktrace namespace
		if ( functionName.find("CallStack::") == std::string::npos && functionName.find("CallStack<") == std::string::npos && functionName.find("StackWalker::") == std::string::npos )
		{
            CallStack::Entry e;
            e.file = entry.lineFileName;
            e.line = entry.lineNumber;
			e.addr = (size_t)entry.offset;
			e.function = functionName;
            stack.push_back(e);
        }
    }
    virtual void OnOutput (LPCSTR /*szText*/) {
        // discard (should never be called)
    }
    virtual void OnSymInit (LPCSTR /*szSearchPath*/, DWORD /*symOptions*/, LPCSTR /*szUserName*/) {
        // discard
    }
    virtual void OnLoadModule (LPCSTR /*img*/, LPCSTR /*mod*/, DWORD64 /*baseAddr*/, DWORD /*size*/, DWORD /*result*/, LPCSTR /*symType*/, LPCSTR /*pdbName*/, ULONGLONG /*fileVersion*/) {
        // discard
    }
    virtual void OnDbgHelpErr (LPCSTR /*szFuncName*/, DWORD /*gle*/, DWORD64 /*addr*/) {
        // discard
    }

public:
    std::vector<CallStack::Entry> stack;       ///< populated stack trace
};
} // namespace

// windows 32 & 64 bit impl.
CallStack::CallStack () {
    CallStack_Extension::StackWalkerAdapter sw;
    sw.ShowCallstack();
    entries = sw.stack;
}

CallStack::~CallStack () throw() {
    // automatic cleanup
}

}} // namespace

#endif // _WIN32
