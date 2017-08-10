/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef OutputPin_DirectoryIterator_output_BinaryData_def
#define OutputPin_DirectoryIterator_output_BinaryData_def

#include "DirectoryIteratorModule.h"
#include "Class_DirectoryIterator_output_FileMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

class OutputPin_DirectoryIterator_output_BinaryData : public IConnectedVisionOutputPin
{
public:
	OutputPin_DirectoryIterator_output_BinaryData(DirectoryIteratorModule* module);

	virtual ~OutputPin_DirectoryIterator_output_BinaryData();
	
	static const pinID_t PinID() { return "BinaryData"; };

	static const bool hasPinID(pinID_t id) { return id == PinID(); };

	virtual void init(const std::string& configStr);

	virtual int getByID(const id_t id, ConnectedVisionResponse &response);

	virtual int getByIndex(const int64_t index, ConnectedVisionResponse &response);

	virtual int getByIndexRange(const int64_t start, const int64_t end, ConnectedVisionResponse &response);

	virtual int getByTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);

	virtual int getBeforeTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);

	virtual int getAfterTimestamp(const timestamp_t timestamp, ConnectedVisionResponse &response);

	virtual int getAllInTimespan(const timestamp_t start, const timestamp_t end, ConnectedVisionResponse &response);

protected:
	int respond(const std::string& filePath, ConnectedVisionResponse& response);

	DirectoryIteratorModule* module;
	Class_generic_config config;
	ConnectedVision::shared_ptr<ConnectedVision::DataHandling::IStore_Read<Class_DirectoryIterator_output_FileMetadata>> fileMetadataOutputPin;
};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // OutputPin_DirectoryIterator_output_BinaryData_def