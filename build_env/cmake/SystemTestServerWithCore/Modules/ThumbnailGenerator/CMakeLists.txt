cmake_minimum_required(VERSION 2.8.12)

project(ThumbnailGenerator)

set(ConnectedVisionCppRoot ../../../../../)

include(${ConnectedVisionCppRoot}/build_env/cmake/common.cmake)

execute_conan_cmake_run_without_targets()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/${ConnectedVisionCppRoot}" CACHE PATH "default install path" FORCE)
endif()


set(ThumbnailGenerator_DataClasses_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Class_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Class_ThumbnailGenerator_input_BoundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Class_ThumbnailGenerator_input_BoundingBox_boundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Class_ThumbnailGenerator_params.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Class_ThumbnailGenerator_params_lineColor.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGenerator_ModuleDescription.h
)

set(ThumbnailGenerator_DataClasses_Sources
)


set(ThumbnailGenerator_DataClasses_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Class_ThumbnailGenerator_input_ImageMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Class_ThumbnailGenerator_input_BoundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_input_BoundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Class_ThumbnailGenerator_input_BoundingBox_boundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_input_BoundingBox_boundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Class_ThumbnailGenerator_params_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_params.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Class_ThumbnailGenerator_params_lineColor_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_params_lineColor.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_ModuleDescription.h
)

set(ThumbnailGenerator_DataClasses_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_input_ImageMetadata.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_input_BoundingBox.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_input_BoundingBox_boundingBox.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_params.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Stub_ThumbnailGenerator_params_lineColor.cpp
)


set(ThumbnailGenerator_InputPins_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/InputPin_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/InputPin_ThumbnailGenerator_input_BoundingBox.h
)

set(ThumbnailGenerator_InputPins_Sources
)

set(ThumbnailGenerator_OutputPins_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ImageOutputPin.h
)

set(ThumbnailGenerator_OutputPins_Sources
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ImageOutputPin.cpp
)


set(ThumbnailGenerator_InputPins_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/InputPin_ThumbnailGenerator_input_ImageMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/InputPin_Stub_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/InputPin_ThumbnailGenerator_input_BoundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/InputPin_Stub_ThumbnailGenerator_input_BoundingBox.h
)

set(ThumbnailGenerator_InputPins_Stubs_Sources
)


set(ThumbnailGenerator_Stores_Stubs_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/sql/ThumbnailGenerator_input_ImageMetadata.sql
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_SQLite_ThumbnailGenerator_input_ImageMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_Ringbuffer_ThumbnailGenerator_input_ImageMetadata_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/sql/ThumbnailGenerator_input_BoundingBox.sql
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_SQLite_ThumbnailGenerator_input_BoundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_SQLite_ThumbnailGenerator_input_BoundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_SQLite_Stub_ThumbnailGenerator_input_BoundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox_Default.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox.h
)

set(ThumbnailGenerator_Stores_Stubs_Sources
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_SQLite_Stub_ThumbnailGenerator_input_ImageMetadata.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_ImageMetadata.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_SQLite_Stub_ThumbnailGenerator_input_BoundingBox.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_SQLite_Stub_ThumbnailGenerator_input_BoundingBox.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/stubs/Store_Manager_Ringbuffer_Stub_ThumbnailGenerator_input_BoundingBox.cpp
)


set(ThumbnailGenerator_Stores_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Store_Manager_SQLite_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Store_SQLite_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Store_Manager_Ringbuffer_ThumbnailGenerator_input_ImageMetadata.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Store_Manager_SQLite_ThumbnailGenerator_input_BoundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Store_SQLite_ThumbnailGenerator_input_BoundingBox.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/Store_Manager_Ringbuffer_ThumbnailGenerator_input_BoundingBox.h
)

set(ThumbnailGenerator_Stores_Sources
)


set(ThumbnailGenerator_Module_Headers
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGeneratorModule.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGeneratorWorker.h
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGeneratorModuleFactory.h
)

set(ThumbnailGenerator_Module_Sources
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGeneratorModule.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGeneratorWorker.cpp
	${ConnectedVisionCppRoot}/modules/ThumbnailGenerator/src/ThumbnailGeneratorModuleFactory.cpp
)



include_directories(
	${ConnectedVisionCppRoot}/core/include/
	${ConnectedVisionCppRoot}/core/src/
)


set(HEADERS
	${ThumbnailGenerator_DataClasses_Headers}
	${ThumbnailGenerator_DataClasses_Stubs_Headers}
	${ThumbnailGenerator_InputPins_Headers}
	${ThumbnailGenerator_InputPins_Stubs_Headers}
	${ThumbnailGenerator_OutputPins_Headers}
	${ThumbnailGenerator_Stores_Stubs_Headers}
	${ThumbnailGenerator_Stores_Headers}
	${ThumbnailGenerator_Module_Headers}
)

set(SOURCES
	${ThumbnailGenerator_DataClasses_Sources}
	${ThumbnailGenerator_DataClasses_Stubs_Sources}
	${ThumbnailGenerator_InputPins_Sources}
	${ThumbnailGenerator_InputPins_Stubs_Sources}
	${ThumbnailGenerator_OutputPins_Sources}
	${ThumbnailGenerator_Stores_Stubs_Sources}
	${ThumbnailGenerator_Stores_Sources}
	${ThumbnailGenerator_Module_Sources}
)


source_group(DataClasses FILES
	${ThumbnailGenerator_DataClasses_Headers}
	${ThumbnailGenerator_DataClasses_Sources}
)
source_group(DataClasses\\Stubs FILES
	${ThumbnailGenerator_DataClasses_Stubs_Headers}
	${ThumbnailGenerator_DataClasses_Stubs_Sources}
)
source_group(InputPins FILES
	${ThumbnailGenerator_InputPins_Headers}
	${ThumbnailGenerator_InputPins_Sources}
)
source_group(InputPins\\Stubs FILES
	${ThumbnailGenerator_InputPins_Stubs_Headers}
	${ThumbnailGenerator_InputPins_Stubs_Sources}
)
source_group(OutputPins FILES
	${ThumbnailGenerator_OutputPins_Headers}
	${ThumbnailGenerator_OutputPins_Sources}
)
source_group(Stores\\Stubs FILES
	${ThumbnailGenerator_Stores_Stubs_Headers}
	${ThumbnailGenerator_Stores_Stubs_Sources}
)
source_group(Stores FILES
	${ThumbnailGenerator_Stores_Headers}
	${ThumbnailGenerator_Stores_Sources}
)
source_group(Module FILES
	${ThumbnailGenerator_Module_Headers}
	${ThumbnailGenerator_Module_Sources}
)


add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})

get_lib_install_directory(InstallDirectory)

install(TARGETS ${PROJECT_NAME} DESTINATION ${InstallDirectory})

install(FILES
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}Module.h"
	"${ConnectedVisionCppRoot}/modules/${PROJECT_NAME}/src/${PROJECT_NAME}ModuleFactory.h"
	DESTINATION "include/Modules/${PROJECT_NAME}"
)