/******************************************************
** Output Data Recorder GUI
**
** written by Michael Rauter in 2014
** 
**
*/

/** \mainpage
*
*	Output Data Recorder GUI for Connected Vision Modules
*	supports both live modules and offline modules via two recording modes
*
*	file: OutputDataRecorder.js
*
*	\author Michael Rauter
*
*
*	\version 1.0
*
*
*	\b Purpose: \n 
*	One can dock onto every compatible Connected Vision module hosted by a Connected Vision Server and record this module's data (export files to disk)\n
*	\n\n
*/

//"use strict";

/* 
 * constant
 */
var RECORDINGMODE_LIVE_MODE = "LIVEMODE";
var RECORDINGMODE_OFFLINE_MODE = "OFFLINEMODE";
var recordingMode; // selected recording mode

var LIVE_RECORDING_RATE_IN_HZ_SPINNER_MIN_VALUE = 0;
var LIVE_RECORDING_RATE_IN_HZ_SPINNER_MAX_VALUE = 60;
var LIVE_RECORDING_RATE_IN_HZ_SPINNER_DEFAULT_VALUE = 0;

/*
 * global variables
 */
var viewModel = createViewModel();

var configsCreatedFileExportModules = []; // file export configs created (one config is created for every selected output pin)
var sendQueueConfigsFileExportModules = []; // queue for file export config creation via IFrame mechanism (workaround for same origin policy)
var listConfigsPreStatus = []; // list with status of first attached config in chain of file export configs (they are checked if they (already existed and) were running prior to creating them in this GUI)
var listConfigsRecordingInfo = []; // info used for recording, e.g. accessor type for request
var listConfigsCurrentInfo = []; // updated on regular basis (when recording a new data element) - used for e.g. stableResults
var lastRequestedQualifierValue = -1; // last requested qualifier value (timestamp or index) - prevent double exports


/**
 * this function maps a tabID to a recording mode
 * @param tabID tab ID to be mapped
 * @returns recording mode
 */
function mapTabIdToRecordingMode(tabId)
{
	var mode;	
    if (tabId == "tab-id-recordingLiveMode")
    {
    	mode = RECORDINGMODE_LIVE_MODE;
    }
    else if (tabId == "tab-id-recordingOfflineMode")
    {
    	mode = RECORDINGMODE_OFFLINE_MODE;
    }
    //alert(mode);
	return mode;
}

/**
 * log message to debug output
 * 
 * @param msg	message to be logged
 */
function logDebug(msg) {
/* debug output is disabled
	if ( !viewModel )
		return;
	var date = new Date();
	viewModel.messages( viewModel.messages() + "<li><b>" + date.toLocaleTimeString() + ":</b> " + msg + "</li>" );
*/
}

/**
 * create viewModel for knockout.js
 * 
 * @returns viewModel
 */
function createViewModel() {
	var viewModel = {};
	
	/*
	 * global section
	 */
	
	viewModel.toolsVisible = ko.observable(true);
	
	viewModel.hostUrl = ko.observable("http://localhost:2020/"); // hostUrl of Connected Vision Server
	
	viewModel.moduleList = ko.mapping.fromJS([]); // will hold list of available modules
	
	viewModel.isPresentFileExportModule = ko.observable(true); // will be set to true if the File Export module was found on the server (this GUI needs the File Export module to be running on the Connected Vision Server to do anything useful)
	
	// structure that will hold information about the selected module of interest
	viewModel.selectedModuleOfInterest = {};
	viewModel.selectedModuleOfInterest.obj = ko.observable(); // selection of drop down list of list of modules
	
	// url of the selected module of interest (will automatically resolve localhost to local ip adress)
	viewModel.selectedModuleOfInterest.url = ko.computed(function() {
		if (this.selectedModuleOfInterest.obj())
		{
			return this.selectedModuleOfInterest.obj().uri();
		}
		else return "please select module!";
    }, viewModel);
	
	// helper function to update list of available modules
	viewModel.updateModuleList = function() {
		viewModel.moduleList([]);
		$.ajax({ 
			url: viewModel.hostUrl() + "_moduleList_",
			dataType: "jsonp",
			success: function( moduleList ) {
				var isPresentFileExportModule = false;
				for ( var i = 0; i < moduleList.length; ++i) {
					if (moduleList[i].name == "FileExport") // do not allow File Export module to appear in list of modules
					{
						moduleList.splice(i,1); // remove it from list of modules
						isPresentFileExportModule = true;
					}									
				}
				ko.mapping.fromJS(moduleList, viewModel.moduleList);
				viewModel.isPresentFileExportModule(isPresentFileExportModule);
			},
			error: function(error) {
				alert(error);
			}
		});	
	};
	
	// helper (wrapper) function (== callback of "use"-button next to host URL line edit) - one could directly call updateModuleList, but i wanted to make clear that it is the callback for the button
	viewModel.useSpecifiedHostURL = function() {
		viewModel.updateModuleList();
	};
	viewModel.hostUrl.subscribe( viewModel.useSpecifiedHostURL ); // subscribe to function useSpecifiedHostURL() -> so that a lost focus in the line edit updates the module list
	
	
	viewModel.selectedModuleOfInterest.selectedConfig = {};
	// currently obj representing selected config from list of configs of module of interest - it is also not really necessary to make this a element inside a structure, but i decided to do so to make it clear that .obj is the knockout connection object
	viewModel.selectedModuleOfInterest.selectedConfig.obj = ko.observable();
	
	viewModel.selectedModuleOfInterest.config = undefined; // config info of selected config
	
	// list of available configs (configsChains)
	viewModel.selectedModuleOfInterest.configList = ko.observableArray();
	
	// helper function to load available configs from module of interest
	viewModel.selectedModuleOfInterest.updateConfigList = function() {
		viewModel.selectedModuleOfInterest.configList([]);
		viewModel.selectedModuleOfInterest.selectedConfig.obj(false);
		
		// protection for callback invocations arising from knockout observables being
		// updated but not ready, e.g. array of modules being cleared - cannot be prevented
		// but we can detect it and return from callback immediately
		if (!viewModel.selectedModuleOfInterest.obj())
		{
			return;
		}
		var url = viewModel.selectedModuleOfInterest.obj().uri() + "/configList";
		logDebug("request config list (" + url + ")");
		
		// two step process
		// step1: get list of configIDs -> put into data
		$.ajax({
			url: url,
			dataType: "jsonp",
			success: function( data ) { // list of configIDs is inside data
				// step2: try to load configs for all configIDs
				for ( var i = 0; i < data.length; ++i) {

					// load config for ID
					$.ajax({
						url: viewModel.selectedModuleOfInterest.obj().uri() + "/" + data[i] +"/config", 
						dataType: "jsonp", 
						success: function( config ) {						
							// compute enhanced name to be displayed -> "name - ID"
							config.displayName = config.name + " - " + config.id;
							// append new config
							viewModel.selectedModuleOfInterest.configList.push( config );
						}
					});
				}
			},
			error: function( error ) {
				// cannot load config ID list
				alert("cannot update config list");
			}
		});
    };
    // whenever selection of module of interest changes, update config list
    viewModel.selectedModuleOfInterest.obj.subscribe( viewModel.selectedModuleOfInterest.updateConfigList );
	
    // available output pins for module of interest 
	viewModel.selectedModuleOfInterest.availableOutputpinList = ko.observableArray();
	
	// number of outputpins selected (= number of checkboxes checked)
	viewModel.numOutputpinsSelected = ko.observable(0);
    
	// helper function to update list of available output pins
    viewModel.selectedModuleOfInterest.updateAvailableOutputpinList = function() {
		viewModel.selectedModuleOfInterest.availableOutputpinList([]);
		
		// protection for callback invocations arising from knockout observables being
		// updated but not ready, e.g. array of modules being cleared - cannot be prevented
		// but we can detect it and return from callback immediately
		if (!viewModel.selectedModuleOfInterest.obj())
		{
			return;
		}
		
		var url = viewModel.selectedModuleOfInterest.url() + "/outputDescription";
		
		logDebug("request outputpin list (" + url + ")");
		$.ajax({ 
			url: url,
			dataType: "jsonp",
			success: function( outputDescription ) {			
				for ( var i = 0; i < outputDescription.length; ++i) {
					// element will hold complete output descriptions as well as additional information e.g. checked state (isChecked)
					var element = ko.mapping.fromJS(outputDescription[i]);
					element.isChecked = ko.observable(false);
					element.isChecked.subscribe( updateNumOutputpinsSelected ); // subscribe to isChecked element -> update number of selected outputpins
					element.filepathFormatString = ko.observable(""); // filepath format string - will be filled later on
					
					viewModel.selectedModuleOfInterest.availableOutputpinList.push( element );
				}
			},
			error: function( error ) {
				alert("cannot update outputpin list");
			}
		});
		
	};
	// whenever selection of module of interest changes, update available outputpin list
	viewModel.selectedModuleOfInterest.obj.subscribe( viewModel.selectedModuleOfInterest.updateAvailableOutputpinList );	
	
	// helper function - callback config list selection made
    viewModel.selectedModuleOfInterest.configItemSelected = function() {
		viewModel.selectedModuleOfInterest.config = undefined;
		// get config of selected config from configList
		for ( var i = 0; i < viewModel.selectedModuleOfInterest.configList().length; ++i)
		{
			if (viewModel.selectedModuleOfInterest.configList()[i].id == viewModel.selectedModuleOfInterest.selectedConfig.obj().id) 
			{
				viewModel.selectedModuleOfInterest.config = viewModel.selectedModuleOfInterest.configList()[i];		
			}
		}
		
		if (viewModel.selectedModuleOfInterest.config != undefined)
		{
			// set filepath config string for all available outputpins
			for ( var i = 0; i < viewModel.selectedModuleOfInterest.availableOutputpinList().length; ++i)
			{
				var element = viewModel.selectedModuleOfInterest.availableOutputpinList()[i];
				var filepathFormatString = "../../../data/export/[year]_[month]_[day]/";
				filepathFormatString += viewModel.selectedModuleOfInterest.obj().name() + "/" + viewModel.selectedModuleOfInterest.selectedConfig.obj().id + "/";
				filepathFormatString += element.name() + "/" /*+ element.name() + "_"*/ + "[uniqueRunningIndex.8]_[timestamp][index][identifier]";
				
				switch(element.type())
				{
					case "image/png":
						filepathFormatString += ".png";
						break;
					case "text/javascript":
						filepathFormatString += ".json";
						break;				
					default:
						filepathFormatString += ".bin";
						break;				
				}
				
				viewModel.selectedModuleOfInterest.availableOutputpinList()[i].filepathFormatString(filepathFormatString);
			}
		}
	};
	// whenever selection of config changes, call configItemSelected() callback function
	viewModel.selectedModuleOfInterest.selectedConfig.obj.subscribe( viewModel.selectedModuleOfInterest.configItemSelected );
	
	// handle of global update timer
	viewModel.recordingTimeoutHandle = ko.observable(0);
	
	/*viewModel.recordingFlag = ko.computed( function() {
		return viewModel.recordingTimeoutHandle() ? true : false;
	});*/
	viewModel.recordingFlag = ko.observable(false);
	viewModel.recordingStatus = ko.observable("idle");
	
	viewModel.recordingRateInHz = ko.observable(LIVE_RECORDING_RATE_IN_HZ_SPINNER_DEFAULT_VALUE);
	viewModel.recordingInterval = ko.computed( function() {
		if (viewModel.recordingRateInHz()>0) {
			return 1000 / viewModel.recordingRateInHz();
		} else {
			return 0; // timeOut = 0 ... as fast as possible
		}
	});
	
	// statusMessage is used for pop-up window when recording is started or stopped to show progress of start-up respectively shut-down progress
	viewModel.statusMessage = ko.observable("");
		
	return viewModel;
};

/**
 * this function returns the number of selected outputpins
 * @returns the number of selected outputpins
 */
