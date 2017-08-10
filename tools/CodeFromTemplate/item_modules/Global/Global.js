var path = require('path');
var fs = require('fs');
var mkpath = require('mkpath');
var utils = require('../../Utilities.js');

function prepareContext (global) {
	log.debug('[Global] ' + path.basename(__filename) + ' - prepareContext');
	
	var moduleDescriptionPath = './def/', moduleDescriptionPathDefault = true;
	// use custom moduleDescriptionPath if set
	try {
		if ( global.moduleStructure.moduleDescriptionPath ) {
			moduleDescriptionPath = global.moduleStructure.moduleDescriptionPath;
			moduleDescriptionPathDefault = false;
		}
	} catch(error) {}
	
	// get moduleID
	if( moduleDescriptionPath )
	{
		try
		{
			var moduleDescription = fs.readFileSync(moduleDescriptionPath + 'ModuleDescription.json', 'utf8');
			moduleDescription = JSON.parse(moduleDescription);
			global.moduleID = moduleDescription.moduleID;
		}
		catch(error)
		{
			if ( !moduleDescriptionPathDefault ) {
				log.error("failed to find ModuleDescription.json in path " + moduleDescriptionPath + " (" + error.message + ")");
				process.exit(1);
			}
		}
	}
	
	// default global module structure
	var default_global = {
		moduleStructure: {
			Paths: {
				moduleDescriptionPath: moduleDescriptionPath,
				sqlPath: './sql/',
				srcPath: './src/',
				stubPath: './src/stubs/',
				VS2010: {
					projectFilename:	global.moduleID,
					projectName:		global.moduleID,
					projectPath:		'../../build_env/vs2010/build/Modules/' + global.moduleID + '/',
					propsPath:			'../../build_env/vs2010/build/Modules/' + global.moduleID + '/_vsprops/',
					outputPath:			'../../bin/vs2010/'
				},
				cmake: {
					projectFilename:	'CMakeLists.txt',
					projectName:		global.moduleID,
					projectPath:		'../../build_env/cmake/Modules/' + global.moduleID + '/',
					outputPath:			'../../bin/cmake/'
				}
			}
		}
	};

	// merge with default
	global = utils.merge(default_global, global);

	if ( !global.moduleStructure.namespace ) {
		// use default namespace
		if ( global.moduleID )
			global.moduleStructure.namespace = ["ConnectedVision", "Module", global.moduleID];
		else
			global.moduleStructure.namespace = [];
	}
	global.namespace = global.moduleStructure.namespace; // promote namespace to global scope
	
	// empty artefacts
	global.artefacts = [];

	// compute relative paths
	global.relativeStubToSrcPath = path.normalize(path.relative(global.moduleStructure.Paths.stubPath, global.moduleStructure.Paths.srcPath) + path.sep).replace('\\', '/'); // use Linux style for include paths
	log.debug('[Global] relativeStubToSrcPath: ' + global.relativeStubToSrcPath);
	
	return global;
};


function render (global) {
	log.debug('[Global] ' + path.basename(__filename) + ' - render');
};

/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;