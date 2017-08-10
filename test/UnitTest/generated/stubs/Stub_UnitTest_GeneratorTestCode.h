// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode.h
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
#include "../Class_UnitTest_GeneratorTestCode_objArray.h"
#include "../Class_UnitTest_GeneratorTestCode_simpleObject.h"
#include "../Class_UnitTest_GeneratorTestCode_complexObject.h"

#ifndef Stub_UnitTest_GeneratorTestCode_def
#define Stub_UnitTest_GeneratorTestCode_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {

/**
 * stub class for: Class_UnitTest_GeneratorTestCode
 * 
 * module: 
 * description: test object to check generator
 */
class Stub_UnitTest_GeneratorTestCode {

public:
	Stub_UnitTest_GeneratorTestCode();
	Stub_UnitTest_GeneratorTestCode(const Stub_UnitTest_GeneratorTestCode& other);
	Stub_UnitTest_GeneratorTestCode(const rapidjson::Value& value);
	Stub_UnitTest_GeneratorTestCode(const std::string& str);
	virtual ~Stub_UnitTest_GeneratorTestCode();
	Stub_UnitTest_GeneratorTestCode &operator =(const Stub_UnitTest_GeneratorTestCode& other);
	Stub_UnitTest_GeneratorTestCode &operator =(Stub_UnitTest_GeneratorTestCode&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
	/* configID - config id */
	virtual ConnectedVision::id_t get_configID() const;
	virtual const ConnectedVision::id_t getconst_configID() const;
	virtual void set_configID(ConnectedVision::id_t value);

	/* id - object id */
	virtual ConnectedVision::id_t get_id() const;
	virtual const ConnectedVision::id_t getconst_id() const;
	virtual void set_id(ConnectedVision::id_t value);

	/* timestamp - timestamp of object */
	virtual ConnectedVision::timestamp_t get_timestamp() const;
	virtual const ConnectedVision::timestamp_t getconst_timestamp() const;
	virtual void set_timestamp(ConnectedVision::timestamp_t value);

	/* boolVal - simple boolean value */
	virtual bool get_boolVal() const;
	virtual const bool getconst_boolVal() const;
	virtual void set_boolVal(bool value);

	/* intVal - simple integer value */
	virtual int64_t get_intVal() const;
	virtual const int64_t getconst_intVal() const;
	virtual void set_intVal(int64_t value);

	/* numberVal - simple float value */
	virtual double get_numberVal() const;
	virtual const double getconst_numberVal() const;
	virtual void set_numberVal(double value);

	/* stringVal - simple string value */
	virtual boost::shared_ptr<std::string> get_stringVal() const;
	virtual const boost::shared_ptr<const std::string> getconst_stringVal() const;
	virtual void set_stringVal(boost::shared_ptr<std::string> value);
	virtual void set_stringVal(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_stringVal(ptr); };

	/* anyVal - a generic type should be handled as plan text */
	virtual boost::shared_ptr<std::string> get_anyVal() const;
	virtual const boost::shared_ptr<const std::string> getconst_anyVal() const;
	virtual void set_anyVal(boost::shared_ptr<std::string> value);
	virtual void set_anyVal(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); set_anyVal(ptr); };

	/* simpleArray - 1 dimensional array of integer */
	virtual boost::shared_ptr<std::vector<int64_t>> get_simpleArray() const;
	virtual const boost::shared_ptr<const std::vector<int64_t>> getconst_simpleArray() const;
	virtual void set_simpleArray(boost::shared_ptr<std::vector<int64_t>> value);
	virtual void set_simpleArray(const std::vector<int64_t> &value) { boost::shared_ptr<std::vector<int64_t>> ptr = boost::make_shared<std::vector<int64_t>>(value); set_simpleArray(ptr); };
	// array functions
	virtual int64_t get_simpleArray(int index) const;
	virtual const int64_t& getconst_simpleArray(int index) const;
	virtual void add_simpleArray(int64_t value);

	/* stringArray - 1 dimensional array of string */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> get_stringArray() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> getconst_stringArray() const;
	virtual void set_stringArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value);
	virtual void set_stringArray(const std::vector<boost::shared_ptr<std::string>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>(value); set_stringArray(ptr); };
	// array functions
	virtual boost::shared_ptr<std::string> get_stringArray(int index) const;
	virtual const boost::shared_ptr<std::string>& getconst_stringArray(int index) const;
	virtual void add_stringArray(boost::shared_ptr<std::string> value);
	virtual void add_stringArray(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); add_stringArray(ptr); };

	/* intArray - 3 dimensional array of integer */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> get_intArray() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> getconst_intArray() const;
	virtual void set_intArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> value);
	virtual void set_intArray(const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>(value); set_intArray(ptr); };
	// array functions
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>> get_intArray(int index) const;
	virtual const boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>& getconst_intArray(int index) const;
	virtual void add_intArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>> value);
	virtual void add_intArray(const std::vector<boost::shared_ptr<std::vector<int64_t>>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::vector<int64_t>>>>(value); add_intArray(ptr); };

	/* floatArray - 3 dimensional array of float */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> get_floatArray() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> getconst_floatArray() const;
	virtual void set_floatArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> value);
	virtual void set_floatArray(const std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>>(value); set_floatArray(ptr); };
	// array functions
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>> get_floatArray(int index) const;
	virtual const boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>& getconst_floatArray(int index) const;
	virtual void add_floatArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>> value);
	virtual void add_floatArray(const std::vector<boost::shared_ptr<std::vector<double>>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::vector<double>>>>(value); add_floatArray(ptr); };

	/* objArray - array of objects */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> get_objArray() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> getconst_objArray() const;
	virtual void set_objArray(boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> value);
	virtual void set_objArray(const std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>>(value); set_objArray(ptr); };
	// array functions
	virtual boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray> get_objArray(int index) const;
	virtual const boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>& getconst_objArray(int index) const;
	virtual void add_objArray(boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray> value);
	virtual void add_objArray(const Class_UnitTest_GeneratorTestCode_objArray &value) { boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray> ptr = boost::make_shared<Class_UnitTest_GeneratorTestCode_objArray>(value); add_objArray(ptr); };

	/* simpleObject - simple object with basic types */
	virtual boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject> get_simpleObject() const;
	virtual const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_simpleObject> getconst_simpleObject() const;
	virtual void set_simpleObject(boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject> value);
	virtual void set_simpleObject(const Class_UnitTest_GeneratorTestCode_simpleObject &value) { boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject> ptr = boost::make_shared<Class_UnitTest_GeneratorTestCode_simpleObject>(value); set_simpleObject(ptr); };
	virtual void set_simpleObject(const rapidjson::Value& value) { simpleObject->parseJson( value ); };

	/* complexObject - simple object with basic types */
	virtual boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject> get_complexObject() const;
	virtual const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_complexObject> getconst_complexObject() const;
	virtual void set_complexObject(boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject> value);
	virtual void set_complexObject(const Class_UnitTest_GeneratorTestCode_complexObject &value) { boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject> ptr = boost::make_shared<Class_UnitTest_GeneratorTestCode_complexObject>(value); set_complexObject(ptr); };
	virtual void set_complexObject(const rapidjson::Value& value) { complexObject->parseJson( value ); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/** config id */
	ConnectedVision::id_t configID;
	
	/** object id */
	ConnectedVision::id_t id;
	
	/** timestamp of object */
	ConnectedVision::timestamp_t timestamp;
	
	/** simple boolean value */
	bool boolVal;
	
	/** simple integer value */
	int64_t intVal;
	
	/** simple float value */
	double numberVal;
	
	/** simple string value */
	boost::shared_ptr<std::string> stringVal;
	
	/** a generic type should be handled as plan text */
	boost::shared_ptr<std::string> anyVal;
	
	/** 1 dimensional array of integer */
	boost::shared_ptr<std::vector<int64_t>> simpleArray;
	
	/** 1 dimensional array of string */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> stringArray;
	
	/** 3 dimensional array of integer */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>> intArray;
	
	/** 3 dimensional array of float */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>> floatArray;
	
	/** array of objects */
	boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>> objArray;
	
	/** simple object with basic types */
	boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject> simpleObject;
	
	/** simple object with basic types */
	boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject> complexObject;
	
};

} // namespace UnitTest
} // namespace ConnectedVision

#endif // Stub_UnitTest_GeneratorTestCode_def