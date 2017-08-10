// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_complexObject.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


// include child classes
#include "../Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h"

#ifndef Stub_UnitTest_GeneratorTestCode_complexObject_def
#define Stub_UnitTest_GeneratorTestCode_complexObject_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {

/**
 * stub class for: Class_UnitTest_GeneratorTestCode_complexObject
 * 
 * module: 
 * description: simple object with basic types
 */
class Stub_UnitTest_GeneratorTestCode_complexObject {

public:
	Stub_UnitTest_GeneratorTestCode_complexObject();
	Stub_UnitTest_GeneratorTestCode_complexObject(const Stub_UnitTest_GeneratorTestCode_complexObject& other);
	Stub_UnitTest_GeneratorTestCode_complexObject(const rapidjson::Value& value);
	Stub_UnitTest_GeneratorTestCode_complexObject(const std::string& str);
	virtual ~Stub_UnitTest_GeneratorTestCode_complexObject();
	Stub_UnitTest_GeneratorTestCode_complexObject &operator =(const Stub_UnitTest_GeneratorTestCode_complexObject& other);
	Stub_UnitTest_GeneratorTestCode_complexObject &operator =(Stub_UnitTest_GeneratorTestCode_complexObject&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* name -  */
	virtual boost::shared_ptr<std::string> get_name() const;
	virtual const boost::shared_ptr<const std::string> getconst_name() const;
	virtual void set_name(boost::shared_ptr<std::string> value);
	virtual void set_name(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_name(ptr); };

	/* subObjectArray - array of sub objects */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> get_subObjectArray() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> getconst_subObjectArray() const;
	virtual void set_subObjectArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> value);
	virtual void set_subObjectArray(const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>>(value); set_subObjectArray(ptr); };
	// array functions
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>> get_subObjectArray(int index) const;
	virtual const boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>& getconst_subObjectArray(int index) const;
	virtual void add_subObjectArray(boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>> value);
	virtual void add_subObjectArray(const std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>(value); add_subObjectArray(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	boost::shared_ptr<std::string> name;
	
	/** array of sub objects */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>> subObjectArray;
	
};

} // namespace UnitTest
} // namespace ConnectedVision

#endif // Stub_UnitTest_GeneratorTestCode_complexObject_def