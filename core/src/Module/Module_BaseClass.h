/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef Module_BaseClass_def
#define Module_BaseClass_def

#include <string>
#include <vector>
#include <map>
#include <sqlite3.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>


#include <IConnectedVisionModule.h>

#include <ConnectedVision.h>

#include "ConnectedVisionOutputPin.h"
#include "DBConnection.h"

#include "Module/Control/Class_generic_status.h"
#include "Module/Control/Store_SQLite_generic_status.h"

#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Store_SQLite_generic_config.h"

#include "Module/Control/Class_PinDescription.h"
#include "CNamedResourcesPool.h"
#include "Module/WorkerController.h"

namespace cv {
	class Mat;
};


namespace ConnectedVision {
namespace Module {

typedef CNamedResourcesPool<id_t, IConnectedVisionInputPin> InputPinPool_t; // TODO: rethink about class instance as "shared_ptr"
typedef CNamedResourcesPool<id_t, IConnectedVisionOutputPin> OutputPinPool_t; // TODO: rethink about class instance as "shared_ptr"

class Module_BaseClass: 
	public IModule, 
	public IWorkerFactory, 
	public Logging::ILogable
{
public:
	const static int inputPinsPoolSize = 2;
	const static int outputPinsPoolSize = 2;

public:
	Module_BaseClass(const char moduleDescription[], const char inputPinDescription[], const char outputPinDescription[]);
    virtual ~Module_BaseClass();

public:

	virtual void initModule( IModuleEnvironment *env ) ;
	virtual void releaseModule();
	virtual bool isModuleReady() const { return this->ready; };
	virtual IModuleEnvironment *getEnv() { return this->env; };

	virtual IModule* getModule() { return static_cast<IModule*>(this); };
	virtual std::string getModuleName() const { return this->moduleName; };
	virtual std::string getModuleID() const { return this->moduleID; };
	virtual std::string getModuleURI() const { return this->moduleURI; };

	virtual int getModuleDescription(ConnectedVisionResponse &response);
	virtual int getInputDescription(ConnectedVisionResponse &response);
	virtual int getOutputDescription(ConnectedVisionResponse &response);

	virtual int getConfigList(ConnectedVisionResponse &response);
	virtual int getConfigListDetailed(ConnectedVisionResponse &response);
	virtual int getModuleStatus(ConnectedVisionResponse &response);

	virtual std::vector<id_t> getConfigIDsByAliasID(std::string aliasID);

	virtual id_t resolvePotentialAliasID(const std::string &inputID);

	virtual int getConfig(const id_t configID, ConnectedVisionResponse &response);
	virtual int setConfig(const id_t configID, const std::string& config, ConnectedVisionResponse &response);
	virtual int deleteConfig(const id_t configID, ConnectedVisionResponse &response);
	virtual int deleteConfigOnlyThis(const id_t configID, ConnectedVisionResponse &response);
	virtual int getConfigHTMLsummary(const id_t configID, ConnectedVisionResponse &response);
	virtual std::string getConfigHTMLsummary(Module_BaseClass &module, const Class_generic_config &config);

	virtual ConnectedVision::shared_ptr<const Class_generic_status> getStatus(const id_t configID);
	virtual int getStatus(const id_t configID, ConnectedVisionResponse &response);	

	virtual int control(const id_t configID, const std::string& command, const id_t senderID, ConnectedVisionResponse &response);

	/**
	 * process parameter command after HTTP-GET request and return status as JSON response
	 *
	 * @param[in] configID		ID of configuration / job
	 * @param[in] command		command: "parameter/name=", "parameter/name", ...
	 * @param[out] response		status of configuration / job
	 *
	 * @return status code (analog to HTTP codes)
	 */
	virtual int processParameterCommand(const id_t configID, const std::string& command, ConnectedVisionResponse &response);
	
	/**
	 * process parameter command after HTTP-PUT/-POST request and return status as JSON response
	 *
	 * @param[in] configID		ID of configuration / job
	 * @param[in] command		command: "parameter/name"
	 * @param[in] payload		the payload of the put/post request
	 * @param[out] response		status of configuration / job
	 *
	 * @return status code (analog to HTTP codes)
	 */
	virtual int processParameterCommand(const id_t configID, const std::string& command, const std::string& payload, ConnectedVisionResponse &response);

	/**
	* get the updated params (with all previous changes to dynamic parameters applied)
	* @param[in] configID		ID of configuration / job
	* @return shared pointer to a string object containing the updated params
	*/
	virtual boost::shared_ptr<std::string> getUpdatedParams(const id_t configID);

	virtual int getInputPinCount(const Class_generic_config& config, const pinID_t pinID);
	virtual int getInputPinCount(const boost::shared_ptr<const Class_generic_config> config, const pinID_t pinID);

	virtual std::vector<pinID_t> getInputPinIDs() const { return this->inputPinIDs; };
	virtual boost::shared_ptr< IConnectedVisionInputPin > getInputPin(const id_t configID, const pinID_t pinID);
	virtual boost::shared_ptr< IConnectedVisionInputPin > getInputPin(const Class_generic_config &config, const pinID_t pinID, int index = -1);
	virtual boost::shared_ptr< IConnectedVisionInputPin > getInputPin(const boost::shared_ptr<const Class_generic_config> config, const pinID_t pinID, int index = -1) { return getInputPin( *(config.get()), pinID, index); };

	virtual std::vector<pinID_t> getOutputPinIDs() const { return this->outputPinIDs; };
	virtual boost::shared_ptr< IConnectedVisionOutputPin > getOutputPin(const id_t configID, const pinID_t pinID);
	virtual boost::shared_ptr< IConnectedVisionOutputPin > getOutputPin(const Class_generic_config &config, const pinID_t pinID);
	virtual boost::shared_ptr< IConnectedVisionOutputPin > getOutputPin(const boost::shared_ptr<const Class_generic_config> config, const pinID_t pinID) { return getOutputPin( *(config.get()), pinID); };



	virtual void registerWorkerInstance(const id_t configID, ConnectedVision::Module::IWorkerControllerCallbacks *workerController);
	virtual void unregisterWorkerInstance(const id_t configID, ConnectedVision::Module::IWorkerControllerCallbacks *workerController);

	virtual void deleteAllData(const id_t configID) = 0;
	virtual bool processConfigRecover(const id_t configID) { return false; }

	/**
	 * returns worker for a given config ID (if existing)
	 *
	 * @throws out_of_range if worker does not exist / is not running
	*/
	virtual ConnectedVision::shared_ptr<ConnectedVision::Module::IWorker> getWorker(
		const id_t configID ///< config ID
	) const;



	virtual DBConnection& getDB() { return dbConn; };

	virtual boost::shared_ptr<Logging::ILogWriter> log() const;

	virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status> > getStatusStore() const { return this->statusStore; }
	virtual ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config> > getConfigStore() const { return this->configStore; }

	// buffer with host logo as PNG data - the logo will be displayed on the main html page
	typedef struct BufferLogoPNG
	{
		char *pBufferLogoAsPNG;
		int sizeBufferLogoAsPNG;
	} BufferLogoPNG;

	/** sets the module logo
	* @param[in] logoPNG		the buffer info of the module PNG logo
	*/
	virtual void setLogoPNG(const BufferLogoPNG &logoPNG);

	/** function to check if a module logo has been set
	* @return boolean value indicating if the module logo has been set 
	*/	
	virtual bool isSetLogo();

	/** get moduleLogo as ConnectedVisionResponse
	* @param[out] response the ConnectedVisionResponse result which will contain the module logo if successful
	* @return status code (analog to HTTP codes)
	*/
	virtual int getModuleLogo(ConnectedVisionResponse &response);


protected:
	virtual void prepareStores() = 0;
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID) = 0;
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID) = 0;

