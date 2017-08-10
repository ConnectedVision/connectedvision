/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <vector>
#include <algorithm>

#include <Module/Control/Class_generic_status.h>

#include <CppUTest/TestHarness.h>

using namespace ConnectedVision;

TEST_GROUP(Class_generic_status)
{
	void setup()
	{
		// Init stuff
	}

	void teardown()
	{
		// Uninit stuff
	}

};

template<class Container>
static ConnectedVision::shared_ptr<Class_generic_status_stableResults> find_stableSesults( Container list, pinID_t pinID )
{
	ConnectedVision::shared_ptr<Class_generic_status_stableResults> found;
	for( auto it = list->begin(); it != list->end(); ++it )
	{
		if ( *(*it)->getconst_pinID() == pinID )
		{
			// results found
			found = *it;
			break;
		}
	}

	return found;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Class_generic_status tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IGNORE_TEST(Class_generic_status, equals_returns_true_on_same_object)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status;

	//////////////////////////////////////
	// actual test
	CHECK( status.equals( status ) );
}

IGNORE_TEST(Class_generic_status, equals_returns_true_on_similar_object)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status1;
	status1.set_id("id");

	Class_generic_status status2( status1.toJson() );

	//////////////////////////////////////
	// actual test
	CHECK( status1.equals( status2 ) );
}

IGNORE_TEST(Class_generic_status, equals_returns_false_on_different_object)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status1;
	status1.set_id("id1");

	Class_generic_status status2( status1.toJson() );
	status2.set_id("id2");

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( status1.equals( status2 ) );
}

IGNORE_TEST(Class_generic_status, equals_makes_deep_compare)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status1;
	status1.get_qualityOfService()->set_compuationDuration(1);

	Class_generic_status status2( status1.toJson() );
	status2.get_qualityOfService()->set_compuationDuration(2);

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( status1.equals( status2 ) );

	status2.get_qualityOfService()->set_compuationDuration( status1.get_qualityOfService()->get_compuationDuration() );
	CHECK( status1.equals( status2 ) );
}

TEST(Class_generic_status, set_stableResultsByPinID_set_pinID)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status;
	Class_generic_status_stableResults results;
	pinID_t pinID = "testPin";

	results.set_indexStart( 0 );
	results.set_indexEnd( 100 );
	results.set_timestampStart( 0 );
	results.set_timestampEnd( 1000 );

	//////////////////////////////////////
	// actual test
	{
		results.set_pinID( pinID );
		status.set_stableResultsByPinID( results, pinID );
		// find pinID
		auto list = status.getconst_stableResults();
		auto found = find_stableSesults(list, pinID);
		CHECK( found );
	}

	// set results with other pinID
	{
		pinID = "xyz";
		status.set_stableResultsByPinID( results, pinID );
		// find pinID
		auto list = status.getconst_stableResults();
		auto found = find_stableSesults(list, pinID);
		CHECK( found );
	}
}

TEST(Class_generic_status, set_stableResultsByPinID_adds_new_results)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status;
	Class_generic_status_stableResults results;
	pinID_t pinID = "testPin";

	results.set_indexStart( 0 );
	results.set_indexEnd( 100 );
	results.set_timestampStart( 0 );
	results.set_timestampEnd( 1000 );

	//////////////////////////////////////
	// actual test
	status.set_stableResultsByPinID( results, pinID );
	
	// find pinID
	auto list = status.getconst_stableResults();
	auto retrieved = find_stableSesults(list, pinID);
	
	CHECK(retrieved);
	LONGS_EQUAL( results.getconst_indexStart(), retrieved->getconst_indexStart() );
	LONGS_EQUAL( results.getconst_indexEnd(), retrieved->getconst_indexEnd() );
	LONGS_EQUAL( results.getconst_timestampStart(), retrieved->getconst_timestampStart() );
	LONGS_EQUAL( results.getconst_timestampEnd(), retrieved->getconst_timestampEnd() );
}

TEST(Class_generic_status, set_stableResultsByPinID_overwrites_old_results)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status;
	Class_generic_status_stableResults results;
	pinID_t pinID = "testPin";

	results.set_indexStart( 0 );
	results.set_indexEnd( 100 );
	results.set_timestampStart( 0 );
	results.set_timestampEnd( 1000 );

	//////////////////////////////////////
	// actual test
	status.set_stableResultsByPinID( results, pinID );
	
	// update results
	results.set_indexStart( 10 );
	results.set_indexEnd( 10 );
	results.set_timestampStart( 10 );
	results.set_timestampEnd( 10 );
	status.set_stableResultsByPinID( results, pinID );

	// find pinID
	auto list = status.getconst_stableResults();
	auto retrieved = find_stableSesults(list, pinID);
	
	CHECK(retrieved);
	LONGS_EQUAL( results.getconst_indexStart(), retrieved->getconst_indexStart() );
	LONGS_EQUAL( results.getconst_indexEnd(), retrieved->getconst_indexEnd() );
	LONGS_EQUAL( results.getconst_timestampStart(), retrieved->getconst_timestampStart() );
	LONGS_EQUAL( results.getconst_timestampEnd(), retrieved->getconst_timestampEnd() );
}

