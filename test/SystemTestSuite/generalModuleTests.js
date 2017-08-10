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

var clone = require("clone");
var path = require("path");
var fs = require("fs.extra");
var async = require("async");
var jsonValidator = require("is-my-json-valid")
var	expect = require("chai").expect;
var	requestJson = require("request-json");
var tools = require("./tools.js");

/**
 * perform HTTP GET request
 */
function httpRequest(
	url,		///< url to perform HTTP GET
	callback	///< callback(error, response, data)
) {
	var http = require("request");
	var buf = [];
	var response;
	
	http.get(url)
	.on("response", function(r) {
		response = r;
	})
	.on("data", function(chunk) {
		buf.push(chunk);
	})
	.on("end", function() {
		// concatenate the array of buffers to a single buffer
		var data = Buffer.concat(buf);
		if ( /^text\//gi.test(response.headers["content-type"]) ) {
			data = data.toString("utf8");
		}
			
		response.body = data;
		callback(null, response, data);
	})
	.on("error", function(error) {
		callback(error, response, {});
	})
}


/*
 * export functions to chain runner
 */
exports.init = init;
exports.load_config = load_config;
exports.send_config = send_config;
exports.delete_config = delete_config;
exports.check_config = check_config;
exports.check_configList = check_configList;
exports.reset_config = reset_config;
exports.start_config = start_config;
exports.stop_config = stop_config;

exports.check_status = check_status;
exports.wait_for_status = wait_for_status;
exports.wait = wait;

exports.check_stableResults = check_stableResults;
exports.request_last_stableResult = request_last_stableResult;
exports.verify_output_data_type = verify_output_data_type;

exports.process_reference_output = process_reference_output;
exports.outputPin_benchmark = outputPin_benchmark;
exports.benchmark = benchmark;

/**
*	init the test suite
*/
function init(
	env	///< [in/out] test environment
) {
	// load external libraries
};

/**
*	load config from file to env.config
*
*	@note using env.configEnv.file
*	@note set env.config
*/
function load_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.configEnv.file, "env.configEnv.file").to.be.not.undefined;

	// parse config
	var config;
	try {
		config = JSON.parse(fs.readFileSync(env.configEnv.file, "utf8"));
		expect(config, "failed to parse config JSON file: " + env.configEnv.file).to.be.not.undefined;
	} catch(e) {
		expect(config, "failed to parse config JSON file: " + env.configEnv.file + " error: " + e);
	}
	env.config = config;

	finishCallback();
};


/**
*	send config (env.config) to a module.
*
*	@note using env.moduleID
*	@note update env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	moduleID: ... } }
*
*/
function send_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.moduleID, "env.moduleID").to.be.not.undefined;
	expect(env.config, "env.config").to.be.not.undefined;
	
	// get local variables
	var moduleID = env.moduleID;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: {
			moduleID: moduleID,
			id: 'any'
		}
	};
	
	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;
	
	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/0/config";
	client.put(url, env.config, function(error, response, body)
	{
		// error: error object (if any)
		// response: object containing
		//		- statusCode: HTTP status code
		//		- body: HTTP plain text response
		//		- headers: HTTP headers
		//		- request: request object sent to server
		// body: response object (already decoded)

		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// update config
		env.config = response.body;
		
		// return via callback
		finishCallback();
	});
};

/**
*	check that a config exists and is equal to the loaded one
*
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	id: ... } }
*/
function check_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;

	// get local variables
	var moduleID = env.moduleID;
	var moduleURI = env.config.moduleURI;
	var configID = env.config.id;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: clone(env.config)
	};
	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/" + configID + "/config";
	client.get(url, function(error, response, body)
	{
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// return via callback
		finishCallback();
	});
};

