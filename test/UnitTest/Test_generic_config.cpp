/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Store_SQLite_generic_config.h>

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {
namespace DataHandling {

TEST_GROUP(generic_config)
{
	void setup()
	{
		// Init stuff
		db.init(":memory:", SQLITE_OPEN_CREATE);
	}

	void teardown()
	{
		// Uninit stuff
	}

	DBConnection db;
};

TEST(generic_config, Store_SQLite_generic_config)
{
	obsolete::Store_SQLite_generic_config store(db);
}

}} // namespace scope
