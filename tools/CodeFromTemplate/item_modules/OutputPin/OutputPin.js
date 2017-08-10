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
	log.debug('[OutputPin] ' + path.basename(__filename) + ' - prepareContext');
	
	// ensure that we have a DataClass context
	if ( !context.DataClass ) {
		var itemType = 'DataClass';
		// load item specific module
		var itemModule = require('../../item_modules/'+ itemType + '/' + itemType + '.js');
		// prepare DataClass context
		itemModule.prepareContext(itemType, context);
	}

	// ensure that we have a StoreSQLite context
	if ( !context.StoreSQLite ) {
		var itemType = 'StoreSQLite';
		// load item specific module
		var itemModule = require('../../item_modules/'+ itemType + '/' + itemType + '.js');
		// prepare DataClass context
		itemModule.prepareContext(itemType, context);
	}
	
	// ensure that we have a StoreRingbuffer context
	if ( !context.StoreRingbuffer ) {
		var itemType = 'StoreRingbuffer';
		// load item specific module
		var itemModule = require('../../item_modules/'+ itemType + '/' + itemType + '.js');
		// prepare DataClass context
		itemModule.prepareContext(itemType, context);
	}	

	// extend context for OutputPin
	context.OutputPin = {};
	context.OutputPin.name = context.DataClass.name;
	context.OutputPin.className = 'OutputPin_' + context.OutputPin.name;
	context.OutputPin.headerName = context.OutputPin.className + '.h';
	context.OutputPin.headerPath = context.OutputPin.headerName.replace('\\', '/'); // use Linux style for include paths
	
	context.OutputPin.defaultHeaderName = context.OutputPin.className + '_Default.h';
	context.OutputPin.defaultHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.OutputPin.defaultHeaderName);
	context.OutputPin.defaultHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.OutputPin.defaultHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
		
	// get relative stub path
	context.OutputPin.stubName = 'OutputPin_Stub_' + context.OutputPin.name;
	context.OutputPin.stubHeaderName = context.OutputPin.stubName + '.h';
	context.OutputPin.stubHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.OutputPin.stubHeaderName);
	context.OutputPin.stubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.OutputPin.stubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.OutputPin.stubSourceName = context.OutputPin.stubName + '.cpp';
	context.OutputPin.stubSourceTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.OutputPin.stubSourceName);
	context.OutputPin.stubSourcePath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.OutputPin.stubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths

	// set Pin ID
	context.OutputPin.PinID = context.item.id;
		
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
	
	log.info('[OutputPin] generate: ' + renderContext.OutputPin.name);
	
	//render class header
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.srcPath + renderContext.OutputPin.headerPath;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[OutputPin] not changing existing file: ' + targetFile);
		touched = false;
	} else {
		log.debug('[OutputPin] write header: ' + targetFile);		
		mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.srcPath);
		rt.renderTemplateToFile(__dirname + '/' + 'OutputPin.h'
			  , targetFile
			  , renderContext);
		touched = true;
	}
	artefacts.files.push({
        type: "OutputPin",
        section: "OutputPins",
        name: renderContext.OutputPin.name,
        path: targetFile,
        touched: touched,
        compileable: false
	});

	
	//render default header
	targetFile = renderContext.OutputPin.defaultHeaderTargetPath;
	log.debug('[OutputPin] write default header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'OutputPin_Default.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "OutputPin",
        section: "OutputPins/Stubs",
        name: renderContext.OutputPin.name,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
	
	//render stubs header
	targetFile = renderContext.OutputPin.stubHeaderTargetPath;
	log.debug('[OutputPin] write stub header: ' + targetFile);	
	mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'OutputPin_Stub.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "OutputPin",
        section: "OutputPins/Stubs",
        name: renderContext.OutputPin.stubName,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
	artefacts.outputPins.push(
			{
	            name: renderContext.OutputPin.PinID,
	            className: renderContext.OutputPin.className,
	            headerPath: renderContext.OutputPin.headerPath,
	            DataClass: {
	                name: renderContext.DataClass.name,
	                description: renderContext.DataClass.description,
	                className: renderContext.DataClass.className,
	                classHeaderPath: renderContext.DataClass.classHeaderPath
	            },
	            StoreSQLite: {
	            	managerName: renderContext.StoreSQLite.managerName,
	            	managerHeaderName: renderContext.StoreSQLite.managerHeaderName,
	            	managerHeaderPath: renderContext.StoreSQLite.managerHeaderPath
	            },
	            StoreRingbuffer: {
	            	managerName: renderContext.StoreRingbuffer.managerName,
	            	managerHeaderName: renderContext.StoreRingbuffer.managerHeaderName,
	            	managerHeaderPath: renderContext.StoreRingbuffer.managerHeaderPath
	            }
	        });
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;