/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <iostream>
#include "ErrorHandling/CallStack.h"
#include "ErrorHandling/Exception_CallStack.h"
#include "ConnectedVision_Exceptions.h"

#include <CppUTest/TestHarness.h>

using namespace ConnectedVision::ErrorHandling;

#ifdef _WIN32
#define noinline __declspec(noinline)
#else
#define noinline __attribute__ ((noinline))
#endif

static noinline std::vector<CallStack::Entry> bar () 
{
	volatile int i = 0; i += 1; // this is a little trick to bypass compiler optimization in release mode (all test helper functions need to be different)
	ConnectedVision::ErrorHandling::CallStack stack;
	return stack.entries;
}
static noinline std::vector<CallStack::Entry> foo () 
{
	return bar();
}

class Base {
public:
	std::vector<CallStack::Entry> method()
	{
		volatile int i = 0; i += 2; // this is a little trick to bypass compiler optimization in release mode (all test helper functions need to be different)
		ConnectedVision::ErrorHandling::CallStack stack;
		return stack.entries;
	}

	virtual std::vector<CallStack::Entry> dynamic()
	{
		volatile int i = 0; i += 3; // this is a little trick to bypass compiler optimization in release mode (all test helper functions need to be different)
		ConnectedVision::ErrorHandling::CallStack stack;
		return stack.entries;
	}

	std::vector<CallStack::Entry> inherited()
	{
		return dynamic();
	}
};

class Derived : public Base {
public:
	std::vector<CallStack::Entry> method()
	{
		volatile int i = 0; i += 4; // this is a little trick to bypass compiler optimization in release mode (all test helper functions need to be different)
		ConnectedVision::ErrorHandling::CallStack stack;
		return stack.entries;
	}

	virtual std::vector<CallStack::Entry> dynamic()
	{
		volatile int i = 0; i += 5; // this is a little trick to bypass compiler optimization in release mode (all test helper functions need to be different)
		ConnectedVision::ErrorHandling::CallStack stack;
		return stack.entries;
	}
};

// test helper macro, do fuzzy search for functin name
#ifdef _DEBUG
	#define FUNCTION_EQUAL( expected, actual )	STRCMP_CONTAINS( static_cast<std::string>(expected).c_str(), static_cast<std::string>(actual).c_str() )
#else
	#define FUNCTION_EQUAL( expected, actual )
#endif

#ifdef CALL_STACK_ENABLED

TEST_GROUP(CallStack)
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

TEST(CallStack, call_stack_of_function)
{
	//////////////////////////////////////
	// test initialization
	CallStack selfStack;

	
	//////////////////////////////////////
	// actual test

	// call foo -> bar
	auto stack = foo();
	// print_stack(stack);

	// check stack depth
	LONGS_EQUAL( selfStack.size()+2, stack.size() );

	// function names
// GCC is removing function names for local functions
// 	FUNCTION_EQUAL( "bar", stack.at(0).function );
//	FUNCTION_EQUAL( "foo", stack.at(1).function );
}

TEST(CallStack, call_stack_of_class_methode)
{
	//////////////////////////////////////
	// test initialization
	CallStack selfStack;

	Base b;
	
	//////////////////////////////////////
	// actual test

	// call normal methode
	auto stack = b.method();
	// print_stack(stack);
	LONGS_EQUAL( selfStack.size()+1, stack.size() );
	FUNCTION_EQUAL( "Base::method", stack.at(0).function );


	// call virtual methode
	stack = b.dynamic();
	LONGS_EQUAL( selfStack.size()+1, stack.size() );
	FUNCTION_EQUAL( "Base::dynamic", stack.at(0).function );

	// call inherited methode -> virtual methode
	stack = b.inherited();
	LONGS_EQUAL( selfStack.size()+2, stack.size() );
	FUNCTION_EQUAL( "Base::dynamic", stack.at(0).function );
	FUNCTION_EQUAL( "Base::inherited", stack.at(1).function );
}

TEST(CallStack, call_stack_of_derived_class)
{
	//////////////////////////////////////
	// test initialization
	CallStack selfStack;

	Derived d;
	
	//////////////////////////////////////
	// actual test

	// call normal methode
	auto stack = d.method();
	// print_stack(stack);
	LONGS_EQUAL( selfStack.size()+1, stack.size() );
	FUNCTION_EQUAL( "Derived::method", stack.at(0).function );

	// call virtual methode
	stack = d.dynamic();
	LONGS_EQUAL( selfStack.size()+1, stack.size() );
	FUNCTION_EQUAL( "Derived::dynamic", stack.at(0).function );

	// call inherited methode -> virtual methode
	stack = d.inherited();
	FUNCTION_EQUAL( "Derived::dynamic", stack.at(0).function );
	FUNCTION_EQUAL( "Base::inherited", stack.at(1).function );
}

TEST(CallStack, call_stack_of_casted_derived_class)
{
	//////////////////////////////////////
	// test initialization
	CallStack selfStack;

	Derived d;
	Base &b = d;
	
	//////////////////////////////////////
	// actual test

	// call normal methode (non-virtual so given class type methode is called)
	auto stack = b.method();
	LONGS_EQUAL( selfStack.size()+1, stack.size() );
	FUNCTION_EQUAL( "Base::method", stack.at(0).function );

	// call virtual methode (virtual so original class type methode is called)
	stack = b.dynamic();
	LONGS_EQUAL( selfStack.size()+1, stack.size() );
	FUNCTION_EQUAL( "Derived::dynamic", stack.at(0).function );

	// call inherited methode -> virtual methode
	stack = b.inherited();
	LONGS_EQUAL( selfStack.size()+2, stack.size() );
	FUNCTION_EQUAL( "Derived::dynamic", stack.at(0).function );
	FUNCTION_EQUAL( "Base::inherited", stack.at(1).function );
}

static noinline void func_throw () 
{
	throw Exception_CallStack<std::runtime_error>("test");
}
TEST(CallStack, call_stack_of_exception)
{
	//////////////////////////////////////
	// test initialization
	CallStack selfStack;

	
	//////////////////////////////////////
	// actual test
	try
	{
		func_throw();
		FAIL("exception not thrown");
	}
	catch (Exception_CallStack<std::runtime_error> &e)
	{
		// print stack
		// print_stack(stack);

		// test stack size
		LONGS_EQUAL( selfStack.size()+1, e.getStack()->size() );
		FUNCTION_EQUAL( selfStack.entries.at(0).function, e.getStack()->entries.at(1).function ); // compare second function name, since directly called function is inlined by GCC

		// search for function name in exception message
		std::string msg = e.what();
		CHECK( msg.find("func_throw") != std::string::npos );
	}
}

TEST(CallStack, ConnectedVision_extension_of_std_exceptions)
{
	//////////////////////////////////////
	// test initialization
	CallStack selfStack;
	
	//////////////////////////////////////
	// actual test
	try
	{
		throw ConnectedVision::runtime_error("test");
	}
	catch (ConnectedVision::runtime_error &e)
	{
		std::string msg = e.what();
		LONGS_EQUAL( selfStack.size(), e.getStack()->size() );
	}
}
#endif