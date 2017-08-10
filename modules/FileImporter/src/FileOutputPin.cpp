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

#include <helper.h>

#include "FileOutputPin.h"

#include <IModuleEnvironment.h>

#define LOG_SCOPE_CONFIG( configID )		Logging::LoggingScope _log_scope( this->log(), Logging::Debug, this->logName, std::string(__FUNCTION__) + std::string("()@") + ConnectedVision::intToStr(__LINE__), ( configID ) );

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

using namespace std;
using namespace ConnectedVision;


FileOutputPin::FileOutputPin(IModuleEnvironment *env) : env(env)
{
	this->logName = "FileOutputPin";
}



FileOutputPin::~FileOutputPin(void)
{

}

void FileOutputPin::init(const std::string& configStr)
{
	LOG_SCOPE;

	this->config.parseJson( configStr.c_str() );
	this->params.parseJson( this->config.get_params() );

	if ( !this->params.get_filename() )
	{
		throw ConnectedVision::runtime_error( "filname not specified" );
	}
}

/**
 * get data from module by ID
 *
 * @param[in] id			ID of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileOutputPin::getByID(const id_t id, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	try 
	{
		ifstream ifs( this->params.get_filename()->c_str(), ios::binary | ios::in);
		string data = string( (istreambuf_iterator<char>(ifs) ), (istreambuf_iterator<char>() ) );

		response.setContentType( *this->params.get_mimeType() );
		response.setContent(data);
		return 200;

	}
	catch (std::runtime_error& e)
	{
		// internal server error --> HTTP Code: 500
		return writeError(response, 500, id_t("FileOutputPin"), string(e.what()) );
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
int FileOutputPin::getByIndex(const int64_t index, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	return getByID( ID_NULL, response);
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
int FileOutputPin::getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	return getByID( ID_NULL, response);
}

/**
 * get data from module by timestamp
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileOutputPin::getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	return getByID( ID_NULL, response);
}

/**
 * get data from module by timestamp before
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileOutputPin::getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	return getByID( ID_NULL, response);
}

/**
 * get data from module by timestamp after
 *
 * @param[in] timestamp		timestamp of requested data
 * @param[out] response		requested data or error response
 *
 * @return status code (analog to HTTP codes)
 */
int FileOutputPin::getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	return getByID( ID_NULL, response);
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
int FileOutputPin::getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response)
{
	LOG_SCOPE_CONFIG( config.get_id() );

	return getByID( ID_NULL, response);
}

/**
 * get log writer
 *
 * @return log writer
 */
boost::shared_ptr<Logging::ILogWriter> FileOutputPin::log() const
{
	if ( this->env ) 
	{
		return this->env->log(); 
	}
	else 
	{
		boost::shared_ptr<Logging::ILogWriter> log( new Logging::LogWriterNULL() );
		return log;
	}
}

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision