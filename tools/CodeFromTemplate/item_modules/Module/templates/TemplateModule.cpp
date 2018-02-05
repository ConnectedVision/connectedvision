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

{{Module.moduleID}}Module::{{Module.moduleID}}Module() : Module_BaseClass(_moduleDescription, _inputPinDescription, _outputPinDescription)
{

}

void {{Module.moduleID}}Module::prepareStores() 
{
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
	{% for d in Module.outputPins %}{% if loop.first %}	if{% else %}	else if{% endif %} ( {{d.className}}::hasPinID(pinID) )
	{
		// {{d.name}} output pin
		return boost::make_shared<OutputPins::OutputPin_JSON<{{d.DataClass.className}}>>(this->storeManager{{d.name}});
	}
	{% endfor %}

	throw ConnectedVision::runtime_error("failed to generate output pin (invalid pin ID: " + pinID + ")");
}

std::unique_ptr<IWorker> {{Module.moduleID}}Module::createWorker(IWorkerControllerCallbacks &controller, ConnectedVision::shared_ptr<const Class_generic_config> config) 
{
	// create worker instance
	std::unique_ptr<IWorker> ptr( new {{Module.moduleID}}Worker(*this, controller, config) );

	return ptr;
}

void {{Module.moduleID}}Module::deleteAllData(const id_t configID)
{
	// delete all results for configID
{% for d in Module.outputPins %}	
	this->storeManager{{d.name}}->getReadWriteStore( configID )->deleteAll();
{% endfor %}
}

{{ closeNamespace(global.namespace) }}