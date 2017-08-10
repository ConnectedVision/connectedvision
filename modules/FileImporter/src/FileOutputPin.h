/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <sqlite3.h>

#include <IConnectedVisionModule.h>

#include "ILogging.h"

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include "Class_FileImporter_params.h"

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

using namespace ConnectedVision;

/**
 *
 */
class FileOutputPin : public IConnectedVisionOutputPin, public Logging::ILogable
{
public:
	static const pinID_t PinID() { return "FileOutput"; };

public:
	FileOutputPin(IModuleEnvironment *env);
	virtual ~FileOutputPin();

	virtual void init(const std::string& configStr);

	virtual int getByID(const id_t id, ConnectedVisionResponse &response);

	virtual int getByIndex(const int64_t index, ConnectedVisionResponse &response);
	virtual int getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response);

	virtual int getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response);

	virtual boost::shared_ptr<Logging::ILogWriter> log() const;

protected:
	Class_generic_config config;
	Class_FileImporter_params params;
	IModuleEnvironment *env;
};

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision