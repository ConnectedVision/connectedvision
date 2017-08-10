/**
* The structure of the modules object which is used and consecutively extented throughout many of the different steps within the entire test suite eventually will have the following structure:
* {
*	<module_name>:
*	{
*		"dir": <module_directory_path>,
*		"outputDescription": <output_description>,
*		"configs":
*		[
*			{
*				"file": <file_path>,
*				"config": <config>,
*				"result": <result>,
*				"output":
*				{
*					<pin_ID>:
*					{
*						"dataGenerationFlag": <data_generation_flag>,
*						"recentAccessorDir": <recent_data_accessor_dir>,
*						"referenceAccessorDir": <reference_data_accessor_dir>
*					}, ...
*				},
*				"benchmarks":
*				{
*					"status": <status>,
*					"output":
*					{
*						<pin_ID>:
*						{
*							"index": [],
*							"timestamp": []
*						}, ...
*					}
*				}
*			}, ...
*		],
*		"customTests":
*		{
*			"<functionA>": {<function_A_body>},
*			"<functionB>": {<function_B_body>},
*			...
*		}
*	}, ...
* }
*/



/**
* Benchmarks the average duration of ouput pin data queries.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.benchmarkOutputPinRequests = function(modules, serverUrl, nRequests, callback)
{
	var async = require("async");
	var expect = require("chai").expect;
	var path = require("path");
	var request = require("request");
	
	benchmarkPins(modules, nRequests);

	function benchmarkPins(modules, nRequests)
	{
		var requests = [];
		
		var moduleId = Object.keys(modules)[0];
		
		// iterate over all output pins
		modules[moduleId].outputDescription.forEach(function(pin, iPin)
		{
			for(var i = 0; i < nRequests; i++)
			{
				// get by index
				requests.push(function(asyncCallback)
				{
					queryData(moduleId, pin, "index", asyncCallback);
				});
				
				// // <todo> benchmark using timestamp as accessor when Connected Vision framework supports timestamp list output
				// // get after timestamp
				// requests.push(function(asyncCallback)
				// {
					// queryData(moduleId, pin, "aftertime", asyncCallback);
				// });
			}
		});
		
		async.series(requests, function(error, result)
		{
			expect(error, "async error: " + error).to.be.null;
			
			computAverageDuration();
		});
	}
	
	function queryData(moduleId, pin, accessor, queryDataCallback)
	{
		var config = modules[moduleId].configs[0];
		var results = getStableResultsInfoForPin(config.result.stableResults, pin.id);

		var accessorValue = "";
		
		if(accessor === "index")
		{
			// select a random index
			accessorValue = results.indexStart + Math.floor(Math.random() * (results.indexEnd - results.indexStart));
		}
		else if(accessor === "timestamp")
		{
			// select random timestamp
			accessorValue = results.timestampStart + Math.floor(Math.random() * (results.timestampEnd - results.timestampStart));
		}
		else
		{
			expect(true, "queryData() invalid value for accessor: " + accessor).to.be.false;
		}
		
		var url = moduleId + "/" + config.config.id + "/" + pin.id + "/" + accessor + "/" + accessorValue;
		
		var startTime = process.hrtime();
		
		// log the duration of the request for the current module, config and pin
		request(serverUrl + "/" + url, function(error, result, body)
		{
			var duration = process.hrtime(startTime);
			
			expect(error, "benchmarkOutputPinRequests::queryData::request() url: " + url + " error: " + error).to.be.null;
			expect(body.status, "benchmarkOutputPinRequests::queryData::request() url: " + url + " message: " + body.error).not.to.equal(404);
			
			if(!modules[moduleId].configs[0].hasOwnProperty("benchmarks"))
			{
				modules[moduleId].configs[0].benchmarks = {};
			}

			if(!modules[moduleId].configs[0].benchmarks.hasOwnProperty("output"))
			{
				modules[moduleId].configs[0].benchmarks.output = {};
			}

			if(!modules[moduleId].configs[0].benchmarks.output.hasOwnProperty(pin.id))
			{
				modules[moduleId].configs[0].benchmarks.output[pin.id] = {};
			}
			
			if(accessor === "index")
			{
				if(!modules[moduleId].configs[0].benchmarks.output[pin.id].hasOwnProperty("index"))
				{
					modules[moduleId].configs[0].benchmarks.output[pin.id].index = [];
				}
				
				modules[moduleId].configs[0].benchmarks.output[pin.id].index.push(duration[0] + duration[1] * 1e-9);
			}
			else if(accessor === "timestamp")
			{
				if(!modules[moduleId].configs[0].benchmarks.output[pin.id].hasOwnProperty("timestamp"))
				{
					modules[moduleId].configs[0].benchmarks.output[pin.id].timestamp = [];
				}
				
				modules[moduleId].configs[0].benchmarks.output[pin.id].timestamp.push(duration[0] + duration[1] * 1e-9);
			}
			else
			{
				expect(true, "invalid value for accessor: " + accessor).to.be.false;
			}

			queryDataCallback(null, null);
		});
	}
	
	// compute the corresponding average duration for all output pins of all modules for all configs
	function computAverageDuration(data)
	{
		var moduleId = Object.keys(modules)[0];
		var config = modules[moduleId].configs[0];
		
		// iterate over all output pins
		modules[moduleId].outputDescription.forEach(function(pin, iPin)
		{
			// iterate over all accessors
			Object.keys(config.benchmarks.output[pin.id]).forEach(function(accessor, iAccessor)
			{
				var sum = 0.0;
				
				// iterate over all duration measurements
				config.benchmarks.output[pin.id][accessor].forEach(function(duration, iDuration)
				{
					sum += duration;
				});
				
				var dirPath = path.join(config.file, "..");
				var configName = exports.shortenString(path.basename(dirPath), 10);
				var n = config.benchmarks.output[pin.id][accessor].length;
				console.log(pin.id + " " + accessor + " " + (sum / n).toFixed(4) + " sec");
			});
		});
		
		callback();
	}
};



/**
* Benchmarks the average duration of module status requests.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param nRequests The number of requests to use for computing the average duration.
* @param callback Callback function to call at the end of the function.
*/
exports.benchmarkStatusRequests = function(modules, serverUrl, nRequests, callback)
{
	var expect = require("chai").expect;

	// repeatedly query the status from the server
	queryStatus(modules);

	function queryStatus(modules)
	{
		nRequests--;
		
		if(nRequests > 0)
		{
			exports.getChainStatus(modules, serverUrl, true, 0, queryStatus);
		}
		else
		{
			exports.getChainStatus(modules, serverUrl, true, 0, recursionEndCallback);
		}
	}
	
	function recursionEndCallback(data)
	{
		var moduleId = Object.keys(modules)[0];
		var config = modules[moduleId].configs[0];
		var sum = 0.0;
		
		// iterate over all duration measurements
		config.benchmarks.status.forEach(function(duration, iDuration)
		{
			sum += duration;
		});
		
		console.log((sum / config.benchmarks.status.length).toFixed(4) + " sec");
		
		callback();
	}
};



/**
* Checks if a request returned an error.
*
* @param error The error object (should be null).
* @param body The returned data of the request.
* @param url The request URL.
* @param attempts The remaining number of retries after a failed attempt before throwing an error.
*/
function checkError(error, body, url, attempts)
{
	var expect = require("chai").expect;
	
	attempts = attempts || 0;
	
	if(error && attempts > 0)
	{
		return error;
	}
	
	var url = url || "";
	
	var message = "checkError() failed";

	if(url.size > 0)
	{
		message += "for url: " + url;
	}
	
	expect(error, message).to.be.null;
	
	// if the message body has a property status with a numerical value, then this is an indicator for an error since Connected Vision status requests have string data as status information
	if(body.hasOwnProperty("status"))
	{
		message += " " + JSON.stringify(body);
		
		if(typeof(body.status) == "number" && attempts > 0)
		{
			return body;
		}

		expect(body.status, message).not.to.be.a("number");
		
		return error;
	}
	
	return error;
}



/**
* Checks if provided status is in the list of possible/expected values.
*
* @param status The config status object (not only the status string) including the status string property.
* @param values The list of possible/expected values.
*/
function checkConfigStatus(status, values, messageSuffix)
{
	var expect = require("chai").expect;
	
	expect(status).to.have.property("status");
	
	var message = "config status is \"" + status.status + "\" (instead of [" + values + "])";
	
	if(status.hasOwnProperty("message") && message)
	{
		message += " message: " + status.message;
	}
	
	if(messageSuffix)
	{
		message += messageSuffix;
	}
	
	expect(values, message).to.include(status.status);
};



