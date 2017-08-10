/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <IStore.h>

#include <CppUTest/TestHarness.h>

#include "MixIn_IStore.h"

namespace ConnectedVision 
{ namespace DataHandling
{


MIXIN_GROUP(MixIn_IStore)
{
	void setup() 
	{
		CHECK(params.env);
		CHECK(params.store);
	}
	void teardown()	
	{}
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// IStore interface tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////

MIXIN_TEST(MixIn_IStore, getByID_Empty)
{
	//////////////////////////////////////
	// actual test
	id_t testID = params.env->prefixID + "0";
	auto readData = params.store->getByID(testID);
	CHECK_FALSE(readData);
}

MIXIN_TEST(MixIn_IStore, getByID_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);

	//////////////////////////////////////
	// actual test
	id_t testID = dataList[4]->getconst_id();
	auto readData = params.store->getByID(testID);
	CHECK( readData );
	CHECK_EQUAL( testID, readData->getconst_id() );
}

MIXIN_TEST(MixIn_IStore, getByID_NotFound)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);

	//////////////////////////////////////
	// actual test
	id_t testID = "???";
	auto readData = params.store->getByID(testID);
	CHECK_FALSE(readData);
}

MIXIN_TEST(MixIn_IStore, getByIndex_Empty)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	int64_t testIndex = 0;
	auto readData = params.store->getByIndex(testIndex);
	CHECK_FALSE(readData);
}

MIXIN_TEST(MixIn_IStore, getByIndex_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);

	//////////////////////////////////////
	// actual test
	size_t testIndex = 2;
	auto readData = params.store->getByIndex(testIndex);
	CHECK_EQUAL( dataList[testIndex]->getconst_id(), readData->getconst_id() );
}

MIXIN_TEST(MixIn_IStore, getByIndex_NotFound)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);

	//////////////////////////////////////
	// actual test
	int64_t testIndex = 999;
	auto readData = params.store->getByIndex(testIndex);
	CHECK_FALSE(readData);
}

MIXIN_TEST(MixIn_IStore, getByIndexRange_Empty)
{
	//////////////////////////////////////
	// test initialization
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getByIndexRange(0, 100);
	LONGS_EQUAL( 0, vec.size() );

	vec = params.store->getByIndexRange(0, 0);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByIndexRange_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getByIndexRange(0, 100);
	LONGS_EQUAL( params.env->initSize, vec.size() );

	vec = params.store->getByIndexRange(0, 0);
	LONGS_EQUAL( 1, vec.size() );

	vec = params.store->getByIndexRange(1, 8);
	LONGS_EQUAL( 8, vec.size() );

	vec = params.store->getByIndexRange(5, 100);
	LONGS_EQUAL( dataList.size()-5, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByIndexRange_NotFound)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getByIndexRange(-5, -1);
	LONGS_EQUAL( 0, vec.size() );

	vec = params.store->getByIndexRange(100, 110);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByTimestamp_Empty)
{
	//////////////////////////////////////
	// test initialization
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getByTimestamp(0);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByTimestamp_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = params.store->getByTimestamp(testTime);
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
}

MIXIN_TEST(MixIn_IStore, getByTimestamp_NotFound)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime + 5;
	vec = params.store->getByTimestamp(testTime);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByTimestamp_Underrun)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime - 10000;
	vec = params.store->getByTimestamp(testTime);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByTimestamp_Overrun)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime + 10000;
	vec = params.store->getByTimestamp(testTime);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getByTimestamp_MultipleObjects)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	timestamp_t testTime = params.env->endTime + 10;
	// additional elements with same timestamp
	for (int i = 100; i< 105; ++i)
	{
		auto data = params.env->makeConstData(i, testTime);
		params.store->save_const(data);
	}

	//////////////////////////////////////
	// actual test
	vec = params.store->getByTimestamp(testTime);
	LONGS_EQUAL( 5, vec.size() );
	id_t id;
	for (size_t i = 0; i < vec.size(); ++i)
	{
		LONGS_EQUAL( testTime, vec.at(i)->getconst_timestamp() ); // test that all objects have the same timestamp
		CHECK( vec.at(i)->getconst_id() != id ); // test that object has different id than previouse one
		id = vec.at(i)->getconst_id();
	}
}

MIXIN_TEST(MixIn_IStore, getBeforeTimestamp_Empty)
{
	//////////////////////////////////////
	// test initialization
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getBeforeTimestamp( 0 );
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getBeforeTimestamp_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = params.store->getBeforeTimestamp( testTime+5 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
}

MIXIN_TEST(MixIn_IStore, getBeforeTimestamp_Underrun)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime - 10000;
	vec = params.store->getBeforeTimestamp(testTime);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getBeforeTimestamp_Overrun)
{
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime + 10000;
	vec = params.store->getBeforeTimestamp(testTime);
	LONGS_EQUAL( 1, vec.size() );
	CHECK( vec.at(0)->getconst_timestamp() < testTime );
}

MIXIN_TEST(MixIn_IStore, getAfterTimestamp_Empty)
{
	//////////////////////////////////////
	// test initialization
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getAfterTimestamp( 0 );
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getAfterTimestamp_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = params.store->getAfterTimestamp( testTime - 5 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
}

MIXIN_TEST(MixIn_IStore, getAfterTimestamp_Underrun)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime - 1000;
	vec = params.store->getAfterTimestamp(testTime);
	LONGS_EQUAL( 1, vec.size() );
	CHECK( vec.at(0)->getconst_timestamp() > testTime );
}

MIXIN_TEST(MixIn_IStore, getAfterTimestamp_Overrun)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = params.env->startTime + 1000;
	vec = params.store->getAfterTimestamp(testTime);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getAllInTimespan_Empty)
{
	//////////////////////////////////////
	// test initialization
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	vec = params.store->getAllInTimespan(0, 0);
	LONGS_EQUAL( 0, vec.size() );

	vec = params.store->getAllInTimespan(0, 1000000);
	LONGS_EQUAL( 0, vec.size() );
}

MIXIN_TEST(MixIn_IStore, getAllInTimespan_Found)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);
	std::vector< shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test
	timestamp_t testTime = dataList[2]->getconst_timestamp();
	vec = params.store->getAllInTimespan( testTime, testTime );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	vec = params.store->getAllInTimespan( testTime, testTime + 10 );
	LONGS_EQUAL( 2, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	LONGS_EQUAL( testTime + 10, vec.at(1)->getconst_timestamp() );

	vec = params.store->getAllInTimespan( testTime - 5, testTime + 15 );
	LONGS_EQUAL( 2, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );
	LONGS_EQUAL( testTime + 10, vec.at(1)->getconst_timestamp() );

	// underrun
	testTime = params.env->startTime;
	vec = params.store->getAllInTimespan( 0, testTime - 100 );
	LONGS_EQUAL( 0, vec.size() );
	vec = params.store->getAllInTimespan( 0, testTime );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

	// overrun
	testTime = params.env->endTime;
	vec = params.store->getAllInTimespan( testTime + 100, 1000000 );
	LONGS_EQUAL( 0, vec.size() );
	vec = params.store->getAllInTimespan( testTime, 1000000 );
	LONGS_EQUAL( 1, vec.size() );
	LONGS_EQUAL( testTime, vec.at(0)->getconst_timestamp() );

}

MIXIN_TEST(MixIn_IStore, save_const)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	//////////////////////////////////////
	// actual test

	auto data = params.env->makeConstData(1, testTime);
	id_t id = params.store->save_const(data);
	CHECK_EQUAL(data->getconst_id(), id);
}

MIXIN_TEST(MixIn_IStore, save_const_overwrites_data_with_same_ID)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	std::vector<shared_ptr<const TestDataClass> > vec;
	for (int i = 0; i < 5; ++i)
	{
		auto data = params.env->makeConstData(i, testTime + i*10);
		params.store->save_const( data );
		vec.push_back(data);
	}

	//////////////////////////////////////
	// actual test

	// update timestamp
	auto dataUpdated = params.env->makeConstData(1, testTime + 100);

	// overwrite data
	params.store->save_const( dataUpdated );

	// make sure that the data are not duplicated
	auto readVec = params.store->getByIndexRange(0, 100);
	LONGS_EQUAL( vec.size(), readVec.size() );
	// check sort order of objects
	for ( size_t i = 0; i < readVec.size(); i++ )
	{
		CHECK_EQUAL( vec[i]->getconst_id(), readVec[i]->getconst_id() );
	}

	// make sure that the data are overwritten and not 
	auto readID = params.store->getByID( dataUpdated->getconst_id() );
	CHECK_DATA_EQUAL( dataUpdated, readID );
	auto readIndex = params.store->getByIndex( 1 );
	CHECK_DATA_EQUAL( dataUpdated, readIndex );

}