TEST(Class_generic_status, set_stableResultsByPinID_object_should_make_local_copy)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status;
	Class_generic_status_stableResults results;
	pinID_t pinID = "testPin";

	results.set_indexStart( 0 );
	results.set_indexEnd( 100 );
	results.set_timestampStart( 0 );
	results.set_timestampEnd( 1000 );

	//////////////////////////////////////
	// actual test
	results.set_pinID( pinID );
	status.set_stableResultsByPinID( results, pinID );
	
	// find pinID
	auto list = status.getconst_stableResults();
	auto retrieved = find_stableSesults(list, pinID);

	// change original
	results.set_indexStart( 100 );
	CHECK( results.getconst_indexStart() != retrieved->getconst_indexStart() );
}

TEST(Class_generic_status, set_stableResultsByPinID_shared_ptr_should_make_local_copy)
{
	//////////////////////////////////////
	// test initialization
	Class_generic_status status;
	auto results = ConnectedVision::make_shared<Class_generic_status_stableResults>();
	pinID_t pinID = "testPin";

	results->set_indexStart( 0 );
	results->set_indexEnd( 100 );
	results->set_timestampStart( 0 );
	results->set_timestampEnd( 1000 );

	//////////////////////////////////////
	// actual test
	results->set_pinID( pinID );
	status.set_stableResultsByPinID( results, pinID );
	
	// find pinID
	auto list = status.getconst_stableResults();
	auto retrieved = find_stableSesults(list, pinID);

	// change original
	results->set_indexStart( 100 );
	CHECK( results->getconst_indexStart() != retrieved->getconst_indexStart() );
}

TEST(Class_generic_status, check_quality_of_service_computation_duration_average_default_value)
{
	Class_generic_status status;
	
	LONGS_EQUAL(-1, status.getconst_qualityOfService()->getconst_compuationDurationAverage());
}

TEST(Class_generic_status, check_quality_of_service_computation_duration_average_being_still_default_after_first_call_to_set_systemTimeProcessing)
{
	Class_generic_status status;

	status.set_systemTimeProcessing(0);
	
	LONGS_EQUAL(-1, status.getconst_qualityOfService()->getconst_compuationDurationAverage());
}

TEST(Class_generic_status, set_systemTimeProcessing_throws_exception_for_decreasing_values)
{
	Class_generic_status status;
	CHECK_THROWS(ConnectedVision::runtime_error, status.set_systemTimeProcessing(-2));

	status = Class_generic_status();
	status.set_systemTimeProcessing(0);
	CHECK_THROWS(ConnectedVision::runtime_error, status.set_systemTimeProcessing(-1));
}

TEST(Class_generic_status, set_systemTimeProcessing_should_compute_quality_of_service_computation_duration_for_increasing_intervals)
{
	Class_generic_status status;
	int windowSize = 1;

	// initialization
	std::vector<timestamp_t> timestamps;

	for(int i = 0; i < 20; i++)
	{
		timestamps.push_back(static_cast<timestamp_t>(10 * i * i));
	}

	// actual test for the typical case after the first call of set_systemTimeProcessing
	for(int i = 0; i < timestamps.size(); i++)
	{
		status.set_systemTimeProcessing(timestamps.at(i));

		if(i < windowSize)
		{
			LONGS_EQUAL(-1, status.getconst_qualityOfService()->getconst_compuationDuration());
		}
		else
		{
			int indexStart = i - windowSize;
			timestamp_t avg = (timestamps.at(i) - timestamps.at(indexStart)) / static_cast<timestamp_t>(windowSize);
			LONGS_EQUAL(avg, status.getconst_qualityOfService()->getconst_compuationDuration());
		}
	}
}

TEST(Class_generic_status, set_systemTimeProcessing_should_compute_quality_of_service_computation_duration_average_for_constant_intervals)
{
	Class_generic_status status;
	int windowSize = 10;

	// initialization
	std::vector<timestamp_t> timestamps;

	for(int i = 0; i < 20; i++)
	{
		timestamps.push_back(static_cast<timestamp_t>(10 * i));
	}

	// actual test for the typical case after the first call of set_systemTimeProcessing
	for(int i = 0; i < timestamps.size(); i++)
	{
		status.set_systemTimeProcessing(timestamps.at(i));

		if(i < windowSize)
		{
			LONGS_EQUAL(-1, status.getconst_qualityOfService()->getconst_compuationDurationAverage());
		}
		else
		{
			LONGS_EQUAL(10, status.getconst_qualityOfService()->getconst_compuationDurationAverage());
		}
	}
}

TEST(Class_generic_status, set_systemTimeProcessing_should_compute_quality_of_service_computation_duration_average_for_increasing_intervals)
{
	Class_generic_status status;
	int windowSize = 10;

	// initialization
	std::vector<timestamp_t> timestamps;

	for(int i = 0; i < 20; i++)
	{
		timestamps.push_back(static_cast<timestamp_t>(10 * i * i));
	}

	// actual test for the typical case after the first call of set_systemTimeProcessing
	for(int i = 0; i < timestamps.size(); i++)
	{
		status.set_systemTimeProcessing(timestamps.at(i));

		if(i < windowSize)
		{
			LONGS_EQUAL(-1, status.getconst_qualityOfService()->getconst_compuationDurationAverage());
		}
		else
		{
			int indexStart = i - windowSize;
			timestamp_t avg = (timestamps.at(i) - timestamps.at(indexStart)) / static_cast<timestamp_t>(windowSize);
			LONGS_EQUAL(avg, status.getconst_qualityOfService()->getconst_compuationDurationAverage());
		}
	}
}