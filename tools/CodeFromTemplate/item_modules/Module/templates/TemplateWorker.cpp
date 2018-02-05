{%- autoescape false -%}{%- include global.macroPath -%}
#include <helper.h>

#include <Module/Control/Class_generic_config.h>
#include <Module/Control/Class_generic_status.h>

#include "{{Module.moduleID}}Module.h"
#include "{{Module.moduleID}}Worker.h"
#include "Class_{{Module.moduleID}}_params.h"

{% for d in Module.inputPins %}
#include "{{d.headerPath}}"
{% endfor %}
{% for d in Module.outputPins %}
#include "{{d.headerPath}}"
#include "{{d.DataClass.classHeaderPath}}"
{% endfor %}

{{ openNamespace(global.namespace) }}

using namespace std;
using namespace ConnectedVision;

void {{Module.moduleID}}Worker::run()
{
	// get config ID
	id_t configID = this->config->get_id();
	int64_t index = 0;

	LOG_SCOPE_CONFIG( configID );
	LOG_INFO_CONFIG("worker start", configID);

	// get status
	auto statusStore = this->module.getStatusStore();
	auto status = statusStore->getByID(configID)->copy();

	// if your algorithm does NOT support RESUME, you must reset the config status and delete old results from the store
	// reset status
	status->resetStableResults();
	// delete previous results
	this->module.deleteAllData( configID );

	// update status timestamps
	status->set_estimatedFinishTime( sysTime() + 1000 ); // TODO: how long do we need?
	status->set_systemTimeProcessing( sysTime() );
	statusStore->save_copy(status);

	try
	{
		// start algorithm

		// read config params
		Class_{{Module.moduleID}}_params params;
		params.parseJson( this->config->get_params() );

		// get input pins
{% set masterInputPin = Module.inputPins[0] %}
{% for d in Module.inputPins %}
		// {{d.name}} input
		ConnectedVision::shared_ptr<{{d.className}}> input{{d.name}}Pin = boost::dynamic_pointer_cast<{{d.className}}>( this->module.getInputPin( this->config, {{d.className}}::PinID() ) ); // get input pin from pool and cast to {{d.name}} pin
		auto input{{d.name}}Status = input{{d.name}}Pin->start(); // start previous module and get current status
		pinID_t input{{d.name}}OutputPinID = input{{d.name}}Pin->getOutputPinID(); // map input pin ID to output pin ID
		auto input{{d.name}}StableResults = input{{d.name}}Status.find_stableResultsByPinID( input{{d.name}}OutputPinID );
{% endfor %}

// TODO --> additional input pins come HERE! <--

		// get output store
{% set masterOutputStore = Module.outputPins[0] %}
{% for d in Module.outputPins %}
		// {{d.name}} store
		auto output{{d.name}}Store = this->module.storeManager{{d.name}}->getReadWriteStore(configID);
{% endfor %}

// TODO --> additional stores / output pins come HERE! <--

{% if Module.outputPins.length > 0 %}
		// reset stable results
{% endif %}
{% for d in Module.outputPins %}
		status->set_stableResultsByPinID( Class_generic_status_stableResults::createFromStore(*output{{d.name}}Store), {{d.className}}::PinID() );
{% endfor %}

		// start processing small chunks of data.
		LOG_INFO_CONFIG("start processing", configID);

		do
		{
			// get status from previous module
{% for d in Module.inputPins %}
			input{{d.name}}Status = input{{d.name}}Pin->getStatus();
			input{{d.name}}StableResults = input{{d.name}}Status.find_stableResultsByPinID( input{{d.name}}OutputPinID );

{% endfor %}
{% if masterInputPin %}
			// if there is no new input data, then wait for some time and try again
			if ( input{{masterInputPin.name}}Status.is_status_running() && index > input{{masterInputPin.name}}StableResults->getconst_indexEnd() && this->controller.intermediateContinueCheck() )
			{
				sleep_ms( 500 );
				continue;
			}

			// process all data we got so far and notify WorkerController that we process the next iteration
			for (; index <= input{{masterInputPin.name}}StableResults->getconst_indexEnd() && this->controller.nextIterationStep(); ++index)
			{
				// get {{masterInputPin.name}} data
				auto {{masterInputPin.name|lower}} = input{{masterInputPin.name}}Pin->getByIndex( index );

				if ( !{{masterInputPin.name|lower}} )
				{
					throw ConnectedVision::runtime_error("{{masterInputPin.name}} not found for index: " + intToStr(index) );
				}

				// get other data
				timestamp_t time = {{masterInputPin.name|lower}}->getconst_timestamp();
{% for d in Module.inputPins %}{% if d.name != masterInputPin.name %}
				// get {{d.name}} data
				auto input{{d.name}} = input{{d.name}}Pin->getByTimestamp( time );
				if ( !input{{d.name}} )
				{
					throw ConnectedVision::runtime_error("{{d.name}} not found for timestamp: " + intToStr(time) );
				}
{% endif %}{% endfor %}
{% endif %}

				// prepare output objects
{% for d in Module.outputPins %}
				auto output{{d.name}} = output{{d.name}}Store->create();
{% endfor %}

// TODO --> do some algorithmic work HERE! <--
// YES YOU HAVE TO WRITE SOME CODE YOUR OWN ...!
// NOW IS THE TIME AND HERE IS THE PLACE!

				// save results
{% for d in Module.outputPins %}
				output{{d.name}}Store->save_move( output{{d.name}} );
{% endfor %}

				// update status
{% for d in Module.outputPins %}
				// compute stable results for {{d.name}}
				status->set_stableResultsByPinID( Class_generic_status_stableResults::createFromStore(*output{{d.name}}Store), {{d.className}}::PinID() );
{% endfor %}

{% if masterInputPin && masterOutputStore %}
				// compute progress
				double progress = 0.0;

				if(input{{masterInputPin.name}}StableResults->getconst_indexEnd() > -1)
				{
					progress = static_cast<double>(max(int64_t(1), index - input{{masterInputPin.name}}StableResults->getconst_indexStart()));
					progress /= static_cast<double>(max(int64_t(1), input{{masterInputPin.name}}StableResults->getconst_indexEnd() - input{{masterInputPin.name}}StableResults->getconst_indexStart()));
				}

				status->set_progress(progress);
{% endif %}

{% if masterInputPin %}
				// compute ETA (we will finish when the previous module is finished)
				status->set_estimatedFinishTime( input{{masterInputPin.name}}Status.get_estimatedFinishTime() );
{% endif %}
				status->set_systemTimeProcessing( sysTime() );

				// No bulk save, so we can update the status immediately. Otherwise, wait until the result data are saved
				statusStore->save_copy(status);
{% if masterInputPin %}
			}

		} while ( input{{masterInputPin.name}}Status.is_status_running() && this->controller.intermediateContinueCheck() ); // do-while there is input data to process and check with WorkerController
{% else %}


		} while ( this->controller.nextIterationStep() ); // TODO: how many data do we generate???
{% endif %}

		// update status
		status->set_estimatedFinishTime( sysTime() );
		status->set_systemTimeProcessing( sysTime() );

		if ( this->controller.intermediateContinueCheck() )
		{
			// worker has finished
			status->set_progress( 1.0 );
			status->set_status_finished();
			LOG_INFO_CONFIG("worker finished", configID);
		}
		else
		{
			// worker has been stopped
			status->set_status_stopped();
			LOG_INFO_CONFIG("worker forced to stop", configID);
		}

		statusStore->save_copy(status);
	}
	catch (const std::exception& e)
	{
		try
		{
			LOG_ERROR_CONFIG( e.what(), configID);

			status->set_status_error();
			status->set_message( e.what() );
			status->set_systemTimeProcessing( sysTime() );
			status->set_estimatedFinishTime( -1 );
			statusStore->save_copy(status);
		}
		catch (...)
		{
				// what can we do now???
		}
	}
	catch (...)
	{
		// 	last resort, before crash
	}
}

{{ closeNamespace(global.namespace) }}