/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "OutputPin_DirectoryIterator_output_BinaryData.h"

#include <fstream>

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

using namespace std;

OutputPin_DirectoryIterator_output_BinaryData::OutputPin_DirectoryIterator_output_BinaryData(DirectoryIteratorModule* module) : module(module)
{
}



OutputPin_DirectoryIterator_output_BinaryData::~OutputPin_DirectoryIterator_output_BinaryData()
{
}



/**
* get data from module by ID
*
* @param[in] id				ID of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getByID(const id_t id, ConnectedVisionResponse &response)
{
	try
	{
		auto metadata = this->fileMetadataOutputPin->getByID(id);

		if(metadata == nullptr)
		{
			return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getByID() failed to obtain visualization metadata");
		}

		return this->respond(*metadata->getconst_filePath(), response);
	}
	catch(const runtime_error& e)
	{
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), string(e.what()));
	}
}



/**
* get data from module by index
*
* @param[in] index			index of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	try
	{
		auto metadata = this->fileMetadataOutputPin->getByIndex(index);

		if(metadata == nullptr)
		{
			return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getByIndex() failed to obtain visualization metadata");
		}

		return this->respond(*metadata->getconst_filePath(), response);
	}
	catch(const runtime_error& e)
	{
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), string(e.what()));
	}
}



/**
* get data from module by index range
*
* @param[in] start			first index of requested data
* @param[in] end			last index of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getByIndexRange() is not implemented");
}



/**
* get data from module by timestamp
*
* @param[in] timestamp		timestamp of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try
	{
		auto metadata = this->fileMetadataOutputPin->getByTimestamp(timestamp);

		if(metadata.empty() || metadata.back() == nullptr)
		{
			return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getByTimestamp() failed to obtain visualization metadata");
		}

		return this->respond(*metadata.back()->getconst_filePath(), response);
	}
	catch(const runtime_error& e)
	{
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), string(e.what()));
	}
}



/**
* get data from module by timestamp before
*
* @param[in] timestamp		timestamp of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try
	{
		auto metadata = this->fileMetadataOutputPin->getBeforeTimestamp(timestamp);

		if(metadata.empty() || metadata.back() == nullptr)
		{
			return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getBeforeTimestamp(" + intToStr(timestamp) + ") failed to obtain visualization metadata");
		}

		return this->respond(*metadata.back()->getconst_filePath(), response);
	}
	catch(const runtime_error& e)
	{
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), string(e.what()));
	}
}

/**
* get data from module by timestamp after
*
* @param[in] timestamp		timestamp of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	try
	{
		auto metadata = this->fileMetadataOutputPin->getAfterTimestamp(timestamp);

		if(metadata.empty() || metadata.back() == nullptr)
		{
			return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getAfterTimestamp() failed to obtain visualization metadata");
		}

		return this->respond(*metadata.back()->getconst_filePath(), response);
	}
	catch(const runtime_error& e)
	{
		return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), string(e.what()));
	}
}



/**
* get data from module by time span
*
* @param[in] start			first timestamp of requested data
* @param[in] end			last timestamp of requested data
* @param[out] response		requested data or error response
*
* @return status code (analog to HTTP codes)
*/
int OutputPin_DirectoryIterator_output_BinaryData::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{
	return writeError(response, HTTP::HTTP_Status_ERROR, id_t(OutputPin_DirectoryIterator_output_BinaryData::PinID()), "getAllInTimespan() is not implemented");
}

/**
 * init output pin with config
 *
 * @param[in] configStr			config chain
 *
 * @return status code (analog to HTTP codes)
 */
void OutputPin_DirectoryIterator_output_BinaryData::init(const std::string& configStr)
{
	this->config.parseJson(configStr.c_str());
	const id_t configID = this->config.getconst_id();
	this->fileMetadataOutputPin = this->module->storeManagerFileMetadata->getReadStore(configID);
}



int OutputPin_DirectoryIterator_output_BinaryData::respond(const std::string& filePath, ConnectedVisionResponse& response)
{
    ifstream ifs(filePath, ios::binary);

    int length;
    char* buffer;

    // get file size
    ifs.seekg(0, ios::end);
    length = ifs.tellg();
    ifs.seekg(0, ios::beg);

    // allocate memory
    buffer = new char[length];

    // read data as a block:
    ifs.read(buffer, length);
    ifs.close();

    string imageDataStr = string(reinterpret_cast<char*>(buffer), length);
    response.setContent(imageDataStr);
    response.setContentType("application/binary");

    delete [] buffer;

	return HTTP::HTTP_Status_OK;
}

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision