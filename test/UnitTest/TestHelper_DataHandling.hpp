/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef TestHelper_DataHandling_code
#define TestHelper_DataHandling_code

#include <CppUTest/TestHarness.h>
#include "IStore.h"

namespace ConnectedVision {
namespace DataHandling {

/*
 * simple test data class
 *
 * implementing IConnectedVisionDataClass interface
 */
class TestDataClass
{
public:
	TestDataClass() : clearCount(0) {};
	virtual ~TestDataClass() {};

	const id_t& getconst_id() const {return this->id;};
	void set_id(id_t value) {this->id = value;};

	const id_t& getconst_configID() const {return this->configID;};
	void set_configID(id_t value) {this->configID = value;}

	const timestamp_t& getconst_timestamp() const {return this->timestamp;}
	void set_timestamp(timestamp_t value) {this->timestamp = value;}

	const int64_t& getconst_x() const {return this->x;}
	void set_x(int64_t value) {this->x = value;}

	void clear() {
		this->id.clear();
		this->configID.clear();
		this->timestamp = 0;
		this->x = 0;
		this->clearCount++;
	}

	std::string toJsonStr()	const {
		std::string str = "{ /* TODO */ }";
		return str;
	}

	// helper functions
	int& spy_clearCount() { return clearCount; }

	ConnectedVision::shared_ptr<TestDataClass> copy() const {
		ConnectedVision::shared_ptr<TestDataClass> clone( new TestDataClass( *this ) );
		return clone;
	}

private:
	int clearCount;
	id_t id;
	id_t configID;
	timestamp_t timestamp;
	int64_t x;
};

/**
	data class allocator and pool management
*/
class TestWrapper_DataAllocator : public IDataAllocator<TestDataClass>
{
public:
	TestWrapper_DataAllocator() {};

	ConnectedVision::shared_ptr<TestDataClass> create()
	{
		ConnectedVision::shared_ptr<TestDataClass> data = ConnectedVision::make_shared<TestDataClass>();
		data->clear(); // reset the data object, not the pointer!
		return data;
	}

	void initiateRelease(ConnectedVision::shared_ptr<const TestDataClass>& data)
	{
		data.reset();
	}

	ConnectedVision::shared_ptr<const TestDataClass> make_const(ConnectedVision::shared_ptr<TestDataClass>& data) const
	{
		if ( data.use_count() > 1 )
			throw ConnectedVision::runtime_error("save_move(): cannot move pointer if object is already shared");
		const ConnectedVision::shared_ptr<const TestDataClass> constData( std::move(data) );
		return constData;
	}
};

static inline ConnectedVision::shared_ptr<const TestDataClass> make_dataConst(ConnectedVision::shared_ptr<TestDataClass> &data)
{
	ConnectedVision::shared_ptr<const TestDataClass> dataConst = boost::const_pointer_cast<const TestDataClass>(data); 
	data.reset();
	return dataConst;
}

template<typename TDataClass>
static inline void CHECK_DATA_EQUAL( const shared_ptr<const TDataClass>& expected, const shared_ptr<const TDataClass>& actual )
{
	CHECK(actual);
	CHECK_EQUAL( expected->getconst_configID(), actual->getconst_configID() );
	CHECK_EQUAL( expected->getconst_id(), actual->getconst_id() );
	LONGS_EQUAL( expected->getconst_timestamp(), actual->getconst_timestamp() );
}

template<typename TDataClass>
static inline void CHECK_DATAVECTOR_EQUAL( const std::vector< shared_ptr<const TDataClass> > expectedList, const std::vector< shared_ptr<const TDataClass> >actualList )
{
	LONGS_EQUAL( expectedList.size(), actualList.size() );
	for( size_t i = 0; i < expectedList.size(); ++i)
	{
		CHECK_DATA_EQUAL(expectedList.at(i), actualList.at(i));
	}
}

}} // namespace scope
#endif // TestHelper_DataHandling_code