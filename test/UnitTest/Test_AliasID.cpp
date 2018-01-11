/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// original author: Michael Rauter

#include <boost/date_time/posix_time/posix_time.hpp> // used for boost::posix_time::milliseconds(msecs)
#include <boost/thread/thread.hpp>  // used for boost::this_thread::sleep(boost::posix_time::milliseconds(msecs));

#include <vector>
#include <Module/Module_BaseClass.h>
#include <IModuleEnvironment.h>
#include "TestHelper_Module.hpp"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {

namespace Module {

using namespace std;

class TestWrapper_AliasID : public Module_BaseClass // TODO use TestHelper Mockup ???
{
public:
	TestWrapper_AliasID(const char moduleDescription[], const char inputPinDescription[], const char outputPinDescription[]) :
		Module_BaseClass(moduleDescription, inputPinDescription, outputPinDescription) {}

	// make function public
	void checkConfig(const Class_generic_config &config)
	{
		Module_BaseClass::checkConfig(config);
	}

	// dummy implementation of abstract functions

	void deleteAllData(const id_t configID) {}

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

	std::unique_ptr<IWorker> createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config)
	{
		std::unique_ptr<IWorker> nullPtr;
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


static const char moduleDescription[] = "{ \"name\": \"TestWrapper_AliasID\","
											"\"description\": \"\","
											"\"version\": 0.1,"
											"\"moduleID\": \"TestWrapper_AliasID\","
											"\"moduleURI\": \"\","
											"\"APIVersion\": 0.5,"
											"\"author\": \"\","
											"\"params\": {} }";
static const char inputPinDescription[] = "[]";
static const char outputPinDescription[] = "[]";

const std::string configStrPart1 =	"{ \"id\": \"\", \"name\": \"test config\", \"description\": \"\",";
const std::string configStrPart2 =	"\"version\": 1, "
									"\"moduleID\": \"TestWrapper_AliasID\", \"moduleURI\": \"\", "
									"\"params\": { \"foo\": 0 }, "
									"\"chain\": []"
									"}";

const string configStr_no_aliasID_list =						configStrPart1 + configStrPart2;
const string configStr_malformed_empty_struct_aliasID_list =	configStrPart1 + "\"aliasID\": [{}]," + configStrPart2;
const string configStr_empty_aliasID_list =						configStrPart1 + "\"aliasID\": []," + configStrPart2;
const string configStr_aliasID_list_with_empty_ID =				configStrPart1 + "\"aliasID\": [{\"id\": \"\"}]," + configStrPart2;
const string configStr_aliasID_list_with_one_ID =				configStrPart1 + "\"aliasID\": [{\"id\": \"alias1\"}]," + configStrPart2;
const string configStr_aliasID_list_with_two_IDs =				configStrPart1 + "\"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"alias2\"}]," + configStrPart2;
const string configStr_aliasID_list_with_two_IDs_and_emptyID =	configStrPart1 + "\"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"\"}, {\"id\": \"alias2\"}]," + configStrPart2;
const string configStr_aliasID_list_with_one_ID_and_two_emptyID=configStrPart1 + "\"aliasID\": [{\"id\": \"\"}, {\"id\": \"alias1\"}, {\"id\": \"\"}]," + configStrPart2;

const string configStr_aliasID_list_with_invalid_ID_slash=		configStrPart1 + "\"aliasID\": [{\"id\": \"invalid alias ID with slash / in ID string\"}]," + configStrPart2;
const string configStr_aliasID_list_with_invalid_ID_backslash=	configStrPart1 + "\"aliasID\": [{\"id\": \"invalid alias ID with backslash \\ in ID string\"}]," + configStrPart2;
const string configStr_aliasID_list_with_invalid_ID_aliasID_cmd=configStrPart1 + "\"aliasID\": [{\"id\": \"invalid alias ID with aliasID= in ID string\"}]," + configStrPart2;
const string configStr_aliasID_list_with_invalid_ID_AliasID_cmd=configStrPart1 + "\"aliasID\": [{\"id\": \"invalid alias ID with AliasID= in ID string\"}]," + configStrPart2;
const string configStr_aliasID_list_with_invalid_ID_colon=		configStrPart1 + "\"aliasID\": [{\"id\": \"invalid alias ID with invalid postfix after colon. Not allowed in string!\"}]," + configStrPart2;

const string configStr_aliasID_list_with_tricky_but_valid_ID=	configStrPart1 + "\"aliasID\": [{\"id\": \"this is a valid aliasID and should result in an AliasID entry! Tricky ones: aliasID = AliasID = ,;*~?#$%&\"}]," + configStrPart2;

const string configStr_config1_fighting_for_aliasID=			"{ \"id\": \"\", \"name\": \"config1\", \"description\": \"\", \"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"alias2\"}, {\"id\": \"alias3\"}], \"version\": 1, \"moduleID\": \"TestWrapper_AliasID\", \"moduleURI\": \"\", \"params\": { \"foo\": 1 }, \"chain\": []}";
const string configStr_config2_fighting_for_aliasID=			"{ \"id\": \"\", \"name\": \"config2\", \"description\": \"\", \"aliasID\": [{\"id\": \"alias4\"}, {\"id\": \"alias1\"}, {\"id\": \"alias2\"}], \"version\": 1, \"moduleID\": \"TestWrapper_AliasID\", \"moduleURI\": \"\", \"params\": { \"foo\": 2 }, \"chain\": []}";
const string configStr_config3_fighting_for_aliasID=			"{ \"id\": \"\", \"name\": \"config3\", \"description\": \"\", \"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"alias5\"}, {\"id\": \"alias6\"}], \"version\": 1, \"moduleID\": \"TestWrapper_AliasID\", \"moduleURI\": \"\", \"params\": { \"foo\": 3 }, \"chain\": []}";

const string configStr_same_config_claims_aliasID_set1=			configStrPart1 + "\"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"alias2\"}]," + configStrPart2;
const string configStr_same_config_claims_aliasID_set2=			configStrPart1 + "\"aliasID\": [{\"id\": \"alias3\"}, {\"id\": \"alias4\"}]," + configStrPart2;

const string configStr_same_config_renews_aliasID_timestamp_r1=	configStrPart1 + "\"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"alias2\"}]," + configStrPart2;
const string configStr_same_config_renews_aliasID_timestamp_r2=	configStrPart1 + "\"aliasID\": [{\"id\": \"alias3\"}, {\"id\": \"alias1\"}]," + configStrPart2;

TEST_GROUP(aliasID_checkConfigCreation)
{
	void setup()
	{
		// Init stuff
		this->module = new TestWrapper_AliasID(moduleDescription, inputPinDescription, outputPinDescription);

		this->module->initModule(&env);
	}

	void teardown()
	{
		// Uninit stuff
		delete(this->module);
	}

	ModuleEnvironment_Mockup env;
	TestWrapper_AliasID* module;
};

TEST_GROUP(aliasID_checkResolving)
{
	void setup()
	{
		// Init stuff
		this->module = new TestWrapper_AliasID(moduleDescription, inputPinDescription, outputPinDescription);

		this->module->initModule(&env);
	}

	void teardown()
	{
		// Uninit stuff
		delete(this->module);
	}

	ModuleEnvironment_Mockup env;
	TestWrapper_AliasID* module;
};

TEST(aliasID_checkConfigCreation, no_aliasID_list)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_no_aliasID_list);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list		
	LONGS_EQUAL(0, listAliasID->size());
}

