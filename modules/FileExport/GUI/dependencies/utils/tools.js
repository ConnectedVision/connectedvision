function getUrlParams() {
	var urlParams = {};
	var match,
		pl     = /\+/g,  // Regex for replacing addition symbol with a space
		search = /([^&=]+)=?([^&]*)/g,
		decode = function (s) { return decodeURIComponent(s.replace(pl, " ")); },
		query  = window.location.search.substring(1);

	while (match = search.exec(query))
	   urlParams[decode(match[1])] = decode(match[2]);
	   
	return urlParams;
};

function sendComand( cmd ) {
	if ( configURL == "" )
		return;

	$.ajax({ 
		url: configURL+"/"+cmd,
		dataType: "jsonp",
		success: function( data ) {
			moduleCount = 0;
			pendingModuleCount = 0;
			$("#canvas").empty();
			if ( displayStatus($("#canvas"), data) )
			{
				setTimeout( getStatus, 500);	
			}
		}
	});			
}

function fileLoad( callback ) {
	$("<input type='file' />").change( function(event) {
		// callback for hidden fileAPI element 
		var file = event.target.files[0]; // FileList object
		if ( !file )
			return;

		// file reader
		var reader = new FileReader();

		// set on load callback
		reader.onload = function(e) {
			callback( e.target.result );
		};

		// start reading file
		reader.readAsText(file);
	}).click();
}		

function fileSave(filename, data) {
	var blob = new Blob([data], {type: "application/javascript;charset=utf-8"});
	saveAs(blob, filename);
}

function isInt(value) {
    var er = /^[0-9]+$/;
    return ( er.test(value) ) ? true : false;
}

function isFloat(value) {
    var er = /^[0-9]*.?[0-9]+$/;
    return ( er.test(value) ) ? true : false;
}

function intPadding(val, size) {
    var s = "000000000" + val;
    return s.substr(s.length-size);
}

