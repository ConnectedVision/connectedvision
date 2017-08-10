// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray_def
#define Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {

/**
 * stub class for: Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray
 * 
 * module: 
 * description: sub object
 */
class Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray {

public:
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray();
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray(const Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray& other);
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray(const rapidjson::Value& value);
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray(const std::string& str);
	virtual ~Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray();
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray &operator =(const Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray& other);
	Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray &operator =(Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* sub -  */
	virtual boost::shared_ptr<std::string> get_sub() const;
	virtual const boost::shared_ptr<const std::string> getconst_sub() const;
	virtual void set_sub(boost::shared_ptr<std::string> value);
	virtual void set_sub(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_sub(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	boost::shared_ptr<std::string> sub;
	
};

} // namespace UnitTest
} // namespace ConnectedVision

#endif // Stub_UnitTest_GeneratorTestCode_complexObject_subObjectArray_def