/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include <IConnectedVisionModule.h>

#include "VideoImporterModule.h"
#include "VideoImporterModule_priv.h"

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

class VideoImport;

typedef std::string (*fp_Encoder)(const id_t configID, const VideoImport* videoImport, const unsigned int colorSpace);

/**
 *
 */
class VideoDataOutputPin : public IConnectedVisionOutputPin
{
public:
	VideoDataOutputPin(VideoImporterModule* module, unsigned int colorspace, std::string mimetype, fp_Encoder encoder);
	virtual ~VideoDataOutputPin();

	virtual void init(const std::string& configStr);

	virtual int getByID(const id_t id, ConnectedVisionResponse &response);
	virtual int getByIndex(const int64_t index, ConnectedVisionResponse &response);
	virtual int getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response);
	virtual int getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response);

	VideoImporterModule *videoImportModule;
	unsigned int		ColorSpace;
	std::string			MimeType;
	fp_Encoder			Encoder;

protected:
	Class_generic_config config;
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision