#ifndef IConnectedVisionModule_def
#define IConnectedVisionModule_def

#include <string>
#include <stdint.h>
#include <vector>
#include <boost/atomic.hpp>

#include "general.h"
#include "ConnectedVision.h"
#include "IStore.h"

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

namespace ConnectedVision
{
	class IModuleEnvironment;
	class IConnectedVisionModule;
	class IConnectedVisionOutputPin;
	class IConnectedVisionInputPin;

	class ConnectedVisionResponse
	{
	public:
		virtual ~ConnectedVisionResponse() {};	

		virtual void setContent(const std::string& data) { this->content = data; };
		virtual void setContentType(const std::string& data) { this->contentType = data; };

		virtual std::string getContent() { return this->content; };
		virtual const std::string& getContentConst() { return this->content; };
		virtual std::string getContentType() { return this->contentType; };
		virtual const std::string& getContentTypeConst() { return this->contentType; };

	public:
		std::string content;
		std::string contentType;

	};

	class IConnectedVisionInputPin
	{
	public:
		// management functions
		virtual void init(const id_t parentConfigID, const std::string& configStr, const pinID_t& outputPinID) = 0;
		virtual void init(const id_t parentConfigID, const boost::shared_ptr<std::string> configStr, const pinID_t& outputPinID) { return init(parentConfigID, *configStr, outputPinID); };
		virtual void init(const id_t parentConfigID, const boost::shared_ptr<Class_generic_config_chain> configConnection, const pinID_t& inputPinID) { init(parentConfigID, *configConnection->get_config(), configConnection->getCorrespondingOutputPinID( inputPinID ) ); };

		virtual pinID_t getInputPinID() const = 0;
		virtual pinID_t getOutputPinID() const = 0;

		// config / control functions
		virtual id_t getID() = 0;
		virtual Class_generic_config getConfig() = 0;
		virtual Class_generic_config setConfig() = 0;
		virtual Class_generic_config setConfig(const id_t parentConfigID, const boost::shared_ptr<Class_generic_config_chain> configConnection, const pinID_t& inputPinID) { init(parentConfigID, configConnection, inputPinID); return setConfig(); };
		virtual Class_generic_config setConfig(const id_t parentConfigID, const std::string& configStr, const pinID_t& outputPinID) { init(parentConfigID, configStr, outputPinID); return setConfig(); };
		virtual Class_generic_config setConfig(const id_t parentConfigID, const boost::shared_ptr<std::string> configStr, const pinID_t& outputPinID) { init(parentConfigID, *configStr, outputPinID); return setConfig(); };
		virtual Class_generic_config deleteConfig() = 0;

		virtual Class_generic_status getStatus() = 0;
		virtual Class_generic_status_stableResults getStableResults() { throw ConnectedVision::runtime_error("not implemented"); };

		virtual Class_generic_status& start() = 0;
		virtual Class_generic_status& stop() = 0;
		virtual Class_generic_status& reset() = 0;
		virtual Class_generic_status& recover() = 0;

		virtual Class_generic_status& notifyStop() = 0; // TODO: rethink better solution?

		/*
		// suggested data functions

		virtual boost::shared_ptr<TDataObject> getByID(const id_t id) = 0;

		virtual boost::shared_ptr<TDataObject> getByIndex(const int64_t index) = 0;
		virtual std::vector< boost::shared_ptr<TDataObject> > getByIndexRange(const int64_t start, const int64_t end) = 0;

		virtual std::vector< boost::shared_ptr<TDataObject> > getByTimestamp(const timestamp_t timestamp) = 0;
		virtual std::vector< boost::shared_ptr<TDataObject> > getBeforeTimestamp(const timestamp_t timestamp) = 0;
		virtual std::vector< boost::shared_ptr<TDataObject> > getAfterTimestamp(const timestamp_t timestamp) = 0;
		virtual std::vector< boost::shared_ptr<TDataObject> > getAllInTimespan(const timestamp_t start, const timestamp_t end) = 0;
		*/
	};

	class IConnectedVisionOutputPin
	{
	public:
		virtual ~IConnectedVisionOutputPin() {};

