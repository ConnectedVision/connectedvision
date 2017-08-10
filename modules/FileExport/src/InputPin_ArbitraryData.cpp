/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

/******************************************************
** InputPin_ArbitraryData.cpp
**
** written by Michael Rauter
** 
*******************************************************/

#include "InputPin_ArbitraryData.h"

#include <boost/lexical_cast.hpp>

// template include guard
#ifndef InputPin_ArbitraryData_def
#define InputPin_ArbitraryData_def

namespace ConnectedVision {
namespace Module {
namespace FileExport {

//using namespace std;

FileExportModule::InputPin_ArbitraryData::InputPin_ArbitraryData(IModuleEnvironment *env, const pinID_t& inputPinID, FileExportModule* pModule) : ConnectedVisionInputPinData(env, inputPinID)
{ 
	this->pModule = pModule;
	this->config.clear();
}



FileExportModule::InputPin_ArbitraryData::~InputPin_ArbitraryData(void)
{

}

} // namespace FileExport
} // namespace Module
} // namespace ConnectedVision

#endif // InputPin_ArbitraryData_def