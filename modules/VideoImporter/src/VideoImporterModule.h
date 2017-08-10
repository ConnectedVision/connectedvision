/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IConnectedVisionModule.h>
#include <ConnectedVisionModule.h>

#include <ConnectedVisionAlgorithmDispatcher.h>

namespace ConnectedVision {
namespace Module {
namespace VideoImporter {

class VideoImporterModule_priv;

class VideoImporterModule: public ConnectedVisionModule
{
public:
	VideoImporterModule();
	virtual ~VideoImporterModule();

	// module init / release
	virtual void initModule( IModuleEnvironment *env );
	virtual void releaseModule();

	// worker
	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config);

	// data handling
	virtual void deleteResults(const boost::shared_ptr<const Class_generic_config> config);

	ConnectedVision::shared_ptr<Class_generic_status> init(boost::shared_ptr<const Class_generic_config> constConfig);

	boost::shared_ptr<VideoImporterModule_priv> priv;

protected:
	// data access
	virtual void prepareStores();

	/**
	 * Ensure that the config is valid. 
	 * I.e. check that the file is readable, the number of connected input pins is in the range of the pin description min and max values. 
	 * If not, then an error is thrown.
	 */
	virtual void checkConfig(
		const Class_generic_config &config	///< [in] config	configuration chain
	);
	
	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);
};

} // namespace VideoImporter
} // namespace Module
} // namespace ConnectedVision