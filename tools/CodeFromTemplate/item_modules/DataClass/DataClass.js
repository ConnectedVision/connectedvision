/*
 * global variables
 */
var path = require('path');
var fs = require('fs');
var utils = require('../../Utilities.js');
var rt = require('../../RenderTemplate.js');
var mkpath = require('mkpath');


/*
 * helper functions
 */


/**
 * extend property with matching C/C++ type
 * 
 * @param prop	property of JSON schema
 */
function setCType(prop, classContext) {
	prop.isPtr = false;
	prop.CType = undefined;
	prop.CConstType = undefined;
	prop.CBaseType = undefined;

	/*
	 * map basic JSON types
	 */
	switch ( prop.type ) {
	case 'string':
		prop.CBaseType = "std::string";
		prop.isPtr = true;
		break;

	case 'number':
		prop.CBaseType = "double";
		break;

	case 'integer':
		prop.CBaseType = "int64_t";
		break;

	case 'boolean':
		prop.CBaseType = "bool";
		break;

	case 'object':
		prop.isPtr = true;
		prop.CBaseType = prop.className;
		break;

	case 'array':
		prop.isPtr = true;
		// get type from array items
		prop.CBaseType = "std::vector<" + prop.items.CType + ">";
		break;

	case 'any':
		prop.isPtr = true;
		prop.CBaseType = "std::string"; // use the JSON text
		break;

	default:
		// this should never happen
		break;
	}
	
	/*
	 * handle extended types
	 */
	
	// ID
	if ( prop.type == 'string' && prop.exttype == 'id' ) {
		prop.CBaseType = 'ConnectedVision::id_t';
		prop.isPtr = false;
	}

	
	// timestamp
	if ( prop.type == 'integer' && prop.exttype == 'timestamp' ) {
		prop.CBaseType = 'ConnectedVision::timestamp_t';
		prop.isPtr = false;
	}
	
	// enforce exttype
	if ( !prop.exttype )
		prop.exttype = prop.type;
	
	// derive C/C++ type from base type
	if ( prop.isPtr ) {
		prop.CType = 'boost::shared_ptr<' + prop.CBaseType + '>';
		prop.CConstType = 'boost::shared_ptr<const ' + prop.CBaseType + '>';
	} else {
		prop.CType = prop.CBaseType;
		prop.CConstType = prop.CBaseType;
	}
}

