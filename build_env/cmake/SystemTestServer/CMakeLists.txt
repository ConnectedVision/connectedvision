cmake_minimum_required(VERSION 2.8.12)

project(SystemTestServer)

option(USE_INSTALL_SUBDIRECTORY_STRUCTURE "create a subdirectory structure for the install directory which consists of architecture and configuration type" OFF)

set(ConnectedVisionCppRoot ../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()
execute_conan_cmake_run_with_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()

include_directories(
	${ConnectedVisionCppRoot}/core/include
	${ConnectedVisionCppRoot}/core/src
)

get_lib_directory(LibDirectory)

if(NOT IS_ABSOLUTE ${LibDirectory})
	set(LibDirectory "${ConnectedVisionCppRoot}/${LibDirectory}")
endif()

link_directories(${LibDirectory})

set(PlatformSpecificSources)

if(MSVC)
	get_conan_variable("CONAN_INCLUDE_DIRS_STACKWALKER" StackWalkerIncludeDir)
	set(PlatformSpecificSources ${StackWalkerIncludeDir}/StackWalker.cpp)
endif()

set(SOURCES
	${ConnectedVisionCppRoot}/test/SystemTestServer/src/main.cpp
	${PlatformSpecificSources}
)

add_executable(${PROJECT_NAME} ${SOURCES})


target_link_libraries(${PROJECT_NAME}
	DirectoryIterator
	DummyBoundingBoxes
	FileExport
	FileImporter
	RTPImporter
	SyntheticVideo
	ThumbnailGenerator
	VideoImporter
	
	ConnectedVisionCore
	
	CONAN_PKG::Boost
	CONAN_PKG::FFmpeg
	CONAN_PKG::OpenCV
	CONAN_PKG::OpenSSL
	CONAN_PKG::POCO
	CONAN_PKG::SQLite
	CONAN_PKG::zlib
)


if(MSVC)
	# set startup project
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
endif()

get_bin_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})