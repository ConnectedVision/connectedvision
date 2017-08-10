{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{DataClass.stubSourcePath}}
// NEVER TOUCH this file!

#include <utility>

#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>
#include <boost/make_shared.hpp>

#include "{{DataClass.stubHeaderName}}"
#include "{{global.relativeStubToSrcPath}}{{DataClass.classHeaderName}}"

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}

{/* declare const enums */}
{% for p in DataClass.properties %}
	{% for e in p.enum %}
const {{p.CType}} {{DataClass.stubName}}::{{p.id}}_{{e|plainString}} = {% if p.exttype == 'string' %}
 boost::make_shared<std::string>("{{e}}"); {%- elseif p.type == 'integer' %}
 {{loop.index0}}; {%- else %}
 {{e}}; {%- endif %}

	{% endfor %}
{% endfor %}

{/* cloneProperty */}
{% macro cloneProperty( x ) %}
{% if !x.isPtr %}
{{x.id}} = other.{{x.id}};{% else %}
if ( other.{{x.id}} ) {{x.id}} = boost::make_shared<{{x.CBaseType}}>(*other.{{x.id}});{% endif %}{% endmacro %}

{/* cloneArrayMacro */}
{% macro cloneArrayMacro( x, variableName, recursionDepth ) %}
{% set _variable = variableName | default('other.'+x.id) %}
{% set _depth = recursionDepth | default(0) %}
{% set _n = 'n' + _depth %}
{% set _a = 'a' + _depth %}
{% set _depth_plus_1 = _depth + 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% set _a1 = 'a' + _depth_plus_1 %}
{% set _i = 'i' + _depth %}
{% set _r = '.' %}
{% if x.isPtr %}{% set _r = '->' %}{% endif %}
{{_depth|tabs}}		const auto& {{_n}} = {{_variable}};	{/* get JSON array node */}
{{_depth|tabs}}		auto {{_a}} = boost::make_shared<{{x.CBaseType}}>( ({{_n}}{{_r}}size()) );	{/* init C++ vector with size */}
{{_depth|tabs}}		for (size_t {{_i}} = 0; {{_i}} < {{_n}}{{_r}}size(); ++{{_i}})	{/* loop over JSON array and fill C++ vector */}
{{_depth|tabs}}		{
{% if x.items.type == 'array' %}
					{/* handle sub arrays, call macro recursively */}
{{ cloneArrayMacro(x.items, _n+_r+'at('+_i+')', _depth+1 ) }}
{/* reset variables, macros have no stack and simply overwrites the old values */}
{% set _variable = variableName | default('other.'+x.id) %}
{% set _depth = recursionDepth | default(0) %}
{% set _n = 'n' + _depth %}
{% set _a = 'a' + _depth %}
{% set _depth_plus_1 = _depth + 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% set _a1 = 'a' + _depth_plus_1 %}
{% set _i = 'i' + _depth %}
{{_depth|tabs}}			{{_a}}{{_r}}at({{_i}}) = {{_a1}};
{% else %}
					{/* final dimension of array, get actual value */}
					{% if !x.items.isPtr %}
{{_depth|tabs}}			{{_a}}{{_r}}at({{_i}}) = {{_n}}{{_r}}at({{_i}});
					{% else %}
{{_depth|tabs}}			if ( {{_n}}{{_r}}at({{_i}}) )
{{_depth|tabs}}				{{_a}}{{_r}}at({{_i}}) = boost::make_shared<{{x.items.CBaseType}}>( *{{_n}}{{_r}}at({{_i}}) );
					{% endif %}
{% endif %}
{{_depth|tabs}}		}{% endmacro %}

// --> Do NOT EDIT <--
/* copy constructors */
{{DataClass.stubName}}::{{DataClass.stubName}}(const {{DataClass.stubName}}& other)
{
	// TODO: other.readLock
{% for p in DataClass.properties %}
	// {{p.id}}
{% if p.type == 'array' %}
	{
{{ cloneArrayMacro(p) }}
		{{p.id}} = a0;
	}
{% else %}
	{% if !p.isPtr %}
	{{p.id}} = other.{{p.id}};
	{% else %}
	if ( other.{{p.id}} ) 
		{{p.id}} = boost::make_shared<{{p.CBaseType}}>(*other.{{p.id}});
	{% endif %}
{% endif %}
{% endfor %}
}

