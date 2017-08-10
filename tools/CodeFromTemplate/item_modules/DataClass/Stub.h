{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{DataClass.stubHeaderPath}}
// NEVER TOUCH this file!

#include <stdint.h>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <rapidjson/document.h>

#include <ConnectedVision.h>
#include <general.h>

{% if DataClass.children.length %}

// include child classes
{% for c in DataClass.children %}
  {% if c.classHeaderPath %}
#include "{{global.relativeStubToSrcPath}}{{c.classHeaderPath}}"
  {% endif %}
{% endfor %}
{% endif %}

#ifndef {{DataClass.stubName}}_def
#define {{DataClass.stubName}}_def

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

/**
 * stub class for: {{DataClass.className}}
 * 
 * module: {{global.moduleName}}
 * description: {{DataClass.description}}
 */
class {{DataClass.stubName}} {

public:
	{{DataClass.stubName}}();
	{{DataClass.stubName}}(const {{DataClass.stubName}}& other);
	{{DataClass.stubName}}(const rapidjson::Value& value);
	{{DataClass.stubName}}(const std::string& str);
	virtual ~{{DataClass.stubName}}();
	{{DataClass.stubName}} &operator =(const {{DataClass.stubName}}& other);
	{{DataClass.stubName}} &operator =({{DataClass.stubName}}&& other) noexcept;

	virtual void clear();
	virtual void parseJson(const rapidjson::Value& value);
	virtual void parseJson(const char *str);
	virtual void parseJson(const std::string str) { this->parseJson( str.c_str() ); };
	virtual void parseJson(const boost::shared_ptr<const std::string> str) { this->parseJson( str->c_str() ); };
	virtual std::string toJsonStr() const;
	virtual std::string toJson() const;
	virtual rapidjson::Value& toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const;

public:
{% for p in DataClass.properties %}
	/* {{p.id}} - {{p.description}} */
	virtual {{p.CType}} get_{{p.id}}() const;
	virtual const {{p.CConstType}} getconst_{{p.id}}() const;
	virtual void set_{{p.id}}({{p.CType}} value);
{/* add implicit conversion to pointer in setter */}
{% if p.isPtr %}
	virtual void set_{{p.id}}(const {{p.CBaseType}} &value) { {{p.CType}} ptr = boost::make_shared<{{p.CBaseType}}>(value); set_{{p.id}}(ptr); };
{% endif %}
{/* add implicit JSON parser for sub-classes */}
{% if p.type == "object" %}
	virtual void set_{{p.id}}(const rapidjson::Value& value) { {{p.id}}->parseJson( value ); };
{% endif %}
{/* add array functions */}
{% if p.type == "array" %}
	// array functions
	virtual {{p.items.CType}} get_{{p.id}}(int index) const;
	virtual const {{p.items.CType}}& getconst_{{p.id}}(int index) const;
	virtual void add_{{p.id}}({{p.items.CType}} value);
 {% if p.items.isPtr %}
	virtual void add_{{p.id}}(const {{p.items.CBaseType}} &value) { {{p.items.CType}} ptr = boost::make_shared<{{p.items.CBaseType}}>(value); add_{{p.id}}(ptr); };
 {% endif %}
 {% endif %}
{/* add enum functions */}
{% if p.enum && p.type != 'array' %}
	// enum functions
	virtual bool is_{{p.id}}(const {{p.CType}}& value) const;
 {% for e in p.enum %}
	const static {{p.CType}} {{p.id}}_{{e|plainString}};
	virtual bool is_{{p.id}}_{{e|plainString}}() const { return is_{{p.id}}( {{DataClass.stubName}}::{{p.id}}_{{e|plainString}} ); }
	virtual void set_{{p.id}}_{{e|plainString}}() { set_{{p.id}} ( {{DataClass.stubName}}::{{p.id}}_{{e|plainString}} ); }
 {% endfor %}
{% endif %}

{% endfor %}

protected:
	/// lock typedef
	typedef boost::unique_lock<boost::shared_mutex>	Lock;
	/// mutex
//FIXME	boost::shared_mutex mutex;

{% for p in DataClass.properties %}
	/** {{p.description}} */
	{{p.CType}} {{p.id}};
	
{% endfor %}
};

{{ closeNamespace(global.namespace) }}

#endif // {{DataClass.stubName}}_def