TEST(aliasID_checkConfigCreation, malformed_empty_struct_aliasID_list)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_config config;

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, config.parseJson(configStr_malformed_empty_struct_aliasID_list) ); // should throw a std::runtime_error
}

TEST(aliasID_checkConfigCreation, empty_aliasID_list)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_empty_aliasID_list);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(0, listAliasID->size());
}


TEST(aliasID_checkConfigCreation, aliasID_list_with_empty_ID)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_empty_ID);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list	
	LONGS_EQUAL(0, listAliasID->size());
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_one_ID)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(1, listAliasID->size());
	CHECK_EQUAL(string("alias1"), *listAliasID->at(0)->getconst_id());
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_two_IDs)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_two_IDs);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(2, listAliasID->size());
	CHECK_EQUAL(string("alias1"), (*listAliasID->at(0)->getconst_id()));
	CHECK_EQUAL(string("alias2"), (*listAliasID->at(1)->getconst_id()));
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_two_IDs_and_emptyID)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_two_IDs_and_emptyID);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(2, listAliasID->size());
	CHECK_EQUAL(string("alias1"), (*listAliasID->at(0)->getconst_id()));
	CHECK_EQUAL(string("alias2"), (*listAliasID->at(1)->getconst_id()));
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_one_ID_and_two_emptyID)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID_and_two_emptyID);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(1, listAliasID->size());
	CHECK_EQUAL(string("alias1"), *listAliasID->at(0)->getconst_id());
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_invalid_ID_slash)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_invalid_ID_slash);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(0, listAliasID->size());
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_invalid_ID_backslash)
{
	//////////////////////////////////////
	// setup == actual test (setup should throw exception (json parsing fails which is part of the "blackbox" Connected Vision (in terms of unit test)
	CHECK_THROWS( ConnectedVision::runtime_error, this->module->SetupConfigForTest(configStr_aliasID_list_with_invalid_ID_backslash));
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_invalid_ID_aliasID_cmd)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_invalid_ID_aliasID_cmd);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(0, listAliasID->size());
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_invalid_ID_AliasID_cmd)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_invalid_ID_AliasID_cmd);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(0, listAliasID->size());
}

