{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{OutputPin.stubHeaderPath}}
// NEVER TOUCH this file!

#include <IStore.h>
#include <IStoreCV.h>
#include <IConnectedVisionModule.h>
#include <ConnectedVisionOutputPin.h>
#include <Module/Control/Class_generic_status.h>

#include "{{global.relativeStubToSrcPath}}{{DataClass.classHeaderPath}}"

#ifndef {{OutputPin.stubName}}_def
#define {{OutputPin.stubName}}_def

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

/**
 * stub class for {{OutputPin.name}}
 *
 * module: {{global.moduleName}}
 * description: {{item.description}}
 */
class {{OutputPin.stubName}} : public ConnectedVisionOutputPin< boost::shared_ptr<{{DataClass.className}}> > {
public:
	static const pinID_t PinID() { return "{{OutputPin.PinID}}"; };
	static const bool hasPinID( pinID_t id ) { return ( id == PinID() ); };
	{{OutputPin.stubName}}(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<{{DataClass.className}}> > > dataStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<{{DataClass.className}}> >( dataStore) {};
	
	/// deprecated constructor
	{{OutputPin.stubName}}(boost::shared_ptr< Store::IStoreCV< boost::shared_ptr<{{DataClass.className}}> > > dataStore, boost::shared_ptr< Store::IStore< boost::shared_ptr<Class_generic_status> > > statusStore) :
			ConnectedVisionOutputPin< boost::shared_ptr<{{DataClass.className}}> >( dataStore) {};

};

{{ closeNamespace(global.namespace) }}

#endif // {{OutputPin.stubName}}_def