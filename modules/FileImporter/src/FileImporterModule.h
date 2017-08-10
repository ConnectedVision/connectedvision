/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <string>

#include <IConnectedVisionModule.h>
#include <ConnectedVisionModule.h>

#include <ConnectedVisionAlgorithmDispatcher.h>

namespace ConnectedVision {
namespace Module {
namespace FileImporter {

class FileImporterModule: public ConnectedVisionModule
{
public:
	FileImporterModule();

public:
	// module init / release
	virtual void initModule( IModuleEnvironment *env );
	virtual void releaseModule();

	// worker
	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config);

	// data handling
	virtual void deleteResults(const boost::shared_ptr<const Class_generic_config> config);

protected:
	// data access
	virtual void prepareStores();

	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);

	virtual void start(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void stop(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void reset(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void recover(boost::shared_ptr<const Class_generic_config> constConfig);

};

} // namespace FileImporter
} // namespace Module
} // namespace ConnectedVision