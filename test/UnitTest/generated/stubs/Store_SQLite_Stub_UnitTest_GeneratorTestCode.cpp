// auto-generated header by CodeFromTemplate
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_UnitTest_GeneratorTestCode.cpp
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "../Store_SQLite_UnitTest_GeneratorTestCode.h"

#include "Store_SQLite_Stub_UnitTest_GeneratorTestCode.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace UnitTest {
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Stub_UnitTest_GeneratorTestCode
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "UnitTest_GeneratorTestCode";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
	("'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */")
	("'configID' VARCHAR(32) NOT NULL DEFAULT '' /* config id (string) */")
	("'id' VARCHAR(32) NOT NULL DEFAULT '' /* object id (string) */")
	("'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp of object (integer) */")
	("'boolVal' TINYINT /* simple boolean value (boolean) */")
	("'intVal' BIGINT /* simple integer value (integer) */")
	("'numberVal' DOUBLE /* simple float value (number) */")
	("'stringVal' TEXT /* simple string value (string) */")
	("'anyVal' BLOB /* a generic type should be handled as plan text (any) */")
	("'simpleArray._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'simpleArray' BIGINT /*  (integer) */")
	("'stringArray._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'stringArray' TEXT /*  (string) */")
	("'intArray._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'intArray._idx2' BIGINT /* array index dimension: 2 (array) */")
	("'intArray._idx3' BIGINT /* array index dimension: 3 (array) */")
	("'intArray' BIGINT /* actual value (integer) */")
	("'floatArray._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'floatArray._idx2' BIGINT /* array index dimension: 2 (array) */")
	("'floatArray._idx3' BIGINT /* array index dimension: 3 (array) */")
	("'floatArray' DOUBLE /* actual value (number) */")
	("'objArray._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'objArray.name' TEXT /*  (string) */")
	("'objArray.index' BIGINT /*  (integer) */")
	("'objArray.subArray._idx2' BIGINT /* array index dimension: 2 (array) */")
	("'objArray.subArray' TEXT /*  (string) */")
	("'simpleObject.name' TEXT /*  (string) */")
	("'simpleObject.value' BIGINT /*  (integer) */")
	("'complexObject.name' TEXT /*  (string) */")
	("'complexObject.subObjectArray._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'complexObject.subObjectArray._idx2' BIGINT /* array index dimension: 2 (array) */")
	("'complexObject.subObjectArray.sub' TEXT /*  (string) */")
;

