/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <vector>
#include <Module/Module_BaseClass.h>
#include "TestHelper_Module.hpp"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {
namespace Module {

/*
* helper funtcion to add a connection to a config
*/
static void addConnection(
	boost::shared_ptr<Class_generic_config_chain>& chainItem,	///< [in/out] chainItem object
	const std::string& inputPinID,	///< [in] ID of input pin for connection
	const std::string& outputPinID	///< [in] ID of input pin for connection
	)
{
	Class_generic_config_chain_connections connection;
	connection.set_inputPinID(inputPinID);
	connection.set_outputPinID(outputPinID);
	chainItem->add_connections(connection);
}

static void addConnection(
	Class_generic_config& config,	///< [in/out] config object
	const std::string& inputPinID,	///< [in] ID of input pin for connection
	const std::string& outputPinID	///< [in] ID of input pin for connection
	)
{
	auto chain = config.get_chain();
	boost::shared_ptr<Class_generic_config_chain> chainItem	= ConnectedVision::make_shared<Class_generic_config_chain>();
	chain->push_back(chainItem);
	addConnection(chainItem, inputPinID, outputPinID);
	config.set_chain(chain);
}



class TestWrapper_ConnectedVisionModule : public Module_BaseClass
{
public:
	TestWrapper_ConnectedVisionModule(const char moduleDescription[], const char inputPinDescription[], const char outputPinDescription[]) :
		Module_BaseClass(moduleDescription, inputPinDescription, outputPinDescription) {}

	// make function public
	void checkConfig(const Class_generic_config &config)
	{
		Module_BaseClass::checkConfig(config);
	}

	// dummy implementation of abstract functions

	void deleteAllData(const id_t configID) {}
	
	void prepareStores() {}

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

	std::unique_ptr<IWorker> createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config)
	{
		std::unique_ptr<IWorker> nullPtr;
		return nullPtr;
	}

};


static const char moduleDescription[] = "{ \"name\": \"TestWrapper_ConnectedVisionModule\","
											"\"description\": \"\","
											"\"version\": 0.1,"
											"\"moduleID\": \"TestWrapper_ConnectedVisionModule\","
											"\"moduleURI\": \"\","
											"\"APIVersion\": 0.5,"
											"\"author\": \"\","
											"\"params\": {} }";
static const char inputPinDescription[] = "["
											"{ \"name\": \"NormalInput\", \"id\": \"NormalInput\", \"description\": \"\", "
											"\"type\": \"application/json\","
											"\"properties\": {"
											"\"id\": { \"type\": \"string\", \"exttype\": \"id\", \"required\": true, \"unit\": \"md5\" },"
											"\"configID\": { \"type\": \"string\", \"exttype\": \"id\", \"required\": true, \"unit\": \"md5\" },"
											"\"timestamp\": { \"type\": \"integer\", \"exttype\": \"timestamp\", \"required\": true, \"unit\": \"ms\" }"
											"} },"
											"{ \"name\": \"OptionalInput\", \"id\": \"OptionalInput\", \"description\": \"\", "
											"\"type\": \"application/json\","
											"\"minPinCount\" : 0,"
											"\"maxPinCount\" : 1,"
											"\"properties\": {"
											"\"id\": { \"type\": \"string\", \"exttype\": \"id\", \"required\": true, \"unit\": \"md5\" },"
											"\"configID\": { \"type\": \"string\", \"exttype\": \"id\", \"required\": true, \"unit\": \"md5\" },"
											"\"timestamp\": { \"type\": \"integer\", \"exttype\": \"timestamp\", \"required\": true, \"unit\": \"ms\" }"
											"} },"
											"{ \"name\": \"MultipleInput\", \"id\": \"MultipleInput\", \"description\": \"\", "
											"\"type\": \"application/json\","
											"\"minPinCount\" : 0,"
											"\"maxPinCount\" : 3,"
											"\"properties\": {"
											"\"id\": { \"type\": \"string\", \"exttype\": \"id\", \"required\": true, \"unit\": \"md5\" },"
											"\"configID\": { \"type\": \"string\", \"exttype\": \"id\", \"required\": true, \"unit\": \"md5\" },"
											"\"timestamp\": { \"type\": \"integer\", \"exttype\": \"timestamp\", \"required\": true, \"unit\": \"ms\" }"
											"} }"
											"]";
static const char outputPinDescription[] = "[]";

const std::string configStr = "{ \"id\": \"\", \"name\": \"\", \"description\": \"\", \"version\": 1, "
											"\"moduleID\": \"TestWrapper_ConnectedVisionModule\", \"moduleURI\": \"\", "
											"\"params\": {}, "
											"\"chain\": []"
											"}";

TEST_GROUP(inputPin)
{
	void setup()
	{
		// Init stuff
		this->module = std::make_shared<TestWrapper_ConnectedVisionModule>(moduleDescription, inputPinDescription, outputPinDescription);
	}

	void teardown()
	{
		// Uninit stuff
	}

	std::shared_ptr<TestWrapper_ConnectedVisionModule> module;
};

TEST(inputPin, checkConfig_normal_config)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "OptionalInput", "OutputID");
	addConnection(config, "MultipleInput", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_indexed_inputPins_same_subChain)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput.0", "OutputID");
	auto configChain0 = config.get_chain(0);
	addConnection(configChain0, "OptionalInput.0", "OutputID");
	addConnection(configChain0, "MultipleInput.0", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_indexed_inputPins_distributed_over_subChains)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput.0", "OutputID");
	addConnection(config, "MultipleInput.0", "OutputID");
	auto configChain0 = config.get_chain(0);
	addConnection(configChain0, "OptionalInput.0", "OutputID");
	addConnection(configChain0, "MultipleInput.1", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_indexed_inputPins_spezial_syntax)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput.000", "OutputID");
	addConnection(config, "OptionalInput.0", "OutputID");
	addConnection(config, "MultipleInput", "OutputID");
	addConnection(config, "MultipleInput.01", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_detects_missing_inputPin)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_optional_inputPin)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_optional_inputPin_indexed)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput.0", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_inputPin_index_out_of_range)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "OptionalInput.0", "OutputID");
	addConnection(config, "OptionalInput.1", "OutputID");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_inputPin_missing_index)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "MultipleInput.", "OutputID");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_inputPin_negative_index)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "MultipleInput.-1", "OutputID");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_inputPin_non_numerical_index)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "MultipleInput.xyz", "OutputID");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_multiple_inputPins_with_same_ID)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "MultipleInput.0", "OutputID");
	addConnection(config, "MultipleInput.1", "OutputID");
	addConnection(config, "MultipleInput.2", "OutputID");

	//////////////////////////////////////
	// actual test
	module->checkConfig(config);
	CHECK( true ); // there was no exception, so the test passed
}

TEST(inputPin, checkConfig_inputPin_index_sequence_error)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "MultipleInput.0", "OutputID");
	addConnection(config, "MultipleInput.2", "OutputID");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_double_usage_of_same_inputPin)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "NormalInput", "AnotherOutputID");


	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}

TEST(inputPin, checkConfig_double_usage_of_same_inputPin_indexed)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config(configStr);
	addConnection(config, "NormalInput", "OutputID");
	addConnection(config, "MultipleInput.0", "OutputID");
	addConnection(config, "MultipleInput.1", "OutputID");
	addConnection(config, "MultipleInput.1", "AnotherOutputID");
	addConnection(config, "MultipleInput.2", "OutputID");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->checkConfig(config) );
}



}} // namespace scope
