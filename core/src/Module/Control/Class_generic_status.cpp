/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "./Class_generic_status.h"

using namespace ConnectedVision;

Class_generic_status::Class_generic_status(const id_t& configID, const std::string& moduleID, const std::string& moduleURI, const std::vector<pinID_t> outputPinIDs)
	: outputPinIDs( outputPinIDs )
{

	// copy config
	this->set_id( configID );
	this->set_moduleID( moduleID );
	this->set_moduleURI( moduleURI );
	this->set_status_init();

	// init default
	this->resetStableResults(outputPinIDs);
	this->resetComputationDuration();
}


void Class_generic_status::computeComputationDuration()
{
	timestamp_t duration = this->computeComputationDurationAverage(1);
	this->get_qualityOfService()->set_compuationDuration(duration);
}


timestamp_t Class_generic_status::computeComputationDurationAverage(unsigned int windowSize)
{
	timestamp_t duration = -1;
	size_t n = this->computationDurationTimestamps.size();

	// computation duration average is only computed when window size + 1 absolute timestamp values exist in order to estimate the computation average duration more robustly
	if(n > windowSize)
	{
		duration = (this->computationDurationTimestamps.at(n - 1) - this->computationDurationTimestamps.at(n - 1 - windowSize)) / static_cast<timestamp_t>(windowSize);
	}

	return duration;
}


void Class_generic_status::computeComputationDurationAverage()
{
	timestamp_t duration = this->computeComputationDurationAverage(computationDurationAverageWindowSize);
	this->get_qualityOfService()->set_compuationDurationAverage(duration);
}


void Class_generic_status::resetComputationDuration()
{
	this->get_qualityOfService()->set_compuationDuration(-1);
	this->get_qualityOfService()->set_compuationDurationAverage(-1);
	this->computationDurationTimestamps.clear();
}


void Class_generic_status::resetStableResults()
{
	if ( this->outputPinIDs.empty() )
	{
		// build pinIDs from current status
		std::vector<pinID_t> pinIDs;
		const std::vector<boost::shared_ptr<Class_generic_status_stableResults>>& stableResults = *getconst_stableResults();
		std::vector<boost::shared_ptr<Class_generic_status_stableResults>>::const_iterator it;
		
		// extract pinIDs from stableResults
		for (it = stableResults.begin(); it != stableResults.end(); ++it)
		{
			pinIDs.push_back( *(*it)->getconst_pinID() );
		}

		this->resetStableResults( pinIDs );
	}
	else
	{
		// use outputPinIDs from constructor
		this->resetStableResults( this->outputPinIDs );
	}
}


void Class_generic_status::resetStableResults(const std::vector<pinID_t> outputPinIDs)
{
	// reset results
	this->set_systemTimeProcessing( sysTime() );
	this->resetComputationDuration();
	this->set_estimatedFinishTime( -1 );
	this->set_progress( 0.0 );

	// ensure to have valid stableResults
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> stableResults( new std::vector<boost::shared_ptr<Class_generic_status_stableResults>>() );
	for ( unsigned int i=0; i < outputPinIDs.size(); ++i )
	{
		boost::shared_ptr<Class_generic_status_stableResults> range( new Class_generic_status_stableResults() );
		range->set_pinID( outputPinIDs[i] );
		range->set_indexStart(-1);
		range->set_indexEnd(-1);
		range->set_timestampStart(-1);
		range->set_timestampEnd(-1);
		stableResults->push_back( range );
	}
	this->set_stableResults( stableResults );
}


boost::shared_ptr<Class_generic_status_stableResults> Class_generic_status::find_stableResultsByPinID(const pinID_t &pinID) const
{

	std::vector<boost::shared_ptr<Class_generic_status_stableResults>>::iterator it;
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_generic_status_stableResults>>> resultsList( get_stableResults() );

	// search for pinID
	for ( it = resultsList->begin(); it != resultsList->end(); ++it )
	{
		if ( pinID == *((*it)->getconst_pinID()) )
			return *it;
	}

	throw ConnectedVision::out_of_range("cannot find pinID: " + pinID);
}


void Class_generic_status::set_stableResultsByPinID(const ConnectedVision::shared_ptr<Class_generic_status_stableResults> &resultsIn, const pinID_t &pinID)
{
	// make copy of stable results object
	auto results = resultsIn->clone();

	// make sure that stable results have correct pinID
	results->set_pinID( pinID );

	// search for pinID
	for ( size_t i = 0; i < this->stableResults->size(); ++i )
	{
		if ( pinID == *this->stableResults->at(i)->getconst_pinID() )
		{
			// update 
			this->stableResults->at(i) = results;
			return;
		}
	}

	// otherwise, append to vector
	this->stableResults->push_back( results );
}


void Class_generic_status::set_systemTimeProcessing(timestamp_t value)
{
	if(value < this->get_systemTimeProcessing())
	{
		throw ConnectedVision::runtime_error("error when updating status systemTimeProcessing: specified value (" + intToStr(value) + ") is smaller than the existing value (" + intToStr(this->get_systemTimeProcessing()) + ")");
	}

	Stub_generic_status::set_systemTimeProcessing(value);

	this->updateComputationDuration();
}


void Class_generic_status::updateComputationDuration()
{
	timestamp_t value = this->get_systemTimeProcessing();

	this->computationDurationTimestamps.push_back(value);

	// throw the oldest entry out of the circular buffer
	if(this->computationDurationTimestamps.size() > (computationDurationAverageWindowSize + 1))
	{
		this->computationDurationTimestamps.erase(this->computationDurationTimestamps.begin());
	}

	this->computeComputationDuration();
	this->computeComputationDurationAverage();
}