function updateNumOutputpinsSelected() {
	var num = 0;
	for ( var i = 0; i < viewModel.selectedModuleOfInterest.availableOutputpinList().length; ++i)
	{
		num += viewModel.selectedModuleOfInterest.availableOutputpinList()[i].isChecked();
		
	}
	viewModel.numOutputpinsSelected(num);
};

function updateCheckboxState() {
	for ( var i = 0; i < viewModel.selectedModuleOfInterest.availableOutputpinList().length; ++i)
	{	var oldValue = viewModel.selectedModuleOfInterest.availableOutputpinList()[i].isChecked();
		viewModel.selectedModuleOfInterest.availableOutputpinList()[i].isChecked(undefined); // enforce checkbox update by making sure that the value of the knockout observable changes (otherwise - in case the value is set to the same value - the checkbox wouldn't be updated)
		viewModel.selectedModuleOfInterest.availableOutputpinList()[i].isChecked(oldValue);
	}
}

/**
 * callback function of clicked event on checkbox-label 
 * checks or unchecks the checkbox which belongs to this checkbox-label but only if no recording is happening
 * @param data is used to hand over the current outputpin from the list of available outputpins (current = foreach index)
 */
function clickedOnCheckboxLabel(data) {
	if (!viewModel.recordingTimeoutHandle()) // only allow toggling of checkbox if currently not recording
	{
		data.isChecked(!data.isChecked());
	}
}



/**
 * creates a promise that will issue an ajax jsonp request with a given url
 * @param url the url used for the ajax jsonp request
 * @returns the promise used to perform the task
 */
function createDeferAjaxGetRequest(url) {
	/*return Q($.ajax({
		 url: url,
		 dataType: "jsonp",
		 type: "GET"
	}).done(resolve()).fail(reject()));
	*/ 
	var d = Q.defer()
	$.ajax({
		url: url,
		dataType: "jsonp",
		type: "GET",
		timeout: 15000,
		/*success: function(data) {
			d.resolve(data);
		},
		error: function(request, textStatus, errorThrown) {
			d.reject(new Error("Fatal Error - This might indicate a problem with the selected module: error reason: " + error));
		}
	 });*/
	 }).done(
			function (data) {
				d.resolve(data);
			}
	)
	.fail(	
			function (request, textStatus, errorThrown) {
				d.reject(new Error("Fatal Error - This might indicate a problem with the selected module: error reason: " + errorThrown));
			}
	);
	return d.promise;	 
}

/*
function createDeferAjaxGetRequest(url, paramDataType) {
	var d = Q.defer()
	var dataType = "jsonp"; // default
	if (paramDataType)
	{
		dataType = paramDataType; 
	}
	 
	$.ajax({
		url: url,
		dataType: dataType
		type: "GET"
	}).done(d.resolve).fail(d.reject);
		 
	return d.promise;	 
}
*/


// --------------------------------------------------------------- prepare recording -----------------------------------------------------------------

/**
 * prepare recording (record button callback function)
 * this function initiates file export configs creation - configs for selected outputpins (the completion
 * is handled in function onLoadCreateConfigIFrameCallback())
 * */
function prepareRecording() {
	//recordingMode = mapTabIdToRecordingMode($("#tabs li.ui-state-active").attr('id')); // update selected recording mode
	
	// test if we are already in playback mode -> global timer is active
	if ( viewModel.recordingTimeoutHandle() )
		return;		
	
	configsCreatedFileExportModules = [];
	sendQueueConfigsFileExportModules = [];
	listConfigsPreStatus = [];
	listConfigsRecordingInfo = [];
	listConfigsCurrentInfo = [];
	
	for ( var i = 0; i < viewModel.selectedModuleOfInterest.availableOutputpinList().length; ++i)
	{
		var element = viewModel.selectedModuleOfInterest.availableOutputpinList()[i];
		if (element.isChecked()) // only selected output pins
		{			
			addFileExportConfig(element); // add config to list via helper function addFileExportConfig()
		}
	}
		
	// open window with status message
	viewModel.statusMessage("sending File Export configs");
	$("#transferDialog").dialog("open");
	
	sendFileExportConfigs(); // this function will start the creation process of the file export configs (it will process the first config to send)
}


/**
 * this function starts the file export configs creation process
 * it sends the next config of the list of prepared file exports configs (sendQueueConfigsFileExportModules) to be created
 * the mechanism is using a Form/IFrame to get the result of the request and the function onLoadCreateConfigIFrameCallback()
 * is registered as callback which is called on when this IFrame finished to load
 * */
function sendFileExportConfigs() {
	// send configs - one after each other - we could not make simultanous post requests to work - so it's done sequentially now
	// config form onload will be used to finally notify via flag (and trigger callback) when all configs are created
	if (sendQueueConfigsFileExportModules.length > 0)
	{
		var config = sendQueueConfigsFileExportModules.pop();
		
		//alert(JSON.stringify(config, null, "\t"));
		
		// send config
		var url = viewModel.hostUrl() + 'FileExport' +'/0/config';
		// Workaround: use form to post data and IFrame to bypass same-origin-policy 
		// set target URL -> module URL + set config path
		$("#createConfigForm").attr("action", url);
		// set payload field in form
		$("#createConfigForm ._payload").val( JSON.stringify(config, null,"\n") );
		// actually post config and wait for notification from IFrame
		$("#createConfigForm ._submit").click();
	}
}


/**
 * callback function when IFrame had finished to load - gets registered in the main function
 * this function does these things:
 * -) checks if all configs that need to be created have already been created
 * -) if there are configs still to be created it invokes sendFileExportConfigs() to create the next config on the list
 * -) if all configs have been created, it:
 * 		-) updates the created file export configs (it gets the configIDs for the configs)
 * 		-) starts actions which needs to be taken after all file configs have been created (function afterFileExportConfigsCreated())
 * */