/**
* Checks if the result at index zero of all output pins with type "application/json" of all configs of all modules has all properties specified in the module output description.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.checkOutputDataTypes = function(modules, serverUrl, callback)
{
	var async = require("async");
	var expect = require("chai").expect;
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	
	exports.getChainStatus(modules, serverUrl, true, 0, getChainStatusCallback);
	
	function getChainStatusCallback()
	{
		var requests = [];
		var moduleId = Object.keys(modules)[0];
		var config = modules[moduleId].configs[0];
		
		// iterate over all output pins of the output description
		modules[moduleId].outputDescription.forEach(function(pin, iPin)
		{
			// check only JSON output pins
			if(pin.type === "application/json")
			{
				var results = getStableResultsInfoForPin(config.result.stableResults, pin.id);
				
				if(results.indexStart >= 0)
				{
					requests.push(function(asyncCallback)
					{
						var url = moduleId + "/" + config.config.id + "/" + pin.id + "/index/" + results.indexEnd;
						
						client.get(url, function(error, result, body)
						{
							checkError(error, body, url);
							
							// there may be custom output pins which provide an array of data elements, which is possibly empty
							if(JSON.stringify(body) === "[]")
							{
								console.log("skipping test for pin " + pin.id + " check because output data is an empty array possibly due to a custom pin @ " + serverUrl + "/" + url);
							}
							else
							{
								var data;
								
								if(Array.isArray(body))
								{
									data = body[0];
								}
								else
								{
									data = body;
								}
								
								recurseProperties(moduleId, pin.id, pin.properties, data);
							}
							
							asyncCallback(null, null);
						});
					});
				}
				else
				{
					console.log("skipping test for pin " + pin.id + " because no stable results exist");
				}
			}
		});
		
		async.series(requests, function(error, result)
		{
			expect(error, "async error: " + error).to.be.null;
			
			callback();
		});
	}
	
	// recursively iterates over the module description and the actual output data to check the data type of all properties
	function recurseProperties(moduleId, pinId, description, data)
	{
		// iterate over all properties of the output pin
		Object.keys(description).forEach(function(propertyName, iProperty)
		{
			var message = moduleId + " module " + pinId + " pin " + propertyName + " property";
			
			// handle objects
			if(description[propertyName].type === "object")
			{
				expect(description[propertyName], message).to.have.property("properties");
				recurseProperties(moduleId, pinId, description[propertyName].properties, data[propertyName]);
			}
			// handle arrays
			else if(description[propertyName].type === "array")
			{
				expect(description[propertyName], message).to.have.property("items");
				
				// only handle non-empty arrays
				if(data[propertyName].length > 0)
				{
					// recurse objects
					if(description[propertyName].items.hasOwnProperty("properties"))
					{
						recurseProperties(moduleId, pinId, description[propertyName].items.properties, data[propertyName][0]);
					}
					// check the first element of arrays of basic types
					else if
					(
						/* if the types are not equal */
						description[propertyName].items.type != typeof(data[propertyName][0])
						/* except for the case of integer in description and number in pin result which are supposed to be equal */
						&& !
						(
							description[propertyName].items.type === "integer"
							&& typeof(data[propertyName][0]) === "number"
						)
					)
					{
						var msg = message + " output property data types do not match";
						expect(data[propertyName][0], msg).to.be.a(description[propertyName].items.type);
					}
				}
			}
			else if
			(
				/* if the types are not equal */
				description[propertyName].type != typeof(data[propertyName])
				/* except for the case of integer in description and number in pin result which are supposed to be equal */
				&& !
				(
					description[propertyName].type === "integer"
					&& typeof(data[propertyName]) === "number"
				)
			)
			{
				var msg = message + " output property data types do not match";
				expect(data[propertyName], msg).to.be.a(description[propertyName].type);
			}
		});
	}
};



/**
* Checks if the data corresponding to the end index / timestamp of the stable the result count are accessible.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.checkResultCount = function(modules, serverUrl, callback)
{
	var async = require("async");
	var expect = require("chai").expect;
	var request = require("request");

	exports.getChainStatus(modules, serverUrl, true, 0, getChainStatusCallback);
	
	function getChainStatusCallback(modules)
	{
		expect(modules).to.be.not.null;
		
		var requests = [];
		var moduleId = Object.keys(modules)[0];
		var config = modules[moduleId].configs[0];

		// iterate over all output pins of the output description
		modules[moduleId].outputDescription.forEach(function(pin, iPin)
		{
			var results = getStableResultsInfoForPin(config.result.stableResults, pin.id);
			
			// get by index
			if(results.indexEnd >= 0)
			{
				requests.push(function(asyncCallback)
				{
					var url = moduleId + "/" + config.config.id + "/" + pin.id + "/index/" + results.indexEnd;
					
					request(serverUrl + "/" + url, function(error, result, body)
					{
						expect(error, "url: " + url).to.be.null;
						expect(body.status, "url: " + url + " message: " + body.error).not.to.equal(404);
						asyncCallback(null, null);
					});
				});
			}
			
			// get by timestamp
			if(results.timestampEnd >= 0)
			{
				requests.push(function(asyncCallback)
				{
					var url = moduleId + "/" + config.config.id + "/" + pin.id + "/timestamp/" + results.timestampEnd;
					
					request(serverUrl + "/" + url, function(error, result, body)
					{
						expect(error, "url: " + url).to.be.null;
						expect(body.status, "url: " + url + " message: " + body.error).not.to.equal(404);
						asyncCallback(null, null);
					});
				});
			}
			
			if(results.indexEnd < 0 && results.timestampEnd < 0)
			{
				console.log("skipping test for pin " + pin.id + " because no stable results exist");
			}
		});
		
		async.series(requests, function(error, result)
		{
			expect(error, "async error: " + error).to.be.null;
			
			callback();
		});
	}
};



/**
* Compares JSON or binary data (comparison method is determined by pin type).
*/
exports.compareData = function(
		dataCurrent,		///< The current data.
		dataReference, 		///< The reference data.
		url, 				///< The source of the data (output pin URL).
		pinID, 				///< The ID of the pin
		pinType, 			///< The pin type, e.g. "application/json".
		compareParams		///< additional compare parameter object
) {
	if(pinType === "application/json")
	{
		return compareJsonData(dataCurrent, dataReference, url, compareParams);
	}
	else
	{
		return compareBinaryData(dataCurrent, dataReference, url, compareParams);
	}
};



/**
* Compares JSON data
*/
function compareJsonData(
		dataCurrent,		///< The current data.
		dataReference, 		///< The reference data.
		url, 				///< The source of the data (output pin URL).
		compareParams		///< additional compare parameter object
							///	- excludedProperties: Object which has exactly the same structure as the objects to compare only for those properties
							///		which should be excluded from the comparison. (optional)
							///		E.g. suppose a is {"id": 0, "x": {"id": 1, "y": "0"}},
							///			b is {"id": 0, "x": {"id": 2, "y": "0"}}
							///			and the value of the child object x.id" property should be excluded,
							///			then excludedProperties should be {"x": {"id": true}}.
) {
	var clone = require("clone");
	var diff = require("deep-diff");
	var expect = require("chai").expect;
	var underscore = require("underscore");
	compareParams = compareParams || {};
	
	// clone the variables and point the reference to the clone (complex input arguments are passed as reference)
	dataCurrent = clone(dataCurrent);
	dataReference = clone(dataReference);

	// check if properties are supposed to be excluded from the comparison
	if(compareParams.excludedProperties)
	{
		// check if the objects to compare are arrays of objects, which need to be treaded one by one for exclusion of the properties
		if(Array.isArray(dataCurrent) || Array.isArray(dataReference))
		{
			expect(Array.isArray(dataCurrent) && Array.isArray(dataReference), "once of the elments is an array, but the other is not").to.be.true;
			
			for(var i = 0; i < dataCurrent.length; i++)
			{
				// delete the properties
				dataCurrent[i] = deleteProperties(dataCurrent[i], compareParams.excludedProperties);
				dataReference[i] = deleteProperties(dataReference[i], compareParams.excludedProperties);
			}
		}
		else
		{
			dataCurrent = deleteProperties(dataCurrent, compareParams.excludedProperties);
			dataReference = deleteProperties(dataReference, compareParams.excludedProperties);
		}
	}
	
	// compare the data
	var equalityFlag = underscore.isEqual(dataCurrent, dataReference);
	
	if(!equalityFlag)
	{
		var diffResultStr = JSON.stringify(diff(dataCurrent, dataReference));
		expect(equalityFlag, "Current data does not match reference data. URL: " + url + " diff: " + diffResultStr).to.be.true;
	}
	
	return true;
}

/**
* Compares binary data using its SHA1 hash values.
*/
function compareBinaryData(
		dataCurrent,		///< The current data.
		dataReference, 		///< The reference data.
		url 				///< The source of the data (output pin URL).
) {
	var crypto = require("crypto");
	var expect = require("chai").expect;
	
	// compute the hash of the reference data
	var hashReference = crypto.createHash("md5");
	hashReference.update(dataReference);
	var shaReference = hashReference.digest("hex");
	
	// compute the hash of the current data
	var hashCurrent = crypto.createHash("md5");
	hashCurrent.update(dataCurrent);
	var shaCurrent = hashCurrent.digest("hex");
	
	expect(shaReference === shaCurrent, "SHA1 hash of reference data does not match the SHA1 hash of the current data. URL: " + url + " reference SHA1: " + shaReference + " current SHA1: " + shaCurrent).to.be.true;
	
	return true;
}