// --> Do NOT EDIT <--
Store_SQLite_Stub_UnitTest_GeneratorTestCode::Store_SQLite_Stub_UnitTest_GeneratorTestCode(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<Class_UnitTest_GeneratorTestCode>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
Store_SQLite_Stub_UnitTest_GeneratorTestCode::~Store_SQLite_Stub_UnitTest_GeneratorTestCode()
{
}

#ifdef ENABLE_SQLITE_SEARCH
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by configID
 */
std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > Store_SQLite_Stub_UnitTest_GeneratorTestCode::getBy_configID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("configID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by id
 */
std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > Store_SQLite_Stub_UnitTest_GeneratorTestCode::getBy_id(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("id", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by timestamp
 */
std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > Store_SQLite_Stub_UnitTest_GeneratorTestCode::getBy_timestamp(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by boolVal
 */
std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > Store_SQLite_Stub_UnitTest_GeneratorTestCode::getBy_boolVal(const bool& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("boolVal", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by intVal
 */
std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > Store_SQLite_Stub_UnitTest_GeneratorTestCode::getBy_intVal(const int64_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("intVal", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by numberVal
 */
std::vector<shared_ptr<const Class_UnitTest_GeneratorTestCode> > Store_SQLite_Stub_UnitTest_GeneratorTestCode::getBy_numberVal(const double& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("numberVal", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

#endif

// --> Do NOT EDIT <--
int Store_SQLite_Stub_UnitTest_GeneratorTestCode::readObject(sqlite3_stmt *stmt, shared_ptr<const Class_UnitTest_GeneratorTestCode>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

	int64_t objSortID = sqlite3_column_int64(stmt, 0);
	int64_t sortID = objSortID;
	outObj.reset( new Class_UnitTest_GeneratorTestCode() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
		// process row
			// UnitTest_GeneratorTestCode_configID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
  				obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
			// UnitTest_GeneratorTestCode_id -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
  				obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,2) ) ) );
			// UnitTest_GeneratorTestCode_timestamp -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 3) != SQLITE_NULL )
  				obj->set_timestamp( sqlite3_column_int64(stmt,3) );
			// UnitTest_GeneratorTestCode_boolVal -> bool
  			if ( sqlite3_column_type(stmt, 4) != SQLITE_NULL )
  				obj->set_boolVal( ( sqlite3_column_int(stmt,4) ? true : false ) );
			// UnitTest_GeneratorTestCode_intVal -> int64_t
  			if ( sqlite3_column_type(stmt, 5) != SQLITE_NULL )
  				obj->set_intVal( sqlite3_column_int64(stmt,5) );
			// UnitTest_GeneratorTestCode_numberVal -> double
  			if ( sqlite3_column_type(stmt, 6) != SQLITE_NULL )
  				obj->set_numberVal( sqlite3_column_double(stmt,6) );
			// UnitTest_GeneratorTestCode_stringVal -> std::string
  			if ( sqlite3_column_type(stmt, 7) != SQLITE_NULL )
  				obj->set_stringVal( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,7)) ) ) );
			// UnitTest_GeneratorTestCode_anyVal -> std::string
  			if ( sqlite3_column_type(stmt, 8) != SQLITE_NULL )
  				obj->set_anyVal( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_blob(stmt,8)), sqlite3_column_bytes(stmt,8) ) ) );
			// UnitTest_GeneratorTestCode_simpleArray -> std::vector<int64_t>
  			if ( sqlite3_column_type(stmt, 9) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<int64_t>>&& a1 = obj->get_simpleArray(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<int64_t> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,9) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// simpleArray -> int64_t
  				if ( sqlite3_column_type(stmt, 10) != SQLITE_NULL )
  					a1->at(idx1) = sqlite3_column_int64(stmt,10);
			}
			// UnitTest_GeneratorTestCode_stringArray -> std::vector<boost::shared_ptr<std::string>>
  			if ( sqlite3_column_type(stmt, 11) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a1 = obj->get_stringArray(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<std::string>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,11) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// stringArray -> std::string
  				if ( sqlite3_column_type(stmt, 12) != SQLITE_NULL )
  					a1->at(idx1) = boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,12)) ) );
			}
			// UnitTest_GeneratorTestCode_intArray -> std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>
  			if ( sqlite3_column_type(stmt, 13) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>>>&& a1 = obj->get_intArray(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,13) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// intArray -> std::vector<boost::shared_ptr<std::vector<int64_t>>>
  				if ( sqlite3_column_type(stmt, 14) != SQLITE_NULL )
  				{
  					boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<int64_t>>>>& a2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !a2 ) a2.reset( new std::vector<boost::shared_ptr<std::vector<int64_t>>> );
  					size_t idx2 = static_cast<size_t>( sqlite3_column_int64(stmt,14) );
  					if ( idx2 >= a2->size() ) a2->resize( idx2 +1 );
					// intArray -> std::vector<int64_t>
  					if ( sqlite3_column_type(stmt, 15) != SQLITE_NULL )
  					{
  						boost::shared_ptr<std::vector<int64_t>>& a3 = a2->at(idx2); // lvalue reference for non-const functions like vector::at()
  						if ( !a3 ) a3.reset( new std::vector<int64_t> );
  						size_t idx3 = static_cast<size_t>( sqlite3_column_int64(stmt,15) );
  						if ( idx3 >= a3->size() ) a3->resize( idx3 +1 );
						// intArray -> int64_t
  						if ( sqlite3_column_type(stmt, 16) != SQLITE_NULL )
  							a3->at(idx3) = sqlite3_column_int64(stmt,16);
					}
				}
			}
			// UnitTest_GeneratorTestCode_floatArray -> std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>
  			if ( sqlite3_column_type(stmt, 17) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>>>&& a1 = obj->get_floatArray(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,17) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// floatArray -> std::vector<boost::shared_ptr<std::vector<double>>>
  				if ( sqlite3_column_type(stmt, 18) != SQLITE_NULL )
  				{
  					boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<double>>>>& a2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !a2 ) a2.reset( new std::vector<boost::shared_ptr<std::vector<double>>> );
  					size_t idx2 = static_cast<size_t>( sqlite3_column_int64(stmt,18) );
  					if ( idx2 >= a2->size() ) a2->resize( idx2 +1 );
					// floatArray -> std::vector<double>
  					if ( sqlite3_column_type(stmt, 19) != SQLITE_NULL )
  					{
  						boost::shared_ptr<std::vector<double>>& a3 = a2->at(idx2); // lvalue reference for non-const functions like vector::at()
  						if ( !a3 ) a3.reset( new std::vector<double> );
  						size_t idx3 = static_cast<size_t>( sqlite3_column_int64(stmt,19) );
  						if ( idx3 >= a3->size() ) a3->resize( idx3 +1 );
						// floatArray -> double
  						if ( sqlite3_column_type(stmt, 20) != SQLITE_NULL )
  							a3->at(idx3) = sqlite3_column_double(stmt,20);
					}
				}
			}
			// UnitTest_GeneratorTestCode_objArray -> std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>
  			if ( sqlite3_column_type(stmt, 21) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>>>&& a1 = obj->get_objArray(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,21) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// UnitTest_GeneratorTestCode_objArray -> Class_UnitTest_GeneratorTestCode_objArray
  				{
  					boost::shared_ptr<Class_UnitTest_GeneratorTestCode_objArray>& o2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !o2 ) o2.reset( new Class_UnitTest_GeneratorTestCode_objArray );
					// UnitTest_GeneratorTestCode_objArray_name -> std::string
  					if ( sqlite3_column_type(stmt, 22) != SQLITE_NULL )
  						o2->set_name( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,22)) ) ) );
					// UnitTest_GeneratorTestCode_objArray_index -> int64_t
  					if ( sqlite3_column_type(stmt, 23) != SQLITE_NULL )
  						o2->set_index( sqlite3_column_int64(stmt,23) );
					// UnitTest_GeneratorTestCode_objArray_subArray -> std::vector<boost::shared_ptr<std::string>>
  					if ( sqlite3_column_type(stmt, 24) != SQLITE_NULL )
  					{
  						boost::shared_ptr<std::vector<boost::shared_ptr<std::string>>>&& a3 = o2->get_subArray(); // rvalue reference for const functions
  						if ( !a3 ) a3.reset( new std::vector<boost::shared_ptr<std::string>> );
  						size_t idx3 = static_cast<size_t>( sqlite3_column_int64(stmt,24) );
  						if ( idx3 >= a3->size() ) a3->resize( idx3 +1 );
						// objArray_subArray -> std::string
  						if ( sqlite3_column_type(stmt, 25) != SQLITE_NULL )
  							a3->at(idx3) = boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,25)) ) );
					}
  				}
			}
			// UnitTest_GeneratorTestCode_simpleObject -> Class_UnitTest_GeneratorTestCode_simpleObject
  			{
  				boost::shared_ptr<Class_UnitTest_GeneratorTestCode_simpleObject>&& o1 = obj->get_simpleObject(); // rvalue reference for const functions
  				if ( !o1 ) o1.reset( new Class_UnitTest_GeneratorTestCode_simpleObject );
				// UnitTest_GeneratorTestCode_simpleObject_name -> std::string
  				if ( sqlite3_column_type(stmt, 26) != SQLITE_NULL )
  					o1->set_name( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,26)) ) ) );
				// UnitTest_GeneratorTestCode_simpleObject_value -> int64_t
  				if ( sqlite3_column_type(stmt, 27) != SQLITE_NULL )
  					o1->set_value( sqlite3_column_int64(stmt,27) );
  			}
			// UnitTest_GeneratorTestCode_complexObject -> Class_UnitTest_GeneratorTestCode_complexObject
  			{
  				boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject>&& o1 = obj->get_complexObject(); // rvalue reference for const functions
  				if ( !o1 ) o1.reset( new Class_UnitTest_GeneratorTestCode_complexObject );
				// UnitTest_GeneratorTestCode_complexObject_name -> std::string
  				if ( sqlite3_column_type(stmt, 28) != SQLITE_NULL )
  					o1->set_name( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,28)) ) ) );
				// UnitTest_GeneratorTestCode_complexObject_subObjectArray -> std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>
  				if ( sqlite3_column_type(stmt, 29) != SQLITE_NULL )
  				{
  					boost::shared_ptr<std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>>>&& a2 = o1->get_subObjectArray(); // rvalue reference for const functions
  					if ( !a2 ) a2.reset( new std::vector<boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>> );
  					size_t idx2 = static_cast<size_t>( sqlite3_column_int64(stmt,29) );
  					if ( idx2 >= a2->size() ) a2->resize( idx2 +1 );
					// complexObject_subObjectArray -> std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>
  					if ( sqlite3_column_type(stmt, 30) != SQLITE_NULL )
  					{
  						boost::shared_ptr<std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>>>& a3 = a2->at(idx2); // lvalue reference for non-const functions like vector::at()
  						if ( !a3 ) a3.reset( new std::vector<boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>> );
  						size_t idx3 = static_cast<size_t>( sqlite3_column_int64(stmt,30) );
  						if ( idx3 >= a3->size() ) a3->resize( idx3 +1 );
						// UnitTest_GeneratorTestCode_complexObject_subObjectArray -> Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray
  						{
  							boost::shared_ptr<Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>& o4 = a3->at(idx3); // lvalue reference for non-const functions like vector::at()
  							if ( !o4 ) o4.reset( new Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray );
							// UnitTest_GeneratorTestCode_complexObject_subObjectArray_sub -> std::string
  							if ( sqlite3_column_type(stmt, 31) != SQLITE_NULL )
  								o4->set_sub( boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,31)) ) ) );
  						}
					}
				}
  			}

		error = sqlite3_step(stmt);
		if ( error == SQLITE_ROW )
			sortID = sqlite3_column_int64(stmt, 0);
	}

	outObj = this->make_const(obj);
	return error;
}