	virtual void checkConfig(const Class_generic_config &config);
	virtual void checkInputPinID(const pinID_t pinID);
	virtual void checkInputPinDescription(const boost::shared_ptr<Class_PinDescription> description);
	
	virtual void updateAliasIDs(boost::shared_ptr<Class_generic_config> config);

	/**
	* tries to get a parameter of interest (acording to function parameter @ref parameterPath)
	* @param[in] config the config object of interest
	* @param[in] parameterPath the string of format "param1/param2/.../paramXYZ" specifying the target parameter inside the "params" object according to the module description	
	* @param[out] response the response of the get parameter command in case of success
	* @throws a runtime_error if parameter of interest is not dynamic, if @ref parameterValue does not fit the expected value or if a processing error occured
	*/
	virtual void getDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, ConnectedVisionResponse &response);

	/**
	* tries to set a parameter of interest (acording to function parameter @ref parameterPath) if it is dynamic
	* @param[in] config the config object of interest (the params object inside this config will be updated and the updated config will be written to the config store)
	* @param[in] parameterPath the string of format "param1/param2/.../paramXYZ" specifying the target parameter inside the "params" object according to the module description
	* @param[in] parameterValue the target value for the parameter of interest in a string in JSON-format
	* @param[out] response the response of the set parameter command in case of success
	* @throws a runtime_error if parameter of interest is not dynamic, if @ref parameterValue does not fit the expected value or if a processing error occured
	*/
	virtual void setDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, const std::string& parameterValue, ConnectedVisionResponse &response);

	/**
	* tries to set a parameter of interest (acording to function parameter @ref parameterPath) if it is dynamic (will be invoked from inside of
	* function @ref void setDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, const std::string& parameterValue, ConnectedVisionResponse &response))
	* @param[in] parameterPath the string of format "param1/param2/.../paramXYZ" specifying the target parameter inside the "params" object according to the module description
	* @param[in] parameterValue the target value for the parameter of interest as JSON-parsed object
	* @param[inout] documentParams the JSON-parsed params object (of type rapidjson::Document& because of its allocator will be used)
	* @throws a runtime_error if parameter of interest is not dynamic, if @ref parameterValue does not fit the expected value or if a processing error occured
	*/
	virtual void setDynamicParameter(const std::string& parameterPath, const rapidjson::Value &parameterValue, rapidjson::Document &documentParams);

	/**
	* reset a parameter of interest to its initial value (from initialParams JSON object from config)
	* @param[in] config the config object of interest (the params object inside this config will be updated and the updated config will be written to the config store)
	* @param[in] parameterPath the string of format "param1/param2/.../paramXYZ" specifying the target parameter inside the "params" object according to the module description	
	* @param[out] response the response of the set parameter command in case of success	
	*/
	virtual void resetParameterToInitialValue(const id_t resolvedConfigID, const std::string& parameterPath, ConnectedVisionResponse &response);

	/**
	* recursively builds a rapidjson object of optional parameters with their default values defined by the parameter section of the module description
	* @param[in] currentNodeInModuleDescription the current node in the parameter description inside the module description
	* @param[out] defaultParameterNode the current node of the default parameter object to be built
	* @param[in] allocator the allocator for the new rapidjson::Value objects that are inserted into the default parameter object
	*/
	virtual void getDefaultParametersRecursiveAsRapidjson(const rapidjson::Value &currentNodeInModuleDescription, rapidjson::Value &defaultParameterNode, rapidjson::Value::AllocatorType &allocator);

	/**
	* checks the sanity of the parameter description inside the module description - this is done recursively	
	* @param[in] node the current node in the parameter tree to be processed (tested)
	* @param[in] expectDynamicValueToBeTrue indicates if the current node should have a member with "dynamic" set to true
	* @param[in] expectDynamicValueToBeTrue indicates if the current node is the content of an array (the "items" section)
	*/
	virtual void testDynamicParameterSanityAndUpdate(rapidjson::Value &node, bool expectDynamicValueToBeTrue, bool inSubArray = false);

	/**
    * the supported json value types for parameters
    */
	enum ParameterValueType {Integer64, Number, String, Boolean, Object, Array, Unsupported};

	/**
	* checks if a rapidjson value type is supported in ConnectedVision
	* @param[in] value the current value to be checked
	* @param[in] the required type that is expected of the value
	* @throws if the value does not match with the expected type or type itself is of type "Unsupported" an exception is thrown
	*/
	virtual void checkValueType(const rapidjson::Value &value, const ParameterValueType &type);

	/**
	* a node in the parameter description tree -
	* the parameter description tree is the mapping of the params object inside the module desciption into the c++-object @ref parameterDesc (a tree with a description of members of the given variable)
	*/
	typedef struct ParameterDescTreeNode
	{
		boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> pSubObject; ///< if empty -> no sub-object
		boost::shared_ptr<ParameterDescTreeNode> pSubArray; ///< if empty -> no sub-array

		/**
		* depending on what parameter type the node represents, this field stands for:\n
		* in case of plain parameter: specifies if parameter is dynamic\n
		* in case of object: If value is true the whole object is dynamic (all sub-elements must be dynamic)\n
		* in case of array: If value is true the array container is dynamic - this means that the number of
		* elements in the array may vary dynamically.
		* If it is true it also means that the elements inside the array container (in @ref pSubArray) are
		* automatically dynamic since the "dynamic" property is inherited by the actual array items.
		* If value is false this means the container is static - the number of array items is thus fixed,
		* but the array items itself (in @ref pSubArray) may be declared as "dynamic" (so their values can
		* be changed).
		* Do not mix up array items with array elements: an array item is a description for array elements.
		* If an array item is declared as dynamic all array elements are dynamic.
		* It is not possible to have individual array elements with different "dynamic" property.
		*/
		bool dynamic;

		/**
		* defines if the parameter is required or optional
		* if the node represents an array this means there must be the array container provided, e.g. "[]"
		* if the node represents an array item this means there must be elements in the array container as well, e.g. "[1, 2, 3]"
		*/
		bool required;

		/**
		* defines the value type of the parameter
		* note:
		* if type == Object -> pSubObject == !NULL
		* if type == Array -> pSubArray == !NULL
		*/
		ParameterValueType type;
	} ParameterDescTreeNode;

	/**
	* recursively builds the parameter description object
	* this function variant is used to process sub-objects
	* @param[in] node the current node in the parameter tree to be processed
	* @param[out] parameterDescTreeNode the current node in the parameter description tree to be built
	*/
	virtual void buildParameterDescriptionRecursive(const rapidjson::Value &node, boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> parameterDescTreeNode);

	/**
	* recursively builds the parameter description object
	* this function variant is used to process sub-arrays
	* @param[in] node the current node in the parameter tree to be processed
	* @param[out] parameterDescTreeNode the current node in the parameter description tree to be built
	*/
	virtual void buildParameterDescriptionRecursive(const rapidjson::Value &node, boost::shared_ptr<ParameterDescTreeNode> parameterDescTreeNode);

	/**
	* used to hold information about a node of the parameter description
	*/
	typedef struct ParameterDescriptionNodeInfo
	{
		//enum NodeType { Value, Object, Array };
		//NodeType type; ///< type of node

		ParameterValueType type; ///< type of node
		bool dynamic; ///< dynamic property of value, object (container) or array container
		bool dynamicItems; ///< used when type is Array: dynamic property of array items
		bool required; ///< required property of value, object (container) or array container
	} ParameterDescriptionNodeInfo;

	/**
	* queries if a given parameter inside to parameter description (part of the module description) is dynamic
	* @param parameterPath the path to the parameter of interest, e.g. "objectName/parameterName" will return the dynamic value of a parameter called "parameterName" inside an object parameter called "objectName"
	* @return the parameter description information of the node specified by @ref parameterPath according to the parameter description (inside the module description)
	*/
	virtual ParameterDescriptionNodeInfo queryParameterDescriptionInfo(const std::string parameterPath);

	/**
	* checks recursively if a given rapidjson::value for a parameter object contains the required value and sub-elements as specified by the "required" field (and the "required" fields of the sub-objects/sub-arrays) of the parameter description (of the module description)
	* further checks if the provided value matches the expected type
	* @param parameterDescTreeNode the node of the parameter description tree that describes the parameter to be tested
	* @param currentParameterNode the node (rapidjson::Value object) of the parameter of interest to be tested
	* @throws in case the parameter does not fulfill the requirements arising from the "required" field (also in sub-objects/sub-arrays) according to the parameter description (inside the module description)
	*/
	virtual void checkRecursivelyRequiredParametersAndType(const boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> &parameterDescTreeNode, const rapidjson::Value &currentParameterNode);

	/**
	* checks recursively if a given rapidjson::value for a parameter array contains the required value and sub-elements as specified by the "required" field (and the "required" fields of the sub-objects/sub-arrays) of the parameter description (of the module description)
	* further checks if the provided value matches the expected type
	* @param parameterDescTreeNode the node of the parameter description tree that describes the parameter to be tested
	* @param currentParameterNode the node (rapidjson::Value object) of the parameter of interest to be tested
	* @throws in case the parameter does not fulfill the requirements arising from the "required" field (also in sub-objects/sub-arrays) according to the parameter description (inside the module description)
	*/
	virtual void checkRecursivelyRequiredParametersAndType(const boost::shared_ptr<ParameterDescTreeNode> &parameterDescTreeNode, const rapidjson::Value &currentParameterNode);

	/**
	* checks recursively if a given rapidjson::value for a parameter object contains any unkown member (parameter) which is not defined in the parameter description (of the module description)
	* @param parameterDescTreeNode the node of the parameter description tree that describes the parameter to be tested
	* @param currentParameterNode the node (rapidjson::Value object) of the parameter of interest to be tested
	* @throws in case a parameter was found which is not defined in the parameter description (inside the module description)
	*/
	virtual void checkRecursivelyIfParameterValueExistsInModuleDescription(const boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> &parameterDescTreeNode, const rapidjson::Value &currentParameterNode);

	/**
	* checks recursively if a given rapidjson::value for a parameter object contains any unkown member (parameter) which is not defined in the parameter description (of the module description)
	* this function variant is used to process sub-objects
	* @param parameterDescTreeNode the node of the parameter description tree that describes the parameter to be tested
	* @param currentInitialParameterNode the node (rapidjson::Value object) of the initial parameter of interest to be tested
	* @param currentParameterNode the node (rapidjson::Value object) of the parameter of interest to be tested
	* @param moduleAndconfigSupportDynamicParameters indicates if the module and the config in operation support dynamic parameters
	* @throws in case a non-dynamic parameter's initialParams value does not match the params value
	*/
	virtual void checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(const boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> &parameterDescTreeNode, const rapidjson::Value &currentInitialParameterNode, const rapidjson::Value &currentParameterNode, bool moduleAndconfigSupportDynamicParameters);

	/**
	* checks recursively if a given rapidjson::value for a parameter object contains any unkown member (parameter) which is not defined in the parameter description (of the module description)
	* this function variant is used to process sub-arrays
	* @param parameterDescTreeNode the node of the parameter description tree that describes the parameter to be tested
	* @param currentInitialParameterNode the node (rapidjson::Value object) of the initial parameter of interest to be tested
	* @param currentParameterNode the node (rapidjson::Value object) of the parameter of interest to be tested
	* @param moduleAndconfigSupportDynamicParameters indicates if the module and the config in operation support dynamic parameters
	* @throws in case a non-dynamic parameter's initialParams value does not match the params value
	*/
	virtual void checkRecursivelyIfNonDynamicInitialParamsAndParamsMatch(const boost::shared_ptr<ParameterDescTreeNode> parameterDescTreeNode, const rapidjson::Value &currentInitialParameterNode, const rapidjson::Value &currentParameterNode, bool moduleAndconfigSupportDynamicParameters);


	virtual void connectDB();

	virtual void initModuleDescription(const char moduleDescription[], const char moduleName[] = NULL, const char moduleID[] = NULL, const char moduleURI[] = NULL);
	virtual void initInputPinDescription(const char inputPinDescription[]);
	virtual void initOutputPinDescription(const char outputPinDescription[]);

	virtual int writeErrorLog(ConnectedVisionResponse &response, int status, std::string error);

	virtual void start(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController);
	virtual void stop(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController);
	virtual void reset(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController);
	virtual void recover(ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController> &workerController);

	ConnectedVision::shared_ptr<WorkerController> getWorkerController(const id_t configID);

