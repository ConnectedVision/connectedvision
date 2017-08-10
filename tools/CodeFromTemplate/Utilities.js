// function to clone an object
exports.clone = function (o) {
	return JSON.parse(JSON.stringify(o));
}

// function to remove duplicate sections
exports.mergeSections = function (arr) {    
   for(var o = {}, i; i=arr.shift(); o[i.name] = i.guid + (o[i.name] || 0));
   for(i in o) arr.push({name:i, guid:o[i]});
}

exports.merge = function() {
    var destination = {},
        sources = [].slice.call( arguments, 0 );
    sources.forEach(function( source ) {
        var prop;
        for ( prop in source ) {
            if ( prop in destination && Array.isArray( destination[ prop ] ) ) {
                
                // Concat Arrays
                destination[ prop ] = destination[ prop ].concat( source[ prop ] );
                
            } else if ( prop in destination && typeof destination[ prop ] === "object" ) {
                
                // Merge Objects
                destination[ prop ] = exports.merge( destination[ prop ], source[ prop ] );
                
            } else {
                
                // Set new values
                destination[ prop ] = source[ prop ];
                
            }
        }
    });
    return destination;
};