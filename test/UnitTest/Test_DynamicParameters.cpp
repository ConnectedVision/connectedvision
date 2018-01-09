/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// original author: Michael Rauter

#include <boost/date_time/posix_time/posix_time.hpp> // used for boost::posix_time::milliseconds(msecs)
#include <boost/thread/thread.hpp>  // used for boost::this_thread::sleep(boost::posix_time::milliseconds(msecs));

#include <vector>
#include <ConnectedVisionModule.h>
#include <IModuleEnvironment.h>
#include "TestHelper_Module.hpp"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {

namespace Module {

class TestWrapper_DynamicParameters : public ConnectedVisionModule
{
public:
	TestWrapper_DynamicParameters(const std::string moduleDescription, const char inputPinDescription[], const char outputPinDescription[]) :
		ConnectedVisionModule(moduleDescription.c_str(), inputPinDescription, outputPinDescription) {}

	// make function public
	void checkConfig(const Class_generic_config &config)
	{
		ConnectedVisionModule::checkConfig(config);
	}

	// dummy implementation of abstract functions

	void deleteResults(const boost::shared_ptr<const Class_generic_config> config) {}
	
	void prepareStores() { }

	void connectDB() 
	{
		LOG_SCOPE;

		// open DB		
		this->dbConn.init(":memory:", SQLITE_OPEN_CREATE);
	}

	boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID) 
	{
		boost::shared_ptr<IConnectedVisionInputPin> nullPtr;
		return nullPtr;
	}

	boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID)
	{
		boost::shared_ptr<IConnectedVisionOutputPin> nullPtr;
		return nullPtr;
	}

	boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
	{
		boost::shared_ptr<IConnectedVisionAlgorithmWorker> nullPtr;
		return nullPtr;
	}

public:
	ConnectedVision::shared_ptr<Class_generic_config> SetupConfigForTest(std::string configStr)
	{
		Class_generic_config configToCreate(configStr); // create temporal config object
		checkConfig(configToCreate);
		id_t configID = configToCreate.compute_id(); // get configID hash

		ConnectedVisionResponse response;
		setConfig("0", configStr, response); // create config in temporary database (e.g. memory database)

		// query temporary database for config
		boost::shared_ptr<const Class_generic_config> constConfig = getConfigStore()->getByID(configID);
		
		// clone config to make it writeable
		auto config = constConfig->copy();
		checkConfig(*config);

		return(config);
	}

	std::string getModuleDescription()
	{
		return this->moduleDescription;
	}

	void getDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, ConnectedVisionResponse &response)
	{
		ConnectedVisionModule::getDynamicParameter(resolvedConfigID, parameterPath, response);
	}

	void setDynamicParameter(const id_t resolvedConfigID, const std::string& parameterPath, const std::string& parameterValue, ConnectedVisionResponse &response)
	{
		ConnectedVisionModule::setDynamicParameter(resolvedConfigID, parameterPath, parameterValue, response);
	}

	void resetParameterToInitialValue(const id_t resolvedConfigID, const std::string& parameterPath, ConnectedVisionResponse &response)
	{
		ConnectedVisionModule::resetParameterToInitialValue(resolvedConfigID, parameterPath, response);
	}
};

const std::string moduleDescriptionPartBegin =
											"{ \"name\": \"TestWrapper_DynamicParameters\","
											"\"description\": \"\","
											"\"version\": 1.0,"
											"\"moduleID\": \"TestWrapper_DynamicParameters\","
											"\"moduleURI\": \"\","
											"\"APIVersion\": 0.5,"
											"\"moduleFeatures\": {"
												"\"supportsDynamicParameters\": true"
											"},"
											"\"author\": \"\",";

const std::string moduleDescriptionPartEnd = "}";

