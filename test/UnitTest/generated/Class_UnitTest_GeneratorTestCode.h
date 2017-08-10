// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// Class_UnitTest_GeneratorTestCode.h
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.
#ifndef Class_UnitTest_GeneratorTestCode_def
#define Class_UnitTest_GeneratorTestCode_def

#include "stubs/Stub_UnitTest_GeneratorTestCode.h"

namespace ConnectedVision {
namespace UnitTest {

// if you want to extend the auto-generated class, enable the line below
//#define Class_UnitTest_GeneratorTestCode_extended

#ifdef Class_UnitTest_GeneratorTestCode_extended
/**
 * Class_UnitTest_GeneratorTestCode
 * 
 * module: 
 * description: test object to check generator
 */
class Class_UnitTest_GeneratorTestCode : public Stub_UnitTest_GeneratorTestCode {

public:
	Class_UnitTest_GeneratorTestCode() {};
	Class_UnitTest_GeneratorTestCode(const ::rapidjson::Value& value) : Stub_UnitTest_GeneratorTestCode(value) {};
	Class_UnitTest_GeneratorTestCode(const std::string& str) : Stub_UnitTest_GeneratorTestCode(str) {};
	virtual ~Class_UnitTest_GeneratorTestCode() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<Class_UnitTest_GeneratorTestCode> Class_UnitTest_GeneratorTestCode_p;
#endif // Class_UnitTest_GeneratorTestCode_extended

} // namespace UnitTest
} // namespace ConnectedVision

#include "stubs/Class_UnitTest_GeneratorTestCode_Default.h"

#endif // Class_UnitTest_GeneratorTestCode_def