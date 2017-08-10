/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "generated/Class_UnitTest_GeneratorTestCode.h"

#include <CppUTest/TestHarness.h>

namespace ConnectedVision {
namespace UnitTest {

using namespace ConnectedVision;

TEST_GROUP(Class_UnitTest_GeneratorTestCode)
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


static inline void initTestObject(Class_UnitTest_GeneratorTestCode& obj)
{
	obj.set_id("testID");
	obj.set_intVal(42);
	obj.set_stringVal("test");

	// simple integer array
	for ( int i = 0; i < 10; ++i )
		obj.add_simpleArray(i);

	// string array
	for ( int i = 0; i < 10; ++i )
		obj.add_stringArray( intToStr(i) );

	// 3 dimensional array of integer
	auto tmpZ = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>();
	for ( size_t z = 0; z < 10; ++z )
	{
		auto tmpY = boost::make_shared<std::vector<boost::shared_ptr<std::vector<int64_t>>>>();
		tmpZ->push_back( tmpY );
		for ( size_t y = 0; y < 10; ++y )
		{
			auto tmpX = boost::make_shared<std::vector<int64_t>>();
			tmpY->push_back( tmpX );
			for ( size_t x = 0; x < 10; ++x )
			{
				tmpX->push_back( z*100 + y*10 + x );
			}
		}
	}
	obj.set_intArray( tmpZ );

	// simple sub object
	Class_UnitTest_GeneratorTestCode_simpleObject tmpObj;
	tmpObj.set_name("init");
	tmpObj.set_value(1);
	obj.set_simpleObject( tmpObj );

	// object array
	for ( int i = 0; i < 5; ++i )
	{
		auto subObj = boost::make_shared<Class_UnitTest_GeneratorTestCode_objArray>();
		subObj->set_name("init");
		subObj->set_index(i);
		obj.add_objArray(subObj);
	}
}

static inline void checkDeepCopy(Class_UnitTest_GeneratorTestCode& orig, Class_UnitTest_GeneratorTestCode& copy)
{
	// check basic members
	CHECK( orig.getconst_id() == copy.getconst_id() );
	orig.set_id("newID");
	CHECK( orig.getconst_id() != copy.getconst_id() );

	CHECK( orig.getconst_intVal() == copy.getconst_intVal() );
	orig.set_intVal(-1);
	CHECK( orig.getconst_intVal() != copy.getconst_intVal() );

	CHECK( *orig.getconst_stringVal() == *copy.getconst_stringVal() );
	// orig.set_stringVal("xyz");
	*orig.get_stringVal() = "xyz";
	CHECK( *orig.getconst_stringVal() != *copy.getconst_stringVal() );

	// check simple integer array
	CHECK( orig.getconst_simpleArray()->size() == copy.getconst_simpleArray()->size() );
	orig.add_simpleArray(100);	
	CHECK( orig.getconst_simpleArray()->size() != copy.getconst_simpleArray()->size() );
	auto&& simpleArray = orig.get_simpleArray();
	CHECK( simpleArray->at(0) == copy.getconst_simpleArray(0) );
	simpleArray->at(0) = 11;
	CHECK( simpleArray->at(0) != copy.getconst_simpleArray(0) );

	// check string array
	CHECK( orig.getconst_stringArray()->size() == copy.getconst_stringArray()->size() );
	orig.add_stringArray("xyz");	
	CHECK( orig.getconst_stringArray()->size() != copy.getconst_stringArray()->size() );
	auto&& stringArray = orig.get_stringArray();
	CHECK( *stringArray->at(0) == *copy.getconst_stringArray(0) );
	stringArray->at(0) = make_shared<std::string>("new");
	CHECK( *stringArray->at(0) != *copy.getconst_stringArray(0) );

	// check 3 dimensional integer array
	CHECK( orig.getconst_intArray()->size() == copy.getconst_simpleArray()->size() );
	orig.add_intArray( copy.get_intArray(0) );
	CHECK( orig.getconst_intArray()->size() != copy.getconst_simpleArray()->size() );
	auto&& intArray = orig.get_intArray();
	CHECK( intArray->at(0)->at(1)->at(2) == copy.getconst_intArray()->at(0)->at(1)->at(2) );
	intArray->at(0)->at(1)->at(2) = -1;
	CHECK( intArray->at(0)->at(1)->at(2) != copy.getconst_intArray()->at(0)->at(1)->at(2) );

	// check simple sub object
	CHECK( *orig.getconst_simpleObject()->getconst_name() == *copy.getconst_simpleObject()->getconst_name() );
	CHECK( orig.getconst_simpleObject()->getconst_value() == copy.getconst_simpleObject()->getconst_value() );
	orig.get_simpleObject()->set_name("xyz");
	orig.get_simpleObject()->set_value(-1);
	CHECK( *orig.getconst_simpleObject()->getconst_name() != *copy.getconst_simpleObject()->getconst_name() );
	CHECK( orig.getconst_simpleObject()->getconst_value() != copy.getconst_simpleObject()->getconst_value() );

	// check object array
	CHECK( orig.getconst_objArray()->size() == copy.getconst_objArray()->size() );
	auto obj = boost::make_shared<Class_UnitTest_GeneratorTestCode_objArray>();
	{
		auto obj = boost::make_shared<Class_UnitTest_GeneratorTestCode_objArray>();
		obj->set_name("new");
		obj->set_index(100);
		orig.add_objArray(obj);	
	}
	CHECK( orig.getconst_objArray()->size() != copy.getconst_objArray()->size() );
	auto&& objArray = orig.get_objArray();
	CHECK( *objArray->at(0)->getconst_name() == *copy.getconst_objArray(0)->getconst_name() );
	objArray->at(0)->set_name("xyz");
	CHECK( *objArray->at(0)->getconst_name() != *copy.getconst_objArray(0)->getconst_name() );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  GeneratedObject tests
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(Class_UnitTest_GeneratorTestCode, copyConstructor_should_make_deep_copy)
{
	//////////////////////////////////////
	// test initialization
	Class_UnitTest_GeneratorTestCode orig;

	initTestObject( orig );

	//////////////////////////////////////
	// actual test

	// copy object
	Class_UnitTest_GeneratorTestCode copy( orig );

	checkDeepCopy( orig, copy );
}

TEST(Class_UnitTest_GeneratorTestCode, copy_assignment_should_make_deep_copy)
{
	//////////////////////////////////////
	// test initialization
	Class_UnitTest_GeneratorTestCode orig;

	initTestObject(orig);

	//////////////////////////////////////
	// actual test

	// copy object
	Class_UnitTest_GeneratorTestCode copy;
	copy = orig;	// make explicit copy

	checkDeepCopy( orig, copy );
}

TEST(Class_UnitTest_GeneratorTestCode, move_assignment)
{
	//////////////////////////////////////
	// test initialization
	Class_UnitTest_GeneratorTestCode orig;

	initTestObject(orig);
	id_t id = orig.getconst_id();

	//////////////////////////////////////
	// actual test

	// copy object
	Class_UnitTest_GeneratorTestCode copy;
	copy = std::move(orig);	// make explicit move
	CHECK_EQUAL( "", orig.getconst_id() );
	CHECK_EQUAL( id, copy.getconst_id() );

	// self move assign
	copy =  std::move(copy);
	CHECK_EQUAL( id, copy.getconst_id() );

}

} // namespace UnitTest
} // namespace ConnectedVision