/**
*	delete config
*
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	id: ... } }
*/
function delete_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;

	// get local variables
	var moduleID = env.moduleID;
	var moduleURI = env.config.moduleURI;
	var configID = env.config.id;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: clone(env.config)
	};
	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/" + configID + "/config";
	client.del(url, function(error, response, body) {
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// check that config does not exist any more
		check_config(env, {expectedResponse: {statusCode: 404}}, function() {
			var url = env.config.moduleURI + "/configList";
			client.get(url, function(error, response, body) {
				expect(body).not.to.include(configID);
				
				// return via callback
				finishCallback();
			});
		});
	});
};

/**
*	check that a config exists and is equal to the loaded one
*
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	id: ... } }
*/
function check_configList(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;

	// get local variables
	var moduleID = env.moduleID;
	var moduleURI = env.config.moduleURI;
	var configID = env.config.id;

	// default settings
	var expectedResponse = {
		statusCode: 200
	};
	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/configList";
	client.get(url, function(error, response, body)
	{
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		expect(body).to.include(configID);
		
		// return via callback
		finishCallback();
	});
};


/**
*	send config (env.config) to a module.
*
*	@note using env.moduleID
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	moduleID: ... } }
*/
function reset_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.moduleID, "env.moduleID").to.be.not.undefined;
	expect(env.config, "env.config").to.be.not.undefined;

	// get local variables
	var moduleID = env.moduleID;
	var moduleURI = env.config.moduleURI;
	var configID = env.config.id;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: {
			moduleID: moduleID,
			id: configID,
			status: "init"
		}
	};
	
	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/" + configID + "/control/reset";
	client.get(url, function(error, response, body)
	{
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// return via callback
		finishCallback();
	});
};

/**
*	send start command for a config
*
*	@note using env.moduleID
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	moduleID: ... } }
*/
function start_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.moduleID, "env.moduleID").to.be.not.undefined;
	expect(env.config, "env.config").to.be.not.undefined;

	// get local variables
	var moduleID = env.moduleID;
	var moduleURI = env.config.moduleURI;
	var configID = env.config.id;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: {
			moduleID: moduleID,
			id: configID
		}
	};

	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/" + configID + "/control/start";
	client.get(url, function(error, response, body)	{
		response.body = JSON.parse(response.body);
		
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// make sure that config was started
		if ( !testParams.expectedResponse )
			expect(["startup", "running", "cleanup", "finished"]).to.include(response.body.status)
		
		// return via callback
		finishCallback();
	});
};

/**
*	send stop command for a config
*
*	@note using env.moduleID
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	moduleID: ... } }
*/
function stop_config(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.moduleID, "env.moduleID").to.be.not.undefined;
	expect(env.config, "env.config").to.be.not.undefined;

	// get local variables
	var moduleID = env.moduleID;
	var moduleURI = env.config.moduleURI;
	var configID = env.config.id;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: {
			moduleID: moduleID,
			id: configID
		}
	};

	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	var client = requestJson.createClient("");
	var url = env.config.moduleURI + "/" + configID + "/control/stop";
	client.get(url, function(error, response, body)	{
		response.body = JSON.parse(response.body);
		
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// make sure that config was stopped
		if ( !testParams.expectedResponse )
			expect(["cleanup", "stopped", "finished"]).to.include(response.body.status)
		
		// return via callback
		finishCallback();
	});
};


/**
*	get and check module status
*
*	@note using env.moduleID
*	@note using env.config
*	@note using testParams.expectedResponse e.g. { statusCode: 200, body: {	moduleID: ... } }
*	@note using testParams.status e.g. { status: "running" }
*/
function check_status(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.moduleID, "env.moduleID").to.be.not.undefined;
	expect(env.config, "env.config").to.be.not.undefined;

	// default settings
	var expectedResponse = {
		statusCode: 200,
		body: {
			moduleID: env.moduleID,
			id: 'any',
			status: testParams.status || 'any' // TODO: extend with alternative options array e.g. status: ["startup", "running"]
		}
	};
	
	// parse params
	if ( testParams.expectedResponse )
		expectedResponse = testParams.expectedResponse;

	// send the config to the server
	getStatus(env.config, function(response) {
		// compare with expected response
		testObjectForExpectedProperties(response, expectedResponse, "response");
		
		// return via callback
		finishCallback();
	});
};

