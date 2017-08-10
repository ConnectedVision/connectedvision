{% macro openNamespace(namespaceArray) %}{% for n in namespaceArray %}namespace {{n}} {{ "{" }}{% if not loop.last %}
{% endif %}{% endfor %}{% endmacro %}{% macro closeNamespace(namespaceArray) %}{% for n in namespaceArray %}{{ "}" }} // namespace {{namespaceArray[loop.revindex0]}}{% if not loop.last %}
{% endif %}{% endfor %}{% endmacro %}