/**
* Deletes all configs of all modules.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.deleteConfigs = function(modules, serverUrl, callback)
{
	var expect = require("chai").expect;
	
	exports.sendRequest(modules, serverUrl, "config?cmd=DELETE", 0, checkDeleteMessage);
	
	// checks if the delete command returned the config itself
	function checkDeleteMessage(data)
	{
		expect(data).to.be.not.null;
		
		// iterate over all modules
		Object.keys(data).forEach(function(moduleId, iModule)
		{
			// iterate over all configs
			data[moduleId].configs.forEach(function(config, iConfig)
			{
				// check if the answer of the delete request is the config itself with properties like "id", etc. which indicates that it has been successfully deleted
				expect(config.result, "moduleID: " + moduleId + " " + config.file).to.have.property("id");
			});
		});
		
		checkStatus();
	}
	
	// query the status of the configs which are supposed to be deleted
	function checkStatus()
	{
		exports.getChainStatus(modules, serverUrl, false, 0, checkStatusCallback);
	}
	
	// checks if the configs were really deleted by inspecting the returned status message
	function checkStatusCallback(data)
	{
		expect(data).to.be.not.null;
		
		// iterate over all modules
		Object.keys(data).forEach(function(moduleId, iModule)
		{
			// iterate over all configs
			data[moduleId].configs.forEach(function(config, iConfig)
			{
				var message = "deliberate attempted access to a supposedly deleted config does not return the expected error";
				expect(config.result, message).to.have.property("status", 404);
				expect(config.result, message).to.have.property("error");
				expect(config.result.error, message).not.to.equal("");
			});
		});
		
		callback();
	}
};



/**
* Deletes the specified properties from the data.
*
* @param data The input data which should be modified.
* @param propertiesToDelete An object which has the same structure as the data input object only for those properties which are supposed to be deleted.
*
* @return The input data stripped from the specified properties.
*/
function deleteProperties(data, propertiesToDelete)
{
	var clone = require("clone");
	var expect = require("chai").expect;
	
	// clone the variable and point the reference to the clone (complex input arguments are passed as reference)
	data = clone(data);
	
	var properties = Object.keys(propertiesToDelete);
	
	for(var i = 0; i < properties.length; i++)
	{
		var property = properties[i];
		
		// check if the data contains the property which is supposed to be deleted
		expect(data, "The specified object does not have the specified property (" + property + "). data: " + JSON.stringify(data) + " to-be-deleted: " + JSON.stringify(propertiesToDelete)).to.have.property(property);
		
		if((typeof(propertiesToDelete[property]) == "object") && Object.keys(propertiesToDelete[property]).length > 0)
		{
			var child = deleteProperties(data[property], propertiesToDelete[property]);
			
			if(Object.keys(child).length == 0)
			{
				delete data[property];
			}
			else
			{
				data[property] = child;
			}
		}
		else
		{
			delete data[property];
		}
	}
	
	return data;
}



/**
* Returns the status of the chains.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param stopOnErrorFlag If true, then the test stops if the checkError method detects an error in the returned request.
* @param attempts The remaining number of retries after a failed attempt before stopping the test which is only done when stopOnErrorFlag is true.
* @param callback Callback function to call at the end of the function. The callback is passed the updated modules object.
*/
exports.getChainStatus = function(modules, serverUrl, stopOnErrorFlag, attempts, callback)
{
	var expect = require("chai").expect;
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	var moduleId = Object.keys(modules)[0];
	var configId = modules[moduleId].configs[0].config.id;
	var url = moduleId + "/" + configId + "/status";
	var startTime = process.hrtime();
	
	client.get(url, function(error, result, body)
	{
		var duration = process.hrtime(startTime);
		
		if(stopOnErrorFlag)
		{
			error = checkError(error, body, url, attempts) || null;
		}
		
		// store the status
		modules[moduleId].configs[0].result = body;
		
		// log the duration of the status request for the current config
		if(!modules[moduleId].configs[0].hasOwnProperty("benchmarks"))
		{
			modules[moduleId].configs[0].benchmarks = {};
		}

		if(!modules[moduleId].configs[0].benchmarks.hasOwnProperty("status"))
		{
			modules[moduleId].configs[0].benchmarks.status = [];
		}

		modules[moduleId].configs[0].benchmarks.status.push(duration[0] + duration[1] * 1e-9);
		
		if(error && attempts > 0)
		{
			var seconds = 3;
			
			console.log("request failed; #attempts: " + attempts + " -> retrying in " + seconds + " seconds");
			console.log("url: " + serverUrl);
			console.log("error:");
			console.log(JSON.stringify(error, null, "\t"));
			
			setTimeout(function()
			{
				exports.getChainStatus(modules, serverUrl, stopOnErrorFlag, attempts - 1, callback)
			}, seconds * 1000);
		}
		else
		{
			expect(error, "failed to obtain status for " + url + " error: " + error).to.be.null;
			
			callback(modules);
		}
	});
};



/**
* Returns the modules object.
*
* @param modulesDir Path of the modules directory.
*
* @return The modules object.
*/
exports.getModules = function(modulesDir, serverUrl, callback)
{
	var expect = require("chai").expect;
	var fs = require("fs");
	var path = require("path");
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	var underscore = require("underscore");

	var moduleCandidates = getModuleCandidates(modulesDir);
	var modules = {};
	
	var url = "_moduleList_";
	
	client.get(url, function(error, result, body)
	{
		checkError(error, body, url);
		
		var moduleList = body;
		
		expect(Array.isArray(body), "returned data is not an array").to.be.true;
		expect(body.length, "module list is empty").to.be.above(0);
		
		// iterate over all module candidates
		Object.keys(moduleCandidates).forEach(function(moduleId)
		{
			var registeredFlag = false;
			
			// check if the module is registered on the server
			moduleList.forEach(function(module)
			{
				if(!registeredFlag && module.name === moduleId)
				{
					registeredFlag = true;
					modules[moduleId] = moduleCandidates[moduleId];
				}
			});
			
			// process module candidate only if it is registered on the server
			if(registeredFlag)
			{
				var testsRootDir = path.join(modules[moduleId].dir, "test");
				
				// get the files and directories (file system objects, FSOs) from the test root dir
				var fsoNames = fs.readdirSync(testsRootDir);
				
				modules[moduleId].configs = [];
					
				// iterate over all FSOs
				for(var j = 0; j < fsoNames.length; j++)
				{
					var fso = path.join(testsRootDir, fsoNames[j]);
				
					// skip the current item if it is not a directory
					if(!fs.statSync(fso).isDirectory())
					{
						continue;
					}
					
					// if the current item is a directory then check if it is the container for a config indicated by the existance of a config.json file
					var configFile = path.join(fso, "config.json");
					
					if(!fs.existsSync(configFile))
					{
						continue;
					}
					
					modules[moduleId].configs.push({"file": configFile});
				}
				
				// load the custom tests
				var customTestsFile = path.join(testsRootDir, "test.js");
				
				if(fs.existsSync(customTestsFile))
				{
					modules[moduleId].customTests = require(customTestsFile);
					
					var standardTestNames =
					[
						"setup",
						"checkInit",
						"statusBenchmark",
						"startConfig",
						"checkConfigExecution",
						"checkLastStableResults",
						"verifyOutputDataType",
						"processReferenceOutput",
						"outputPinBenchmark",
						"stopConfig",
						"deleteConfig"
					];
					
					// check for test name conflicts with any of the standard tests
					Object.keys(modules[moduleId].customTests).forEach(function(testName)
					{
						expect(underscore.contains(standardTestNames, testName), "Conflicting custom test name \"" + testName + "\". Custom test names should not equal any of the standard test names " + JSON.stringify(standardTestNames)).to.be.false;
					});
				}
			}
		});
		
		// check if at least one config has been found
		var message = "no module with a test subdirectory has been found in parent directory of the modules: " + path.resolve(modulesDir);
		expect(Object.keys(modules), message).to.have.length.above(0);
		
		//Object.keys(modules).forEach(function(moduleId, iModule)
		//{
		//	expect(modules[moduleId].configs.length, "no configs have been found for module " + moduleId).to.be.above(0);
		//});

		callback(modules);
	});
};



/**
* Returns the filenames from the specified directory.
*
* @param dirPath The directory path.
* @param sortFlag If true and the filenames (without extension) can be interpreted as integers, then the list is sorted numerically.
*
* @return The filenames.
*/
exports.getFilenames = function(dirPath, sortFlag)
{
	var expect = require("chai").expect;
	var fs = require("fs");
	var path = require("path");
	
	expect(fs.existsSync(dirPath) && fs.statSync(dirPath).isDirectory(), "the specified directory does not exist").to.be.true;
	
	var filenames = [];
	var content = fs.readdirSync(dirPath);
	
	for(var i = 0; i < content.length; i++)
	{
		var filename = content[i];
		var filePath = path.join(dirPath, filename);
		
		if(fs.statSync(filePath).isFile())
		{
			var extension = path.extname(content[i]);
			var filenameWoExt = path.basename(filename, extension);
			
			if(sortFlag)
			{
				filenames.push([filenameWoExt, filename]);
			}
			else
			{
				filenames.push(filename);
			}
		}
	}
	
	if(sortFlag)
	{
		var filenamesTemp = exports.parseArray(filenames);
		
		var array2DFlag = Array.isArray(filenames[0]);
		
		if(array2DFlag)
		{
			filenamesTemp.sort(function(a,b)
			{
				return (a[0] - b[0]);
			});
		}
		else
		{
			filenamesTemp.sort();
		}
		
		filenames = new Array(filenamesTemp.length);
		
		if(array2DFlag)
		{
			for(var i = 0; i < filenamesTemp.length; i++)
			{
				filenames[i] = filenamesTemp[i][1];
			}
		}
		else
		{
			filenames = filenamesTemp;
		}
	}
	
	return filenames;
};



