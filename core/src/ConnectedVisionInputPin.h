/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

// include guard
#ifndef ConnectedVisionInputPin_def
#define ConnectedVisionInputPin_def

#include "Module/Control/Class_generic_config.h"
#include "Module/Control/Class_generic_status.h"

#include <IStoreCV.h>

#include <IModuleSource.h>
#include "ModuleSource_REST_BaseClass.h"
#include "ModuleSource_Memory_BaseClass.h"

#include <IDataSource.h>
#include "DataSource_REST_BaseClass.h"
#include "DataSource_Memory_BaseClass.h"

#include <IModuleEnvironment.h>

namespace ConnectedVision
{

class NotFound_exception: public ::ConnectedVision::runtime_error
{
public:
	NotFound_exception(const std::string& msg) : ::ConnectedVision::runtime_error(msg) {};
};

/**
 *
 */
class ConnectedVisionInputPinControl : public IConnectedVisionInputPin
{
public:
	ConnectedVisionInputPinControl(IModuleEnvironment *env, const pinID_t& inputPinID);
	virtual ~ConnectedVisionInputPinControl();

	using IConnectedVisionInputPin::init;
	virtual void init(const id_t parentConfigID, const std::string& configStr, const pinID_t& outputPinID);

	virtual pinID_t getInputPinID() const;
	virtual pinID_t getOutputPinID() const;

	virtual id_t getID();

	using IConnectedVisionInputPin::getConfig;
	virtual Class_generic_config getConfig();
	using IConnectedVisionInputPin::setConfig;
	virtual Class_generic_config setConfig();
	using IConnectedVisionInputPin::deleteConfig;
	virtual Class_generic_config deleteConfig();

	using IConnectedVisionInputPin::getStatus;
	virtual Class_generic_status getStatus();
	using IConnectedVisionInputPin::getStableResults;
	virtual Class_generic_status_stableResults getStableResults();

	virtual Class_generic_status& start();
	virtual Class_generic_status& stop();
	virtual Class_generic_status& reset();
	virtual Class_generic_status& recover();

	virtual Class_generic_status& notifyStop();

protected:
	virtual Class_generic_status& control(std::string command);
	virtual void update();

	IModuleEnvironment *env;
	pinID_t inputPinID;
	pinID_t outputPinID;

	id_t parentConfigID;

	Class_generic_config config;
	Class_generic_status status;

	boost::shared_ptr<IModuleSource> getModuleSource();
	boost::shared_ptr<IModuleSource> pModuleSource;

	boost::shared_ptr<ModuleSource_Memory_BaseClass> pModuleSource_Memory;
	boost::shared_ptr<ModuleSource_REST_BaseClass> pModuleSource_REST;
};

/**
 *
 */
template <class TDataObject>
class ConnectedVisionInputPinData : public ConnectedVisionInputPinControl
{
public:
	ConnectedVisionInputPinData(IModuleEnvironment *env, const pinID_t inputPinID);
	virtual ~ConnectedVisionInputPinData();

	virtual boost::shared_ptr<TDataObject> getByID(const id_t id);
	virtual boost::shared_ptr<TDataObject> getByIndex(const int64_t index);
	virtual std::vector< boost::shared_ptr<TDataObject> > getByIndexRange(const int64_t start, const int64_t end);
	virtual std::vector< boost::shared_ptr<TDataObject> > getByTimestamp(const timestamp_t timestamp);
	virtual std::vector< boost::shared_ptr<TDataObject> > getBeforeTimestamp(const timestamp_t timestamp);
	virtual std::vector< boost::shared_ptr<TDataObject> > getAfterTimestamp(const timestamp_t timestamp);
	virtual std::vector< boost::shared_ptr<TDataObject> > getAllInTimespan(const timestamp_t start, const timestamp_t end);

protected:
	virtual void update();

	boost::shared_ptr<IDataSource<TDataObject>> getDataSource();
	boost::shared_ptr<IDataSource<TDataObject>> pDataSource;

	boost::shared_ptr<DataSource_Memory_BaseClass<TDataObject>> pDataSource_Memory;
	boost::shared_ptr<DataSource_REST_BaseClass<TDataObject>> pDataSource_REST;
};

} // namespace ConnectedVision

#endif // ConnectedVisionInputPin_def

// include source code: template inclusion model
#include "ConnectedVisionInputPinData.cpp"
