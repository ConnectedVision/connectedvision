// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Stub_UnitTest_GeneratorTestCode_objArray.h
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>


#ifndef Stub_UnitTest_GeneratorTestCode_objArray_def
#define Stub_UnitTest_GeneratorTestCode_objArray_def

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {

/**
 * stub class for: Class_UnitTest_GeneratorTestCode_objArray
 * 
 * module: 
 * description: 
 */
class Stub_UnitTest_GeneratorTestCode_objArray {

public:
	Stub_UnitTest_GeneratorTestCode_objArray();
	Stub_UnitTest_GeneratorTestCode_objArray(const Stub_UnitTest_GeneratorTestCode_objArray& other);
	Stub_UnitTest_GeneratorTestCode_objArray(const rapidjson::Value& value);
	Stub_UnitTest_GeneratorTestCode_objArray(const std::string& str);
	virtual ~Stub_UnitTest_GeneratorTestCode_objArray();
	Stub_UnitTest_GeneratorTestCode_objArray &operator =(const Stub_UnitTest_GeneratorTestCode_objArray& other);
	Stub_UnitTest_GeneratorTestCode_objArray &operator =(Stub_UnitTest_GeneratorTestCode_objArray&& other) noexcept;

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

	/* index -  */
	virtual int64_t get_index() const;
	virtual const int64_t getconst_index() const;
	virtual void set_index(int64_t value);

	/* subArray -  */
	virtual boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> get_subArray() const;
	virtual const boost::shared_ptr<const std::vector<boost::shared_ptr<std::string>>> getconst_subArray() const;
	virtual void set_subArray(boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> value);
	virtual void set_subArray(const std::vector<boost::shared_ptr<std::string>> &value) { boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> ptr = boost::make_shared<std::vector<boost::shared_ptr<std::string>>>(value); set_subArray(ptr); };
	// array functions
	virtual boost::shared_ptr<std::string> get_subArray(int index) const;
	virtual const boost::shared_ptr<std::string>& getconst_subArray(int index) const;
	virtual void add_subArray(boost::shared_ptr<std::string> value);
	virtual void add_subArray(const std::string &value) { boost::shared_ptr<std::string> ptr = boost::make_shared<std::string>(value); add_subArray(ptr); };


protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

	/**  */
	boost::shared_ptr<std::string> name;
	
	/**  */
	int64_t index;
	
	/**  */
	boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>> subArray;
	
};

} // namespace UnitTest
} // namespace ConnectedVision

#endif // Stub_UnitTest_GeneratorTestCode_objArray_def