/**
*	wait for specific module status
*
*	@note using env.config
*	@note using testParams.status e.g. { status: "running" }
*	@note using testParams.timeout
*	@note using testParams.interval
*/
function wait_for_status(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;
	expect(testParams.status, "test parameter: status").to.be.not.undefined;
	expect(testParams.timeout, "test parameter: timeout").to.be.above(0);
	expect(testParams.interval, "test parameter: interval").to.be.above(0);
	expect(testParams.interval, "test parameter: timeout").to.be.below(testParams.timeout);

	// get local variables
	var finished = false;
	var status = "";
	
	var timeout = null;
	var interval = null;
	
	timeout = setTimeout(function (){
		// clear interval execution
		clearInterval(interval);

		// report error
		expect(status, "timeout").to.be.equal(testParams.status);
		
		// return via callback
		finishCallback();
	}, testParams.timeout);
	
	
	interval = setInterval(function (){
		// request status
		getStatus(env.config, function(response) {
			if ( !finished ) {
				status = response.body.status;
				
				// compare with expected status
				if ( status == testParams.status ) {
					finished = true;
					
					// stop requests
					clearInterval(interval);
					clearTimeout(timeout);
	
					// return via callback
					finishCallback();
				}
			}
		});
	}, testParams.interval);
}

/**
*	wait a specified time
*
*	@note using testParams.time wait-time in milliseconds
*/
function wait(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(testParams.time, "test parameter: time").to.be.above(0);

	setTimeout(function (){
		// return via callback
		finishCallback();
	}, testParams.time);
}

/**
*	check that the stable results correspond to the output pin description
*
*	@note using env.config
*	@note using env.outputDescription
*
*/
function check_stableResults(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;
	expect(env.outputDescription, "env.outputDescription").to.be.not.undefined;

	// send the config to the server
	getStatus(env.config, function(response) {
		var stableResults = response.body.stableResults;
		
		expect(stableResults).to.have.length( env.outputDescription.length );
		var outputPinIDList = [];
		for( i in env.outputDescription ) {
			outputPinIDList.push( env.outputDescription[i].id );
		}
		
		// check pin ID
		for( i in stableResults ) {
			var results = stableResults[i];
			expect(outputPinIDList).to.include(results.pinID);
			expect(results.indexEnd).to.be.at.least(results.indexStart);
			expect(results.timestampEnd).to.be.at.least(results.timestampStart);
		}
		
		// return via callback
		finishCallback();
	});
};

/**
*	checks if the data corresponding to the end index / timestamp of the stable the result count are accessible.
*
*	@note using env.config
*
*/
function request_last_stableResult(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;

	// send the config to the server
	getStatus(env.config, function(response) {
		var stableResults = response.body.stableResults;
		
		// iterate over all output pins
		var requestDataList = [];
		for( i in stableResults ) {
			var results = stableResults[i];
			
			// get by index
			if(results.indexEnd >= 0) {
				expect(results.indexEnd).to.be.at.least(results.indexStart);
				requestDataList.push({
					results: results,
					url: env.config.moduleURI + "/" + env.config.id + "/" + results.pinID + "/index/" + results.indexEnd
				});
			}
			
			// get by timestamp
			if(results.timestampEnd >= 0) {
				expect(results.timestampEnd).to.be.at.least(results.timestampStart);
				requestDataList.push({
					results: results,
					url: env.config.moduleURI + "/" + env.config.id + "/" + results.pinID + "/timestamp/" + results.timestampEnd
				});
			}

			if(results.indexEnd < 0 && results.timestampEnd < 0) {
				console.log("!!! skipping test for pin " + results.pinID + " because no stable results exist");
			}
		}
		
		function asyncRequest(data, asyncCallback) {
			httpRequest(data.url, function(error, response, body)
			{
				expect(error, "url: " + data.url).to.not.exist;
				expect(response.statusCode, "url: " + data.url + " message: " + body.error).to.equal(200);
				asyncCallback(null, true);
			});
		}
		
		async.mapSeries(requestDataList, asyncRequest, function(error, result) {
			expect(error, "async error: " + error).to.be.null;
			// return via callback
			finishCallback();
		});
	});
}

