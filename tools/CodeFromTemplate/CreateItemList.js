var fs = require('fs');
var path = require('path');
var mkpath = require('mkpath');
var utils = require('./Utilities.js');
var winston = require('winston');
var global_mod = require('./item_modules/Global/Global.js');

/*
 * create items.json for Connected Vision module
 *
 * arguments:
 * node CreateItemList.js <target_path> <ConnectedVision_CPP_path> [folder_structure] [-verbose/-silent]
 */


//CREATE GLOBAL CONTEXT -----------------------------------------------------------------------------------------
try {

//globale settings
var settings = {
	logLevel: 'info'
}

//set logger
for( var i in process.argv ) {
	if ( process.argv[i] == '-v' || process.argv[i] == '-verbose' )
		settings.logLevel = 'debug';	
	if ( process.argv[i] == '-s' || process.argv[i] == '-silent' )
		settings.logLevel = 'error';	
}
//global scope for log!
log = new (winston.Logger)({ transports: [ new (winston.transports.Console)({ level: settings.logLevel }) ] });
log.info('[CreateItemList] create items list ...');
for( var i in process.argv ) {
	log.debug('param ' + i + ' -> ' + process.argv[i]);	
}

var pre_global = {};

//get custom generator settings
var generatorSettingsPath = path.normalize("generatorSettings.json");
if (process.argv[4] && process.argv[4][0] != '-' )
	generatorSettingsPath = path.normalize(process.argv[4]);
if ( fs.existsSync(generatorSettingsPath) ) {
	log.debug('[CreateItemList] generatorSettingsPath: ' + generatorSettingsPath);
	var generatorSettings = fs.readFileSync(generatorSettingsPath , 'utf8');
	pre_global.moduleStructure = JSON.parse(generatorSettings);
	pre_global.moduleStructurePath = generatorSettingsPath;
}

// compute global
var global = global_mod.prepareContext(pre_global);
global.moduleDescriptionPath = path.normalize(global.moduleStructure.Paths.moduleDescriptionPath);


// get command-line arguments
global.targetPath = path.normalize(process.argv[2] + '/');
log.debug('[CreateItemList] targetPath: ' + global.targetPath);
mkpath.sync(global.targetPath);

//get connected vision cpp path
global.cvCppRootDir = path.normalize(process.argv[3] + '/');
log.debug('[CreateItemList] cvCppRootDir: ' + global.cvCppRootDir);

log.debug('[CreateItemList] moduleDescriptionPath: ' + global.moduleDescriptionPath);

global.cvCommonSchemaPath = path.normalize(global.cvCppRootDir + '/core/def/');
log.debug('[CreateItemList] cvCommonSchemaPath: ' + global.cvCommonSchemaPath);

// parse module description
global.moduleDescription = fs.readFileSync(global.moduleDescriptionPath + 'ModuleDescription.json', 'utf8');
global.moduleDescription = JSON.parse(global.moduleDescription);
global.moduleID = global.moduleDescription.moduleID;
global.moduleName = global.moduleDescription.name;
log.info('[CreateItemList] module: ' + global.moduleName + ' (ID: ' + global.moduleID + ')');


global.inputDescription = fs.readFileSync(global.moduleDescriptionPath + 'InputDescription.json' , 'utf8');
global.inputDescription = JSON.parse(global.inputDescription);

global.outputDescription = fs.readFileSync(global.moduleDescriptionPath + 'OutputDescription.json' , 'utf8');
global.outputDescription = JSON.parse(global.outputDescription);

fs.writeFileSync(global.targetPath + 'global.json', JSON.stringify(global, null, '\t'), 'utf8');

// CREATE ITEMS --------------------------------------------------------------------------------------------------

/*
 * write items list for data handling step ( = data classes, storage, input/output pins, stubs, ... )
 */

var itemList = [];

global.inputDescription.forEach(function(current_input){
	var input = utils.clone(current_input);
	input.filenamePart = 'input_' + input.id;
	delete input.name;
	var item = (
			{
				name: current_input.name,
				type: 'InputPin',
				generate: {},
				context: input
			}
	)
	
	
	if ( input.type ==  'application/json' ) {
		item.generate = {
			DataClass: {
				InputPin: {},
				StoreSQLite: {},
				StoreRingbuffer: {}
			},
		};
		item.context.type = 'object';
	}
	
	itemList.push(item);
});

global.outputDescription.forEach(function(current_output){
	var output = utils.clone(current_output);
	output.filenamePart = 'output_' + output.id;
	delete output.name;
	var item = (
			{
				name: current_output.name,
				type: 'OutputPin',
				generate: {},
				context: output
			}
	)

	if ( output.type ==  'application/json' ) {
		item.generate = {
			DataClass: {
				StoreSQLite: {
					OutputPin: {}
				},
				StoreRingbuffer: {}
			}
		};
		item.context.type = 'object';
	}

	itemList.push(item);
	
});

var paramsContext = utils.clone(global.moduleDescription.params);
paramsContext.filenamePart = 'params';
var item = (
		{
			name: global.moduleDescription.name,
			type: 'Params',
			generate: {
				DataClass: {}
			},
			context: paramsContext
		}
);
itemList.push(item);

var item = (
		{
			name: global.moduleDescription.name,
			type: 'ModuleDescription',
			generate: {
				ModuleDescription: {
					Swagger: {}
				}
			},
			context: {
				moduleDescription: utils.clone(global.moduleDescription),
				inputDescription: utils.clone(global.inputDescription),
				outputDescription: utils.clone(global.outputDescription)
			}
		}
);
itemList.push(item);

log.debug('[CreateItemList] write file: ' + global.targetPath + 'items_data.json');
fs.writeFileSync(global.targetPath + 'items_data.json', JSON.stringify(itemList, null, '\t'), 'utf8');


/*
 * write items list for computation step ( = module + worker + factory + ... )
 */

var itemList = [];

var item = (
		{
			name: global.moduleDescription.name,
			type: 'Module',
			generate: {
				Module: {}
			},
			context: {
				moduleDescription: utils.clone(global.moduleDescription),
				inputDescription: utils.clone(global.inputDescription),
				outputDescription: utils.clone(global.outputDescription)
			}
		}
);
itemList.push(item);

log.debug('[CreateItemList] write file: ' + global.targetPath + 'items_computation.json');
fs.writeFileSync(global.targetPath + 'items_computation.json', JSON.stringify(itemList, null, '\t'), 'utf8');


/*
 * write items list for build environment step
 */
var itemList = [];

var item = (
		{
			name: global.moduleDescription.name,
			type: 'Build',
			generate: {
				/*VS2010: {},*/
				cmake: {}
			},
			context: {}
		}
);
itemList.push(item);

log.debug('[CreateItemList] write file: ' + global.targetPath + 'items_build.json');
fs.writeFileSync(global.targetPath + 'items_build.json', JSON.stringify(itemList, null, '\t'), 'utf8');

log.info('OK');

}
catch(err) {
	log.error(err.message);
	process.exit(1);
}
