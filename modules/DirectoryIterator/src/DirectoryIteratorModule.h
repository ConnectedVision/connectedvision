/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef DirectoryIteratorModule_def
#define DirectoryIteratorModule_def

#include <IConnectedVisionModule.h>
#include <IStore.h>

#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>

#include "Class_DirectoryIterator_output_FileMetadata.h"

namespace ConnectedVision {
namespace Module {
namespace DirectoryIterator {

/**
*	module class: Directory Iterator
*	Iterates a directory and returns the files with the extensions specified in the config.
*/
class DirectoryIteratorModule: public ConnectedVisionModule
{
friend class DirectoryIteratorWorker;
friend class OutputPin_DirectoryIterator_output_BinaryData;

public:
	/**
	* module constructor
	*/
	DirectoryIteratorModule();

	/**
	* module init
	*  - allocate resources
	*  - prepare module / worker
	*/
	virtual void initModule(
		IModuleEnvironment *env	///< [in] general environment
	);

	/**
	* module release
	*  - free resources
	*  - tear-down module / worker
	*/
	virtual void releaseModule();

	/**
	* worker factory
	*
	* @return Directory Iterator worker
	*/
	virtual boost::shared_ptr<IConnectedVisionAlgorithmWorker> createWorker(
		IModuleEnvironment *env,								///< [in] general environment
		boost::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	);

	/**
	* delete data / results of a given config
	*/
	virtual void deleteResults(
		const boost::shared_ptr<const Class_generic_config> config	///< [in] config for this worker instance
	);

protected:
	/**
	* connect to stores
	*/
	virtual void prepareStores();
	
	/**
	* output pin factory
	*
	* @return output pin for pinID
	*/
	virtual boost::shared_ptr<IConnectedVisionOutputPin> generateOutputPin(
		const pinID_t& pinID	///< [in] pinID of output pin to be generated
	);

	/**
	* input pin factory
	*
	* @return output pin for pinID
	*/
	virtual boost::shared_ptr<IConnectedVisionInputPin> generateInputPin(
		const pinID_t& pinID	///< [in] pinID of input pin to be generated
	);

	// data store
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<Class_DirectoryIterator_output_FileMetadata> > storeManagerFileMetadata;
};

} // namespace DirectoryIterator
} // namespace Module
} // namespace ConnectedVision

#endif // DirectoryIteratorModule_def