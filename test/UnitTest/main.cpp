/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <boost/regex.hpp>
#include <CppUTest/TestHarness.h>
#include <CppUTest/CommandLineTestRunner.h>


int main(int ac, char** av)
{
	MemoryLeakWarningPlugin::turnOffNewDeleteOverloads();

	std::locale::global(std::locale("C"));

	// dummy call of boots regex to avoid false-positive memory leak warning
	boost::smatch matches;
	boost::regex_match(std::string(""), matches, boost::regex("'([\\w\\.]+)'\\s(.*)"));

	for(;;)
		CommandLineTestRunner::RunAllTests(ac, av);
}
