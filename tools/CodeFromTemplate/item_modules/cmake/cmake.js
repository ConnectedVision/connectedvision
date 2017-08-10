var path = require('path');
var fs = require('fs');
var mkpath = require('mkpath');
var rt = require('../../RenderTemplate.js');
var uuid = require('node-uuid');
var utils = require('../../Utilities.js');

/**
 * prepareContext for Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  
 *  @return enriched context
 */
function prepareContext (key, context) {
	log.debug('[cmake] ' + path.basename(__filename) + ' - prepareContext');
	
	context[key] = {};
	
	// get module name
	context[key].moduleID = context.global.moduleID;
	
	// get project name and filename
	context[key].projectFilename = context.global.moduleStructure.Paths.cmake.projectFilename;
	context[key].projectName = context.global.moduleStructure.Paths.cmake.projectName;
	
	// get files
	context[key].files = utils.clone(context.global.artefacts.files);
	
	// get connected vision cpp path
	context[key].cvCppRootDir = context.global.cvCppRootDir;
	log.debug('[cmake] cvCppRootDir: ' + context[key].cvCppRootDir);

	// get module path
	context[key].modulePath = context.global.targetPath;
	log.debug('[cmake] modulePath: ' + context[key].modulePath);

	// get data from Connected Vision structure file
	context[key].cvStructure = context.global.cvStructure;

	// set source path
	context[key].sourcePath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.srcPath + '\\').replace(/\\/g,"/");
	mkpath.sync(context[key].sourcePath);

	// set project files path
	context[key].projectPath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.cmake.projectPath + '\\').replace(/\\/g,"/");
	mkpath.sync(context[key].projectPath);

	// get relative src path
	context[key].relativeSourcePathPrefix = path.normalize(path.relative(context[key].projectPath, context[key].sourcePath) + '\\').replace("\\","/").replace(/\\/g,"/");
	log.debug('[cmake] relativeSourcePathPrefix: ' + context[key].relativeSourcePathPrefix);

	// get output path
	context[key].outputPath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.cmake.outputPath + '\\').replace(/\\/g,"/"); 
	context[key].relativeOutputPath = path.normalize(path.relative(context[key].projectPath, context[key].outputPath) + '\\').replace(/\\/g,"/");
	
	// get relative ConnectedVision\Cpp path
	context[key].relativeCvCppRootDir = path.normalize(path.relative(context[key].modulePath, context[key].cvCppRootDir) + '\\').replace(/\\/g,"/");
	log.debug('[cmake] relativeCvCppRootDir: ' + context[key].relativeCvCppRootDir);
	
	// get relative ConnectedVision\Cpp path from CMakeLists.txt path
	context[key].relativeProjectToCvCppRootPath = path.normalize(path.relative(context[key].projectPath, context[key].cvCppRootDir) + '\\').replace(/\\/g,"/");
	log.debug('[cmake] relativeProjectToCvCppRootPath: ' + context[key].relativeProjectToCvCppRootPath);
	
	// show module name
	log.debug('[cmake] moduleID: ' + context[key].moduleID);

	// generate a RFC4122 v4 UUID for the project
	context[key].projectGuid = '{' + uuid.v4().toString().toUpperCase() + '}';
	
	// add array of unique section names to data context
	context[key].uniqueSections = [];
	// get all section names
	context[key].files.forEach(function (element, index, array) {
		var section = new Object();
		section.name = element.section;
		section.guid = ''; // set empty
		context[key].uniqueSections.push(section);
	});
	// remove the duplicates
	utils.mergeSections(context[key].uniqueSections);
	// now generate a RFC4122 v4 UUID for each unique section
	context[key].uniqueSections.forEach(function (element, index, array) {
		element.guid = '{' + uuid.v4().toString().toUpperCase() + '}';
	});
	
	var temp = [];

	context[key].files.forEach(function(file)
	{
		if([".json", ".sql"].indexOf(path.extname(file.path)) === -1)
		{
			file.path = path.relative(context[key].projectPath, file.path).replace(/\\/g,"/");
			temp.push(file);
		}
	});
	
	context[key].files = temp;
	
	return context;	
};

/**
 * render Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  @param artefacts	generated artefacts / files
 *  @param settings		globale settings (optional)
 *  
 */
function render (key, context, artefacts, settings) {
	if ( !settings ) settings = {};

	var touched;
	
	log.info('[cmake] generate: ' + context[key].moduleID);
	
	targetFile = context[key].projectPath + context[key].projectFilename;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[cmake] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[cmake] write cmake file: ' + targetFile);		
		rt.renderTemplateToFile(__dirname + '/' + 'CMakeLists.txt'
								, targetFile
								, context);
		touched = true;
	}
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;