/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_generic_status.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_generic_status_def
#define Class_generic_status_def

#include "stubs/Stub_generic_status.h"



namespace ConnectedVision { 


// if you want to extend the auto-generated class, enable the line below
#define Class_generic_status_extended

#ifdef Class_generic_status_extended
/**
 * Class_generic_status
 * 
 * module: 
 * description: config status
 */
class Class_generic_status : public Stub_generic_status {

public:
	Class_generic_status() {};
	Class_generic_status(const rapidjson::Value& value) : Stub_generic_status(value) {};
	Class_generic_status(const std::string& str) : Stub_generic_status(str) {};
	virtual ~Class_generic_status() {};

	inline ConnectedVision::shared_ptr<Class_generic_status> copy() const
	{
		ConnectedVision::shared_ptr<Class_generic_status> obj( new Class_generic_status( static_cast<const Class_generic_status &>(*this) ) );
		return obj;
	}

	inline bool equals( const Class_generic_status& other ) const
	{
		// TODO: implement Class_generic_status compare function
		bool equal = false;
		return equal;
	}

	inline bool processing_pending() const
	{
		return (this->is_status_init() || is_status_starting() || is_status_running() || is_status_stopping());
	}

	// helper functions
	Class_generic_status(const id_t& configID, const std::string& moduleID, const std::string& moduleURI, const std::vector<pinID_t> outputPinIDs);

	virtual void resetStableResults(const std::vector<pinID_t> outputPinIDs);
	virtual void resetStableResults();

	/**
	* Resets the computation duration, the computation duration average and the measurement data.
	*/
	void resetComputationDuration();

	virtual boost::shared_ptr<Class_generic_status_stableResults> find_stableResultsByPinID(const pinID_t &pinID) const;
	virtual void set_stableResultsByPinID(const ConnectedVision::shared_ptr<Class_generic_status_stableResults> &results, const pinID_t &pinID);
	virtual void set_stableResultsByPinID(const Class_generic_status_stableResults &results, const pinID_t &pinID) { set_stableResultsByPinID(ConnectedVision::make_shared<Class_generic_status_stableResults>(results), pinID); }

	/**
	* Calls the parent method and computes the quality of service computation duration average parameter.
	*/
	virtual void set_systemTimeProcessing(timestamp_t value);

	// dummy configID getter / setter
	virtual const id_t getconst_configID() const { return ID_NULL; } // the generic status class does not use the configID
	virtual id_t get_configID() const { return ID_NULL; } // the generic status class does not use the configID
	virtual void set_configID(id_t configID) { /* do nothing */ }

	static const unsigned int computationDurationAverageWindowSize = 10; // number of timestamp differences (number of timestamps - 1) used for the computation of the average compuation duration

protected:
	/**
	* Computes and sets the computation duration of the preceding iteration.
	*/
	void computeComputationDuration();

	/**
	* Computes and returns the computation duration average of computationDurationAverageWindowSize preceding iterations using the simple moving average method.
	*/
	timestamp_t computeComputationDurationAverage(unsigned int windowSize);

	/**
	* Computes and sets the computation duration average of n preceding iterations using the simple moving average method.
	*/
	void computeComputationDurationAverage();

	/**
	* Updates the computation duration and the computation duration average.
	*/
	void updateComputationDuration();

	std::vector<pinID_t> outputPinIDs;
	std::vector<timestamp_t> computationDurationTimestamps; // contains timestamp measurements (absolute epoch values) used for the computation of the average compuation duration
};
typedef boost::shared_ptr<Class_generic_status> Class_generic_status_p;
#endif // Class_generic_status_extended



} // namespace ConnectedVision 


#include "stubs/Class_generic_status_Default.h"

#endif // Class_generic_status_def
