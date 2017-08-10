/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// template include guard
#ifndef Store_Null_code
#define Store_Null_code

#include "Store_Null.h"

namespace ConnectedVision {
namespace DataHandling {

template<class TDataClass>
shared_ptr<TDataClass> Store_Null<TDataClass>::create()
{
	return make_shared<TDataClass>();
}

template<class TDataClass>
shared_ptr<const TDataClass> Store_Null<TDataClass>::make_const(shared_ptr<TDataClass>& data) const
{
	return make_shared<const TDataClass>();
}
		
template<class TDataClass>
void Store_Null<TDataClass>::initiateRelease(shared_ptr<const TDataClass>& dataConst)
{
}

template<class TDataClass>
DataRange Store_Null<TDataClass>::getDataRange() const
{
	return DataRange();
}

template<class TDataClass>
const id_t& Store_Null<TDataClass>::getConfigID() const
{
	return ID_NULL;
}

template<class TDataClass>
shared_ptr<const TDataClass> Store_Null<TDataClass>::getByID(const id_t& id)
{
	return make_shared<const TDataClass>();
}

template<class TDataClass>
shared_ptr<const TDataClass> Store_Null<TDataClass>::getByIndex(const int64_t index)
{
	return make_shared<const TDataClass>();
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Null<TDataClass>::getByIndexRange(const int64_t start,	const int64_t end)
{
	return std::vector< shared_ptr<const TDataClass> >();
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Null<TDataClass>::getByTimestamp(const timestamp_t timestamp)
{
	return std::vector< shared_ptr<const TDataClass> >();
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Null<TDataClass>::getBeforeTimestamp(const timestamp_t timestamp)
{
	return std::vector< shared_ptr<const TDataClass> >();
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Null<TDataClass>::getAfterTimestamp(const timestamp_t timestamp)
{
	return std::vector< shared_ptr<const TDataClass> >();
}

template<class TDataClass>
std::vector< shared_ptr<const TDataClass> > Store_Null<TDataClass>::getAllInTimespan(const timestamp_t start, const timestamp_t end)
{
	return std::vector< shared_ptr<const TDataClass> >();
}

template<class TDataClass>
std::vector<id_t> Store_Null<TDataClass>::getIDList()
{
	return std::vector< id_t> ();
}

template<class TDataClass>
id_t Store_Null<TDataClass>::save_const(const shared_ptr<const TDataClass>& data)
{
	return ID_NULL;
}

template<class TDataClass>
std::vector<id_t> Store_Null<TDataClass>::save_constVector(const std::vector< shared_ptr<const TDataClass> >& dataList)
{
	return std::vector< id_t >();
}

template<class TDataClass>
void Store_Null<TDataClass>::deleteAll()
{
}

template<class TDataClass>
void Store_Null<TDataClass>::deleteByID (const id_t& id)
{
}


}} // namespace scope
#endif // Store_Null_code