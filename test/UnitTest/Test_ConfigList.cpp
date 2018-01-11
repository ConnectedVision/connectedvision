/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// original author: Michael Rauter

#include <boost/date_time/posix_time/posix_time.hpp> // used for boost::posix_time::milliseconds(msecs)
#include <boost/thread/thread.hpp>  // used for boost::this_thread::sleep(boost::posix_time::milliseconds(msecs));

//#include <vector>
#include <Module/Module_BaseClass.h>
#include <IModuleEnvironment.h>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {

class TestMockupModuleEnvironment : public IModuleEnvironment{
public:

	virtual void registerModule( boost::shared_ptr<ConnectedVision::Module::IModule> module ) {};
	virtual boost::shared_ptr<ConnectedVision::Module::IModule> getModule( std::string moduleName ) const { return(NULL); };
	virtual std::string getModuleURL(std::string serverAddress, std::string moduleName ) const { return(""); };
	virtual std::string getDataPath() const { return(""); };

	virtual Class_HostStatus getHostStatus() { Class_HostStatus status; return(status); };

};

namespace Module {

using namespace std;

class TestWrapper_ConfigList : public Module_BaseClass // TODO use TestHelper Mockup ???
{
public:
	TestWrapper_ConfigList(const char moduleDescription[], const char inputPinDescription[], const char outputPinDescription[]) :
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
	};

};


static const char moduleDescription[] = "{ \"name\": \"TestWrapper_ConfigList\","
											"\"description\": \"\","
											"\"version\": 0.1,"
											"\"moduleID\": \"TestWrapper_ConfigList\","
											"\"moduleURI\": \"\","
											"\"APIVersion\": 0.5,"
											"\"author\": \"\","
											"\"params\": {} }";
static const char inputPinDescription[] = "[]";
static const char outputPinDescription[] = "[]";

const std::string config1 =	"{"	
							"	\"id\": \"\", \"name\": \"test config 1\", \"description\": \"\","
							"	\"aliasID\": [{\"id\": \"alias1\"}, {\"id\": \"alias2\"}],"
							"	\"version\": 1, "
							"	\"moduleID\": \"TestWrapper_ConfigList\", \"moduleURI\": \"\", "
							"	\"params\": { \"foo\": 1 }, "
							"	\"chain\": []"
							"}";
const std::string config2 =	"{"	
							"	\"id\": \"\", \"name\": \"test config 2\", \"description\": \"\","
							"	\"aliasID\": [{\"id\": \"alias3\"}, {\"id\": \"alias4\"}],"
							"	\"version\": 1, "
							"	\"moduleID\": \"TestWrapper_ConfigList\", \"moduleURI\": \"\", "
							"	\"params\": { \"foo\": 2 }, "
							"	\"chain\": []"
							"}";

TEST_GROUP(configList)
{
	void setup()
	{
		// Init stuff
		this->module = new TestWrapper_ConfigList(moduleDescription, inputPinDescription, outputPinDescription);

		this->module->initModule(&env);
	}

	void teardown()
	{
		// Uninit stuff
		delete(this->module);
	}

	TestMockupModuleEnvironment env;
	TestWrapper_ConfigList* module;
};

TEST(configList, command_configList_with_no_configs)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	this->module->getConfigList(response);

	//////////////////////////////////////
	// actual test
	CHECK_EQUAL(string("application/json"), response.getContentTypeConst());

	rapidjson::Document document;
	bool errorParsing = document.Parse<0>(response.getContentConst().c_str()).HasParseError();
	CHECK_FALSE(errorParsing);

	CHECK_TRUE(document.IsArray());
	CHECK_EQUAL(0, document.Size());
}

TEST(configList, command_configList_with_one_config)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(config1);

	ConnectedVisionResponse response;
	this->module->getConfigList(response);

	//////////////////////////////////////
	// actual test
	std::string contentType = response.getContentTypeConst();
	std::string content = response.getContentConst();

	CHECK_EQUAL(response.getContentTypeConst(), "application/json");

	// parse data
	rapidjson::Document document;
	bool errorParsing = document.Parse<0>(response.getContentConst().c_str()).HasParseError();
	CHECK_FALSE(errorParsing);

	CHECK_TRUE(document.IsArray());
	CHECK_EQUAL(1, document.Size());
}

TEST(configList, command_configList_with_two_configs)
{
	//////////////////////////////////////
	// test initialization
	auto config_1 = this->module->SetupConfigForTest(config1);
	auto config_2 = this->module->SetupConfigForTest(config2);

	ConnectedVisionResponse response;
	this->module->getConfigList(response);

	//////////////////////////////////////
	// actual test
	std::string contentType = response.getContentTypeConst();
	std::string content = response.getContentConst();

	CHECK_EQUAL(response.getContentTypeConst(), "application/json");

	// parse data
	rapidjson::Document document;
	bool errorParsing = document.Parse<0>(response.getContentConst().c_str()).HasParseError();
	CHECK_FALSE(errorParsing);

	CHECK_TRUE(document.IsArray());
	CHECK_EQUAL(2, document.Size());
}