function onLoadCreateConfigIFrameCallback() { // if there are configs to send do so (sequential sending mechanism)
	// this first check is necessary because this function is invoked when this function is registered
	// in the main function in the line "$("#createConfigIFrame").load( onLoadCreateConfigIFrameCallback );"
	if (configsCreatedFileExportModules.length > 0) 
	{		
		if (sendQueueConfigsFileExportModules.length > 0) // configs left to be created?
		{
			sendFileExportConfigs(); // initate creation of next config
			return;
		}
		
		// now all configs have been created
		updateConfigListFileExport() // update configIDs of all previously created file export configs
		.then(function () {
			return afterFileExportConfigsCreated(); // initiate further actions (see function afterFileExportConfigsCreated() for further actions)
		})
		.fail(function (error) {
			stopRecording();
			alert("Error occurred in function onLoadCreateConfigIFrameCallback(): " + error);
		})
		.done();
	}
}


/**
 * helper function that creates a config data object from a file export config template and fills in the config specific information  
 * @param filepathFormatString the filepath format string specified by the user
 * @param pinID the pinID of the selected pin of the selected module of interest
 * @param selectedConfig the config of the selected module of interest
 * @returns the created config 
 */
function createFileExportConfig(filepathFormatString, pinID, selectedConfig) {
	// map viewModel to plain object
	var config = JSON.parse(JSON.stringify(configFileExportTemplate)); // configFileExportTemplate is loaded in OutputDataRecorder with command "<script type="text/javascript" src="js/OutputDataRecorder_configFileExport.js"></script>"
	
	config.params.filepath_format = filepathFormatString;
	config.chain[0].connections[0].outputPinID = pinID;
	config.chain[0].config = selectedConfig;
	
	return config;
}


/**
 * this function prepares the file export configs (for the selected outputpins) for creation
 * -) it creates a temporary list of created file export modules (they are not created but the list
 * is already build up and the configID needs to be retrieved later)
 * -) it creates a send queue (list) of these configs (which will be used to actually create these configs
 * in function sendFileExportConfigs() triggered by function prepareRecording())
 * -) it builds a recordingInfo list corresponding to the configs of the selected outputpins and sets
 * the structure field accessorTypeForRequest according to the first accessor-placeholder in the filepath format string
 */
function addFileExportConfig( element ) {
	var config = createFileExportConfig(element.filepathFormatString(), element.id(), viewModel.selectedModuleOfInterest.config);
	configsCreatedFileExportModules.push(config);
	sendQueueConfigsFileExportModules.push(config);
	
	var stringIndexFirstTimestampPlaceholder = element.filepathFormatString().indexOf("[timestamp]");
	var stringIndexFirstIndexPlaceholder = element.filepathFormatString().indexOf("[index]");
	var stringIndexFirstIdentifierPlaceholder = element.filepathFormatString().indexOf("[identifier]");
	
	var tmpList = [stringIndexFirstTimestampPlaceholder, stringIndexFirstIndexPlaceholder, stringIndexFirstIdentifierPlaceholder];
	for (var i=0; i<tmpList.length; i++)
	{
		if (tmpList[i]<0) // placeholder not found
		{
			tmpList[i] = Number.MAX_VALUE;
		}		
	}
	var minIdx = tmpList.indexOf(Math.min.apply(Math, tmpList));
	
	var recordingInfo = {};
	switch(minIdx)
	{
	case 0:
		recordingInfo.accessorTypeForRequest = "byTimestamp";
		break;
	case 1:
		recordingInfo.accessorTypeForRequest = "byIndex";
		break;
	case 2:
		recordingInfo.accessorTypeForRequest = "byIdentifier";
		break;
	default:
		recordingInfo.accessorTypeForRequest = "byTimestamp";
		break;
	}
	listConfigsRecordingInfo.push(recordingInfo);
}



/**
 * this function creates a promise that will update the list of file export configs with the generated configID (generated by Connected Vision Server - so we need to get it here)
 * @returns the promise used to perform the task
 */
function updateConfigListFileExport() {
	return Q.Promise(function(resolve, reject) {
		var url = viewModel.hostUrl() + "FileExport/configList";
		logDebug("request config list (" + url + ")");
		
		// get list of all configs running on the Connected Vision Server (all file export configs potentially including file export configs which
		// do not belong to the list of configs created by this GUI script - these are ignored in function updateConfigFileExport()
		// by filtering out configs that do not match the created configs 
		$.ajax({ 
			url: url,
			dataType: "jsonp",
			success: function( configIDList ) {
				listPromisesRequests = [];
				for( var i = 0; i < configIDList.length; i++ ) {
					var tmpPromise = updateConfigFileExport(configIDList[i]); // update "matching" configs
					listPromisesRequests.push(tmpPromise);
				}
				
				Q.all(listPromisesRequests)
				.then(function () {			 	
					resolve();
				})
				.fail(function (error) {
					reject(new Error("Error occurred in function updateConfigListFileExport(): " + error));
				})
				.done();
			},
			error: function( error ) {
				reject(new Error("Error occurred in function updateConfigListFileExport(): ajax request failed: cannot update config list - ") + error);
			}
		});
	});
}

/**
 * this function creates a promise that will:
 * -) try to find the matching config in the list of created file export configs which matches the config of the config with the provided configID parameter
 * -) if a matching config is found, update the configID of the config from the list of created file export configs with this configID (since this configID was
 * assigned by the Connected Vision Server to this config
 * @param configID the configID of the config to be matched against the configs in the list of created file export configs (which initially do not have a valid configID)
 * @returns the promise used to perform the task
 */
function updateConfigFileExport(configID) {
	return Q.Promise(function(resolve, reject) {
		var url = viewModel.hostUrl() + "FileExport/" + configID + "/config";
		logDebug("request config by configID (configID: " + configID + ", url: " + url + ")");
		
		// get config of the list of all configs running on the Connected Vision Server with id configID
		$.ajax({ 
			url: url,
			dataType: "jsonp",
			success: function( config ) { // with this config
				// check all configs created by the GUI script
				for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
					// test if the config and the i-th config in the created file export config list match
					if (	( config.params.filepath_format == configsCreatedFileExportModules[i].params.filepath_format) &&
							( config.chain[0].connections[0].outputPinID == configsCreatedFileExportModules[i].chain[0].connections[0].outputPinID) &&
							( config.chain[0].config.id == configsCreatedFileExportModules[i].chain[0].config.id) )
					{
						configsCreatedFileExportModules[i].id = config.id; // if so - store the configID (the one assigned by the Connected Vision Server)
					}
				}
				resolve();
			},
			error: function( error ) {
				reject("Error occurred in function updateConfigFileExport(): ajax request failed: cannot retrieve config with configID " + configID + ")");
			}
		});
	});
}



