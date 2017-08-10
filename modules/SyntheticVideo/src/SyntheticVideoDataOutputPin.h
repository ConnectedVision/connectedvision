/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include <IConnectedVisionModule.h>

#include "SyntheticVideoModule.h"
#include "SyntheticVideoModule_priv.h"

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

class SyntheticVideo;

typedef std::string (*fp_Encoder)(const id_t configID, const SyntheticVideo* syntheticVideo, const unsigned int colorSpace);

/**
 *
 */
class SyntheticVideoDataOutputPin : public IConnectedVisionOutputPin
{
public:
	SyntheticVideoDataOutputPin(SyntheticVideoModule* module, unsigned int colorspace, std::string mimetype, fp_Encoder encoder);
	virtual ~SyntheticVideoDataOutputPin();

	virtual void init(const std::string& configStr);

	virtual int getByID(const id_t id, ConnectedVisionResponse &response);
	virtual int getByIndex(const int64_t index, ConnectedVisionResponse &response);
	virtual int getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response);
	virtual int getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);
	virtual int getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response);

	SyntheticVideoModule *syntheticVideoModule;
	unsigned int		ColorSpace;
	std::string			MimeType;
	fp_Encoder			Encoder;

protected:
	Class_generic_config config;
};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision