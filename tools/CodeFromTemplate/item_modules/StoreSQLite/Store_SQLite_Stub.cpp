{%- autoescape false -%}{%- include global.macroPath -%}
// auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision
// CodeFromTemplate Version: {{global.codeFromTemplateVersion}}
// {{StoreSQLite.stubSourcePath}}
// NEVER TOUCH this file!

#include <exception>
#include <boost/assign/list_of.hpp>

#include "{{global.relativeStubToSrcPath}}{{StoreSQLite.headerPath}}"

#include "{{StoreSQLite.stubHeaderName}}"

// --> Do NOT EDIT <--
{{ openNamespace(global.namespace) }}
namespace DataHandling {

//////////////////////////////////////////////////////////////////////////////
//
// {{StoreSQLite.stubName}}
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
static const std::string _tableName = "{{StoreSQLite.table.name}}";

// --> Do NOT EDIT <--
static const std::vector<std::string> _columnDesc = boost::assign::list_of
{% for c in StoreSQLite.table.columns %}
	("'{{c.columnName}}' {{c.SQLType}} {% if c.required %} NOT NULL {%- endif %}{% if c.SQLdefault || c.required %} DEFAULT '{{c.SQLdefault}}' {%- endif %} /* {{c.description}} ({{c.type}}) */")
{% endfor %};

// --> Do NOT EDIT <--
{{StoreSQLite.stubName}}::{{StoreSQLite.stubName}}(const id_t& configID, DBConnection& db) :
	Store_SQLite_BaseClass<{{DataClass.className}}>(configID, db, _tableName, _columnDesc)
{
}

// --> Do NOT EDIT <--
{{StoreSQLite.stubName}}::~{{StoreSQLite.stubName}}()
{
}

{/* search functions */}
#ifdef ENABLE_SQLITE_SEARCH
{% for c in StoreSQLite.table.columns %}
{% if c.isSearchable %}
// --> Do NOT EDIT <--
/**
 *  Get objects filtered by {{c.columnName}}
 */
std::vector<shared_ptr<const {{DataClass.className}}> > {{StoreSQLite.stubName}}::getBy_{{c.id}}(const {{c.CType}}& val)
{
	std::vector< Store::FilterEntry > filterList;
	std::vector< Store::SortEntry > sortList;
{% if c.exttype == 'id' %}
	filterList.push_back( Store::FilterEntry("{{c.columnName}}", Store::Op::EQUAL, IDToStr(val) ) );
{% elseif c.type == 'string' && p.isPtr %}
	filterList.push_back( Store::FilterEntry("{{c.columnName}}", Store::Op::EQUAL, *val) );
{% else %}
	filterList.push_back( Store::FilterEntry("{{c.columnName}}", Store::Op::EQUAL, val) );
{% endif %}
	return getByFilter(filterList, sortList);
}

{% endif %}
{% endfor %}
#endif

// --> Do NOT EDIT <--
int {{StoreSQLite.stubName}}::readObject(sqlite3_stmt *stmt, shared_ptr<const {{DataClass.className}}>& outObj, sqlite3 *db)
{
	int error = SQLITE_ROW;

{% set _objSortIDidx = 'undefined' %}
{% for c in StoreSQLite.table.columns %}
{% if c.columnName == StoreSQLite.SQL_OBJSORTID && c.metaField %}
	{% set _objSortIDidx = c.columnIndex %}
{% endif %}
{% endfor %}
	int64_t objSortID = sqlite3_column_int64(stmt, {{_objSortIDidx}});
	int64_t sortID = objSortID;
	outObj.reset( new {{DataClass.className}}() );
	auto obj = this->create();

	while ( (error == SQLITE_ROW) && (sortID == objSortID) )
	{
{% macro setterMacro( setter, value, useAssign ) %}
{% if useAssign %}
{{setter}} = {{value }};
{% else %}
{{setter}}( {{value }} );
{% endif %}
{% endmacro %}
{% macro readObjectColumnsMacro( obj, rvalue_reference, accessor, useAssign ) %}
{% for c in obj %}
{% set c_depth_minus_1 = c.depth - 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% if c.depth > 1 %}{% set _o = "o" + c_depth_minus_1 %}{% else %}{% set _o = 'obj' %}{% endif %}
{% if accessor %}{% set _get = accessor %}{% else %}{% set _get = _o+'->get_'+c.id+'()' %}{% endif %}
{% if accessor %}{% set _set = accessor %}{% else %}{% set _set = _o+'->set_'+c.id %}{% endif %}
{{c.depth|tabs}}		// {{c.name|replace('\.', '_', 'g')}} -> {{c.CBaseType}}
  {% if c.exttype == 'id' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, 'strToID( reinterpret_cast<const char *>(sqlite3_column_text(stmt,' + c.columnIndex + ') ) )', useAssign) -}}
    {% elseif c.exttype == 'timestamp' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, 'sqlite3_column_int64(stmt,' + c.columnIndex + ')', useAssign) -}}
  {% elseif c.type == 'integer' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, 'sqlite3_column_int64(stmt,' + c.columnIndex + ')', useAssign) -}}
  {% elseif c.type == 'number' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, 'sqlite3_column_double(stmt,' + c.columnIndex + ')', useAssign) -}}
  {% elseif c.type == 'boolean' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, '( sqlite3_column_int(stmt,' + c.columnIndex + ') ? true : false )', useAssign) -}}
  {% elseif c.type == 'string' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, 'boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_text(stmt,' + c.columnIndex + ')) ) )', useAssign) -}}
  {% elseif c.type == 'any' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}			{{ setterMacro( _set, 'boost::shared_ptr<std::string>( new std::string( reinterpret_cast<const char *>(sqlite3_column_blob(stmt,' + c.columnIndex + ')), sqlite3_column_bytes(stmt,' + c.columnIndex + ') ) )', useAssign) -}}
  {% elseif c.type == 'array' %}
  {{c.depth|tabs}}		if ( sqlite3_column_type(stmt, {{c.columnIndex}}) != SQLITE_NULL )
  {{c.depth|tabs}}		{
{%- set _a = "a" + c.depth %}{% set _idx = "idx" + c.depth %}
  {% if rvalue_reference %}
  {{c.depth|tabs}}			{{c.CType}}&& {{_a}} = {{_get}}; // rvalue reference for const functions
  {% else %}
  {{c.depth|tabs}}			{{c.CType}}& {{_a}} = {{_get}}; // lvalue reference for non-const functions like vector::at()
  {% endif %}
  {{c.depth|tabs}}			if ( !{{_a}} ) {{_a}}.reset( new {{c.CBaseType}} );
  {{c.depth|tabs}}			size_t {{_idx}} = static_cast<size_t>( sqlite3_column_int64(stmt,{{c.columnIndex}}) );
  {{c.depth|tabs}}			if ( {{_idx}} >= {{_a}}->size() ) {{_a}}->resize( {{_idx}} +1 );
{{ readObjectColumnsMacro([c.items], false, _a+'->at('+_idx+')', true) -}}
  {{c.depth|tabs}}		}
  {% elseif c.type == 'object' %}
  {{c.depth|tabs}}		{
{% set _s = "o" + c.depth %}
  {% if rvalue_reference %}
  {{c.depth|tabs}}			{{c.CType}}&& {{_s}} = {{_get}}; // rvalue reference for const functions
  {% else %}
  {{c.depth|tabs}}			{{c.CType}}& {{_s}} = {{_get}}; // lvalue reference for non-const functions like vector::at()
  {% endif %}
  {{c.depth|tabs}}			if ( !{{_s}} ) {{_s}}.reset( new {{c.CBaseType}} );
{{ readObjectColumnsMacro(c.properties, true) -}}
{% set c_depth_minus_1 = c.depth - 1 %}{/* workaround for non working parenthesis in x86 node.js */}
{% if c.depth > 1 %}{% set _o = "o" + c_depth_minus_1 %}{% else %}{% set _o = 'obj' %}{% endif %}
  {{c.depth|tabs}}		}
  {% elseif c.exttype == 'null' %}
		// NULL read for: {{c.columnName}}
  {% else %}
		#error unsupported type for: {{c.columnName}} -> {{c.exttype}}
  {% endif %}
{% endfor %}{% endmacro %}
		// process row
{{ readObjectColumnsMacro(StoreSQLite.obj.properties, true) }}
		error = sqlite3_step(stmt);
		if ( error == SQLITE_ROW )
			sortID = sqlite3_column_int64(stmt, {{_objSortIDidx}});
	}

	outObj = this->make_const(obj);
	return error;
}