/**
* Returns the module candidates from the specified modules directory. A directory is assumed to represent a module candidate if it at least contains data, src and test subdirectories.
*
* @param modulesDir The path of the modules directory.
*
* @return The module candidates object.
*/
function getModuleCandidates(modulesDir)
{
	var expect = require("chai").expect;
	var fs = require("fs");
	var path = require("path");

	var dirs = fs.readdirSync(modulesDir);
	
	var modules = {};
	
	// iterate over all directories
	for(var i = 0; i < dirs.length; i++)
	{
		var dirName = dirs[i];
		
		var moduleDir = path.join(modulesDir, dirName);
		
		if(!fs.statSync(moduleDir).isDirectory())
		{
			continue;
		}
		
		// check if the module candiate directory contains certain subdirectories
		var subdirs = ["def", "src", "test"];
		
		if(!hasSubdirs(moduleDir, subdirs))
		{
			continue;
		}
		
		// check if the def directory contains the module description json file
		var moduleDescriptionFile = path.join(moduleDir, "def", "ModuleDescription.json");
		
		if(!fs.existsSync(moduleDescriptionFile))
		{
			continue;
		}
		
		// extract the module ID from the module description file in the def directory
		var moduleDescriptionJson = fs.readFileSync(moduleDescriptionFile, "utf8");
		var moduleDescription = JSON.parse(moduleDescriptionJson);

		expect(moduleDescription, "failed to obtain the module ID because the module description JSON file does not contain the moduleID property: " + moduleDescriptionJson).to.have.property("moduleID");
		var moduleId = moduleDescription.moduleID;
		expect(moduleId, "the module ID in the module description is empty").not.to.equal("");
		
		modules[moduleId] = {};
		modules[moduleId].dir = moduleDir;
	}
	
	return modules;
}



/**
* Returns the module output description.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.getOutputDescription = function(modules, serverUrl, callback)
{
	var expect = require("chai").expect;
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	
	var moduleId = Object.keys(modules)[0];
	var url = moduleId + "/outputDescription";
	
	client.get(url, function(error, result, body)
	{
		checkError(error, body, url);
		
		expect(Array.isArray(body), "returned data is not an array").to.be.true;
		expect(body.length, "").to.be.above(0);
		
		// check if all pins have at least certain properties
		body.forEach(function(pin)
		{
			expect(pin).to.have.property("id");
			expect(pin).to.have.property("type");
		});
		
		modules[moduleId].outputDescription = body;
		
		callback();
	});
};



exports.getOutputPinAccessorValueRange = getOutputPinAccessorValueRange;
/**
* Returns the range of accessor values for the specified module, config and output pin.
*
* @return The range object with the array of accessor values to check. E.g. { "index|timestamp": { "values": [0, 1, 2, ...] } }.
* 			If the values property is an empty array, then this means that currently there are no accessor values availabe but
* 			it is expected, that there will be further values as long as the module is running. If the values property itself is
* 			missing, then this means that there are no more accessor values expected. The later situation might occur when the
* 			user-specified end accessor (status: running or finished) or the stable results end accessor (status: finished)
* 			has been reached.
*/
function getOutputPinAccessorValueRange(
	pinDir, 			///< reference data directory for a specific module, config and output pin
	pinId,  			///< pin ID
	status,  			///< config status
	outputDir,  		///< output directory for the current module config, e.g. "c:\modules\<module>\test\<config>\output"
	referenceGenerationFlag,  			///< True if data does not exist and needs to be created, otherwise false (data needs to be compared).
	successfulQueryAccessorValueMax 	///< The accessor value of the last successful query or -1 if there is none.
) {
	var expect = require("chai").expect;
	var fs = require("fs");
	var path = require("path");
	
	// check if the config is either running or finished
	checkConfigStatus(status, ["running", "finished"]);
	
	// assign the range file path
	var rangeFile = path.join(outputDir, "range.json");
	
	// get the stable results for the pin
	var results = getStableResultsInfoForPin(status.stableResults, pinId);
	
	// check if a certain accessor range has been specified
	var range = {};
	
	// reference data does not exist yet and needs to be generated
	if(referenceGenerationFlag)
	{
		// if the range file exists, then parse it and check it for invalid values or accessor combinations
		if(fs.existsSync(rangeFile))
		{
			var rangeInputJson;
		
			try
			{
				rangeInputJson = fs.readFileSync(rangeFile, "utf8");
			}
			catch(e)
			{
				expect(e, " error when trying to read " + rangeFile + " message: " + e).to.be.null;
			}
			
			var rangeInput;
			
			try
			{
				rangeInput = JSON.parse(rangeInputJson);
			}
			catch(e)
			{
				expect(e, " error when trying to parse " + rangeFile + " message: " + e).to.be.null;
			}
			
			// check if range was specified for specific pin
			if(rangeInput.hasOwnProperty(pinId) && (rangeInput[pinId].hasOwnProperty("index") || rangeInput[pinId].hasOwnProperty("timestamp")))
			{
				range = rangeInput[pinId];
				
				if(range.hasOwnProperty("index"))
				{
					// check the start value
					if(!range.index.hasOwnProperty("start"))
					{
						range.index.start = results.indexStart;
					}
					
					// check the end value
					if(!range.index.hasOwnProperty("end"))
					{
						range.index.end = results.indexEnd;
					}
					
					// remove invalid accessor combination
					if(range.hasOwnProperty("timestamp"))
					{
						delete range.timestamp;
					}
				}
				else if(range.hasOwnProperty("timestamp"))
				{
					// check the start value
					if(!range.timestamp.hasOwnProperty("start"))
					{
						range.timestamp.start = results.timestampStart;
					}
					
					// check the end value
					if(!range.timestamp.hasOwnProperty("end"))
					{
						range.timestamp.end = results.timestampEnd;
					}
				
					// remove invalid accessor combination
					if(range.hasOwnProperty("index"))
					{
						delete range.index;
					}
				}
			}
			// check if same range was specified for all pins
			else if(rangeInput.hasOwnProperty("index") || rangeInput.hasOwnProperty("timestamp"))
			{
				if(rangeInput.hasOwnProperty("index"))
				{
					range.index = rangeInput.index;
					
					// check the start value
					if(!range.index.hasOwnProperty("start"))
					{
						range.index.start = results.indexStart;
					}
					
					// check the end value
					if(!range.index.hasOwnProperty("end"))
					{
						range.index.end = results.indexEnd;
					}
					
					// remove invalid accessor combination
					if(range.hasOwnProperty("timestamp"))
					{
						delete range.timestamp;
					}
				}
				else if(rangeInput.hasOwnProperty("timestamp"))
				{
					range.timestamp = rangeInput.timestamp;
					
					// check the start value
					if(!range.timestamp.hasOwnProperty("start"))
					{
						range.timestamp.start = results.timestampStart;
					}
					
					// check the end value
					if(!range.timestamp.hasOwnProperty("end"))
					{
						range.timestamp.end = results.timestampEnd;
					}
				
					// remove invalid accessor combination
					if(range.hasOwnProperty("index"))
					{
						delete range.index;
					}
				}
			}
		}
		
		// index range check
		if(range.hasOwnProperty("index"))
		{
			expect(range.index.start > range.index.end, "the specified start index for the reference data (" + range.index.start  + ") is greater than the specified end index for the reference data (" + range.index.end + ") for pin " + pinId).to.be.false;
		}
		// timestamp range check
		else if(range.hasOwnProperty("timestamp"))
		{
			expect(range.timestamp.start > range.timestamp.end, "the specified start timestamp for the reference data (" + range.timestamp.start  + ") is greater than the specified end timestamp for the reference data (" + range.timestamp.end + ") for pin " + pinId).to.be.false;
		}
		// if none of the accessors exists, then default it to index and set the range to the stable results
		else
		{
			range.index = {};
			range.index.start = results.indexStart;
			range.index.end = results.indexEnd;
			range.index.values = [];
		}

		// generate the individual index values
		if(range.hasOwnProperty("index"))
		{
			var iStart = Math.max(successfulQueryAccessorValueMax + 1, Math.max(range.index.start, results.indexStart));
			var iEnd = Math.min(range.index.end, results.indexEnd);
			
			if(iStart <= iEnd || (status.status === "running" && (range.index.start > results.indexEnd || results.indexEnd < range.index.end)))
			{
				range.index.values = [];
				
				for(var i = iStart; i <= iEnd; i++)
				{
					range.index.values.push(i);
				}
			}
			else if(iStart < 0 || iEnd < 0)
			{
				delete range.index;
			}
		}
		else
		{
			expect(true, "<todo> create timestamp value range when Connected Vision framework supports timestamp list output").to.be.false;
		}
	}
	// reference data already exists and needs to be compared to the current data
	else
	{
		var indexDir = path.join(pinDir, "index");
		var timestampDir = path.join(pinDir, "timestamp");
		
		if(fs.existsSync(indexDir) && fs.statSync(indexDir).isDirectory())
		{
			range.index = {};

			var filenames = exports.getFilenames(path.join(pinDir, "index"), true);
			
			if(successfulQueryAccessorValueMax < parseInt(filenames[filenames.length - 1]))
			{
				range.index.values = [];
				
				for(var i = 0; i < filenames.length; i++)
				{
					var value = parseInt(filenames[i]);
					
					if(value > successfulQueryAccessorValueMax)
					{
						if(value > results.indexEnd && status.status !== "running")
						{
							str = "reference data for " + pinId + " pin does exist at index " + value + " but the config status is " + status.status + " and the stable results end index is " + results.indexEnd;
							expect(true, str).to.be.false;
						}
						
						if(value <= results.indexEnd)
						{
							range.index.values.push(value);
						}
					}
				}
			}
		}
		else if(fs.existsSync(timestampDir) && fs.statSync(timestampDir).isDirectory())
		{
			expect(true, "<todo> create timestamp value range when Connected Vision framework supports timestamp list output").to.be.false;
		}
	}
		
	return range;
}



