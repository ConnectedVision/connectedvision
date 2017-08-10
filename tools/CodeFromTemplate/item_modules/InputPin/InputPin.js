/*
 * global variables
 */
var path = require('path');
var fs = require('fs');
var utils = require('../../Utilities.js');
var rt = require('../../RenderTemplate.js');
var mkpath = require('mkpath');

/**
 * prepareContext for Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  
 *  @return enriched context
 */
function prepareContext (key, context) {
	log.debug('[InputPin] ' + path.basename(__filename) + ' - prepareContext');
	
	// ensure that we have a DataClass context
	if ( !context.DataClass ) {
		var itemType = 'DataClass';
		// load item specific module
		var itemModule = require('../../item_modules/'+ itemType + '/' + itemType + '.js');
		// prepare DataClass context
		itemModule.prepareContext(itemType, context);
	}
	
	// extend context for InputPin
	context.InputPin = {};
	context.InputPin.name = context.DataClass.name;
	context.InputPin.className = 'InputPin_' + context.InputPin.name;
	context.InputPin.headerName = context.InputPin.className + '.h';
	context.InputPin.headerPath = context.InputPin.headerName.replace('\\', '/'); // use Linux style for include paths
	context.InputPin.stubName = 'InputPin_Stub_' + context.InputPin.name;
	
	context.InputPin.defaultHeaderName = context.InputPin.className + '_Default.h';
	context.InputPin.defaultHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.InputPin.defaultHeaderName);
	context.InputPin.defaultHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.InputPin.defaultHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	
	// get relative stub path
	context.InputPin.stubName = 'InputPin_Stub_' + context.InputPin.name;
	context.InputPin.stubHeaderName = context.InputPin.stubName + '.h';
	context.InputPin.stubHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.InputPin.stubHeaderName);
	context.InputPin.stubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.InputPin.stubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.InputPin.stubSourceName = context.InputPin.stubName + '.cpp';
	context.InputPin.stubSourceTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.InputPin.stubSourceName);
	context.InputPin.stubSourcePath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.InputPin.stubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths

	// set Pin ID
	context.InputPin.PinID = context.item.id;
		
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

	// renderContext
	// This is the prepared context generated with prepareContext()  
	var renderContext = context;
	
	var touched;
	var targetFile;
	
	log.info('[InputPin] generate: ' + renderContext.InputPin.name);
	
	//render class header
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + renderContext.InputPin.headerPath;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[InputPin] not changing existing file: ' + renderContext.InputPin.headerPath);
		touched = false;
	} else {	
		log.debug('[InputPin] write class header: ' + renderContext.InputPin.headerPath);
		mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.srcPath);
		rt.renderTemplateToFile(__dirname + '/' + 'InputPin.h'
			  , targetFile
			  , renderContext);
		touched = true;
	}
	artefacts.files.push({
        type: "InputPin",
        section: "InputPins",
        name: renderContext.InputPin.name,
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	//render default header
	targetFile = renderContext.InputPin.defaultHeaderTargetPath;
	log.debug('[InputPin] write default header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'InputPin_Default.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "InputPin",
        section: "InputPins/Stubs",
        name: renderContext.InputPin.name,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
	//render stubs header
	log.debug('[InputPin] write stub header: ' + renderContext.InputPin.stubHeaderTargetPath);
	mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'InputPin_Stub.h'
			  , renderContext.InputPin.stubHeaderTargetPath
			  , renderContext);	
	artefacts.files.push({
        type: "InputPin",
        section: "InputPins/Stubs",
        name: renderContext.InputPin.stubName,
        path: renderContext.InputPin.stubHeaderTargetPath,
        touched: true,
        compileable: false
	});
	
	artefacts.inputPins.push(
			{
	            name: renderContext.InputPin.PinID,
	            className: renderContext.InputPin.className,
	            headerPath: renderContext.InputPin.headerPath,
	            DataClass: {
	                name: renderContext.DataClass.name,
	                description: renderContext.DataClass.description,
	                className: renderContext.DataClass.className,
	                classHeaderPath: renderContext.DataClass.classHeaderPath
	            }
	        });
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;