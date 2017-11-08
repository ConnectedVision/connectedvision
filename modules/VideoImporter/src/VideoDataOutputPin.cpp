/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef VideoDataOutputPin_def
#define VideoDataOutputPin_def

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/lexical_cast.hpp>

#include "VideoDataOutputPin.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

using namespace std;



VideoDataOutputPin::VideoDataOutputPin(VideoImporterModule* module, unsigned int colorspace, std::string mimetype, fp_Encoder encoder)
{
	this->videoImportModule = module;
	this->ColorSpace = colorspace;
	this->MimeType = mimetype;
	this->Encoder = encoder;
	this->config.clear();
}



VideoDataOutputPin::~VideoDataOutputPin(void)
{

}

/**
 * init output pin with config
 *
 * @param[in] configStr			config chain
 *
 * @return status code (analog to HTTP codes)
 */
void VideoDataOutputPin::init(const std::string& configStr)
{
	this->config.parseJson( configStr.c_str() );
}


/**
 * get data from module by ID
 *
 * @param[in] id			ID of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int VideoDataOutputPin::getByID(const id_t id, ConnectedVisionResponse &response)
{
	return getByIndex(boost::lexical_cast<int64_t>(id.c_str()),response);
}

/**
 * get data from module by index
 *
 * @param[in] index			index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int VideoDataOutputPin::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	videoImportModule->priv->VideoImport_init( this->config );

	id_t configID = this->config.get_id();
	try 
	{
		boost::shared_ptr<ConnectedVision::Module::VideoImporter::VideoImport> pVideoImportInstance;
		{   // first lock the videoImportMap mutex (as scoped section - so that mutex is unlocked as soon as possible)
			boost::mutex::scoped_lock(videoImportModule->priv->mutexVideoImportMap);
			auto it = videoImportModule->priv->videoImportMap.find(configID);
			if (it != videoImportModule->priv->videoImportMap.end())
			{
				// then get shared pointer of VideoImport instance
				pVideoImportInstance = it->second;
			}
			else
			{
				return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
			}
		}

		// now lock the instance mutex
		boost::mutex::scoped_lock lock(pVideoImportInstance->m_mutex);

	    videoImportModule->priv->VideoImport_goToFrameNumber(configID, index, ColorSpace);
		
		response.setContentType(MimeType);
		response.setContent(Encoder(configID, &(*pVideoImportInstance), (const unsigned int) ColorSpace));

		return ConnectedVision::HTTP::HTTP_Status_OK;		
	}
	catch (runtime_error& e)
	{
		return writeError(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("VideoDataOutputPin"), string(e.what()) );
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

int VideoDataOutputPin::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	int nRet = getByIndex(start,response);
	
	if (nRet == ConnectedVision::HTTP::HTTP_Status_OK)
	{		
		std::string content = response.getContent();
		if (response.getContentType().compare("application/json") == 0)
		{
			content = "[\n" + content + "\n]\n";
		}
		response.setContent(content);
	}
	
	return nRet;
}

/**
 * get data from module by timestamp
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int VideoDataOutputPin::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	videoImportModule->priv->VideoImport_init( this->config );

	id_t configID = this->config.get_id();
	
	try
	{
		boost::shared_ptr<ConnectedVision::Module::VideoImporter::VideoImport> pVideoImportInstance;
		{   // first lock the videoImportMap mutex (as scoped section - so that mutex is unlocked as soon as possible)
			boost::mutex::scoped_lock(videoImportModule->priv->mutexVideoImportMap);
			auto it = videoImportModule->priv->videoImportMap.find(configID);
			if (it != videoImportModule->priv->videoImportMap.end())
			{
				// then get shared pointer of VideoImport instance
				pVideoImportInstance = it->second;
			}
			else
			{
				return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
			}
		}

		// now lock the instance mutex
		boost::mutex::scoped_lock lock(pVideoImportInstance->m_mutex);

		videoImportModule->priv->VideoImport_goToTimestamp(configID, timestamp, ColorSpace);
	
		if (timestamp == pVideoImportInstance->m_Frame.timestamp)
		{		
			response.setContentType(MimeType);
			std::string content = Encoder(configID, &(*pVideoImportInstance), (const unsigned int) ColorSpace);
			if (MimeType.compare("application/json") == 0)
			{
				content = "[\n" + content + "\n]\n";
			}
			response.setContent(content);

			return ConnectedVision::HTTP::HTTP_Status_OK;
		}
		else
		{
			return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
		}
	}
	catch (runtime_error& e)
	{
		return writeError(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("VideoDataOutputPin"), string(e.what()) );
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

int VideoDataOutputPin::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	videoImportModule->priv->VideoImport_init( this->config );
	
	id_t configID = this->config.get_id();
	
	try
	{
		boost::shared_ptr<ConnectedVision::Module::VideoImporter::VideoImport> pVideoImportInstance;
		{   // first lock the videoImportMap mutex (as scoped section - so that mutex is unlocked as soon as possible)
			boost::mutex::scoped_lock(videoImportModule->priv->mutexVideoImportMap);
			auto it = videoImportModule->priv->videoImportMap.find(configID);
			if (it != videoImportModule->priv->videoImportMap.end())
			{
				// then get shared pointer of VideoImport instance
				pVideoImportInstance = it->second;
			}
			else
			{
				return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
			}
		}
		
		// now lock the instance mutex
		boost::mutex::scoped_lock lock(pVideoImportInstance->m_mutex);

		videoImportModule->priv->VideoImport_goToTimestamp(configID, timestamp-1, ColorSpace);
		
		if (!(pVideoImportInstance->m_Frame.timestamp < timestamp))
		{
			videoImportModule->priv->VideoImport_goToFrameNumber(configID, pVideoImportInstance->m_Frame.framenumber - 1, ColorSpace);
		}
		
		if (pVideoImportInstance->m_Frame.timestamp < timestamp)
		{
			response.setContentType(MimeType);
			std::string content = Encoder(configID, &(*pVideoImportInstance), (const unsigned int) ColorSpace);			
			if (MimeType.compare("application/json") == 0)
			{
				content = "[\n" + content + "\n]\n";
			}
			response.setContent(content);

			return ConnectedVision::HTTP::HTTP_Status_OK;
		}
		else
		{
			return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
		}
	}
	catch (runtime_error& e)
	{
		return writeError(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("VideoDataOutputPin"), string(e.what()) );
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

int VideoDataOutputPin::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	videoImportModule->priv->VideoImport_init( this->config );

	id_t configID = this->config.get_id();
	
	try
	{
		boost::shared_ptr<ConnectedVision::Module::VideoImporter::VideoImport> pVideoImportInstance;
		{   // first lock the videoImportMap mutex (as scoped section - so that mutex is unlocked as soon as possible)
			boost::mutex::scoped_lock(videoImportModule->priv->mutexVideoImportMap);
			auto it = videoImportModule->priv->videoImportMap.find(configID);
			if (it != videoImportModule->priv->videoImportMap.end())
			{
				// then get shared pointer of VideoImport instance
				pVideoImportInstance = it->second;
			}
			else
			{
				return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
			}
		}

		// now lock the instance mutex
		boost::mutex::scoped_lock lock(pVideoImportInstance->m_mutex);

		videoImportModule->priv->VideoImport_goToTimestamp(configID, timestamp+1, ColorSpace);
		
		if (!(pVideoImportInstance->m_Frame.timestamp > timestamp))
		{
			videoImportModule->priv->VideoImport_goToFrameNumber(configID, pVideoImportInstance->m_Frame.framenumber + 1, ColorSpace);
		}
		
		if (pVideoImportInstance->m_Frame.timestamp > timestamp)
		{
			response.setContentType(MimeType);
			std::string content = Encoder(configID, &(*pVideoImportInstance), (const unsigned int) ColorSpace);
			if (MimeType.compare("application/json") == 0)
			{
				content = "[\n" + content + "\n]\n";
			}
			response.setContent(content);
				
			return ConnectedVision::HTTP::HTTP_Status_OK;
		}
		else
		{
			return writeError(response, ConnectedVision::HTTP::HTTP_Status_NOT_FOUND, id_t("VideoDataOutputPin"), "not found");
		}
	}
	catch (runtime_error& e)
	{
		return writeError(response, ConnectedVision::HTTP::HTTP_Status_ERROR, id_t("VideoDataOutputPin"), string(e.what()) );
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
int VideoDataOutputPin::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{

	return getByTimestamp(start,response);
}

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision

#endif // VideoDataOutputPin_def
