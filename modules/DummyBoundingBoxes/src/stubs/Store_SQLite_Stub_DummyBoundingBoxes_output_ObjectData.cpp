// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: 0.3 alpha
// stubs/Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.cpp
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "../Store_SQLite_DummyBoundingBoxes_output_ObjectData.h"

#include "Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData.h"

// --> Do NOT EDIT <--
namespace ConnectedVision {
namespace Module {
namespace DummyBoundingBoxes {
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "DummyBoundingBoxes_output_ObjectData";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
	("'_sortID' BIGINT NOT NULL DEFAULT '0' /* object sortable id () */")
	("'configID' VARCHAR(32) NOT NULL DEFAULT '' /* ID of config chain (string) */")
	("'id' VARCHAR(32) NOT NULL DEFAULT '' /* object ID (string) */")
	("'timestamp' BIGINT NOT NULL DEFAULT '0' /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */")
	("'objectID' VARCHAR(32) NOT NULL DEFAULT '' /* object ID (string) */")
	("'detections._idx1' BIGINT /* array index dimension: 1 (array) */")
	("'detections.timestamp' BIGINT /* timestamp in milliseconds since 1970-01-01 00:00:00.000 UTC (integer) */")
	("'detections.confidence' DOUBLE DEFAULT '1' /* confidence of detection [0-1] (number) */")
	("'detections.boundingBox.left' DOUBLE /* x position of top left point of the rectangle (number) */")
	("'detections.boundingBox.right' DOUBLE /* x position of bottom right point of the rectangle (number) */")
	("'detections.boundingBox.top' DOUBLE /* y position of top left point of the rectangle (number) */")
	("'detections.boundingBox.bottom' DOUBLE /* y position of bottom right point of the rectangle (number) */")
	("'detections.basePoint.x' DOUBLE /* x position of point (number) */")
	("'detections.basePoint.y' DOUBLE /* y position of point (number) */")
;

// --> Do NOT EDIT <--
Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<Class_DummyBoundingBoxes_output_ObjectData>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::~Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData()
{
}

#ifdef ENABLE_SQLITE_SEARCH
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by configID
 */
std::vector<shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData> > Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::getBy_configID(const ConnectedVision::id_t& val)
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
std::vector<shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData> > Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::getBy_id(const ConnectedVision::id_t& val)
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
std::vector<shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData> > Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::getBy_timestamp(const ConnectedVision::timestamp_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("timestamp", Store::Op::EQUAL, val) );
	return getByFilter(filterList, sortList);
}

// --> Do NOT EDIT <--
/**
 *  Get objects filtered by objectID
 */
std::vector<shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData> > Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::getBy_objectID(const ConnectedVision::id_t& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
	filterList.push_back( Store::FilterEntry("objectID", Store::Op::EQUAL, IDToStr(val) ) );
	return getByFilter(filterList, sortList);
}

#endif

// --> Do NOT EDIT <--
int Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::readObject(sqlite3_stmt *stmt, shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

	int64_t objSortID = sqlite3_column_int64(stmt, 0);
	int64_t sortID = objSortID;
	outObj.reset( new Class_DummyBoundingBoxes_output_ObjectData() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
		// process row
			// DummyBoundingBoxes_output_ObjectData_configID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 1) != SQLITE_NULL )
  				obj->set_configID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,1) ) ) );
			// DummyBoundingBoxes_output_ObjectData_id -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 2) != SQLITE_NULL )
  				obj->set_id( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,2) ) ) );
			// DummyBoundingBoxes_output_ObjectData_timestamp -> ConnectedVision::timestamp_t
  			if ( sqlite3_column_type(stmt, 3) != SQLITE_NULL )
  				obj->set_timestamp( sqlite3_column_int64(stmt,3) );
			// DummyBoundingBoxes_output_ObjectData_objectID -> ConnectedVision::id_t
  			if ( sqlite3_column_type(stmt, 4) != SQLITE_NULL )
  				obj->set_objectID( strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,4) ) ) );
			// DummyBoundingBoxes_output_ObjectData_detections -> std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>
  			if ( sqlite3_column_type(stmt, 5) != SQLITE_NULL )
  			{
  				boost::shared_ptr<std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>>>&& a1 = obj->get_detections(); // rvalue reference for const functions
  				if ( !a1 ) a1.reset( new std::vector<boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>> );
  				size_t idx1 = static_cast<size_t>( sqlite3_column_int64(stmt,5) );
  				if ( idx1 >= a1->size() ) a1->resize( idx1 +1 );
				// DummyBoundingBoxes_output_ObjectData_detections -> Class_DummyBoundingBoxes_output_ObjectData_detections
  				{
  					boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections>& o2 = a1->at(idx1); // lvalue reference for non-const functions like vector::at()
  					if ( !o2 ) o2.reset( new Class_DummyBoundingBoxes_output_ObjectData_detections );
					// DummyBoundingBoxes_output_ObjectData_detections_timestamp -> ConnectedVision::timestamp_t
  					if ( sqlite3_column_type(stmt, 6) != SQLITE_NULL )
  						o2->set_timestamp( sqlite3_column_int64(stmt,6) );
					// DummyBoundingBoxes_output_ObjectData_detections_confidence -> double
  					if ( sqlite3_column_type(stmt, 7) != SQLITE_NULL )
  						o2->set_confidence( sqlite3_column_double(stmt,7) );
					// DummyBoundingBoxes_output_ObjectData_detections_boundingBox -> Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox
  					{
  						boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox>&& o3 = o2->get_boundingBox(); // rvalue reference for const functions
  						if ( !o3 ) o3.reset( new Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox );
						// DummyBoundingBoxes_output_ObjectData_detections_boundingBox_left -> double
  						if ( sqlite3_column_type(stmt, 8) != SQLITE_NULL )
  							o3->set_left( sqlite3_column_double(stmt,8) );
						// DummyBoundingBoxes_output_ObjectData_detections_boundingBox_right -> double
  						if ( sqlite3_column_type(stmt, 9) != SQLITE_NULL )
  							o3->set_right( sqlite3_column_double(stmt,9) );
						// DummyBoundingBoxes_output_ObjectData_detections_boundingBox_top -> double
  						if ( sqlite3_column_type(stmt, 10) != SQLITE_NULL )
  							o3->set_top( sqlite3_column_double(stmt,10) );
						// DummyBoundingBoxes_output_ObjectData_detections_boundingBox_bottom -> double
  						if ( sqlite3_column_type(stmt, 11) != SQLITE_NULL )
  							o3->set_bottom( sqlite3_column_double(stmt,11) );
  					}
					// DummyBoundingBoxes_output_ObjectData_detections_basePoint -> Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint
  					{
  						boost::shared_ptr<Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint>&& o3 = o2->get_basePoint(); // rvalue reference for const functions
  						if ( !o3 ) o3.reset( new Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint );
						// DummyBoundingBoxes_output_ObjectData_detections_basePoint_x -> double
  						if ( sqlite3_column_type(stmt, 12) != SQLITE_NULL )
  							o3->set_x( sqlite3_column_double(stmt,12) );
						// DummyBoundingBoxes_output_ObjectData_detections_basePoint_y -> double
  						if ( sqlite3_column_type(stmt, 13) != SQLITE_NULL )
  							o3->set_y( sqlite3_column_double(stmt,13) );
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
int Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::writeObject(sqlite3_stmt *stmt, const shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;


		size_t i1_max = 1;
		if ( i1_max < obj->getconst_detections()->size() )
			i1_max = obj->getconst_detections()->size();
	for ( size_t i1 = 0; i1 < i1_max; i1++ )
	{
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);

		bind_DummyBoundingBoxes_output_ObjectData( stmt, obj, sortID );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_detections()->size() )
		bind_detections( stmt, obj->getconst_detections()->at(i1), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_detections()->size() )
		bind_detections_boundingBox( stmt, obj->getconst_detections()->at(i1)->getconst_boundingBox(), sortID, i1 );
		// enforce left-to-right evaluation
		if ( i1 < obj->getconst_detections()->size() )
		bind_detections_basePoint( stmt, obj->getconst_detections()->at(i1)->getconst_basePoint(), sortID, i1 );
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
	}
	return error;
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::bind_DummyBoundingBoxes_output_ObjectData(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData>& obj, const int64_t sortID) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_text(stmt, 2, IDToChar(obj->getconst_configID()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_text(stmt, 3, IDToChar(obj->getconst_id()), -1, SQLITE_TRANSIENT);
	sqlite3_bind_int64(stmt, 4, obj->getconst_timestamp() );
	sqlite3_bind_text(stmt, 5, IDToChar(obj->getconst_objectID()), -1, SQLITE_TRANSIENT);
  	// array: detections handled separately
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::bind_detections(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 6, idx1 );
	sqlite3_bind_int64(stmt, 7, obj->getconst_timestamp() );
  	sqlite3_bind_double(stmt, 8, obj->getconst_confidence() );
	// object: boundingBox handled separately
	// object: basePoint handled separately
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::bind_detections_boundingBox(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections_boundingBox>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 6, idx1 );
  	sqlite3_bind_double(stmt, 9, obj->getconst_left() );
  	sqlite3_bind_double(stmt, 10, obj->getconst_right() );
  	sqlite3_bind_double(stmt, 11, obj->getconst_top() );
  	sqlite3_bind_double(stmt, 12, obj->getconst_bottom() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::bind_detections_basePoint(sqlite3_stmt *stmt, const boost::shared_ptr<const Class_DummyBoundingBoxes_output_ObjectData_detections_basePoint>& obj, const int64_t sortID, const int64_t idx1) const
{
	sqlite3_bind_int64(stmt, 1, sortID );
	sqlite3_bind_int64(stmt, 6, idx1 );
  	sqlite3_bind_double(stmt, 13, obj->getconst_x() );
  	sqlite3_bind_double(stmt, 14, obj->getconst_y() );
}

// --> Do NOT EDIT <--
void Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("_sortID", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string Store_SQLite_Stub_DummyBoundingBoxes_output_ObjectData::objectKey() const
{
	return std::string("_sortID");
}


//////////////////////////////////////////////////////////////////////////////
//
// Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData::Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData::~Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_DummyBoundingBoxes_output_ObjectData> > Store_SQLite_Factory_Stub_DummyBoundingBoxes_output_ObjectData::create(const id_t configID = ID_NULL)
{
#ifdef Store_SQLite_Factory_DummyBoundingBoxes_output_ObjectData_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<Class_DummyBoundingBoxes_output_ObjectData> > (make_shared< DataHandling::Store_SQLite_DummyBoundingBoxes_output_ObjectData >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<Class_DummyBoundingBoxes_output_ObjectData> >();
#endif
}


} // namespace DataHandling
} // namespace DummyBoundingBoxes
} // namespace Module
} // namespace ConnectedVision