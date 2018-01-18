cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(PROJECT_NAME sqlite)

project(${PROJECT_NAME} C)

message("Building on: ${CMAKE_SYSTEM_NAME}")

set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib" CACHE PATH "Installation directory for libraries")
set(INSTALL_INC_DIR "${CMAKE_INSTALL_PREFIX}/include" CACHE PATH "Installation directory for headers")

# determine version string
file(STRINGS "${PROJECT_SOURCE_DIR}/sqlite3.h" _sqlite_api_h_VER_STRING REGEX ".*#define[ ]+SQLITE_VERSION[ ]+")

string(REGEX MATCH "[0-9\\.]+" SQLITE_VER_STRING ${_sqlite_api_h_VER_STRING})
string(REGEX MATCHALL "[0-9]+" _sqlite_ver_LIST "${SQLITE_VER_STRING}")
list(LENGTH _sqlite_ver_LIST _sqlite_list_len)
list(GET _sqlite_ver_LIST 0 SQLITE_VER_MAJOR)
list(GET _sqlite_ver_LIST 1 SQLITE_VER_MINOR)
list(GET _sqlite_ver_LIST 2 SQLITE_VER_PATCH)
if(_sqlite_list_len EQUAL 4)
	list(GET _sqlite_ver_LIST 3 SQLITE_VER_PATCHLEVEL)
	message("Patch level: ${SQLITE_VER_PATCHLEVEL}")
endif()

message("FOUND: SQLite version = ${SQLITE_VER_STRING}")

set(SQLITE_STATIC_NAME "${PROJECT_NAME}${SQLITE_VER_MAJOR}")

if(MSVC)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MP /Z7")
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MP")
endif()

find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_LIB_FILE ${PROJECT_SOURCE_DIR}/sqlite${SQLITE_VER_MAJOR}.c)

file(GLOB HDR_FILES ${PROJECT_SOURCE_DIR}/*.h)

add_library(${SQLITE_STATIC_NAME} STATIC ${SRC_LIB_FILE})

list(APPEND TO_INSTALL ${SQLITE_STATIC_NAME})

install(TARGETS ${TO_INSTALL}
		ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
		LIBRARY DESTINATION "${INSTALL_LIB_DIR}" )
install(FILES ${HDR_FILES} DESTINATION "${INSTALL_INC_DIR}")