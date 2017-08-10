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
	log.debug('[StoreRingbuffer] ' + path.basename(__filename) + ' - prepareContext');
	
	// ensure that we have a DataClass context
	if ( !context.DataClass ) {
		var itemType = 'DataClass';
		// load item specific module
		var itemModule = require('../../item_modules/'+ itemType + '/' + itemType + '.js');
		// prepare DataClass context
		itemModule.prepareContext(itemType, context);
	}

	// extend context for SQLite store
	context.StoreRingbuffer = {};
	context.StoreRingbuffer.name = context.DataClass.name;
	context.StoreRingbuffer.obj = utils.clone(context.DataClass);
	
	context.StoreRingbuffer.managerName = 'Store_Manager_Ringbuffer_' + context.StoreRingbuffer.name;
	context.StoreRingbuffer.managerStubName = 'Store_Manager_Ringbuffer_Stub_' + context.StoreRingbuffer.name;
	
	context.StoreRingbuffer.managerHeaderName = context.StoreRingbuffer.managerName + '.h';
	context.StoreRingbuffer.managerHeaderPath = context.StoreRingbuffer.managerHeaderName.replace('\\', '/'); // use Linux style for include paths
	context.StoreRingbuffer.managerHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.StoreRingbuffer.managerHeaderName);
	
	context.StoreRingbuffer.managerDefaultHeaderName = context.StoreRingbuffer.managerName + '_Default.h';
	context.StoreRingbuffer.managerDefaultHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreRingbuffer.managerDefaultHeaderName);
	context.StoreRingbuffer.managerDefaultHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreRingbuffer.managerDefaultHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.StoreRingbuffer.managerStubHeaderName = context.StoreRingbuffer.managerStubName + '.h';
	context.StoreRingbuffer.managerStubHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreRingbuffer.managerStubHeaderName);
	context.StoreRingbuffer.managerStubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreRingbuffer.managerStubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.StoreRingbuffer.managerStubSourceName = context.StoreRingbuffer.managerStubName + '.cpp';
	context.StoreRingbuffer.managerStubSourceTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreRingbuffer.managerStubSourceName);
	context.StoreRingbuffer.managerStubSourcePath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreRingbuffer.managerStubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	return context;	
};

/**
 * render Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  @param artefacts	generated artefacts / files
 *  @param settings		globale settings (optional)
 */
function render (key, context, artefacts, settings) {
	if ( !settings ) settings = {};

	// renderContext
	// This is the prepared context generated with prepareContext()
	var renderContext = context;
	
	var touched;
	var targetFile;
	
	log.info('[StoreRingbuffer] generate: ' + renderContext.StoreRingbuffer.name);
	
	//render manager header
	targetFile = renderContext.StoreRingbuffer.managerHeaderTargetPath;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[StoreRingbuffer] not changing existing file: ' + targetFile);
		touched = false;
	} else {	
		log.debug('[StoreRingbuffer] write manager header: ' + targetFile);
		mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.srcPath);
		rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_Ringbuffer.h'
			  , targetFile
			  , renderContext);
		touched = true;
	}
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores",
        name: renderContext.StoreRingbuffer.managerName,
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	//render manager default header
	targetFile = renderContext.StoreRingbuffer.managerDefaultHeaderTargetPath;
	log.debug('[StoreRingbuffer] write manager header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_Ringbuffer_Default.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreRingbuffer.managerName,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
	//render manager stubs header
	targetFile = renderContext.StoreRingbuffer.managerStubHeaderTargetPath;
	log.debug('[StoreRingbuffer] write manager stub header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_Ringbuffer_Stub.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreRingbuffer.stubManagerName,
        path: targetFile,
        touched: true,
        compileable: false
	});

	//render manager stubs source
	targetFile = renderContext.StoreRingbuffer.managerStubSourceTargetPath;
	log.debug('[StoreRingbuffer] write manager stub header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_Ringbuffer_Stub.cpp'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreRingbuffer.stubManagerName,
        path: targetFile,
        touched: true,
        compileable: true
	});
	
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;