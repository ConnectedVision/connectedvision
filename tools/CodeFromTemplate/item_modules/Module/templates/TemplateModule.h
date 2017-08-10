{%- autoescape false -%}{%- include global.macroPath -%}
#ifndef {{Module.moduleID}}Module_def
#define {{Module.moduleID}}Module_def

#include <IConnectedVisionModule.h>
#include <IStore.h>

#include <ConnectedVisionModule.h>
#include <ConnectedVisionAlgorithmDispatcher.h>

{% for d in Module.outputPins %}
#include "{{d.DataClass.classHeaderPath}}"
{% endfor %}

{{ openNamespace(global.namespace) }}

/**
*	module class: {{Module.name}}
*	{{Module.description}}
*/
class {{Module.moduleID}}Module: public ConnectedVisionModule
{
friend class {{Module.moduleID}}Worker;
public:
	/**
	* module constructor
	*/
	{{Module.moduleID}}Module();

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
	* @return {{Module.name}} worker
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
{% for d in Module.outputPins %}
	ConnectedVision::shared_ptr< ConnectedVision::DataHandling::IStore_Manager<{{d.DataClass.className}}> > storeManager{{d.name}};
{% endfor %}
};

{{ closeNamespace(global.namespace) }}

#endif // {{Module.moduleID}}Module_def