TEST(aliasID_checkConfigCreation, aliasID_list_with_invalid_ID_colon)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_invalid_ID_colon);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(0, listAliasID->size());
}


TEST(aliasID_checkConfigCreation, aliasID_list_with_tricky_but_valid_ID)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(configStr_aliasID_list_with_tricky_but_valid_ID);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config->getconst_aliasID(); // get aliasID list
	LONGS_EQUAL(1, listAliasID->size());
	CHECK_EQUAL(string("this is a valid aliasID and should result in an AliasID entry! Tricky ones: aliasID = AliasID = ,;*~?#$%&"), *listAliasID->at(0)->getconst_id());
}

TEST(aliasID_checkConfigCreation, configs_fighting_for_aliasID)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_config1_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config2 = this->module->SetupConfigForTest(configStr_config2_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config3 = this->module->SetupConfigForTest(configStr_config3_fighting_for_aliasID);

	//////////////////////////////////////
	// actual test

	// tests for "alias1"
	std::vector<id_t> configListForAlias1 = this->module->getConfigIDsByAliasID("alias1");
	LONGS_EQUAL(3, configListForAlias1.size()); // "alias1" was claimed by all three configs - so check this first
	CHECK_EQUAL(config3->getconst_id(), configListForAlias1.at(0)); // config3 should be first
	CHECK_EQUAL(config2->getconst_id(), configListForAlias1.at(1)); // config2 should be second
	CHECK_EQUAL(config1->getconst_id(), configListForAlias1.at(2)); // config1 should be third
	
	// tests for "alias2"
	std::vector<id_t> configListForAlias2 = this->module->getConfigIDsByAliasID("alias2");	
	LONGS_EQUAL(2, configListForAlias2.size()); // "alias2" was claimed by config1 and config2 (2 configs) - so check this first
	CHECK_EQUAL(config2->getconst_id(), configListForAlias2.at(0)); // config2 should be first
	CHECK_EQUAL(config1->getconst_id(), configListForAlias2.at(1)); // config1 should be second

	// tests for "alias3"
	std::vector<id_t> configListForAlias3 = this->module->getConfigIDsByAliasID("alias3");
	LONGS_EQUAL(1, configListForAlias3.size()); // "alias3" was claimed by config2 (1 config) - so check this first
	CHECK_EQUAL(config1->getconst_id(), configListForAlias3.at(0)); // config1 should be the only config

	// tests for "alias4"
	std::vector<id_t> configListForAlias4 = this->module->getConfigIDsByAliasID("alias4");
	LONGS_EQUAL(1, configListForAlias4.size()); // "alias4" was claimed by config2 (1 config) - so check this first
	CHECK_EQUAL(config2->getconst_id(), configListForAlias4.at(0)); // config2 should be the only config

	// tests for "alias5"
	std::vector<id_t> configListForAlias5 = this->module->getConfigIDsByAliasID("alias5");
	LONGS_EQUAL(1, configListForAlias5.size()); // "alias5" was claimed by config3 (1 config) - so check this first
	CHECK_EQUAL(config3->getconst_id(), configListForAlias5.at(0)); // config3 should be the only config

	// tests for "alias6"
	std::vector<id_t> configListForAlias6 = this->module->getConfigIDsByAliasID("alias6");
	LONGS_EQUAL(1, configListForAlias6.size()); // "alias6" was claimed by config3 (1 config) - so check this first
	CHECK_EQUAL(config3->getconst_id(), configListForAlias6.at(0)); // config3 should be the only config
}

