/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef TestHelper_Threads_Linux_code
#define TestHelper_Threads_Linux_code

/*
	helper functions to get list of active threads in Linux
*/

#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


static Thread_Info getCurrentThread() 
{ 
	Thread_Info threadInfo;
	boost::thread::id tid = boost::this_thread::get_id();
	uint64_t id;
	std::stringstream ss;
	ss << std::hex << boost::lexical_cast<std::string>(tid);
	ss >> id;

	threadInfo.id = id;
	threadInfo.priority = 0;

	return threadInfo;
}

static std::vector<Thread_Info> getRunningThreads()
{ 
	pid_t pid = getpid();

	std::vector<Thread_Info> threadList;

	std::string directory = std::string("/proc/") + boost::lexical_cast<std::string>(pid) + std::string("/task");
    if( boost::filesystem::exists( directory ) )
    {
    	boost::filesystem::directory_iterator end;

       for( boost::filesystem::directory_iterator iter(directory) ; iter != end; ++iter ) {
         if ( boost::filesystem::is_directory( *iter ) )
         {
            std::string tidPath = iter->path().string();

 			Thread_Info threadInfo;

 			std::vector<std::string> tokens;
 			boost::split(tokens, tidPath, boost::is_any_of("/"));

 			threadInfo.id = boost::lexical_cast<uint64_t>(tokens.back());
 			threadInfo.priority = 0;
 			threadList.push_back(threadInfo);
         }
       }
    }

	return threadList;
}

#endif // TestHelper_Threads_Linux_code
