{%- autoescape false -%}{%- include global.macroPath -%}
#ifndef {{Module.moduleID}}Module_def
#define {{Module.moduleID}}Module_def

#include <IConnectedVisionModule.h>
#include <IStore.h>

#include <Module/Module_BaseClass.h>

{% for d in Module.outputPins %}
#include "{{d.DataClass.classHeaderPath}}"
{% endfor %}

{{ openNamespace(global.namespace) }}

/**
*	module class: {{Module.name}}
*	{{Module.description}}
*/
class {{Module.moduleID}}Module: public Module_BaseClass
{
friend class {{Module.moduleID}}Worker;
public:
	/**
	* module constructor
	*/
	{{Module.moduleID}}Module();

	
	
	/**
	* worker factory (implement IWorkerFactory interface)
	*
	* @return {{Module.name}} worker
	*/
	virtual std::unique_ptr<IWorker> createWorker(
		IWorkerControllerCallbacks &controller,									///< reference to worker controller
		ConnectedVision::shared_ptr<const Class_generic_config> config	///< config for the worker to be created
	);

	/**
	* delete data / results of a given config
	*/
	virtual void deleteAllData(
		const id_t configID		///< [in] config ID of data to be deleted
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