/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#pragma once

#include <IConnectedVisionModule.h>
#include <ConnectedVisionModule.h>

#include <ConnectedVisionAlgorithmDispatcher.h>

//#include "WinDef.h" 
typedef unsigned char       BYTE;

namespace ConnectedVision {
namespace Module {
namespace SyntheticVideo {

class SyntheticVideoModule_priv;

class SyntheticVideoModule: public ConnectedVisionModule
{
public:
	SyntheticVideoModule();
	virtual ~SyntheticVideoModule();

public:
	// module init / release
	virtual void initModule( IModuleEnvironment *env );
	virtual void releaseModule();

	// worker
	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config);

	// data handling
	virtual void deleteResults(const boost::shared_ptr<const Class_generic_config> config);

public:
	boost::shared_ptr<SyntheticVideoModule_priv> priv;

protected:
	// data access
	virtual void prepareStores();
	
	// input / output pins
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(const pinID_t& pinID);
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(const pinID_t& pinID);

	// overwrite control functions
	virtual void start(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void stop(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void reset(boost::shared_ptr<const Class_generic_config> constConfig);
	virtual void recover(boost::shared_ptr<const Class_generic_config> constConfig);

};

} // namespace SyntheticVideo
} // namespace Module
} // namespace ConnectedVision