function extendFilePaths(context,name,global) {
	
	// get relative stub path
	context.className = 'Class_' + context.name;
	context.classHeaderName = context.className + '.h';
	context.classHeaderTargetPath = path.normalize(global.targetPath + global.moduleStructure.Paths.srcPath + context.classHeaderName);
	context.classHeaderPath = path.normalize(path.relative(global.targetPath + global.moduleStructure.Paths.srcPath, context.classHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	//////////////	
	context.relativeSrcPath = path.normalize(path.relative(global.moduleStructure.Paths.stubPath, global.moduleStructure.Paths.srcPath) + path.sep);
	log.debug('[DataClass] relativeSrcPath: ' + context.relativeSrcPath);

	context.classTargetPath = path.normalize(global.targetPath + global.moduleStructure.Paths.srcPath + context.classPath);
	context.classIncludePath = context.relativeSrcPath + context.classPath;
	context.classIncludePath = context.classIncludePath.replace('\\', '/'); // use Linux style for include paths
	////////////	

	context.defaultHeaderName = context.className + '_Default.h';
	context.defaultHeaderTargetPath = path.normalize(global.targetPath + global.moduleStructure.Paths.stubPath + context.defaultHeaderName);
	context.defaultHeaderPath = path.normalize(path.relative(global.targetPath + global.moduleStructure.Paths.srcPath, context.defaultHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context.stubName = 'Stub_' + name;
	context.stubHeaderName = context.stubName + '.h';
	context.stubHeaderTargetPath = path.normalize(global.targetPath + global.moduleStructure.Paths.stubPath + context.stubHeaderName);
	context.stubHeaderPath = path.normalize(path.relative(global.targetPath + global.moduleStructure.Paths.srcPath, context.stubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.stubSourceName = context.stubName + '.cpp';
	context.stubSourceTargetPath = path.normalize(global.targetPath + global.moduleStructure.Paths.stubPath + context.stubSourceName);
	context.stubSourcePath = path.normalize(path.relative(global.targetPath + global.moduleStructure.Paths.srcPath, context.stubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths
}


/**
 * extend the context with Array specific properties
 * 
 * This function is called recursively for all sub-classes.
 * 
 * @param context	class context to be extended
 * @param name 		full name of class
 */
function extendArrayContext(parent, context, name, global) {

	/*
	 * general extensions
	 */
	
	// make a depth-first recursion of sub-classes to have the context of the children (sub-classes) ready for variables and other things
	if ( !parent.children )
		parent.children = [];
	
	// build up array stack
	var a = context;
	var arrayStack = [];
	while ( a ) {
		a.items.id = context.id;
		arrayStack.push( a );

		// dive int sub-array
		if ( a.items.type == 'array' )
			a = a.items;
		else
			a = null;
	}			

	// process array stack bottom - up
	a = arrayStack.pop();
	while ( a ) {
		if ( a.items.type == 'object' ) {
			// process sub-class recursively
			extendClassContext(a.items, name, global);
			
			// add to sub-class list
			parent.children.push(a.items);
		} else if ( a.items.type == 'array' ) {
			// propagate up from sub-array
			setCType( a.items, parent );
		} else {
			// basic type
			setCType( a.items, parent );
		}
		
		a = arrayStack.pop();
	}
	
	// set type of class itself 
	setCType( parent, parent );		
}

/**
 * extend the context with Class specific properties
 * 
 * This function is called recursively for all sub-classes.
 * 
 * @param context	class context to be extended
 * @param name 		full name of class
 */
function extendClassContext(context, name, global) {

	/*
	 * general extensions
	 */
	context.name = name;
	context.children = [];

	// files
	extendFilePaths(context, name, global);
	
	// make a depth-first recursion of sub-classes to have the context of the children (sub-classes) ready for variables and other things
	for (var p in context.properties) {
		var prop = context.properties[p];
		
		// set property ID (variable name)
		prop.id = p;
		prop.name = name + '_' + prop.id;
		
		// is it a sub class?
		if ( prop.type == 'object' ) {
			
			// process sub-class recursively
			extendClassContext(prop, prop.name, global);
			
			// add to sub-class list
			context.children.push(prop);
		}

		// is it an array?
		if ( prop.type == 'array' ) {
			extendArrayContext(context, prop, prop.name, global);
		}

		
		// prepare member variables (properties)
		
		// set C/C++ type
		// do this after we have all sub-class types 
		setCType( prop, context );
	}	

	// set type of class itself 
	setCType( context, context );		
}


/*
 * item type API functions 
 */

/**
 * prepareContext for Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  
 *  @return enriched context
 */
function prepareContext (key, context) {
	log.debug('[DataClass] ' + path.basename(__filename) + ' - prepareContext');

	// prepare class name
	var className = "";
	if ( context.global.moduleID )
		className += context.global.moduleID + '_'; 
	if ( context.global.classPrefix )
		className += context.global.classPrefix + '_'; 
	className += context.item.filenamePart;
	
	var classContext = utils.clone(context.item);
	if ( classContext.type == 'object' ) {
		// check for configID and timestamp
		var configIDFound = false;
		var timestampFound = false;
		for( var k in classContext.properties) {
			if ( k == 'configID' )
				configIDFound = true;
			if ( k == 'timestamp' )
				timestampFound = true;
		}
		if ( !configIDFound ) {
			classContext.properties['configID'] = {
				description: "virtual config id",
				type: "string",
				exttype:"id",
				required: false,
				unit: "md5",
				default: "",
				virtual: true
			};
		}	
		if ( !timestampFound ) {
			classContext.properties['timestamp'] = {
				description: "virtual timestamp",
				type: "integer",
				exttype: "timestamp",
				required: false,
				unit: "ms",
				default: 0,
				virtual: true
			};
		}			
		extendClassContext(classContext, className, context.global);
	} else if ( classContext.type == 'array' ) {
		extendArrayContext(classContext, classContext, className, context.global);
	} else {
		throw '[DataClass] unknown type: ' + classContext.type;
		
	}
	
	context.DataClass = classContext;
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
function renderFiles(context, classContext, artefacts, settings) {
	if ( !settings ) settings = {};
	
	// renderContext
	// This is the prepared context generated with prepareContext()  
	var renderContext = utils.clone(context);
	// set DataClass to classContext (actual class or subclass) 
	renderContext.DataClass = utils.clone(classContext);
	
	var touched;
	var targetFile;

	log.info('[DataClass] generate: ' + classContext.name);
	
	//render class header
	targetFile = classContext.classHeaderTargetPath;
	if ( targetFile ) {
		if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
			log.debug('[DataClass] not changing existing file: ' + targetFile);
			touched = false;
		} else {	
			log.debug('[DataClass] write class header: ' + targetFile);
			mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.srcPath);
			rt.renderTemplateToFile(__dirname + '/' + 'Class.h'
				  , targetFile
				  , renderContext);
			touched = true;
		}
		artefacts.files.push({
	        type: "DataClass",
	        section: "DataClasses",
	        name: classContext.name,
	        path: targetFile,
	        touched: touched,
	        compileable: false
		});
	}

	//render default header
	targetFile = classContext.defaultHeaderTargetPath;
	if ( targetFile ) {
		log.debug('[DataClass] write stub header: ' + targetFile);
		mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
		rt.renderTemplateToFile(__dirname + '/' + 'Header_Default.h'
				  , targetFile
				  , renderContext);
		artefacts.files.push({
	        type: "DataClass",
	        section: "DataClasses/Stubs",
	        name: classContext.name,
	        path: targetFile,
	        touched: true,
	        compileable: false
		});
	}
	
	//render stub header
	targetFile = classContext.stubHeaderTargetPath;
	if ( targetFile ) {
		log.debug('[DataClass] write stub header: ' + targetFile);
		mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
		rt.renderTemplateToFile(__dirname + '/' + 'Stub.h'
				  , targetFile
				  , renderContext);
		artefacts.files.push({
	        type: "DataClass",
	        section: "DataClasses/Stubs",
	        name: classContext.stubName,
	        path: targetFile,
	        touched: true,
	        compileable: false
		});
	}
	
	//render stub class source
	targetFile = classContext.stubSourceTargetPath;
	if ( targetFile ) {
		log.debug('[DataClass] write stub source: ' + targetFile);
		mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
		rt.renderTemplateToFile(__dirname + '/' + 'Stub.cpp'
				  , targetFile
				  , renderContext);
		artefacts.files.push({
	        type: "DataClass",
	        section: "DataClasses/Stubs",
	        name: classContext.stubName,
	        path: targetFile,
	        touched: true,
	        compileable: true
		});
	}
	
	// recursively render sub-classes
	for ( var c in classContext.children ) {
		var subCalssContext = classContext.children[c];
		renderFiles(context, subCalssContext, artefacts, settings) 
	}
	
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
	log.debug('[DataClass] ' + path.basename(__filename) + ' - render');
	
	renderFiles(context, context.DataClass, artefacts, settings);
	
};


/*
 * exports functions to node.js
 */
exports.prepareContext = prepareContext;
exports.render = render;