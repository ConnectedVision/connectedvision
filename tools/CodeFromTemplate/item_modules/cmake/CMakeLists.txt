cmake_minimum_required(VERSION 2.8.12)

project({{cmake.projectName}})

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/../../" CACHE PATH "default install path" FORCE)
endif()

{% for s in cmake.uniqueSections %}

set({{cmake.projectName}}_{{s.name|replace('/', '_', 'g')}}_Headers
{% for d in cmake.files %}
{% if (!d.compileable) && (d.section == s.name) %}
	{{d.path}}
{% endif %}
{% endfor %}
)

set({{cmake.projectName}}_{{s.name|replace('/', '_', 'g')}}_Sources
{% for d in cmake.files %}
{% if (d.compileable) && (d.section == s.name) %}
	{{d.path}}
{% endif %}
{% endfor %}
)

{% endfor %}


# if Connected Vision itself is not provided as a Conan package, then the include directories need to specified explicitly
if(EXISTS "$ENV{ConnectedVision}/core/include")
	include_directories(
		"$ENV{ConnectedVision}/core/include"
		"$ENV{ConnectedVision}/core/src"
	)
endif()


set(HEADERS
	{% for s in cmake.uniqueSections %}
	${ {{-cmake.projectName}}_{{s.name|replace('/', '_', 'g')}}_Headers}
	{% endfor %}
)

set(SOURCES
	{% for s in cmake.uniqueSections %}
	${ {{-cmake.projectName}}_{{s.name|replace('/', '_', 'g')}}_Sources}
	{% endfor %}
)


{% for s in cmake.uniqueSections %}
source_group({{s.name|replace('/', '\\ ', 'g')|replace(' ', '', 'g')}} FILES
	${ {{-cmake.projectName}}_{{s.name|replace('/', '_', 'g')}}_Headers}
	${ {{-cmake.projectName}}_{{s.name|replace('/', '_', 'g')}}_Sources}
)
{% endfor %}


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})