/**
 * this function creates a promise that will get the config prestatus of the connected Connected Vision module - this is important if
 * the config to be created already exists and is running - so that a stop record command later can correctly relinquish from
 * stopping the config (imagine an algorithm already running and you want to just record some data without interfering with the algorithm/module status) 
 * @returns the promise used to perform the task
 */
function getConfigsPreStatus() {
	return Q.Promise(function(resolve, reject) {
		viewModel.statusMessage("request chained config status");
		listPromisesRequests = [];
		for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
			configID = configsCreatedFileExportModules[i].id;
			var url = viewModel.hostUrl() + "FileExport/" + configID + "/status";
			listPromisesRequests.push(createDeferAjaxGetRequest(url));
		}
		
		Q.all(listPromisesRequests)
		.then(function (results) { // results is the list of results of the promises in listPromisesRequests
			for ( var i = 0; i < configsCreatedFileExportModules.length; i++ )
			{
				listConfigsPreStatus[i] = results[i].chain[0].status;
			}
			resolve();
		})
		.fail(function (error) {
			reject(new Error("Error occurred: " + error));
		})
		.done();
	});
}

/**
 * this function creates a promise that will start the created file export configs
 * @returns the promise used to perform the task
 */
function startFileExportConfigs() {	
	return Q.Promise(function(resolve, reject) {
		viewModel.statusMessage("start File Export configs");
		listPromisesRequests = [];
		for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
			configID = configsCreatedFileExportModules[i].id;
			var url = viewModel.hostUrl() + "FileExport/" + configID + "/control/start";
			listPromisesRequests.push(createDeferAjaxGetRequest(url));
		}
		
		Q.all(listPromisesRequests)
		.then(function () {
			resolve();
		})
		.fail(function (error) {
			reject(new Error("Error occurred: " + error));
		})
		.done();		
	});
}

/**
 * this function creates a promise that will initiate the actions to be taken after the file export configs have been created
 * @returns the promise used to perform the task
 */
function afterFileExportConfigsCreated() {
	return Q.Promise(function(resolve, reject) {
		getConfigsPreStatus()
		.then(function(res) {return startFileExportConfigs()})
		.then(
			function () { return Q().delay(5000); } // wait some time - initial wait for 1 second
		)
		.then(
			function () { return Q().delay(viewModel.numOutputpinsSelected() * 1000); } // wait some time - modules should have time to startup and finish initialization (e.g. fill ringbuffer with data elements) - times n for selected outputpins
		)
		.then(function(res) {return Q(startRecording())})
		.then(function() {
			resolve();
		})
		.fail(function (error) {
			reject("error reported by function afterFileExportConfigsCreated():" + error);
		})
		.done();
	});
}



//--------------------------------------------------------------- start recording -----------------------------------------------------------------

/**
 * this function starts recording (for both recording modes)
 */
function startRecording() {
	if (recordingMode == RECORDINGMODE_LIVE_MODE)
	{
		for ( var i = 0; i < configsCreatedFileExportModules.length; i++ )
		{
			listConfigsCurrentInfo[i] = {};
		}
		
		updateListConfigsCurrentInfoConfig()
		.then(function(result) {
			viewModel.recordingTimeoutHandle(setTimeout( function() {
				recordingIterationInLiveMode();
			}, viewModel.recordingInterval() ) );
		})
		.fail(function (error) {
			stopRecording();
			alert("error reported by function startRecording():" + error);
		})
		.done();
		
		/* OLD approach with setInterval
		// set timer to periodically request new data
		viewModel.recordingTimeoutHandle( setInterval( function() {
			
			updateListConfigsCurrentInfoStatus()
			.then(function(result1) {return updateListConfigsCurrentInfoConfig()})
			.then(function(result2) {return recordNextDataElementInLiveMode()})
			.fail(function (error) {
				stopRecording();
				alert("error reported by function startRecording():" + error);
			})
			.done();
		
		}, viewModel.recordingInterval() ) );	*/	 
	}
	else if (recordingMode == RECORDINGMODE_OFFLINE_MODE)
	{
		for ( var i = 0; i < configsCreatedFileExportModules.length; i++ )
		{
			listConfigsCurrentInfo[i] = {};
		}
	
		for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults = undefined;
		}
		
		updateListConfigsCurrentInfoConfig()
		.then(function(result) {
			viewModel.recordingTimeoutHandle(setTimeout( function() {
				processExportIterationInOfflineMode();
			}, 0 ) );
		})
		.fail(function (error) {
			stopRecording();
			alert("error reported by function startRecording():" + error);
		})
		.done();
	}
	
	// close status window
	$("#transferDialog").dialog("close");
	
	viewModel.recordingStatus("recording");
	viewModel.recordingFlag(true);
	
	$("#tools *").prop("disabled", true);
	$('#settings *').prop("disabled", true);
	$( "#tabs" ).tabs( { disabled: [0, 1] } );
	$( "#spinnerLiveRecordingRateInHz" ).spinner().spinner("disable");
	$('#recordingButton *').prop("disabled", false);
}


/**
 * this function creates a promise that will get the current status of the configs of the list of created file export configs
 * will write the status into listConfigsCurrentInfo[i].status where i is the index of the correspoding created file export config
 * @returns the promise used to perform the task
 */
function updateListConfigsCurrentInfoStatus() {	
	return Q.Promise(function(resolve, reject) {
		listPromisesRequests = [];
		for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
			configID = configsCreatedFileExportModules[i].id;
			var url = viewModel.hostUrl() + "FileExport/" + configID + "/status";
			listPromisesRequests.push(createDeferAjaxGetRequest(url));
		}
		
		Q.all(listPromisesRequests)
		.then(function (results) {
			for ( var i = 0; i < configsCreatedFileExportModules.length; i++ )
			{
				listConfigsCurrentInfo[i].status = results[i];	 
			}
			resolve();
		})
		.fail(function (error) {
			reject(new Error("Error occurred: " + error));
		})
		.done();
	});
}

