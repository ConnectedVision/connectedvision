/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <VersionInfo/VersionInfo.h> // version info of Connected Vision
#include "../build/resources/VersionInfo.h" // version info of application
#include "../build/resources/version.h"

#include "../../Skeleton/src/SkeletonModuleFactory.h"

#include <Modules/DirectoryIterator/DirectoryIteratorModuleFactory.h>
#include <Modules/DummyBoundingBoxes/DummyBoundingBoxesModuleFactory.h>
#include <Modules/FileImporter/FileImporterModuleFactory.h>
#include <Modules/FileExport/FileExportModuleFactory.h>
#include <Modules/RTPImporter/RTPImporterModuleFactory.h>
#include <Modules/SyntheticVideo/SyntheticVideoModuleFactory.h>
#include <Modules/ThumbnailGenerator/ThumbnailGeneratorModuleFactory.h>
#include <Modules/VideoImporter/VideoImporterModuleFactory.h>

#include <ModuleDispatcher/ModuleDispatcher.h>

#ifdef CRASHRPT_ENABLED
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "CrashRpt.h"
#endif

#include <Windows.h>
#include <tchar.h>
#include <iostream>

#define DEFAULT_DATAPATH "C:\\ConnectedVisionDemoService\\data"

SERVICE_STATUS        g_ServiceStatus = {0};
SERVICE_STATUS_HANDLE g_StatusHandle = NULL;
HANDLE                g_ServiceStopEvent = INVALID_HANDLE_VALUE;

VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv);
VOID WINAPI ServiceCtrlHandler (DWORD);
DWORD WINAPI ServiceWorkerThread (LPVOID lpParam);


using namespace std;
using namespace ConnectedVision;
using namespace ConnectedVision::Module;

#define SERVICE_NAME  _T("My Sample Service")

int _tmain (int argc, TCHAR *argv[])
{
    OutputDebugString(_T("My Sample Service: Main: Entry"));

    SERVICE_TABLE_ENTRY ServiceTable[] = 
    {
        {SERVICE_NAME, (LPSERVICE_MAIN_FUNCTION) ServiceMain},
        {NULL, NULL}
    };

    if (StartServiceCtrlDispatcher (ServiceTable) == FALSE)
    {
       OutputDebugString(_T("My Sample Service: Main: StartServiceCtrlDispatcher returned error"));
       return GetLastError ();
    }

    OutputDebugString(_T("My Sample Service: Main: Exit"));
    return 0;
}


VOID WINAPI ServiceMain (DWORD argc, LPTSTR *argv)
{
    DWORD Status = E_FAIL;

    OutputDebugString(_T("My Sample Service: ServiceMain: Entry"));

    g_StatusHandle = RegisterServiceCtrlHandler (SERVICE_NAME, ServiceCtrlHandler);

    if (g_StatusHandle == NULL) 
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: RegisterServiceCtrlHandler returned error"));
        goto EXIT;
    }

    // Tell the service controller we are starting
    ZeroMemory (&g_ServiceStatus, sizeof (g_ServiceStatus));
    g_ServiceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwServiceSpecificExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE) 
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

    /* 
     * Perform tasks neccesary to start the service here
     */
    OutputDebugString(_T("My Sample Service: ServiceMain: Performing Service Start Operations"));

    // Create stop event to wait on later.
    g_ServiceStopEvent = CreateEvent (NULL, TRUE, FALSE, NULL);
    if (g_ServiceStopEvent == NULL) 
    {
        OutputDebugString(_T("My Sample Service: ServiceMain: CreateEvent(g_ServiceStopEvent) returned error"));

        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
        g_ServiceStatus.dwWin32ExitCode = GetLastError();
        g_ServiceStatus.dwCheckPoint = 1;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
	    {
		    OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
	    }
        goto EXIT; 
    }    

    // Tell the service controller we are started
    g_ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
    g_ServiceStatus.dwCurrentState = SERVICE_RUNNING;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 0;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
	    OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }

    // Start the thread that will perform the main task of the service
    HANDLE hThread = CreateThread (NULL, 0, ServiceWorkerThread, NULL, 0, NULL);

    OutputDebugString(_T("My Sample Service: ServiceMain: Waiting for Worker Thread to complete"));

    // Wait until our worker thread exits effectively signaling that the service needs to stop
    WaitForSingleObject (hThread, INFINITE);
    
    OutputDebugString(_T("My Sample Service: ServiceMain: Worker Thread Stop Event signaled"));
    
    
    /* 
     * Perform any cleanup tasks
     */
    OutputDebugString(_T("My Sample Service: ServiceMain: Performing Cleanup Operations"));

    CloseHandle (g_ServiceStopEvent);

    g_ServiceStatus.dwControlsAccepted = 0;
    g_ServiceStatus.dwCurrentState = SERVICE_STOPPED;
    g_ServiceStatus.dwWin32ExitCode = 0;
    g_ServiceStatus.dwCheckPoint = 3;

    if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
    {
	    OutputDebugString(_T("My Sample Service: ServiceMain: SetServiceStatus returned error"));
    }
    
    EXIT:
    OutputDebugString(_T("My Sample Service: ServiceMain: Exit"));

    return;
}


