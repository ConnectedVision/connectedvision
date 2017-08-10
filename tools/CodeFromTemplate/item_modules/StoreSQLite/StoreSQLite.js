/*
 * global variables
 */
var path = require('path');
var fs = require('fs');
var utils = require('../../Utilities.js');
var rt = require('../../RenderTemplate.js');
var mkpath = require('mkpath');

var C_CLASS_DELIMITER = '_';
var SQL_COLUMN_DELIMITER = '.';
var SQL_OBJSORTID = '_sortID';
var SQL_ARRAYIDX = '_idx';	


/**
 * convert a generic name / string to a valid C variable / function name
 * 
 * @param name	generic string
 * 
 * @return C variable name
 */
function makeCName(name) {
	
	// replace all non valid characters
	name = name.replace(/\W/g, C_CLASS_DELIMITER); 
	
	// prefix with underscore if first character is numeric
	if ( name[0] >= '0' && name[0] <= '9' )
		name = '_' + name;
	
	return name;
}

/**
 * extend property with matching SQLite type
 * 
 * @param prop	property of JSON schema
 */
function setSQLType(prop) {

	prop.SQLType = undefined;
	prop.isSearchable = false;
	prop.SQLdefault = prop['default'];
	
	/*
	 * map basic JSON types
	 */
	switch ( prop.type ) {
	case 'string':
		prop.SQLType = "TEXT";
		if ( !prop.SQLdefault )
			prop.SQLdefault = "";
		break;

	case 'number':
		prop.SQLType = "DOUBLE";
		if ( !prop.SQLdefault )
			prop.SQLdefault = 0;
		prop.isSearchable = true;
		break;

	case 'integer':
		prop.SQLType = "BIGINT";
		if ( !prop.SQLdefault )
			prop.SQLdefault = 0;
		prop.isSearchable = true;
		break;

	case 'boolean':
		prop.SQLType = "TINYINT";
		if ( !prop.SQLdefault )
			prop.SQLdefault = false;
		prop.isSearchable = true;
		break;

	case 'object':
		prop.SQLType = "VARCHAR(32)";	// object ID
		break;

	case 'array':
		prop.SQLType = "BIGINT";	// array index
		break;

	case 'any':
		prop.SQLType = "BLOB";
		if ( !prop.SQLdefault )
			prop.SQLdefault = "";
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
		prop.SQLType = 'VARCHAR(32)';
		if ( !prop.SQLdefault )
			prop.SQLdefault = '';
		prop.isSearchable = true;		
	}

	
	// timestamp
	if ( prop.type == 'integer' && prop.exttype == 'timestamp' ) {
		prop.SQLType = 'BIGINT';
		if ( !prop.SQLdefault )
			prop.SQLdefault = 0;		
		prop.isSearchable = true;		
	}

}


/**
 * create table columns context list
 * 
 * @param properties	list of object / array properties
 * @param columns 		columns list to be updated
 * @param bindings		object bindings list to be updated
 * @param idxKeys		array indices 
 * @param depth			recursion depth
 * @param arrayIdx		recursion array index / dimension
 * @param prefix		column name prefix
 * 
 * @returns columns list
 */