// --> Do NOT EDIT <--
int {{StoreSQLite.stubName}}::writeObject(sqlite3_stmt *stmt, const shared_ptr<const {{DataClass.className}}>& obj, sqlite3 *db, const int64_t sortID)
{
	int error = 0;

{% set _objSortIDidx = 'undefined' %}
{% for c in StoreSQLite.table.columns %}
{% if c.columnName == StoreSQLite.SQL_OBJSORTID && c.metaField %}
	{% set _objSortIDidx = c.columnIndex %}
{% endif %}
{% endfor %}
{/* count number of indices / maximum depth of arrays */}
{% set _idxCount = 0 %}
{% for b in StoreSQLite.table.columns %}
{% for i in b.idxKeys %} 
{% if _idxCount < loop.index %}{% set _idxCount = loop.index %}{% endif %}
{% endfor %}
{% endfor %}
{/* create helper array */}
{% set _idxArray = Array(_idxCount) %}

{% for _idx in _idxArray %}
{% set _idx = loop.index %}
		size_t i{{_idx}}_max = 1;
{% for b in StoreSQLite.table.columns %}
{% if b.type == 'array' && _idx == b.idxKeys.length %}
{% for i in b.idxKeys %}
{% if loop.index < _idx %}
		if ( i{{loop.index}} < obj->{{i.getter}}->size() )
		{% endif %}
{% endfor %}
		if ( i{{_idx}}_max < obj->{{b.getter}}->size() )
			i{{_idx}}_max = obj->{{b.getter}}->size();
{% endif %}
{% endfor %}
	for ( size_t i{{_idx}} = 0; i{{_idx}} < i{{_idx}}_max; i{{_idx}}++ )
	{
{% endfor %}
		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);
{% for b in StoreSQLite.table.objectBindings %}
{% if b.idxKeys.length %}
		// enforce left-to-right evaluation
{% for i in b.idxKeys %}		if ( i{{loop.index}} < obj->{{i.getter}}->size() ) {% endfor %}
{% endif %}

		bind_{{b.bindingName}}( stmt, obj{% if b.getter %}->{{b.getter}}{% endif %}, sortID{% for i in b.idxKeys %}, i{{loop.index}} {% endfor %} );
{% endfor %}
		// write object base data and sub objects
		error = sqlite3_step(stmt);
		if ( error != SQLITE_DONE )
			return error;
{% for i in _idxArray %}
	}
{% endfor %}
	return error;
}
{% for b in StoreSQLite.table.objectBindings %}

