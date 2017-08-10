ko.dirtyFlag = function(watchedData, isInitiallyDirty, invertFlag) {

	var closure = {
		watchedData: watchedData,
		invertFlag: invertFlag || false,
		initialState: ko.observable()
	}
	
	var dirtyFlag = ko.computed( function() {
		return ( closure.initialState() != ko.toJSON( closure.watchedData ) ) ^ invertFlag;
	}).extend({throttle: 200}) ;
	
	dirtyFlag.reset = function() {
		closure.initialState( ko.toJSON( closure.watchedData ) );
	};
	
	if ( !isInitiallyDirty )
		dirtyFlag.reset();

	return dirtyFlag;
};

ko.bindingHandlers.slideVisible = {
	init: function(element, valueAccessor) {
		// Initially set the element to be instantly visible/hidden depending on the value
		var value = valueAccessor();
		$(element).toggle(ko.unwrap(value)); // Use "unwrapObservable" so we can handle values that may or may not be observable
	},
	update: function(element, valueAccessor) {
		// Whenever the value subsequently changes, slowly fade the element in or out
		var value = valueAccessor();
//		ko.unwrap(value) ? $(element).slideDown() : $(element).slideUp();
		ko.unwrap(value) ? $(element).show() : $(element).hide();
	}
};
 
ko.loadTemplates = function( templateList, callback ) {
	var loadedTemplates = [];
	ko.utils.arrayForEach(templateList, function(name) {
		$.get("templates/" + name + ".html", function( templateData ) {
			$("body").append( templateData );
//			$("body").append( "<script id=\"" + name + "\" type=\"text/html\">" + templateData + "<\/script>" );
			loadedTemplates.push(name);
			if ( templateList.length === loadedTemplates.length ) {
				callback();
			}
		}, "html");
	});
}
 