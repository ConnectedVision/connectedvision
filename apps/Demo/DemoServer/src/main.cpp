/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "../../Skeleton/src/SkeletonModuleFactory.h"

#include "MyServer.h"

#include <VersionInfo/VersionInfo.h> // version info of Connected Vision
#include "../build/resources/VersionInfo.h" // version info of application

#ifdef _WIN32
	#include "../build/resources/version.h"
#endif

#include <Modules/DirectoryIterator/DirectoryIteratorModuleFactory.h>
#include <Modules/DummyBoundingBoxes/DummyBoundingBoxesModuleFactory.h>
#include <Modules/FileImporter/FileImporterModuleFactory.h>
#include <Modules/FileExport/FileExportModuleFactory.h>
#include <Modules/RTPImporter/RTPImporterModuleFactory.h>
#include <Modules/SyntheticVideo/SyntheticVideoModuleFactory.h>
#include <Modules/ThumbnailGenerator/ThumbnailGeneratorModuleFactory.h>
#include <Modules/VideoImporter/VideoImporterModuleFactory.h>

#include <ModuleDispatcher/ModuleDispatcher.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <iostream>

using namespace std;
using namespace ConnectedVision;
using namespace ConnectedVision::Module;

int main(int argc, char **argv)
{
	try
	{
		string dataPath = "data";
		
		if(argc > 1)
		{
			dataPath = string(argv[1]);
		}
		else
		{			
			// read ini file
			boost::property_tree::ptree pt;
			boost::property_tree::ptree::const_assoc_iterator pt_const_assoc_iter;
			
			try
			{
				boost::property_tree::ini_parser::read_ini("config.ini", pt);
				
				if(boost::optional<string> filename_config = pt.get_optional<string>("General.DataPath"))
				{
					dataPath = filename_config.get();
				}
			}
			catch(...){}
		}

		// remove trailing slashes and backslashes from the data directory path
		dataPath.erase(dataPath.find_last_not_of("\\/") + 1);

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

		cout << "Connected Vision Demo Server Git commit hash: " << GIT_COMMIT_HASH << (GIT_LOCAL_MODIFICATIONS ? " (local modifications)" : "") << endl;
		cout << "Connected Vision Core Git commit hash: " << CONNECTED_VISION_CORE_GIT_COMMIT_HASH << (CONNECTED_VISION_CORE_GIT_LOCAL_MODIFICATIONS ? " (local modifications)" : "") << endl;
		cout << "Test server started on port: " << httpServerParams.listeningPort << endl << "press enter to quit..." << endl;
		cin.ignore();

		server.stop();

		cout << "Test server stopped" << endl;
	}
	catch (exception& e)
	{
		cout << "Exception: " << e.what() << endl;
		getchar();
	}
}
