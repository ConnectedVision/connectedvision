/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "rapidjson/document.h"

#include <CppUTest/TestHarness.h>

using namespace rapidjson;

TEST_GROUP(RapidJSON)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}
};



TEST(RapidJSON, deepCopy)
{
	Document document;
	document.SetObject();
	document.AddMember("name", "foo", document.GetAllocator());

	Value v2;
	v2.SetObject();
	v2.CopyFrom(document, document.GetAllocator());

}
