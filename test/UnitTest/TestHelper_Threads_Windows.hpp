/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef TestHelper_Threads_Windows_code
#define TestHelper_Threads_Windows_code

/*
	helper functions to get list of active threads in Windows

	see:
	https://msdn.microsoft.com/en-us/library/windows/desktop/ms686852%28v=vs.85%29.aspx
*/

#include <windows.h>
#include <tlhelp32.h>

static Thread_Info getCurrentThread() 
{ 
	Thread_Info threadInfo;
	threadInfo.id = GetCurrentThreadId();
	threadInfo.priority = 0;

	return threadInfo;
}

static std::vector<Thread_Info> getRunningThreads()
{ 
	DWORD dwOwnerPID = GetCurrentProcessId();
	HANDLE hThreadSnap = INVALID_HANDLE_VALUE; 
	THREADENTRY32 te32; 
	std::vector<Thread_Info> threadList;
 
	// Take a snapshot of all running threads  
	hThreadSnap = CreateToolhelp32Snapshot( TH32CS_SNAPTHREAD, 0 ); 
	if( hThreadSnap == INVALID_HANDLE_VALUE ) 
		return threadList; 
 
	// Fill in the size of the structure before using it. 
	te32.dwSize = sizeof(THREADENTRY32 ); 
 
	// Retrieve information about the first thread,
	// and exit if unsuccessful
	if( !Thread32First( hThreadSnap, &te32 ) ) 
	{
		throw ConnectedVision::runtime_error("cannot get information of the first thread");
	}

	// Now walk the thread list of the system,
	// and display information about each thread
	// associated with the specified process
	do 
	{ 
		if( te32.th32OwnerProcessID == dwOwnerPID )
		{
			Thread_Info threadInfo;
			threadInfo.id = te32.th32ThreadID;
			threadInfo.priority = te32.tpBasePri;
			threadList.push_back(threadInfo);
		}
	} while( Thread32Next(hThreadSnap, &te32 ) );


	//  Don't forget to clean up the snapshot object.
	CloseHandle( hThreadSnap );
	return threadList;
}

#endif // TestHelper_Threads_Windows_code