const std::string moduleDescription_emptyParams =
											moduleDescriptionPartBegin +
											"\"params\": {}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_emptyParamsSubObject =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": true,"
												"\"type\": \"object\","
												"\"properties\": {}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_wholeParamsDynamic_objectWithValueDynamicNotSpecified =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": true,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"dynamicValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"unit\": \"\""
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_wholeParamsDynamic_objectWithValueDynamicTrue =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": true,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"dynamicValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"unit\": \"\""
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_wholeParamsDynamic_objectWithValueDynamicFalse =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": true," // *
												"\"type\": \"object\","
												"\"properties\": {"
													"\"dynamicValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"dynamic\": false," // this is not allowed since above object with comment mark * is declared dynamic
														"\"unit\": \"\""
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_wholeParamsDynamic_objectWithOneDynamicValueTrueAndOneValueDynamicFalse =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": true," // *
												"\"type\": \"object\","
												"\"properties\": {"
													"\"dynamicValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"unit\": \"\""
													"},"
													"\"staticValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"dynamic\": false," // this is not allowed since above object with comment mark * is declared dynamic
														"\"unit\": \"\""
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_wholeParamsNotDynamic_objectWithOneDynamicValueTrueAndOneValueDynamicFalse =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"dynamicValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"unit\": \"\""
													"},"
													"\"staticValue\": {"
														"\"description\": \"\","
														"\"type\": \"integer\","
														"\"required\": true,"
														"\"dynamic\": false,"
														"\"unit\": \"\""
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsValueInObjectValid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"object\","
														"\"properties\": {"
															"\"dummy\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": false,"
																"\"unit\": \"\","
																"\"default\": 1,"
																"\"dynamic\": true"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsValueInObjectInvalid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"object\","
														"\"properties\": {"
															"\"dummy\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": false,"
																"\"unit\": \"\","
																"\"default\": 1,"
																"\"dynamic\": false" // this is not allowed since above object with comment mark * is declared dynamic
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsTwoValuesInObjectInvalid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"object\","
														"\"properties\": {"
															"\"dummy1\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": true,"
																"\"unit\": \"\","
																"\"dynamic\": true"
															"},"
															"\"dummy2\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": true,"
																"\"unit\": \"\","
																"\"dynamic\": false" // this is not allowed since above object with comment mark * is declared dynamic
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsObjectInObjectValid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"object\","
														"\"properties\": {"
															"\"subObject2\": {"
																"\"description\": \"\","
																"\"required\": true,"
																"\"dynamic\": true,"
																"\"type\": \"object\","
																"\"properties\": {"
																	"\"dummy\": {"
																		"\"description\": \"\","
																		"\"type\": \"integer\","
																		"\"required\": false,"
																		"\"unit\": \"\","
																		"\"default\": 1,"
																		"\"dynamic\": true"
																	"}"
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsObjectInObjectInvalid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"object\","
														"\"properties\": {"
															"\"subObject2\": {"
																"\"description\": \"\","
																"\"required\": true,"
																"\"dynamic\": false," // this is not allowed since above object with comment mark * is declared dynamic
																"\"type\": \"object\","
																"\"properties\": {"
																	"\"dummy\": {"
																		"\"description\": \"\","
																		"\"type\": \"integer\","
																		"\"required\": false,"
																		"\"unit\": \"\","
																		"\"default\": 1,"
																		"\"dynamic\": true"
																	"}"
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsValueInArrayValid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"type\": \"integer\","
															"\"required\": false,"
															"\"unit\": \"\","
															"\"default\": 1,"
															"\"dynamic\": true"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsValueInArrayValid2 = // array container with "dynamic": false, but array items dynamic (this is allowed)
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": false,"
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"type\": \"integer\","
															"\"required\": false,"
															"\"unit\": \"\","
															"\"default\": 1,"
															"\"dynamic\": true"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsValueInArrayInvalid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"type\": \"integer\","
															"\"required\": false,"
															"\"unit\": \"\","
															"\"default\": 1,"
															"\"dynamic\": false" // this is not allowed since above array container with comment mark * was already declared dynamic
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsArrayInArrayValid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"required\": true,"
															"\"dynamic\": true,"
															"\"type\": \"array\","
															"\"items\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": false,"
																"\"unit\": \"\","
																"\"default\": 1,"
																"\"dynamic\": true"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsArrayInArrayInvalid1 =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"required\": true,"
															"\"dynamic\": false," // this is not allowed since above array container with comment mark * was already declared dynamic
															"\"type\": \"array\","
															"\"items\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": false,"
																"\"unit\": \"\","
																"\"default\": 1,"
																"\"dynamic\": true"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsArrayInArrayInvalid2 =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"required\": true,"
															"\"dynamic\": true," // *
															"\"type\": \"array\","
															"\"items\": {"
																"\"description\": \"\","
																"\"type\": \"integer\","
																"\"required\": false,"
																"\"unit\": \"\","
																"\"default\": 1,"
																"\"dynamic\": false"  // this is not allowed since above array container with comment mark * was already declared dynamic
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsObjectInArrayValid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"required\": true,"
															"\"dynamic\": true,"
															"\"type\": \"object\","
															"\"properties\": {"
																"\"subObject\": {"
																	"\"description\": \"\","
																	"\"type\": \"integer\","
																	"\"required\": false,"
																	"\"unit\": \"\","
																	"\"default\": 1,"
																	"\"dynamic\": true"
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsObjectInArrayInvalid1 =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"required\": true,"
															"\"dynamic\": false," // this is not allowed since above array container with comment mark * was already declared dynamic
															"\"type\": \"object\","
															"\"properties\": {"
																"\"subObject\": {"
																	"\"description\": \"\","
																	"\"type\": \"integer\","
																	"\"required\": false,"
																	"\"unit\": \"\","
																	"\"default\": 1,"
																	"\"dynamic\": true"
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsObjectInArrayInvalid2 =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"array\","
														"\"items\": {"
															"\"description\": \"\","
															"\"required\": true,"
															"\"dynamic\": true," // *
															"\"type\": \"object\","
															"\"properties\": {"
																"\"subObject\": {"
																	"\"description\": \"\","
																	"\"type\": \"integer\","
																	"\"required\": false,"
																	"\"unit\": \"\","
																	"\"default\": 1,"
																	"\"dynamic\": false" // this is not allowed since above object with comment mark * is declared dynamic
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsArrayInObjectValid =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"object\","
														"\"properties\": {"
															"\"subObject2\": {"
																"\"description\": \"\","
																"\"required\": true,"
																"\"dynamic\": true,"
																"\"type\": \"array\","
																"\"items\": {"
																	"\"description\": \"\","
																	"\"type\": \"integer\","
																	"\"required\": false,"
																	"\"unit\": \"\","
																	"\"default\": 1,"
																	"\"dynamic\": true"
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsArrayInObjectInvalid1 =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true," // *
														"\"type\": \"object\","
														"\"properties\": {"
															"\"subObject2\": {"
																"\"description\": \"\","
																"\"required\": true,"
																"\"dynamic\": false," // this is not allowed since above object with comment mark * is declared dynamic
																"\"type\": \"array\","
																"\"items\": {"
																	"\"description\": \"\","
																	"\"type\": \"integer\","
																	"\"required\": false,"
																	"\"unit\": \"\","
																	"\"default\": 1,"
																	"\"dynamic\": true"
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;

const std::string moduleDescription_paramsArrayInObjectInvalid2 =
											moduleDescriptionPartBegin +
											"\"params\": {"
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"subObject\": {"
														"\"description\": \"\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"type\": \"object\","
														"\"properties\": {"
															"\"subObject2\": {"
																"\"description\": \"\","
																"\"required\": true,"
																"\"dynamic\": true," // *
																"\"type\": \"array\","
																"\"items\": {"
																	"\"description\": \"\","
																	"\"type\": \"integer\","
																	"\"required\": false,"
																	"\"unit\": \"\","
																	"\"default\": 1,"
																	"\"dynamic\": false" // this is not allowed since above array container with comment mark * was already declared dynamic
																"}"
															"}"
														"}"
													"}"
												"}"
											"}"
											+ moduleDescriptionPartEnd;


static const char inputPinDescription[] = "[]";
static const char outputPinDescription[] = "[]";

const std::string moduleDescriptionPartBegin_forConfigTests =
											"{ \"name\": \"TestWrapper_DynamicParameters\","
											"\"description\": \"\","
											"\"version\": 1.0,"
											"\"moduleID\": \"TestWrapper_DynamicParameters\","
											"\"moduleURI\": \"\","
											"\"APIVersion\": 0.5,";