// --> Do NOT EDIT <--
void {{StoreSQLite.stubName}}::bind_{{b.bindingName}}(sqlite3_stmt *stmt, const {{b.CConstType}}& obj, const int64_t sortID {% for i in b.idxKeys %}, const int64_t idx{{loop.index}} {% endfor %}) const
{
{% set _objSortIDidx = 'undefined' %}
{% for c in StoreSQLite.table.columns %}
{% if c.columnName == StoreSQLite.SQL_OBJSORTID && c.metaField %}
	{% set _objSortIDidx = c.columnIndex %}
{% endif %}
{% endfor %}
	sqlite3_bind_int64(stmt, {{_objSortIDidx+1}}, sortID );
{% for i in b.idxKeys %}
	sqlite3_bind_int64(stmt, {{i.columnIndex+1}}, idx{{loop.index}} );
{% endfor %}
{% for c in b.properties %}
{% set _getter = 'obj' %}
{% if c.parent.type == 'object' %}
{% set _getter = 'obj->getconst_' + c.id + '()' %}
{% endif %}
{/*	// {{DataClass.name}}_{{c.columnName|replace('\.', '_', 'g')}} -> {{c.CBaseType}} */}
  {% if c.exttype == 'id' %}
	sqlite3_bind_text(stmt, {{c.columnIndex+1}}, IDToChar({{_getter}}), -1, SQLITE_TRANSIENT);
  {% elseif c.exttype == 'timestamp' %}
	sqlite3_bind_int64(stmt, {{c.columnIndex+1}}, {{_getter}} );
  {% elseif c.type == 'integer' %}
  	sqlite3_bind_int64(stmt, {{c.columnIndex+1}}, {{_getter}} );
  {% elseif c.type == 'number' %}
  	sqlite3_bind_double(stmt, {{c.columnIndex+1}}, {{_getter}} );
  {% elseif c.type == 'boolean' %}
	sqlite3_bind_int64(stmt, {{c.columnIndex+1}}, {{_getter}} );
  {% elseif c.type == 'string' %}
  	sqlite3_bind_text(stmt, {{c.columnIndex+1}}, {{_getter}}->c_str(), -1, SQLITE_TRANSIENT );
  {% elseif c.type == 'any' %}
  	sqlite3_bind_blob(stmt, {{c.columnIndex+1}}, {{_getter}}->c_str(), (int){{_getter}}->size(), SQLITE_TRANSIENT); // TODO update & use sqlite3_bind_blob64()
  {% elseif c.type == 'array' %}
  	// array: {{c.id}} handled separately
  {% elseif c.type == 'object' %}
	// object: {{c.id}} handled separately
  {% elseif c.type == 'null' %}
	// NULL read for: {{c.id}}
  {% else %}
	#error unsupported type for: {{c.columnName}} -> {{c.type}}
  {% endif %}
{% endfor %}
}
{% endfor %}