TEST(configList, command_configListDetailed_with_no_configs)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVisionResponse response;
	this->module->getConfigListDetailed(response);

	//////////////////////////////////////
	// actual test
	CHECK_EQUAL(string("application/json"), response.getContentTypeConst());

	rapidjson::Document document;
	bool errorParsing = document.Parse<0>(response.getContentConst().c_str()).HasParseError();
	CHECK_FALSE(errorParsing);

	CHECK_TRUE(document.IsArray());
	CHECK_EQUAL(0, document.Size());
}

TEST(configList, command_configListDetailed_with_one_config)
{
	//////////////////////////////////////
	// test initialization
	auto config = this->module->SetupConfigForTest(config1);

	ConnectedVisionResponse response;
	this->module->getConfigListDetailed(response);

	//////////////////////////////////////
	// actual test
	CHECK_EQUAL(response.getContentTypeConst(), "application/json");

	// parse data
	rapidjson::Document document;
	bool errorParsing = document.Parse<0>(response.getContentConst().c_str()).HasParseError();
	CHECK_FALSE(errorParsing);

	CHECK_TRUE(document.IsArray());
	CHECK_EQUAL(1, document.Size()); // exactly 1 config found?

	rapidjson::Value& value = document[rapidjson::SizeType(0)]; // process config1
	rapidjson::Value& listAliasID = value["aliasIDs"];
	CHECK_TRUE(listAliasID.IsArray());
	CHECK_EQUAL(2, listAliasID.Size()); // config1 has 2 aliasIDs assigned

	// check for correct aliasIDs
	CHECK_TRUE(listAliasID[rapidjson::SizeType(0)].IsObject());
	CHECK_TRUE(listAliasID[rapidjson::SizeType(0)]["id"].IsString());
	CHECK_EQUAL(string("alias1"), listAliasID[rapidjson::SizeType(0)]["id"].GetString());

	CHECK_TRUE(listAliasID[rapidjson::SizeType(1)].IsObject());
	CHECK_TRUE(listAliasID[rapidjson::SizeType(1)]["id"].IsString());
	CHECK_EQUAL(string("alias2"), listAliasID[rapidjson::SizeType(1)]["id"].GetString());
}

TEST(configList, command_configListDetailed_with_two_configs)
{
	//////////////////////////////////////
	// test initialization
	auto config_1 = this->module->SetupConfigForTest(config1);
	auto config_2 = this->module->SetupConfigForTest(config2);

	ConnectedVisionResponse response;
	this->module->getConfigListDetailed(response);

	//////////////////////////////////////
	// actual test
	CHECK_EQUAL(response.getContentTypeConst(), "application/json");

	// parse data
	rapidjson::Document document;
	bool errorParsing = document.Parse<0>(response.getContentConst().c_str()).HasParseError();
	CHECK_FALSE(errorParsing);

	CHECK_TRUE(document.IsArray());
	CHECK_EQUAL(2, document.Size()); // 2 configs found?

	rapidjson::Value& value = document[rapidjson::SizeType(0)]; // process config1
	rapidjson::Value& listAliasID = value["aliasIDs"];
	CHECK_TRUE(listAliasID.IsArray());
	CHECK_EQUAL(2, listAliasID.Size()); // config1 has 2 aliasIDs assigned

	// check for correct aliasIDs
	CHECK_TRUE(listAliasID[rapidjson::SizeType(0)].IsObject());
	CHECK_TRUE(listAliasID[rapidjson::SizeType(0)]["id"].IsString());
	CHECK_EQUAL(string("alias1"), listAliasID[rapidjson::SizeType(0)]["id"].GetString());

	CHECK_TRUE(listAliasID[rapidjson::SizeType(1)].IsObject());
	CHECK_TRUE(listAliasID[rapidjson::SizeType(1)]["id"].IsString());
	CHECK_EQUAL(string("alias2"), listAliasID[rapidjson::SizeType(1)]["id"].GetString());

	value = document[rapidjson::SizeType(1)]; // process config2
	listAliasID = value["aliasIDs"];
	CHECK_TRUE(listAliasID.IsArray());
	CHECK_EQUAL(2, listAliasID.Size()); // config2 has 2 aliasIDs assigned

	// check for correct aliasIDs
	CHECK_TRUE(listAliasID[rapidjson::SizeType(0)].IsObject());
	CHECK_TRUE(listAliasID[rapidjson::SizeType(0)]["id"].IsString());
	CHECK_EQUAL(string("alias3"), listAliasID[rapidjson::SizeType(0)]["id"].GetString());

	CHECK_TRUE(listAliasID[rapidjson::SizeType(1)].IsObject());
	CHECK_TRUE(listAliasID[rapidjson::SizeType(1)]["id"].IsString());
	CHECK_EQUAL(string("alias4"), listAliasID[rapidjson::SizeType(1)]["id"].GetString());
}

} // namespace Module
} // namespace ConnectedVision