/**
*	checks that the data type of the output pins is correct
*
*	@note using env.config
*	@note using env.outputDescription
*
*/
function verify_output_data_type(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;
	expect(env.outputDescription, "env.outputDescription").to.be.not.undefined;

	// send the config to the server
	getStatus(env.config, function(response) {
		var stableResults = response.body.stableResults;

		// iterate over all output pins
		var requestDataList = [];
		for( i in stableResults ) {
			var results = stableResults[i];
			var outputDescription;
			
			// get corresponding outputPin description
			for (var j in env.outputDescription ) {
				if ( env.outputDescription[j].id == results.pinID ) {
					outputDescription = env.outputDescription[j];
					break;
				}
			}
			expect(outputDescription, "no outputDescription found for pinID: " + results.pinID).to.be.not.undefined;
			
			// add pin to request List
			if(results.indexEnd >= 0) {
				expect(results.indexEnd).to.be.at.least(results.indexStart);
				requestDataList.push({
					results: results,
					pin: outputDescription,
					url: env.config.moduleURI + "/" + env.config.id + "/" + results.pinID + "/index/" + results.indexEnd
				});
			} else {
				console.log("skipping test for pin " + results.pinID + " because no stable results exist");
			}
		}

		function asyncRequest(data, asyncCallback) {
			httpRequest(data.url, function(error, response, body)
			{
				expect(error, "url: " + data.url).to.not.exist;
				expect(response.statusCode, "url: " + data.url + " message: " + body.error).to.equal(200);
				
				// test MIME type
				expect(response.headers["content-type"], "type").to.equal(data.pin.type);
				
				// check content
				if ( data.pin.type === "application/json" || data.pin.type === "application/javascript" ) {
					var schemaCheck = jsonValidator({
						  required: true,
						  type: "object",
						  properties: data.pin.properties
						});
					var json = JSON.parse(body);

					if ( schemaCheck(json) == false ) {
						console.log("schemaCheck for: " + data.url);
						console.log(schemaCheck.errors);
						expect( schemaCheck(json) ).to.be.ok;
					}
				}
				
				asyncCallback(null, true);
			});
		}
		
		async.mapSeries(requestDataList, asyncRequest, function(error, result) {
			expect(error, "async error: " + error).to.be.null;
			// return via callback
			finishCallback();
		});
	});
}


