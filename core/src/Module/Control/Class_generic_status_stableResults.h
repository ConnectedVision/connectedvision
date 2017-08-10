/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// Class_generic_status_stableResults.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_generic_status_stableResults_def
#define Class_generic_status_stableResults_def


#include <IStore.h>
#include <ConnectedVision.h>

#include "stubs/Stub_generic_status_stableResults.h"

namespace ConnectedVision { 


// if you want to extend the auto-generated class, enable the line below
#define Class_generic_status_stableResults_extended

#ifdef Class_generic_status_stableResults_extended
/**
 * Class_generic_status_stableResults
 * 
 * module: 
 * description: 
 */
class Class_generic_status_stableResults : public Stub_generic_status_stableResults {

public:
	Class_generic_status_stableResults() {};
	Class_generic_status_stableResults(const ::rapidjson::Value& value) : Stub_generic_status_stableResults(value) {};
	Class_generic_status_stableResults(const std::string& str) : Stub_generic_status_stableResults(str) {};
	virtual ~Class_generic_status_stableResults() {};

	// copy function
	inline ::ConnectedVision::shared_ptr<Class_generic_status_stableResults> clone() const
	{
		::ConnectedVision::shared_ptr<Class_generic_status_stableResults> ptr( new Class_generic_status_stableResults(*this) );
		return ptr;
	}

	// additional functions
	inline int64_t get_indexCount() const
	{
		if(getconst_indexEnd() < 0)
		{
			return 0;
		}
		else
		{
			return getconst_indexEnd() - getconst_indexStart() + 1;
		}
	}

	inline timestamp_t get_timestampRange() const { return (getconst_timestampEnd() - getconst_timestampStart()); }

	template <class TDataClass>
	inline void importFromStore( const ::ConnectedVision::DataHandling::IStore_Read<TDataClass> &store )
	{
		auto storeDataRange = store.getDataRange();
		this->set_indexStart( storeDataRange.indexStart );
		this->set_indexEnd( storeDataRange.indexEnd );
		this->set_timestampStart( storeDataRange.timestampStart );
		this->set_timestampEnd( storeDataRange.timestampEnd );
	}

	template <class TDataClass>
	static inline ::ConnectedVision::shared_ptr<Class_generic_status_stableResults> createFromStore( ::ConnectedVision::DataHandling::IStore_Read<TDataClass> &store )
	{
		::ConnectedVision::shared_ptr<Class_generic_status_stableResults> stableResults = ::ConnectedVision::make_shared<Class_generic_status_stableResults>();
		stableResults->importFromStore( store );
		return stableResults;
	}
};
typedef boost::shared_ptr<Class_generic_status_stableResults> Class_generic_status_stableResults_p;
#endif // Class_generic_status_stableResults_extended



} // namespace ConnectedVision 


#include "stubs/Class_generic_status_stableResults_Default.h"

#endif // Class_generic_status_stableResults_def
