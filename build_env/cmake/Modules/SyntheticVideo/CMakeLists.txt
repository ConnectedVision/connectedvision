cmake_minimum_required(VERSION 2.8.12)

project(SyntheticVideo)

set(ConnectedVisionCppRoot ../../../..)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(SyntheticVideo_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/Class_SyntheticVideo_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/Class_SyntheticVideo_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/Class_SyntheticVideo_params.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/Class_SyntheticVideo_params_bgColor.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/Class_SyntheticVideo_params_fgColor.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/Class_SyntheticVideo_params_osdTextColor.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideo_ModuleDescription.h
)

set(SyntheticVideo_DataClasses_Sources
)


set(SyntheticVideo_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Class_SyntheticVideo_output_VideoMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Class_SyntheticVideo_output_FrameMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Class_SyntheticVideo_params_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Class_SyntheticVideo_params_bgColor_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params_bgColor.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Class_SyntheticVideo_params_fgColor_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params_fgColor.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Class_SyntheticVideo_params_osdTextColor_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params_osdTextColor.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_ModuleDescription.h
)

set(SyntheticVideo_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_output_VideoMetadata.cpp
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_output_FrameMetadata.cpp
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params.cpp
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params_bgColor.cpp
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params_fgColor.cpp
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/Stub_SyntheticVideo_params_osdTextColor.cpp
)


set(SyntheticVideo_Stores_Stubs_Headers
)

set(SyntheticVideo_Stores_Stubs_Sources
)


set(SyntheticVideo_Stores_Headers
)

set(SyntheticVideo_Stores_Sources
)


set(SyntheticVideo_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/OutputPin_SyntheticVideo_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/OutputPin_SyntheticVideo_output_FrameMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoDataOutputPin.h
)

set(SyntheticVideo_OutputPins_Sources
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoDataOutputPin.cpp
)


set(SyntheticVideo_OutputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/OutputPin_SyntheticVideo_output_VideoMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/OutputPin_Stub_SyntheticVideo_output_VideoMetadata.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/OutputPin_SyntheticVideo_output_FrameMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/stubs/OutputPin_Stub_SyntheticVideo_output_FrameMetadata.h
)

set(SyntheticVideo_OutputPins_Stubs_Sources
)


set(SyntheticVideo_Module_Headers
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoModule.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoModuleFactory.h
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoModule_priv.h
)

set(SyntheticVideo_Module_Sources
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoModule.cpp
	${ConnectedVisionCppRoot}/modules/SyntheticVideo/src/SyntheticVideoModuleFactory.cpp
)



include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${SyntheticVideo_DataClasses_Headers}
	${SyntheticVideo_DataClasses_Stubs_Headers}
	${SyntheticVideo_Stores_Stubs_Headers}
	${SyntheticVideo_Stores_Headers}
	${SyntheticVideo_OutputPins_Headers}
	${SyntheticVideo_OutputPins_Stubs_Headers}
	${SyntheticVideo_Module_Headers}
)

set(SOURCES
	${SyntheticVideo_DataClasses_Sources}
	${SyntheticVideo_DataClasses_Stubs_Sources}
	${SyntheticVideo_Stores_Stubs_Sources}
	${SyntheticVideo_Stores_Sources}
	${SyntheticVideo_OutputPins_Sources}
	${SyntheticVideo_OutputPins_Stubs_Sources}
	${SyntheticVideo_Module_Sources}
)


source_group(DataClasses FILES
	${SyntheticVideo_DataClasses_Headers}
	${SyntheticVideo_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${SyntheticVideo_DataClasses_Stubs_Headers}
	${SyntheticVideo_DataClasses_Stubs_Sources}
)
source_group(Stores\\Stubs FILES
	${SyntheticVideo_Stores_Stubs_Headers}
	${SyntheticVideo_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${SyntheticVideo_Stores_Headers}
	${SyntheticVideo_Stores_Sources}
)
source_group(OutputPins FILES
	${SyntheticVideo_OutputPins_Headers}
	${SyntheticVideo_OutputPins_Sources}
)
source_group(OutputPins\\Stubs FILES
	${SyntheticVideo_OutputPins_Stubs_Headers}
	${SyntheticVideo_OutputPins_Stubs_Sources}
)
source_group(Module FILES
	${SyntheticVideo_Module_Headers}
	${SyntheticVideo_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)