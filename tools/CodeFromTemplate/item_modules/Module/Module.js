var path = require('path');
var fs = require('fs');
var mkpath = require('mkpath');
var rt = require('../../RenderTemplate.js');
var uuid = require('node-uuid');
var utils = require('../../Utilities.js');
var itemDataClass = require('../../item_modules/DataClass/DataClass.js');

/**
 * prepareContext for Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  
 *  @return enriched context
 */
function prepareContext (key, context) {
	log.debug('[Module] ' + path.basename(__filename) + ' - prepareContext');

	// copy module description
	context.Module = utils.clone(context.item.moduleDescription);
	
	// get module path
	context.Module.modulePath = context.global.targetPath;
	
	// get inputPins
	context.Module.inputPins = context.global.artefacts.inputPins;
	
	// get outputPins
	context.Module.outputPins = context.global.artefacts.outputPins;
	
	// get files
	context.Module.files = context.global.artefacts.files;

	// get data from Connected Vision structure file
	context.Module.cvStructure = context.global.cvStructure;

	// set source path
	context.Module.sourcePath = path.normalize(context.Module.modulePath + path.sep + context.global.moduleStructure.Paths.srcPath + path.sep);
	mkpath.sync(context.Module.sourcePath);

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
	var targetFile;
	
	log.debug('[Module] ' + path.basename(__filename) + ' - render');
	
	log.info('[Module] generate: ' + context.Module.moduleID + ' - Module');
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.Module.moduleID + 'Module.cpp';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[Module] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[Module] write file: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/templates/TemplateModule.cpp'
								, targetFile
								, context);
		touched = true;
	}
	artefacts.files.push({
        type: "ModuleSource",
        section: "Module",
        name: context.Module.moduleID + 'Module',
        path: targetFile,
        touched: touched,
        compileable: true
	});
	
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.Module.moduleID + 'Module.h';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[Module] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[Module] write file: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/templates/TemplateModule.h'
								, targetFile
								, context);
		touched = true;
	}
	artefacts.files.push({
        type: "ModuleSource",
        section: "Module",
        name: context.Module.moduleID + 'Module',
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	log.info('[Module] generate: ' + context.Module.moduleID + ' - Worker');
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.Module.moduleID + 'Worker.cpp';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[Module] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[Module] write file: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/templates/TemplateWorker.cpp'
								, targetFile
								, context);
		touched = true;
	}
	artefacts.files.push({
        type: "ModuleSource",
        section: "Module",
        name: context.Module.moduleID + 'Worker',
        path: targetFile,
        touched: touched,
        compileable: true
	});
	
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.Module.moduleID + 'Worker.h';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[Module] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[Module] write file: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/templates/TemplateWorker.h'
								, targetFile
								, context);
		touched = true;
	}
	artefacts.files.push({
        type: "ModuleSource",
        section: "Module",
        name: context.Module.moduleID + 'Worker',
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	log.info('[Module] generate: ' + context.Module.moduleID + ' - Factory');
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.Module.moduleID + 'ModuleFactory.cpp';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[Module] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[Module] write file: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/templates/TemplateModuleFactory.cpp'
								, targetFile
								, context);
		touched = true;
	}
	artefacts.files.push({
        type: "ModuleSource",
        section: "Module",
        name: context.Module.moduleID + 'ModuleFactory',
        path: targetFile,
        touched: touched,
        compileable: true
	});
	
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.Module.moduleID + 'ModuleFactory.h';
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[Module] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		// render template to file
		log.debug('[Module] write file: ' + targetFile);
		rt.renderTemplateToFile(__dirname + '/templates/TemplateModuleFactory.h'
								, targetFile
								, context);
		touched = true;
	}
	artefacts.files.push({
        type: "ModuleSource",
        section: "Module",
        name: context.Module.moduleID + 'ModuleFactory',
        path: targetFile,
        touched: touched,
        compileable: false
	});	
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;