/**
* Parses an array of integers encoded as strings.
*
* @param strArr The 1- or 2-dimensional array of strings. If it is a 2-dimensional array then the values of the 1st column are converted.
*
* @return The array of integers
*/
exports.parseArray = function(x)
{
	var y = [];
	
	for(var i = 0; i < x.length; i++)
	{
		var value;
		
		if(Array.isArray(x[i]))
		{
			value = [parseInt(x[i][0]), x[i][1]];
		}
		else
		{
			value = parseInt(x[i]);
		}
		
		y.push(value);
	}
	
	return y;
};



/**
* Returns the item from the stable results array which is part of the Connected Vision status information for the specified pin ID.
*
* @param results The stable results array from the Connected Vision status information
* @param pinId The pin ID for which to return the stable results information
*
* @return The stable results information for the specified pin ID
*/
function getStableResultsInfoForPin(results, pinId)
{
	var expect = require("chai").expect;
	
	// get the index of the current pin within the status.stableResults array
	var result = null;
	
	for(var i = 0; i < results.length; i++)
	{
		if(results[i].pinID == pinId)
		{
			result = results[i];
			break;
		}
	}
		
	expect(result).to.be.not.null;
	expect(result).to.have.property("indexEnd");
	
	return result;
}



/**
* Returns true if the parent directory contains all the specified subdirectories, otherwise false.
*
* @param parent The parent directory.
* @param dirs The child subdirectories.
*
* @return True if the parent directory contains all the specified subdirectories, otherwise false.
*/
function hasSubdirs(parent, dirs)
{
	var fs = require("fs");

	var flag = true;
	
	for(var i = 0; i < dirs.length; i++)
	{
		var dir = parent + "/" + dirs[i];
		
		if(!fs.existsSync(dir) || !fs.statSync(dir).isDirectory())
		{
			flag = false;
			break;
		}
	}

	return flag;
}



/**
* Checks if the server is alive.
*
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function. The callback is passed an array of the resulting Connected Vision configs.
*/
exports.isServerAlive = function(serverUrl, callback)
{
	var expect = require("chai").expect;
	var request = require("request");
	
	// check if contacting the server succeeds
	request(serverUrl, function(error, response, body)
	{
		expect(error, "failed to connect to server (error is not null)").to.be.null;
		expect(response, "failed to connect to server (response is undefined)").not.to.be.undefined;
		expect(response, "failed to connect to server").to.have.property("statusCode", 200);
		expect(body, "failed to connect to server (body is undefined)").not.to.be.undefined;
		
		callback();
	});
};



/**
* Checks if the config for the Joe test suite has the expected parameters
*
* @param config The config.
*
* @return Callback function to call at the end of the function.
*/
exports.checkTestSuiteConfig = function(configIn)
{
	var argv = require("optimist").argv;
	var clone = require("clone");
	var expect = require("chai").expect;
	var fs = require("fs");
	var path = require("path");
	var underscore = require("underscore");
	
	var config = clone(configIn);
	
	expect(argv).to.have.property("rootdir");
	expect(argv).to.have.property("architecture");
	expect(argv).to.have.property("buildconfig");
	
	// check the application architecture
	if(!config.hasOwnProperty("architecture"))
	{
		config.architecture = argv.architecture;
	}
	
	// check the server URL
	expect(config).to.have.property("serverUrl");
	expect(config.serverUrl).to.have.length.above(0);
	
	// check the modules directory
	expect(config).to.have.property("modulesDir");
	config.modulesDir = config.modulesDir.replace("<rootdir>", argv.rootdir);
	config.modulesDir = path.resolve(config.modulesDir);
	expect(fs.existsSync(config.modulesDir), "modules directory does not exist: " + config.modulesDir).to.be.true;
	
	// check the startup directory
	expect(config).to.have.property("startupDir");
	config.startupDir = config.startupDir.replace("<rootdir>", argv.rootdir);
	config.startupDir = config.startupDir.replace("<architecture>", config.architecture);
	config.startupDir = config.startupDir.replace("<buildconfig>", argv.buildconfig);
	config.startupDir = path.resolve(config.startupDir);
	expect(fs.existsSync(config.startupDir), "startup directory does not exist: " + config.startupDir).to.be.true;
	
	// check the server exe file
	expect(config).to.have.property("serverExeFile");
	config.serverExeFile = config.serverExeFile.replace("<rootdir>", argv.rootdir);
	config.serverExeFile = config.serverExeFile.replace("<architecture>", config.architecture);
	config.serverExeFile = config.serverExeFile.replace("<buildconfig>", argv.buildconfig);
	config.serverExeFile = path.resolve(config.serverExeFile);
	expect(fs.existsSync(config.serverExeFile), "server exe file does not exist: " + config.serverExeFile).to.be.true;
	
	// optional flag that indicates if server output should be displayed on console
	if(!config.hasOwnProperty("serverOutputDisplayFlag"))
	{
		config.serverOutputDisplayFlag = false;
	}
	
	// optional test-specific parameters
	if(!config.hasOwnProperty("tests"))
	{
		config.tests = [];
	}
	
	// check config execution
	var testName = "checkConfigExecution";
	var i = underscore.findIndex(config.tests, function(obj){ return Object.keys(obj)[0] == testName; });

	if(i != -1 && (!config.tests[i][testName].hasOwnProperty("criteria") || underscore.isEmpty(config.tests[i][testName].criteria)))
	{
		config.tests[i][testName].criteria = { "status": "finished" };
	}
	
	// status benchmark
	testName = "statusBenchmark";
	i = underscore.findIndex(config.tests, function(obj){ return Object.keys(obj)[0] == testName; });
	
	if(i != -1)
	{
		if(!config.tests[i][testName].hasOwnProperty("requests"))
		{
			config.tests[i][testName].requests = 1;
		}
		else
		{
			expect(config.tests[i][testName].requests, "test suite config.tests.statusBenchmark.requests must be a number").to.be.a("number");
			expect(config.tests[i][testName].requests).to.be.above(-1);
		}
	}
	
	// output pin benchmark
	testName = "outputPinBenchmark";
	i = underscore.findIndex(config.tests, function(obj){ return Object.keys(obj)[0] == testName; });
	
	if(i != -1)
	{
		if(!config.tests[i][testName].hasOwnProperty("requests"))
		{
			config.tests[i][testName].requests = 1;
		}
		else
		{
			expect(config.tests[i][testName].requests, "test suite config.tests.outputPinBenchmark.requests must be a number").to.be.a("number");
			expect(config.tests[i][testName].requests).to.be.above(-1);
		}
	}
	
	return config;
};



/**
* Loads the configuration for the Joe test suite.
*
* @return The configuration.
*/
exports.loadTestSuiteConfig = function(configFilePath)
{
	var argv = require("optimist").argv;
	var expect = require("chai").expect;
	var fs = require("fs");
	
	// if the config file path parameter was not specified, then check if the value exists in the command line arguments
	if(!configFilePath)
	{
		expect(argv).to.have.property("configfile");
		
		configFilePath = argv.configfile;
	}

	expect(fs.existsSync(configFilePath), "test suite config file does not exist: " + configFilePath).to.be.ok;
	
	// try to read and parse the config file
	var config = JSON.parse(fs.readFileSync(configFilePath, "utf8"));
	
	return config;
};