		/**
		 * init output pin with config
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual void init(
			const std::string& configStr	///< [in] config chain
		) = 0;

		/**
		 * get data from module by ID
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getByID(
			const id_t id,						///< [in] ID of requested data
			ConnectedVisionResponse &response	///< [out] requested data or error response
		) = 0;

		/**
		 * get data from module by index
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getByIndex(
			const int64_t index,				///< [in] index of requested data (index according to store)
			ConnectedVisionResponse &response	///< [out] requested data or error response
		) = 0;

		/**
		 * get data from module by index range
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getByIndexRange(
			const int64_t start,				///< [in] first index of requested data
			const int64_t end,					///< [in] last index of requested data
			ConnectedVisionResponse &response	///< [out] requested data or error response
		) = 0;

		/**
		 * get data from module by timestamp
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getByTimestamp(
			const timestamp_t timestamp,		///< [in] timestamp of requested data
			ConnectedVisionResponse &response	///< [out] requested data or error response
		) = 0;

		/**
		 * get data from module by timestamp before
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getBeforeTimestamp(
			const timestamp_t timestamp,		///< [in] timestamp of requested data
			ConnectedVisionResponse &response	///< [out] requested data or error response
			) = 0;

		/**
		 * get data from module by timestamp after
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getAfterTimestamp(
			const timestamp_t timestamp,		///< [in] timestamp of requested data
			ConnectedVisionResponse &response	///< [out] requested data or error response
			) = 0;

		/**
		 * get data from module by time span
		 *
		 * @return status code (analog to HTTP codes)
		 */
		virtual int getAllInTimespan(
			const timestamp_t start,			///< [in] first timestamp of requested data
			const timestamp_t end,				///< [in] last timestamp of requested data
			ConnectedVisionResponse &response	///< [out] requested data or error response
		) = 0;

	};

	class IConnectedVisionModule // TODO -> replaced by ConnectedVision::Module::IModule
	{
	public:
		/** constructor */
		IConnectedVisionModule() {}
		/** virtual destructor */
		virtual ~IConnectedVisionModule() {}

	public:

		//////////////////////////////////////////////////////////////////////////////////
		// module specific

		/**
		* get user-friendly display name of module
		*
		* @return module name
		*/
		virtual std::string getModuleName() const = 0;

		/**
		* get ID of module
		*
		* @return module ID
		*/
		virtual std::string getModuleID() const = 0;

		/**
		* get URL of module
		*
		* @return module URL
		*/
		virtual std::string getModuleURI() const = 0;

		/**
		* initialize module
		*
		* This function allocates required ressources, open DBs, ...
		*/
		virtual void initModule( 
			IModuleEnvironment *env	///< module environment
		) = 0;

		/**
		* release module
		*/
		virtual void releaseModule() = 0;
	
		/**
		* is module initialized and ready
		*
		* @return module initialization is finished
		*/
		virtual bool isModuleReady() const = 0;

		/**
		* get module initialization environment
		*
		* @return module environment
		*/
		virtual IModuleEnvironment *getEnv() = 0;

		/**
		* get module description as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getModuleDescription(
			ConnectedVisionResponse &response	///< [out] response containing module description
		) = 0;

		/**
		* get input pins description as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getInputDescription(
			ConnectedVisionResponse &response	///< [out] response containing input pins description
		) = 0;

		/**
		* get output pins description as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getOutputDescription(
			ConnectedVisionResponse &response	///< [out] response containing output pins description
		) = 0;

		/**
		* get list of configIDs as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getConfigList(
			ConnectedVisionResponse &response	///< [out] response containing list of configIDs
		) = 0;
	
		/**
		* get detailed config list as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getConfigListDetailed(
			ConnectedVisionResponse &response	///< [out] response containing detailed config list
		) = 0;
	
		/**
		* get module status as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getModuleStatus(
			ConnectedVisionResponse &response	///< [out] response containing module status
		) = 0;

		/**
		* get status store
		*
		* @return status store
		*/
		virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > getStatusStore() const = 0;