MIXIN_TEST(MixIn_IStore, save_const_checks_that_ID_is_set)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	//////////////////////////////////////
	// actual test

	auto data = params.env->makeData(1, testTime);
	data->set_id( ID_NULL );
	auto dataConst = params.store->make_const(data);
	CHECK_THROWS( ConnectedVision::runtime_error, params.store->save_const( dataConst ) );
}

MIXIN_TEST(MixIn_IStore, getDataRange_Empty)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	//////////////////////////////////////
	// actual test

	// update timestamp
	auto range = params.store->getDataRange();

	LONGS_EQUAL( -1, range.indexStart );
	LONGS_EQUAL( -1, range.indexEnd );
	LONGS_EQUAL( -1, range.timestampStart );
	LONGS_EQUAL( -1, range.timestampEnd );

}

MIXIN_TEST(MixIn_IStore, getDataRange_Found)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	std::vector<shared_ptr<const TestDataClass> > vec;
	for (int i = 0; i < 5; ++i)
	{
		auto data = params.env->makeConstData(i, testTime + i*10);
		params.store->save_const( data );
		vec.push_back(data);
	}

	//////////////////////////////////////
	// actual test

	// update timestamp
	auto range = params.store->getDataRange();

	LONGS_EQUAL( 0, range.indexStart );
	LONGS_EQUAL( vec.size()-1, range.indexEnd );
	LONGS_EQUAL( vec[0]->getconst_timestamp(), range.timestampStart );
	LONGS_EQUAL( vec[vec.size()-1]->getconst_timestamp(), range.timestampEnd );

}

MIXIN_TEST(MixIn_IStore, save_move)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	//////////////////////////////////////
	// actual test

	auto data = params.env->makeData(1, testTime);
	params.store->save_move(data);
	CHECK_FALSE(data);
}

MIXIN_TEST(MixIn_IStore, save_move_handles_NULL_pointer)
{
	//////////////////////////////////////
	// test initialization
	shared_ptr<TestDataClass> dataNULL;

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, params.store->save_move(dataNULL) );
}

MIXIN_TEST(MixIn_IStore, save_move_overwrites)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;
	auto data = params.env->makeData(1, testTime);
	params.store->save_move(data);

	//////////////////////////////////////
	// actual test

	// update timestamp
	auto dataUpdated = params.env->makeData(1, testTime + 100);
	auto dataCopy = params.env->makeData(1, testTime + 100);

	// overwrite data
	params.store->save_move( dataCopy );

	// make sure that the data are not duplicated
	auto readVec = params.store->getByIndexRange(0, 100);
	LONGS_EQUAL( 1, readVec.size() );

	// make sure that the data are overwritten and not 
	auto read = params.store->getByID( dataUpdated->getconst_id() );
	CHECK_DATA_EQUAL( read, params.store->make_const(dataUpdated) );
}

MIXIN_TEST(MixIn_IStore, save_const_handles_NULL_pointer)
{
	//////////////////////////////////////
	// test initialization
	shared_ptr<const TestDataClass> dataNULL;

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, params.store->save_const(dataNULL) );
}

MIXIN_TEST(MixIn_IStore, save_copy_handles_NULL_pointer)
{
	//////////////////////////////////////
	// test initialization
	shared_ptr<TestDataClass> dataNULL;

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, params.store->save_copy(dataNULL) );
}

MIXIN_TEST(MixIn_IStore, save_copy)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;

	//////////////////////////////////////
	// actual test

	auto data = params.env->makeData(1, testTime);
	params.store->save_copy(data);
	CHECK(data);

	auto readData = params.store->getByID(data->getconst_id());
	CHECK( readData );
	CHECK_DATA_EQUAL( params.store->make_const(data), readData );
}

MIXIN_TEST(MixIn_IStore, save_constVector)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;
	std::vector<shared_ptr<const TestDataClass> > vec;

	//////////////////////////////////////
	// actual test

	vec.clear();
	for (int i = 0; i < 5; ++i)
	{
		auto data = params.env->makeConstData(i, testTime + i*10);
		vec.push_back(data);
	}
	auto idList = params.store->save_constVector(vec);
	for ( size_t i = 0; i < vec.size(); ++i)
	{
		CHECK_EQUAL(vec[i]->getconst_id(), idList[i]);
	}
}