/**
*	checks that the computed output is equal to the reference data
*
*	If no reference data are available, they will be created.
*
*	testParams:
*		- customTests: custom comparison for each pin (optional)
*			{
*				"pinID": {
*					compareFunction: myFunction // function(dataCurrent, dataReference, url, pinID, pinType, compareParams)
*													-> return true on success
*		 			compareParams: {...}
*				}
*			}
*
*	@note using env.config
*	@note using env.configEnv.file
*	@note using env.outputDescription
*	@note using customTests
*
*/
function process_reference_output(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;
	expect(env.configEnv.file, "env.configEnv.file").to.be.not.undefined;
	expect(env.outputDescription, "env.outputDescription").to.be.not.undefined;

	// set config specific paths
	// e.g. config.file: "c:\modules\<module>\test\<config>\config.json" -> "c:\modules\<module>\test\<config>"
	var configDir = path.join(env.configEnv.file, "..");
	// -> "c:\modules\<module>\test\<config>\output"
	var outputDir = path.join(configDir, "outputNew");
	// -> "c:\modules\<module>\test\<config>\output\reference"
	var referenceDir = path.join(outputDir, "reference");
	// -> "c:\modules\<module>\test\<config>\output\recent"
	var recentDir = path.join(outputDir, "recent");
	
	// init output paths
	var outputPins = {};
	
	// iterate over all output pins
	for( var i in env.outputDescription ) {
		var outputDescription = env.outputDescription[i];
		var pinID = outputDescription.id;

		outputPin = {
			pinID: pinID
		}
		
		// set pin specific paths
		// -> "c:\modules\<module>\test\<config>\output\reference\<pinId>"
		var referencePinDir = path.join(referenceDir, pinID);
		outputPin.referencePinDir = referencePinDir;
		// -> "c:\modules\<module>\test\<config>\output\recent\<pinId>"
		var recentPinDir = path.join(recentDir, pinID);
		outputPin.recentPinDir = recentPinDir;
		
		// do we have to generate reference data?
		var referenceGenerationFlag = true;
		if ( fs.existsSync(path.join(referencePinDir, "index")) ) {
			// reference directory and data exists for getByIndex requests
// TODO check if directory is not empty -> referenceGenerationFlag = false;
			referenceGenerationFlag = false;
		} else if( fs.existsSync(path.join(referencePinDir, "timestamp")) ) {
			// reference directory and data exists for getByTimestamp requests
// TODO check if directory is not empty -> referenceGenerationFlag = false;
			referenceGenerationFlag = false;
		}
		
		// if the recent data pin directory from a preceding execution of the test exists, then delete it
		fs.removeSync(recentPinDir);
		
		// get output data range
		// TODO get data range (read range.json) and set accessorType
//			var range = tools.getOutputPinAccessorValueRange(referencePinDir, pinID, status, outputDir, referenceGenerationFlag);
		var accessorType = "index";
		outputPin.valueInc = 1; // TODO increase value depending on accessor type???
		outputPin.accessorType = accessorType;
		outputPin.accessorUrl = env.config.moduleURI + "/" + env.config.id + "/" + pinID + "/" + accessorType + "/";
			
		// -> "c:\modules\<module>\test\<config>\output\reference\<pinId>\<accessor>
		var referenceAccessorDir = path.join(referencePinDir, accessorType);
		outputPin.referenceAccessorDir = referenceAccessorDir;
		if ( !fs.existsSync(referenceAccessorDir) ) {
			referenceGenerationFlag = true;
			// create reference directory
			fs.mkdirpSync(referenceAccessorDir);
		}
		// -> "c:\modules\<module>\test\<config>\output\recent\<pinId>\<accessor>
		var recentAccessorDir = path.join(recentPinDir, accessorType);
		outputPin.recentAccessorDir = recentAccessorDir;
		if ( !fs.existsSync(recentAccessorDir) ) {
			// create recent data directory
			fs.mkdirpSync(recentAccessorDir);
		}
		
		// file handling
		outputPin.filemeta = getFileMetadataFromContentType(outputDescription.type);

		// use the build-in compare function as default settings
		if ( !outputPin.compareFunction ) {
			outputPin.compareFunction = tools.compareData;
			outputPin.compareParams = {};	// TODO add excludedProperties to compareParams
			excludedProperties = false;
		}
		
		// overwrite compare function if a user-defined, custom comparison method is defined
		if( testParams.customTests ) {
			if( testParams.customTests[pinID] ) {
				if( testParams.customTests[pinID].compareFunction ) {
					// set compare function
					var compareFunction = testParams.customTests[pinID].compareFunction;
					expect( typeof env.customTests[compareFunction] === "function", "custom compare function: " + compareFunction).to.be.ok;
					outputPin.compareFunction = env.customTests[compareFunction];
				}
				if( testParams.customTests[pinID].compareParams ) {
					// set compare parametest
					outputPin.compareParams = testParams.customTests[pinID].compareParams;
				}
			}
		}
		
		// push to output pin list
		outputPins[pinID] = outputPin;
	}
		
	processReferenceOutputRecursive(env.config, outputPins, referenceGenerationFlag, finishCallback);

}


