/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <helper.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include "DirectoryIteratorModule.h"
#include "DirectoryIteratorWorker.h"
#include "Class_DirectoryIterator_params.h"

#include "Class_DirectoryIterator_output_FileMetadata.h"
#include "OutputPin_DirectoryIterator_output_FileMetadata.h"
#include "OutputPin_DirectoryIterator_output_BinaryData.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

using namespace std;
using namespace ConnectedVision;

void DirectoryIteratorWorker::run()
{
	// get config ID
	id_t configID = this->config->get_id();

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module->getStatusStore();
	auto status = statusStore->getByID(configID)->copy();

	// reset status
	status->resetStableResults();

	// delete previous results
	this->module->deleteResults( this->config );

	// update status timestamps
	status->set_estimatedFinishTime(sysTime() + 1000);
	status->set_systemTimeProcessing(sysTime());
	statusStore->save_copy(status);

	try
	{
		// read config params
		Class_DirectoryIterator_params params;
		params.parseJson(this->config->get_params());

		// get output store
		auto fileMetadataStore = dynamic_cast<DirectoryIteratorModule *>(this->module)->storeManagerFileMetadata->getReadWriteStore(configID);

		// reset stable results
		status->set_stableResultsByPinID(Class_generic_status_stableResults::createFromStore(*fileMetadataStore), OutputPin_DirectoryIterator_output_FileMetadata::PinID());

		// start processing small chunks of data.
		LOG_INFO_CONFIG("start processing", configID);

        // load file types
        auto filetypes = params.get_fileTypes();

        // file iteration
        boost::filesystem::path targetDir(*params.get_rootDirectory());
        boost::filesystem::directory_iterator it(targetDir);

        // precompute number of files
        vector<string> vecPath;
        
		for(boost::filesystem::recursive_directory_iterator end, dir(*params.get_rootDirectory()); dir != end; ++dir )
        {
            for(size_t i = 0; i < filetypes->size(); i++)
            {
                if(is_regular_file(*dir) && boost::filesystem::extension(*dir) == *filetypes->at(i))
                {
                    vecPath.push_back(dir->path().string());
                    break;
                }
            }
        }

        timestamp_t timestampStart = sysTime();

        for(size_t i = 0; i < vecPath.size(); i++)
        {
			auto fileMetadata = fileMetadataStore->create();
			fileMetadata->set_id(boost::lexical_cast<string>(i));
			fileMetadata->set_timestamp(sysTime());
            fileMetadata->set_filePath(vecPath.at(i));

            // save the metadata
            fileMetadataStore->save_move(fileMetadata);

            // update status
            auto stableResults = Class_generic_status_stableResults::createFromStore(*fileMetadataStore);

			status->set_stableResultsByPinID(stableResults, OutputPin_DirectoryIterator_output_FileMetadata::PinID());
            status->set_stableResultsByPinID(stableResults, OutputPin_DirectoryIterator_output_BinaryData::PinID());

            // update estimated process time
            timestamp_t t = sysTime();
            timestamp_t t_diff = t - timestampStart;
            timestamp_t t_oneIter = static_cast<double>(t_diff) / static_cast<double>(i);
            status->set_estimatedFinishTime(timestampStart + (t_oneIter * vecPath.size()));
            status->set_progress(static_cast<float>(i) / static_cast<float>(vecPath.size()));
			status->set_systemTimeProcessing(sysTime());
			statusStore->save_copy(status);
		}

		// update status
		status->set_estimatedFinishTime(sysTime());
		status->set_systemTimeProcessing(sysTime());

		if(this->go)
		{
			// worker has finished
			status->set_progress(1.0);
			status->set_status_finished();
			LOG_INFO_CONFIG("worker finished", configID);
		}
		else
		{
			// worker has been stopped
			status->set_status_stopped();
			LOG_INFO_CONFIG("worker forced to stop", configID);
		}

		statusStore->save_copy(status);
	}
	catch(const exception& e)
	{
		try
		{
			LOG_ERROR_CONFIG(e.what(), configID);

			status->set_status_error();
			status->set_message(e.what());
			status->set_systemTimeProcessing(sysTime());
			status->set_estimatedFinishTime(-1);
			statusStore->save_copy(status);
		}
		catch (...)
		{
				// what can we do now???
		}
	}
	catch (...)
	{
		// 	last resort, before crash
	}
}

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision