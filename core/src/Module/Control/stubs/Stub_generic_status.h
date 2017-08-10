/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_generic_status.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


// include child classes
#include "../Class_generic_status_qualityOfService.h"
#include "../Class_generic_status_stableResults.h"

#ifndef Stub_generic_status_def
#define Stub_generic_status_def

// --> Do NOT EDIT <--
namespace ConnectedVision {

/**
 * stub class for: Class_generic_status
 * 
 * module: 
 * description: config status
 */
class Stub_generic_status {

public:
	Stub_generic_status();
	Stub_generic_status(const Stub_generic_status& other);
	Stub_generic_status(const rapidjson::Value& value);
	Stub_generic_status(const std::string& str);
	virtual ~Stub_generic_status();
	Stub_generic_status &operator =(const Stub_generic_status& other);
	Stub_generic_status &operator =(Stub_generic_status&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* id - config id */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* timestamp - time of modification */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* moduleID - ID of module */
	virtual ConnectedVision::id_t get_moduleID() const;
	virtual const ConnectedVision::id_t getconst_moduleID() const;
	virtual void set_moduleID(ConnectedVision::id_t value);

	/* moduleURI - URI of module instance */
	virtual boost::shared_ptr<std::string> get_moduleURI() const;
	virtual const boost::shared_ptr<const std::string> getconst_moduleURI() const;
	virtual void set_moduleURI(boost::shared_ptr<std::string> value);
	virtual void set_moduleURI(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_moduleURI(ptr); };

	/* status - current status of config / job */
	virtual boost::shared_ptr<std::string> get_status() const;
	virtual const boost::shared_ptr<const std::string> getconst_status() const;
	virtual void set_status(boost::shared_ptr<std::string> value);
	virtual void set_status(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_status(ptr); };
	// enum functions
	virtual bool is_status(const boost::shared_ptr<std::string>& value) const;
	const static boost::shared_ptr<std::string> status_na;
	virtual bool is_status_na() const { return is_status( Stub_generic_status::status_na ); }
	virtual void set_status_na() { set_status ( Stub_generic_status::status_na ); }
	const static boost::shared_ptr<std::string> status_init;
	virtual bool is_status_init() const { return is_status( Stub_generic_status::status_init ); }
	virtual void set_status_init() { set_status ( Stub_generic_status::status_init ); }
	const static boost::shared_ptr<std::string> status_startup;
	virtual bool is_status_startup() const { return is_status( Stub_generic_status::status_startup ); }
	virtual void set_status_startup() { set_status ( Stub_generic_status::status_startup ); }
	const static boost::shared_ptr<std::string> status_running;
	virtual bool is_status_running() const { return is_status( Stub_generic_status::status_running ); }
	virtual void set_status_running() { set_status ( Stub_generic_status::status_running ); }
	const static boost::shared_ptr<std::string> status_stopping;
	virtual bool is_status_stopping() const { return is_status( Stub_generic_status::status_stopping ); }
	virtual void set_status_stopping() { set_status ( Stub_generic_status::status_stopping ); }
	const static boost::shared_ptr<std::string> status_stopped;
	virtual bool is_status_stopped() const { return is_status( Stub_generic_status::status_stopped ); }
	virtual void set_status_stopped() { set_status ( Stub_generic_status::status_stopped ); }
	const static boost::shared_ptr<std::string> status_finished;
	virtual bool is_status_finished() const { return is_status( Stub_generic_status::status_finished ); }
	virtual void set_status_finished() { set_status ( Stub_generic_status::status_finished ); }
	const static boost::shared_ptr<std::string> status_error;
	virtual bool is_status_error() const { return is_status( Stub_generic_status::status_error ); }
	virtual void set_status_error() { set_status ( Stub_generic_status::status_error ); }
	const static boost::shared_ptr<std::string> status_reset;
	virtual bool is_status_reset() const { return is_status( Stub_generic_status::status_reset ); }
	virtual void set_status_reset() { set_status ( Stub_generic_status::status_reset ); }
	const static boost::shared_ptr<std::string> status_cleanup;
	virtual bool is_status_cleanup() const { return is_status( Stub_generic_status::status_cleanup ); }
	virtual void set_status_cleanup() { set_status ( Stub_generic_status::status_cleanup ); }

	/* message - general message (e.g. description of last error) */
	virtual boost::shared_ptr<std::string> get_message() const;
	virtual const boost::shared_ptr<const std::string> getconst_message() const;
	virtual void set_message(boost::shared_ptr<std::string> value);
	virtual void set_message(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_message(ptr); };

	/* progress - processing progress (0.0 - 1.0) */
	virtual double get_progress() const;
	virtual const double getconst_progress() const;
	virtual void set_progress(double value);

	/* startTime - System time when the config was started. */
	virtual ConnectedVision::timestamp_t get_startTime() const;
	virtual const ConnectedVision::timestamp_t getconst_startTime() const;
	virtual void set_startTime(ConnectedVision::timestamp_t value);

	/* systemTimeProcessing - System time when the config was / is processed. This time is updated only during processing the config (i.e. status='running'). */
	virtual ConnectedVision::timestamp_t get_systemTimeProcessing() const;
	virtual const ConnectedVision::timestamp_t getconst_systemTimeProcessing() const;
	virtual void set_systemTimeProcessing(ConnectedVision::timestamp_t value);

	/* estimatedFinishTime - estimated time to finish processing of this configChain */
	virtual ConnectedVision::timestamp_t get_estimatedFinishTime() const;
	virtual const ConnectedVision::timestamp_t getconst_estimatedFinishTime() const;
	virtual void set_estimatedFinishTime(ConnectedVision::timestamp_t value);

	/* qualityOfService - quality of service (QoS) parameters */
	virtual boost::shared_ptr<Class_generic_status_qualityOfService> get_qualityOfService() const;
	virtual const boost::shared_ptr<const Class_generic_status_qualityOfService> getconst_qualityOfService() const;
	virtual void set_qualityOfService(boost::shared_ptr<Class_generic_status_qualityOfService> value);
	virtual void set_qualityOfService(const Class_generic_status_qualityOfService &value) { boost::shared_ptr<Class_generic_status_qualityOfService> ptr = boost::make_shared<Class_generic_status_qualityOfService>(value); set_qualityOfService(ptr); };
	virtual void set_qualityOfService(const rapidjson::Value& value) { qualityOfService->parseJson( value ); };

	/* stableResults - Index and timestamp range of available and stable (non-changing) results. One entry for each output pin. */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> get_stableResults() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> getconst_stableResults() const;
	virtual void set_stableResults(boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> value);
	virtual void set_stableResults(const std::vector<boost::shared_ptr<Class_generic_status_stableResults>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>>(value); set_stableResults(ptr); };
	// array functions
	virtual boost::shared_ptr<Class_generic_status_stableResults> get_stableResults(int index) const;
	virtual const boost::shared_ptr<Class_generic_status_stableResults>& getconst_stableResults(int index) const;
	virtual void add_stableResults(boost::shared_ptr<Class_generic_status_stableResults> value);
	virtual void add_stableResults(const Class_generic_status_stableResults &value) { boost::shared_ptr<Class_generic_status_stableResults> ptr = boost::make_shared<Class_generic_status_stableResults>(value); add_stableResults(ptr); };

	/* chain - Status of previous modules. */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> get_chain() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> getconst_chain() const;
	virtual void set_chain(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value);
	virtual void set_chain(const std::vector<boost::shared_ptr<std::string>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>(value); set_chain(ptr); };
	// array functions
	virtual boost::shared_ptr<std::string> get_chain(int index) const;
	virtual const boost::shared_ptr<std::string>& getconst_chain(int index) const;
	virtual void add_chain(boost::shared_ptr<std::string> value);
	virtual void add_chain(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); add_chain(ptr); };

