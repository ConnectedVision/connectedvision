/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <ModuleDispatcher/ModuleDispatcher.h>

#include "../../../modules/DirectoryIterator/src/DirectoryIteratorModuleFactory.h"
#include "../../../modules/DummyBoundingBoxes/src/DummyBoundingBoxesModuleFactory.h"
#include "../../../modules/FileExport/src/FileExportModuleFactory.h"
#include "../../../modules/FileImporter/src/FileImporterModuleFactory.h"
#include "../../../modules/SyntheticVideo/src/SyntheticVideoModuleFactory.h"
#include "../../../modules/RTPImporter/src/RTPImporterModuleFactory.h"
#include "../../../modules/ThumbnailGenerator/src/ThumbnailGeneratorModuleFactory.h"
#include "../../../modules/VideoImporter/src/VideoImporterModuleFactory.h"

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
		ModuleDispatcher::HttpServerParams httpServerParams;
		httpServerParams.listeningPort = 2020;
		httpServerParams.numThreads = 2;

		ModuleDispatcher server(httpServerParams);

		std::string dataPath = "data";
		
		if(argc > 1)
		{
			dataPath = std::string(argv[1]);
		}
		else
		{			
			// read ini file
			boost::property_tree::ptree pt;
			boost::property_tree::ptree::const_assoc_iterator pt_const_assoc_iter;
			
			try
			{
				boost::property_tree::ini_parser::read_ini("config.ini", pt);
				
				if(boost::optional<std::string> filename_config = pt.get_optional<std::string>("General.DataPath"))
				{
					dataPath = filename_config.get();
				}
			}
			catch(...){}
		}
		
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

		auto syntheticVideo = SyntheticVideo::SyntheticVideoModuleFactory::createModule();
		server.registerModule(syntheticVideo);

		auto thumbnailGenerator = ThumbnailGenerator::ThumbnailGeneratorModuleFactory::createModule();
		server.registerModule(thumbnailGenerator);

		auto videoImporter = VideoImporter::VideoImporterModuleFactory::createModule();
		server.registerModule(videoImporter);

		server.start();		

		cout << "server started on port: " << httpServerParams.listeningPort << endl << "press enter to quit..." << endl;
		cin.ignore();

		server.stop();

		cout << "server stopped" << endl;
	}
	catch (exception& e)
	{
		cout << "exception: " << e.what() << endl;
		getchar();
	}
}