/**
 * this function creates a promise that will get the current config of the configs of the list of created file export configs
 * will write the config into listConfigsCurrentInfo[i].config where i is the index of the correspoding created file export config
 * this is basically a convenience extra copy of the config ;)
 * @returns the promise used to perform the task
 */
function updateListConfigsCurrentInfoConfig() {	
	return Q.Promise(function(resolve, reject) {
		// only get once - config does not change while recording
		if (!listConfigsCurrentInfo[0].config) // only testing first array entry since either all are present or none...
		{
			listPromisesRequests = [];
			for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
				configID = configsCreatedFileExportModules[i].id;
				var url = viewModel.hostUrl() + "FileExport/" + configID + "/config";
				listPromisesRequests.push(createDeferAjaxGetRequest(url));
			}
			
			Q.all(listPromisesRequests)
			.then(function (results) {
				for ( var i = 0; i < configsCreatedFileExportModules.length; i++ )
				{
					listConfigsCurrentInfo[i].config = results[i];	 
				}
				resolve();
			})
			.fail(function (error) {
				reject(new Error("Error occurred: " + error));
			})
			.done();	
		}
		else
		{
			resolve(); // already exists - no json request for config is necessary
		}
	});
}

/**
 * helper function that finds a target value for a specific structure attribute element inside an array where the array elements are a structure -
 * the target value is the specific structure attribute element value inside the array which is computed by a comparison compare function
 * e.g.: computation of the minimum of a structure attribute inside an array: array[i].name -> result = finder(Math.min, array, "name");
 * @param cmp the compare function, e.g. Math.min
 * @param arr the array of structures
 * @param attr the structure attribute of interest as string
 * @returns the target value
 */
function finder(cmp, arr, attr) {
    var val = arr[0][attr];
    for(var i=1;i<arr.length;i++) {
        val = cmp(val, arr[i][attr])
    }
    return val;
}

// --------------------------------------------------------------- live recording mode -----------------------------------------------------------------

/**
 * this function creates a promise that will trigger recording of the next data element in live recording mode
 * @returns the promise used to perform the task
 */
function recordNextDataElementInLiveMode() {
	return Q.Promise(function(resolve, reject) {
		
		if (!viewModel.recordingTimeoutHandle()) // workaround to prevent outputpin requests after file export modul was stopped
		{
			resolve();
		}
		
		listOfStableResultsForCreatedFileExportModules = [];
		
		for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) { // configsCreatedFileExportModules, listConfigsRecordingInfo and listConfigsCurrentInfo have same number of elements and are in same order
			//var str = JSON.stringify(listConfigsCurrentInfo[i].status.chain[0].stableResults) + "\n" + JSON.stringify(listConfigsCurrentInfo[i].config.chain[0].connections[0].outputPinID);
			//alert(str);
			
			// DONE (TODO): match outputPin from config with list of pins in status and corresponding stableResults -> add this stableResults range to a list with all 
			//		stable results of all selected outputpins (configsCreatedFileExportModules) and find the newest stable results common for all output pins
			//		 -> use this element timestamp/index to trigger all file export configs			
			
			var connectedOutputPinID = listConfigsCurrentInfo[i].config.chain[0].connections[0].outputPinID;
			for (var j = 0; j < listConfigsCurrentInfo[i].status.chain[0].stableResults.length; j++ ) {
				if (listConfigsCurrentInfo[i].status.chain[0].stableResults[j].pinID == connectedOutputPinID) {
					//alert(JSON.stringify(listConfigsCurrentInfo[i].status.chain[0].stableResults[j]));
					listOfStableResultsForCreatedFileExportModules[i] = listConfigsCurrentInfo[i].status.chain[0].stableResults[j]; // get stable results for selected [i] connected output pin [j]
				}
			}
		}
		
		// test if all selected output pins agree on the type of accessor (timestamp or index) for the request (the first filepath placeholder must be the same for all selected output pins to be exported)
		var accessorTypeForRequest = listConfigsRecordingInfo[0].accessorTypeForRequest;
		for( var i = 1; i < configsCreatedFileExportModules.length; i++ ) {
			if (accessorTypeForRequest != listConfigsRecordingInfo[i].accessorTypeForRequest)
			{
				reject(new Error("accessor type for request does not match (the first filepath placeholder must be the same for all selected output pins to be exported)"));
			}		
		}
		
		// get latest shared stable result of all created file export modules (maximum that is common to all == two step process:
		// 	1.) minimum of indexEnd resp. timestampEnd
		//	2.) test afterwards if in stable results range of all file export module's stable results)
		if (listConfigsRecordingInfo[0].accessorTypeForRequest == "byTimestamp")
		{	
			var minTimestampEnd = -1;
			for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) { 			
				minTimestampEnd = (finder(Math.min, listOfStableResultsForCreatedFileExportModules, "timestampEnd"));
			}
			var maxSharedTimestampEnd = minTimestampEnd;
			for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
				if (listOfStableResultsForCreatedFileExportModules[i].timestampStart > minTimestampEnd)
				{
					maxSharedTimestampEnd = -1;
					reject(new Error("selected output pins do not share a maximum timestamp"));
				}
			}
			
			if (lastRequestedQualifierValue != maxSharedTimestampEnd)
			{
				listPromisesRequests = [];
				for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
					configID = configsCreatedFileExportModules[i].id;
					var url = viewModel.hostUrl() + "FileExport/" + configID + "/FileExportTrigger/time/" + maxSharedTimestampEnd;
					listPromisesRequests.push(createDeferAjaxGetRequest(url));
				}			
										
				Q.all(listPromisesRequests)
				.then(function () {
					lastRequestedQualifierValue = maxSharedTimestampEnd;
					resolve();
				})
				.fail(function (error) { reject(error);})
				.done();			
			}
			else
			{
				resolve();			
			}
		}
		else if (listConfigsRecordingInfo[0].accessorTypeForRequest == "byIndex")
		{
			var minIndexEnd = -1;
			for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) { 			
				minIndexEnd = (finder(Math.min, listOfStableResultsForCreatedFileExportModules, "indexEnd"));
			}
			var maxSharedIndexEnd = minIndexEnd;
			for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
				if (listOfStableResultsForCreatedFileExportModules[i].timestampStart > minIndexEnd)
				{
					maxSharedIndexEnd = -1;
					reject("selected output pins do not share a maximum index");
				}
			}
			
			if (lastRequestedQualifierValue != maxSharedIndexEnd)
			{
				listPromisesRequests = [];
				for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
					configID = configsCreatedFileExportModules[i].id;
					var url = viewModel.hostUrl() + "FileExport/" + configID + "/FileExportTrigger/index/" + maxSharedIndexEnd;
					listPromisesRequests.push(createDeferAjaxGetRequest(url));
				}			
														
				Q.all(listPromisesRequests)
				.then(function () {
					lastRequestedQualifierValue = maxSharedTimestampEnd;
					resolve();
				})
				.fail(function (error) { reject(error);})
				.done();
			}
			else
			{
				resolve();			
			}
		}
	});
}