// --> Do NOT EDIT <--
void {{StoreSQLite.stubName}}::appendObjectGrouping(std::vector< Store::SortEntry >& sortList) const
{
	sortList.push_back( Store::SortEntry ("{{StoreSQLite.SQL_OBJSORTID}}", Store::Order::ASC) );
}

// --> Do NOT EDIT <--
/**
 *  append object internal sort criteria to list
 */
const std::string {{StoreSQLite.stubName}}::objectKey() const
{
	return std::string("{{StoreSQLite.SQL_OBJSORTID}}");
}


//////////////////////////////////////////////////////////////////////////////
//
// {{StoreSQLite.factoryStubName}}
//
//////////////////////////////////////////////////////////////////////////////

// --> Do NOT EDIT <--
{{StoreSQLite.factoryStubName}}::{{StoreSQLite.factoryStubName}}(DBConnection& db) :
	db(db)
{}

// --> Do NOT EDIT <--
{{StoreSQLite.factoryStubName}}::~{{StoreSQLite.factoryStubName}}()
{}

shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<{{DataClass.className}}> > {{StoreSQLite.factoryStubName}}::create(const id_t configID = ID_NULL)
{
#ifdef {{StoreSQLite.factoryName}}_enabled
	return boost::dynamic_pointer_cast< ConnectedVision::DataHandling::IStore_ReadWrite<{{DataClass.className}}> > (make_shared< DataHandling::{{StoreSQLite.className}} >(configID, this->db));
#else
	return shared_ptr< ConnectedVision::DataHandling::IStore_ReadWrite<{{DataClass.className}}> >();
#endif
}


} // namespace DataHandling
{{ closeNamespace(global.namespace) }}