/**
* Processes the reference output data.
* If the data does not exist, it generates it, otherwise it compares it with the current
* data returned by the module.
* The method is called recursively to deal with running chains where new results are
* being computed while querying the pin for existing results.
*
*/
function processReferenceOutputRecursive(
		config, 		///< current config
		outputPins, 	///< paths of output pins
		referenceGenerationFlag,  			///< True if data does not exist and needs to be created, otherwise false (data needs to be compared).
		finishCallback	///< Callback function to call at the end of the function.
) {
	var outputPinRequests = {};
	var stopFlag = true;

	getStatus(config, function(response) {
		status = response.body;
		// iterate over all output pins and create requests
		for( var i in status.stableResults ) {
			var pinID = status.stableResults[i].pinID;
			
			// skip the current pin if it does not have at least the referenceAccessorDir property
			// which is the case when no reference data is supposed to be processed
			if( !outputPins[pinID].referenceAccessorDir ) {
				continue;
			}
	
			// determine the last successfully processed accessor value
			accessorValue = outputPins[pinID].accessorValue || 0;
			
			// build actual request data list
			var requests = [];
			if ( outputPins[pinID].accessorType == "index" ) {
				if ( accessorValue < status.stableResults[i].indexStart )
					accessorValue = status.stableResults[i].indexStart;
				for (; accessorValue <= status.stableResults[i].indexEnd; accessorValue += outputPins[pinID].valueInc) {
					var req = clone(outputPins[pinID]);
					req.url = outputPins[pinID].accessorUrl + accessorValue;
					req.filename = accessorValue + "." + outputPins[pinID].filemeta.extension;
					requests.push(req);
				}
			} else {
				// TODO accessorType by timestamp
				expect(false,"unsupported accessor type: " + outputPins[pinID].accessorType).to.be.ok;
			}
	
			if ( outputPins[pinID].accessorValue != accessorValue ) {
				outputPins[pinID].accessorValue == accessorValue;
				stopFlag = false;
			}
			outputPinRequests[pinID] = requests;
		}
		
		// stop when there are no more requests
		if(stopFlag) {
			callback();
			return;
		}
	
		// interleave the requests of the pins
		// this is done for modules which use a ring buffer and not a database for the output data
		// when using ring buffers, accessor values close to the accessor start value are likely to
		// get removed from the ring buffer sooner than values closer to the accessor end value
		// process the ring buffer values closer to the start for all pins before proceeding to the
		// values closer to the end e.g. [[pin_A_index_0, pin_A_index_1, ...], [pin_B_index_3, pin_B_index_4, ...]]
		// -> [pin_A_index_0, pin_B_index_3, pin_A_index_1, pin_B_index_4, ...]
		// ATTENTION: this may only work for cases where all start values are within an interval with
		// its size being a fraction of the ringbuffer size
		var interleavedRequests = [];
		var pinIDs = Object.keys(outputPinRequests);
		var i = 0;
		while (true) {
			var lenOld = interleavedRequests.length;
			for (var pinID in outputPinRequests) {
				var r = outputPinRequests[pinID];
				if ( r.length > i )
					interleavedRequests.push( r[i] );
			}
			if ( interleavedRequests.length == lenOld )
				break;
			i++;
		}
		
		// console.log("processing " + requests.length + " requests ...");
	
		/**
		 * performs a request to an output pin and compares the data with the reference data
		 * or generates a reference output
		 */
		function asyncRequest(
			request,		///< request and comparison object
			asyncCallback	///< finish callback
		) {
			httpRequest(request.url, function(error, response, data) {
				expect(error, "url: " + request.url).to.not.exist;
				expect(response.statusCode, "url: " + request.url + " message: " + request.error).to.equal(200);
				
				// save data to disk
				try	{
					// write recent output data
					var fullpath = path.join(request.recentAccessorDir, request.filename);
					fs.writeFileSync(fullpath, data, request.filemeta.encoding);
					
					if ( referenceGenerationFlag ) {
						// generate reference
						var fullpath = path.join(request.referenceAccessorDir, request.filename);
						fs.writeFileSync(fullpath, data, request.filemeta.encoding);
					}
				} catch(e) {
					expect(e, " error when trying to write recent data file " + recentDataFile + " message: " + e).to.be.undefined;
				}
	
				if ( !referenceGenerationFlag ) {
					// load reference data from file
					var referenceData;
					try	{
						var fullpath = path.join(request.referenceAccessorDir, request.filename);
						referenceData = fs.readFileSync(fullpath, request.filemeta.encoding);
					} catch(e) {
						expect(e, " error when trying to read reference data file " + referenceFile + " message: " + e).to.be.undefined;
					}
					
					// compare with reference
					expect( request.compareFunction(data, referenceData, request.url, request.pinID, request.filemeta.contentType, request.compareParams) ).to.be.ok;
				}

				// next
				asyncCallback();
			})
		};
		
		// do actual requests
		async.mapSeries(interleavedRequests, asyncRequest, function(error, result) {
			expect(error, "async error: " + error).to.be.null;
			// return via callback
			finishCallback();
		});
	});
}