// --> Do NOT EDIT <--
/* copy assignment operator */
{{DataClass.stubName}}& {{DataClass.stubName}}::operator =(const {{DataClass.stubName}}& other)
{
	{{DataClass.stubName}} tmp(other); // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

// --> Do NOT EDIT <--
/* mopy assignment operator */
{{DataClass.stubName}}& {{DataClass.stubName}}::operator =({{DataClass.stubName}}&& other) noexcept
{
{% for p in DataClass.properties %}
	// {{p.id}}
    std::swap({{p.id}}, other.{{p.id}});
{% endfor %}

	return *this;
}

// --> Do NOT EDIT <--
/* default constructors */
{{DataClass.stubName}}::{{DataClass.stubName}}()
{
	clear();
}

// --> Do NOT EDIT <--
{{DataClass.stubName}}::{{DataClass.stubName}}(const rapidjson::Value& value)
{
	clear();
	parseJson( value );
}

// --> Do NOT EDIT <--
{{DataClass.stubName}}::{{DataClass.stubName}}(const std::string& str)
{
	clear();
	parseJson( str );
}

// --> Do NOT EDIT <--
{/* destructor */}
{{DataClass.stubName}}::~{{DataClass.stubName}}()
{
}

// --> Do NOT EDIT <--
{/* clear and reset the class */}
void {{DataClass.stubName}}::clear()
{
{% for p in DataClass.properties %}
{/* test for supported extended type first */}
 {% if p.exttype == 'id' %}
	this->{{p.id}} = "{{p.default}}"; {/* TODO default -> ID_NULL */}
 {% elseif p.exttype == 'timestamp' %}
	this->{{p.id}} = {{p.default|default('0')}};
{/* now match base JSON type */}
 {% elseif p.type == 'string' %}
	this->{{p.id}}.reset( new std::string("{{p.default}}") );
 {% elseif p.type == 'object' %}
	this->{{p.id}}.reset( new {{p.CBaseType}} ); {/* TODO use default constructor -> {{p.CBaseType}}() */}
 {% elseif p.type == 'array' %}
	this->{{p.id}}.reset( new {{p.CBaseType}} );
 {% elseif p.type == 'any' %}
	this->{{p.id}}.reset( new std::string("{{p.default}}") );
 {% elseif p.type == 'integer' %}
	this->{{p.id}} = static_cast<{{p.CType}}>({{p.default|default('0')}});
 {% elseif p.type == 'number' %}
	this->{{p.id}} = static_cast<{{p.CType}}>({{p.default|default('0.0')}});
 {% elseif p.type == 'boolean' %}
	this->{{p.id}} = static_cast<{{p.CType}}>({{p.default|default('false')}});
 {% else %}
	#error "UNKNOWN type ({{p.type}}) for this->{{p.id}}"
 {% endif %}
{% endfor %}
}

// --> Do NOT EDIT <--
void {{DataClass.stubName}}::parseJson(const char *str)
{
	// ignore empty data
	if ( str[0] == 0 )
		return;
	
	// parse data
	rapidjson::Document document;
	if (document.Parse<0>(str).HasParseError())
	{
		std::string context;
		size_t off = document.GetErrorOffset();
		size_t i, line_start = 0, context_start = 0;
		int num_line = 1;
		for ( i = 0; (i < off) && str[i]; i++ )
		{
			if ( str[i] == '\n' )
			{ line_start = i+1; context_start = i+1; num_line++; }
			if ( str[i] == '{' || str[i] == '[' )
			{ context_start = i; }
		}
		for ( i = context_start; str[i]; i++ )
		{
			if ( str[i] == '\n' || str[i] == '\r' ) break;
			context += str[i];
			if ( str[i] == '}' || str[i] == ']' ) break;
		}
		throw ConnectedVision::runtime_error( std::string("parse error of JSON Object: ") + rapidjson::GetParseError_En(document.GetParseError()) + std::string(" at line ") + ConnectedVision::intToStr( num_line ) + ": " + context);
	}

	parseJson(document);
}

{/* read value from JSON node */}
{% macro valueFromJSONNode( x, variableName ) %}
{% set _variable = variableName | default('value["'+x.id+'"]') %}
{/* test JSON type and set value */} {%- if x.exttype == 'id' -%}
ConnectedVision::strToID( {{_variable}}.GetString() ) {%- elseif x.exttype == 'timestamp' -%}
{{_variable}}.GetInt64() {/* now match base JSON type */} {%- elseif x.type == 'string' -%}
{{x.CType}}( new {{x.CBaseType}}( {{_variable}}.GetString() ) ) {%- elseif x.type == 'object' -%}
{{x.CType}}( new {{x.CBaseType}}( {{_variable}} ) ) {%- elseif x.type == 'array' -%}
#error "valueFromJSONNode MACRO should never be called for an array" {%- elseif x.type == 'any' -%}
{{x.CType}}( new {{x.CBaseType}}( ConnectedVision::jsonToStr({{_variable}}) ) ) {%- elseif x.type == 'integer' -%}
{{_variable}}.GetInt64() {%- elseif x.type == 'number' -%}
{{_variable}}.GetDouble() {%- elseif x.type == 'boolean' -%}
{{_variable}}.GetBool() {%- else -%}
#error "UNKNOWN type ({{x.type}}) for this->{{x.id}}"
{%- endif %}{% endmacro %}
// --> Do NOT EDIT <--
void {{DataClass.stubName}}::parseJson(const rapidjson::Value& value)
{
	clear();
	if ( !value.IsObject() )
		throw ConnectedVision::runtime_error( "no JSON Object");

{/* test JSON type and set value */}
{% for p in DataClass.properties %}
{% if !p.virtual %}
	// {{p.id}}
{/* test for supported extended type first */}
{% if p.exttype == 'id' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsString())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% elseif p.exttype == 'timestamp' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsInt64())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{/* now match base JSON type */}
{% elseif p.type == 'string' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsString())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% elseif p.type == 'object' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsObject())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% elseif p.type == 'array' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsArray())
	{
{/* parse JSON array and save value to a? */}
{% macro parseJsonArrayMacro( x, variableName, recursionDepth ) %}
{% set _variable = variableName | default('value["'+x.id+'"]') %}
{% set _depth = recursionDepth | default(0) %}
{% set _n = 'n' + _depth %}
{% set _a = 'a' + _depth %}
{% set _depth_plus_1 = _depth + 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% set _a1 = 'a' + _depth_plus_1 %}
{% set _i = 'i' + _depth %}
{{_depth|tabs}}		const rapidjson::Value& {{_n}} = {{_variable}};	{/* get JSON array node */}
{{_depth|tabs}}		{{x.CType}} {{_a}}( new {{x.CBaseType}}({{_n}}.Size()) );	{/* init C++ vector with size of JSON array */}
{{_depth|tabs}}		for (rapidjson::SizeType {{_i}} = 0; {{_i}} < {{_n}}.Size(); {{_i}}++)	{/* loop over JSON array and fill C++ vector */}
{{_depth|tabs}}		{
						{% if x.items.type == 'array' %}
						{/* handle sub arrays, call macro recursively */}
{{ parseJsonArrayMacro(x.items, _n+'['+_i+']', _depth+1 ) }}
{/* reset variables, macros have no stack and simply overwrites the old values */}
{% set _variable = variableName | default('value["'+x.id+'"]') %}
{% set _depth = recursionDepth | default(0) %}
{% set _n = 'n' + _depth %}
{% set _a = 'a' + _depth %}
{% set _depth_plus_1 = _depth + 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% set _a1 = 'a' + _depth_plus_1 %}
{% set _i = 'i' + _depth %}
{{_depth|tabs}}			{{_a}}->at({{_i}}) = {{_a1}};
						{% else %}
						{/* final dimension of array, get actual value */}
{{_depth|tabs}}			{{_a}}->at({{_i}}) = {{ valueFromJSONNode(x.items, _n+'['+_i+']') }};	{/* set actual data */}
						{% endif %}
{{_depth|tabs}}		}{% endmacro %}
{{ parseJsonArrayMacro(p) }}
		set_{{p.id}}( a0 );
	}
{% elseif p.type == 'any' %}
	if ((value.HasMember("{{p.id}}")) && ( value["{{p.id}}"].IsObject() || value["{{p.id}}"].IsArray() || value["{{p.id}}"].IsInt64() || value["{{p.id}}"].IsNumber() || value["{{p.id}}"].IsBool() ))
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% elseif p.type == 'integer' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsInt64())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% elseif p.type == 'number' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsNumber())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% elseif p.type == 'boolean' %}
	if ((value.HasMember("{{p.id}}")) && value["{{p.id}}"].IsBool())
	{
		set_{{p.id}}( {{valueFromJSONNode(p)}} );
	}
{% else %}
	#error "UNKNOWN type ({{p.type}}) for this->{{p.id}}"
{% endif %}
{% if p.required %}
	else
		throw ConnectedVision::runtime_error( "required member is missing: '{{p.id}}'");

