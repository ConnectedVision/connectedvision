cmake_minimum_required(VERSION 2.8.12)
project(FileExport)

set(ConnectedVisionCppRoot ../../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(FileExport_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/FileExport/src/Class_FileExport_output_FileExportTrigger.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/Class_FileExport_params.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExport_ModuleDescription.h
)

set(FileExport_DataClasses_Sources
)


set(FileExport_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Class_FileExport_output_FileExportTrigger_Default.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Stub_FileExport_output_FileExportTrigger.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Class_FileExport_params_Default.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Stub_FileExport_params.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Stub_FileExport_ModuleDescription.h
)

set(FileExport_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Stub_FileExport_output_FileExportTrigger.cpp
	${ConnectedVisionCppRoot}/modules/FileExport/src/stubs/Stub_FileExport_params.cpp
)

set(FileExport_InputPins_Headers
	${ConnectedVisionCppRoot}/modules/FileExport/src/InputPin_ArbitraryData.h
)

set(FileExport_InputPins_Sources
	${ConnectedVisionCppRoot}/modules/FileExport/src/InputPin_ArbitraryData.cpp
)

set(FileExport_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportTriggerOutputPin.h
)

set(FileExport_OutputPins_Sources
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportTriggerOutputPin.cpp
)


set(FileExport_OutputPins_Stubs_Headers
)

set(FileExport_OutputPins_Stubs_Sources
)


set(FileExport_Module_Headers
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportModule.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportWorker.h
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportModuleFactory.h
)

set(FileExport_Module_Sources
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportModule.cpp
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportWorker.cpp
	${ConnectedVisionCppRoot}/modules/FileExport/src/FileExportModuleFactory.cpp
)



include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${FileExport_DataClasses_Headers}
	${FileExport_DataClasses_Stubs_Headers}
	${FileExport_Stores_Stubs_Headers}
	${FileExport_InputPins_Headers}
	${FileExport_OutputPins_Headers}
	${FileExport_OutputPins_Stubs_Headers}
	${FileExport_Module_Headers}
)

set(SOURCES
	${FileExport_DataClasses_Sources}
	${FileExport_DataClasses_Stubs_Sources}
	${FileExport_Stores_Stubs_Sources}
	${FileExport_InputPins_Sources}
	${FileExport_OutputPins_Sources}
	${FileExport_OutputPins_Stubs_Sources}
	${FileExport_Module_Sources}
)


source_group(DataClasses FILES
	${FileExport_DataClasses_Headers}
	${FileExport_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${FileExport_DataClasses_Stubs_Headers}
	${FileExport_DataClasses_Stubs_Sources}
)
source_group(InputPins FILES
	${FileExport_InputPins_Headers}
	${FileExport_InputPins_Sources}
)
source_group(OutputPins FILES
	${FileExport_OutputPins_Headers}
	${FileExport_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${FileExport_OutputPins_Stubs_Headers}
	${FileExport_OutputPins_Stubs_Sources}
)
source_group(Module FILES
	${FileExport_Module_Headers}
	${FileExport_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)