const std::string moduleDescriptionPartEnd_forConfigTests =
											"\"author\": \"\","
											"\"params\": {" 											
												"\"description\": \"\","
												"\"required\": true,"
												"\"dynamic\": false,"
												"\"type\": \"object\","
												"\"properties\": {"
													"\"dummy\": {"
														"\"description\": \"parameter with member [dynamic] not specified\","
														"\"required\": true,"
														"\"unit\": \"\","
														"\"type\": \"integer\""
													"},"
													"\"dummy_dynamic_parameter\": {"
														"\"description\": \"a dynamic parameter\","
														"\"required\": false,"
														"\"unit\": \"\","
														"\"type\": \"integer\","
														"\"default\": 1,"
														"\"dynamic\": true"
													"},"
													"\"dummy_static_parameter\": {"
														"\"description\": \"an explicit static parameter\","
														"\"required\": false,"
														"\"unit\": \"\","
														"\"type\": \"integer\","
														"\"default\": 2,"
														"\"dynamic\": false"
													"},"
													"\"dummy_object\": {"
														"\"description\": \"an object with a dummy member\","
														"\"required\": true,"
														"\"type\": \"object\","
														"\"dynamic\": true,"
														"\"properties\": {"
															"\"dummy_value\": {"
																"\"description\": \"dummy value inside dummy_object\","
																"\"type\": \"integer\","
																"\"required\": true,"
																"\"unit\": \"\""
															"},"
															"\"dummy_value2\": {"
																"\"description\": \"dummy value inside dummy_object\","
																"\"type\": \"integer\","
																"\"required\": false,"
																"\"unit\": \"\","
																"\"default\": 1,"
																"\"dynamic\": true"
															"}"
														"}"
													"},"
													"\"dummy_object_with_object\": {"
														"\"description\": \"an object with a dummy member\","
														"\"required\": true,"
														"\"type\": \"object\","
														"\"dynamic\": true,"
														"\"properties\": {"
															"\"inner_object\": {"
																"\"description\": \"dummy value inside dummy_object\","
																"\"type\": \"object\","
																"\"required\": true,"
																"\"unit\": \"\","
																"\"properties\": {"
																	"\"dummy_value\": {"
																		"\"description\": \"dummy value inside dummy_object\","
																		"\"type\": \"integer\","
																		"\"required\": true,"
																		"\"unit\": \"\","
																		"\"dynamic\": true"
																	"}"
																"}"			
															"}"				
														"}"
													"},"
													"\"dummy_object_with_array\": {"
														"\"description\": \"an object with a dummy member\","
														"\"required\": true,"
														"\"type\": \"object\","
														"\"dynamic\": true,"
														"\"properties\": {"
															"\"inner_array\": {"
																"\"description\": \"an array of integers\","
																"\"type\": \"array\","
																"\"required\": true,"
																"\"dynamic\": true,"
																"\"items\": {"
																	"\"required\": true,"
																	"\"unit\": \"\","
																	"\"type\": \"integer\","
																	"\"dynamic\": true"
																"}"		
															"}"				
														"}"
													"},"
													"\"dummy_array\": {"
														"\"description\": \"an array of integers\","
														"\"type\": \"array\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"items\": {"
															"\"required\": true,"
															"\"unit\": \"\","
															"\"type\": \"integer\","
															"\"dynamic\": true"
														"}"
													"},"
													"\"dummy_array_with_items_not_required\": {"
														"\"description\": \"an array of integers (array items not required)\","
														"\"type\": \"array\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"items\": {"
															"\"required\": false,"
															"\"unit\": \"\","
															"\"type\": \"integer\","
															"\"default\": 0,"
															"\"dynamic\": true"
														"}"
													"},"
													"\"dummy_array_with_object\": {"
														"\"description\": \"an array of objects\","
														"\"type\": \"array\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"items\": {"
															"\"required\": true,"
															"\"unit\": \"\","
															"\"type\": \"object\","
															"\"dynamic\": true,"
															"\"properties\": {"
																"\"dummy_value\": {"
																	"\"description\": \"dummy value inside dummy_object\","
																	"\"type\": \"integer\","
																	"\"required\": true,"
																	"\"unit\": \"\","
																	"\"dynamic\": true"
																"}"
															"}"
														"}"
													"},"
													"\"dummy_non_required_array_with_object_with_non_required_member\": {" // for redmine issue #732
														"\"description\": \"\","
														"\"type\": \"array\","
														"\"required\": false,"
														"\"default\": [],"
														"\"dynamic\": true,"
														"\"items\": {"														
															"\"description\": \"\","
															"\"type\": \"object\","
															"\"properties\": {"
																"\"dummy_value\": {"
																	"\"description\": \"\","
																	"\"type\": \"string\","
																	"\"required\": true"
																"},"
																"\"dummy_value2\": {"
																	"\"description\": \"\","
																	"\"type\": \"number\","
																	"\"default\": 0.0,"
																	"\"required\": false"
																"}"
															"}"
														"}"
													"},"
													"\"dummy_array_of_strings\": { " // for redmine issue #731
														"\"description\": \"\","
														"\"type\": \"array\","
														"\"required\": false,"
 														"\"default\": [],"
														"\"items\": {"
															"\"type\": \"string\","
															"\"required\": false,"
															"\"default\": \"\""
														"}"
													"},"
													"\"dummy_array_with_array\": {"
														"\"description\": \"an array of objects\","
														"\"type\": \"array\","
														"\"required\": true,"
														"\"dynamic\": true,"
														"\"items\": {"
															"\"description\": \"an array inside of other array\","
															"\"type\": \"array\","
															"\"required\": true,"
															"\"dynamic\": true,"
															"\"items\": {"
																	"\"description\": \"dummy value inside array inside dummy_array_with_array\","
																	"\"type\": \"integer\","
																	"\"required\": true,"
																	"\"unit\": \"\","
																	"\"dynamic\": true"						
															"}"
														"}"
													"}"
												"}"	
											"}"
											"}";

const std::string moduleDescription_forConfigTests =
	moduleDescriptionPartBegin_forConfigTests +
	"\"moduleFeatures\": {"
		"\"supportsDynamicParameters\": true"
	"}," +
	moduleDescriptionPartEnd_forConfigTests;

const std::string moduleDescription_forConfigTestsNoDynamicParametersModule =
	moduleDescriptionPartBegin_forConfigTests +
	"\"moduleFeatures\": {"
		"\"supportsDynamicParameters\": false"
	"}," +
	moduleDescriptionPartEnd_forConfigTests;


const std::string configStr_DynamicParameters =
												"{ \"id\": \"\", \"name\": \"test config\", \"description\": \"\","
												"\"version\": 1, "
												"\"moduleID\": \"TestWrapper_DynamicParameters\", \"moduleURI\": \"\","
												"\"configFeatures\": {"
													"\"allowDynamicParameters\": true"
												"},"
												"\"params\": {"
												"\"dummy\": 1,"
												"\"dummy_dynamic_parameter\": 100,"
												"\"dummy_static_parameter\": 55,"
												"\"dummy_object\": {\"dummy_value\": 7},"
												"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
												"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
												"\"dummy_array\": [10,20,30,40,50],"
												"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
												"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"
												"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"
												"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}]"
												"},"
												"\"chain\": []"
												"}";

