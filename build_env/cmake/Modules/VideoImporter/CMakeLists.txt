cmake_minimum_required(VERSION 2.8.12)

project(VideoImporter)

set(ConnectedVisionCppRoot ../../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(VideoImporter_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/Class_VideoImporter_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/Class_VideoImporter_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/Class_VideoImporter_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/Class_VideoImporter_params.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporter_ModuleDescription.h
)

set(VideoImporter_DataClasses_Sources
)


set(VideoImporter_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Class_VideoImporter_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_input_Trigger.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Class_VideoImporter_output_VideoMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Class_VideoImporter_output_FrameMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Class_VideoImporter_params_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_params.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_ModuleDescription.h
)

set(VideoImporter_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_input_Trigger.cpp
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_output_VideoMetadata.cpp
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_output_FrameMetadata.cpp
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/Stub_VideoImporter_params.cpp
)


set(VideoImporter_InputPins_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/InputPin_VideoImporter_input_Trigger.h
)

set(VideoImporter_InputPins_Sources
)


set(VideoImporter_InputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/InputPin_VideoImporter_input_Trigger_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/InputPin_Stub_VideoImporter_input_Trigger.h
)

set(VideoImporter_InputPins_Stubs_Sources
)


set(VideoImporter_Stores_Stubs_Headers
)

set(VideoImporter_Stores_Stubs_Sources
)


set(VideoImporter_Stores_Headers
)

set(VideoImporter_Stores_Sources
)


set(VideoImporter_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/OutputPin_VideoImporter_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/OutputPin_VideoImporter_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoDataOutputPin.h
)

set(VideoImporter_OutputPins_Sources
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoDataOutputPin.cpp
)


set(VideoImporter_OutputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/OutputPin_VideoImporter_output_VideoMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/OutputPin_Stub_VideoImporter_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/OutputPin_VideoImporter_output_FrameMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/stubs/OutputPin_Stub_VideoImporter_output_FrameMetadata.h
)

set(VideoImporter_OutputPins_Stubs_Sources
)


set(VideoImporter_Module_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterModule.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterModule_priv.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterWorker.h
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterModuleFactory.h
)

set(VideoImporter_Module_Sources
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterModule.cpp
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterWorker.cpp
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImporterModuleFactory.cpp
)

set(VideoImporter_VideoImport_FFmpeg_Headers
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImport_FFmpeg/VideoImport_FFmpeg.h
)

set(VideoImporter_VideoImport_FFmpeg_Sources
	${ConnectedVisionCppRoot}/modules/VideoImporter/src/VideoImport_FFmpeg/VideoImport_FFmpeg.cpp
)

include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${VideoImporter_DataClasses_Headers}
	${VideoImporter_DataClasses_Stubs_Headers}
	${VideoImporter_InputPins_Headers}
	${VideoImporter_InputPins_Stubs_Headers}
	${VideoImporter_Stores_Stubs_Headers}
	${VideoImporter_Stores_Headers}
	${VideoImporter_OutputPins_Headers}
	${VideoImporter_OutputPins_Stubs_Headers}
	${VideoImporter_Module_Headers}
	${VideoImporter_VideoImport_FFmpeg_Headers}
)

set(SOURCES
	${VideoImporter_DataClasses_Sources}
	${VideoImporter_DataClasses_Stubs_Sources}
	${VideoImporter_InputPins_Sources}
	${VideoImporter_InputPins_Stubs_Sources}
	${VideoImporter_Stores_Stubs_Sources}
	${VideoImporter_Stores_Sources}
	${VideoImporter_OutputPins_Sources}
	${VideoImporter_OutputPins_Stubs_Sources}
	${VideoImporter_Module_Sources}
	${VideoImporter_VideoImport_FFmpeg_Sources}
)


source_group(DataClasses FILES
	${VideoImporter_DataClasses_Headers}
	${VideoImporter_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${VideoImporter_DataClasses_Stubs_Headers}
	${VideoImporter_DataClasses_Stubs_Sources}
)
source_group(InputPins FILES
	${VideoImporter_InputPins_Headers}
	${VideoImporter_InputPins_Sources}
)
source_group(InputPins\\Stubs FILES
	${VideoImporter_InputPins_Stubs_Headers}
	${VideoImporter_InputPins_Stubs_Sources}
)
source_group(Stores\\Stubs FILES
	${VideoImporter_Stores_Stubs_Headers}
	${VideoImporter_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${VideoImporter_Stores_Headers}
	${VideoImporter_Stores_Sources}
)
source_group(OutputPins FILES
	${VideoImporter_OutputPins_Headers}
	${VideoImporter_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${VideoImporter_OutputPins_Stubs_Headers}
	${VideoImporter_OutputPins_Stubs_Sources}
)
source_group(Module FILES
	${VideoImporter_Module_Headers}
	${VideoImporter_Module_Sources}
)
source_group(VideoImport_FFmpeg FILES
	${VideoImporter_VideoImport_FFmpeg_Headers}
	${VideoImporter_VideoImport_FFmpeg_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)