		/**
		* get config store
		*
		* @return config store
		*/
		virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > getConfigStore() const = 0;

		/**
		* get list of input pin IDs
		*
		* @return input pin IDs
		*/
		virtual std::vector<pinID_t> getInputPinIDs() const = 0;

		/**
		* get specific input pin instance for given configID
		*
		* If no such instance exists, a new one is created.
		*
		* @return input pin
		*/
		virtual boost::shared_ptr< IConnectedVisionInputPin > getInputPin(
			const id_t configID,	///< ID of according config
			const pinID_t pinID		///< ID of requested input pin
		) = 0;

		/**
		* get list of output pin IDs
		*
		* @return output pin IDs
		*/
		virtual std::vector<pinID_t> getOutputPinIDs() const = 0;

		/**
		* get specific output pin instance for given configID
		*
		* If no such instance exists, a new one is created.
		*
		* @return output pin
		*/
		virtual boost::shared_ptr< IConnectedVisionOutputPin > getOutputPin(
			const id_t configID,	///< ID of according config
			const pinID_t pinID		///< ID of requested output pin
		) = 0;


		//////////////////////////////////////////////////////////////////////////////////
		// config specific

		/**
		* get configuration for given config ID as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getConfig(
			const id_t configID,				///< [in] ID of config
			ConnectedVisionResponse &response	///< [out] response containing config chain
		) = 0;

		/**
		* set configuration and return JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int setConfig(
			const id_t configID,				///< [in] ID of config
			const std::string& config,			///< [in] config chain to be set
			ConnectedVisionResponse &response	///< [out] response containing config chain
		) = 0;

		/**
		* delete full config chain for given config ID as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int deleteConfig(
			const id_t configID,				///< [in] ID of config
			ConnectedVisionResponse &response	///< [out] response containing deleted config chain
		) = 0;

		/**
		* delete the secified config but keep other configs from the config chain 
		* return deleted config as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int deleteConfigOnlyThis(
			const id_t configID,				///< [in] ID of config
			ConnectedVisionResponse &response	///< [out] response containing deleted config chain
		) = 0;

		/**
		* get status for given config ID as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int getStatus(
			const id_t configID,				///< [in] ID of config
			ConnectedVisionResponse &response	///< [out] response containing status
		) = 0;

		/**
		* execute a control command and return status as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int control(
			const id_t configID,				///< [in] ID of config
			const std::string& command,			///< [in] control command: start, stop, recover, reset, stopThis, resetThis, notifyStop
			const id_t senderID,				///< [in] ID of sender (successor module)
			ConnectedVisionResponse &response	///< [out] response containing status
		) = 0;

		/**
		* process parameter command after HTTP-GET request and return status as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int processParameterCommand(
			const id_t configID,				///< [in] ID of config
			const std::string& command,			///< [in] command: "parameter/name=", "parameter/name", ...		
			ConnectedVisionResponse &response	///< [out] response containing status
		) = 0;

		/**
		* process parameter command after HTTP-PUT/-POST request and return status as JSON response
		*
		* @return status code (analog to HTTP codes)
		*/
		virtual int processParameterCommand(
			const id_t configID,				///< [in] ID of config
			const std::string& command,			///< [in] command: "parameter/name"
			const std::string& payload,			///< [in] payload the payload in case of a put/post request
			ConnectedVisionResponse &response	///< [out] response containing status
		) = 0;

		/** get moduleLogo as ConnectedVisionResponse
		* @param[out] response the ConnectedVisionResponse result which will contain the module logo if successful
		* @return status code (analog to HTTP codes)
		*/
		virtual int getModuleLogo(ConnectedVisionResponse &response) = 0;
	};

	namespace Module {
		class IWorkerControllerCallbacks;

		class IModule
		{
		public:
			/** constructor */
			IModule() {}
			/** virtual destructor */
			virtual ~IModule() {}

		public:

			//////////////////////////////////////////////////////////////////////////////////
			// module specific

			/**
			* get user-friendly display name of module
			*
			* @return module name
			*/
			virtual std::string getModuleName() const = 0;

