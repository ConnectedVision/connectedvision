/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "InputPin_PNG.h"

namespace ConnectedVision {

InputPin_PNG::InputPin_PNG(IModuleEnvironment *env, pinID_t inputPinID)  
	: ConnectedVisionInputPinData(env, inputPinID)
{
}



InputPin_PNG::~InputPin_PNG(void)
{
}

/*
boost::shared_ptr<std::string> InputPin_PNG::getByID(const id_t id)
{	
	boost::shared_ptr<std::string> data;
	string uri = *this->config.get_moduleURI();
 	string protocol, name;
	parseURI(uri, protocol, name);

	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{
		// web service
		
		string restURI;
		restURI = uri + "/" + this->config.get_id() + "/" + this->outputPinID + "/id/" + id;
		this->http.reset();
		this->http.setURL( restURI );
		this->http.sendRequestRetry();

		if ( this->http.getHeader("Content-Type").compare("image/png") != 0 )
		{
			throw ConnectedVision::runtime_error("InputPin_PNG: unknown content: " + this->http.getHeader("Content-Type") );
		}

		data = boost::shared_ptr<string>( new string(this->http.getBody()) );

	}
	else
	{
		throw ConnectedVision::runtime_error("InputPin_PNG: unsupported protocol: " + *this->config.get_moduleURI());
	}

	return data;	
}


boost::shared_ptr<std::string> InputPin_PNG::getByIndex(const int64_t index)
{
	boost::shared_ptr<std::string> data;
	string uri = *this->config.get_moduleURI();
 	string protocol, name;
	parseURI(uri, protocol, name);

	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{
		// web service
		
		string restURI;
		restURI = uri + "/" + this->config.get_id() + "/" + this->outputPinID + "/index/" + intToStr( index );
		this->http.reset();
		this->http.setURL( restURI );
		this->http.sendRequestRetry();

		if ( this->http.getHeader("Content-Type").compare("image/png") != 0 )
		{
			throw ConnectedVision::runtime_error("InputPin_PNG: unknown content: " + this->http.getHeader("Content-Type") );
		}

		data = boost::shared_ptr<string>( new string(this->http.getBody()) );

	}
	else
	{
		throw ConnectedVision::runtime_error("InputPin_PNG: unsupported protocol: " + *this->config.get_moduleURI());
	}

	return data;
}


boost::shared_ptr<std::string> InputPin_PNG::getByTimestamp(const timestamp_t timestamp)
{
	boost::shared_ptr<std::string> data;
	string uri = *this->config.get_moduleURI();
 	string protocol, name;
	parseURI(uri, protocol, name);

	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{
		// web service
		
		string restURI;
		restURI = uri + "/" + this->config.get_id() + "/" + this->outputPinID + "/time/" + intToStr( timestamp );
		this->http.reset();
		this->http.setURL( restURI );
		this->http.sendRequestRetry();

		if ( this->http.getHeader("Content-Type").compare("image/png") != 0 )
		{
			throw ConnectedVision::runtime_error("InputPin_PNG: unknown content: " + this->http.getHeader("Content-Type") );
		}

		data = boost::shared_ptr<string>( new string(this->http.getBody()) );

	}
	else
	{
		throw ConnectedVision::runtime_error("InputPin_PNG: unsupported protocol: " + *this->config.get_moduleURI());
	}

	return data;
}


boost::shared_ptr<std::string> InputPin_PNG::getBeforeTimestamp(const timestamp_t timestamp)
{
	boost::shared_ptr<std::string> data;
	string uri = *this->config.get_moduleURI();
 	string protocol, name;
	parseURI(uri, protocol, name);

	if ( protocol.compare("http") == 0 || protocol.compare("https") == 0 )
	{
		// web service
		
		string restURI;
		restURI = uri + "/" + this->config.get_id() + "/" + this->outputPinID + "/beforetime/" + intToStr( timestamp );
		this->http.reset();
		this->http.setURL( restURI );
		this->http.sendRequestRetry();

		data = boost::shared_ptr<string>( new string(this->http.getBody()) );
		if ( this->http.getHeader("Content-Type") != "image/png" || data->empty() )
		{
			throw ConnectedVision::runtime_error("InputPin_PNG: unknown content: " + this->http.getHeader("Content-Type") );
		}


	}
	else
	{
		throw ConnectedVision::runtime_error("InputPin_PNG: unsupported protocol: " + *this->config.get_moduleURI());
	}

	return data;
}


boost::shared_ptr<std::string> InputPin_PNG::getAfterTimestamp(const timestamp_t timestamp)
{
	boost::shared_ptr<std::string> data;
	string uri = *this->config.get_moduleURI();
 	string protocol, name;
	parseURI(uri, protocol, name);

	if ( protocol.compare("http") == 0 || protocol.compare("https") != 0 )
	{
		// web service
		
		string restURI;
		restURI = uri + "/" + this->config.get_id() + "/" + this->outputPinID + "/aftertime/" + intToStr( timestamp );
		this->http.reset();
		this->http.setURL( restURI );
		this->http.sendRequestRetry();

		data = boost::shared_ptr<string>( new string(this->http.getBody()) );
		if ( this->http.getHeader("Content-Type") != "image/png" || data->empty() )
		{
			throw ConnectedVision::runtime_error("InputPin_PNG: unknown content: " + this->http.getHeader("Content-Type") );
		}
	}
	else
	{
		throw ConnectedVision::runtime_error("InputPin_PNG: unsupported protocol: " + *this->config.get_moduleURI());
	}

	return data;
}
*/

} // namespace ConnectedVision