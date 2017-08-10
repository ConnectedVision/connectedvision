/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <map>
// compile with: /EHsc 
#include <unordered_map>

#include "hayai/hayai.hpp"

#define BENCHMARK_GROUP(group) struct group : public ::hayai::Fixture
#define BENCHMARK(group, test, iterations)	BENCHMARK_F(group, test, 10, iterations)
#define BENCHMARK(group, test)	BENCHMARK_F(group, test, 10, 100)

static const int64_t size = 1000;
typedef std::string key_t;
typedef int64_t value_t;


BENCHMARK_GROUP(Cpp11_Map_linear)
{
    virtual void SetUp()
    {
		// build
		for (int64_t i=0; i < size; ++i)
		{
			char str[10]; itoa(i,str,10);
			// keys[i] = i;
			keys[i] = str;
			values[i] = i;
		}

		// fill maps
		for (int64_t i=0; i < size; ++i)
		{
			stdMap.insert ( std::make_pair(keys[i],values[i]) );
			hashMap.insert ( std::make_pair(keys[i],values[i]) );
		}

	}
 
    virtual void TearDown()
    {}

	std::map<key_t,int64_t> stdMap;
	std::unordered_map <key_t,int64_t> hashMap;
	key_t keys[size];
	value_t values[size];
};

BENCHMARK(Cpp11_Map_linear, map_lookup)
{
    for(int64_t i = 0; i < size; i++)
	{
		auto data = stdMap.find( keys[i] );
	}
}

BENCHMARK(Cpp11_Map_linear, unordered_map_lookup)
{
    for(int64_t i = 0; i < size; i++)
	{
		auto data = hashMap.find( keys[i] );
	}
}


BENCHMARK_GROUP(Cpp11_Map_mixed)
{
    virtual void SetUp()
    {
		// build
		for (int64_t i=0; i < size; ++i)
		{
			char str[10]; itoa(i,str,10);
			// keys[i] = i;
			keys[i] = str;

			values[i] = i;
		}

		// mix
		for (int64_t i=0; i < size; ++i)
		{
			int64_t j = (i*i + i) % size;
			if ( i != j )
			{
				std::swap( keys[i], keys[j] );
				std::swap( values[i], values[j] );
			}
		}

		// fill maps
		for (int64_t i=0; i < size; ++i)
		{
			stdMap.insert ( std::make_pair(keys[i],values[i]) );
			hashMap.insert ( std::make_pair(keys[i],values[i]) );
		}

	}
 
    virtual void TearDown()
    {}

	std::map<key_t,int64_t> stdMap;
	std::unordered_map <key_t,int64_t> hashMap;
	key_t keys[size];
	value_t values[size];
};

BENCHMARK(Cpp11_Map_mixed, map_lookup)
{
    for(int64_t i = 0; i < size; i++)
	{
		auto data = stdMap.find( keys[i] );
	}
}

BENCHMARK(Cpp11_Map_mixed, unordered_map_lookup)
{
    for(int64_t i = 0; i < size; i++)
	{
		auto data = hashMap.find( keys[i] );
	}
}

