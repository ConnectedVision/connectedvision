/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <sstream>

#include "ConnectedVision_SmartPointer.h"

#include <CppUTest/TestHarness.h>

class TestElement
{
public:
	TestElement() {}
	uint64_t getAddr() {
		return (uint64_t)this;
	}
};

TEST_GROUP(SharedPointer)
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

TEST(SharedPointer, default_constructor_should_create_empty)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr;

	CHECK( !ptr );
}

TEST(SharedPointer, parameterized_constructor_should_create_unique)
{
	//////////////////////////////////////
	// test initialization
	TestElement* pElement = new TestElement;

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr(pElement);

	POINTERS_EQUAL(pElement, ptr.get() );
	LONGS_EQUAL(1, ptr.use_count() );
}

TEST(SharedPointer, constructor_should_accept_boost_shared)
{
	//////////////////////////////////////
	// test initialization
	boost::shared_ptr<TestElement> boostEmpty;
	boost::shared_ptr<TestElement> boostPtr( boost::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test

	// empty
	ConnectedVision::shared_ptr<TestElement> empty(boostEmpty);
	CHECK(!empty);
	POINTERS_EQUAL(NULL, empty.get() );
	LONGS_EQUAL(0, empty.use_count() );

	// object pointer
	ConnectedVision::shared_ptr<TestElement> ptr(boostPtr);
	CHECK(ptr);
	POINTERS_EQUAL(boostPtr.get(), ptr.get() );
	LONGS_EQUAL(2, ptr.use_count() );
}

TEST(SharedPointer, copyConstructor_from_empty_should_create_empty)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr(empty);

	CHECK( !ptr );
	CHECK( !empty );
}

TEST(SharedPointer, copyConstructor_from_unique_should_create_shared)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> other( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr(other);

	CHECK( other == ptr );
	POINTERS_EQUAL(other.get(), ptr.get() );
	LONGS_EQUAL(2, ptr.use_count() );
}

TEST(SharedPointer, move_Constructor_from_empty_should_create_empty)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr( std::move(empty) );

	CHECK( !ptr );
	CHECK( !empty );
}

TEST(SharedPointer, copyConstructor_from_unique_should_move)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> other( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr( std::move(other) );

	CHECK( !other );
	CHECK( other != ptr );
	LONGS_EQUAL(1, ptr.use_count() );
}

TEST(SharedPointer, assignement_should_not_change_original_pointer)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> other( ConnectedVision::make_shared<TestElement>() );
	auto raw = other.get();

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr;

	// assign empty pointer
	ptr = empty;
	CHECK( !ptr );
	CHECK( ptr == empty );

	// assign data pointer
	ptr = other;
	CHECK( ptr );
	CHECK( ptr == other );
	LONGS_EQUAL(2, ptr.use_count() );

	// not change to original pointer
	POINTERS_EQUAL( NULL, empty.get() );
	POINTERS_EQUAL( raw, other.get() );
}

TEST(SharedPointer, assignement_should_accept_boost_shared)
{
	//////////////////////////////////////
	// test initialization
	boost::shared_ptr<TestElement> boostEmpty;
	boost::shared_ptr<TestElement> boostPtr( boost::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test

	// empty
	ConnectedVision::shared_ptr<TestElement> empty;
	empty = boostEmpty;
	CHECK(!empty);
	POINTERS_EQUAL(NULL, empty.get() );
	LONGS_EQUAL(0, empty.use_count() );

	// object pointer
	ConnectedVision::shared_ptr<TestElement> ptr;
	ptr = boostPtr;
	CHECK(ptr);
	POINTERS_EQUAL(boostPtr.get(), ptr.get() );
	LONGS_EQUAL(2, ptr.use_count() );
}

TEST(SharedPointer, shared_ptr_should_be_assignable_to_boost_shared)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> ptr( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test

	// empty
	boost::shared_ptr<TestElement> boostEmpty;
	boostEmpty = empty;
	CHECK(!boostEmpty);
	POINTERS_EQUAL(NULL, boostEmpty.get() );

	// object pointer
	boost::shared_ptr<TestElement> boostPtr;
	boostPtr = ptr;
	CHECK(boostPtr);
	POINTERS_EQUAL(ptr.get(), boostPtr.get());
	LONGS_EQUAL(2, ptr.use_count() );
	LONGS_EQUAL(2, boostPtr.use_count() );
}

TEST(SharedPointer, move_assignement_should_accept_boost_shared)
{
	//////////////////////////////////////
	// test initialization
	boost::shared_ptr<TestElement> boostEmpty;
	boost::shared_ptr<TestElement> boostPtr( boost::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test

	// empty
	ConnectedVision::shared_ptr<TestElement> empty;
	empty = std::move( boostEmpty );
	CHECK(!empty);
	POINTERS_EQUAL(NULL, empty.get() );
	LONGS_EQUAL(0, empty.use_count() );

	// object pointer
	ConnectedVision::shared_ptr<TestElement> ptr;
	ptr = std::move( boostPtr );
	CHECK(ptr);
	LONGS_EQUAL(1, ptr.use_count() );
	CHECK(!boostPtr);
	LONGS_EQUAL(0, boostPtr.use_count() );
}

TEST(SharedPointer, shared_ptr_should_be_move_assignable_to_boost_shared)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> ptr( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test

	// empty
	boost::shared_ptr<TestElement> boostEmpty;
	boostEmpty = std::move( empty );
	CHECK(!boostEmpty);
	POINTERS_EQUAL(NULL, boostEmpty.get() );

	// object pointer
	boost::shared_ptr<TestElement> boostPtr;
	boostPtr = std::move( ptr );
	CHECK(!ptr);
	LONGS_EQUAL(0, ptr.use_count() );
	CHECK(boostPtr);
	LONGS_EQUAL(1, boostPtr.use_count() );
}

TEST(SharedPointer, move_assignement_should_move_change_original_pointer)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> other( ConnectedVision::make_shared<TestElement>() );
	auto raw = other.get();

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr;

	// assign empty pointer
	ptr = std::move(empty);
	CHECK( !empty );

	// assign data pointer
	ptr = std::move(other);
	CHECK( ptr );
	LONGS_EQUAL(1, ptr.use_count() );
	CHECK( !other );

	// memory check, release ptr
	ptr.reset();
}

TEST(SharedPointer, useCount_from_empty_should_return_zero)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;

	//////////////////////////////////////
	// actual test
	LONGS_EQUAL(0, empty.use_count() );
}

TEST(SharedPointer, useCount_should_return_use_count)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> other( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr;

	// not assigned
	LONGS_EQUAL(0, empty.use_count() );
	LONGS_EQUAL(0, ptr.use_count() );
	LONGS_EQUAL(1, other.use_count() );

	// assinge pointer -> 2 pointers to same object
	ptr = other;
	LONGS_EQUAL(2, ptr.use_count() );
	LONGS_EQUAL(2, other.use_count() );
}

TEST(SharedPointer, get_should_return_raw_pointer)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	TestElement* raw = new TestElement;
	ConnectedVision::shared_ptr<TestElement> other(raw);

	//////////////////////////////////////
	// actual test
	POINTERS_EQUAL( NULL, empty.get() );
	POINTERS_EQUAL( raw, other.get() );

	// share object / assign to another shared pointer
	auto ptr = other;
	POINTERS_EQUAL( raw, ptr.get() );
}

TEST(SharedPointer, reset_should_clear_pointer)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> ptr( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test

	// empty pointer
	empty.reset();
	CHECK( !empty );
	POINTERS_EQUAL( NULL, empty.get() );
	LONGS_EQUAL( 0, empty.use_count() );

	// data pointer
	CHECK( ptr );
	ptr.reset();
	CHECK( !ptr );
	POINTERS_EQUAL( NULL, ptr.get() );
	LONGS_EQUAL( 0, ptr.use_count() );
}

TEST(SharedPointer, reset_of_copy_should_not_clear_original)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> original( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	auto ptr = original;
	CHECK( ptr );
	LONGS_EQUAL( 2, ptr.use_count() );

	// reset copy
	ptr.reset();
	CHECK( !ptr );
	POINTERS_EQUAL( NULL, ptr.get() );
	LONGS_EQUAL( 0, ptr.use_count() );

	CHECK( original );
	LONGS_EQUAL( 1, original.use_count() );
}

TEST(SharedPointer, dereference_operator_on_object_should_call_operation)
{
	//////////////////////////////////////
	// test initialization
	TestElement* raw = new TestElement();
	ConnectedVision::shared_ptr<TestElement> ptr( raw );
	ConnectedVision::shared_ptr<TestElement> other( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	POINTERS_EQUAL( raw, raw->getAddr() );
	CHECK( raw->getAddr() == ptr->getAddr() );
	CHECK( ptr->getAddr() != other->getAddr() );
}

TEST(SharedPointer, dereference_operator_on_empty_should_throw_exception)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;
	ConnectedVision::shared_ptr<TestElement> ptr( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	CHECK_THROWS( ConnectedVision::illegal_reference, empty->getAddr() );

	ptr.reset();
	CHECK_THROWS( ConnectedVision::illegal_reference, ptr->getAddr() );
}

TEST(SharedPointer, bool_on_empty_should_return_false)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> empty;

	//////////////////////////////////////
	// actual test
	CHECK_FALSE( empty );
}

TEST(SharedPointer, bool_on_data_pointer_should_return_true)
{
	//////////////////////////////////////
	// test initialization
	ConnectedVision::shared_ptr<TestElement> ptr( ConnectedVision::make_shared<TestElement>() );

	//////////////////////////////////////
	// actual test
	CHECK_TRUE( ptr );
}

TEST_GROUP(MakeShared)
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


TEST(MakeShared, make_shared_pointer_with_default_constructor)
{
	//////////////////////////////////////
	// test initialization

	//////////////////////////////////////
	// actual test
	ConnectedVision::shared_ptr<TestElement> ptr = ConnectedVision::make_shared<TestElement>();
	CHECK( ptr );
}

TEST(MakeShared, exception_in_constructor_should_be_caught)
{
	//////////////////////////////////////
	// test initialization
	class TestConstructorThrows
	{
	public:
		TestConstructorThrows()
		{
			throw ConnectedVision::runtime_error("constructor throws");
		}
	};

	//////////////////////////////////////
	// actual test
	auto ptr = ConnectedVision::make_shared<TestConstructorThrows>();
	CHECK( !ptr );
}

TEST(MakeShared, make_shared_pointer_with_one_argument_constructor)
{
	//////////////////////////////////////
	// test initialization
	class TestConstructorPrimitive
	{
	public:
		TestConstructorPrimitive(int i) {}
	};

	class TestConstructorStringObject
	{
	public:
		TestConstructorStringObject(std::string s) {}
	};

	class TestConstructorStringReference
	{
	public:
		TestConstructorStringReference(std::string &s) 
		{ s = "TestConstructorStringObject"; }
	};

	//////////////////////////////////////
	// actual test
	{
		// integral type
		CHECK( ConnectedVision::make_shared<TestConstructorPrimitive>(1) );
		int i = 0;
		CHECK( ConnectedVision::make_shared<TestConstructorPrimitive>(i) );
	}

	{
		// string type
		std::string str = "test";
		const std::string constStr = "const";
		CHECK( ConnectedVision::make_shared<TestConstructorStringObject>("test") );
		CHECK( ConnectedVision::make_shared<TestConstructorStringObject>(str) );
		CHECK( ConnectedVision::make_shared<TestConstructorStringObject>(constStr) );
	}

	{
		// string reference
		std::string str = "test";
		CHECK( ConnectedVision::make_shared<TestConstructorStringReference>(str) );
		CHECK_EQUAL( "TestConstructorStringObject", str);
	}
}

TEST(MakeShared, make_shared_pointer_with_two_argument_constructor)
{
	//////////////////////////////////////
	// test initialization
	class TestConstructorPrimitive
	{
	public:
		TestConstructorPrimitive(int x, int y) {}
	};

	class TestConstructorReference
	{
	public:
		TestConstructorReference(int &x, int &y) { x=42; y=1; }
	};

	class TestConstructorConstReference
	{
	public:
		TestConstructorConstReference(const int &x, const int &y) {}
	};

	class TestConstructorSecondConstReference
	{
	public:
		TestConstructorSecondConstReference(std::string &p, const std::string &q) 
		{ p = "42"; }
	};

	//////////////////////////////////////
	// actual test
	{
		// integral type
		CHECK( ConnectedVision::make_shared<TestConstructorPrimitive>(1, 2) );
		int x=0, y=0;
		CHECK( ConnectedVision::make_shared<TestConstructorPrimitive>(x, y) );
	}

	{
		// reference
		int x=0, y=0;
		CHECK( ConnectedVision::make_shared<TestConstructorReference>(x, y) );
		LONGS_EQUAL( 42, x );
		LONGS_EQUAL( 1, y );
	}

	{
		// const reference
		CHECK( ConnectedVision::make_shared<TestConstructorConstReference>(1, 2) );
		int x=0, y=0;
		CHECK( ConnectedVision::make_shared<TestConstructorConstReference>(x, y) );
	}

	{
		// second const reference
		std::string p = "p";
		std::string q = "q";
		CHECK( ConnectedVision::make_shared<TestConstructorSecondConstReference>(p, q) );
		CHECK_EQUAL( "42", p );
		CHECK( ConnectedVision::make_shared<TestConstructorSecondConstReference>(p, "xxx") );
	}


}
