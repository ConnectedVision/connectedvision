/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "hayai/hayai.hpp"

#define BENCHMARK_GROUP(group) struct FIXTURE_##group## : public ::hayai::Fixture
#define BENCHMARK(group, test, iterations)	BENCHMARK_F(FIXTURE_##group, test, 10, iterations)
#define BENCHMARK(group, test)	BENCHMARK_F(FIXTURE_##group, test, 10, 1000)

/*
BENCHMARK_GROUP(SampleGroup)
{
    virtual void SetUp()
    {}
 
    virtual void TearDown()
    {}
};

BENCHMARK(SampleGroup, sampleTest)
{
	// do some action
    for(int64_t i = 0; i < 10000; i++)
	{
		int j = i*i;
	}
}
*/