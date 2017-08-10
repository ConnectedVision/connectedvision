var fs = require('fs');
var utils = require('../../Utilities.js');
var method = Definition.prototype;

// Constructor
function Definition(name, type, outputPinId, schemaPath, schema, mimeTypeDefault) {
	this.name = name;
	this.type = type;
	this.outputPinId = outputPinId;
	this.schemaPath = schemaPath;
	
	if (!schemaPath){
		this.schema = utils.clone(schema);
	} else {
		this.schema = JSON.parse(fs.readFileSync(this.schemaPath , 'utf8'));
	}
	
	this.mimeTypes = [];
	
	this.pinBinaryFlag = false;
	
	if(['inputPin', 'outputPin'].indexOf(type) > -1)
	{
		// if the current element is an input or output pin then add the corresponding MIME type to the MIME types array if it is not already part of it
		if(this.schema.hasOwnProperty('type'))
		{
			this.mimeTypes.push(this.schema.type);
		}

		// if a default MIME type was provided, then add it to the MIME types array
		if(mimeTypeDefault && this.mimeTypes.indexOf(mimeTypeDefault) < 0)
		{
			this.mimeTypes.push(mimeTypeDefault);
		}
		
		if(this.schema.type != 'text/javascript' && this.schema.type != 'application/json')
		{
			this.pinBinaryFlag = true;
		}
	}
	
	traverse(this.schema, deleteUselessKeys, this.type);
	this.schemaString = JSON.stringify(this.schema, null, '\t').replace(/\n/g, '\n\t\t');
}

function deleteUselessKeys(object, key, value, type) {
	// log.debug('[Swagger] ' + key + " : "+value);
	
	var keyBlacklist =
	[
		'additionalProperties',
		'dynamic',
		'exttype',
		'id',
		'name',
		'unit'
	];
	
	// delete certain keys for all definition types
	if(keyBlacklist.indexOf(key) > -1)
	{
		delete object[key];
	}
	
	if(['inputPin', 'outputPin'].indexOf(type) > -1 && key === 'static')
	{
		delete object[key];
	}
	
	// handle the 'required' property
	if(object && object.hasOwnProperty('properties') && typeof object.properties === 'object' && !Array.isArray(object.properties))
	{
		Object.keys(object.properties).forEach
		(
			function(propertyName)
			{
				// check if the object has a property 'required' of type boolean
				if(object.properties[propertyName].hasOwnProperty('required') && typeof object.properties[propertyName].required === 'boolean')
				{
					// only proceed if the 'required' property is true and the key is not in the key blacklist
					if(object.properties[propertyName].required && keyBlacklist.indexOf(propertyName) < 0)
					{
						if(object.hasOwnProperty('required') && !Array.isArray(object.required))
						{
							delete object.required;
						}
						
						if(!object.hasOwnProperty('required'))
						{
							object.required = [];
						}
						
						object.required.push(propertyName);
					}
					
					// delete the boolean 'required' property
					delete object.properties[propertyName].required;
				}
			}
		);
	}
	
	if(key === 'required' && object.hasOwnProperty(key) && typeof object[key] === 'boolean')
	{
		delete object[key];
	}
	
	if(key === 'type')
	{
		if(value === 'any')
		{
			object[key] = 'string'
		}
		else if(value === 'integer')
		{
			object.format = 'int64'
		}
		// if the current element is an output pin
		else if(['inputPin', 'outputPin'].indexOf(type) > -1 && value && (typeof value) === 'string')
		{
			// check if the value of type indicates a JSON data MIME type
			if(value == 'text/javascript' || value == 'application/json')
			{
				object[key] = 'object'
			}
			else
			{
				// verify that the type has the form "xxx/xxx"
				// this is an indicator for a MIME type specification (due to recursion other typical values like "number" or "string" may occur)
				var re = new RegExp('^[^/]+/[^/]+$', 'g');
				var result = re.exec(value);
				
				// delete the type specification for binary pins (JSON pin was handled in if-statement)
				if(result && result.length > 0)
				{
					delete object[key];
				}
			}
		}
	}
}

function traverse(o,func,typ) {
	for (var i in o) {
		func.apply(this,[o,i,o[i],typ]);
		if (o[i] !== null && typeof(o[i])=="object") {
			//going on step down in the object tree!!
			traverse(o[i],func, typ);
		}
	}
}

//class methods
method.updateSchemaAndSchemaString = function() {
	traverse(this.schema, deleteUselessKeys, this.type);
	this.schemaString = JSON.stringify(this.schema, null, '\t').replace(/\n/g, '\n\t\t');
};
// export the class
module.exports = Definition;