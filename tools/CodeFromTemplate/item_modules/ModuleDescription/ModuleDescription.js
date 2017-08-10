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
	log.debug('[ModuleDescription] ' + path.basename(__filename) + ' - prepareContext');
	
	context[key] = {};
	
	// get module name
	context[key].moduleID = context.global.moduleID;
	
	// get module path
	context[key].modulePath = context.global.targetPath;
	
	// set source path
	context[key].sourcePath = path.normalize(context[key].modulePath + context.global.moduleStructure.Paths.srcPath);
	mkpath.sync(context[key].sourcePath);
	
	context[key].className = context[key].moduleID +'_ModuleDescription.h';
	context[key].classHeaderPath = context[key].className;
	
	// get relative stub path
	context[key].stubHeaderName = 'Stub_' + context[key].moduleID + '_ModuleDescription.h';
	context[key].stubHeaderTargetPath = context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context[key].stubHeaderName;
	context[key].stubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context[key].stubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context[key].moduleDescription = JSON.stringify(context.item.moduleDescription, null, '\t');	
	context[key].inputDescription = JSON.stringify(context.item.inputDescription, null, '\t');	
	context[key].outputDescription = JSON.stringify(context.item.outputDescription, null, '\t');
	
	// get files
	context[key].files = context.global.artefacts.files;
	
	return context;
};


/**
 * render Class files
 * 
 * This function is called recursively for all sub-classes.
 * 
 *  @param context			context root
 *  @param artefacts		generated artefacts / files
 *  @param settings			globale settings (optional)
 */
function renderFiles(context, moduleContext, artefacts, settings) {
	if ( !settings ) settings = {};
	
	// renderContext
	// This is the prepared context generated with prepareContext()  
	var renderContext = utils.clone(context);
	// set DataClass to moduleContext (actual class or subclass) 
	renderContext.DataClass = utils.clone(moduleContext);
	
	var touched;
	var targetFile;
	
	log.info('[ModuleDescription] generate: ' + moduleContext.className);
	
	//render class header
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + moduleContext.classHeaderPath;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[ModuleDescription] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		log.debug('[ModuleDescription] write header: ' + targetFile);		
		mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.srcPath);
		rt.renderTemplateToFile(__dirname + '/' + 'TemplateModuleDescription.h'
			  , targetFile
			  , renderContext);
		touched = true;
	}
	artefacts.files.push({
        type: "DataClass",
        section: "DataClasses",
        name: moduleContext.name,
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	//render stub header
	targetFile = moduleContext.stubHeaderTargetPath;
	log.debug('[ModuleDescription] write stub header: ' + targetFile);		
	mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'TemplateModuleDescriptionStub.h'
			  , targetFile
			  , renderContext);
	artefacts.files.push({
        type: "DataClass",
        section: "DataClasses/Stubs",
        name: moduleContext.stubName,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
}

/**
 * render Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  @param artefacts	generated artefacts / files
 *  @param settings		globale settings (optional)
 */
function render (key, context, artefacts, settings) {
	log.debug('[ModuleDescription] ' + path.basename(__filename) + ' - render');
	
	renderFiles(context, context[key], artefacts, settings);
	
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;