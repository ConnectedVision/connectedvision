/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "hayai/hayai.hpp"

int main()
{
	hayai::ConsoleOutputter consoleOutputter;
	hayai::Benchmarker::AddOutputter(consoleOutputter);

//	hayai::XMLOutputter xmlOutputter;
//	hayai::Benchmarker::AddOutputter(xmlOutputter);

    hayai::Benchmarker::RunAllTests();

    return 0;
}
