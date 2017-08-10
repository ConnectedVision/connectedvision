var path = require("path");
var expect = require("chai").expect;

/**
*	dummy comparison function
*/
exports.compareOK = function(
		dataCurrent,		///< The current data.  
		dataReference, 		///< The reference data.
		url, 				///< The source of the data (output pin URL).
		pinID, 				///< The ID of the pin
		pinType, 			///< The pin type, e.g. "application/json".
		compareParams		///< additional compare parameter object 	
) {
	return true;
}