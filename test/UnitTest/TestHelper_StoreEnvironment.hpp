/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef TestHelper_StoreEnvironment_def
#define TestHelper_StoreEnvironment_def

namespace ConnectedVision 
{ namespace DataHandling
{

template <class TDataClass>
class StoreEnvironment
{
public:
	id_t configID;
	id_t prefixID;
	timestamp_t startTime;
	timestamp_t endTime;
	int initSize;

	StoreEnvironment() :
		configID("TestConfigID"),
		prefixID("id"),
		startTime(123450),
		endTime(0),
		initSize(10)
	{}
	virtual ~StoreEnvironment() {}

	virtual shared_ptr<TDataClass> makeData(const int idx, timestamp_t time = -1, id_t configID = ID_NULL)
	{
		if ( time < 0 )
			time = this->startTime;
		if ( configID == ID_NULL )
			configID = this->configID;

		shared_ptr<TDataClass> data = ConnectedVision::make_shared<TDataClass>();
		data->set_configID(configID);
		data->set_id( prefixID + intToStr(idx));
		data->set_timestamp(time);

		return data;
	}

	virtual shared_ptr<const TDataClass> makeConstData(const int idx, timestamp_t time = -1, const id_t& configID = ID_NULL)
	{
		if ( time < 0 )
			time = this->startTime;

		shared_ptr<const TDataClass> data = boost::const_pointer_cast<const TDataClass>(makeData(idx, time, configID));
		return data;
	}

	virtual std::vector< shared_ptr<const TDataClass> > fillStoreWithData(IStore_ReadWrite<TDataClass>& store, size_t len, const id_t& configID = ID_NULL)
	{
		std::vector< shared_ptr<const TDataClass> > list;
		shared_ptr<const TDataClass> data;

		// add elements
		for (int i = 0; i < (int)len; i++ )
		{
			this->endTime = this->startTime + i*10;
			data = makeConstData(i, this->endTime, configID);
			store.save_const(data);
			list.push_back(data);
		}

		return list;
	}
};

}} // namespace scope

#endif // TestHelper_StoreEnvironment_def