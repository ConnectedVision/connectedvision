/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ILogging_def
#define ILogging_def

#include <ostream>
#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include "general.h"

namespace ConnectedVision
{

namespace Logging 
{
	enum LogLevel_t { Debug = 0, Info = 1, Warning = 2, Error = 3, Fatal = 4 };
	static const char *LevelName[] = { "Debug", "Info", "Warning", "Error", "Fatal" };

	// interface implemented by classes providing logging functions
	class ILogWriter {
	public:
		virtual void write( const Logging::LogLevel_t level, const std::string domainName, const std::string scopeName, const std::string message, const id_t configID = ID_NULL ) = 0;
	};

	/// interface implemented by classes using the logging functionality
	class ILogable {
	public:
		/// log writer
		virtual boost::shared_ptr<Logging::ILogWriter> log() const = 0;
	protected:		
		/// log or module name
		std::string logName;
	};

	class LogWriterNULL : public ILogWriter {
	public:
		void write( const Logging::LogLevel_t level, const std::string domainName, const std::string scopeName, const std::string message, const id_t configID ) {};
	};

	class LogWriterStream : public ILogWriter {
	public:
		LogWriterStream( std::ostream& os ) : os( os ) {};

		void write( const Logging::LogLevel_t level, const std::string domainName, const std::string scopeName, const std::string message, const id_t configID )
		{
			boost::timed_mutex::scoped_timed_lock lock(mutex, boost::posix_time::milliseconds(1));
			if ( lock ) 
			{
				os << domainName << " [" << Logging::LevelName[level] << "] " << scopeName << ": (" << configID << ") "<< message << std::endl;
			}
		};

	protected:
		std::ostream& os;
		boost::timed_mutex mutex;
	};

	class LoggingScope {
	public:
		LoggingScope(boost::shared_ptr<Logging::ILogWriter> log, const Logging::LogLevel_t level, const std::string domainName, const std::string scopeName, const id_t configID = ID_NULL) : 
		  log(log), level(level), domainName(domainName), scopeName(scopeName), configID(configID)
			{
				this->log->write( this->level, this->domainName, this->scopeName, "entered", this->configID); 
			};
		virtual ~LoggingScope() 
			{ 
				this->log->write( this->level, this->domainName, this->scopeName, "exited", this->configID); 
			};

	protected:
		boost::shared_ptr<Logging::ILogWriter> log;
		const Logging::LogLevel_t level;
		const std::string domainName;
		const std::string scopeName;
		const id_t configID;
	};
}


#define LOG( level, msg )	{ this->log()->write( (level), this->logName, std::string(__FUNCTION__) + std::string("()@") + ConnectedVision::intToStr(__LINE__), (msg) ); }
#define LOG_DEBUG( msg )	LOG( Logging::Debug, msg )
#define LOG_INFO( msg )		LOG( Logging::Info, msg )
#define LOG_WARN( msg )		LOG( Logging::Warning, msg )
#define LOG_ERROR( msg )	LOG( Logging::Error, msg )
#define LOG_FATAL( msg )	LOG( Logging::Fatal, msg )
#define LOG_SCOPE			Logging::LoggingScope _log_scope( this->log(), Logging::Debug, this->logName, std::string(__FUNCTION__) + std::string("()@") + ConnectedVision::intToStr(__LINE__));

} // namespace ConnectedVision

#endif // ILogging_def