cmake_minimum_required(VERSION 2.8.12)

project(FileImporter)

set(ConnectedVisionCppRoot ../../../../../)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(FileImporter_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/FileImporter/src/Class_FileImporter_params.h
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileImporter_ModuleDescription.h
)

set(FileImporter_DataClasses_Sources
)


set(FileImporter_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/FileImporter/src/stubs/Class_FileImporter_params_Default.h
	${ConnectedVisionCppRoot}/modules/FileImporter/src/stubs/Stub_FileImporter_params.h
	${ConnectedVisionCppRoot}/modules/FileImporter/src/stubs/Stub_FileImporter_ModuleDescription.h
)

set(FileImporter_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/FileImporter/src/stubs/Stub_FileImporter_params.cpp
)


set(FileImporter_Module_Headers
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileImporterModule.h
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileImporterModuleFactory.h
)

set(FileImporter_Module_Sources
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileImporterModule.cpp
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileImporterModuleFactory.cpp
)


set(FileImporter_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileOutputPin.h
)

set(FileImporter_OutputPins_Sources
	${ConnectedVisionCppRoot}/modules/FileImporter/src/FileOutputPin.cpp
)



include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${FileImporter_DataClasses_Headers}
	${FileImporter_DataClasses_Stubs_Headers}
	${FileImporter_Module_Headers}
	${FileImporter_OutputPins_Headers}
)

set(SOURCES
	${FileImporter_DataClasses_Sources}
	${FileImporter_DataClasses_Stubs_Sources}
	${FileImporter_Module_Sources}
	${FileImporter_OutputPins_Sources}
)


source_group(DataClasses FILES
	${FileImporter_DataClasses_Headers}
	${FileImporter_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${FileImporter_DataClasses_Stubs_Headers}
	${FileImporter_DataClasses_Stubs_Sources}
)
source_group(Module FILES
	${FileImporter_Module_Headers}
	${FileImporter_Module_Sources}
)
source_group(OutputPins FILES
	${FileImporter_OutputPins_Headers}
	${FileImporter_OutputPins_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)