// --> Do NOT EDIT <--
int Store_SQLite_Stub_UnitTest_GeneratorTestCode::writeObject(sqlite3_stmt *stmt, const shared_ptr<const Class_UnitTest_GeneratorTestCode>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;


		size_t i1_max = 1;
		if ( i1_max < obj->getconst_simpleArray()->size() )
			i1_max = obj->getconst_simpleArray()->size();
		if ( i1_max < obj->getconst_stringArray()->size() )
			i1_max = obj->getconst_stringArray()->size();
		if ( i1_max < obj->getconst_intArray()->size() )
			i1_max = obj->getconst_intArray()->size();
		if ( i1_max < obj->getconst_floatArray()->size() )
			i1_max = obj->getconst_floatArray()->size();
		if ( i1_max < obj->getconst_objArray()->size() )
			i1_max = obj->getconst_objArray()->size();
		if ( i1_max < obj->getconst_complexObject()->getconst_subObjectArray()->size() )
			i1_max = obj->getconst_complexObject()->getconst_subObjectArray()->size();
	for ( size_t i1 = 0; i1 < i1_max; i1++ )
	{
		size_t i2_max = 1;
		if ( i1 < obj->getconst_intArray()->size() )
		if ( i2_max < obj->getconst_intArray()->at(i1)->size() )
			i2_max = obj->getconst_intArray()->at(i1)->size();
		if ( i1 < obj->getconst_floatArray()->size() )
		if ( i2_max < obj->getconst_floatArray()->at(i1)->size() )
			i2_max = obj->getconst_floatArray()->at(i1)->size();
		if ( i1 < obj->getconst_objArray()->size() )
		if ( i2_max < obj->getconst_objArray()->at(i1)->getconst_subArray()->size() )
			i2_max = obj->getconst_objArray()->at(i1)->getconst_subArray()->size();
		if ( i1 < obj->getconst_complexObject()->getconst_subObjectArray()->size() )
		if ( i2_max < obj->getconst_complexObject()->getconst_subObjectArray()->at(i1)->size() )
			i2_max = obj->getconst_complexObject()->getconst_subObjectArray()->at(i1)->size();
	for ( size_t i2 = 0; i2 < i2_max; i2++ )
	{
		size_t i3_max = 1;
		if ( i1 < obj->getconst_intArray()->size() )
		if ( i2 < obj->getconst_intArray()->at(i1)->size() )
		if ( i3_max < obj->getconst_intArray()->at(i1)->at(i2)->size() )
			i3_max = obj->getconst_intArray()->at(i1)->at(i2)->size();
		if ( i1 < obj->getconst_floatArray()->size() )
		if ( i2 < obj->getconst_floatArray()->at(i1)->size() )
		if ( i3_max < obj->getconst_floatArray()->at(i1)->at(i2)->size() )
			i3_max = obj->getconst_floatArray()->at(i1)->at(i2)->size();
	for ( size_t i3 = 0; i3 < i3_max; i3++ )
	{
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		bind_UnitTest_GeneratorTestCode( stmt, obj, sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_simpleArray()->size() )
		bind_simpleArray( stmt, obj->getconst_simpleArray()->at(i1), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_stringArray()->size() )
		bind_stringArray( stmt, obj->getconst_stringArray()->at(i1), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_intArray()->size() )		if ( i2 < obj->getconst_intArray()->at(i1)->size() )		if ( i3 < obj->getconst_intArray()->at(i1)->at(i2)->size() )
		bind_intArray( stmt, obj->getconst_intArray()->at(i1)->at(i2)->at(i3), sortID, i1, i2, i3 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_floatArray()->size() )		if ( i2 < obj->getconst_floatArray()->at(i1)->size() )		if ( i3 < obj->getconst_floatArray()->at(i1)->at(i2)->size() )
		bind_floatArray( stmt, obj->getconst_floatArray()->at(i1)->at(i2)->at(i3), sortID, i1, i2, i3 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_objArray()->size() )
		bind_objArray( stmt, obj->getconst_objArray()->at(i1), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_objArray()->size() )		if ( i2 < obj->getconst_objArray()->at(i1)->getconst_subArray()->size() )
		bind_objArray_subArray( stmt, obj->getconst_objArray()->at(i1)->getconst_subArray()->at(i2), sortID, i1, i2 );

		bind_simpleObject( stmt, obj->getconst_simpleObject(), sortID );

		bind_complexObject( stmt, obj->getconst_complexObject(), sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_complexObject()->getconst_subObjectArray()->size() )		if ( i2 < obj->getconst_complexObject()->getconst_subObjectArray()->at(i1)->size() )
		bind_complexObject_subObjectArray( stmt, obj->getconst_complexObject()->getconst_subObjectArray()->at(i1)->at(i2), sortID, i1, i2 );
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
	}
	}
	}
	return error;
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_UnitTest_GeneratorTestCode(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_configID()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, IDToChar(obj->getconst_id()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 4, obj->getconst_timestamp() );
	sqlite3_bind_int64(stmt, 5, obj->getconst_boolVal() );
  	sqlite3_bind_int64(stmt, 6, obj->getconst_intVal() );
  	sqlite3_bind_double(stmt, 7, obj->getconst_numberVal() );
  	sqlite3_bind_text(stmt, 8, obj->getconst_stringVal()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_blob(stmt, 9, obj->getconst_anyVal()->c_str(), (int)obj->getconst_anyVal()->size(), SQLITE_TRANSIENT); // TODO update & use sqlite3_bind_blob64()
  	// array: simpleArray handled separately
  	// array: stringArray handled separately
  	// array: intArray handled separately
  	// array: floatArray handled separately
  	// array: objArray handled separately
	// object: simpleObject handled separately
	// object: complexObject handled separately
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_simpleArray(sqlite3_stmt *stmt, const int64_t& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 10, idx1 );
  	sqlite3_bind_int64(stmt, 11, obj );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_stringArray(sqlite3_stmt *stmt, const boost::shared_ptr<const std::string>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 12, idx1 );
  	sqlite3_bind_text(stmt, 13, obj->c_str(), -1, SQLITE_TRANSIENT );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_intArray(sqlite3_stmt *stmt, const int64_t& obj, const int64_t sortID, const int64_t idx1, const int64_t idx2, const int64_t idx3) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 14, idx1 );
	sqlite3_bind_int64(stmt, 15, idx2 );
	sqlite3_bind_int64(stmt, 16, idx3 );
  	sqlite3_bind_int64(stmt, 17, obj );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_floatArray(sqlite3_stmt *stmt, const double& obj, const int64_t sortID, const int64_t idx1, const int64_t idx2, const int64_t idx3) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 18, idx1 );
	sqlite3_bind_int64(stmt, 19, idx2 );
	sqlite3_bind_int64(stmt, 20, idx3 );
  	sqlite3_bind_double(stmt, 21, obj );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_objArray(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_objArray>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 22, idx1 );
  	sqlite3_bind_text(stmt, 23, obj->getconst_name()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_int64(stmt, 24, obj->getconst_index() );
  	// array: subArray handled separately
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_objArray_subArray(sqlite3_stmt *stmt, const boost::shared_ptr<const std::string>& obj, const int64_t sortID, const int64_t idx1, const int64_t idx2) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 22, idx1 );
	sqlite3_bind_int64(stmt, 25, idx2 );
  	sqlite3_bind_text(stmt, 26, obj->c_str(), -1, SQLITE_TRANSIENT );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_simpleObject(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_simpleObject>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
  	sqlite3_bind_text(stmt, 27, obj->getconst_name()->c_str(), -1, SQLITE_TRANSIENT );
  	sqlite3_bind_int64(stmt, 28, obj->getconst_value() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_complexObject(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_complexObject>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
  	sqlite3_bind_text(stmt, 29, obj->getconst_name()->c_str(), -1, SQLITE_TRANSIENT );
  	// array: subObjectArray handled separately
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::bind_complexObject_subObjectArray(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_UnitTest_GeneratorTestCode_complexObject_subObjectArray>& obj, const int64_t sortID, const int64_t idx1, const int64_t idx2) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 30, idx1 );
	sqlite3_bind_int64(stmt, 31, idx2 );
  	sqlite3_bind_text(stmt, 32, obj->getconst_sub()->c_str(), -1, SQLITE_TRANSIENT );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_UnitTest_GeneratorTestCode::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string Store_SQLite_Stub_UnitTest_GeneratorTestCode::objectKey() const
{
	return std::string("_sortID");
}


//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode::Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode::~Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_UnitTest_GeneratorTestCode> > Store_SQLite_Factory_Stub_UnitTest_GeneratorTestCode::create(const id_t configID = ID_NULL)
{
#ifdef Store_SQLite_Factory_UnitTest_GeneratorTestCode_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<Class_UnitTest_GeneratorTestCode> > (make_shared< DataHandling::Store_SQLite_UnitTest_GeneratorTestCode >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_UnitTest_GeneratorTestCode> >();
#endif
}


} // namespace DataHandling
} // namespace UnitTest
} // namespace ConnectedVision