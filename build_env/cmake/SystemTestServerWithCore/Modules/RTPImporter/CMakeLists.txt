cmake_minimum_required(VERSION 2.8.12)

project(RTPImporter)

set(ConnectedVisionCppRoot ../../../../../)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(RTPImporter_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/Class_RTPImporter_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/Class_RTPImporter_params.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporter_ModuleDescription.h
)

set(RTPImporter_DataClasses_Sources
)


set(RTPImporter_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Class_RTPImporter_output_FrameMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Stub_RTPImporter_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Class_RTPImporter_params_Default.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Stub_RTPImporter_params.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Stub_RTPImporter_ModuleDescription.h
)

set(RTPImporter_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Stub_RTPImporter_output_FrameMetadata.cpp
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/stubs/Stub_RTPImporter_params.cpp
)


set(RTPImporter_Stores_Stubs_Headers
)

set(RTPImporter_Stores_Stubs_Sources
)


set(RTPImporter_Stores_Headers
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/Store_Manager_Ringbuffer_RTPImporter_output_FrameMetadata.h
)

set(RTPImporter_Stores_Sources
)


set(RTPImporter_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/OutputPin_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/OutputPin_FramePNG.h
)

set(RTPImporter_OutputPins_Sources
)


set(RTPImporter_OutputPins_Stubs_Headers
)

set(RTPImporter_OutputPins_Stubs_Sources
)


set(RTPImporter_Module_Headers
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporterModule.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporterWorker.h
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporterModuleFactory.h
)

set(RTPImporter_Module_Sources
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporterModule.cpp
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporterWorker.cpp
	${ConnectedVisionCppRoot}/modules/RTPImporter/src/RTPImporterModuleFactory.cpp
)

include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${RTPImporter_DataClasses_Headers}
	${RTPImporter_DataClasses_Stubs_Headers}
	${RTPImporter_Stores_Stubs_Headers}
	${RTPImporter_Stores_Headers}
	${RTPImporter_OutputPins_Headers}
	${RTPImporter_OutputPins_Stubs_Headers}
	${RTPImporter_Module_Headers}
)

set(SOURCES
	${RTPImporter_DataClasses_Sources}
	${RTPImporter_DataClasses_Stubs_Sources}
	${RTPImporter_Stores_Stubs_Sources}
	${RTPImporter_Stores_Sources}
	${RTPImporter_OutputPins_Sources}
	${RTPImporter_OutputPins_Stubs_Sources}
	${RTPImporter_Module_Sources}
)


source_group(DataClasses FILES
	${RTPImporter_DataClasses_Headers}
	${RTPImporter_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${RTPImporter_DataClasses_Stubs_Headers}
	${RTPImporter_DataClasses_Stubs_Sources}
)
source_group(Stores\\Stubs FILES
	${RTPImporter_Stores_Stubs_Headers}
	${RTPImporter_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${RTPImporter_Stores_Headers}
	${RTPImporter_Stores_Sources}
)
source_group(OutputPins FILES
	${RTPImporter_OutputPins_Headers}
	${RTPImporter_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${RTPImporter_OutputPins_Stubs_Headers}
	${RTPImporter_OutputPins_Stubs_Sources}
)
source_group(Module FILES
	${RTPImporter_Module_Headers}
	${RTPImporter_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)