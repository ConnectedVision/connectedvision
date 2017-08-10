/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <CppUTest/TestHarness.h>
#include "CppUTestExt/MockSupport.h"

#include <string>

TEST_GROUP(SampleGroup)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
		mock().clear();
	}
};

/**
 * this is a helper fuction to demonstrate an exception catch
 */
void throwFunction()
{
	throw std::runtime_error("throwFunction");
}

TEST(SampleGroup, sampleTest)
{
	// checks any boolean result.
    CHECK( true );

	// checks any boolean result and prints text on failure.
    CHECK_TEXT(true, "failure");

	// checks for equality between entities using ==. 
	// So if you have a class that supports operator==() you can use this macro to compare two instances. 
	// You will also need to add a StringFrom() function like those found in SimpleString. This is for printing the objects when the check failed.
    std::string expected = "test", actual = "test";
	CHECK_EQUAL(expected, actual);

	// checks if expression throws expected_exception (e.g. std::exception). 
	// CHECK_THROWS is only available if CppUTest is built with the Standard C++ Library (default).
	CHECK_THROWS( std::runtime_error, throwFunction() );
	
	// check const char* strings for equality using strcmp().
    STRCMP_EQUAL("test", "test");

	// Compares two numbers.
	int expected_i = 1, actual_i = 1;
    LONGS_EQUAL(expected_i, actual_i);

	// Compares two doubles within some tolerance
	double expected_d = 1.0, actual_d = 1.09;
	DOUBLES_EQUAL(expected_d, actual_d, 0.1);

	// Compares two numbers, eight bits wide.
    BYTES_EQUAL(expected_i, actual_i);

	// Compares two pointers.
	const char *expected_p = (std::string("test")).c_str();
	const char *actual_p = expected_p;
    POINTERS_EQUAL(expected_p, actual_p);

	// always fails
    //FAIL(text);

}

static void productionCode()
{
    mock().actualCall("foo");
}

TEST(SampleGroup, mock_a_function)
{
    mock().expectOneCall("foo");
    productionCode();
    mock().checkExpectations();
}