const std::string configStr_DynamicParameters_withAllowDynamicParametersFalse =
															"{ \"id\": \"\", \"name\": \"test config\", \"description\": \"\","
															"\"version\": 1, "
															"\"moduleID\": \"TestWrapper_DynamicParameters\", \"moduleURI\": \"\","
															"\"configFeatures\": {"
																"\"allowDynamicParameters\": false"
															"},"
															"\"params\": {"
															"\"dummy\": 1,"
															"\"dummy_dynamic_parameter\": 100,"
															"\"dummy_static_parameter\": 55,"
															"\"dummy_object\": {\"dummy_value\": 7},"
															"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
															"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
															"\"dummy_array\": [10,20,30,40,50],"
															"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
															"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"
															"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]]"															
															"},"
															"\"chain\": []"
															"}";

const std::string configStr_arrayOfStringsWrongType =
												"{ \"id\": \"\", \"name\": \"test config\", \"description\": \"\","
												"\"version\": 1, "
												"\"moduleID\": \"TestWrapper_DynamicParameters\", \"moduleURI\": \"\","
												"\"configFeatures\": {"
													"\"allowDynamicParameters\": true"
												"},"
												"\"params\": {"
												"\"dummy\": 1,"
												"\"dummy_dynamic_parameter\": 100,"
												"\"dummy_static_parameter\": 55,"
												"\"dummy_object\": {\"dummy_value\": 7},"
												"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
												"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
												"\"dummy_array\": [10,20,30,40,50],"
												"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
												"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"
												"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"
												"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
												"\"dummy_array_of_strings\": [{\"fieldName\": \"value\"}]" // for redmine issue #731 - not allowed: string expected, but this is an object
												"},"
												"\"chain\": []"
												"}";


TEST_GROUP(DynamicParameters_moduleDescriptions)
{
	void setup()
	{
		// Init stuff
		this->module.reset();
	}

	void teardown()
	{
		// Uninit stuff
		this->module.reset();
	}

	ModuleEnvironment_Mockup env;
	boost::shared_ptr<TestWrapper_DynamicParameters> module;
};

TEST_GROUP(DynamicParameters_moduleAndConfigFeaturesRelatedToDynamicParameters)
{
	void setup()
	{
		// Init stuff
		this->module.reset();
	}

	void teardown()
	{
		// Uninit stuff
		this->module.reset();
	}

	ModuleEnvironment_Mockup env;
	boost::shared_ptr<TestWrapper_DynamicParameters> module;
};

TEST_GROUP(DynamicParameters_configs)
{
	void setup()
	{
		// Init stuff
		this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_forConfigTests, inputPinDescription, outputPinDescription);
		this->module->initModule(&env);
	}

	void teardown()
	{
		// Uninit stuff
		this->module.reset();
	}

	ModuleEnvironment_Mockup env;
	boost::shared_ptr<TestWrapper_DynamicParameters> module;
};


/////////////////////////////////////////////////////////////////////// tests for dynamic parameters regarding module description format ///////////////////////////////////////////////////////////////

TEST(DynamicParameters_moduleDescriptions, paramsEmpty)
{
	//////////////////////////////////////
	// test initialization = actual test (no exception should be thrown)
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_emptyParams, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsEmptySubObject)
{
	//////////////////////////////////////
	// test initialization actual test (no exception should be thrown)
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_emptyParamsSubObject, inputPinDescription, outputPinDescription);
	CHECK(true);
}


TEST(DynamicParameters_moduleDescriptions, wholeParamsDynamic_ParamsObjectWithValueDynamicNotSpecified)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_wholeParamsDynamic_objectWithValueDynamicNotSpecified, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, wholeParamsDynamic_ParamsObjectWithValueDynamicTrue)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_wholeParamsDynamic_objectWithValueDynamicTrue, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, wholeParamsDynamic_objectWithValueDynamicFalse)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_wholeParamsDynamic_objectWithValueDynamicFalse, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, wholeParamsDynamic_objectWithOneDynamicValueTrueAndOneValueDynamicFalse)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_wholeParamsDynamic_objectWithOneDynamicValueTrueAndOneValueDynamicFalse, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, wholeParamsNotDynamic_objectWithOneDynamicValueTrueAndOneValueDynamicFalse)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_wholeParamsNotDynamic_objectWithOneDynamicValueTrueAndOneValueDynamicFalse, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsValueInObjectValid)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsValueInObjectValid, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsValueInObjectInvalid)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsValueInObjectInvalid, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsTwoValuesInObjectInvalid)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsTwoValuesInObjectInvalid, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsObjectInObjectValid)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsObjectInObjectValid, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsObjectInObjectInvalid)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsObjectInObjectInvalid, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsValueInArrayValid)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsValueInArrayValid, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsValueInArrayValid2)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsValueInArrayValid2, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsValueInArrayInvalid)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsValueInArrayInvalid, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsArrayInArrayValid)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsArrayInArrayValid, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsArrayInArrayInvalid1)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsArrayInArrayInvalid1, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsArrayInArrayInvalid2)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsArrayInArrayInvalid2, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsObjectInArrayValid)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)	
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsObjectInArrayValid, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsObjectInArrayInvalid1)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsObjectInArrayInvalid1, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsObjectInArrayInvalid2)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsObjectInArrayInvalid2, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsArrayInObjectValid)
{
	//////////////////////////////////////
	// initialization = actual test (no exception should be thrown)
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsArrayInObjectValid, inputPinDescription, outputPinDescription);
	CHECK(true);
}

TEST(DynamicParameters_moduleDescriptions, paramsArrayInObjectInvalid1)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsArrayInObjectInvalid1, inputPinDescription, outputPinDescription));
}

TEST(DynamicParameters_moduleDescriptions, paramsArrayInObjectInvalid2)
{
	//////////////////////////////////////
	// initialization = actual test (should thrown exception)
	CHECK_THROWS(ConnectedVision::runtime_error, this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_paramsArrayInObjectInvalid2, inputPinDescription, outputPinDescription));
}



/////////////////////////////////////////////////////////////////////// tests for dynamic parameters regarding module and config features ///////////////////////////////////////////////////////////////

TEST(DynamicParameters_moduleAndConfigFeaturesRelatedToDynamicParameters, noSetWhenModuleIsNoDynamicParametersModule)
{
	//////////////////////////////////////
	// test initialization
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_forConfigTestsNoDynamicParametersModule, inputPinDescription, outputPinDescription);
	this->module->initModule(&env);

	//////////////////////////////////////
	// actual test - invalid moduleFeatures/supportsDynamicParameters and configFeatures/allowDynamicParameters configuration
	ConnectedVision::shared_ptr<Class_generic_config> config;
	CHECK_THROWS(std::runtime_error, config = this->module->SetupConfigForTest(configStr_DynamicParameters));

	// obsolete since you cannot get here anymore...
	//auto configID = config->compute_id();
	//
	////////////////////////////////////////
	//// actual test
	//std::string value = "1001";
	//ConnectedVisionResponse responseFromSet;
	//CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_dynamic_parameter", value, responseFromSet));
}