TEST(aliasID_checkConfigCreation, same_config_claims_different_aliasID_sets)
{
	//////////////////////////////////////
	// test initialization
	auto config_after_setConfig1 = this->module->SetupConfigForTest(configStr_same_config_claims_aliasID_set1);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config_after_setConfig2 = this->module->SetupConfigForTest(configStr_same_config_claims_aliasID_set2);

	//////////////////////////////////////
	// actual test
	auto listAliasID = config_after_setConfig2->getconst_aliasID(); // get (hopefully) updated aliasID list
	LONGS_EQUAL(4, listAliasID->size());
	CHECK_EQUAL(string("alias3"), *listAliasID->at(0)->getconst_id());
	CHECK_EQUAL(string("alias4"), *listAliasID->at(1)->getconst_id());
	CHECK_EQUAL(string("alias1"), *listAliasID->at(2)->getconst_id());
	CHECK_EQUAL(string("alias2"), *listAliasID->at(3)->getconst_id());
}

TEST(aliasID_checkConfigCreation, same_config_renews_aliasID_timestamp)
{
	//////////////////////////////////////
	// test initialization
	auto config_after_setConfig1 = this->module->SetupConfigForTest(configStr_same_config_renews_aliasID_timestamp_r1);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config_after_setConfig2 = this->module->SetupConfigForTest(configStr_same_config_renews_aliasID_timestamp_r2);


	//////////////////////////////////////
	// actual test
	auto listAliasID = config_after_setConfig2->getconst_aliasID(); // get (hopefully) updated aliasID list
	LONGS_EQUAL(3, listAliasID->size());
	CHECK_EQUAL(string("alias3"), *listAliasID->at(0)->getconst_id());
	CHECK_EQUAL(string("alias1"), *listAliasID->at(1)->getconst_id());
	CHECK_EQUAL(string("alias2"), *listAliasID->at(2)->getconst_id());
	
	// test if timestamp was updated ("alias1" was updated, can be found at index position 1 in listAliasID resp. in config1 index position 0 of aliasID list
	CHECK(listAliasID->at(1)->getconst_timestamp() >= config_after_setConfig1->getconst_aliasID(0)->getconst_timestamp());

	// consistency check (updated list must have same timestamp as config2 corresponding timestamp
	CHECK(listAliasID->at(1)->getconst_timestamp() == config_after_setConfig2->getconst_aliasID(1)->getconst_timestamp());
}

TEST(aliasID_checkResolving, correctConfigID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_two_IDs);
	id_t configID = newConfig->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID(configID);
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, oneExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);
	id_t configID = newConfig->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("alias1");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, twoExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_two_IDs);
	id_t configID = newConfig->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("alias1");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);

	resolvedConfigID = module->resolvePotentialAliasID("alias2");
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, explicitAliasIDcommandWithEmptyArgument)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("aliasID="));
}

TEST(aliasID_checkResolving, explicitAliasIDcommandWithExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);
	id_t configID = newConfig->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("aliasID=alias1");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);

	resolvedConfigID = module->resolvePotentialAliasID("AliasID=alias1");
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, explicitAliasIDcommandWithNonExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("aliasID=nonExistingAliasID"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("AliasID=nonExistingAliasID"));
}

