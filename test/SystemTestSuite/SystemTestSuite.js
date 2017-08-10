/**
* This test suite for the Connected Vision framework and its modules is used for a wide range of tests.
* Amongst others, these tests cover server startup, server responding to requests, setup of configs,
* starting, running and finishing of configs, matching output data description to the actual returned
* data types, creating referance data, checking the reference data to the current data, conducting
* user-specified output data comparison methods, deleting chains and stopping the server.
*/

const joe = require("joe");

joe.setReporter(new (require("joe-reporter-console"))());

joe.describe("CV", function(describe, it)
{
	var clone = require("clone");
	var diff = require("deep-diff");
	var expect = require("chai").expect;
	var extend = require("node.extend");
	var fs = require("fs");
	
	var tools = require("./Tools.js");
	var generalModuleTests = require("./generalModuleTests.js");
	var suiteConfigGlobal = null;
	var server = null;
	var modules = null;

	
	
	describe("server", function(describe, it)
	{
		it("check test suite config", function()
		{
			suiteConfigGlobal = tools.loadTestSuiteConfig();
			suiteConfigGlobal = tools.checkTestSuiteConfig(suiteConfigGlobal);
		});
		
		
		
		it("start", function(done)
		{
			tools.startServer(suiteConfigGlobal, serverStartedCallback);
			
			function serverStartedCallback(data)
			{
				server = data;
				done();
			}
		});
		
		
		
		it("answer is-alive request", function(done)
		{
			// give the server some time for starting up before trying to send any requests
			setTimeout(function()
			{
				tools.isServerAlive(suiteConfigGlobal.serverUrl, done);
			}, 5000);
		});
		
		
		
		it("obtain modules", function(done)
		{
			tools.getModules(suiteConfigGlobal.modulesDir, suiteConfigGlobal.serverUrl, getModulesCallback);
			
			function getModulesCallback(data)
			{
				modules = data;
				done();
			}
		});
	});
	
	
	
	describe("modules", function(describe, it)
	{
		var path = require("path");
		
		Object.keys(modules).forEach(function(moduleId, iModule)
		{
			describe(tools.shortenString(moduleId, 10), function(describe, it)
			{
				var mods = {};
				mods[moduleId] = modules[moduleId];
				
				var suiteConfigModule;
				var suiteConfigModuleFilePath = path.join(mods[moduleId].dir, "test", "config.joe.json")
				
				// load the possibly existing module-specific test suite config and merge it with the global one
				if(fs.existsSync(suiteConfigModuleFilePath))
				{
					suiteConfigModule = tools.loadTestSuiteConfig(suiteConfigModuleFilePath)
					
					// check if there are properties in the module-specific test suite config which do not exist in the global one excluding the tests array which is expected to contain items which are not present in the global test suite
					var suiteConfigGlobalWithoutCustomTests = clone(suiteConfigGlobal);
					suiteConfigGlobalWithoutCustomTests.tests = [];
					
					var suiteConfigModuleWithoutCustomTests = clone(suiteConfigModule);
					suiteConfigModuleWithoutCustomTests.tests = [];
					
					var result = diff(suiteConfigGlobalWithoutCustomTests, suiteConfigModuleWithoutCustomTests);
					
					result.forEach(function(diffItem, iDiff)
					{
						expect(diffItem.kind, "the module-specific test suite config contains properties which are not in the global test suite config: " + diffItem.path).not.to.equal("N");
					});
					
					var tests = suiteConfigModule.tests;
					
					suiteConfigModule = extend(true, suiteConfigGlobalWithoutCustomTests, suiteConfigModuleWithoutCustomTests);
					
					if(suiteConfigModule.hasOwnProperty("tests"))
					{
						suiteConfigModule.tests = tests;
					}
					
					suiteConfigModule = tools.checkTestSuiteConfig(suiteConfigModule);
				}
				else
				{
					suiteConfigModule = clone(suiteConfigGlobal);
				}
				
				
				
				it("wait for module ready status", function(done)
				{
					tools.waitForModuleReady(mods, suiteConfigModule.serverUrl, done)
				});
				
				
				
				it("obtain module output descriptions", function(done)
				{
					tools.getOutputDescription(mods, suiteConfigModule.serverUrl, done);
				});
				
				var env = {};
				
				mods[moduleId].configs.forEach(function(moduleConfig, iConfig)
				{
					var dirPath = path.join(moduleConfig.file, "..");
					var configName = tools.shortenString(path.basename(dirPath), 10);
					
					describe(configName, function(describe, it)
					{
						var m = {};
						m[moduleId] = mods[moduleId];
						m[moduleId].configs = [moduleConfig];
						env.modules = m;
						
						// reset the possibly altered (by preceding loop iteration) test suite config
						var suiteConfigModuleConfig;
						var testConfigName = path.basename(path.join(mods[moduleId].configs[0].file, ".."));
						var suiteConfigModuleConfigFilePath = path.join(mods[moduleId].dir, "test", testConfigName, "config.joe.json");
						
						// load the possibly existing module-config-specific test suite config and merge it with the module-specific one
						if(fs.existsSync(suiteConfigModuleConfigFilePath))
						{
							var suiteConfigModuleConfig = tools.loadTestSuiteConfig(suiteConfigModuleConfigFilePath)
							
							// check if there are properties in the module-config-specific test suite config which do not exist in the module-specific one excluding the tests array which is expected to contain items which are not present in the module-specific test suite
							var suiteConfigModuleWithoutCustomTests = clone(suiteConfigModule);
							suiteConfigModuleWithoutCustomTests.tests = [];
							
							var suiteConfigModuleConfigWithoutCustomTests = clone(suiteConfigModuleConfig);
							suiteConfigModuleConfigWithoutCustomTests.tests = [];
							
							var result = diff(suiteConfigModuleWithoutCustomTests, suiteConfigModuleConfigWithoutCustomTests);
							
							result.forEach(function(diffItem, iDiff)
							{
								expect(diffItem.kind, "the module-config-specific test suite config contains properties which are not in the module-specific test suite config: " + diffItem.path).not.to.equal("N");
							});
							
							var tests = suiteConfigModuleConfig.tests;
							
							suiteConfigModuleConfig = extend(true, suiteConfigModuleWithoutCustomTests, suiteConfigModuleConfigWithoutCustomTests);
							
							if(suiteConfigModuleConfig.hasOwnProperty("tests"))
							{
								suiteConfigModuleConfig.tests = tests;
							}
							
							suiteConfigModuleConfig = tools.checkTestSuiteConfig(suiteConfigModuleConfig);
						}
						else
						{
							suiteConfigModuleConfig = clone(suiteConfigModule);
						}
						
						// set test environment
						var testEnv = {
							configEnv: clone(env.modules[moduleId].configs[0]),
							inputDescription: clone(modules[moduleId].inputDescription),
							outputDescription: clone(modules[moduleId].outputDescription),
							moduleID: clone(moduleId)
						};

						// add build-in module test to environment
						testEnv.generalModuleTests = generalModuleTests;
						
						// setup build-in module test
						generalModuleTests.init(testEnv);

						// setup custom tests
						testEnv.customTests = m[moduleId].customTests;
						if ( m[moduleId].customTests && m[moduleId].customTests.init ) {
							m[moduleId].customTests.init(testEnv);
						}


						// run all tests
						suiteConfigModuleConfig.tests.forEach(function(test, iTest)
						{
							var testName = Object.keys(test)[0];
							var testParams = clone(suiteConfigModuleConfig.tests[iTest][testName]);
							if ( !testParams.name )
								testParams.name = testName.split('_').join(' ')
							
							if ( typeof generalModuleTests[testName] === "function") {
								// build-in module test
								
								it(testParams.name, function(done) {
									generalModuleTests[testName](testEnv, testParams, done);
								});
								
							} else {
								// old style build-in module test
								switch(testName)
								{
									case "setup":
										it("set up", function(done)
										{
											tools.setUpConfig(m, suiteConfigModuleConfig.serverUrl, done);
										});
										break;

									
									case "statusBenchmark":
										it("benchmark status requests", function(done)
										{
											tools.benchmarkStatusRequests(m, suiteConfigModuleConfig.serverUrl, suiteConfigModuleConfig.tests[iTest][testName].requests, done);
										});
										break;
									
									
									case "startConfig":
										it("start config", function(done)
										{
											tools.startConfig(m, suiteConfigModuleConfig.serverUrl, done);
										});
										break;
										
										
									case "checkConfigExecution":
										it("check config execution", function(done)
										{
											tools.checkConfigExecution(m, suiteConfigModuleConfig.serverUrl, suiteConfigModuleConfig.tests[iTest][testName].criteria, done)
										});
										break;
									
									
									case "checkLastStableResults":
										it("check last stable result existence", function(done)
										{
											tools.checkResultCount(m, suiteConfigModuleConfig.serverUrl, done);
										});
										break;
									
									
									case "verifyOutputDataType":
										it("verify output data type", function(done)
										{
											tools.checkOutputDataTypes(m, suiteConfigModuleConfig.serverUrl, done);
										});
										break;
									
									
									case "processReferenceOutput":
										it("process reference output", function(done)
										{
											tools.processReferenceOutput(m, suiteConfigModuleConfig.architecture, suiteConfigModuleConfig.serverUrl, done);
										});
										break;
									
									
									case "outputPinBenchmark":
										it("benchmark output pin requests", function(done)
										{
											tools.benchmarkOutputPinRequests(m, suiteConfigModuleConfig.serverUrl, suiteConfigModuleConfig.tests[iTest][testName].requests, done);
										});
										break;
									
									
									case "stopConfig":
										it("stop config", function(done)
										{
											tools.stopConfig(m, suiteConfigModuleConfig.serverUrl, done);
										});
										break;
									
									
									case "deleteConfig":
										it("delete config", function(done)
										{
											tools.deleteConfigs(m, suiteConfigModuleConfig.serverUrl, done);
										});
										break;
									
									default:
										// custom module test
										expect(m[moduleId].customTests, "custom test \"" + testName + "\" specified in test suite config does not exist in module-specific test.js file").to.have.property(testName);
										
										it(testName, function(done)
										{
											m[moduleId].customTests[testName](testEnv, testParams, done);
										});
										break;
								}
							}
						});
					});
				});
			});
		});
	});
	
	
	
	describe("server", function(describe, it)
	{
		it("stop", function(done)
		{
			expect(server, "Connected Vision server instance is not initialized").to.be.not.null;
			expect(server.pid, "Connected Vision server instance is not running (pid: " + server.pid + ")").to.not.equal(0);
			
			// define the exit callback to check the success of the server termination
			server.on("exit", function(code)
			{
				done();
			});
			
			// stop the server by sending the enter/return key as input
			server.stdin.write("\n");
		});
	});
});