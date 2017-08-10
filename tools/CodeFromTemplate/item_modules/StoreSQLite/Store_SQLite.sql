{%- autoescape false -%}
/* auto-generated header by CodeFromTemplate - Connected Vision - https://github.com/ConnectedVision */
/* CodeFromTemplate Version: {{global.codeFromTemplateVersion}} */
/* {{StoreSQLite.SQLName}} */
/* NEVER TOUCH this file! */

/* This SQL will DELETE ALL existing DATA! */
DROP TABLE IF EXISTS "{{StoreSQLite.table.name}}";
CREATE TABLE "{{StoreSQLite.table.name}}"
(
{% for c in StoreSQLite.table.columns %}
	'{{c.columnName}}' {{c.SQLType}} {% if c.required %} NOT NULL {%- endif %}{% if c.SQLdefault || c.required %} DEFAULT '{{c.SQLdefault}}' {%- endif %} /* {{c.description}} ({{c.type}}) */{% if !loop.last %},{% endif %}

{% endfor %}
);
