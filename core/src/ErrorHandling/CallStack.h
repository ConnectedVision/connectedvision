/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef CallStack_def
#define CallStack_def

/**
@note
	based on the "stacktrace" project by Ethan Tira-Thompson, Fredrik Orderud.
	http://stacktrace.sourceforge.net/
	stacktrace is licenced under BSD licence (http://www.opensource.org/licenses/bsd-license.php) 
*/

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <limits>

namespace ConnectedVision {
namespace ErrorHandling {

template< typename T >
std::string int_to_hex( T i )
{
	std::stringstream stream;
	stream << "0x" 
			<< std::setfill ('0') << std::setw( std::numeric_limits<T>::digits/4 ) 
			<< std::hex << i;
	return stream.str();
}

/** Stack-trace base class, for retrieving the current call-stack. */
class CallStack {

public:	
/** Call-stack entry datastructure. */
struct Entry {
    /** Default constructor that clears all fields. */
    Entry () : line(0), addr(0) {}

    std::string file;		///< filename
    size_t      line;		///< line number
    std::string function;	///< name of function or method
	size_t		addr;		///< address of function

    /** Serialize CallStack::Entry into a text string. */
    std::string to_string () const {
        std::ostringstream os;
		std::string filename;
		auto found = file.find_last_of("/\\");
		if ( found == std::string::npos )
			filename = file;
		else
			filename = file.substr(found+1);

		if ( function.empty() )
			os << int_to_hex(addr);	// if we have no function name, use address instead
		else
			os << function;
        os << "() " << filename << " @ " << line;
        return os.str();
    }
};

public:
    /** Stack-trace consructor. */
    CallStack ();

    virtual ~CallStack () throw();

    /** Serializes the entire call-stack into a text string. */
    std::string to_string () const {
        std::ostringstream os;
		size_t size = entries.size();
        for (size_t i = 0; i < size; i++)
            os << (size-i) << ": " << entries[i].to_string() << std::endl;
        return os.str();
    }

	/** returns size of stack */
	size_t size() const { return entries.size(); }

    /** Call stack. */
    std::vector<CallStack::Entry> entries;

protected:
	// TODO static boost::mutex mutex; // make sure that only one instance is accessing th stack
};

}} // namespace

#endif // CallStack_def
