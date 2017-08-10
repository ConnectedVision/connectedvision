/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include <general.h>
#include <helper.h>
#include "./Class_generic_config_chain.h"

using namespace std;
using namespace ConnectedVision;

pinID_t Class_generic_config_chain::getCorrespondingOutputPinID(const pinID_t& pinID) const
{
	pinID_t pinIdIndexed = getIndexedPinID(pinID);

	const auto& connections = this->getconst_connections();
	
	// loop through all connections to find the corresponding pin
	for(auto it = connections->begin(); it != connections->end(); ++it)
	{
		pinID_t connectionInputPinID = *((*it)->get_inputPinID());
		pinID_t connectionInputPinIdIndexed = getIndexedPinID(connectionInputPinID);

		if(connectionInputPinIdIndexed == pinIdIndexed)
		{
			return *(*it)->get_outputPinID();
		}
	}

	return pinID_t();
}