/**
 * this function will perform a recording iteration in live recording mode
 */
function recordingIterationInLiveMode() {
	updateListConfigsCurrentInfoStatus()
	.then(function(result) {return recordNextDataElementInLiveMode()})
	.then(function(result) {
		if (viewModel.recordingTimeoutHandle()) // workaround to prevent outputpin requests after file export modul was stopped
		{
			viewModel.recordingTimeoutHandle(setTimeout( function() {
				if (viewModel.recordingTimeoutHandle())
				{
					recordingIterationInLiveMode();
				}
			}, viewModel.recordingInterval() ) );
		}
	})
	.fail(function (error) {		
		if (viewModel.recordingTimeoutHandle()) // throw error only if no timeout happened because of timed-out REST-request due to already stopped recording
		{
			stopRecording();
			alert("error reported by function recordingIterationInLiveMode():" + error);
		}
	})
	.done();
}




//--------------------------------------------------------------- offline recording mode -----------------------------------------------------------------

/**
 * this function will update stable results (on first run: initialize offline recording) of the connected outputpin for all created file export
 * configs in offline recording mode
 */
function updateExportStableResultsInOfflineMode() {
	listOfStableResultsForCreatedFileExportModules = [];
	for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
		
		var connectedOutputPinID = listConfigsCurrentInfo[i].config.chain[0].connections[0].outputPinID;
		for (var j = 0; j < listConfigsCurrentInfo[i].status.chain[0].stableResults.length; j++ ) {
			if (listConfigsCurrentInfo[i].status.chain[0].stableResults[j].pinID == connectedOutputPinID) {
				//alert(JSON.stringify(listConfigsCurrentInfo[i].status.chain[0].stableResults[j]));
				listOfStableResultsForCreatedFileExportModules[i] = listConfigsCurrentInfo[i].status.chain[0].stableResults[j]; // get stable results for selected [i] connected output pin [j]
			}
		}
		
		if (listConfigsRecordingInfo[i].listOutputpinsExportStableResults == undefined) // first stable results query
		{
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults = {};
			
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults.timestampStart = listOfStableResultsForCreatedFileExportModules[i].timestampStart;
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults.timestampEnd = listOfStableResultsForCreatedFileExportModules[i].timestampEnd;
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults.timestampNextPending = listConfigsRecordingInfo[i].listOutputpinsExportStableResults.timestampStart;
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexStart = listOfStableResultsForCreatedFileExportModules[i].indexStart;
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexEnd = listOfStableResultsForCreatedFileExportModules[i].indexEnd;
			listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexNextPending = listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexStart;
		}
		else // update stable results
		{
			if (listOfStableResultsForCreatedFileExportModules[i].timestampEnd>listConfigsRecordingInfo[i].listOutputpinsExportStableResults.timestampEnd)
			{
				listConfigsRecordingInfo[i].listOutputpinsExportStableResults.timestampEnd = listOfStableResultsForCreatedFileExportModules[i].timestampEnd;
			}

			if (listOfStableResultsForCreatedFileExportModules[i].indexEnd>listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexEnd)
			{
				listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexEnd = listOfStableResultsForCreatedFileExportModules[i].indexEnd;
			}
		}
	}
}

/**
 * this function will iterate over the stable results and process the next element to be exported in offline recording mode
 * it uses the index as accessor since we can iterate from indexStart to indexEnd which is not working for timestamps since we don't
 * know the exact intermediate timestamps between timestampStart and timestampEnd 
 */
function processExportIterationInOfflineMode() {
	var batchFinished = false;
	updateListConfigsCurrentInfoStatus()
	.then(function(res) {
		return Q(updateExportStableResultsInOfflineMode());
	})
	.then(function(res) {
		return Q.Promise(function(resolve, reject) {
			listPromisesRequests = [];
			for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
				configID = configsCreatedFileExportModules[i].id;
				var url = undefined;

				if (listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexNextPending <= listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexEnd)
				{
					url = viewModel.hostUrl() + "FileExport/" + configID + "/FileExportTrigger/index/" + listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexNextPending;
					listConfigsRecordingInfo[i].listOutputpinsExportStableResults.indexNextPending++;
				}
				
				if (url!=undefined)
				{
					listPromisesRequests.push(createDeferAjaxGetRequest(url));
				}
			}
			
			if (listPromisesRequests.length<=0)
			{
				batchFinished = true;
				resolve(); // nothing left to export
			}
			
			Q.all(listPromisesRequests)
			.then(function () {
				resolve();
			})
			.fail(function (error) { reject(error);})
			.done();
		});
	})
	.then(function(result) {
		if (batchFinished==false)
		{
			if (viewModel.recordingTimeoutHandle())
			{  	
				// trigger next iteration via setTimeout()
				viewModel.recordingTimeoutHandle(setTimeout( function() {
					processExportIterationInOfflineMode();
				}, 0 ) );
			}
		}
		else
		{
			stopRecording();	
		}
	})
	.fail(function (error) {
		stopRecording();
		alert("error reported by function processExportIterationInOfflineMode():" + error);
	})
	.done();
}




