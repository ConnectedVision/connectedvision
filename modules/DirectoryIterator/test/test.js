/**
* Executes a custom module output data comparison for FileMetadata output pin.
*
* @param dataCurrent The current data.
* @param dataReference The referece data.
* @param url The address of the data source.
* @param pin The module output pin description data structure.
*/
exports.compareFileMetadata = function(dataCurrent, dataReference, url, pin)
{
	var path = require("path");
	var tools = require(path.join(process.cwd(), "Tools.js"));
	
	tools.compareData(dataCurrent, dataReference, url, pin.id, pin.type, { "excludedProperties": { "timestamp": true } });
};