	/* configID - virtual config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** config id */
	ConnectedVision::id_t id;
	
	/** time of modification */
	ConnectedVision::timestamp_t timestamp;
	
	/** ID of module */
	ConnectedVision::id_t moduleID;
	
	/** URI of module instance */
	boost::shared_ptr<std::string> moduleURI;
	
	/** current status of config / job */
	boost::shared_ptr<std::string> status;
	
	/** general message (e.g. description of last error) */
	boost::shared_ptr<std::string> message;
	
	/** processing progress (0.0 - 1.0) */
	double progress;
	
	/** System time when the config was started. */
	ConnectedVision::timestamp_t startTime;
	
	/** System time when the config was / is processed. This time is updated only during processing the config (i.e. status='running'). */
	ConnectedVision::timestamp_t systemTimeProcessing;
	
	/** estimated time to finish processing of this configChain */
	ConnectedVision::timestamp_t estimatedFinishTime;
	
	/** quality of service (QoS) parameters */
	boost::shared_ptr<Class_generic_status_qualityOfService> qualityOfService;
	
	/** Index and timestamp range of available and stable (non-changing) results. One entry for each output pin. */
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> stableResults;
	
	/** Status of previous modules. */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> chain;
	
	/** virtual config id */
	ConnectedVision::id_t configID;
	
};

} // namespace ConnectedVision

#endif // Stub_generic_status_def