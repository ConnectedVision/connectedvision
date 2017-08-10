// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_simpleObject.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_UnitTest_GeneratorTestCode_simpleObject_def
#define Stub_UnitTest_GeneratorTestCode_simpleObject_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {

/**
 * stub class for: Class_UnitTest_GeneratorTestCode_simpleObject
 * 
 * module: 
 * description: simple object with basic types
 */
class Stub_UnitTest_GeneratorTestCode_simpleObject {

public:
	Stub_UnitTest_GeneratorTestCode_simpleObject();
	Stub_UnitTest_GeneratorTestCode_simpleObject(const Stub_UnitTest_GeneratorTestCode_simpleObject& other);
	Stub_UnitTest_GeneratorTestCode_simpleObject(const rapidjson::Value& value);
	Stub_UnitTest_GeneratorTestCode_simpleObject(const std::string& str);
	virtual ~Stub_UnitTest_GeneratorTestCode_simpleObject();
	Stub_UnitTest_GeneratorTestCode_simpleObject &operator =(const Stub_UnitTest_GeneratorTestCode_simpleObject& other);
	Stub_UnitTest_GeneratorTestCode_simpleObject &operator =(Stub_UnitTest_GeneratorTestCode_simpleObject&& other) noexcept;

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

	/* value -  */
	virtual int64_t get_value() const;
	virtual const int64_t getconst_value() const;
	virtual void set_value(int64_t value);


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	boost::shared_ptr<std::string> name;
	
	/**  */
	int64_t value;
	
};

} // namespace UnitTest
} // namespace ConnectedVision

#endif // Stub_UnitTest_GeneratorTestCode_simpleObject_def