/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#ifndef ConnectedVisionInputPinData_code
#define ConnectedVisionInputPinData_code

#include <IConnectedVisionModule.h>
#include "ConnectedVisionInputPin.h"
#include "HTTP/HTTPXClient.h"

#include "helper.h"

#include <string>

namespace ConnectedVision {

template <class TDataObject>
ConnectedVisionInputPinData<TDataObject>::ConnectedVisionInputPinData(IModuleEnvironment *env, const pinID_t inputPinID)  
	: ConnectedVisionInputPinControl(env, inputPinID)
{
	pDataSource.reset();

	pDataSource_REST.reset(new DataSource_REST_BaseClass<TDataObject>());
	pDataSource_Memory.reset(new DataSource_Memory_BaseClass<TDataObject>());
}


template <class TDataObject>
ConnectedVisionInputPinData<TDataObject>::~ConnectedVisionInputPinData(void)
{
}

template <class TDataObject>
void ConnectedVisionInputPinData<TDataObject>::update()
{
	// call parent update
	ConnectedVisionInputPinControl::update();

	std::string uri = *config.getconst_moduleURI();
	std::string configID = config.getconst_id();
 	std::string protocol;
	std::string name;
	parseURI(uri, protocol, name);

	
	std::string moduleID = *config.getconst_moduleURI();

	// reduce module URI to a string that just contains the moduleID
	size_t found = std::string::npos;
	do
	{
		found = moduleID.find_last_of("/");
		if (found != std::string::npos)
		{
			if (found == moduleID.length()-1) // if slash was just at the end of the string repeat to find slash that is separating the host URI from the module identifier
			{
				moduleID = moduleID.substr(0, found); // replace old tmpURI string with string containing everything before the slash
			}
			else
			{
				moduleID = moduleID.substr(found+1, std::string::npos); // replace old tmpURI string with string containing everything after the slash - which should be the moduleID now
				break;
			}
		}
		else
		{
			throw ConnectedVision::runtime_error("ill-formated module URI detected"); // no slash found although it is expected
		}
	}
	while (true);	

	if ((uri.compare("")!=0)&&(configID.compare("")!=0))
	{
		pDataSource_REST->init(uri, configID, outputPinID);
		pDataSource_Memory->init(env, moduleID, configID, outputPinID);

		pDataSource = this->getDataSource();
	}
}

template <class TDataObject>
boost::shared_ptr<IDataSource<TDataObject>> ConnectedVisionInputPinData<TDataObject>::getDataSource()
{
	std::string tmpURI = *config.getconst_moduleURI();

	// reduce module URI to a string that just contains the host URI
	size_t found = std::string::npos;
	do
	{
		found = tmpURI.find_last_of("/");
		if (found != std::string::npos)
		{
			tmpURI = tmpURI.substr(0, found); // replace old tmpURI string with string containing everything before the slash
		}
		else
		{
			throw ConnectedVision::runtime_error("ill-formated module URI detected"); // no slash found although it is expected
		}
	}
	while (found == tmpURI.length()-1); // if slash was just at the end of the string repeat to find slash that is separating the host URI from the module identifier

	std::stringstream restURL;
	restURL << tmpURI << "/_hostStatus_";
	
	ConnectedVision::HTTP::HTTPClientRequest request;
	request.setUri(restURL.str());
	request.setMethod(ConnectedVision::HTTP::HTTP_Method_GET);
	
	ConnectedVision::HTTP::HTTPResponse response;

	ConnectedVision::HTTP::HTTPXClient::performHttpxRequest(request, response);

	ConnectedVision::HTTP::EnumHTTPStatus code = response.status;
	if ( ( code != ConnectedVision::HTTP::HTTP_Status_OK ) && ( code != ConnectedVision::HTTP::HTTP_Status_NOT_FOUND ) )
	{
		throw ConnectedVision::runtime_error( response.content.getContentConst() );
	}

	Class_HostStatus hostStatusConnectedModule;

	hostStatusConnectedModule.parseJson(response.content.getContentConst());

	boost::shared_ptr<IDataSource<TDataObject>> pDataSource;

	if (env->getHostStatus().getconst_hostID().compare(hostStatusConnectedModule.getconst_hostID())==0)
	{
		pDataSource = pDataSource_Memory;
	}
	else
	{
		pDataSource = pDataSource_REST;
	}

	return(pDataSource);
}

template <class TDataObject>
boost::shared_ptr<TDataObject> ConnectedVisionInputPinData<TDataObject>::getByID(const id_t id)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getByID(id);
}

template <class TDataObject>
boost::shared_ptr<TDataObject> ConnectedVisionInputPinData<TDataObject>::getByIndex(const int64_t index)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getByIndex(index);
}

template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > ConnectedVisionInputPinData<TDataObject>::getByIndexRange(const int64_t start, const int64_t end)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getByIndexRange(start, end);
}

template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > ConnectedVisionInputPinData<TDataObject>::getByTimestamp(const timestamp_t timestamp)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getByTimestamp(timestamp);
}

template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > ConnectedVisionInputPinData<TDataObject>::getBeforeTimestamp(const timestamp_t timestamp)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getBeforeTimestamp(timestamp);
}

template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > ConnectedVisionInputPinData<TDataObject>::getAfterTimestamp(const timestamp_t timestamp)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getAfterTimestamp(timestamp);
}

template <class TDataObject>
std::vector< boost::shared_ptr<TDataObject> > ConnectedVisionInputPinData<TDataObject>::getAllInTimespan(const timestamp_t start, const timestamp_t end)
{
	if ( !pDataSource )
		throw ConnectedVision::runtime_error("ConnectedVisionInputPinData: no valid data pDataSource");

	return pDataSource->getAllInTimespan(start, end);
}

} // namespace ConnectedVision

#endif // ConnectedVisionInputPinData_code