function createTableColumns( properties, columns, bindings, parent, idxKeys, depth, arrayIdx, prefix ) {
	if ( !depth ) depth = 1;
	if ( !arrayIdx ) arrayIdx = 1;
	if ( !prefix ) prefix = '';
	if ( !idxKeys ) idxKeys = [];
	
	for( var k in properties) {
		var c = properties[k];
		
		// copy default values for column
		var name = prefix + c.id;
		setSQLType(c);
		c.columnName = name;
		if ( !c.name )
			c.name = name;
		if ( !c.className )
			c.className = parent.className;
		if ( depth > 1 ) {
			// enforce column not to be required or search-able for array (sub-)items
			c.required = false;
			c.isSearchable = false;
		}
		c.parent = parent;
		c.metaField = false;
		c.idxKeys = [];
		for ( i in idxKeys )
			c.idxKeys.push(idxKeys[i]);
		c.depth = depth;
		if ( parent.getter )
			c.getter = parent.getter + '->';
		else
			c.getter = '';
		if ( parent.type == 'array' )
			c.getter += 'at(i' + (arrayIdx-1) + ')';
		else
			c.getter += 'getconst_' + c.id + '()';
		
		if ( c.type == 'object' ) {
			// handle sub objects
			c.description = 'object';
			c.required = false;
			c.metaField = true;
			c.bindingName = makeCName(name);

			// add bindings
			bindings.push(c);
			
			// create columns for sub objects recursively
			createTableColumns( c.properties, columns, bindings, c, c.idxKeys, depth +1, arrayIdx, name + SQL_COLUMN_DELIMITER );
			
		} else if ( c.type == 'array' ) {
			// handle array index
			c.columnName = name + SQL_COLUMN_DELIMITER + SQL_ARRAYIDX + arrayIdx;
			c.description = 'array index dimension: ' + arrayIdx;
			c.required = false;
			c.metaField = true;
		
			// add array index column
			c.idxKeys.push(c);
			columns.push(c);
			// create columns for sub objects recursively
			createTableColumns( [c.items], columns, bindings, c, c.idxKeys, depth +1, arrayIdx +1, prefix );

			
		} else {
			
			// add to bindings if it is an array
			if ( parent.type == 'array' ) {
				c.bindingName = makeCName(name);
				c.properties = [c]; // add self-reference for binding function
				bindings.push(c);
			}
			
			// add actual column
			columns.push(c);
		}
	}

	return columns;
}

/**
 * prepareContext for Class templates
 * 
 *  @param key			name of item type
 *  @param context		context object
 *  
 *  @return enriched context
 */
