var version = '0.3 alpha';

//required modules
var fs = require('fs');
var path = require('path');
var utils = require('./Utilities.js');
var winston = require('winston');
var global_mod = require('./item_modules/Global/Global.js');

/*
 * create auto-generated files according to items.json
 *
 * arguments:
 * node CodeFromTemplate.js <global.json> <items.json> [-verbose/-silent] [-force]
 */

function recursiveIterateOverGenerate(types, context, artefacts, settings) {
	
	// loop over all items in list
	for (var itemType in types) {
		
		// load item specific module
		var itemModule = require('./item_modules/'+ itemType + '/' + itemType + '.js');
		
		// prepare item specific context
		var itemContext = itemModule.prepareContext(itemType, context);

		// render item and write files
		itemModule.render(itemType, itemContext, artefacts, settings);
		
		/*var new_artefacts = itemModule.render(key, itemContext);
		
		for (var i = 0; i < new_artefacts.length; i++) {
			context.global.artefacts.push(new_artefacts[i]);
		}*/
		
		// generate dependent items in hierarchy
		var dependentItems = types[itemType];
		recursiveIterateOverGenerate(dependentItems, itemContext, artefacts, settings);

	}
}

//globale settings
var settings = {
	forceOverwrite: false,
	logLevel: 'info'
}

// set logger
for( var i in process.argv ) {
	if ( process.argv[i] == '-v' || process.argv[i] == '-verbose' )
		settings.logLevel = 'debug';	
	if ( process.argv[i] == '-s' || process.argv[i] == '-silent' )
		settings.logLevel = 'error';	
}

// global scope for log!
log = winston.createLogger({
	format: winston.format.printf(info => { return `${info.message}`; }),
	transports: [new winston.transports.Console({ level: settings.logLevel })]
});

// other settings
for( var i in process.argv ) {
	if ( process.argv[i] == '-f' || process.argv[i] == '-force' ) {
		log.info('[CodeFromTemplate] force overwrite');
		settings.forceOverwrite = true;	
	}
}

try {

//get globals from file
var pre_global = fs.readFileSync(process.argv[2], 'utf8');
pre_global = JSON.parse(pre_global);

//get items from file
var items = fs.readFileSync(process.argv[3], 'utf8');
items = JSON.parse(items);

//get artefacts from file
if (process.argv[4] && process.argv[4][0] != '-' ) {
	var artefacts = fs.readFileSync(process.argv[4], 'utf8');
	artefacts = JSON.parse(artefacts);	
}
else
{
	var artefacts = {
			inputPins: [],
			outputPins: [],
			files: []
		}
}


//prepare global context
var global = global_mod.prepareContext(pre_global);
global.codeFromTemplateVersion = version;
global.macroPath = __dirname + "/SwigMacros.h";

//iterate over items
for( var i in items ) {
	var item = items[i];
	
	log.info('[CodeFromTemplate] ' + item.name + ' as ' + item.type);
	
	// put item context into private namespace
	var context = {};
	context.global = global;
	context.item = utils.clone(item.context);
	
	context.global.artefacts = artefacts;
	
	recursiveIterateOverGenerate(item.generate, context, artefacts, settings);
}

// write artefacts file
log.debug('[CodeFromTemplate] write: artefacts.json');
fs.writeFileSync(global.targetPath + 'artefacts.json', JSON.stringify(global.artefacts, null, '\t'), 'utf8');

log.info('OK');

}
catch(err) {
	log.error('[CodeFromTemplate] ' + err);
	process.exit(1);
}