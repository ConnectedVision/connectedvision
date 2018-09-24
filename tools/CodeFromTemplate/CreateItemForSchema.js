var fs = require('fs');
var path = require('path');
var mkpath = require('mkpath');
var utils = require('./Utilities.js');
var winston = require('winston');
var global_mod = require('./item_modules/Global/Global.js');

/*
 * create items.json for a data object created from a JSON schema
 * the items.json will create:
 *  - data object
 *  - SQLite store
 *
 * arguments:
 * node CreateItemForSchema.js <target_path> <ConnectedVision_CPP_path> <schema_file> [folder_structure] [-verbose/-silent]
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
log = winston.createLogger({
	format: winston.format.printf(info => { return `${info.message}`; }),
	transports: [new winston.transports.Console({ level: settings.logLevel })]
});

log.info('[CreateItemForSchema] create items list ...');

var pre_global = {};

//get custom generator settings
var generatorSettingsPath = path.normalize("generatorSettings.json");
if (process.argv[5] && process.argv[5][0] != '-' )
	generatorSettingsPath = path.normalize(process.argv[5]);
if ( fs.existsSync(generatorSettingsPath ) ) {
	log.debug('[CreateItemList] moduleStructurePath: ' + generatorSettingsPath);
	var generatorSettings = fs.readFileSync(generatorSettingsPath , 'utf8');
	pre_global.moduleStructure = JSON.parse(generatorSettings);
	pre_global.moduleStructurePath = generatorSettingsPath;
}

// compute global
var global = global_mod.prepareContext(pre_global);

//set logger
for( var i in process.argv ) {
	if ( process.argv[i] == '-id' )	{
		global.moduleID = process.argv[++i] 
		log.debug('[CreateItemForSchema] moduleID: ' + global.moduleID);
	}
}

// get command-line arguments
global.targetPath = path.normalize(process.argv[2] + '/');
log.debug('[CreateItemForSchema] targetPath: ' + global.targetPath);
mkpath.sync(global.targetPath);

//get connected vision cpp path
global.cvCppRootDir = path.normalize(process.argv[3] + '/');
log.debug('[CreateItemForSchema] cvCppRootDir: ' + global.cvCppRootDir);

//get schema file
var schemaFile = process.argv[4];
log.debug('[CreateItemForSchema] schemaFile: ' + schemaFile);
var schema = fs.readFileSync(schemaFile, 'utf8');
schema = JSON.parse(schema);
if ( !schema.name ) {
	// use filename as schema name
	var basename = path.basename(schemaFile, path.extname(schemaFile));
	schema.name = basename;
}

fs.writeFileSync(global.targetPath + 'global.json', JSON.stringify(global, null, '\t'), 'utf8');

// CREATE ITEMS --------------------------------------------------------------------------------------------------

/*
 * write items list for data handling step ( = data classes, storage, stubs, ... )
 */

var itemList = [];

// ensure that schema.name is well-formed
schema.name = schema.name.replace(/[^0-9a-zA-Z_]/g, '_');

var item = (
	{
		name: schema.name,
		type: 'Schema',
		generate: {
			DataClass: {
				StoreSQLite: {},
				StoreRingbuffer: {}
			}
		},
		context: schema
	}
)
item.context.filenamePart = schema.name;

itemList.push(item);

log.debug('[CreateItemForSchema] write file: ' + global.targetPath + 'items.json');
fs.writeFileSync(global.targetPath + 'items.json', JSON.stringify(itemList, null, '\t'), 'utf8');

log.info('OK');

}
catch(err) {
	log.error(err.message);
	process.exit(1);
}