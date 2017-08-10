{%- autoescape false -%}{%- include global.macroPath -%}
#include <Module/OutputPins/OutputPin_JSON.h>

#include "{{Module.moduleID}}Module.h"
#include "{{Module.moduleID}}Worker.h"

#include "{{Module.moduleID}}_ModuleDescription.h"

{% for d in Module.inputPins %}
#include "{{d.headerPath}}"
{% endfor %}
{% for d in Module.outputPins %}
#include "{{d.headerPath}}"
#include "{{d.DataClass.classHeaderPath}}"
#include "{{d.StoreSQLite.managerHeaderPath}}"
#include "{{d.StoreRingbuffer.managerHeaderPath}}"
{% endfor %}

{{ openNamespace(global.namespace) }}

#define STORE_USE_RINGBUFFER 0

using namespace ConnectedVision;

{{Module.moduleID}}Module::{{Module.moduleID}}Module() : ConnectedVisionModule(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}

void {{Module.moduleID}}Module::initModule( IModuleEnvironment *env ) 
{
	LOG_SCOPE;

	// clean up module before init
	releaseModule();

	// call parent init
	ConnectedVisionModule::initModule(env);
}

void {{Module.moduleID}}Module::releaseModule() 
{
	LOG_SCOPE;

	// call parent release
	ConnectedVisionModule::releaseModule();

	// reset store managers
{% for d in Module.outputPins %}	
	this->storeManager{{d.name}}.reset();	
{% endfor %}

// TODO --> do additional clean-up HERE! <--

}

void {{Module.moduleID}}Module::prepareStores() 
{
	LOG_SCOPE;

	// module specific stores

{% for d in Module.outputPins %}
	// {{d.name}} output pin
#if STORE_USE_RINGBUFFER
	this->storeManager{{d.name}} = ConnectedVision::make_shared<DataHandling::{{d.StoreRingbuffer.managerName}}>(
		10,			// number of stores in manager
		1000,		// number of element slots in ringbuffer
		10010		// total number of available objects (for all ring buffers)
	);
#else
	this->storeManager{{d.name}} = ConnectedVision::make_shared<DataHandling::{{d.StoreSQLite.managerName}}>( this->getDB() );
#endif

{% endfor %}
}

boost::shared_ptr<IConnectedVisionInputPin> {{Module.moduleID}}Module::generateInputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	{% for d in Module.inputPins %}	{% if loop.first %}	if{% else %}	else if{% endif %} ( {{d.className}}::hasPinID(pinID) )
	{
		// {{d.name}} input pin
		return boost::make_shared<{{d.className}}>( this->env, pinID );
	}
	{% endfor %}

	throw ConnectedVision::runtime_error("failed to generate input pin (invalid pin ID: " + pinID + ")");
}

boost::shared_ptr<IConnectedVisionOutputPin > {{Module.moduleID}}Module::generateOutputPin(const pinID_t& pinID)
{
	LOG_SCOPE;

	{% for d in Module.outputPins %}{% if loop.first %}	if{% else %}	else if{% endif %} ( {{d.className}}::hasPinID(pinID) )
	{
		// {{d.name}} output pin
		return boost::make_shared<OutputPins::OutputPin_JSON<{{d.DataClass.className}}>>(this->storeManager{{d.name}});
	}
	{% endfor %}

	throw ConnectedVision::runtime_error("failed to generate output pin (invalid pin ID: " + pinID + ")");
}

boost::shared_ptr<IConnectedVisionAlgorithmWorker> {{Module.moduleID}}Module::createWorker(IModuleEnvironment *env, boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE;

	// create worker instance
	return boost::make_shared<{{Module.moduleID}}Worker>(env, this, config);
}

void {{Module.moduleID}}Module::deleteResults(const boost::shared_ptr<const Class_generic_config> config)
{
	LOG_SCOPE_CONFIG( config->getconst_id() );

	// delete all results for configID
{% for d in Module.outputPins %}	
	this->storeManager{{d.name}}->getReadWriteStore( config->getconst_id() )->deleteAll();
{% endfor %}
}

{{ closeNamespace(global.namespace) }}