TEST(DynamicParameters_moduleAndConfigFeaturesRelatedToDynamicParameters, noSetWhenConfigFeatureAllowDynamicParametersIsFalse)
{
	//////////////////////////////////////
	// test initialization
	this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_forConfigTests, inputPinDescription, outputPinDescription);
	this->module->initModule(&env);

	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters_withAllowDynamicParametersFalse);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "1001";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_dynamic_parameter", value, responseFromSet));
}



/////////////////////////////////////////////////////////////////////// tests for dynamic parameters regarding config use and parameter get/set commands ///////////////////////////////////////////////////////////////

TEST(DynamicParameters_configs, getPlainParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get value and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_dynamic_parameter", response);
	CHECK_EQUAL(response.content, "100");
}

TEST(DynamicParameters_configs, setPlainParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_dynamic_parameter", responseGetBeforeSet);
	CHECK_EQUAL(responseGetBeforeSet.content, "100");

	std::string value = "901";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_dynamic_parameter", value, responseFromSet);
	CHECK_EQUAL(responseFromSet.content, value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_dynamic_parameter", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(responseGetAfterSet.content, value);
}

TEST(DynamicParameters_configs, setPlainParameterWithWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a wrong value type for the parameter should result in an exception
	std::string value = "\"aStringIsTheWrongTypeHere\"";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_dynamic_parameter", value, responseFromSet));
}

TEST(DynamicParameters_configs, tryToSetPlainParameterNonDynamic)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a parameter which was specified as non-dynamic parameter should result in an exception, afterwards get should yield old value
	std::string value = "18";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_static_parameter", value, responseFromSet));

	ConnectedVisionResponse responseGet;
	this->module->getDynamicParameter(configID, "dummy_static_parameter", responseGet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(responseGet.content, "55");
}

TEST(DynamicParameters_configs, tryToSetPlainParameterWithDynamicNotSpecifiedButInheritedAsNonDynamic)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a parameter with non-specified member "dynamic" and thus inheriting from parent object (which was specified as non-dynamic) should result in an exception, afterwards get should yield old value
	std::string value = "16";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy", value, responseFromSet));

	ConnectedVisionResponse responseGet;
	this->module->getDynamicParameter(configID, "dummy", responseGet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(responseGet.content, "1");
}

TEST(DynamicParameters_configs, getObjectParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get object and compare it if it matches expected object
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_object", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "{\"dummy_value\":7,\"dummy_value2\":1}");
}

TEST(DynamicParameters_configs, setObjectParameterOnlyRequired)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set object and compare if its response matches the expected object, also test before and after set via get command if it matches the expected object
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "{\"dummy_value\":7,\"dummy_value2\":1}");

	std::string value = "{\"dummy_value\":38}";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), "{\"dummy_value\":38,\"dummy_value2\":1}"); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), "{\"dummy_value\":38,\"dummy_value2\":1}");
}

TEST(DynamicParameters_configs, setObjectParameterOnlyRequiredOptionalResetingToDefault)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "{\"dummy_value\":7,\"dummy_value2\":1}");

	std::string value = "{\"dummy_value\":38,\"dummy_value2\":83}";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object", responseGetAfterSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);

	value = "{\"dummy_value\":38}";
	this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), "{\"dummy_value\":38,\"dummy_value2\":1}"); // check if optional parameter is reset back to default value

	this->module->getDynamicParameter(configID, "dummy_object", responseGetAfterSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), "{\"dummy_value\":38,\"dummy_value2\":1}");
}

TEST(DynamicParameters_configs, setObjectParameterAll)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "{\"dummy_value\":7,\"dummy_value2\":1}");

	std::string value = "{\"dummy_value\":76,\"dummy_value2\":22}";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setObjectParameterMissingRequiredValue)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a object without a required (sub-)parameter
	std::string value = "{\"dummy_value2\":89}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet));
}

TEST(DynamicParameters_configs, setObjectParameterWithWrongTypeArray)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a wrong value type for the parameter should result in an exception
	std::string value = "[11,12,13]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet));
}

TEST(DynamicParameters_configs, setObjectParameterWithWrongTypePlain)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a wrong value type for the parameter should result in an exception
	std::string value = "\"aStringIsTheWrongTypeHere\"";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet));
}

TEST(DynamicParameters_configs, setObjectParameterTryingToSetValueNotExisting)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a object without a required (sub-)parameter
	std::string value = "{\"dummy_value\":7,\"dummy_value2\":1,\"value_not_existing\":666}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object", value, responseFromSet));
}

TEST(DynamicParameters_configs, getObjectWithInnerObjectParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get object and compare it if it matches expected object
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_object_with_object", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "{\"inner_object\":{\"dummy_value\":43}}");
}

TEST(DynamicParameters_configs, setObjectWithInnerObjectParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set object and compare if its response matches the expected object, also test before and after set via get command if it matches the expected object
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_object", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "{\"inner_object\":{\"dummy_value\":43}}");

	std::string value = "{\"inner_object\":{\"dummy_value\":15}}";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object_with_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_object", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setObjectWithInnerObjectParameterSetInnerObject)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set object and compare if its response matches the expected object, also test before and after set via get command if it matches the expected object
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_object/inner_object", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "{\"dummy_value\":43}");

	std::string value = "{\"dummy_value\":15}";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object_with_object/inner_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_object/inner_object", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setObjectWithInnerObjectParameterSetParameterOfInnerObject)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set object and compare if its response matches the expected object, also test before and after set via get command if it matches the expected object
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_object/inner_object/dummy_value", responseGetBeforeSet);
	CHECK_EQUAL(responseGetBeforeSet.content, "43");

	std::string value = "15";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object_with_object/inner_object/dummy_value", value, responseFromSet);
	CHECK_EQUAL(responseFromSet.content, value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_object/inner_object/dummy_value", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(responseGetAfterSet.content, value);
}

TEST(DynamicParameters_configs, setObjectWithInnerObjectParameterMissingRequiredValueAndTryingToSetValueNot)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a object without a required (sub-)parameter
	std::string value = "{\"inner_object\":{}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object_with_object", value, responseFromSet));
}

TEST(DynamicParameters_configs, setObjectWithInnerObjectParameterTryingToSetValueNotExisting)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - trying to set a object without a required (sub-)parameter
	std::string value = "{\"inner_object\":{\"dummy_value\":15,\"value_not_existing\":666}}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object_with_object", value, responseFromSet));
}

TEST(DynamicParameters_configs, getObjectWithInnerArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get array inside of object and compare it if it matches expected array
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_object_with_array", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "{\"inner_array\":[25,50,75,100]}");
}