function prepareContext (key, context) {
	log.debug('[StoreSQLite] ' + path.basename(__filename) + ' - prepareContext');
	
	// ensure that we have a DataClass context
	if ( !context.DataClass ) {
		var itemType = 'DataClass';
		// load item specific module
		var itemModule = require('../../item_modules/'+ itemType + '/' + itemType + '.js');
		// prepare DataClass context
		itemModule.prepareContext(itemType, context);
	}

	// extend context for SQLite store
	context.StoreSQLite = {};
	context.StoreSQLite.name = context.DataClass.name;
	context.StoreSQLite.obj = utils.clone(context.DataClass);
	context.StoreSQLite.className = 'Store_SQLite_' + context.StoreSQLite.name;

	context.StoreSQLite.SQLName = context.StoreSQLite.name + '.sql';
	context.StoreSQLite.SQLPath = context.global.targetPath + context.global.moduleStructure.Paths.sqlPath + context.StoreSQLite.SQLName;

	context.StoreSQLite.headerName = context.StoreSQLite.className + '.h';
	context.StoreSQLite.headerPath = context.StoreSQLite.headerName.replace('\\', '/'); // use Linux style for include paths
	context.StoreSQLite.headerTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.StoreSQLite.headerName);
	
	context.StoreSQLite.defaultHeaderName = context.StoreSQLite.className + '_Default.h';
	context.StoreSQLite.defaultHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.defaultHeaderName);
	context.StoreSQLite.defaultHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.defaultHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context.StoreSQLite.stubName = 'Store_SQLite_Stub_' + context.StoreSQLite.name;
	context.StoreSQLite.stubHeaderName = context.StoreSQLite.stubName + '.h';
	context.StoreSQLite.stubHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.stubHeaderName);
	context.StoreSQLite.stubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.stubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.StoreSQLite.stubSourceName = context.StoreSQLite.stubName + '.cpp';
	context.StoreSQLite.stubSourceTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.stubSourceName);
	context.StoreSQLite.stubSourcePath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.stubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context.StoreSQLite.factoryName = 'Store_SQLite_Factory_' + context.StoreSQLite.name; 
	context.StoreSQLite.factoryStubName = 'Store_SQLite_Factory_Stub_' + context.StoreSQLite.name; 

	context.StoreSQLite.managerName = 'Store_Manager_SQLite_' + context.StoreSQLite.name; 
	context.StoreSQLite.managerStubName = 'Store_Manager_SQLite_Stub_' + context.StoreSQLite.name; 

	context.StoreSQLite.managerHeaderName = context.StoreSQLite.managerName + '.h'; 
	context.StoreSQLite.managerHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.StoreSQLite.managerHeaderName);
	context.StoreSQLite.managerHeaderPath = context.StoreSQLite.managerHeaderName.replace('\\', '/'); // use Linux style for include paths

	context.StoreSQLite.managerDefaultHeaderName = context.StoreSQLite.managerName + '_Default.h'; 
	context.StoreSQLite.managerDefaultHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.managerDefaultHeaderName);
	context.StoreSQLite.managerDefaultHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.managerDefaultHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context.StoreSQLite.managerStubHeaderName = context.StoreSQLite.managerStubName + '.h'; 
	context.StoreSQLite.managerStubHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.managerStubHeaderName);
	context.StoreSQLite.managerStubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.managerStubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context.StoreSQLite.managerStubSourceName = context.StoreSQLite.managerStubName + '.cpp'; 
	context.StoreSQLite.managerStubSourceTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.managerStubSourceName);
	context.StoreSQLite.managerStubSourcePath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.managerStubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths
	
	context.StoreSQLite.headerName = 'Store_SQLite_' + context.StoreSQLite.name + '.h'; 
	context.StoreSQLite.headerTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.srcPath + context.StoreSQLite.headerName);
	context.StoreSQLite.headerPath = context.StoreSQLite.headerName.replace('\\', '/'); // use Linux style for include paths
	
	context.StoreSQLite.stubHeaderName = 'Store_SQLite_Stub_' + context.StoreSQLite.name + '.h'; 
	context.StoreSQLite.stubHeaderTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.stubHeaderName);
	context.StoreSQLite.stubHeaderPath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.stubHeaderTargetPath)).replace('\\', '/'); // use Linux style for include paths

	context.StoreSQLite.stubSourceName = 'Store_SQLite_Stub_' + context.StoreSQLite.name + '.cpp'; 
	context.StoreSQLite.stubSourceTargetPath = path.normalize(context.global.targetPath + context.global.moduleStructure.Paths.stubPath + context.StoreSQLite.stubSourceName);
	context.StoreSQLite.stubSourcePath = path.normalize(path.relative(context.global.targetPath + context.global.moduleStructure.Paths.srcPath, context.StoreSQLite.stubSourceTargetPath)).replace('\\', '/'); // use Linux style for include paths	
	
	context.StoreSQLite.SQL_COLUMN_DELIMITER = SQL_COLUMN_DELIMITER;
	context.StoreSQLite.SQL_OBJSORTID = SQL_OBJSORTID;
	context.StoreSQLite.SQL_ARRAYIDX = 	SQL_ARRAYIDX;
	
	// create table context
	context.StoreSQLite.table = {
		name: context.StoreSQLite.name,
		columns: [{
			name: SQL_OBJSORTID,
			columnName: SQL_OBJSORTID,
			description: 'object sortable id',
			exttype: 'id',
			CBaseType: 'id_t',
			SQLType: 'BIGINT',
			SQLdefault: 0,
			required: true,
			metaField: true
		}],
		objectBindings: []
	}

	// determine base class
// TODO to be removed !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
	if (( context.StoreSQLite.obj.properties &&
			context.StoreSQLite.obj.properties.configID && 
			context.StoreSQLite.obj.properties.id && 
			context.StoreSQLite.obj.properties.timestamp ) &&
		( !context.StoreSQLite.obj.properties.configID.virtual &&
			!context.StoreSQLite.obj.properties.id.virtual &&
			!context.StoreSQLite.obj.properties.timestamp.virtual )) {
		context.StoreSQLite.baseClass = 'StoreCV_SQLite_BaseClass';
	}
	else
		context.StoreSQLite.baseClass = 'Store_SQLite_BaseClass_old';