/**
*	benchmark a given test
*
*	@note using env.generalModuleTests
*	@note using testParams.test test to be benchmarked
*	@note using testParams.testParams for test to be benchmarked
*	@note using testParams.repeat
*	@note using testParams.avgRuntime
*/
function benchmark(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.generalModuleTests, "env.generalModuleTests").to.be.not.empty;
	expect(testParams.repeat, "test parameter: repeat").to.be.above(0);
	expect(testParams.test, "test parameter: test").to.be.not.undefined;

	// get local variables
	var remaining = testParams.repeat;
	var testName = testParams.test;
	expect(env.generalModuleTests, "test \"" + testName + "\" specified in benchmark does not exist").to.have.property(testName);
	var test = env.generalModuleTests[testName];
	var startTime = 0;
	var testEnv = clone(env);
	var subTestParams = testParams.testParams || {};
	
	function benchmark_test_clousure() {
		if ( remaining > 0 ) {
			remaining--;
			
			// call test function recursively
			test(testEnv, subTestParams, benchmark_test_clousure);
		} else {
			// stop measurement
			var duration = process.hrtime(startTime);
			var avgRuntime = (duration[0] + duration[1] * 1e-9) / testParams.repeat *1000;
			console.log( testName + " - average runtime: " + (avgRuntime).toFixed(1) + " ms");
			if ( testParams.avgRuntime )
				expect(avgRuntime, "average runtime of " + testName).to.be.most(testParams.avgRuntime);
			
			// return via callback
			finishCallback();
		}
	};

	// start measurement
	startTime = process.hrtime();
	benchmark_test_clousure();
};

