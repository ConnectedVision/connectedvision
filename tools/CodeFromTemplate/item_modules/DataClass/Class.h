{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{DataClass.classHeaderPath}}
// This file contains the business logic.
// It is generated once and will NOT be OVERWRITTEN by CodeFromTemplate.

#ifndef {{DataClass.className}}_def
#define {{DataClass.className}}_def

#include "{{DataClass.stubHeaderPath}}"

{{ openNamespace(global.namespace) }}

// if you want to extend the auto-generated class, enable the line below
//#define {{DataClass.className}}_extended

#ifdef {{DataClass.className}}_extended
/**
 * {{DataClass.className}}
 * 
 * module: {{global.moduleName}}
 * description: {{DataClass.description}}
 */
class {{DataClass.className}} : public {{DataClass.stubName}} {

public:
	{{DataClass.className}}() {};
	{{DataClass.className}}(const ::rapidjson::Value& value) : {{DataClass.stubName}}(value) {};
	{{DataClass.className}}(const std::string& str) : {{DataClass.stubName}}(str) {};
	virtual ~{{DataClass.className}}() {};

 // TODO --> Your declarations and code comes HERE! <--

};
typedef boost::shared_ptr<{{DataClass.className}}> {{DataClass.className}}_p;
#endif // {{DataClass.className}}_extended

{{ closeNamespace(global.namespace) }}

#include "{{DataClass.defaultHeaderPath}}"

#endif // {{DataClass.className}}_def