			/**
			* get ID of module
			*
			* @return module ID
			*/
			virtual std::string getModuleID() const = 0;

			/**
			* get URL of module
			*
			* @return module URL
			*/
			virtual std::string getModuleURI() const = 0;

			/**
			* initialize module
			*
			* This function allocates required ressources, open DBs, ...
			*/
			virtual void initModule( 
				IModuleEnvironment *env	///< module environment
			) = 0;

			/**
			* release module
			*/
			virtual void releaseModule() = 0;
	
			/**
			* is module initialized and ready
			*
			* @return module initialization is finished
			*/
			virtual bool isModuleReady() const = 0;

			/**
			* get module status as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getModuleStatus(
				ConnectedVisionResponse &response	///< [out] response containing module status
			) = 0;

			/**
			* get module initialization environment
			*
			* @return module environment
			*/
			virtual IModuleEnvironment *getEnv() = 0;

			/**
			* get module description as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getModuleDescription(
				ConnectedVisionResponse &response	///< [out] response containing module description
			) = 0;

			/**
			* get input pins description as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getInputDescription(
				ConnectedVisionResponse &response	///< [out] response containing input pins description
			) = 0;

			/**
			* get output pins description as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getOutputDescription(
				ConnectedVisionResponse &response	///< [out] response containing output pins description
			) = 0;

			/**
			* get list of configIDs as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getConfigList(
				ConnectedVisionResponse &response	///< [out] response containing list of configIDs
			) = 0;
	
			/**
			* get detailed config list as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getConfigListDetailed(
				ConnectedVisionResponse &response	///< [out] response containing detailed config list
			) = 0;
	
			/**
			* get status store
			*
			* @return status store
			*/
			virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > getStatusStore() const = 0;

			/**
			* get config store
			*
			* @return config store
			*/
			virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > getConfigStore() const = 0;

			/**
			* get list of input pin IDs
			*
			* @return input pin IDs
			*/
			virtual std::vector<pinID_t> getInputPinIDs() const = 0;

			/**
			* get specific input pin instance for given configID
			*
			* If no such instance exists, a new one is created.
			*
			* @return input pin
			*/
			virtual boost::shared_ptr< IConnectedVisionInputPin > getInputPin(
				const id_t configID,	///< ID of according config
				const pinID_t pinID		///< ID of requested input pin
			) = 0;

			/**
			* get list of output pin IDs
			*
			* @return output pin IDs
			*/
			virtual std::vector<pinID_t> getOutputPinIDs() const = 0;

			/**
			* get specific output pin instance for given configID
			*
			* If no such instance exists, a new one is created.
			*
			* @return output pin
			*/
			virtual boost::shared_ptr< IConnectedVisionOutputPin > getOutputPin(
				const id_t configID,	///< ID of according config
				const pinID_t pinID		///< ID of requested output pin
			) = 0;


			//////////////////////////////////////////////////////////////////////////////////
			// config specific external API functions

			/**
			* get configuration for given config ID as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getConfig(
				const id_t configID,				///< [in] ID of config
				ConnectedVisionResponse &response	///< [out] response containing config chain
			) = 0;

			/**
			* set configuration and return JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int setConfig(
				const id_t configID,				///< [in] ID of config
				const std::string& config,			///< [in] config chain to be set
				ConnectedVisionResponse &response	///< [out] response containing config chain
			) = 0;

			/**
			* delete full config chain for given config ID as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int deleteConfig(
				const id_t configID,				///< [in] ID of config
				ConnectedVisionResponse &response	///< [out] response containing deleted config chain
			) = 0;

			/**
			* delete the secified config but keep other configs from the config chain 
			* return deleted config as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int deleteConfigOnlyThis(
				const id_t configID,				///< [in] ID of config
				ConnectedVisionResponse &response	///< [out] response containing deleted config chain
			) = 0;

			/**
			* get status for given config ID as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int getStatus(
				const id_t configID,				///< [in] ID of config
				ConnectedVisionResponse &response	///< [out] response containing status
			) = 0;

			/**
			* execute a control command and return status as JSON response
			*
			* @return status code (analog to HTTP codes)
			*/
			virtual int control(
				const id_t configID,				///< [in] ID of config
				const std::string& command,			///< [in] control command: start, stop, recover, reset, stopThis, resetThis, notifyStop
				const id_t senderID,				///< [in] ID of sender (successor module)
				ConnectedVisionResponse &response	///< [out] response containing status
			) = 0;