VOID WINAPI ServiceCtrlHandler (DWORD CtrlCode)
{
    OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: Entry"));

    switch (CtrlCode) 
	{
     case SERVICE_CONTROL_STOP :

        OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: SERVICE_CONTROL_STOP Request"));

        if (g_ServiceStatus.dwCurrentState != SERVICE_RUNNING)
           break;

        /* 
         * Perform tasks neccesary to stop the service here 
         */
        
        g_ServiceStatus.dwControlsAccepted = 0;
        g_ServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
        g_ServiceStatus.dwWin32ExitCode = 0;
        g_ServiceStatus.dwCheckPoint = 4;

        if (SetServiceStatus (g_StatusHandle, &g_ServiceStatus) == FALSE)
		{
			OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: SetServiceStatus returned error"));
		}

        // This will signal the worker thread to start shutting down
        SetEvent (g_ServiceStopEvent);

        break;

     default:
         break;
    }

    OutputDebugString(_T("My Sample Service: ServiceCtrlHandler: Exit"));
}


DWORD WINAPI ServiceWorkerThread (LPVOID lpParam)
{
    OutputDebugString(_T("My Sample Service: ServiceWorkerThread: Entry"));

    //Sleep(10000);// helps with debugging
	
	try
	{
		string dataPath = DEFAULT_DATAPATH;

		// remove trailing slashes and backslashes from the data directory path
		dataPath.erase(dataPath.find_last_not_of("\\/") + 1);
		
		#ifdef CRASHRPT_ENABLED
			ConnectedVision::ErrorHandling::Exception_BaseClass_CallStack::setCallStackEnabled(false);

			// create the parent directory for the crash reports subdirectory manually because CrashRpt would fail if it does not exist
			if(!boost::filesystem::exists(dataPath))
			{
				boost::filesystem::create_directories(dataPath);

				if(!boost::filesystem::exists(dataPath))
				{
					boost::filesystem::path dataPathAbs(dataPath);

					if(dataPathAbs.is_relative())
					{
						dataPathAbs = boost::filesystem::absolute(dataPathAbs);
					}

					throw std::runtime_error("failed to create the data directory: " + dataPathAbs.string());
				}
			}

			CR_INSTALL_INFO crashRptInfo = CR_INSTALL_INFO();
			crashRptInfo.cb = sizeof(CR_INSTALL_INFO);
			string crashRptReportDir = dataPath + "/CrashReports";
			wstring crashRptReportDirW = wstring(crashRptReportDir.begin(), crashRptReportDir.end());
			crashRptInfo.pszErrorReportSaveDir = crashRptReportDirW.c_str();
			crashRptInfo.uMiniDumpType = MINIDUMP_TYPE(MiniDumpIgnoreInaccessibleMemory | MiniDumpWithFullAuxiliaryState | MiniDumpWithFullMemory | MiniDumpWithFullMemoryInfo | MiniDumpWithHandleData | MiniDumpWithProcessThreadData | MiniDumpWithThreadInfo | MiniDumpWithTokenInformation | MiniDumpWithUnloadedModules);
			crashRptInfo.dwFlags |= CR_INST_DONT_SEND_REPORT;
			crashRptInfo.dwFlags |= CR_INST_STORE_ZIP_ARCHIVES;
			#ifndef _DEBUG
				crashRptInfo.dwFlags |= CR_INST_AUTO_THREAD_HANDLERS;
			#endif
			// use the product name as the crash report parent directory name, allow only a limited set of characters and remove all other characters
			string appName = boost::regex_replace(string(VER_PRODUCTNAME_STR), boost::regex("[^\\w\\.]"), "");
			wstring appNameW = wstring(appName.begin(), appName.end());
			crashRptInfo.pszAppName = appNameW.c_str();
			string appVersion = VER_FILE_VERSION_STR;
			wstring appVersionW = wstring(appVersion.begin(), appVersion.end());
			crashRptInfo.pszAppVersion = appVersionW.c_str();

			CrAutoInstallHelper crashRpt(&crashRptInfo);
	
			if(crashRpt.m_nInstallStatus != 0)
			{
				wstring szErrorMsg;
				szErrorMsg.resize(1024);
				LPWSTR x = const_cast<LPWSTR>(szErrorMsg.c_str());
				crGetLastErrorMsg(x, static_cast<UINT>(szErrorMsg.size()));
				wcout << "failed to initialize CrashRpt (" << szErrorMsg << ")" << endl;
			}
		#endif
		
		ModuleDispatcher::HttpServerParams httpServerParams;
		httpServerParams.listeningPort = 2020;
		httpServerParams.numThreads = 20;

		/*
		ModuleDispatcher::HttpsServerParams httpsServerParams;
		httpsServerParams.listeningPort = 2021;
		httpsServerParams.numThreads = 20;
		httpsServerParams.privateKeyFile = "../../../data/zertifikat-key.pem"; // create certificates, ca files: see https://thomas-leister.de/internet/eine-eigene-openssl-ca-erstellen-und-zertifikate-ausstellen/
		httpsServerParams.certificateFile = "../../../data/zertifikat-pub.pem";
		httpsServerParams.caLocation = "../../../data/ca-root.pem";			
		httpsServerParams.password = "secret";

		HTTPXClient::HttpsClientParams httpsClientParams;
		httpsClientParams.caLocation = "../../../data/ca-root.pem";
		httpsClientParams.caPassword = "secret";
		HTTPXClient::setHttpsClientParams(httpsClientParams);
		*/

		ModuleDispatcher server(httpServerParams);	// standard module server
//		ModuleDispatcher server(httpServerParams, httpsServerParams); // http and https server standard module server
//		MyServer server(httpServerParams);			// customized server with overwritten default page

		server.setDataPath(dataPath);

		auto directoryIterator = DirectoryIterator::DirectoryIteratorModuleFactory::createModule();
		server.registerModule(directoryIterator);

		auto dummyBoundingBoxes = DummyBoundingBoxes::DummyBoundingBoxesModuleFactory::createModule();
		server.registerModule(dummyBoundingBoxes);

		auto fileExport = FileExport::FileExportModuleFactory::createModule();
		server.registerModule(fileExport);

		auto fileImporter = FileImporter::FileImporterModuleFactory::createModule();
		server.registerModule(fileImporter);

		auto rtpImporter = RTPImporter::RTPImporterModuleFactory::createModule();
		server.registerModule(rtpImporter);

		auto skeleton = Skeleton::SkeletonModuleFactory::createModule();
		server.registerModule(skeleton);

		auto syntheticVideo = SyntheticVideo::SyntheticVideoModuleFactory::createModule();
		server.registerModule(syntheticVideo);

		auto thumbnailGenerator = ThumbnailGenerator::ThumbnailGeneratorModuleFactory::createModule();
		server.registerModule(thumbnailGenerator);

		auto videoImporter = VideoImporter::VideoImporterModuleFactory::createModule();
		server.registerModule(videoImporter);

		server.start();

		cout << "Connected Vision Demo Server Windows Service started on port: " << httpServerParams.listeningPort << endl << "press enter to quit..." << endl;
	
	
		//  Periodically check if the service has been requested to stop
		while (WaitForSingleObject(g_ServiceStopEvent, 0) != WAIT_OBJECT_0)
		{        
			/* 
			 * Perform main service function here
			 */

			//  Simulate some work by sleeping
			Sleep(3000);

		}

		server.stop();

		OutputDebugString(_T("My Sample Service: ServiceWorkerThread: Exit"));

		return ERROR_SUCCESS;
	
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
		getchar();
		
		return ERROR_NOT_READY;
	}
}