TEST(DynamicParameters_configs, setObjectWithInnerArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set array in object and compare if its response matches the expected array, also test before and after set via get command if it matches the expected array
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_array", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "{\"inner_array\":[25,50,75,100]}");

	std::string value = "{\"inner_array\":[101,102,103,104]}";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object_with_array", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_array", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setObjectWithInnerArrayParameterSetInnerArray)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_array/inner_array", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[25,50,75,100]");

	std::string value = "[101,102,103,104]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object_with_array/inner_array", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_object_with_array/inner_array", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setObjectWithInnerArrayParameterWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "{\"inner_array\": {}}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object_with_array", value, responseFromSet));
}

TEST(DynamicParameters_configs, setObjectWithInnerArrayParameterMissingRequiredArrayItems)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "{\"inner_array\":[]}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object_with_array", value, responseFromSet));
}

TEST(DynamicParameters_configs, setObjectWithInnerArrayParameterItemsOfWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "{\"inner_array\":[1,\"string not allowed\",2]}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_object_with_array", value, responseFromSet));
}

TEST(DynamicParameters_configs, getArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get array and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[10,20,30,40,50]");
}

TEST(DynamicParameters_configs, setArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set array and compare if its response matches the expected array, also test before and after set via get command if it matches the expected array
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[10,20,30,40,50]");

	std::string value = "[999,888,777,666,555]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setArrayParameterWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "{}";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array", value, responseFromSet));
}

TEST(DynamicParameters_configs, setArrayParameterMissingRequiredArrayItems)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array", value, responseFromSet));
}

TEST(DynamicParameters_configs, setArrayParameterWithArrayItemsOfWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[1,\"string not allowed\",2]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array", value, responseFromSet));
}

TEST(DynamicParameters_configs, setArrayParameterWithArrayOfStringsItemsOfWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[12]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_of_strings", value, responseFromSet));
}

TEST(DynamicParameters_configs, setArrayParameterEmptyArrayItemsWhenAllowed)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array_with_items_not_required", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[1,2,3,4,5]");

	std::string value = "[]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array_with_items_not_required", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), "[]"); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array_with_items_not_required", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), "[]");
}

TEST(DynamicParameters_configs, getArrayWithInnerObjectParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get array and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array_with_object", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[{\"dummy_value\":10},{\"dummy_value\":20},{\"dummy_value\":30},{\"dummy_value\":40},{\"dummy_value\":50}]");
}

TEST(DynamicParameters_configs, setArrayWithInnerObjectParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set array and compare if its response matches the expected array, also test before and after set via get command if it matches the expected array
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array_with_object", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[{\"dummy_value\":10},{\"dummy_value\":20},{\"dummy_value\":30},{\"dummy_value\":40},{\"dummy_value\":50}]");

	std::string value = "[{\"dummy_value\":333},{\"dummy_value\":222},{\"dummy_value\":111}]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array_with_object", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array_with_object", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, getArrayWithInnerObjectParameterTryingToGetInnerObjectWhichIsNotAllowed)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseFromGet;
	CHECK_THROWS(std::runtime_error, this->module->getDynamicParameter(configID, "dummy_array_with_object/dummy_value", responseFromGet));
}

TEST(DynamicParameters_configs, setArrayWithInnerObjectParameterTryingToSetInnerObjectWhichIsNotAllowed)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "666";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_object/dummy_value", value, responseFromSet));
}

TEST(DynamicParameters_configs, getArrayWithInnerArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get array of array and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array_with_array", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[[10,20,30,40,50],[90,80,70]]");
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set array of array and compare if its response matches the expected array, also test before and after set via get command if it matches the expected array of array
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array_with_array", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[[10,20,30,40,50],[90,80,70]]");

	std::string value = "[[19,17,15,13],[1,4,7,10,13,16],[9]]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array_with_array", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameterOuterArrayInvalidEmptyArrayContainer)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[[29,27,25,23,21],{},[7]]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet));	
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameterOuterArrayInvalidArrayItemWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[[29,27,25,23,21],\"aStringIsWrongTypeHere\",[7]]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet));	
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameterOuterArrayInvalidArrayItemWrongTypeObject)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[[29,27,25,23,21],{},[7]]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet));	
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameterInnerArrayInvalidEmptyArrayContainer)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[[29,27,25,23,21],[],[7]]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet));	
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameterInnerArrayInvalidArrayItemWrongType)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[[29,27,25,23,21],[\"aStringIsNotAllowedHere\"],[7]]";
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet));	
}

TEST(DynamicParameters_configs, setArrayWithInnerArrayParameterInnerArrayInvalidArrayItemWrongTypeObject)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	std::string value = "[[29,27,25,23,21],[{}],[7]]";	
	ConnectedVisionResponse responseFromSet;
	CHECK_THROWS(std::runtime_error, this->module->setDynamicParameter(configID, "dummy_array_with_array", value, responseFromSet));	
}

TEST(DynamicParameters_configs, setNonRequiredArrayWithObjectWithNonRequiredMember)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_non_required_array_with_object_with_non_required_member", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[{\"dummy_value\":\"initialValue\"}]");

	std::string value = "[{\"dummy_value\":\"test\"}]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_non_required_array_with_object_with_non_required_member", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_non_required_array_with_object_with_non_required_member", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_configs, setArrayOfStringsWrongType) // test for redmine issue #731
{
	//////////////////////////////////////
	// test initialization = actual test
	CHECK_THROWS(ConnectedVision::runtime_error, this->module->SetupConfigForTest(configStr_arrayOfStringsWrongType));
}



/////////////////////////////////////////////////////////////////////// tests for resetting params to initialParams ///////////////////////////////////////////////////////////////

