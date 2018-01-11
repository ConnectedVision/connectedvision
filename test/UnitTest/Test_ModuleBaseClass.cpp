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
		std::unique_ptr<Worker_Mockup> worker( new Worker_Mockup( this, controller, 5000, true ) );
		return std::move(worker);
	}

	// test helper
public:
	ConnectedVision::shared_ptr<Class_generic_config> SetupConfigForTest(std::string configStr)
	{
		Class_generic_config configToCreate(configStr); // create temporal config object
		checkConfig(configToCreate);
		id_t configID = configToCreate.compute_id(); // get configID hash

		ConnectedVisionResponse response;
		setConfig("0", configStr, response); // create config in temporary database (e.g. memory database)

		// query temporary database for config (NOTE: this will be different from a config object created from the input configStr
		// since the aliasID list from the config from the store will be a modified version of aliasID list from a config object
		// created from the input configStr (e.g. additional timestamps, empty and invalid aliasIDs erased))
		boost::shared_ptr<const Class_generic_config> constConfig = getConfigStore()->getByID(configID);
		
		// clone config to make it writeable
		auto config = constConfig->copy();
		checkConfig(*config);

		return(config);
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
static const char inputPinDescription[] = "[]";
static const char outputPinDescription[] = "[]";

const std::string configStr = "{ \"id\": \"\", \"name\": \"\", \"description\": \"\", \"version\": 1, "
											"\"moduleID\": \"TestWrapper_ConnectedVisionModule\", \"moduleURI\": \"\", "
											"\"params\": {}, "
											"\"chain\": []"
											"}";



TEST_GROUP(moduleControl)
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

	ModuleEnvironment_Mockup env;
	std::shared_ptr<TestWrapper_ConnectedVisionModule> module;
};


TEST(moduleControl, missing_status_store_returns_error)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	auto statusStore = module->getStatusStore();

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( statusStore );

	auto http_code = module->control(ID_NULL, "", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_ERROR, http_code);
}

TEST(moduleControl, missing_config_store_returns_error)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	auto configStore = module->getConfigStore();

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( configStore );

	auto http_code = module->control(ID_NULL, "", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_ERROR, http_code);
}

TEST(moduleControl, missing_config_returns_error)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);

	//////////////////////////////////////
	// actual test
	auto http_code = module->control(ID_NULL, "", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, http_code);
}

TEST(moduleControl, reset_config)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	auto http_code = module->control(config->getconst_configID(), "reset", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_OK, http_code);
}

TEST(moduleControl, start_config)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	auto http_code = module->control(config->getconst_configID(), "start", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_OK, http_code);
}

TEST(moduleControl, start_unknown_config_returns_error)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	auto http_code = module->control("123", "start", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_ERROR, http_code);
}

TEST(moduleControl, stop_config)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	module->control(config->getconst_configID(), "start", ID_NULL, response);
	auto http_code = module->control(config->getconst_configID(), "stop", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_OK, http_code);
}

TEST(moduleControl, recover_config)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	auto http_code = module->control(config->getconst_configID(), "recover", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_OK, http_code);
}

TEST(moduleControl, resetThis_config)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	auto http_code = module->control(config->getconst_configID(), "resetThis", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_OK, http_code);
}

TEST(moduleControl, stopThis_config)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	module->initModule(&env);
	auto config = module->SetupConfigForTest(configStr);

	//////////////////////////////////////
	// actual test
	module->control(config->getconst_configID(), "start", ID_NULL, response);
	auto http_code = module->control(config->getconst_configID(), "stopThis", ID_NULL, response);

	CHECK_EQUAL(ConnectedVision::HTTP::HTTP_Status_OK, http_code);
}


/* TODO

TEST(moduleInternal, deleteAllData_clears_DB)
{
	//////////////////////////////////////
	// test initialization


	//////////////////////////////////////
	// actual test

	TODO
}
*/

}} // namespace scope