//----------------------------------------------------------------- stop recording -------------------------------------------------------------------

/**
 * this function creates a promise that will delete all file export configs (not affecting subconfigs (the configs inside the chains))
 * @returns the promise used to perform the task
 */
function deleteConfigs() {
	
	var deferred = Q.defer();
	viewModel.statusMessage("deleting File Export configs");
	
	listPromisesRequests = [];
	
	// delete all created file export configs
	while (configsCreatedFileExportModules.length > 0)
	{
		var config = configsCreatedFileExportModules.pop();
		var url = viewModel.hostUrl() + "FileExport/" + config.id + "/configOnlyThis?cmd=DELETE";
		listPromisesRequests.push(createDeferAjaxGetRequest(url));
	}
	
	Q.all(listPromisesRequests).then(function () {	
		deferred.resolve();
	})
	.fail(function (error) {
		deferred.reject(new Error("Error occurred: " + error));
	})
	.done();

	return deferred.promise;
}

/**
 * this function creates a promise that will stop all file export configs (dependend of the config's chained module pre status)
 * @returns the promise used to perform the task
 */
function stopConfigs() {
	
	var deferred = Q.defer();
	viewModel.statusMessage("stopping File Export configs");
	listPromisesRequests = [];
	for( var i = 0; i < configsCreatedFileExportModules.length; i++ ) {
		configID = configsCreatedFileExportModules[i].id;
		var url;
		if (listConfigsPreStatus[i] == 'running')
			url = viewModel.hostUrl() + "FileExport/" + configID + "/control/stopThis"; // only stop the file export module
		else
			url = viewModel.hostUrl() + "FileExport/" + configID + "/control/stop"; // stop file export module AND chained modules
		listPromisesRequests.push(createDeferAjaxGetRequest(url));
	}
	
	Q.all(listPromisesRequests)
	 .then(function () {
		 deferred.resolve();
	 })
	 .fail(function (error) {
		deferred.reject(new Error("Error occurred: " + error));
	 })
	 .done();

	return deferred.promise;
}

/**
 * this function stops recording
 */
function stopRecording() {
		viewModel.statusMessage("");
		$("#transferDialog").dialog("open");
		
		// test if we are in recording mode -> clear timeout
		if ( viewModel.recordingTimeoutHandle() )
			clearTimeout( viewModel.recordingTimeoutHandle() );
		
		// reset global timer
		viewModel.recordingTimeoutHandle(0);
		
		viewModel.statusMessage("stop recording initiated");
		
		Q().delay(viewModel.numOutputpinsSelected() * 500) // wait some time - pending requests should have time to finish - times n for selected outputpins
		.then(function(res) {return stopConfigs()})		
		.then(function(res) {return deleteConfigs()})
		.fail(function (error) {
			alert("error reported by function stopRecording():" + error);
		})
		.done(function(res) {
			$("#tools *").prop("disabled", false);
			$('#settings *').prop("disabled", false);
			$( "#tabs" ).tabs( { disabled: [] } );
			$( "#spinnerLiveRecordingRateInHz" ).spinner().spinner("enable");
			
			updateCheckboxState();
			
			viewModel.recordingStatus("idle");
			viewModel.recordingFlag(false);
			
			// close status window
			$("#transferDialog").dialog("close");			
		});
}


//---------------------------------------------------------------------- tools ------------------------------------------------------------------------

function deleteAllFileExportConfigs() {
	Q().then(function () {
		var url = viewModel.hostUrl() + "FileExport/configList";		
		return createDeferAjaxGetRequest(url);
	})
	.then(function (configIDList) {
		var deferred = Q.defer();
		
		listPromisesRequests = [];
		for ( var i = 0; i < configIDList.length; ++i)
		{
			var url = viewModel.hostUrl() + "FileExport/" + configIDList[i] + "/configOnlyThis?cmd=DELETE";
			listPromisesRequests.push(createDeferAjaxGetRequest(url));
		}
	
		Q.all(listPromisesRequests).then(function () {	
			deferred.resolve();
		})
		.fail(function (error) {
		deferred.reject(new Error("Error occurred: " + error));
		})
		.done();
		
		return deferred.promise;
	})
	.fail(function (error) {
		alert(new Error("Error occurred: " + error));
	})
	.done();
}

//--------------------------------------------------------------- main function -----------------------------------------------------------------

/**
 * main function
 */
$( function() {
	
	/*
	 * init dialogs
	 */
	$("#transferDialog").dialog({ autoOpen: false, modal: true, dialogClass: "no-close" });
	
	/*
	 * init knockout
	 * bind view model
	 */
	ko.applyBindings(viewModel);

	viewModel.updateModuleList();
	
	// configure settings button to slide settings section in/out
	$("#showTools").click( function() {
		$("#tools").slideToggle();
	});		
	
	// set listener to notification from server (response to set config)
	// The listener has to be attached only once (otherwise callback is attached on every .load()).
	$("#createConfigIFrame").load( onLoadCreateConfigIFrameCallback );
	
	// hide loading message and show main application view
	$("#loading").hide();
	$("#app").css("visibility", "");
	
	$('#tabs').tabs({ selected: 0 });
			
	$("#tabs").tabs({
		  beforeActivate: function (event, ui) {
		    recordingMode = mapTabIdToRecordingMode(ui.newTab.attr('id'));
		  }
	});
	recordingMode = mapTabIdToRecordingMode($("#tabs li.ui-state-active").attr('id')); // update selected recording mode
	
	$( "#spinnerLiveRecordingRateInHz" ).spinner().spinner({
		min: LIVE_RECORDING_RATE_IN_HZ_SPINNER_MIN_VALUE, max: LIVE_RECORDING_RATE_IN_HZ_SPINNER_MAX_VALUE,
		change: function (event, ui ) {
			var val = $("#spinnerLiveRecordingRateInHz").spinner("value");
			$("#spinnerLiveRecordingRateInHz").spinner("value", parseInt(val,10) || LIVE_RECORDING_RATE_IN_HZ_SPINNER_MIN_VALUE);
		}
	});
});