/**
* Sends the configs to the server
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.sendConfigs = function(modules, serverUrl, callback)
{
	var expect = require("chai").expect;
	var fs = require("fs");
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	var moduleId = Object.keys(modules)[0];
	var config = modules[moduleId].configs[0];

	// read the file content
	var data;
	
	try
	{
		data = JSON.parse(fs.readFileSync(config.file, "utf8"));
	}
	catch(e)
	{
		expect(data, "failed to parse config JSON file: " + config.file + " error: " + e).to.be.not.undefined;
	}
	
	var url = "/" + moduleId + "/0/config";
	
	client.put(url, data, function(error, result, body)
	{
		checkError(error, body, url);
		expect(body).to.have.property("moduleID");
		expect(body).to.have.property("id");
		
		// assign the config object returned by the server
		modules[moduleId].configs[0].config = body;
		
		callback();
	});
};



/**
* Triggers the method for processing the reference output data.
*
* @param modules The modules object.
* @param architecture The application architecture (e.g. Win32, x64).
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.processReferenceOutput = function(modules, architecture, serverUrl, callback)
{
	var expect = require("chai").expect;
	var fs = require("fs.extra");
	var path = require("path");
	
	expect(Object.keys(modules).length).to.equal(1);
	var moduleId = Object.keys(modules)[0];
	
	expect(modules[moduleId].configs.length).to.equal(1);
	var config = modules[moduleId].configs[0];
	
	// e.g. config.file: "c:\modules\<module>\test\<config>\config.json" -> "c:\modules\<module>\test\<config>"
	var configDir = path.join(modules[moduleId].configs[0].file, "..");
	
	modules[moduleId].configs[0].output = {};
	
	// -> "c:\modules\<module>\test\<config>\output"
	var outputDir = path.join(configDir, "output");
	
	// -> "c:\modules\<module>\test\<config>\output\reference"
	var referenceDir = path.join(outputDir, architecture, "reference");
		
	// -> "c:\modules\<module>\test\<config>\output\recent"
	var recentDir = path.join(outputDir, architecture, "recent");
	
	// iterate over all output pins of the output description
	modules[moduleId].outputDescription.forEach(function(pin, iPin)
	{
		modules[moduleId].configs[0].output[pin.id] = {};
		
		// -> "c:\modules\<module>\test\<config>\output\reference\<pinId>"
		var referencePinDir = path.join(referenceDir, pin.id);
		
		// -> "c:\modules\<module>\test\<config>\output\recent\<pinId>"
		var recentPinDir = path.join(recentDir, pin.id);
		
		// if not all data generation flags of the pins have the same value, i.e. reference data exists for some pins which is an inconsistent unexpected state, then the corresponding preceding expect statement would have failed -> merge all flags into a single flag
		modules[moduleId].configs[0].output[pin.id] = {};
		
		var dataGenerationFlag;
		
		// if no accessor directory exists, then the reference data needs to be generated
		if(fs.existsSync(path.join(referencePinDir, "index")) && exports.getFilenames(path.join(referencePinDir, "index")).length > 0)
		{
			dataGenerationFlag = false;
		}
		else if(fs.existsSync(path.join(referencePinDir, "timestamp")) && exports.getFilenames(path.join(referencePinDir, "timestamp")).length > 0)
		{
			dataGenerationFlag = false;
		}
		else
		{
			dataGenerationFlag = true;
		}
		
		var range = getOutputPinAccessorValueRange(referencePinDir, pin.id, modules[moduleId].configs[0].result, outputDir, dataGenerationFlag);
		
		if(Object.keys(range).length === 0)
		{
			dataGenerationFlag = false;
		}
		
		modules[moduleId].configs[0].output[pin.id].dataGenerationFlag = dataGenerationFlag;
		
		// if the recent data pin directory from a preceding execution of the test exists, then delete it
		fs.removeSync(recentPinDir);
			
		if(Object.keys(range).length > 0)
		{
			var accessorType = Object.keys(range)[0];
			
			modules[moduleId].configs[0].output[pin.id].accessorType = accessorType;
			
			// -> "c:\modules\<module>\test\<config>\output\reference\<pinId>\<accessor>
			modules[moduleId].configs[0].output[pin.id].referenceAccessorDir = path.join(referencePinDir, accessorType);
			
			// -> "c:\modules\<module>\test\<config>\output\recent\<pinId>\<accessor>
			modules[moduleId].configs[0].output[pin.id].recentAccessorDir = path.join(recentPinDir, accessorType);
			
			// check if reference data needs to be generated and create the directory if required
			if(dataGenerationFlag && !fs.existsSync(modules[moduleId].configs[0].output[pin.id].referenceAccessorDir))
			{
				fs.mkdirpSync(modules[moduleId].configs[0].output[pin.id].referenceAccessorDir);
			}
			
			// create the recent data directory
			if(!fs.existsSync(modules[moduleId].configs[0].output[pin.id].recentAccessorDir))
			{
				fs.mkdirpSync(modules[moduleId].configs[0].output[pin.id].recentAccessorDir);
			}
		}
	});

	processReferenceOutputRecursive(modules, serverUrl, outputDir, {}, callback);
};



/**
* Processes the reference output data.
* If the data does not exist, it generates it, otherwise it compares it with the current data returned by the module.
* The method is called recursively to deal with running chains where new results are being computed while querying the pin for existing results.
*/
function processReferenceOutputRecursive
(
	modules,		///< The modules object.
	serverUrl,		///< The Connected Vision server URL, e.g. http://localhost:2020.
	outputDir, 		///< The output directory for the current module config, e.g. "c:\modules\<module>\test\<config>\output".
	valuesMaxPrev,	///< The maximum successfully processed accessor value of the preceding iteration.
					///		For each pin the object has a property with the corresponding pin ID and accessor value
					///		e.g. { "<pin_ID_1>": <pin_ID_1_value>, "<pin_ID_2>": <pin_ID_2_value>, ... }
	callback		///< Callback function to call at the end of the function.
)
{
	var async = require("async");
	var clone = require("clone");
	var expect = require("chai").expect;
	var path = require("path");
	
	expect(Object.keys(modules).length).to.equal(1);
	var moduleId = Object.keys(modules)[0];
	var requestsLinear = {};
	var stopFlag = true;

	// iterate over all output pins of the output description and generate the requests for querying the output pin
	for(var i = 0; i < modules[moduleId].outputDescription.length; i++)
	{
		var pin = modules[moduleId].outputDescription[i];
		
		// skip the current pin if it does not have at least the referenceAccessorDir property which is the case when no reference data is supposed to be processed
		if(!modules[moduleId].configs[0].output[pin.id].hasOwnProperty("referenceAccessorDir"))
		{
			continue;
		}
		
		var referencePinDir = path.join(modules[moduleId].configs[0].output[pin.id].referenceAccessorDir, "..");
		
		// determine the last successfully processed accessor value
		var valueMaxPrev = -1;
		
		if(valuesMaxPrev && valuesMaxPrev.hasOwnProperty(pin.id) && valuesMaxPrev[pin.id] > -1)
		{
			valueMaxPrev = valuesMaxPrev[pin.id];
		}
				
		// obtain the accessor value range to process starting with the value after (the possibly defined) valueMaxPrev
		var range = getOutputPinAccessorValueRange(referencePinDir, pin.id, modules[moduleId].configs[0].result, outputDir, modules[moduleId].configs[0].output[pin.id].dataGenerationFlag, valueMaxPrev);
		
		var accessorType = Object.keys(range)[0];
		
		if
		(
			stopFlag &&
			accessorType &&
			range.hasOwnProperty(accessorType) &&
			range[accessorType].hasOwnProperty("values") &&
			!
			(
				range[accessorType].values.length === 0 &&
				(
					!range[accessorType].hasOwnProperty("end") ||
					valueMaxPrev >= range[accessorType].end
				)
			)
		)
		{
			stopFlag = false;
		}
		
		// var sr = getStableResultsInfoForPin(modules[moduleId].configs[0].result.stableResults, pin.id);
		// console.log("pin: " + pin.id + " results: " + sr.indexStart + "..." +  sr.indexEnd + " prev: " + valueMaxPrev + " range: " + (range.index.hasOwnProperty("values") ? (range.index.values[0] + "..." + range.index.values[range.index.values.length - 1]) : "none -> stop"));
		
		// get the requests for the async module based on the determined value range
		requestsLinear[pin.id] = processReferenceOutputPin(modules[moduleId], moduleId, pin, range, serverUrl);
	}
	
	// stop when there are no more requests
	if(stopFlag)
	{
		callback();
		return;
	}
		
	// interleave the requests of the pins
	// this is done for modules which use a ring buffer and not a database for the output data
	// when using ring buffers, accessor values close to the accessor start value are likely to get removed from the ring buffer sooner than values closer to the accessor end value
	// process the ring buffer values closer to the start for all pins before proceeding to the values closer to the end
	// e.g. [[pin_A_index_0, pin_A_index_1, ...], [pin_B_index_3, pin_B_index_4, ...]] -> [pin_A_index_1, pin_B_index_3, pin_A_index_1, pin_B_index_4, ...]
	// ATTENTION: this may only work for cases where all start values are within an interval with its size being a fraction of the ringbuffer size
	var requests = [];
	var nMax = -1;
	
	Object.keys(requestsLinear).forEach(function(pinId, iPin)
	{
		nMax = Math.max(nMax, requestsLinear[pinId].length);
	});
	
	for(var i = 0; i < nMax; i++)
	{
		Object.keys(requestsLinear).forEach(function(pinId, iPin)
		{
			if(i < requestsLinear[pinId].length)
			{
				requests.push(requestsLinear[pinId][i]);
			}
		});
	}
	
	//if(requests.length > 0)
	//{
	//	console.log("processing " + requests.length + " requests ...");
	//}
	
	async.series(requests, function(error, result)
	{
		var valuesMax = valuesMaxPrev;
		
		// get the maximum successful query accessor value for each pin
		for(var i = 0; i < result.length; i++)
		{
			var pinId = result[i].pinId;
			
			expect(result[i], "ref output async.series i: " + i).not.to.be.undefined;
			expect(result[i], "ref output async.series i: " + i).not.to.be.null;
			
			if(!valuesMax.hasOwnProperty(pinId))
			{
				valuesMax[pinId] = -1;
			}
			
			if(result[i].accessorValue > valuesMax[pinId])
			{
				valuesMax[pinId] = result[i].accessorValue;
			}
		}
		
		var status = modules[moduleId].configs[0].result.status;
		
		if(status === "running")
		{
			var waitFlag = true;
			
			Object.keys(valuesMax).forEach(function(pinId, iPinId)
			{
				if(waitFlag && (!valuesMaxPrev || !valuesMaxPrev.hasOwnProperty(pinId) || valuesMax[pinId] - valuesMaxPrev[pinId] > 10))
				{
					waitFlag = false;
				}
			});
		
			// if the current and the previous max processed accessor value match, then wait some time for the output pin to provided further results
			if(waitFlag)
			{
				// console.log("running + timeout ...");
				
				setTimeout(function()
				{
					exports.getChainStatus(modules, serverUrl, true, 0, getChainStatusCallback);
				}, 1000);
			}
			// otherwise immediately proceed to querying further results
			else
			{
				// console.log("running ... ");
				
				exports.getChainStatus(modules, serverUrl, true, 0, getChainStatusCallback);
			}
		}
		else if(status === "finished")
		{
			// console.log("finished ... ");
			
			exports.getChainStatus(modules, serverUrl, true, 0, getChainStatusCallback);
		}
		else
		{
			expect(true, "reference output async.series status != running || finished").to.be.false;
		}
		
		function getChainStatusCallback(data)
		{
			processReferenceOutputRecursive(data, serverUrl, outputDir, valuesMax, callback);
		}
	});
}



