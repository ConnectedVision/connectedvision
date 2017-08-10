ko.observableModuleURL = function(defaultValue) {
	var shadow = ko.observable(defaultValue);
	return ko.computed({
		read: function() {
			return shadow();
		},
		write: function(url) {
			// remove tailing slash from URL
			while ( url[url.length-1] == '/' )
				url = url.substring(0, url.length - 1);

			// remove description URL parts
			var idx = url.lastIndexOf("moduleDescription");
			if ( idx > 0 )
				url = url.substring(0, idx - 1);
			var idx = url.lastIndexOf("inputDescription");
			if ( idx > 0 )
				url = url.substring(0, idx - 1);
			var idx = url.lastIndexOf("outputDescription");
			if ( idx > 0 )
				url = url.substring(0, idx - 1);

			// make sure that URL starts with http or https
			if ( url && url.indexOf("http://") != 0 && url.indexOf("https://") != 0 )
				url = "http://" + url;

			shadow( url );
		}
	});
}

ko.observableStopWatch = function() {
	var duration = ko.observable(0);
	var stopWatch = ko.computed({
		read: function() {
			return duration();
		}
	});
	stopWatch.startTime = ko.observable(0);
	stopWatch.start = function() {
		this.startTime( (new Date()).getTime() );
	};
	stopWatch.stop = function() {
		if ( this.startTime() )
			duration( (new Date()).getTime() - this.startTime() );
		this.startTime(0);
	};
	stopWatch.isRunning = function() {
		return ( this.startTime() != 0 );
	};
	
	return stopWatch;
}

ko.observableAverage = function(valueFn, size) {
	var avg_data = [];
	var avg_index = 0;
	var avg_sum = ko.observable(0);

	// automatically update on change of value
	valueFn.subscribe(function(value) {
		var sum = avg_sum() - (avg_data[ avg_index ] || 0) + value;
		avg_data[ avg_index ] = value;
		++avg_index; if ( avg_index >= size ) avg_index = 0;
		avg_sum( sum );
	});
	valueFn.extend({ notify: 'always' });
	
	var avg = ko.computed({
		read: function() {
			var sum = avg_sum();
			return sum / avg_data.length;
		}
	}).extend({ throttle: 5 });
	avg.reset = function() {
		avg_data = [];
		avg_index = 0;
		avg_sum(0);
	};
	
	return avg
}

