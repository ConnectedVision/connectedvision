var path = require('path');
var fs = require('fs');
var mkpath = require('mkpath');
var rt = require('../../RenderTemplate.js');
var uuid = require('node-uuid');
var utils = require('../../Utilities.js');
var Definition = require('./Definition.js');

/**
 * prepareContext for Swagger templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  
 *  @return enriched context
 */
function prepareContext (key, context) {
	log.debug('[Swagger] ' + path.basename(__filename) + ' - prepareContext');
	
	context[key] = {};
	
	// get module name
	context[key].moduleID = context.global.moduleID;
	
	// get module path
	context[key].modulePath = context.global.targetPath;
	
	// set source path
	context[key].sourcePath = path.normalize(context[key].modulePath + context.global.moduleStructure.Paths.srcPath);
	mkpath.sync(context[key].sourcePath);
	
	context[key].className = 'Swagger.json';
	context[key].classSwaggerPath = context[key].className;
	
	
	
	context[key].description = 'This is the API definition of the ' + context[key].moduleID + ' Module.';
	context[key].tagDescription = '';
	context[key].version = context.global.moduleDescription.version;
	context[key].author = context.global.moduleDescription.author;
	
	context[key].hostFunctions = ['_hostStatus_'];
	context[key].moduleFunctions = ['moduleDescription'];
	context[key].outputPinFunctions = ['index'];
	
	
	
	context[key].definitions = [];
	
	// ********
	// * Host *
	// ********
	
	// HostStatus
	context[key].definitions.push(
			new Definition(
					'HostStatus'
					, 'host'
					, ''
					, path.normalize(context.global.cvCommonSchemaPath + '/HostStatus.schema')
					, {}
					)
			);
	
	// **********************
	// * Module Description *
	// **********************
	
	// ModuleParams
	var defModuleParams = new Definition(
			context[key].moduleID + '_ModuleParams'
			, 'module'
			, ''
			, path.normalize(context.global.cvCommonSchemaPath + '/ModuleDescription.schema')
			, {}
			);
	// tweak ModuleParams
	defModuleParams.schema.description = context.item.moduleDescription.params.description;
	delete defModuleParams.schema.properties;
	delete defModuleParams.schema.required;
	defModuleParams.schema.properties = utils.clone(context.item.moduleDescription.params.properties);	
	defModuleParams.updateSchemaAndSchemaString();	
	context[key].definitions.push(defModuleParams);
	
	// ModuleDescription
	var defModuleDescription = new Definition(
			context[key].moduleID + '_ModuleDescription'
			, 'module'
			, ''
			, path.normalize(context.global.cvCommonSchemaPath + '/ModuleDescription.schema')
			, {}
			);
	// tweak ModuleDescription configuration params
	delete defModuleDescription.schema.properties.params;
	defModuleDescription.schema.properties.params = { $ref: '#/definitions/' + context[key].moduleID + '_ModuleParams' };
	defModuleDescription.updateSchemaAndSchemaString();	
	context[key].definitions.push(defModuleDescription);
	
	// InputDescription
	var defInputDescription = new Definition(
			context[key].moduleID + '_InputDescription'
			, 'module'
			, ''
			, path.normalize(context.global.cvCommonSchemaPath + '/PinDescription.schema')
			, {}
			);
	context[key].definitions.push(defInputDescription);
	
	// OutputDescription
	var pinDescriptionSchemaPath = path.normalize(context.global.cvCommonSchemaPath + '/PinDescription.schema');
	var pinDescriptionSchema = JSON.parse(fs.readFileSync(pinDescriptionSchemaPath , 'utf8'));
	var pinDescriptionSchemaMimeTypeDefault = pinDescriptionSchema.items.properties.type.default;
	
	var defOutputDescription = new Definition(
			context[key].moduleID + '_OutputDescription'
			, 'module'
			, ''
			, pinDescriptionSchemaPath
			, {}
			, pinDescriptionSchemaMimeTypeDefault
			);
	context[key].definitions.push(defOutputDescription);
	
	// ModuleStatus
	context[key].definitions.push(
			new Definition(
					context[key].moduleID + '_ModuleStatus'
					, 'module'
					, ''
					, path.normalize(context.global.cvCommonSchemaPath + '/ModuleStatus.schema')
					, {}
					)
			);
	
	// *****************
	// * Configuration *
	// *****************
	
	// Config
	var defModuleConfiguration = new Definition(
			context[key].moduleID + '_Configuration'
			, 'configuration'
			, ''
			, path.normalize(context.global.cvCommonSchemaPath + '/generic_config.schema')
			, {}
			);
	defModuleConfiguration.schema.properties.params = { $ref: '#/definitions/' + context[key].moduleID + '_ModuleParams' };
	defModuleConfiguration.schema.properties.initialParams = { $ref: '#/definitions/' + context[key].moduleID + '_ModuleParams' };
	defModuleConfiguration.updateSchemaAndSchemaString();
	context[key].definitions.push(defModuleConfiguration);
	
	// ConfigurationStatus
	context[key].definitions.push(
			new Definition(
					context[key].moduleID + '_ConfigurationStatus'
					, 'module'
					, ''
					, path.normalize(context.global.cvCommonSchemaPath + '/generic_status.schema')
					, {}
					)
			);
	
	// ***************
	// * Request API *
	// ***************
	
	// InputPins
	for (var i in context.item.inputDescription)
	{
		var def = new Definition
		(
			context[key].moduleID + '_InputPin_' + context.item.inputDescription[i].id
			, 'inputPin'
			, context.item.inputDescription[i].id
			, ''
			, context.item.inputDescription[i]
			, pinDescriptionSchemaMimeTypeDefault
		);
		
		context[key].definitions.push(def);
	}
	
	// OutputPins
	for (var i in context.item.outputDescription)
	{
		var def = new Definition
		(
			context[key].moduleID + '_OutputPin_' + context.item.outputDescription[i].id
			, 'outputPin'
			, context.item.outputDescription[i].id
			, ''
			, context.item.outputDescription[i]
			, pinDescriptionSchemaMimeTypeDefault
		);
		
		context[key].definitions.push(def);
	}
	
	// get files
	context[key].files = context.global.artefacts.files;
	
	return context;
};


/**
 * render Swagger files
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
	
	log.info('[Swagger] generate: ' + moduleContext.className);
	
	//render Swagger
	targetFile = context.global.targetPath + context.global.moduleStructure.Paths.moduleDescriptionPath + moduleContext.classSwaggerPath;
	
//	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
//		log.debug('[Swagger] not changing existing file: ' + targetFile);
//		touched = false;
//	} else {
		log.debug('[Swagger] write file: ' + targetFile);		
		mkpath.sync(context.global.targetPath + context.global.moduleStructure.Paths.moduleDescriptionPath);
		rt.renderTemplateToFile(__dirname + '/' + 'TemplateSwagger.json'
			  , targetFile
			  , renderContext);
		touched = true;
//	}
	artefacts.files.push({
        type: "Swagger",
        section: "Swagger",
        name: moduleContext.name,
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
}

/**
 * render Swagger templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  @param artefacts	generated artefacts / files
 *  @param settings		globale settings (optional)
 */
function render (key, context, artefacts, settings) {
	log.debug('[Swagger] ' + path.basename(__filename) + ' - render');
	
	renderFiles(context, context[key], artefacts, settings);
	
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;