TEST(DynamicParameters_configs, resetWholeParamsObject)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();

	const std::string referenceValue =	
								"{"
								"\"dummy\": 1,"
								"\"dummy_dynamic_parameter\": 100,"
								"\"dummy_static_parameter\": 55,"
								"\"dummy_object\": {\"dummy_value\": 7, \"dummy_value2\": 1},"
								"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
								"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
								"\"dummy_array\": [10,20,30,40,50],"
								"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
								"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"
								"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"
								"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
								"\"dummy_array_of_strings\": []"
								"}";

	const std::string referenceValueAfterSet =	
								"{"
								"\"dummy\": 1,"
								"\"dummy_dynamic_parameter\": 100,"
								"\"dummy_static_parameter\": 55,"
								"\"dummy_object\": {\"dummy_value\": 84, \"dummy_value2\": 35},"
								"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
								"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
								"\"dummy_array\": [8,6,4,2,0,-2],"
								"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
								"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"
								"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"															
								"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
								"\"dummy_array_of_strings\": []"
								"}";

	const std::string referenceValueAfterReset =	
								"{"
								"\"dummy\": 1,"
								"\"dummy_dynamic_parameter\": 100,"
								"\"dummy_static_parameter\": 55,"
								"\"dummy_object\": {\"dummy_value\": 7, \"dummy_value2\": 1},"
								"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
								"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
								"\"dummy_array\": [10,20,30,40,50],"
								"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
								"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"
								"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"
								"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
								"\"dummy_array_of_strings\": []"
								"}";
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseFromGet;
	this->module->getDynamicParameter(configID, "", responseFromGet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromGet.content), trimStringAndRemoveSpaces(referenceValue));

	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object", "{\"dummy_value\": 84, \"dummy_value2\": 35}", responseFromSet);
	this->module->setDynamicParameter(configID, "dummy_array", "[8,6,4,2,0,-2]", responseFromSet);
	ConnectedVisionResponse responseFromGetAfterSet;
	this->module->getDynamicParameter(configID, "", responseFromGetAfterSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromGetAfterSet.content), trimStringAndRemoveSpaces(referenceValueAfterSet));

	ConnectedVisionResponse responseFromGetAfterReset;
	this->module->resetParameterToInitialValue(configID, "", responseFromGetAfterReset);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromGetAfterReset.content), trimStringAndRemoveSpaces(referenceValueAfterReset));
}

TEST(DynamicParameters_configs, resetParamsSubObject)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_DynamicParameters);
	auto configID = config->compute_id();

	const std::string referenceValue =	
								"{"
								"\"dummy\": 1,"
								"\"dummy_dynamic_parameter\": 100,"
								"\"dummy_static_parameter\": 55,"
								"\"dummy_object\": {\"dummy_value\": 7, \"dummy_value2\": 1},"
								"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
								"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
								"\"dummy_array\": [10,20,30,40,50],"
								"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
								"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"								
								"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"
								"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
								"\"dummy_array_of_strings\": []"
								"}";

	const std::string referenceValueAfterSet =	
								"{"
								"\"dummy\": 1,"
								"\"dummy_dynamic_parameter\": 100,"
								"\"dummy_static_parameter\": 55,"
								"\"dummy_object\": {\"dummy_value\": 84, \"dummy_value2\": 35},"
								"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
								"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
								"\"dummy_array\": [8,6,4,2,0,-2],"
								"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
								"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"								
								"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"
								"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
								"\"dummy_array_of_strings\": []"
								"}";

	const std::string referenceValueAfterReset =	
								"{"
								"\"dummy\": 1,"
								"\"dummy_dynamic_parameter\": 100,"
								"\"dummy_static_parameter\": 55,"
								"\"dummy_object\": {\"dummy_value\": 7, \"dummy_value2\": 1},"
								"\"dummy_object_with_object\": {\"inner_object\": {\"dummy_value\": 43}},"
								"\"dummy_object_with_array\": {\"inner_array\": [25,50,75,100]},"
								"\"dummy_array\": [8,6,4,2,0,-2],"
								"\"dummy_array_with_items_not_required\": [1,2,3,4,5],"
								"\"dummy_array_with_object\": [{\"dummy_value\": 10}, {\"dummy_value\": 20}, {\"dummy_value\": 30}, {\"dummy_value\": 40}, {\"dummy_value\": 50}],"								
								"\"dummy_array_with_array\": [[10,20,30,40,50],[90,80,70]],"															
								"\"dummy_non_required_array_with_object_with_non_required_member\": [{\"dummy_value\":\"initialValue\"}],"
								"\"dummy_array_of_strings\": []"
								"}";
	
	//////////////////////////////////////
	// actual test
	ConnectedVisionResponse responseFromGet;
	this->module->getDynamicParameter(configID, "", responseFromGet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromGet.content), trimStringAndRemoveSpaces(referenceValue));

	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_object", "{\"dummy_value\": 84, \"dummy_value2\": 35}", responseFromSet); // change "dummy_object" value (this should be affected by reset to "dummy_object")
	this->module->setDynamicParameter(configID, "dummy_array", "[8,6,4,2,0,-2]", responseFromSet); // change "dummy_array" value (this should not be affected by reset to "dummy_object")
	ConnectedVisionResponse responseFromGetAfterSet;
	this->module->getDynamicParameter(configID, "", responseFromGetAfterSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromGetAfterSet.content), trimStringAndRemoveSpaces(referenceValueAfterSet));

	ConnectedVisionResponse responseFromReset;
	this->module->resetParameterToInitialValue(configID, "dummy_object", responseFromReset);

	// test for expected params object -> if "dummy_object" value was reset, but "dummy_array" value was not reset
	ConnectedVisionResponse responseFromGetAfterReset;
	this->module->getDynamicParameter(configID, "", responseFromGetAfterReset);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromGetAfterReset.content), trimStringAndRemoveSpaces(referenceValueAfterReset));
}



/////////////////////////////////////////////////////////////////////// tests for module with non-required dynamic parameters ///////////////////////////////////////////////////////////////