{% endif %}
{% endif %}
{% endfor %}
}

// --> Do NOT EDIT <--
std::string {{DataClass.stubName}}::toJsonStr() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
std::string {{DataClass.stubName}}::toJson() const
{
	rapidjson::StringBuffer s;
	rapidjson::Document doc; doc.SetObject();
	this->toJson(doc, doc.GetAllocator());
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);
	doc.Accept(writer);
	return std::string(s.GetString());
}

// --> Do NOT EDIT <--
rapidjson::Value& {{DataClass.stubName}}::toJson(rapidjson::Value& node, rapidjson::Value::AllocatorType& allocator) const
{
{% for p in DataClass.properties %}
{% if !p.virtual %}
	{ // {{p.id}}
{/* test for supported extended type first */}
{% if p.exttype == 'id' %}
		node.AddMember("{{p.id}}", rapidjson::Value().SetString( ConnectedVision::IDToChar( get_{{p.id}}() ), allocator), allocator);
{% elseif p.exttype == 'timestamp' %}
		node.AddMember("{{p.id}}", rapidjson::Value().SetInt64( get_{{p.id}}() ), allocator);
{/* now match base JSON type */}
{% elseif p.type == 'string' %}
		node.AddMember("{{p.id}}", rapidjson::Value().SetString( get_{{p.id}}()->c_str(), allocator), allocator);
{% elseif p.type == 'object' %}
		node.AddMember("{{p.id}}", get_{{p.id}}()->toJson( rapidjson::Value().SetObject(), allocator), allocator);
{% elseif p.type == 'array' %}
{/* write array to JSON */}
{% macro toJsonArrayMacro( x, rvalue_reference, variableName, recursionDepth ) %} {/* rvalue_reference is used to specify rvalue (&&) or lvalue (&) references - rvalue for const functions, lvalue for non-const functions on right side of assignment operation */}
{% set _variable = variableName | default('get_'+x.id+'()') %}
{% set _depth = recursionDepth | default(0) %}
{% set _n = 'n' + _depth %}
{% set _a = 'a' + _depth %}
{% set _i = 'i' + _depth %}
{{_depth|tabs}}		rapidjson::Value {{_n}}; {{_n}}.SetArray();		{/* prepare JSON array */}
{% if rvalue_reference %}
{{_depth|tabs}}		{{x.CType}}&& {{_a}} = {{_variable}}; {/* shortcut to C++ vector */} // rvalue reference for const functions
{% else %}
{{_depth|tabs}}		{{x.CType}}& {{_a}} = {{_variable}}; {/* shortcut to C++ vector */} // lvalue reference for non-const functions like vector::at()
{% endif %}
{{_depth|tabs}}		for (size_t {{_i}} = 0; {{_i}} < {{_a}}->size(); {{_i}}++)	{/* loop over C++ vector */}
{{_depth|tabs}}		{
{{_depth|tabs}}			// process array level {{_depth}}
{% if x.items.type == 'array' %}
{/* handle sub arrays, call macro recursively */}
{{ toJsonArrayMacro(x.items, false, _a+'->at('+_i+')', _depth+1 ) }}
{/* reset variables, macros have no stack and simply overwrites the old values */}
{% set _variable = variableName | default('value["'+x.id+'"]') %}
{% set _depth = recursionDepth | default(0) %}
{% set _n = 'n' + _depth %}
{% set _a = 'a' + _depth %}
{% set _depth_plus_1 = _depth + 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% set _n1 = 'n' + _depth_plus_1 %}
{% set _i = 'i' + _depth %}
{{_depth|tabs}}			// add actual data to array level {{_depth}}
{{_depth|tabs}}			{{_n}}.PushBack({{_n1}}, allocator);	{/* push sub array */}
{% elseif x.items.exttype == 'id' %}
{{_depth|tabs}}			// final level of array, add ID
{{_depth|tabs}}			{{_n}}.PushBack(rapidjson::Value().SetString( ConnectedVision::IDToChar( {{_a}}->at({{_i}}) ), allocator), allocator);	{/* push actual data */}
{% elseif x.items.type == 'string' %}
{{_depth|tabs}}			// final level of array, add string
{{_depth|tabs}}			{{_n}}.PushBack(rapidjson::Value().SetString( {{_a}}->at({{_i}})->c_str(), allocator), allocator);	{/* push actual data */}
{% elseif x.items.type == 'integer' %}
{{_depth|tabs}}			// final level of array, add integer
{{_depth|tabs}}			{{_n}}.PushBack(rapidjson::Value().SetInt64( {{_a}}->at({{_i}}) ), allocator);	{/* push actual data */}
{% elseif x.items.type == 'number' %}
{{_depth|tabs}}			// final level of array, add number
{{_depth|tabs}}			{{_n}}.PushBack(rapidjson::Value().SetDouble( {{_a}}->at({{_i}}) ), allocator);	{/* push actual data */}
{% elseif x.items.type == 'boolean' %}
{{_depth|tabs}}			// final level of array, add boolean
{{_depth|tabs}}			{{_n}}.PushBack(rapidjson::Value().SetBool( {{_a}}->at({{_i}}) ), allocator);	{/* push actual data */}
{% elseif x.items.type == 'any' %}
{{_depth|tabs}}			// final level of array, add raw data
{{_depth|tabs}}			if ( {{_a}}->at({{_i}}) )	// ensure that we have no NULL pointer
{{_depth|tabs}}			{
{{_depth|tabs}}				rapidjson::Document doc(&allocator);
{{_depth|tabs}}				doc.Parse<0>( {{_a}}->at({{_i}})->c_str() );
{{_depth|tabs}}				{{_n}}.PushBack(static_cast<rapidjson::Value&>(doc), allocator);
{{_depth|tabs}}			}
{% else %}
{{_depth|tabs}}			// final dimension of array, add actual value
{{_depth|tabs}}			if ( {{_a}}->at({{_i}}) )	// ensure that we have no NULL pointer
{{_depth|tabs}}			{
{{_depth|tabs}}				{{_n}}.PushBack({{_a}}->at({{_i}})->toJson( rapidjson::Value().SetObject(), allocator), allocator);	{/* push actual data */}
{{_depth|tabs}}			}
{% endif %}
{{_depth|tabs}}		}{% endmacro %}
{{ toJsonArrayMacro(p, true) }}
		node.AddMember("{{p.id}}", n0, allocator);
{% elseif p.type == 'any' %}
		rapidjson::Document doc(&allocator);
		doc.Parse<0>( get_{{p.id}}()->c_str() );
		node.AddMember("{{p.id}}", static_cast<rapidjson::Value&>(doc), allocator);
{% elseif p.type == 'integer' %}
		node.AddMember("{{p.id}}", rapidjson::Value().SetInt64( get_{{p.id}}() ), allocator);
{% elseif p.type == 'number' %}
		node.AddMember("{{p.id}}", rapidjson::Value().SetDouble( get_{{p.id}}() ), allocator);
{% elseif p.type == 'boolean' %}
		node.AddMember("{{p.id}}", rapidjson::Value().SetBool( get_{{p.id}}() ), allocator);
{% else %}
		#error "UNKNOWN type ({{p.type}}) for this->{{p.id}}"
{% endif %}
	}
{% endif %}
{% endfor %}
	return node;
}