/**
*	Benchmarks the average duration of ouput pin data queries.
*
*	@note using env.config
*	@note using testParams.repeat
*	@note using testParams.avgRuntime as object with pinID as key in milliseconds e.g. { MetaDataPin: 10, PNG-Image: 200 }
*/
function outputPin_benchmark(
	env, 			///< test environment
	testParams,		///< test specific parameter
	finishCallback	///< function to be called when test has finished
) {
	expect(env.config, "env.config").to.be.not.undefined;
	expect(testParams.repeat, "test parameter: repeat").to.be.above(0);

	getStatus(env.config, function(response) {
		function asyncBenchmark(results, asyncCallback) {
			
			// check that we have some results
			if(results.indexEnd < 0 && results.timestampEnd < 0) {
				console.log("!!! skipping test for pin " + results.pinID + " because no stable results exist");

				if ( testParams.avgRuntime && testParams.avgRuntime[results.pinID])
					expect(avgRuntime, "average runtime of " + results.pinID).to.be.most(testParams.avgRuntime[results.pinID]);
				
				// return via callback
				asyncCallback();
				return;
			}
			
			
			// local variables
			var remaining = testParams.repeat;
			var startTime = 0;

			function benchmark_test_clousure() {
				if ( remaining > 0 ) {
					remaining--;
					
					// request data
					var accessorValue = results.indexStart + Math.floor((Math.random()/2+0.5) * (results.indexEnd - results.indexStart));
					var url = env.config.moduleURI + "/" + env.config.id + "/" + results.pinID + "/index/" + accessorValue;
					
					httpRequest(url, function(error, response, body) {
						expect(error, "url: " + url).to.not.exist;
						expect(response.statusCode, "url: " + url + " message: " + body.error).to.equal(200);
	
						// next iteration
						benchmark_test_clousure();
					});
				} else {
					// stop measurement
					var duration = process.hrtime(startTime);
					var avgRuntime = (duration[0] + duration[1] * 1e-9) / testParams.repeat *1000;
					console.log( results.pinID + " by index - average runtime: " + (avgRuntime).toFixed(1) + " ms");
					if ( testParams.avgRuntime && testParams.avgRuntime[results.pinID])
						expect(avgRuntime, "average runtime of " + results.pinID).to.be.most(testParams.avgRuntime[results.pinID]);
					
					// return via callback
					asyncCallback();
					return;
				}
			};
		
			// start measurement
			startTime = process.hrtime();
			benchmark_test_clousure();
		}
		
		async.mapSeries(response.body.stableResults, asyncBenchmark, function(error, result) {
			expect(error, "async error: " + error).to.be.null;
			// return via callback
			finishCallback();
		});
		
	});

};

function testObjectForExpectedProperties(testObj, expectedObj, scope) {
	scope = scope || "";

	if ( typeof testObj === "string" )
		testObj = JSON.parse(testObj);
	
	for (var key in expectedObj) {
		var expectedVal = expectedObj[key];
				
		if ( expectedVal === null ) {
			// should not exists
			expect( testObj, scope ).to.not.have.property( key );
		} else if ( expectedVal === 'any' ) {
			// should not exists
			expect( testObj, scope ).to.have.property( key );
		} else if ( typeof expectedVal === "object" ) {
			// check if property exists
			expect( testObj, scope ).to.have.property( key );
			testObjectForExpectedProperties(testObj[key], expectedVal, scope + "." + key)
		} else {
			// check value
			expect( testObj, scope ).to.have.property( key );
			expect( testObj[key], "error when checking " + scope + "." + key + "\n" + "object:" + "\n" + JSON.stringify(testObj, null, "\t") ).to.equal( expectedVal );
		}
	}
}

function getStatus(
	config,		///< config
	callback	///< callback function returning status
){
	var client = requestJson.createClient("");
	var url = config.moduleURI + "/" + config.id + "/status";
	client.get(url, function(error, response, body)	{
		response.body = JSON.parse(response.body);
		callback(response);
	});
}

/**
 * get metadata for a file by its content / MIME type
 *	- extension (e.g. json, png, ...)
 *	- encoding (binary, utf8)
 */
function getFileMetadataFromContentType(
	contentType	///< content / MIME type of data
) {
	var meta = {
		contentType: contentType
	};
	
	// determine encoding
	if ( RegExp("^text\/", "gi").test(contentType) )
		meta.encoding = "utf8";
	else
		meta.encoding = "binary";
	
	meta.extension = "dat";
	
	// determine extension
	if( contentType == "application/json" )
	{
		meta.extension = "json";
	} else if( contentType == "application/javascript" ) {
		meta.extension = "js";
	} else if(contentType && contentType.length > 0) {
		// determine the file extension based on the module output description pin type using the string after the last forward slash character e.g. "image/jpeg" -> "jpeg"
		var result = RegExp("[^\/]+$", "gi").exec(contentType);
		
		if(result && result.length > 0)
		{
			meta.extension = result[0];
		}
	}
	
	return meta;
}
