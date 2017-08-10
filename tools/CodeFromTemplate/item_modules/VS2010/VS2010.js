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
	log.debug('[VS2010] ' + path.basename(__filename) + ' - prepareContext');
	
	context[key] = {};
	
	// get module name
	context[key].moduleID = context.global.moduleID;
	
	// get project name and filename
	context[key].projectFilename = context.global.moduleStructure.Paths.VS2010.projectFilename;
	context[key].projectName = context.global.moduleStructure.Paths.VS2010.projectName;
	
	// get files
	context[key].files = utils.clone(context.global.artefacts.files);
	
	// get connected vision cpp path
	context[key].cvCppRootDir = context.global.cvCppRootDir;
	log.debug('[VS2010] cvCppRootDir: ' + context[key].cvCppRootDir);

	// get module path
	context[key].modulePath = context.global.targetPath;
	log.debug('[VS2010] modulePath: ' + context[key].modulePath);

	// get data from Connected Vision structure file
	context[key].cvStructure = context.global.cvStructure;

	// set source path
	context[key].sourcePath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.srcPath + '\\').replace(/\\/g,"/");
	mkpath.sync(context[key].sourcePath);

	// set project files path
	context[key].projectPath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.VS2010.projectPath + '\\').replace(/\\/g,"/");
	mkpath.sync(context[key].projectPath);

	// set property sheet path
	context[key].propSheetPath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.VS2010.propsPath + '\\').replace(/\\/g,"/");
	mkpath.sync(context[key].propSheetPath);

	// get relative src path
	context[key].relativeSourcePathPrefix = path.normalize(path.relative(context[key].projectPath, context[key].sourcePath) + '\\').replace(/\\/g,"/");
	log.debug('[VS2010] relativeSourcePathPrefix: ' + context[key].relativeSourcePathPrefix);

	// get relative prop sheet path
	context[key].relativePropSheetPath = path.normalize(path.relative(context[key].projectPath, context[key].propSheetPath) + '\\' + 'projectSpecificProperties.props').replace(/\\/g,"/");
	log.debug('[VS2010] relativePropSheetPath: ' + context[key].relativePropSheetPath);

	// get output path
	context[key].outputPath = path.normalize(context[key].modulePath + '\\' + context.global.moduleStructure.Paths.VS2010.outputPath + '\\').replace(/\\/g,"/"); 
	context[key].relativeOutputPath = path.normalize(path.relative(context[key].projectPath, context[key].outputPath) + '\\').replace(/\\/g,"/");
	
	// get relative ConnectedVision\Cpp path
	context[key].relativeCvCppRootDir = path.normalize(path.relative(context[key].modulePath, context[key].cvCppRootDir) + '\\').replace(/\\/g,"/");
	log.debug('[VS2010] relativeCvCppRootDir: ' + context[key].relativeCvCppRootDir);
	
	// show module name
	log.debug('[VS2010] moduleID: ' + context[key].moduleID);

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

	context[key].files.forEach(function(file) {
	    file.path = path.relative(context[key].projectPath, file.path);
	});

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
	
	log.info('[VS2010] generate: ' + context[key].moduleID);
	
	targetFile = context[key].propSheetPath + 'projectSpecificProperties.props';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[VS2010] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[VS2010] write property sheet: ' + targetFile);		
		rt.renderTemplateToFile(__dirname + '/' + 'TemplateProjectSpecificProperties.props'
								, targetFile
								, context);
		touched = true;
	}
	
	targetFile = context[key].projectPath + context[key].projectFilename + '.vcxproj';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[VS2010] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[VS2010] write project: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/' + 'TemplateModule.vcxproj'
								, targetFile
								, context);
		touched = true;
	}
	
	
	targetFile = context[key].projectPath + context[key].projectFilename + '.vcxproj.filters';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[VS2010] not changing existing file: ' + targetFile);
		touched = false;
	} else {	
		// render template to file
		log.debug('[VS2010] write project filters: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/' + 'TemplateModule.vcxproj.filters'
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