{/* getter and setter functions */}
{% for p in DataClass.properties %}
// --> Do NOT EDIT <--
{{p.CType}} {{DataClass.stubName}}::get_{{p.id}}() const
{
	return( this->{{p.id}} );
}

// --> Do NOT EDIT <--
const {{p.CConstType}} {{DataClass.stubName}}::getconst_{{p.id}}() const
{
{%if p.isPtr %}
	return( boost::static_pointer_cast<const {{p.CBaseType}}>(this->{{p.id}}) );
{% else %}
	return( this->{{p.id}} );
{% endif %}
}

// --> Do NOT EDIT <--
void {{DataClass.stubName}}::set_{{p.id}}({{p.CType}} value)
{
	{/* TODO minimum, maximum, constrain check */}
	this->{{p.id}} = value;
}

{/* add array specific getter & setter */}
{% if p.type == 'array' %}
// --> Do NOT EDIT <--
{{p.items.CType}} {{DataClass.stubName}}::get_{{p.id}}(int index) const
{
	return( this->{{p.id}}->at(index) );
}

// --> Do NOT EDIT <--
const {{p.items.CType}}& {{DataClass.stubName}}::getconst_{{p.id}}(int index) const
{
	return( this->{{p.id}}->at(index) );
}

// --> Do NOT EDIT <--
void {{DataClass.stubName}}::add_{{p.id}}({{p.items.CType}} value)
{
	{/* TODO minimum, maximum, constrain check */}
	this->{{p.id}}->push_back(value);
}

{% endif %}
{/* add enum specific functions */}
{% if p.enum && p.type != 'array' %}
// --> Do NOT EDIT <--
bool {{DataClass.stubName}}::is_{{p.id}}(const {{p.CType}} &value) const
{
{% if p.isPtr %}
	return ( (*this->{{p.id}}) == (*value) );
{% else %}
	return ( this->{{p.id}} == value );
{% endif %}
}

{% endif %}
{% endfor %}

{{ closeNamespace(global.namespace) }}