/**
* Processes the reference output data for a specific pin.
* If the data does not exist, it generates it, otherwise it compares it to the current data returned by the module.
*
* @param module The module object.
* @param moduleId The module ID.
* @param pin A pin from the module output description.
* @param range The range object with the array of accessor values to check. E.g. { "index|timestamp": { "values": [0, 1, 2, ...] } }
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
*/
function processReferenceOutputPin(module, moduleId, pin, range, serverUrl)
{
	var expect = require("chai").expect;
	var fs = require("extfs");
	var http = require("http");
	var path = require("path");
	var requestJson = require("request-json");
	var url = require("url");
	
	var requests = [];
	var accessorType = module.configs[0].output[pin.id].accessorType;
	
	if(!range.hasOwnProperty(accessorType) || !range[accessorType].hasOwnProperty("values"))
	{
		return requests;
	}
	
	var client = requestJson.createClient(serverUrl);
	
	var extension = "dat";
	
	if(pin.type === "application/json")
	{
		extension = "json";
	}
	// determine the file extension based on the module output description content type using the string after the last forward slash character e.g. "image/jpeg" -> "jpeg"
	else
	{
		var re = new RegExp("[^\/]+$", "g");

		for(var i = 0; i < module.outputDescription.length; i++)
		{
			if(module.outputDescription[i].id === pin.id)
			{
				var str = module.outputDescription[i].type;
				var result = re.exec(str);
				
				if(result && result.length > 0)
				{
					extension = result[0];
				}
			}
		}
	}
	
	range[accessorType].values.forEach(function(accessorValue, iAccessorValue)
	{
		var urlPart = moduleId + "/" + module.configs[0].config.id + "/" + pin.id + "/" + accessorType + "/" + accessorValue;
		
		// -> "c:\modules\<module>\test\<config>\output\reference\<pinId>\<accessor>\<value>.<extension>"
		var referenceFile = path.join(module.configs[0].output[pin.id].referenceAccessorDir, accessorValue.toString() + "." + extension);
		
		// -> "c:\modules\<module>\test\<config>\output\recent\<pinId>\<accessor>\<value>.<extension>"
		var recentDataFile = path.join(module.configs[0].output[pin.id].recentAccessorDir, accessorValue.toString() + "." + extension);
			
		// if the variable is not null after the following assignments, then the user-defined, custom comparison method will be used
		var customComparison = null;
		
		if(module.hasOwnProperty("customTests"))
		{
			if(module.customTests.hasOwnProperty("compare" + pin.id) && typeof(module.customTests["compare" + pin.id]) === "function")
			{
				customComparison = module.customTests["compare" + pin.id];
			}
			else if(module.customTests.hasOwnProperty("compare") && typeof(module.customTests["compare"]) === "function")
			{
				customComparison = module.customTests["compare"];
			}
		}
		
		// process JSON data
		if(pin.type === "application/json")
		{
			requests.push(function(asyncCallback)
			{
				client.get(urlPart, function(error, result, body)
				{
					// console.log("url: " + urlPart);
				
					var ret = {};
					ret.pinId = pin.id;
					ret.accessorValue = accessorValue;
										
					var dataCurrentJson = JSON.stringify(body);
					
					// generated the JSON data files
					if(module.configs[0].output[pin.id].dataGenerationFlag)
					{
						// write the current data to a json (text) file
						try
						{
							fs.writeFileSync(referenceFile, dataCurrentJson, "utf8");
						}
						catch(e)
						{
							expect(e, " error when trying to write reference data file " + referenceFile + " message: " + e).to.be.null;
						}
					}
					// compare the reference JSON data to the current JSON data
					else
					{
						// read the reference data from a json (text) file
						var dataReferenceJson;
						
						try
						{
							dataReferenceJson = fs.readFileSync(referenceFile, "utf8");
						}
						catch(e)
						{
							expect(e, " error when trying to read reference data file " + referenceFile + " message: " + e).to.be.null;
						}
						
						// parse the reference data
						var dataReference;
						
						try
						{
							dataReference = JSON.parse(dataReferenceJson);
						}
						catch(e)
						{
							expect(e, " error when trying to parse reference data file " + referenceFile + " message: " + e).to.be.null;
						}
						
						if(customComparison === null)
						{
							compareJsonData(body, dataReference, urlPart);
						}
						else
						{
							customComparison(body, dataReference, urlPart, pin);
						}
					}
					
					// always write the data of the current test execution as recent data to a file
					try
					{
						fs.writeFileSync(recentDataFile, dataCurrentJson, "utf8");
					}
					catch(e)
					{
						expect(e, " error when trying to write recent data file " + recentDataFile + " message: " + e).to.be.null;
					}
					
					asyncCallback(null, ret);
				});
			});
		}
		// process binary data
		else
		{
			requests.push(function(asyncCallback)
			{
				http.get(url.parse(serverUrl + "/" + urlPart), function(res)
				{
					var ret = {};
					ret.pinId = pin.id;
					ret.accessorValue = accessorValue;
				
					var data = [];

					res.on("data", function(chunk)
					{
						data.push(chunk);
					});
					
					res.on("end", function()
					{
						// concatenate the array of buffers to a single buffer
						var dataCurrent = Buffer.concat(data);
						
						// generated the binary data files
						if(module.configs[0].output[pin.id].dataGenerationFlag)
						{
							fs.writeFileSync(referenceFile, dataCurrent, "binary");
						}
						// compare the reference binary data to the current binary data using hashes
						else
						{
							var dataReference;
							
							// read the binary data file
							try
							{
								dataReference = fs.readFileSync(referenceFile);
							}
							catch(e)
							{
								expect(e, " error when trying to read reference data file " + referenceFile + " message: " + e).to.be.null;
							}
							
							if(customComparison === null)
							{
								compareBinaryData(dataCurrent, dataReference, urlPart);
							}
							else
							{
								customComparison(dataCurrent, dataReference, urlPart, pin);
							}
						}
							
						asyncCallback(null, ret);
					
						// always write the data of the current test execution as recent data to a file
						try
						{
							fs.writeFileSync(recentDataFile, dataCurrent, "binary");
						}
						catch(e)
						{
							expect(e, " error when trying to write recent data file " + recentDataFile + " message: " + e).to.be.null;
						}
					});
				});
			});
		}
	});
	
	return requests;
}



/**
* Sends a request to a server.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param request The request, i.e. the URL part after the module name and id, e.g. the substring "control/start/" from "http://localhost:2020/MyModule/xyz/control/start/".
* @param attempts The remaining number of retries after a failed attempt before throwing an error.
* @param callback Callback function to call at the end of the function. The callback is passed the updated modules object.
*/
exports.sendRequest = function(modules, serverUrl, request, attempts, callback)
{
	var expect = require("chai").expect;
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	
	var moduleId = Object.keys(modules)[0];
	attempts = attempts || 0;
	var url = moduleId + "/" + modules[moduleId].configs[0].config.id + "/" + request;
	
	client.get(url, function(error, result, body)
	{
		error = checkError(error, body, url, attempts) || null;
		
		if(attempts == 0)
		{
			expect(body).to.have.property("moduleID");
			expect(body).to.have.property("id");
		}

		modules[moduleId].configs[0].result = body;
		
		if(error && attempts > 0)
		{
			var seconds = 3;
			
			console.log("request failed; #attempts: " + attempts + " -> retrying in " + seconds + " seconds");
			console.log("url: " + serverUrl);
			console.log("error:");
			console.log(JSON.stringify(error, null, "\t"));
			
			setTimeout(function()
			{
				exports.sendRequest(modules, serverUrl, request, attempts - 1, callback);
			}, seconds * 1000);
		}
		else
		{
			expect(error, "failed to send request to " + url + " error: " + error).to.be.null;
			
			callback(modules);
		}
	});
};

/**
* Sends the config to the server and resets it.
*
* @param modulesDir Path of the modules directory.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.setUpConfig = function(modules, serverUrl, callback)
{
	var expect = require("chai").expect;

	// send the config to the server
	exports.sendConfigs(modules, serverUrl, sendConfigsCallback);
	
	// reset the config
	function sendConfigsCallback()
	{
		//setTimeout(function()
		//{
			exports.sendRequest(modules, serverUrl, "control/reset/", 0, resetCallback);
		//}, 1000);
	}
	
	function resetCallback(data)
	{
		callback();
	}
};

/**
* Shortens the specified string by excluding a substring from the middle of the string and placing a filler string into the gap so that the final string has the specified maximum length.
*
* @param str The string to shorten.
* @param lengthMax The maximum lengtht of the returned string.
* @param fillerStr The filler string used as replacement.
*/
exports.shortenString = function(str, lengthMax, fillerStr)
{
	if(str.length > lengthMax)
	{
		if(fillerStr === undefined || typeof(fillerStr) != "string")
		{
			fillerStr = "..";
		}
		
		var lengthMaxWoFiller = lengthMax - fillerStr.length;
		var s11 = 0;
		var s12 = Math.floor(lengthMaxWoFiller / 2) - ((lengthMaxWoFiller + 1) % 2) + 1;
		var s21 = str.length - Math.floor(lengthMaxWoFiller / 2);
		var s22 = str.length;
		
		str = str.substring(s11, s12) + fillerStr + str.substring(s21, s22);
	}
	
	return str;
};


