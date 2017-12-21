/**
* Connected Vision - https://github.com/ConnectedVision
* MIT License
*/

#include "Exception_CallStack.h"

// init global flag
bool ConnectedVision::ErrorHandling::Exception_BaseClass_CallStack::printToStdOut = false;
#ifdef DEBUG
	bool ConnectedVision::ErrorHandling::Exception_BaseClass_CallStack::callStackEnabled = true;
#else
	bool ConnectedVision::ErrorHandling::Exception_BaseClass_CallStack::callStackEnabled = false;
#endif