MIXIN_TEST(MixIn_IStore, save_constVector_overwrites)
{
	//////////////////////////////////////
	// test initialization
	const timestamp_t testTime = params.env->startTime;
	std::vector<shared_ptr<const TestDataClass> > vec;
	for (int i = 0; i < 5; ++i)
	{
		auto data = params.env->makeConstData(i, testTime + i*10);
		vec.push_back(data);
	}
	params.store->save_constVector(vec);

	//////////////////////////////////////
	// actual test

	// update timestamp
	vec.clear();
	for (int i = 0; i < 5; ++i)
	{
		auto data = params.env->makeConstData(i, testTime + 100 + i*10);
		vec.push_back(data);
	}

	// overwrite data
	params.store->save_constVector(vec);

	// make sure that the data are overwritten and not duplicated, or discarded
	auto readVec = params.store->getByIndexRange(0, 100);
	CHECK_DATAVECTOR_EQUAL( vec, readVec );
}

MIXIN_TEST(MixIn_IStore, create_should_return_a_preinitialized_object)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestDataClass> data;

	//////////////////////////////////////
	// actual test

	// get element from factory
	data = params.store->create();
	CHECK(data);
	CHECK_EQUAL(params.env->configID, data->getconst_configID());	// check config ID
	CHECK_EQUAL(ID_NULL, data->getconst_id());						// check object ID

	// modify element
	id_t testID = "ID-test";
	data->set_id(testID);
	CHECK_EQUAL(testID, data->getconst_id());
}

MIXIN_TEST(MixIn_IStore, make_const_should_return_a_pointer_to_an_const_object)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestDataClass> data = params.store->create();
	auto *rawPtr = data.get();

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<const TestDataClass> constData = params.store->make_const(data);
	CHECK(constData);
	POINTERS_EQUAL( rawPtr, constData.get() );
}

MIXIN_TEST(MixIn_IStore, make_const_should_move_the_pointer)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestDataClass> data = params.store->create();

	//////////////////////////////////////
	// actual test
	CHECK(data);
	auto constData = params.store->make_const(data);
	CHECK_FALSE(data);
}

MIXIN_TEST(MixIn_IStore, initiateRelease_should_move_the_pointer)
{
	//////////////////////////////////////
	// test initialization
	auto data = params.store->create();
	auto dataConst = params.store->make_const( data );

	//////////////////////////////////////
	// actual test
	CHECK(dataConst);
	params.store->initiateRelease(dataConst);
	CHECK_FALSE(dataConst);
}

MIXIN_TEST(MixIn_IStore, getConfigID_should_return_configID)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	CHECK_EQUAL( params.env->configID, params.store->getConfigID() );
}

MIXIN_TEST(MixIn_IStore, save_should_check_configID)
{
	//////////////////////////////////////
	// test initialization
	auto data = params.env->makeConstData(1, params.env->startTime, "???");

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, params.store->save_const(data) );
}

MIXIN_TEST(MixIn_IStore, save_constVector_should_check_configID)
{
	//////////////////////////////////////
	// test initialization
	std::vector<shared_ptr<const TestDataClass> > dataList;
	for (int i = 0; i < 5; ++i)
		dataList.push_back( params.env->makeConstData(i, params.env->startTime + i*10, "???") );

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::runtime_error, params.store->save_constVector(dataList) );
}

MIXIN_TEST(MixIn_IStore, deleteAll_should_reset_store_indices)
{
	//////////////////////////////////////
	// test initialization
	auto dataList = params.env->fillStoreWithData(*params.store, params.env->initSize);

	//////////////////////////////////////
	// actual test
	auto range = params.store->getDataRange();
	CHECK( range.indexEnd > 0 );
	CHECK( range.timestampEnd > 0 );

	params.store->deleteAll();
	range = params.store->getDataRange();

	LONGS_EQUAL( -1, range.indexStart );
	LONGS_EQUAL( -1, range.indexEnd );
	LONGS_EQUAL( -1, range.timestampStart );
	LONGS_EQUAL( -1, range.timestampEnd );
}

}} // namespace scope