const std::string moduleDescription_forConfigTestsNonRequiredDynamicParametersModule =
	"{ \"name\": \"TestWrapper_DynamicParameters\","
	"\"description\": \"\","
	"\"version\": 1.0,"
	"\"moduleID\": \"TestWrapper_DynamicParameters\","
	"\"moduleURI\": \"\","
	"\"APIVersion\": 0.5,"
	"\"moduleFeatures\": {"
		"\"supportsDynamicParameters\": true"
	"},"
	"\"author\": \"\","
	"\"params\": {" 											
		"\"description\": \"\","
		"\"required\": true,"
		"\"dynamic\": false,"
		"\"type\": \"object\","
		"\"properties\": {"
			"\"dummy_dynamic_non_required_parameter\": {"
				"\"description\": \"a non-required dynamic parameter\","
				"\"required\": false,"
				"\"unit\": \"\","
				"\"type\": \"integer\","
				"\"default\": 1,"
				"\"dynamic\": true"
			"},"
			"\"dummy_array_dynamic_non_required\": {"
				"\"description\": \"an array of integers\","
				"\"type\": \"array\","
				"\"required\": false,"
				"\"default\": [0,1,2],"
				"\"dynamic\": true,"
				"\"items\": {"
					"\"required\": false,"
					"\"unit\": \"\","
					"\"type\": \"integer\","
					"\"dynamic\": true"
				"}"
			"},"
			"\"dummy_array_of_array_dynamic_non_required\": {"
				"\"description\": \"an array of objects\","
				"\"type\": \"array\","
				"\"required\": false,"
				"\"default\": [[0,1,2],[3,4,5],[6,7,8]],"
				"\"dynamic\": true,"
				"\"items\": {"
					"\"description\": \"an array inside of other array\","
					"\"type\": \"array\","
					"\"required\": false,"
					"\"dynamic\": true,"
					"\"items\": {"
							"\"description\": \"dummy value inside array inside dummy_array_with_array\","
							"\"type\": \"integer\","
							"\"required\": false,"
							"\"unit\": \"\","
							"\"dynamic\": true"						
					"}"
				"}"
			"},"
			"\"dummy_array2_dynamic_non_required\": {"
				"\"description\": \"an array of integers\","
				"\"type\": \"array\","
				"\"required\": false,"
				"\"default\": [],"
				"\"dynamic\": true,"
				"\"items\": {"
					"\"required\": false,"
					"\"unit\": \"\","
					"\"type\": \"integer\","
					"\"dynamic\": true"
				"}"
			"},"
			"\"dummy_array_of_objects_dynamic_non_required\":"
			"{"
				"\"description\": \"an array of objects\","
				"\"type\": \"array\","
				"\"required\": false,"
				"\"default\": [],"
				"\"dynamic\": true,"
				"\"items\":"
				"{"
					"\"description\": \"object inside the array\","
						"\"type\": \"object\","
						"\"exttype\": \"rectangle\","
						"\"required\": false,"
						"\"properties\":"
						"{"
						"\"a\":"
						"{"
							"\"type\": \"number\","
							"\"description\": \"a number\","
							"\"minimum\": 0.0,"
							"\"maximum\": 1.0,"
							"\"default\": 0.0,"
							"\"required\": false"
						"},"
						"\"b\":"
						"{"
							"\"type\": \"number\","
							"\"description\": \"a number\","
							"\"minimum\": 0.0,"
							"\"maximum\": 1.0,"
							"\"default\": 0.0,"
							"\"required\": false"
						"}"
					"}"
				"}"
			"}"
		"}"	
	"}"
	"}";

const std::string configStr_NonRequiredDynamicParametersModule =
																"{ \"id\": \"\", \"name\": \"test config\", \"description\": \"\","
																"\"version\": 1, "
																"\"moduleID\": \"TestWrapper_DynamicParameters\", \"moduleURI\": \"\","
																"\"configFeatures\": {"
																	"\"allowDynamicParameters\": true"
																"},"
																"\"params\": {"													
																"},"
																"\"chain\": []"
																"}";


TEST_GROUP(DynamicParameters_moduleWithNonRequiredDynamicParameters)
{
	void setup()
	{
		// Init stuff
		this->module = boost::make_shared<TestWrapper_DynamicParameters>(moduleDescription_forConfigTestsNonRequiredDynamicParametersModule, inputPinDescription, outputPinDescription);
		this->module->initModule(&env);
	}

	void teardown()
	{
		// Uninit stuff
		this->module.reset();
	}

	ModuleEnvironment_Mockup env;
	boost::shared_ptr<TestWrapper_DynamicParameters> module;
};


TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, getNonRequiredDynamicPlainParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get value and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_dynamic_non_required_parameter", response);
	CHECK_EQUAL(response.content, "1");
}


TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, setNonRequiredDynamicPlainParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_dynamic_non_required_parameter", responseGetBeforeSet);
	CHECK_EQUAL(responseGetBeforeSet.content, "1");

	std::string value = "733";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_dynamic_non_required_parameter", value, responseFromSet);
	CHECK_EQUAL(responseFromSet.content, value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_dynamic_non_required_parameter", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(responseGetAfterSet.content, value);
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, getNonRequiredDynamicArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get value and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array_dynamic_non_required", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[0,1,2]");
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, setNonRequiredDynamicArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array_dynamic_non_required", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[0,1,2]");

	std::string value = "[78,23,41,90]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array_dynamic_non_required", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array_dynamic_non_required", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, getNonRequiredDynamicArrayOfArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get value and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array_of_array_dynamic_non_required", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[[0,1,2],[3,4,5],[6,7,8]]");
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, setNonRequiredDynamicArrayOfArrayParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array_of_array_dynamic_non_required", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[[0,1,2],[3,4,5],[6,7,8]]");

	std::string value = "[[22,51,62,6,5,3],[643,71,8991,12,11]]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array_of_array_dynamic_non_required", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array_of_array_dynamic_non_required", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, getNonRequiredDynamicArrayParameterWithEmptyDefaultArray)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get value and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array2_dynamic_non_required", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[]");
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, setNonRequiredDynamicArrayParameterWithEmptyDefaultArray)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array2_dynamic_non_required", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[]");

	std::string value = "[19,20,21,22,23,24,25,26,0,-20]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array2_dynamic_non_required", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), value); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array2_dynamic_non_required", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), value);
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, getNonRequiredDynamicArrayOfObjectsParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - get value and compare it if it matches expected value
	ConnectedVisionResponse response;
	this->module->getDynamicParameter(configID, "dummy_array_of_objects_dynamic_non_required", response);
	CHECK_EQUAL(trimStringAndRemoveSpaces(response.content), "[]");
}

TEST(DynamicParameters_moduleWithNonRequiredDynamicParameters, setNonRequiredDynamicArrayOfObjectsParameter)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_NonRequiredDynamicParametersModule);
	auto configID = config->compute_id();
	
	//////////////////////////////////////
	// actual test - set value and compare if its response matches the expected value, also test before and after set via get command if it matches the expected values
	ConnectedVisionResponse responseGetBeforeSet;
	this->module->getDynamicParameter(configID, "dummy_array_of_objects_dynamic_non_required", responseGetBeforeSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetBeforeSet.content), "[]");

	std::string value = "["
            "{\"a\": 0.334375,\"b\": 0.915},"
            "{\"a\": 0.41875,\"b\": 0.8475}"
			"]";
	ConnectedVisionResponse responseFromSet;
	this->module->setDynamicParameter(configID, "dummy_array_of_objects_dynamic_non_required", value, responseFromSet);
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseFromSet.content), trimStringAndRemoveSpaces(value)); // check if response of function setDynamicParameter has expected value

	ConnectedVisionResponse responseGetAfterSet;
	this->module->getDynamicParameter(configID, "dummy_array_of_objects_dynamic_non_required", responseGetAfterSet); // check if response of function getDynamicParameter has expected value (function getDynamicParameter will reload config from store)
	CHECK_EQUAL(trimStringAndRemoveSpaces(responseGetAfterSet.content), trimStringAndRemoveSpaces(value));
}

} // namespace Module
} // namespace ConnectedVision