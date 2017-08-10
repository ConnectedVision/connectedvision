/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <boost/lexical_cast.hpp>

#include "SyntheticVideoDataOutputPin.h"

// template include guard
#ifndef SyntheticVideoDataOutputPin_def
#define SyntheticVideoDataOutputPin_def

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

using namespace std;

SyntheticVideoDataOutputPin::SyntheticVideoDataOutputPin(SyntheticVideoModule* module, unsigned int colorspace, std::string mimetype, fp_Encoder encoder)
{
	syntheticVideoModule = module;
	ColorSpace = colorspace;
	MimeType = mimetype;
	Encoder = encoder;
}



SyntheticVideoDataOutputPin::~SyntheticVideoDataOutputPin(void)
{

}

/**
 * init output pin with config
 *
 * @param[in] configStr			config chain
 *
 * @return status code (analog to HTTP codes)
 */
void SyntheticVideoDataOutputPin::init(const std::string& configStr)
{
	this->config.parseJson( configStr.c_str() );
}


/**
 * get data from module by ID
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] id			ID of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getByID(const id_t id, ConnectedVisionResponse &response)
{
	return getByIndex(boost::lexical_cast<int64_t>(id.c_str()),response);
}

/**
 * get data from module by index
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] index			index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	syntheticVideoModule->priv->prepareVideoHandle( this->config );

	id_t configID = this->config.get_id();
	try 
	{
	    int nRet = syntheticVideoModule->priv->SyntheticVideo_goToFrameNumber(configID, index, ColorSpace);

		std::map<id_t,SyntheticVideo>::iterator it;

		it = syntheticVideoModule->priv->syntheticVideoMap.find(configID);
	
		if ((it != syntheticVideoModule->priv->syntheticVideoMap.end())
			&& (nRet == 0))
		{		
			response.setContentType(MimeType);
			response.setContent(Encoder(configID, (const SyntheticVideo*) &it->second, (const unsigned int) ColorSpace));

			return 200;
		}

		return writeError(response, 404, id_t("SyntheticVideoDataOutputPin"), "not found");
	}
	catch (std::runtime_error& e)
	{
		// internal server error --> HTTP Code: 500
		return writeError(response, 500, id_t("SyntheticVideoDataOutputPin"), string(e.what()) );
	}
}

/**
 * get data from module by index range
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] start			first index of requested data
 * @param[in] end			last index of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{

	int nRet = getByIndex(start,response);
	
	if (nRet == 200)
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
 * @param[in] configID		ID of configuration / job
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	syntheticVideoModule->priv->prepareVideoHandle( this->config );

	id_t configID = this->config.get_id();
	try 
	{
	    int nRet = syntheticVideoModule->priv->SyntheticVideo_goToTimestamp(configID, timestamp, ColorSpace);

		std::map<id_t,SyntheticVideo>::iterator it;

		it = syntheticVideoModule->priv->syntheticVideoMap.find(configID);
	
		if ((it != syntheticVideoModule->priv->syntheticVideoMap.end())
			&& (nRet == 0)
			&& (timestamp == it->second.timestamp))
		{		
			response.setContentType(MimeType);
			std::string content = Encoder(configID, (const SyntheticVideo*) &it->second, (const unsigned int) ColorSpace);
			if (MimeType.compare("application/json") == 0)
			{
				content = "[\n" + content + "\n]\n";
			}
			response.setContent(content);

			return 200;
		}

		return writeError(response, 404, id_t("SyntheticVideoDataOutputPin"), "not found");
	}
	catch (std::runtime_error& e)
	{
		// internal server error --> HTTP Code: 500
		return writeError(response, 500, id_t("SyntheticVideoDataOutputPin"), string(e.what()) );
	}

}

/**
 * get data from module by timestamp before
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	syntheticVideoModule->priv->prepareVideoHandle( this->config );

	id_t configID = this->config.get_id();
	try 
	{
	    int nRet = syntheticVideoModule->priv->SyntheticVideo_goToTimestamp(configID, timestamp, ColorSpace);

		std::map<id_t,SyntheticVideo>::iterator it;

		it = syntheticVideoModule->priv->syntheticVideoMap.find(configID);
	
		if (it != syntheticVideoModule->priv->syntheticVideoMap.end())
		{
			if (!(it->second.timestamp < timestamp))
			{
				nRet = syntheticVideoModule->priv->SyntheticVideo_goToFrameNumber(configID, it->second.framenumber - 1, ColorSpace);
			}

			if ((nRet == 0)
				&& (it->second.timestamp < timestamp))
			{
				response.setContentType(MimeType);
				std::string content = Encoder(configID, (const SyntheticVideo*) &it->second, (const unsigned int) ColorSpace);
				if (MimeType.compare("application/json") == 0)
				{
					content = "[\n" + content + "\n]\n";
				}
				response.setContent(content);

				return 200;
			}
		}

		return writeError(response, 404, id_t("SyntheticVideoDataOutputPin"), "not found");
	}
	catch (std::runtime_error& e)
	{
		// internal server error --> HTTP Code: 500
		return writeError(response, 500, id_t("SyntheticVideoDataOutputPin"), string(e.what()) );
	}

}

/**
 * get data from module by timestamp after
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	// make sure that video importer is init
	syntheticVideoModule->priv->prepareVideoHandle( this->config );

	id_t configID = this->config.get_id();
	try 
	{
	    int nRet = syntheticVideoModule->priv->SyntheticVideo_goToTimestamp(configID, timestamp, ColorSpace);

		std::map<id_t,SyntheticVideo>::iterator it;

		it = syntheticVideoModule->priv->syntheticVideoMap.find(configID);
	
		if (it != syntheticVideoModule->priv->syntheticVideoMap.end())
		{
			if (!(it->second.timestamp > timestamp))
			{
				nRet = syntheticVideoModule->priv->SyntheticVideo_goToFrameNumber(configID, it->second.framenumber + 1, ColorSpace);
			}

			if ((nRet == 0)
				&& (it->second.timestamp > timestamp))
			{
				response.setContentType(MimeType);
				std::string content = Encoder(configID, (const SyntheticVideo*) &it->second, (const unsigned int) ColorSpace);
				if (MimeType.compare("application/json") == 0)
				{
					content = "[\n" + content + "\n]\n";
				}

				if ( content.empty() )
					return writeError(response, 500, id_t("SyntheticVideoDataOutputPin"), "encoder error");

				response.setContent(content);
				return 200;
			}
		}

		return writeError(response, 404, id_t("SyntheticVideoDataOutputPin"), "not found");
	}
	catch (std::runtime_error& e)
	{
		// internal server error --> HTTP Code: 500
		return writeError(response, 500, id_t("SyntheticVideoDataOutputPin"), string(e.what()) );
	}

}

/**
 * get data from module by time span
 *
 * @param[in] configID		ID of configuration / job
 * @param[in] start			first timestamp of requested data
 * @param[in] end			last timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */

int SyntheticVideoDataOutputPin::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{

	return getByTimestamp(start,response);
}

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision

#endif // SyntheticVideoDataOutputPin_def