// TODO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
	
	// add object binding
	context.StoreSQLite.obj.bindingName = makeCName(context.StoreSQLite.obj.name);
	context.StoreSQLite.table.objectBindings.push(context.StoreSQLite.obj);
	
	// add content columns
	createTableColumns(context.StoreSQLite.obj.properties, context.StoreSQLite.table.columns, context.StoreSQLite.table.objectBindings, context.StoreSQLite.obj);

	// create column index
	for ( var i = 0; i < context.StoreSQLite.table.columns.length; i++ ) {
		context.StoreSQLite.table.columns[i].columnIndex = i;
	}
	
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
	
	log.info('[StoreSQLite] generate: ' + renderContext.StoreSQLite.name);
	
	//render SQL file
	targetFile = renderContext.StoreSQLite.SQLPath;
	log.debug('[StoreSQLite] write SQL file: ' + targetFile);	
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.sqlPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_SQLite.sql'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.name,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
	//render manager header
	targetFile = renderContext.StoreSQLite.managerHeaderTargetPath;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[StoreSQLite] not changing existing file: ' + targetFile);
		touched = false;
	} else {	
		log.debug('[StoreSQLite] write manager header: ' + targetFile);
		mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.srcPath);
		rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_SQLite.h'
			  , targetFile
			  , renderContext);
		touched = true;
	}
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores",
        name: renderContext.StoreSQLite.className,
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	//render manager default header
	targetFile = renderContext.StoreSQLite.managerDefaultHeaderTargetPath;
	log.debug('[StoreSQLite] write manager default header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_SQLite_Default.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.className,
        path: targetFile,
        touched: true,
        compileable: false
	});	
	
	//render manager stubs header
	targetFile = renderContext.StoreSQLite.managerStubHeaderTargetPath;
	log.debug('[StoreSQLite] write manager stub header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_SQLite_Stub.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.stubName,
        path: targetFile,
        touched: true,
        compileable: false
	});	
	
	//render manager stubs class
	targetFile = renderContext.StoreSQLite.managerStubSourceTargetPath;
	log.debug('[StoreSQLite] write manager stub header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_Manager_SQLite_Stub.cpp'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.stubName,
        path: targetFile,
        touched: true,
        compileable: true
	});	
	
	//render class header
	targetFile = renderContext.StoreSQLite.headerTargetPath;
	if ( fs.existsSync(targetFile) && !settings.forceOverwrite ){
		log.debug('[StoreSQLite] not changing existing file: ' + targetFile);
		touched = false;
	} else {	
		log.debug('[StoreSQLite] write header: ' + targetFile);
		mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.srcPath);
		rt.renderTemplateToFile(__dirname + '/' + 'Store_SQLite.h'
			  , targetFile
			  , renderContext);
		touched = true;
	}
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores",
        name: renderContext.name,
        path: targetFile,
        touched: touched,
        compileable: false
	});
	
	//render default header
	targetFile = renderContext.StoreSQLite.defaultHeaderTargetPath;
	log.debug('[StoreSQLite] write default header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_SQLite_Default.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.stubName,
        path: targetFile,
        touched: true,
        compileable: false
	});
		
	//render stubs header
	targetFile = renderContext.StoreSQLite.stubHeaderTargetPath;
	log.debug('[StoreSQLite] write stub header: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_SQLite_Stub.h'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.stubName,
        path: targetFile,
        touched: true,
        compileable: false
	});
	
	//render stubs source
	targetFile = renderContext.StoreSQLite.stubSourceTargetPath;
	log.debug('[StoreSQLite] write stub source: ' + targetFile);
	mkpath.sync(context.global.targetPath + renderContext.global.moduleStructure.Paths.stubPath);
	rt.renderTemplateToFile(__dirname + '/' + 'Store_SQLite_Stub.cpp'
			  , targetFile
			  , renderContext);	
	artefacts.files.push({
        type: "Store.SQLite",
        section: "Stores/Stubs",
        name: renderContext.StoreSQLite.stubName,
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