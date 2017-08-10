/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef TestHelper_Threads_code
#define TestHelper_Threads_code

#include <algorithm>

class Thread_Info;

/*
* compare two vectors and compute delta vector
*
* @return difference between vector A and B
*/
template<class T>
static inline std::vector<T> compareVector(const std::vector<T>& vecA, const std::vector<T>& vecB)
{
	std::vector<Thread_Info> delta;

	//search for entries that are in vector A but not in vector B
	for(auto it = vecA.begin(); it != vecA.end(); ++it)
	{
		if ( std::find(vecB.begin(), vecB.end(), *it) == vecB.end() )
			delta.push_back( *it );
	}

	//search for entries that are in vector B but not in vector A
	for(auto it = vecB.begin(); it != vecB.end(); ++it)
	{
		if ( std::find(vecA.begin(), vecA.end(), *it) == vecA.end() )
			delta.push_back( *it );
	}

	return delta;
}

/**
* generic thread info
*/
class Thread_Info
{
public:
	uint64_t	id;
	int32_t		priority;
};
static bool operator==(const Thread_Info& lhs, const Thread_Info& rhs) {
    return lhs.id == rhs.id;
}

/*
*	platform specifiv implementation
*/

// forward declaration
static std::vector<Thread_Info> getRunningThreads();
static Thread_Info getCurrentThread();

#ifdef __unix__
	#include "TestHelper_Threads_Linux.hpp"
#elif defined(_WIN32) || defined(WIN32)
	#include "TestHelper_Threads_Windows.hpp"
#else
	#error "threading test helpers are not implemented for: unknown platform"
#endif


#endif // TestHelper_Threads_code