protected:
	IModuleEnvironment *env;
	std::string moduleDescription;
	std::string inputPinDescription;
	std::string outputPinDescription;
	std::vector<pinID_t> inputPinIDs;
	std::vector<pinID_t> outputPinIDs;
	std::vector<boost::shared_ptr<Class_PinDescription>> inputPinDescriptions;
	std::vector<boost::shared_ptr<Class_PinDescription>> outputPinDescriptions;

	id_t moduleID;
	std::string moduleName;
	std::string moduleURI;
	
	DBConnection dbConn;

	/**
	* map that holds already initialized worker controllers
	*/
	ConnectedVision::thread_safe_map<id_t, ConnectedVision::shared_ptr<ConnectedVision::Module::WorkerController>> mapWorkerControllers;
	const timestamp_t workerTimeout;

	ConnectedVision::shared_ptr<ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_status>> statusStore;
	ConnectedVision::shared_ptr<ConnectedVision::DataHandling::IStore_ReadWrite<Class_generic_config>> configStore;

	bool ready;

	rapidjson::Document moduleDescriptionJSON; ///< rapidjson document for module description (needed for allocator)
	rapidjson::Value defaultParameters; ///< rapidjson object with default parameters of module

	/*
	* module specific control functions
	*/
	virtual void start(boost::shared_ptr<const Class_generic_config> constConfig) {}
	virtual void stop(boost::shared_ptr<const Class_generic_config> constConfig) {}
	virtual void reset(boost::shared_ptr<const Class_generic_config> constConfig) {}
	virtual void recover(boost::shared_ptr<const Class_generic_config> constConfig) {}

	/**
	* holds the parameter description object which provides required info about the parameter description (part of the module description) as c++-object
	* parameterDesc == NULL <-> params: {}
	*/
	boost::shared_ptr<std::map<std::string, ParameterDescTreeNode>> parameterDesc;
	
	/**
	* map that holds the cashed parameters of the configs - configID is the key, Value is of type CachedConfigParameters
	*/
	ConnectedVision::thread_safe_map<id_t, std::string> mapCachedConfigParameters;

	/**
	* configID map to syncronize set & delete config per configID
	*/
	std::map<id_t, ConnectedVision::shared_ptr<std__mutex>> mapLockedConfigs;
	std__mutex mapLockedConfigsMutex;

	ConnectedVision::thread_safe_map<id_t, bool> runningSuccessorList; ///< list which config ids of all running successor modules (used to manage control/stop control/reset mechanism when several processing chains that share sub-chains are involved

	std::map< pinID_t, boost::shared_ptr<InputPinPool_t> > inputPinsPool; // TODO: synchronization mechanism needed for initialization
	std::map< pinID_t, boost::shared_ptr<OutputPinPool_t> > outputPinsPool; // TODO: synchronization mechanism needed for initialization
// TODO	ConnectedVision::thread_safe_map< pinID_t, boost::shared_ptr<InputPinPool_t> > inputPinsPool; // TODO: synchronization mechanism needed for initialization
// TODO	ConnectedVision::thread_safe_map< pinID_t, boost::shared_ptr<OutputPinPool_t> > outputPinsPool; // TODO: synchronization mechanism needed for initialization

	// the module logo as cv::Mat image
	boost::shared_ptr<cv::Mat> logo;
};




}} // namespace scope

#endif // Module_BaseClass_def
