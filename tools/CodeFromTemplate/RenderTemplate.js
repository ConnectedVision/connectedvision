var fs = require('fs');
var os = require('os');
var swig = require('swig');

/**
 * Swig filter: removing all non alpha-numeric characters.
 *  
 * @param input	input text
 * 
 * @returns	text without white-spaces or special characters 
 */
function swigFilterPlainString(input) {
	input = String(input); // enforce input to be a string
	return input.replace(/[^0-9a-zA-Z_]/g, ''); 
}
swig.setFilter('plainString', swigFilterPlainString);

/**
 * Swig filter: replace all non alpha-numeric characters with underscore
 *  
 * @param input	input text
 * 
 * @returns	text without white-spaces or special characters 
 */
function swigFilterUnderscore(input) {
	input = String(input); // enforce input to be a string
	return input.replace(/[^0-9a-zA-Z_]/g, ''); 
}
swig.setFilter('_', swigFilterUnderscore);

/**
 * Swig filter: write as qualified namespace
 *	 e.g. ["ConnecetdVision", "Module"] -> ConnectedVision::Module
 *
 * @param input	array of namespaces
 * 
 * @returns	qualified namespace string
 */
function swigFilterQualifyNamespace(input) {
	return input.join("::");
}
swig.setFilter('qualify', swigFilterQualifyNamespace);


/**
 * Swig filter: prepare tab indention
 * 
 * @param input		number if tabs
 * @returns {String} indention string
 */
function swigFilterTabs(input) {
	var str = "";
	for ( var i = 0; i < input; i++)
		str += "\t";
	return str; 
}
swig.setFilter('tabs', swigFilterTabs);

// function to render a templateFile into a targetFile
function renderTemplateToFile(templateFile, targetFile, context) {
	var source = fs.readFileSync(templateFile).toString();

	
	// remove template comments
	source = source.replace(/(?:\r\n|\r|\n)?[\t ]*{\/\*(.)*\*\/}/g, '');
	
	// remove all whitespaces before and all line-feeds before and after logical tags
	source = source.replace(/[\t ]*{%/g, '{%');
	source = source.replace(/%}[\t ]*(?:\r\n|\r|\n)/g, '%}');

	var result = swig.render(source, { locals: context });
	
	// replace all \n without a preceding \r with \r\n if the current OS is Windows since swig replaces all \r\n with \n (regardless of the current OS or the specified template)
	if(os.platform() == 'win32')
	{
		// negative look behinds are not supported in JavaScript
		// result = result.replace('(?<!\r)\n', '\r\n');
		result = result.replace(/([^\r]?)\n/g, '$1\r\n');
	}
	
	log.debug('[RenderTemplate] write file: ' + targetFile);
	fs.writeFileSync(targetFile, result, 'utf8');
};

// function to render a templateFile into a string
function renderTemplate(templateFile, context) {
	var source = fs.readFileSync(templateFile).toString();
	var result = swig.render(source, { locals: context });
	return result;
};

/*
 * exports functions to node.js
 */
exports.renderTemplateToFile = renderTemplateToFile;
exports.renderTemplate = renderTemplate;