			//////////////////////////////////////////////////////////////////////////////////
			// config / worker specific


			/**
			 * register worker instance for specific config
			 */
			virtual void registerWorkerInstance(
				const id_t configID,						///< [in] ID of config
				const IWorkerControllerCallbacks *workerController	///< [in] worker controller instance
			) = 0;

			/**
			 * unregister worker instance for specific config
			 */
			virtual void unregisterWorkerInstance(
				const id_t configID,						///< [in] ID of config
				const IWorkerControllerCallbacks *workerController	///< [in] worker controller instance
			) = 0;


			/**
			 * delete all results for a given configID
			 */
			virtual void deleteAllData(
				const id_t configID				///< [in] ID of config
			) = 0;

			/**
			 * try to recover a given config
			 *
			 * @return	- true: if recovering was sucessfully (status is stopped)
			 *			- false: if config could not be recovered or module does not support recovering
			 */
			virtual bool processConfigRecover(
				const id_t configID				///< [in] ID of config
			) = 0;

		};

		class IWorker
		{
		public:
			/** constructor */
			IWorker() {}
			/** virtual destructor */
			virtual ~IWorker() {}

			/**
			* start worker
			*/
			virtual void run() = 0;

			/**
			* get associated module
			*
			* @return module 
			*/
			virtual IModule* getModule() = 0; 
		};

		class IWorkerControllerCallbacks
		{
		public:
			/** constructor */
			IWorkerControllerCallbacks() {}
			/** virtual destructor */
			virtual ~IWorkerControllerCallbacks() {}

			//////////////////////////////////////////////////////////////////////////////////
			// callback functions for worker

			/**
			* should the worker continue running
			*
			* This function can be called multiple times during one (long) computation step without any side effects.
			* It explicitely does NOT trigger any status or progress update.
			*
			* @note This function has to be thread-safe!
			*
			* @return continue working
			*/
			virtual bool intermediateContinueCheck() const = 0;

			/**
			* Inform the worker controller that one computation iteration step (e.g. frame) has been finished,
			* and ask to continue with the next computation.
			*
			* @note This function has to be thread-safe!
			*
			* @return true if worker should continue
			*/
			virtual bool nextIterationStep() = 0;

		};

		class IWorkerFactory
		{
		public:
			/** constructor */
			IWorkerFactory() {}
			/** virtual destructor */
			virtual ~IWorkerFactory() {}

			/**
			* get corresponding module
			*
			* @return module 
			*/
			virtual IModule* getModule() const = 0; 

			/**
			* create a new worker instance for a given config
			*
			* @note This function has to be thread-safe!
			*
			* @return worker instance
			*/
			virtual std::unique_ptr<IWorker> createWorker(
				IWorkerControllerCallbacks &controller,									///< reference to worker controller
				ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
			) = 0;
		};

		/**
		* create and handle all worker (threads) of the module
		*/
		class IWorkerDispatcher
		{
		public:
			/** constructor */
			IWorkerDispatcher() {}
			/** virtual destructor */
			virtual ~IWorkerDispatcher() {}

			/**
			* start the worker for a given config
			*
			* If there is already an existing worker, this function does nothing.
			*/
			virtual void start( 
				const boost::shared_ptr<const Class_generic_config> config	///< config for the worker to be started
			) = 0;
	
			/**
			* stop the worker of a specific config chain
			*/
			virtual void stop(
				const id_t& configID	///< [in] config chain ID
			) = 0;

			/**
			* get IDs of currently running workers
			*
			* @return config IDs of currently active workers
			*/
			virtual std::vector<const id_t> getRunningWorkerIDs() = 0;
		};

	}

} // namespace ConnectedVision

#endif // IConnectedVisionModule_def