TEST(aliasID_checkResolving, explicitAliasIDandCreationOrderCommandsWithExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);
	id_t configID = newConfig->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("aliasID=alias1.0");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);

	resolvedConfigID = module->resolvePotentialAliasID("AliasID=alias1.0");
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, explicitAliasIDcommandNotStartingAtStringPosition0)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID(" aliasID=alias1"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID(" AliasID=alias1"));
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	id_t configID = newConfig->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("alias1.0");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithNonExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto newConfig = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("nonExistingAliasID.0"));
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithTwoConfigsClaimingExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_config1_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config2 = this->module->SetupConfigForTest(configStr_config2_fighting_for_aliasID);
	id_t configID1 = config1->compute_id();
	id_t configID2 = config2->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("alias1.0");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID2, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);

	resolvedConfigID = module->resolvePotentialAliasID("alias1.1");
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID1, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithNonExistingIndex)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_config1_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config2 = this->module->SetupConfigForTest(configStr_config2_fighting_for_aliasID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("nonExistingAliasID.0"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("nonExistingAliasID.1"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias3.1")); // "alias3" should only exist as .0, so .1 should throw exception
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias4.1")); // "alias4" should only exist as .0, so .1 should throw exception
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithInvalidIndex)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias1.0a"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias1.a0"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias1.1a1"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias1.1e7"));
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias1.2.1"));
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithEmptyIndex)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_aliasID_list_with_one_ID);

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, module->resolvePotentialAliasID("alias1."));
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWithThreeConfigsClaimingExistingAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_config1_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config2 = this->module->SetupConfigForTest(configStr_config2_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	auto config3 = this->module->SetupConfigForTest(configStr_config3_fighting_for_aliasID);
	id_t configID1 = config1->compute_id();
	id_t configID2 = config2->compute_id();
	id_t configID3 = config3->compute_id();

	//////////////////////////////////////
	// actual test
	id_t resolvedConfigID = module->resolvePotentialAliasID("alias1.0");
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID3, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);

	resolvedConfigID = module->resolvePotentialAliasID("alias1.1");
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID2, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);

	resolvedConfigID = module->resolvePotentialAliasID("alias1.2");
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(configID1, resolvedConfigID);
	CHECK_EQUAL(config->getconst_id(), resolvedConfigID);
}

TEST(aliasID_checkResolving, explicitCreationOrderIndexCommandsWhenSwitchingConfigsClaimingSameAliasID)
{
	//////////////////////////////////////
	// test initialization
	auto config1 = this->module->SetupConfigForTest(configStr_config1_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	CHECK(config1); // check if config1 exists
	id_t resolvedConfigID = module->resolvePotentialAliasID("alias1.0");
	CHECK_EQUAL(config1->getconst_id(), resolvedConfigID);
	auto config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(resolvedConfigID, config->getconst_id());
	std::vector<id_t> configListForAlias1 = this->module->getConfigIDsByAliasID("alias1");
	CHECK_EQUAL(resolvedConfigID, configListForAlias1.at(0));

	//////////////////////////////////////
	// actual test

	// set 2nd config which claims same aliasID ("alias1") again
	auto config2 = this->module->SetupConfigForTest(configStr_config2_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	CHECK(config2); // check if config2 exists
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	resolvedConfigID = module->resolvePotentialAliasID("alias1.0");
	CHECK_EQUAL(config2->getconst_id(), resolvedConfigID);
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(resolvedConfigID, config->getconst_id());
	configListForAlias1.clear();
	configListForAlias1 = this->module->getConfigIDsByAliasID("alias1");
	CHECK_EQUAL(resolvedConfigID, configListForAlias1.at(0));

	// now reset 1st config which claims same aliasID ("alias1") again, aliasID creation timestamp update should happen
	config1 = this->module->SetupConfigForTest(configStr_config2_fighting_for_aliasID);
	boost::this_thread::sleep(boost::posix_time::milliseconds(1)); // wait to ensure aliasID creation timestamp is different
	CHECK(config1); // check if config1 exists
	resolvedConfigID = module->resolvePotentialAliasID("alias1.0");
	CHECK_EQUAL(config1->getconst_id(), resolvedConfigID);
	config = module->getConfigStore()->getByID(resolvedConfigID);
	CHECK(config); // check if config exists
	CHECK_EQUAL(resolvedConfigID, config->getconst_id());
	configListForAlias1.clear();
	configListForAlias1 = this->module->getConfigIDsByAliasID("alias1");
	CHECK_EQUAL(resolvedConfigID, configListForAlias1.at(0));
}

} // namespace Module
} // namespace ConnectedVision