/**
* Starts the config.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.startConfig = function(modules, serverUrl, callback)
{
	exports.sendRequest(modules, serverUrl, "control/start/", 10, startCallback);
	
	function startCallback(data)
	{
		callback();
	}
};



/**
* Starts the Connected Vision server.
*
* @param config The Joe test suite config.
*
* @return The server process handle.
*/
exports.startServer = function(config, callback)
{
	var expect = require("chai").expect;
	var path = require("path");
	var spawn = require("child_process").spawn;
	
	var serverExeFile = path.resolve(config.serverExeFile);
	var startupDir = path.resolve(config.startupDir);
	
	// start the server
	var server = spawn(serverExeFile, [], { cwd: startupDir });
	
	// handle the case of the server failing to start
	server.on("error", function(error)
	{
		expect(error, "failed to start Connected Vision server (" + error + ")").to.be.null;
	});
	
	// check if the Connected Vision server console data is supposed to be diplayed on the current console
	if(config.serverOutputDisplayFlag)
	{
		server.stdout.on("data", function (data)
		{
			process.stdout.write(data);
		});
	}
	
	expect(server.pid, "Connected Vision server instance is not running (pid: " + server.pid + ")").to.not.equal(0);

	// give the server additional time for starting up
	setTimeout(function()
	{
		callback(server);
	}, 5000);
};



/**
* Stops the config.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.stopConfig = function(modules, serverUrl, callback)
{
	var expect = require("chai").expect;
	
	var moduleId = Object.keys(modules)[0];
	var config = modules[moduleId].configs[0];
	var timeStart = Date.now();
	var timeoutMax = 60 * 1000;
	
	exports.sendRequest(modules, serverUrl, "control/stop/", 0, stopConfigCallback);
	
	function stopConfigCallback()
	{
		// continue querying the status when the config is still running and the timeout has not been reached
		if((Date.now() - timeStart) < timeoutMax && config.result.hasOwnProperty("status") && config.result.status === "running")
		{
			setTimeout(function()
			{
				exports.getChainStatus(modules, serverUrl, true, 0, stopConfigCallback);
			}, 5000);
		}
		else
		{
			checkConfigStatus(config.result, ["finished", "stopped"]);
			callback();
		}
	}
};



/**
* Checks the correct execution of the config according to the specified criteria.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param criteria Contains certain criteria which have to be fulfilled before calling the callback function.
			criteria.results.index.count: The minimal stable results count that has to be reached by every pin.
			criteria.runtime: If the value (seconds) is greater 0.0, then the status is queried in a regular interval until the config is either finished or is still running after the the specified time has elapsed.
			criteria.status: The status needs to equal the specified value (e.g. "finished").
* @param callback Callback function to call after all requests have been sent.
*/
exports.checkConfigExecution = function(modules, serverUrl, criteria, callback)
{
	var expect = require("chai").expect;
	
	if(criteria.hasOwnProperty("runtime"))
	{
		expect(criteria.runtime).to.be.above(0);
	}
	
	var moduleId = Object.keys(modules)[0];
	
	
	exports.sendRequest(modules, serverUrl, "status/", 10, checkConfigExecutionRecursion);
	
	var recursionStartTime = (new Date()).getTime();
	
	var criteriaTimeout = 30000;
	var recursionTimeoutStartup = 5000;
	var recursionTimeoutSubsequent = 3000;
	var recursionTimeout = recursionTimeoutStartup;
	
	function checkConfigExecutionRecursion(data)
	{
		var config = data[moduleId].configs[0];
		
		expect(config.result).to.have.property("status");
		
		var now = (new Date()).getTime();
		
		// general criteria-independent timeout flag
		var timeoutFlag = (now - recursionStartTime) > criteriaTimeout;
		
		
		// check the minimum runtime criterion
		var runtimeFulfilledFlag = true;
		
		// if a minimum runtime was specified, then check if it is already elapsed
		if(criteria.hasOwnProperty("runtime"))
		{
			runtimeFulfilledFlag = false;
			
			var elapsed = config.result.systemTimeProcessing - config.result.startTime;
			var threshold = criteria.runtime * 1000;
				
			if(config.result.status === "running")
			{
				runtimeFulfilledFlag = elapsed > threshold;
			}
			// consider a config with status "finished" to have fulfilled the runtime criterion regardless of the actual runtime
			else if(config.result.status === "finished")
			{
				runtimeFulfilledFlag = true;
			}
			else
			{
				var messageSuffix = "";
				
				if(timeoutFlag)
				{
					messageSuffix = " and the general timeout has expired";
				}
				
				checkConfigStatus(config.result, ["running", "finished"], messageSuffix);
			}
		}
		
		
		// check the stable results criterion
		var resultsFulfilledFlag = true;
		
		// if a minimum number of stable results has been specified, then check if it has already been reached
		if(criteria.hasOwnProperty("results"))
		{
			var pinIDs = Object.keys(criteria.results);

			for(var i = 0; i < pinIDs.length; i++)
			{
				var pinID = pinIDs[i];
				
				for(var j = 0; j < config.result.stableResults.length; j++)
				{
					var pin = config.result.stableResults[j];
					
					if(pin.pinID !== pinID)
					{
						continue;
					}
					
					var accessor = Object.keys(criteria.results[pinID])[0];
					
					expect(["index", "timestamp"], "invalid stable results accessor \"" + accessor + "\" specified in criteria").to.include(accessor);
					
					if(accessor === "index")
					{
						if(criteria.results[pinID][accessor].hasOwnProperty("count"))
						{
							expect(criteria.results[pinID][accessor].count).to.be.a("number");
							
							var iStart = pin[accessor + "Start"];
							var iEnd = pin[accessor + "End"];
							
							if(iStart < 0 || iEnd < 0 || (iEnd - iStart + 1) < criteria.results[pinID][accessor].count)
							{
								resultsFulfilledFlag = false;
								break;
							}
						}
						else if(criteria.results[pinID][accessor].hasOwnProperty("indexEnd"))
						{
							expect(criteria.results[pinID][accessor].indexEnd).to.be.a("number");
							
							var iEnd = pin[accessor + "End"];
							
							if(iEnd < criteria.results[pinID][accessor].indexEnd)
							{
								resultsFulfilledFlag = false;
								break;
							}
						}
						else
						{
							expect(criteria.results[pinID][accessor]).to.have.property("count || indexEnd");
						}
					}
					else
					{
						expect(accessor, "only accessor criteria criteria.index.count is supported").to.equal("index");
					}
				}
			}
			
			// check if the criterion is not fulfilled, the status is not running and the timeout has expired
			expect(!resultsFulfilledFlag && config.result.status !== "running" && timeoutFlag, "config is not running and the general timeout has expired").to.be.false;
		}
		
		
		// check the status criterion
		var statusFulfilledFlag = true;
		
		if(criteria.hasOwnProperty("status"))
		{
			// check if the criterion is not fulfilled and the general timeout has expired
			statusFulfilledFlag = config.result.status === criteria.status;
			var str = "status " + config.result.status + " != " + criteria.status + " and the general timeout has expired" + (config.result.message ? (" error: " + config.result.message) : "");
			expect(!statusFulfilledFlag && timeoutFlag, str).to.be.false;
		}
		
		
		// all checks passed
		if(runtimeFulfilledFlag && resultsFulfilledFlag && statusFulfilledFlag)
		{
			callback();
		}
		else
		{
			// schedule a recursive check of the running configs after a certain timeout
			setTimeout(function()
			{
				// wait for a shorter period of time at the first iteration than for the following iterations
				if(recursionTimeout === recursionTimeoutStartup)
				{
					recursionTimeout = recursionTimeoutSubsequent;
				}
				
				exports.sendRequest(data, serverUrl, "status/", 10, checkConfigExecutionRecursion);
			}, recursionTimeout);
		}
	}
};



/**
* Waits for the module to be ready.
*
* @param modules The modules object.
* @param serverUrl The Connected Vision server URL, e.g. http://localhost:2020.
* @param callback Callback function to call at the end of the function.
*/
exports.waitForModuleReady = function(modules, serverUrl, callback)
{
	var expect = require("chai").expect;
	var requestJson = require("request-json");
	var client = requestJson.createClient(serverUrl);
	
	var moduleId = Object.keys(modules)[0];
	
	var url = serverUrl + "/" + moduleId + "/status/";
	
	client.get(url, function(error, result, body)
	{
		expect(body).to.have.property("moduleStatus");
		
		if(body.moduleStatus !== "up")
		{
			setTimeout(function()
			{
				exports.waitForModuleReady(modules, serverUrl, callback);
			}, 1000);
		}
		else
		{
			callback();
		}
	});
};